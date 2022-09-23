### load CMakeLists.txt project
* use a platform console run the kdevelop
* should set `-DCMAKE_MAKE_PROGRAM=`
* the c++language analisys backend would not use your CMAKE options
  * you should set this options via project configuration ui (Language Support):
    * c++11 or c++14 or ...
    * include path
    * link path  
