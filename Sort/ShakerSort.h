//
// Created by Kate on 14.11.2024.
//

#ifndef SHAKERSORT_H
#define SHAKERSORT_H

#include "Isorter.h"
#include "../Pointers/SharedPtr.h"
#include "../Sequence/Sequence.h"

template <typename T, typename Comparator>
class ShakerSort : public ISorter<T, Comparator> {
public:
    void sort(SharedPtr<Sequence<T>> sequence, Comparator comp) {
        int left = 0, right = sequence->getLength() - 1;
        while (left <= right) {
            for (int i = left; i < right; ++i) {
                if (comp((*sequence)[i + 1], (*sequence)[i])) { //sequence[i] > sequence[i + 1]
                    std::swap((*sequence)[i], (*sequence)[i + 1]);
                }
            }
            --right;
            for (int i = right; i > left; --i) {
                if (comp((*sequence)[i], (*sequence)[i - 1])) {// if (sequence[i] < sequence[i - 1]) {
                    std::swap((*sequence)[i], (*sequence)[i - 1]);
                }
            }
            ++left;
        }
    }
};



#endif //SHAKERSORT_H
