#include "Intpressor.h"

namespace Intpressor
{
    std::vector<unsigned char> compress(const std::vector<int> &values, const std::vector<int> &sizes)
    {
        int totalSize = std::accumulate(std::begin(sizes), std::end(sizes), 0);
        int bitIndex = 0;
        std::vector<unsigned char> bytes;
        std::vector<bool> bits(totalSize, 0);
        for (int valueIndex = 0; valueIndex < values.size(); valueIndex++)
        {
            int size = sizes[valueIndex];
            int value = values[valueIndex];
            for (int i = 0; i < size; i++)
            {
                bits[bitIndex + i] = ((value & (1 << (size - i - 1))) != 0);
            }
            bitIndex += size;
        }
        size_t remainder = bits.size() % 8;
        if (remainder != 0)
        {
            for (size_t i = 0; i < 8 - remainder; ++i)
            {
                bits.push_back(false);
            }
        }
        for (size_t i = 0; i < bits.size(); i += 8)
        {
            unsigned char byte = 0;
            for (size_t j = 0; j < 8; ++j)
            {
                byte |= (bits[i + j] << (7 - j));
            }
            bytes.push_back(byte);
        }
        return bytes;
    }

    std::vector<int> extract(const std::vector<unsigned char> &bytes, const std::vector<int> &sizes)
    {
        std::vector<int> values;
        std::vector<bool> bits;
        for (unsigned char byte : bytes)
        {
            for (int i = 7; i >= 0; i--)
            {
                bits.push_back((byte & (1 << i)) != 0);
            }
        }
        int bitIndex = 0;
        for (int size : sizes)
        {
            int value = 0;
            for (int i = bitIndex; i < bitIndex + size; i++)
            {
                value = (value << 1) | static_cast<int>(bits[i]);
            }
            values.push_back(value);
            bitIndex += size;
        }
        return values;
    }

}
