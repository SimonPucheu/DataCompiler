# Intpressor
This is a C++ code that compress multiple variables (intergers or booleans) into one single array of bytes.
The resulting array of bytes is as small as possible. Given the values and the sizes (in number of bits), the program fills every bytes. In that way, 8 booleans can fit in 1 byte.

This library is perfect for communication that requires efficency.

The sizes and the values are given to the library via two vectors:

```cpp
std::vector<int> values = {1, 0, 1, 9, 150, 200, 300, 250, 500};
std::vector<int> sizes = {1, 1, 1, 4, 8, 9, 9, 9, 9};
```

They have to be matching (the first element of the values vector is 1, its corresponding is therefore located in the first element of the sizes vector.

You can find an example of use in the file [main.cpp](./main.cpp).

You can find an equivalent of this library compatible with Arduino (ino) in the following repository: [SimonPucheu/IntpressorArduino](https://github.com/SimonPucheu/IntpressorArduino).
