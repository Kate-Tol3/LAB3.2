//
// Created by Kate on 13.11.2024.
//

#ifndef MERGESORT_H
#define MERGESORT_H



class MergeSort {

};



#endif //MERGESORT_H


public static int[] mergeSort(int... src) {
    if (src.length <= 1) {
        return src;
    }
    int[] left = Arrays.copyOfRange(src, 0, src.length / 2);
    int[] right = Arrays.copyOfRange(src, left.length, src.length);
    return merge(mergeSort(left), mergeSort(right));
}

private static int[] merge(int[] left, int[] right) {
    int index = 0, indexL = 0, indexR = 0;
    int[] result = new int[left.length + right.length];
    while (indexL < left.length && indexR < right.length) {
        result[index++] = left[indexL] < right[indexR] ? left[indexL++] : right[indexR++];
    }
    while (index < result.length) {
        result[index++] = indexL != left.length ? left[indexL++] : right[indexR++];
    }
    return result;
}