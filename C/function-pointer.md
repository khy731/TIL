# 함수를 가리키는 포인터 변수

기계어 명령문으로 이루어진 프로그램이 실행되어 프로그램 형태로 메모리에 저장되면, 내부의 명령문들은 코드 세그먼트에 저장됩니다. 명령문들도 메모리에 저장되어 있다는 것은, 이들의 메모리 주소만 알고 있다면 포인터 문법을 사용하여 특정 명령문이 저장된 메모리의 주소로 바로 이동해서 명령문을 실행시킬 수 있다는 것을 의미합니다. 그러나 마음대로 메모리 위치를 이동하면서 명령문을 실행하면 C언어의 스택 프레임이 망가지게 됩니다. 이 때 명령문들을 묶어놓은 함수 단위로 포인터 변수를 사용해준다면 가장 효율적인 활용이 되지 않을까요?

# 함수 포인터 Function Pointer

특정 함수를 구성하는 여러개의 명령 中 시작 명령의 위치를 가리키는 포인터. 함수 포인터를 사용하여 해당 함수를 호출하여 실행할 수 있다.

## 함수의 원형에 대하여

함수의 형식(원형)이 같으려면?

- 같은 수의 매개변수
- 같은 자료형
- 같은 형태의 반환 값

## 함수 포인터 선언하기

함수 원형 Function Prototype을 사용하여 포인터를 선언한다.

```c
int (*p)(int, int);     // Sum 함수를 가리킬 수 있는 
p=&Sum;                 // Sum 함수의 주소를 p에 저장
```

## 함수 포인터 호출(사용)하기

```c
int result= (*p)(2,3);
```

## 함수 포인터의 장점: 함수 그룹

형식이 같은 함수들끼리 모아서 그룹으로 묶어 사용할 수 있다.

예를 들어,

- 덧셈 함수 Sum(int a, int b)
- 뺄셈 함수 Sub(int a, int b)
- 곱셈 함수 Mul(int a, int b)
- 나눗셈 함수 Div(int a, int b)

위 함수 4개로 8과 2의 연산값을 얻으려면 함수 4개를 일일이 호출해야 한다. 그러나 이 함수들은 이름만 다를 뿐 원형은 일치하므로 함수 포인터를 사용하면 편리하다.

### 배열 형식의 포인터 선언하기

```c
int (*p[4])(int, int) = (&Sum, &sub, &Mul, &Div);   // 각 함수의 주소 값으로 포인터를 초기화
```

### 함수 포인터를 배열로 선언하기

```c
int (*p[4])(int, int) = {&Sum, &Sub, &Mul, &Div};
int result[4], i;
for(i=0; i<4; i++) result[i]=(*p[i])(8,2);

/* typedef로 단순화 */
typedef int (*OP_TYPE)(int, int);
OP_TYPE p[4] = {&Sum, &Sub, &Mul, &Div};
```

### 함수 포인터를 사용하여 사칙연산하기

```c
#include <stdio.h>

int Sum(int a, int b)
{
    return a+b;
}
int Sub(int a, int b)
{
    return a-b;
}
int Mul(int a, int b)
{
    return a*b;
}
int Div(int a, int b)
{
    return a/b;
}

void main()
{
    int (*p[4])(int, int) = {&Sum, &Sub, &Mul, &Div}, i;
    char on_table[4] = {'+', '-', '*', '/'};

    for (i=0; i<4; i++) printf("%d %c %d = %d\n", 8, on_table[i], 2, (*p[i])(8,2));
}
```

# 콜백 함수와 함수 포인터

함수 포인터의 유연성이 갖는 장점에 대해서 설명한다.

예를 들어 라이브러리 프로그래머의 경우, 특별한 지식이 필요한 작업코드를 함수화해서 판매하는 경우가 많다. 이 때 코드가 노출되면 안 되기 때문에 함수의 원형이 설명되어 있는 .h파일만을 사용자에게 제공하게 된다.

## 라이브러리 프로그래머(1)

```c
// Sum 함수의 원형
int Sum(int a, int b);

// sum.lib

// 두 값을 합산하는 함수
int Sum(int a, int b)
{
    return a+b;
}

// 사용자가 사용하는 형태
#include "sum.h"
#pragma comment(lib, "sum.lib")

void main()
{
    int result = Sum(2,3);
}
```

그런데 만약, Sum의 사용자가 추가 요청을 한 경우 라이브러리 프로그래머는 어떻게 해야 할까?

<aside>
❓ Sum 함수에 전달되는 두 숫자 값이 음수인 경우 양수로 변환 후 연산 실행하게 해 주세요!

</aside>

<aside>
❗ 새로운 함수를 추가하여, 다시 라이브러리 파일로 만들어서, 배포해야 겠군...

</aside>

## 라이브러리 프로그래머(2)

```c
// sum.h

// Sum 함수의 원형
int Sum(int a, int b);
// SumABS 함수의 원형
int SUmABS(int a, int b);

// sum.lib

// 두 값을 합산하는 함수
int Sum(int a, int b)
{
    return a+b;
}

// 두 절댓값을 환산하는 함수
int SumABS(int a, int b)
{
    if (a<0) a * -1;
    if (b<0) b * -1;

    return a+b;
}

// 라이브러리 사용자가 사용하는 형태

#include "sum.h"
#pragma comment(lib, "sum.lib")

void main()
{
    int result1, result2;

    result1 = Sum(-2,3);
    result2 = SumABS(-2,3);
}
```

느꼈겠듯이, 이 방식은 문제점이 있다.

- 이후 추가적인 요청이 들어왔을 때 모든 요청마다 코드를 수정해야 한다
- 이는 단순히 함수가 늘어나게 되는 문제를 넘어, 라이브러리가 사용자의 요구에 종속되는 결과를 가져온다.
- 또한 라이브러리 코드의 본질(원래 목적. 이 예제에서는 두 숫자간의 덧셈 계산.)이 흐려지게 된다

즉 라이브러리의 함수는,

<aside>
👌 라이브러리 함수는 본래의 기능/본질 유지하면서 + 사용자가 원하는 경우 스스로 함수의 기능을 일부 수정하게 제공하는 것이 좋다

</aside>

이때 사용하는 것이 바로 함수 포인터이다.

함수를 계속해서 추가하는 것이 아닌, 함수 포인터를 사용해서 함수를 구성하여 이후 사용자들이 스스로 원하는대로 부가적인 기능을 만들어 사용할 수 있게 한다.

## 라이브러리 프로그래머(3)

```c
// Sum.lib

void MyAbsolute(int *p)
{
    if ((*p)<0)) *p = (*p)*(-1);    // 절댓값으로 만들어주는 코드
}

int SumABS(int a, int b)
{
    MyAbsolute(&a);
    MyAbsolute(&b);

    return a+b;
}
```

포인터를 매개변수로 사용하여 절댓값 덧셈 프로그램을 보다 유연하게 만든 코드이다. 그러나 사용자는 기존 라이브러리의 헤더파일에 MyAbsolute 함수의 원형이(이름이) 명시되어 있지 않으므로 이를 사용할 수 없게 된다.

이 때, 함수 포인터를 활용하면 함수 이름이 없어도, "함수의 주소를 받아서" 함수를 호출할 수 있다.

- MyAbsolute 함수의 함수 포인터 생성

```c
void (*fp_abs)(int *);
```

- 함수 포인터를 매개변수로 사용하는 함수 SumABS

```c
int SumABS(int a, int b, void (*fp_abs)(int *))     // fp는 함수 포인터의 약자. abs는 함수를 알 수 있게 해줌.
                                                    // 이렇게 변수 이름에 변수의 특징을 드러내 주는 것이 좋다
{
    (*fp_abs)(&a);
    (*fp_abs)(&b);

    return a+b;
}
```

이렇게 라이브러리 프로그래머가 함수 포인터를 이용해서 SumABS 함수를 구성하면, 사용자는 MyAbsolute라는 함수를 자신이 직접 만들어서, 이를 매개변수로 전달만 해주면 원하는 기능을 정상적으로 사용 가능하다. 굳이 이 기능이 아니라 그 어떤 기능이더라도 자신이 만든 함수를 매개변수로 넘겨주기만 하면, 어떤 기능이든 실행된다.

- 추가적인 기능의 함수가 필요하지 않고, 기존의 기본 기능만 필요한 경우

```c
int SumABS(int a, int b, void (*fp_abs)(int *))
{
    // fp_abs에 저장된 주소가 (함수가 아니라) NULL일 경우를 조건문으로 달아준다
    // NULL인 경우, 추가 기능 함수(여기서는 음->양)가 없다는 뜻이므로, 그냥 바로 넘어간다

    // 즉 추가기능 함수를 호출할 것인지, 선택할 수 있게 되는 것

    if (NULL != fp_abs) (*fp_abs)(&a);
    if (NULL != fp_abs) (*fp_abs)(&b);

    return a+b;
}
```

함수 포인터 매개변수 자리에 NULL을 써주면 된다. 기존의 코드는 매개변수에 NULL이 넘어오는 상황을 대비하지 않았기 때문에 if문으로 이 조건을 추가해준다.

## 라이브러리 프로그래머(4)

```c
// sum.h

int Sum(int a, int b, void (*pa) (int *), void (*pb) (int *));

// sum.lib

int Sun(int a, int b, void (*pa)(int *), void (*pb)(int *))
{
    if (NULL != pa) (*pa)(&a);
    if (NULL != pb) (*pb)(&b);

    return a+b;
}

// 추가기능x 단순 덧셈만 필요한 경우

#include "sum.h"
#pragma comment(lib, "sum.lib")

void main()
{
    int result = Sum(-2,-3,NULL,NULL);
}

// 추가기능o 첫 번째 매개변수에만 절댓값 적용

#include "sum.h"
#pragma comment(lib, "sum.lib")

void MyAbsolute(int *p)     // Sum 함수가 매개변수로 받기 위해서는 Sum 함수가 매개변수로써 정해놓은 형식을 지켜야 한다
                            // 즉 함수의 원형이 일치해야 한다. void (*p)(int *) 로
{
    if (*p<0) (*p) * -1;
}

void main()
{
    int result = Sum(-2, -3, MyAbsolute, NULL)      // 실제로 수행되는 코드
                                                    // MyAbsolute(&a);
                                                    // return a+b;
}
```

결과적으로 라이브러리 안에 있는 Sum 함수는 수정되지 않았지만, Sum 함수를 프로그래밍 할 때부터 '사용자가 원하는 추가 기능이 담긴, 사용자가 직접 만든 새로운 함수'를 받을 매개변수로 프로그래밍하여 원래 기능(명령어)이 실행되기 전에 실행되도록 하고, 이게 없을 경우도 예상해서 NULL에 관련된 if문도 추가해준 것이다.

이런 식으로 라이브러리를 프로그래밍 해 놓으면

- 사용자는 자신이 직접 추가 기능이 담긴 함수를 만들고 그것을 매개변수로 전달하기만 하면 된다.
- 매개변수로 함수를 호출하고 싶다면 함수 포인터를 사용하면 된다.

## 콜백 함수

이렇게 함수 포인터를 매개변수로 쓸 경우, 라이브러리 사용자 입장에서는 Sum.lib 파일 내부의 실제 소스코드는 볼 수 없으므로 실제로 언제,어떻게 호출되는지 자세한 사항은 알기 힘들다.

```c
if (NULL != pa) (*pa)(&a);
if (NULL != pb) (*pb)(&b);
```

즉 이런 세부적인 내부 코드를 알 수 없다는 뜻. 사용자는 그냥 적당히~ Sum함수가 적절한 시점에 매개변수로 전달된 함수를 호출해서 결과를 주겠거니~ 하게 된다.

이런식으로 자신이 사용할 함수가 명시적으로 호출되지 않고, 함수 포인터에 의해서 호출되는 방식을 콜백이라고 한다.

<aside>
💡 암시적 호출: 콜백 (Call Back)

</aside>

구체적으로 함수를 명시하지는 않지만, 주어진 상황을 통해 판단해서 함수를 사용(호출)하는 방법이다. 그러니까 우리가 지금까지 한 라이브러리와 함수 포인터 매개변수의 개념을 이용해서 만든 Sum함수가 콜백함수인거다.

### 콜백의 장점

콜백은 유지보수에 대하여, 미래를 예측하고준비하는 함수이다. 프로그래밍에서 예측을 많이 한다는 것은, 그 내용을 전부 if문으로 대비해줘야 한다는 것이고, 조건문이 많아지면 그 함수는 비효율적인 함수가 되어버리는 것이 필연적이다. 그런 의미에 있어서 콜백 구조는 효율적인 것이다. 정말 필요한 찐 본질적인 기능만 함수에 직접적으로 구현하고, 나머지 예상되는 조건은 함수 포인터를 사용하여 사용자들에게 스스로 추가하여 사용할 수 있게 하기 때문이다. 이것이 바로 OS가 콜백 구조를 사용하는 이유이기도 하다.