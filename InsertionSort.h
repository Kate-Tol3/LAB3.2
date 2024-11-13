//
// Created by Kate on 11.11.2024.
//

#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H
#include <bits/ranges_base.h>
#include <bits/range_access.h>


class InsertionSort {


    void insertionSort(std::vector<int>& data) {
        for (int i = 1; i < data.size(); i++) {
            int key = data[i];
            int j = i - 1;

            // Перемещаем элементы data[0..i-1], которые больше ключа, на одну позицию вперед
            while (j >= 0 && data[j] > key) {
                data[j + 1] = data[j];
                j--;
            }

            // Вставляем ключ на найденную позицию
            data[j + 1] = key;
        }
    }
};



#endif //INSERTIONSORT_H
