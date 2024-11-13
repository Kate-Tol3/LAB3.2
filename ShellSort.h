//
// Created by Kate on 13.11.2024.
//

#ifndef SHELLSORT_H
#define SHELLSORT_H



class ShellSort {

};



#endif //SHELLSORT_H


void ShellSort(int n, int mass[])
{
    int i, j, step;
    int tmp;
    for (step = n / 2; step > 0; step /= 2)
        for (i = step; i < n; i++)
        {
            tmp = mass[i];
            for (j = i; j >= step; j -= step)
            {
                if (tmp < mass[j - step])
                    mass[j] = mass[j - step];
                else
                    break;
            }
            mass[j] = tmp;
        }
}

из другого места

#include  <iostream>
using namespace std;

// реализация сортировки Шелла
int shellSort(int arr[], int N)
{
    for (int gap = N/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < N; i += 1)
        {
            //сортировка подсписков, созданных с помощью gap
            int temp = arr[i];

            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            arr[j] = temp;
        }
    }
    return 0;
}

int main()
{
    int arr[] = {45,23,53,43,18,24,8,95,101}, i;
    //Вычислить размер массива
    int N = sizeof(arr)/sizeof(arr[0]);

    cout << "Array to be sorted: \n";
    for (int i=0; i<N; i++)
        cout << arr[i] << " ";

    shellSort(arr, N);

    cout << "\nArray after shell sort: \n";
    for (int i=0; i<N; i++)
        cout << arr[i] << " ";

    return 0;
}