#pragma once

#include "../Pointers/SharedPtr.h"
#include "../Sequence/Sequence.h"
#include "../Sequence/MutableSequence.h"


template <typename T, typename Comparator>
class ISorter {
public:

    //нужен дефолтный конструктор
    virtual ~ISorter() = default;
    virtual void sort(SharedPtr<Sequence<T>> sequence, Comparator comp) = 0;
};

