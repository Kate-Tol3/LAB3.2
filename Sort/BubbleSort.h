

#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "ISorter.h"

template <typename T, typename Comparator>
class BubbleSort: public ISorter<T, Comparator> {
    //private
    //std::function<T> comporator
public:

    //конструктор класса, можешь юзать дефолтный,тогда не нужен в прайват компоратор так как ты его передаешь
    //можно не юзать умные указатели а так топ
    void sort(SharedPtr<Sequence<T>> sequence, Comparator comp) override {
        int n = sequence->getLength();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (comp(sequence[j], sequence[j + 1])) {
                    std::swap(sequence[j], sequence[j + 1]);
                }
            }
        }
    }
};

#endif //BUBBLESORT_H
