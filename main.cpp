#include <iostream>
#include <iomanip>
#include <bitset>
#include <vector>

unsigned char getBits(unsigned char byte, int startIndex, int endIndex)
{
    if (startIndex < 0 || startIndex > 7 || endIndex < 0 || endIndex > 7 || startIndex > endIndex)
    {
        return 0;
    }
    unsigned char mask = ((1 << (endIndex - startIndex + 1)) - 1) << startIndex;
    unsigned char result = (byte & mask) >> startIndex;
    return result;
}

std::vector<unsigned char> compress(const std::vector<int> &values, const std::vector<int> &sizes)
{
    std::vector<unsigned char> bytes;
    unsigned char currentByte = 0;
    int remainingBits = 8;
    for (size_t i = 0; i < values.size(); ++i)
    {
        int size = sizes[i];
        int value = values[i];
        if (size <= remainingBits)
        {
            currentByte |= (value & ((1 << size) - 1)) << (8 - remainingBits);
            remainingBits -= size;
        }
        else
        {
            bytes.push_back(currentByte);
            currentByte = (value & ((1 << remainingBits) - 1)) << (8 - remainingBits);
            remainingBits = 8 - (size - remainingBits);
        }
        if (remainingBits == 0)
        {
            bytes.push_back(currentByte);
            currentByte = 0;
            remainingBits = 8;
        }
    }
    if (remainingBits < 8)
    {
        bytes.push_back(currentByte);
    }
    return bytes;
}

std::vector<int> extract(const std::vector<unsigned char> &bytes, const std::vector<int> &sizes)
{
    std::vector<int> values;
    int byteIndex = 0;
    int bitIndex = 0;
    for (int i = 0; i < sizes.size(); i++)
    {
        int size = sizes[i];
        int endIndex = bitIndex + size - 1;
        if (endIndex >= 8)
        {
            bitIndex = 0;
            byteIndex++;
        }
        unsigned char byte = bytes[byteIndex];
        // values[i] = getBits(byte, bitIndex, endIndex);
        std::cout << i << ". OG: " << std::bitset<8>(byte) << ", STRT: " << bitIndex << ", END: " << bitIndex + size - 1 << " -> " << (int)getBits(byte, bitIndex, endIndex) << std::endl;
        bitIndex += size;
    }
    return values;
}

int main()
{
    // unsigned char byte = 0b11001101; // Example byte

    // int startIndex = 0;
    // int endIndex = 7;

    // unsigned char extractedBits = getBits(byte, startIndex, endIndex);

    // std::cout << "Original Byte: ";
    // for (int i = 7; i >= 0; --i)
    // {
    //     std::cout << ((byte >> i) & 1);
    // }
    // std::cout << std::endl;

    // std::cout << "Extracted Bits: " << std::bitset<8>(extractedBits) << std::endl;

    std::vector<int> values = {1, 0, 1, 9, 103, 129, 123, 167, -164};
    std::vector<int> sizes = {1, 1, 1, 4, 8, 9, 9, 9, 9};

    std::vector<unsigned char> compressed = compress(values, sizes);

    std::cout << "Bytes (BIN):" << std::endl;
    for (const auto &byte : compressed)
    {
        for (int i = 7; i >= 0; --i)
        {
            std::cout << ((byte >> i) & 1);
        }
        std::cout << " ";
    }
    std::cout << std::endl
              << std::endl;

    std::cout << "Bytes (DEC): " << std::endl;
    for (const auto &byte : compressed)
    {
        std::cout << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl
              << std::endl;

    std::cout << "Size of Compressed Array: " << compressed.size() << std::endl
              << std::endl;

    std::cout << "///" << std::endl
              << std::endl;

    std::vector<int> extracted = extract(compressed, sizes);

    std::cout << "Extracted (INT): " << std::endl;
    for (const auto &value : extracted)
    {
        std::cout << static_cast<int>(value) << " ";
    }
    std::cout << std::endl
              << std::endl;

    std::cout << "Size of Extracted Array: " << compressed.size() << std::endl;

    return 0;
}
