#include <stdio.h>

int swap(int *a, int *b) {
    int temp = 0;
    temp = *a;
    *a = *b;
    *b = temp;

    return 0;
}

int main(void) {
    int num_1 = 10;
    int num_2 = 20;

    printf("swap 전 : %d %d", num_1, num_2);

    swap(&num_1, &num_2);

    printf("swap 후 : %d %d", num_1, num_2);

    return 0;
}