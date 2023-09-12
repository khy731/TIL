// 2. 포인터를 이용하여서 크기가 5인 1차원 정수 배열에 저장된 값을 역순으로 출력해보자.

#include <stdio.h>
#define SIZE = 5;

int sort_num(int *A) {
    for(int i = 5; i>-1; i--) {
        printf("%d", A[i]);
    }
}

int main(void) {
    int arr[5];

    printf("숫자 입력: ");
    for(int i = 0; i<5; i++) {
        scanf("%d", arr[i]);
    }

    printf("역순 : ");
    sort_num(arr);

    return 0;
}