#ifndef NPJH_UTIL_ARRAY_LENGTH_H_
#define NPJH_UTIL_ARRAY_LENGTH_H_

namespace npjh {

template<typename T, int N>
constexpr int ArrayLength(const T(&ary)[N]) // 检查数组长度
{
    return N;
}

}

#endif