## zhelper/xml/zamples
**libexpat**, **tinyxml2**, **pugixml** and **boost::ptree** samples are given.

each sample has four examples for common usage.

they are
- **load()** :load xml from memory or file
- **scan()** :write iteration procedures to iterate things from top.
- **visit()** :walk though the loaded doc object, and use visitor visit things.
- **save()** :restore xml to memory or file

there are two mode for traverse the xml doc elements.

* 1. scan mode,

you should write procedure to iterate from the root node of doc, and iterate the sub nodes or not.

* 2. visit mode

it is similar to visitor-pattern, the doc walk though every node, and call your visitor to allow you visit the node.

libexpat is not more than a parser, it does not support load and save. the advantage is that, it can parse partial of xml, and you can only visit node when it is parsing xml. the disadvantage is that, you can not locate a node by name.

## benchmark 
pugixml gives a benchmark at https://pugixml.org/benchmark.html.
