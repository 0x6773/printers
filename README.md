# printers
(c) Govind Sahai 2016

**Now its easier to use printers**
# How to install?

    $ git clone https://github.com/mafiya69/printers --depth 1
    $ cd printers
    $ cmake .
    $ sudo make install
    
# How to use?

    // Your C++ File
    #include <printers.hpp>
    using namespace printers;
    
Now use the printers : 
```
 std::vector<int> ar = { 1,2,3,4,5,6,7 };
 std::cout << ar << std::endl;
 
 std::map<int, std::string> mp = {{1, "Govind"}, {2, "Sahai"}, {3, "mafiya69"}};
 std::cout << mp << std::endl;
```
will output : 
```
vec7[1, 2, 3, 4, 5, 6, 7] 
map3[pr2{1, "Govind"}, pr2{2, "Sahai"}, pr2{3, "mafiya69"}] 
```

See [pc.cpp](https://github.com/mafiya69/printers/blob/master/pc.cpp) for more examples.

# Contributions 
Are always welcome.
  
