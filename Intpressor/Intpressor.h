#ifndef INTPRESSOR_H
#define INTPRESSOR_H

#include <vector>
#include <numeric>

namespace Intpressor
{
    std::vector<unsigned char> compress(const std::vector<int> &values, const std::vector<int> &sizes);
    std::vector<int> extract(const std::vector<unsigned char> &bytes, const std::vector<int> &sizes);
}

#endif // INTPRESSOR_H
