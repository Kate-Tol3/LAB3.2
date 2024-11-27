#ifndef SHELLSORT_H
#define SHELLSORT_H

#include "ISorter.h"
#include "../Pointers/SharedPtr.h"
#include "../Sequence/Sequence.h"

template <typename T, typename Comparator>
class ShellSort : public ISorter<T, Comparator> {
public:
    void sort(SharedPtr<Sequence<T>> sequence, Comparator comp) override{
        int n = sequence->getLength();
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; ++i) {
                T temp = (*sequence)[i];
                int j;
                for (j = i; j >= gap && comp(temp, (*sequence)[j - gap]); j -= gap) {
                    (*sequence)[j] = (*sequence)[j - gap];
                    // sequence->Set(j, sequence->Get(j - gap));
                }
                (*sequence)[j] = temp;
                //sequence->Set(j, temp);
            }
        }
    }
};



#endif //SHELLSORT_H
