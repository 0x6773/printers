# printers
(c) Govind Sahai 2016-

Header only C++ printers.hpp for different C++ Containers/Iterators/Pointers

# How to use?

Download [printers.hpp](https://github.com/mnciitbhu/printers/blob/master/printers.hpp) file

    $ wget https://github.com/mnciitbhu/printers/raw/master/printers.hpp

    // Your C++ File
    #include "printers.hpp"
    using namespace printers;
    
Now use the printers : 
```
 std::vector<int> ar = { 1,2,3,4,5,6,7 };
 std::cout << ar << std::endl;
 
 std::map<int, std::string> mp = {{1, "Govind"}, {2, "Sahai"}, {3, "mnciitbhu"}};
 std::cout << mp << std::endl;
```
will output : 
```
vec7[1, 2, 3, 4, 5, 6, 7] 
map3[pr2{1, "Govind"}, pr2{2, "Sahai"}, pr2{3, "mnciitbhu"}] 
```

See [pc.cpp](https://github.com/mafiya69/printers/blob/master/pc.cpp) for more examples.

# Contributions 
Are always welcome.
  
