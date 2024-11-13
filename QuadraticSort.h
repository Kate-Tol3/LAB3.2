//
// Created by Kate on 11.11.2024.
//

#ifndef QUADRATICSORT_H
#define QUADRATICSORT_H



class QuadraticSort {
    //FROM GPT

#include <vector>
#include <iostream>
#include <algorithm>

    void enhancedSelectionSort(std::vector<int>& data) {
        int left = 0;                    // Начало неотсортированной части
        int right = data.size() - 1;      // Конец неотсортированной части

        while (left < right) {
            int minIndex = left;
            int maxIndex = right;

            // Находим минимальный и максимальный элементы в текущем диапазоне
            for (int i = left; i <= right; i++) {
                if (data[i] < data[minIndex]) {
                    minIndex = i;
                }
                if (data[i] > data[maxIndex]) {
                    maxIndex = i;
                }
            }

            // Меняем местами минимальный элемент с элементом в начале текущего диапазона
            std::swap(data[left], data[minIndex]);

            // Если максимальный элемент был на позиции `left`, он теперь перемещен
            // на позицию `minIndex`, поэтому обновляем его индекс
            if (maxIndex == left) {
                maxIndex = minIndex;
            }

            // Меняем местами максимальный элемент с элементом в конце текущего диапазона
            std::swap(data[right], data[maxIndex]);

            // Сдвигаем границы, так как крайние элементы уже на своих местах
            left++;
            right--;
        }
    }

};



#endif //QUADRATICSORT_H
