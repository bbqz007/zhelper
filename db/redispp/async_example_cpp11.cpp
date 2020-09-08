//
// g++ async_example.cpp -o async_example -I.. -lboost_serialization -lboost_program_options -lhiredis -lev
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <string>
#include <iostream>
#include <hiredis/async.h>

#include <hiredispp.h>
#include <hiredispp_async.h>

#include <thread>

#include <boost/bind.hpp>
#include <boost/random.hpp>
#include <boost/program_options.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>

using namespace std;
using namespace hiredispp;
using namespace boost::posix_time;
using namespace boost::accumulators;

namespace po = boost::program_options;

namespace std
{
    std::ostream& operator << (ostream& os, const Redis::Element& reply)
    {
        switch (reply.get()->type)
        {
        case REDIS_REPLY_STATUS: os << reply.getStatus(); break;
        case REDIS_REPLY_INTEGER: os << (int64_t)reply; break;
        case REDIS_REPLY_NIL: os << "nil"; break;
        case REDIS_REPLY_STRING: os << (string)reply; break;
        case REDIS_REPLY_ARRAY:
            {
                os << "array:" << endl;
                for (int i = 0; i < reply.size(); ++i)
                    os << reply[i] << ", ";
                os << "endarray" << endl;
                break;
            }
        case REDIS_REPLY_ERROR: os << reply.getErrorMessage(); break;
        default:break;
        }
        return os;
    }
    std::ostream& operator << (ostream& os, const RedisCommandBase<char>& cmd)
    {
        for (int i = 0; i < cmd.size(); ++i)
            os << cmd[i] << " ";
        return os;
    }
};

int main(int argc, char** argv)
{
    string host;
    int    port;

    po::options_description desc("options");

    desc.add_options()
        ("help", "produce this help message")
        ("host", po::value<string>(&host)->default_value("localhost"), "host")
        ("port", po::value<int>(&port)->default_value(6379), "port")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << endl;
        return 0;
    }

    signal(SIGPIPE, SIG_IGN);
    ev_default_loop(0);

    // lifetime protector, held by disconnect handle or lambda
    struct protector_t
    {
        ~protector_t()
        {
            cout << "~protector_t()" <<endl;
        };
        std::function<void()> f;
        boost::shared_ptr<RedisConnectionAsync> myredis;
    };
    boost::shared_ptr<protector_t> protector(new protector_t);
    protector->myredis.reset(new RedisConnectionAsync(host, port));
    cout << "\n====================\n"
            "first show:\n"
            "auto req/rep after connection\n";
    {
        RedisConnectionAsync& myredis = *protector->myredis;
        std::function<void()>& f = protector->f;
        f = [&](){
            // request
            static int mycnt = 0;
            const int bound = 10;
            if (mycnt > bound * 2)
            {
                myredis.disconnect();
                return;
            }

            boost::shared_ptr<RedisCommandBase<char> > cmd_protector(new RedisCommandBase<char>);
            RedisCommandBase<char>& cmd = *cmd_protector;
            if (mycnt++ < bound)
                cmd << "set" <<  boost::lexical_cast<string>(mycnt)
                        << boost::lexical_cast<string>(mycnt);
            else
                cmd << "get" << boost::lexical_cast<string>(mycnt - bound);
            myredis.execAsyncCommand(cmd,
                                     // reply
                                     [&f, cmd_protector](RedisConnectionAsync& ac, Redis::Element* reply){
                                         RedisCommandBase<char>& cmd = *cmd_protector;
                                         cout << cmd << endl;
                                         try {
                                            if (reply) {
                                                reply->checkError();
                                            }
                                            else {
                                                throw RedisException(std::string("disconnected"));
                                            }
                                            cout << *reply << endl;
                                            // next req/rep
                                            f();
                                         }
                                         catch (const hiredispp::RedisException& ex) {
                                             cout<< ex.what() <<endl;
                                             ac.disconnect();
                                         }
                                     });
        };

        myredis.connect([&](boost::shared_ptr<RedisException>& ex) {
                            cout << "RR myredis connected" << endl;
                            f();
                        },
                        [&myredis, protector](boost::shared_ptr<RedisException>& ex) {
                            cout << "RR myredis disconnected" << endl;
                            (void)protector;
                        });
        protector.reset();
    }
    ev_loop(EV_DEFAULT, 0);

    protector.reset(new protector_t);
    protector->myredis.reset(new RedisConnectionAsync(host, port));
    cout << "\n====================\n"
            "second show:\n"
            "pipeline(non-req/rep-statefull):\n";
    {
        RedisConnectionAsync& myredis = *protector->myredis;
        std::function<void()>& f = protector->f;
        // pipeline, just send commands
        f = [&]() {
            const int limit = 20;
            for (int i = 0; i < 20; ++i)
            {
                const int bound = 10;
                boost::shared_ptr<RedisCommandBase<char> > cmd_protector(new RedisCommandBase<char>);
                RedisCommandBase<char>& cmd = *cmd_protector;
                if (i < bound)
                    cmd << "set" <<  boost::lexical_cast<string>(i)
                            << boost::lexical_cast<string>(20 + i);
                else
                    cmd << "get" << boost::lexical_cast<string>(i - bound);
                myredis.execAsyncCommand(cmd,
                                         [cmd_protector, i, limit](RedisConnectionAsync& ac, Redis::Element* reply){
                                             RedisCommandBase<char>& cmd = *cmd_protector;
                                             cout << cmd << endl;
                                             try {
                                                if (reply) {
                                                    reply->checkError();
                                                }
                                                else {
                                                    throw RedisException(std::string("disconnected"));
                                                }
                                                cout << *reply << endl;
                                             }
                                             catch (const hiredispp::RedisException& ex) {
                                                 cout<< ex.what() <<endl;
                                                 ac.disconnect();
                                             }
                                             if (i == limit - 1)
                                                ac.disconnect();
                                         });
            }
        };
        myredis.connect([&](boost::shared_ptr<RedisException>& ex) {
                            cout << "PL myredis connected" << endl;
                            f();
                        },
                        [protector](boost::shared_ptr<RedisException>& ex) {
                            cout << "PL myredis disconnected" << endl;
                        });

        protector.reset();
    }
    ev_loop(EV_DEFAULT, 0);

    protector.reset(new protector_t);
    protector->myredis.reset(new RedisConnectionAsync(host, port));
    cout << "\n====================\n"
            "third show:\n"
            "\n";
    {
        RedisConnectionAsync& myredis = *protector->myredis;
        std::function<void()>& f = protector->f;
        f = [&]() {
            RedisCommandBase<char> cmd;
            cmd << "subscribe 1 2 3 4";
            myredis.execAsyncCommand(cmd,
                                 [](RedisConnectionAsync& ac, Redis::Element* reply){
                                     cout << "origin 1 2 3 4" << endl;
                                     try {
                                        if (reply) {
                                            reply->checkError();
                                        }
                                        else {
                                            throw RedisException(std::string("disconnected"));
                                        }
                                        cout << *reply << endl;
                                     }
                                     catch (const hiredispp::RedisException& ex) {
                                         cout<< ex.what() <<endl;
                                         ac.disconnect();
                                     }
                                 });
            RedisCommandBase<char> cmd2;
            cmd2 << "subscribe 3 4";
            myredis.execAsyncCommand(cmd2,
                                 [](RedisConnectionAsync& ac, Redis::Element* reply){
                                     cout << "overload 3 4" << endl;;
                                     try {
                                        if (reply) {
                                            reply->checkError();
                                        }
                                        else {
                                            throw RedisException(std::string("disconnected"));
                                        }
                                        cout << *reply << endl;
                                     }
                                     catch (const hiredispp::RedisException& ex) {
                                         cout<< ex.what() <<endl;
                                         ac.disconnect();
                                     }
                                 });
        };
        myredis.connect([&](boost::shared_ptr<RedisException>& ex) {
                            cout << "PubSub myredis connected" << endl;
                            f();
                        },
                        [protector](boost::shared_ptr<RedisException>& ex) {
                            cout << "PubSub myredis disconnected" << endl;
                        });

        struct ev_timer_ctx
        {
            ev_timer timer;
            boost::shared_ptr<RedisConnectionAsync> myredis;
            boost::shared_ptr<Redis> pubredis;
            int repeat;
        };
        int begin_after = 2;
        int repeat_every = 1;
        ev_timer_ctx timer_ctx;
        ev_timer_init(&timer_ctx.timer,
                      [](struct ev_loop *loop, ev_timer *timer, int revent) {
                           ev_timer_ctx* timer_ctx = (ev_timer_ctx*)timer;
                           RedisConnectionAsync& myredis = *timer_ctx->myredis;
                           // we should use another connection to publish
                           // otherwise, a subcribed connection would get fault.
                           Redis& pubredis = *timer_ctx->pubredis;
                           RedisCommandBase<char> cmd;
                           cmd << "publish 3 4";
                           Redis::Reply reply = pubredis.doCommand(cmd);
                           cout << cmd << endl;
                           cout << reply << endl;
                            if (++timer_ctx->repeat > 5)
                            {
                                ev_timer_stop(loop, timer);
                                myredis.disconnect();
                            }

                      }, begin_after, repeat_every);
        timer_ctx.repeat = 0;
        timer_ctx.myredis = protector->myredis;
        timer_ctx.pubredis.reset(new Redis(host, port));
        ev_timer_start(EV_DEFAULT, &timer_ctx.timer);
        ev_loop(EV_DEFAULT, 0);
    }

    return 0;
}
