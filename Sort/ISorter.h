//
// Created by Kate on 14.11.2024.
//

#ifndef ISORTER_H
#define ISORTER_H
#include "Sequence/MutableArraySequence.h"
#include "Pointers/SharedPtr.h"


template <typename T, typename Comparator>
class ISorter {
public:

    //нужен дефолтный конструктор
    virtual ~ISorter() = default;
    virtual void sort(SharedPtr<Sequence<T>> sequence, Comparator comp) = 0;
};

#endif //ISORTER_H