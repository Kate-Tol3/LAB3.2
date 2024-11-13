

#ifndef BUBBLESORT_H
#define BUBBLESORT_H
#include <bits/stdc++.h>

class BubbleSort {

    public:
    // An optimized version of Bubble Sort
    void sort(std::vector<int>& v){

        int n = v.size();
        for (int i = 0; i < n - 1; i++) {

            // Creating a flag to denote the case when array
            // is sorted and doesn't cause any swap
            bool flag = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (v[j] > v[j + 1]) {
                    std::swap(v[j], v[j + 1]);

                    // Setting flag true when swap happened
                    flag = true;
                }
            }

            // Checking if the flag is set or not
            if (!flag)
                break;
        }
    }

};



#endif //BUBBLESORT_H
