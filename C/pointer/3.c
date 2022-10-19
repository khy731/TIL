// 3. 2차 방정식의 근을 계산하는 함수를 작성하고 이 함수를 호출하여서 2차 방정식의 근을 출력하는 프로그램을 작성해보자.
// 매개 변수로 포인터를 사용하면 함수가 2개 이상의 값을 반환할 수 있다.다음과 같이 두개의 근을 모두 포인터를 이용하여서 반환하도록 한다.

/* sqrt() -> 제곱근
pow() -> 제곱 */

#include <stdio.h>

int cal(int a, int b, double *value_pos, double *value_neg) {
    *value_pos = /*근의공식*/ ;
    *value_neg = /*근의공식*/;
}

int main(void) {
    int a = 1, b = 2;
    double value_pos = 0, value_neg = 0;

    cal(a, b, &value_pos, &value_neg);

    printf("근은 %lf와 %lf", value_pos, value_neg);
    
    return 0;
}