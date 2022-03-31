# 컴퓨터처럼 생각하고, 사용자의 입장에서 프로그래밍하라

사용자로부터 입력을 받아 처리하는 C언어의 표준 입력 함수는 문법은 단순하지만 내부 처리 과정은 상당히 복잡합니다. 내부 처리 과정은 컴퓨터의 입장에서, 문법은 사용자의 입장에서 공부해 봅시다.

# 표준 입력 함수에 대하여

## 동작 원리

<aside>
💡 사용자 입력 → 표준 입력 버퍼(임시 저장) → Enter 입력 →  입력값 사용

</aside>

입력 버퍼에 사용자가 입력한 값이 남아있거나, 없으면 Enter 키를 누를 때까지 데이터를 입력받아 표준입력함수가 동작하게 됩니다.

## 입력 버퍼 초기화 함수 rewind

```c
rewind(stdin);
```

입력 버퍼에 쓰레기값이 남아있으면 다음 실행될 함수에게 악영향을 미칩니다. 이러한 경우를 대비하여 입력 버퍼 초기화 함수를 사용합니다.

# 문자, 문자열 입력 함수

## getchar 함수

```c
#include <stdio.h>

void main()
{
    int input_data;
    input_data=getchar();
    printf("입력받은 값은 %c입니다\n", input_data);
}
```

- 문자 한 개를 입력받는 표준 입력 함수
- int형으로 데이터 반환 (이 자료형은 확장키 값을 위해 정의된 것이기 때문에, 일반적인 입력 문자의 크기인 char을 사용해도 상관없다.)

### getchar 함수의 한계점

```c
int input_data;

input_data=getchar();
printf("첫번째 입력받은 값은 %c입니다\n", input_data);
input_data=getchar();
printf("두번째 입력받은 값은 %c입니다\n", input_data);
```

문자 여러개를 각각 입력받아 순서대로 출력하는 작업이 불가능하다.  첫 번째 입력에서 데이터를 입력하고 Enter을 누르는 순간 코드의 getchar 함수가 전부 가동하므로 이후 입력은 정상적인 입력 값이 아닌 Enter의 값만이 인식이 되어 new line만 출력된다.

### getchar 함수의 한계점의 해결법?

1. getchar 함수 밑에 또 getchar 함수를 한번 더 써줌으로써 Enter 키 입력 무시하게끔 하기

→ 그러나 이는 getchar 함수의 근본적 기능을 해치고, 사용자의 입력 수를 예측할수 없다.

1. rewind 함수를 사용하여 표준 입력 버퍼를 초기화한다
2. getc 함수를 사용한다.

getc 함수: getchar 함수의 어머니. 파일 포인터를 매개변수로 넘겨주면 파일을 1바이트씩 읽어주는 파일 입출력 함수. 표준 입출력에 와서는 인수로 stdin을 일일히 입력하는 것이 귀찮아 getchar를 따로 정의하게 된 것.

## gets 함수

```c
#include <stdio.h>

void main()
{
    char input_string[20];
    gets(input_string);
    printf("%s\n", input_string);
}
```

- 문자열을 입력받는 표준 입력 함수
- Enter를 누르는 순간 입력된 모든 문자를 하나의 문자열로 간주하여 보낸다.
- 매개변수를 사용: char 배열로 선언된 변수의 시작 주소를 받는다.

(배열의 시작 주소=배열의 첫 번째 요소의 시작 주소이므로 정확한 표현은 gets(&input_string[0])이다.)

- Enter 키까지 입력 버퍼에서 읽어와 사용하므로 getchar처럼 Enter값이 trash 값으로 취급되지 않고, Enter 키를 입력한 위치에 NULL을 표현하는 아스키 문자인 ‘0’이 들어가게 된다.

### gets 함수의 한계점

1. 표준입력을 받던 도중 ctrl+c로 프로그램을 중지시키면 입력 버퍼의 문자열이 인수에 복사되지 못한 채 함수 종료→출력시 trash값이 섞여 출력됨
2. 입력받는 문자열의 개수를 제한하지 못함→예상하여 지정한 크기보다 더 긴 문자열이 입력되면 강종된다.

### gets 함수의 한계점의 해결법?

```c
#include <stdio.h>

void main()
{
    char input_string[10];

    if (NULL != gets(input_string)) {
        printf("%s\n", input_string);}
    else {
        printf("입력이 취소되었습니다\n");}
}
```

1. 사용자가 정상적으로 입력을 하지 않은 상황에서도 대처가 가능하도록 NULL 조건문을 사용한다.

```c
#include <stdio.h>

int GetMyString (char myString[], int limit)
{
    int i;
    for (i=0; i<limit; i++) {
        myString[i]=getchar();
        if (myString[i] == '\n') {
            myString[i]=0;
            return 1;
        }
    }
    myString[i] = 0;
    rewind(stdin);
    return 0;
}

void main()
{
    char data[10];
    int state=GetMyString(data,9);

    if (state==1) {
        printf("%s\n", data);
    }
    else {
        printf("입력 오류입니다\n");
    }
}
```

1. getchar 함수를 for문을 사용하여 gets 함수처럼 사용한다.

# 문자열을 정수로 변환하기

gets로 입력받은 값은 문자열이므로, 숫자값을 입력받아도 이로 산수를 하지 못한다. gets로 입력받은 문자열을 정수로 변환하여 연산해보자.

## 아스키코드 표 이용하기

### 문자 1 ⇒ 숫자 1

<aside>
💡 ‘1’ - ‘0’ ⇒ 49 - 48 ⇒ 1

</aside>

특정 숫자의 아스키코드 값에서 0의 아스키코드를 빼주면 원래의 숫자값이 나오는 것을 이용한다.

### 문자123 ⇒ 숫자123

<aside>
💡 ('1'-'0')*100 + ('2'-'0')*10 + ('3'-'0')*1 -> 100+20+3 -> 123

</aside>

### 함수1

```c
#include <stdio.h>

void main()
{
    int pos_num=100, num=0, i, temp_num;

    char num_string[] = "123";

    for (i=0; i<3; i++) {
        temp_num=num_string[i]-'0';
        num=num+temp_num*pos_num;
        pos_num=pos_num/10;
    }
    printf("%s -> %d", num_string, num);
}
```

### 함수2: 길이 제한 없이

```c
#include <stdio.h>
#include <string.h>

void main()
{
    char num_string[] = "2423432";
    int i, num=0, temp_num, count=strlen(num_string), pos_num=1;

    for (i=0; i<count-1; i++) pos_num=pos_num*10;

    for (i=0; i<count; i++) {
        temp_num = num_string[i]-'0';
        num=num+temp_num*pos_num;
        pos_num=pos_num/10;
    }
    printf("%s -> %d", num_string, num);
}
```

### 함수3: 자릿수 제한 없이

```c
#include <stdio.h>

void main()
{
    int num=0, i=0;
    char num_string[]="14214";

    while(num_string[i] !=0) {
        num=num*10 + (num_string[i] -'0');
        i++;
    }
    printf("%s -> %d\n", num_string, num);
}
```

### 함수4: 최종

```c
#include <stdio.h>

int ArrayToInteger(char string[])
{
    int num=0, i=0;

    while(string[i] !=0) {
        num=num*10 + (string[i] -'0');
        i++;
    }
    return num;
}

void main()
{
    int input_num;
    char input_string;

    printf("input number: ");
    gets(input_string);

    input_num = ArrayToInteger(input_string);

    printf("\n%d\n", input_num);
}
```

### atoi 함수

```c
#include <stdlib.h>

void main()
{
int num;
char string[10];

printf("숫자 입력: \n");
gets(string);

num=atoi(string);
printf("%d", num);
}
```

숫자 형태의 문자열을 정수로 바꾸는 함수는 사용 빈도가 높으므로 C언어 표준 라이브러리에서 제공한다.

# 표준 입력 함수 scanf

```c
int datda;
scanf (”%d”, &data);
```

- scanf는 형식화된 입력을 제공합니다.

<aside>
💡 입력 형식 지정 키워드 + 입력받은 값을 저장할 변수의 주소

</aside>

- scanf는 포인터 기술을 사용하여 값을 반환합니다. → getchar와 달리 한 번의 호출로 여러개의 값을 입력받을 수 있습니다.

<aside>
💡 사용자 입력 → Enter/공백 등 ‘단 한 번의 클릭’ → scanf가 입력받은 주소로 찾아가서 지정한 형식에 맞게 갑 대입

</aside>

## scanf 함수 사용 시 주의점

변수의 자료형과 입력 키워드가 일치해야 한다.

```c
short num;
scanf("값 입력: %d", &num);
// error !!
```

입력 키워드의 의미: 함수 내부적으로 casting하여 처리한다는 뜻. %d를 사용하면 int *, %c를 사용하면 char *형으로 형변환한다.

printf 함수는 변수의 값을 전달받아 사용자가 지정한 형식에 맞게 출력하는 방식이기 때문에 서로의 자료형이 일치하지 않으면 error가 생기게 된다.

## 예제: 나이 입력받기(false code)

```c
#include <stdio.h>

void main()
{
    int age=0;

    while (1) {     //정상적인 나이를 입력할 때까지 무한 반복을 사용
    printf("나이 입력: ");
    scanf("%d", &age);
        if (age>0 && age<100) {
            printf("당신의 나이는 %d입니다", age);
            break;
        }
        else {
            printf("잘못된 값입니다. 다시 입력하세요");
        }
    }
}
```

### 문제점

입력 범위가 정수에 한해있기 때문에 실수로 유저가 문자를 입력할 경우 scanf는 %d만 인식하는데 정수가 아닌 문자가 오니, 입력 형식을 인식하는 과정에서 오류가 생겨 오류 값만 무한 반환한다.

### 해결

사용자의 잘못된 입력으로 scanf함수가 실패했을 때를 대비하여 입력 버퍼에 저장되어 있는 잘못된 코드를 제거해주기 위해 rewind 함수를 사용한다.

## 예제: 나이 입력받기(clean code)

```c
#include <stdio.h>

void main()
{
    int age=0;

    while (1) {     //정상적인 나이를 입력할 때까지 무한 반복을 사용
    printf("나이 입력: ");
    scanf("%d", &age);
        if (scanf("%d", &age)==0) {
            rewind(stdin);
            printf("숫자만 입력이 가능합니다");
        }
        else if (age>0 && age<100) {
            printf("당신의 나이는 %d입니다", age);
            break;
        }
        else {
            printf("잘못된 값입니다. 다시 입력하세요");
        }
    }
}
```