#include <iostream>
#include "Intpressor/Intpressor.h"

int main()
{
    std::cout << "Intpressor Demo File @ Simon Pucheu" << std::endl << std::endl;

    std::vector<int> values = {1, 0, 9, 150, 1, 200, 300, 250, 500};
    std::vector<int> sizes = {1, 1, 4, 8, 1, 9, 9, 9, 9};

    std::vector<unsigned char> compressed = Intpressor::compress(values, sizes);

    std::cout << "Bytes (BIN):" << std::endl;
    for (const auto &byte : compressed)
    {
        for (int i = 7; i >= 0; i--)
        {
            std::cout << ((byte >> i) & 1);
        }
        std::cout << " ";
    }
    std::cout << std::endl
              << std::endl;

    std::cout << "Size of Compressed Array: " << compressed.size() << std::endl
              << std::endl;

    std::cout << "//////////////////////////////////////////////////////////////" << std::endl
              << std::endl;

    std::vector<int> extracted = Intpressor::extract(compressed, sizes);

    std::cout << "Extracted (INT): " << std::endl;
    for (const auto &value : extracted)
    {
        std::cout << static_cast<int>(value) << " ";
    }
    std::cout << std::endl
              << std::endl;

    std::cout << "Size of Extracted Array: " << extracted.size() << std::endl
              << std::endl;

    return 0;
}
