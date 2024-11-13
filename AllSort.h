//
// Created by Kate on 13.11.2024.
//

#ifndef ALLSORT_H
#define ALLSORT_H



class AllSort {

    #include <vector>
#include <algorithm>

// Шаблонный класс Sorter с реализацией различных методов сортировки
template <typename T>
class Sorter {
public:
    // Метод пузырька
    static void BubbleSort(std::vector<T>& sequence) {
        int n = sequence.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (sequence[j] > sequence[j + 1]) {
                    std::swap(sequence[j], sequence[j + 1]);
                }
            }
        }
    }

    // Шейкерная сортировка
    static void ShakerSort(std::vector<T>& sequence) {
        int left = 0, right = sequence.size() - 1;
        while (left <= right) {
            for (int i = left; i < right; ++i) {
                if (sequence[i] > sequence[i + 1]) {
                    std::swap(sequence[i], sequence[i + 1]);
                }
            }
            --right;
            for (int i = right; i > left; --i) {
                if (sequence[i] < sequence[i - 1]) {
                    std::swap(sequence[i], sequence[i - 1]);
                }
            }
            ++left;
        }
    }

    // Метод простых вставок
    static void InsertionSort(std::vector<T>& sequence) {
        int n = sequence.size();
        for (int i = 1; i < n; ++i) {
            T key = sequence[i];
            int j = i - 1;
            while (j >= 0 && sequence[j] > key) {
                sequence[j + 1] = sequence[j];
                --j;
            }
            sequence[j + 1] = key;
        }
    }

    // Сортировка с помощью простого выбора
    static void SelectionSort(std::vector<T>& sequence) {
        int n = sequence.size();
        for (int i = 0; i < n - 1; ++i) {
            int minIdx = i;
            for (int j = i + 1; j < n; ++j) {
                if (sequence[j] < sequence[minIdx]) {
                    minIdx = j;
                }
            }
            std::swap(sequence[i], sequence[minIdx]);
        }
    }

    // Сортировка подсчетом (для целых чисел)
    static void CountingSort(std::vector<int>& sequence) {
        int max = *std::max_element(sequence.begin(), sequence.end());
        int min = *std::min_element(sequence.begin(), sequence.end());
        int range = max - min + 1;

        std::vector<int> count(range), output(sequence.size());
        for (int i : sequence) count[i - min]++;
        for (int i = 1; i < range; ++i) count[i] += count[i - 1];
        for (int i = sequence.size() - 1; i >= 0; --i) {
            output[count[sequence[i] - min] - 1] = sequence[i];
            count[sequence[i] - min]--;
        }
        sequence = output;
    }

    // Метод двоичных вставок
    static void BinaryInsertionSort(std::vector<T>& sequence) {
        int n = sequence.size();
        for (int i = 1; i < n; ++i) {
            T key = sequence[i];
            int left = 0, right = i;
            while (left < right) {
                int mid = (left + right) / 2;
                if (key >= sequence[mid]) left = mid + 1;
                else right = mid;
            }
            for (int j = i; j > left; --j) sequence[j] = sequence[j - 1];
            sequence[left] = key;
        }
    }

    // Пирамидальная сортировка
    static void HeapSort(std::vector<T>& sequence) {
        auto heapify = [](std::vector<T>& arr, int n, int i) {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if (left < n && arr[left] > arr[largest]) largest = left;
            if (right < n && arr[right] > arr[largest]) largest = right;
            if (largest != i) {
                std::swap(arr[i], arr[largest]);
                heapify(arr, n, largest);
            }
        };

        int n = sequence.size();
        for (int i = n / 2 - 1; i >= 0; --i) heapify(sequence, n, i);
        for (int i = n - 1; i >= 0; --i) {
            std::swap(sequence[0], sequence[i]);
            heapify(sequence, i, 0);
        }
    }

    // Быстрая сортировка
    static void QuickSort(std::vector<T>& sequence, int left = 0, int right = -1) {
        if (right == -1) right = sequence.size() - 1;
        if (left < right) {
            int pivot = partition(sequence, left, right);
            QuickSort(sequence, left, pivot - 1);
            QuickSort(sequence, pivot + 1, right);
        }
    }

    // Вспомогательная функция для быстрой сортировки
    static int partition(std::vector<T>& sequence, int left, int right) {
        T pivot = sequence[right];
        int i = left - 1;
        for (int j = left; j < right; ++j) {
            if (sequence[j] < pivot) {
                ++i;
                std::swap(sequence[i], sequence[j]);
            }
        }
        std::swap(sequence[i + 1], sequence[right]);
        return i + 1;
    }

    // Сортировка слиянием
    static void MergeSort(std::vector<T>& sequence) {
        if (sequence.size() > 1) {
            std::vector<T> left(sequence.begin(), sequence.begin() + sequence.size() / 2);
            std::vector<T> right(sequence.begin() + sequence.size() / 2, sequence.end());
            MergeSort(left);
            MergeSort(right);
            merge(sequence, left, right);
        }
    }

    // Вспомогательная функция для сортировки слиянием
    static void merge(std::vector<T>& sequence, std::vector<T>& left, std::vector<T>& right) {
        auto it = sequence.begin();
        auto leftIt = left.begin();
        auto rightIt = right.begin();
        while (leftIt != left.end() && rightIt != right.end()) {
            if (*leftIt < *rightIt) *it++ = *leftIt++;
            else *it++ = *rightIt++;
        }
        while (leftIt != left.end()) *it++ = *leftIt++;
        while (rightIt != right.end()) *it++ = *rightIt++;
    }

    // Сортировка Шелла
    static void ShellSort(std::vector<T>& sequence) {
        int n = sequence.size();
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; ++i) {
                T temp = sequence[i];
                int j;
                for (j = i; j >= gap && sequence[j - gap] > temp; j -= gap) {
                    sequence[j] = sequence[j - gap];
                }
                sequence[j] = temp;
            }
        }
    }
};


};



#endif //ALLSORT_H


template <typename T>
class EnhancedSelectionSort {
public:
    static void Sort(std::vector<T>& sequence) {
        int left = 0;
        int right = sequence.size() - 1;

        while (left < right) {
            int minIdx = left;
            int maxIdx = right;

            for (int i = left; i <= right; ++i) {
                if (sequence[i] < sequence[minIdx]) {
                    minIdx = i;
                }
                if (sequence[i] > sequence[maxIdx]) {
                    maxIdx = i;
                }
            }

            std::swap(sequence[left], sequence[minIdx]);
            if (maxIdx == left) {
                maxIdx = minIdx;
            }
            std::swap(sequence[right], sequence[maxIdx]);

            ++left;
            --right;
        }
    }
};


#include <memory>

template <typename T>
class TreeNode {
public:
    T value;
    std::unique_ptr<TreeNode<T>> left;
    std::unique_ptr<TreeNode<T>> right;

    explicit TreeNode(T val) : value(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class TreeSelectionSort {
public:
    static void Sort(std::vector<T>& sequence) {
        std::unique_ptr<TreeNode<T>> root = nullptr;
        for (const auto& val : sequence) {
            insert(root, val);
        }
        sequence.clear();
        inOrderTraversal(root, sequence);
    }

private:
    static void insert(std::unique_ptr<TreeNode<T>>& node, T value) {
        if (!node) {
            node = std::make_unique<TreeNode<T>>(value);
        } else if (value < node->value) {
            insert(node->left, value);
        } else {
            insert(node->right, value);
        }
    }

    static void inOrderTraversal(const std::unique_ptr<TreeNode<T>>& node, std::vector<T>& sequence) {
        if (!node) return;
        inOrderTraversal(node->left, sequence);
        sequence.push_back(node->value);
        inOrderTraversal(node->right, sequence);
    }
};


template <typename T>
class ShellSortWithGaps {
public:
    static void Sort(std::vector<T>& sequence) {
        std::vector<int> gaps = {701, 301, 132, 57, 23, 10, 4, 1}; // Последовательность Седжвика
        int n = sequence.size();
        for (int gap : gaps) {
            for (int i = gap; i < n; ++i) {
                T temp = sequence[i];
                int j;
                for (j = i; j >= gap && sequence[j - gap] > temp; j -= gap) {
                    sequence[j] = sequence[j - gap];
                }
                sequence[j] = temp;
            }
        }
    }
};


template <typename T>
class BitonicSort {
public:
    static void Sort(std::vector<T>& sequence) {
        bitonicSort(sequence, 0, sequence.size(), true);
    }

private:
    static void bitonicSort(std::vector<T>& sequence, int low, int count, bool ascending) {
        if (count > 1) {
            int k = count / 2;
            bitonicSort(sequence, low, k, true);
            bitonicSort(sequence, low + k, k, false);
            bitonicMerge(sequence, low, count, ascending);
        }
    }

    static void bitonicMerge(std::vector<T>& sequence, int low, int count, bool ascending) {
        if (count > 1) {
            int k = count / 2;
            for (int i = low; i < low + k; ++i) {
                if (ascending == (sequence[i] > sequence[i + k])) {
                    std::swap(sequence[i], sequence[i + k]);
                }
            }
            bitonicMerge(sequence, low, k, ascending);
            bitonicMerge(sequence, low + k, k, ascending);
        }
    }
};


std::vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6};

// Квадратичная сортировка (усовершенствованная сортировка выбором)
EnhancedSelectionSort<int>::Sort(data);

// Сортировка с помощью выбора из дерева
TreeSelectionSort<int>::Sort(data);

// Сортировка Шелла (с выбором смещения)
ShellSortWithGaps<int>::Sort(data);

// Схема Бэтчера
BitonicSort<int>::Sort(data);


template <typename T>
class BatcherSort {
public:
    static void Sort(std::vector<T>& sequence) {
        OddEvenMergeSort(sequence, 0, sequence.size());
    }

private:
    static void OddEvenMergeSort(std::vector<T>& sequence, int low, int n) {
        if (n > 1) {
            int m = n / 2;
            OddEvenMergeSort(sequence, low, m);
            OddEvenMergeSort(sequence, low + m, m);
            OddEvenMerge(sequence, low, n, 1);
        }
    }

    static void OddEvenMerge(std::vector<T>& sequence, int low, int n, int r) {
        int m = r * 2;
        if (m < n) {
            OddEvenMerge(sequence, low, n, m);
            OddEvenMerge(sequence, low + r, n, m);
            for (int i = low + r; i + r < low + n; i += m) {
                if (sequence[i] > sequence[i + r]) {
                    std::swap(sequence[i], sequence[i + r]);
                }
            }
        } else {
            if (sequence[low] > sequence[low + r]) {
                std::swap(sequence[low], sequence[low + r]);
            }
        }
    }
};

