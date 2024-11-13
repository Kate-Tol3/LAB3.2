//
// Created by Kate on 11.11.2024.
//

#ifndef COUNTINGSORT_H
#define COUNTINGSORT_H



class CountingSort {
#include <vector>
#include <iostream>
#include <algorithm>

    //ИЗ ГПТ
    void countingSort(std::vector<int>& data) {
        if (data.empty()) return;

        // Находим минимальный и максимальный элементы для определения диапазона значений
        int minElement = *std::min_element(data.begin(), data.end());
        int maxElement = *std::max_element(data.begin(), data.end());

        int range = maxElement - minElement + 1;
        std::vector<int> count(range, 0); // Массив для подсчета вхождений
        std::vector<int> output(data.size()); // Массив для отсортированных значений

        // Подсчитываем количество каждого элемента
        for (int num : data) {
            count[num - minElement]++;
        }

        // Модифицируем массив count, чтобы каждый элемент хранил кумулятивную сумму
        for (int i = 1; i < range; i++) {
            count[i] += count[i - 1];
        }

        // Заполняем выходной массив, размещая элементы в правильных позициях
        for (int i = data.size() - 1; i >= 0; i--) {
            output[count[data[i] - minElement] - 1] = data[i];
            count[data[i] - minElement]--;
        }

        // Копируем отсортированные элементы обратно в исходный массив
        data = output;
    }


    //ИЗ ИНТЕРНЕТА

    vector<int> countSort(vector<int>& inputArray)
{

    int N = inputArray.size();

    // Finding the maximum element of array inputArray[].
    int M = 0;

    for (int i = 0; i < N; i++)
        M = max(M, inputArray[i]);

    // Initializing countArray[] with 0
    vector<int> countArray(M + 1, 0);

    // Mapping each element of inputArray[] as an index
    // of countArray[] array

    for (int i = 0; i < N; i++)
        countArray[inputArray[i]]++;

    // Calculating prefix sum at every index
    // of array countArray[]
    for (int i = 1; i <= M; i++)
        countArray[i] += countArray[i - 1];

    // Creating outputArray[] from countArray[] array
    vector<int> outputArray(N);

    for (int i = N - 1; i >= 0; i--)

    {
        outputArray[countArray[inputArray[i]] - 1]
            = inputArray[i];

        countArray[inputArray[i]]--;
    }

    return outputArray;
}


};



#endif //COUNTINGSORT_H
