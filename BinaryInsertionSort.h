//
// Created by Kate on 11.11.2024.
//

#ifndef BINARYINSERTIONSORT_H
#define BINARYINSERTIONSORT_H



class BinaryInsertionSort {
    // Функция для бинарного поиска правильной позиции вставки
    int binarySearch(const std::vector<int>& data, int item, int low, int high) {
        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Определяем, в какую часть массива продолжать поиск
            if (data[mid] == item) {
                return mid + 1;
            }
            else if (data[mid] < item) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        return low;  // Возвращаем позицию для вставки
    }

    // Функция сортировки методом двоичных вставок
    void binaryInsertionSort(std::vector<int>& data) {
        for (int i = 1; i < data.size(); i++) {
            int key = data[i];

            // Находим правильную позицию для вставки ключа
            int pos = binarySearch(data, key, 0, i - 1);

            // Сдвигаем элементы, чтобы освободить место для вставки ключа
            for (int j = i; j > pos; j--) {
                data[j] = data[j - 1];
            }

            // Вставляем ключ на найденную позицию
            data[pos] = key;
        }
    }
};



#endif //BINARYINSERTIONSORT_H
