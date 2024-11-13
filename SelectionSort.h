//
// Created by Kate on 11.11.2024.
//

#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H
#include <vector>
#include <iostream>


class SelectionSort {


    void selectionSort(std::vector<int>& data) {
        int n = data.size();

        for (int i = 0; i < n - 1; i++) {
            // Ищем индекс минимального элемента в оставшейся части массива
            int minIndex = i;

            for (int j = i + 1; j < n; j++) {
                if (data[j] < data[minIndex]) {
                    minIndex = j;
                }
            }

            // Меняем местами текущий элемент и найденный минимальный элемент
            std::swap(data[i], data[minIndex]);
        }
    }

};



#endif //SELECTIONSORT_H
