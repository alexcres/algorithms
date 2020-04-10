#ifndef ALGORITHMS_UTIL_H
#define ALGORITHMS_UTIL_H

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
}// namespace Util
#endif //ALGORITHMS_UTIL_HXX
