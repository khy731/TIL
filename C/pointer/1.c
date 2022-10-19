// 1. 1차원 배열을 받아서 배열 요소들의 합을 계산하는 함수 int get_array_sum(int *A, int size)을 구현하고
// int data[10] = {1,2,3,4,5,6,7,8,9};을 가지고 테스트하라.

#include <stdio.h>

int get_array_sum(int *A, int size) {
    int array_sum = 0;

    for(int i=0; i<size; i++) {
        array_sum += A[i];
    }

    return array_sum;
}

int main(void) {
    int arr[5];

    printf("숫자 입력 : ");
    for(int i=0; i<5; i++) {
        scanf("%d", &arr[i]);
    }

    printf("배열 요소들의 합은 %d입니다.\n", get_array_sum(arr, 5));

    return 0;
}