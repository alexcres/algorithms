#pragma once

#include <iostream>

namespace Util {
    template<typename Data>
    void resize(Data *&array, int size);

    template<typename Data>
    void resize(Data *&array, int size) {
        int *temp{new Data[size]};
        for (int i = 0; i != size; ++i) {
            temp[i] = array[i];
        }
        delete[] array;
        array = temp;
    }

    template<typename V>
    void p(V v) {
        std::cout << v << " ";
    }

    template<typename Head, typename... Tail>
    void rp(Head h, Tail... t) {
        p(h);
        if constexpr (sizeof...(Tail) > 0) {
            rp(t...);
        } else {
            return;
        }
    }

}// namespace Util
