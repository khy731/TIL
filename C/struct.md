# 배열의 한계 극복
배열은 간단하지만 리스트의 크기가 가변적이지 못합니다. 자료형이 서로 다른 데이터를 한 곳에 묶어 원하는 크기의 리스트에 보관할 수는 없을까요?

# typedef

기존 자료형을 다른 이름으로 새롭게 정의하여 복잡한 문법을 단순화 해 봅시다.

```c
typedef unsigned char short int US;
US temp;
```

>장점
1. 복잡한 문법 단순화

문법을 보다 직관적이고 이해하기 쉬운 표현으로 사용 가능하다.

2. 자료형의 크기 변경 용이

예를 들어, 나이를 이용하는 프로그램을 짤 경우, int age라는 지역변수를 사용했다고 치자. age는 코드 여기저기서 중복되어서 사용된다. 만약 age의 자료형을 바꾸고 싶다면 코드에 존재하는 모든 age를 찾아다니면서 바꾸어줘야 한다. typedef는 이 불편함을 한 번에 변경 가능하도록 해결해준다.

>typedef와 배열

```c
typedef int MY_DATA[5];
MY_DATA temp;    // int temp[5];
```

>typedef와 포인터

```c
typedef int MY_DATA[5];
MY_DATA *p;    // int (*p)[5]
```

int (*p)[5]; 는 int[5] =20바이트 크기의 사용범위를 가지는 포인터 변수를 의미하며, 4바이트 크기의 포인터 변수 p가 가리키는 대상의 크기가 int[5]라는 뜻과 같다. 이 문법을 typedef를 통해 선언하면 포인터 변수 p가 MY_DATA라는 자료형(크기)를 가지며, 이 크기는 int[5]라는 것이 더 잘 드러난다.

# 구조체

 

## 배열의 한계

데이터를 관리하는 데 있어서, 나열형은 한계가 있다. 그래서 나온 것이 배열이다. 그러나, 배열은 크기가 같은(==자료형이 같은)데이터만 그룹으로 묶을 수 있기 때문에 실용성이 떨어지는 단점이 있다.

<aside>
✔️ 유저를 정리하는 프로그램을 만들 때, 이름/키/몸무게를 각 항목별로 정리하는 것 보다, 각 요소를 한 번에 묶어 “사람 한 명”단위로 정리하는 것이 효과적이다.

</aside>

  

## 구조체 선언하기

```c
struct People
{
    char name[12];              // 이름, 12바이트  
    unsigned short int age;     // 나이, 2바이트
    float height;               // 키, 4바이트
    float weight;               // 몸무게, 4바이트
}
```

  

## 구조체의 크기

```c
struct People data;                 // 일반 변수 (22바이트)
struct People friend_list[64];      // 배열 (22x64바이트)
struct People *p;                   // 포인터 (4바이트) -> 주소값 저장
```

구조체 People 자료형의 크기는 22(12+2+4+4), 즉 구조체 내에 선언한 요소들의 크기를 모두 더한 것과 같다.

## 구조체와 typedef

typedef를 사용하여 구조체로 선언한 자료형을 보다 쉽게 이용해 보자.

```c
typedef struct People   //앞에 typedef가 없으면 새 자료형에 대한 별명(typedef)이 아닌,
                        //걍 구조체 people에 대한 변수 Person을 선언한 것이 되므로 표기 주의
{
    char name[12];             
    unsigned short int age;     
    float height;               
    float weight;               
} Person;
```

## 구조체로 선언한 변수의 요소 사용하기

각 요소에 인덱스 “ . “ 로 접근할 수 있다.

```c
typedef struct People
 {
    char nage[12];
    unsigned short int age;     
    float height;               
    float weight;   
 } Person;

 void main()
 {
    Person data;    // Person 자료형으로 data라는 지역변수 선언

    data.age=21;    // data 변수 내의 age라는 요소에 21 대입
    data.height=178.3;  // data 변수 내의 height라는 요소에 178.3 대입
 }
```

> 구조체 자료형으로 배열 변수 선언 및 요소 사용하기

```c
Person friends[3];      // Person 데이터 3개를 저장할 수 있는 메모리 할당 (크기는 22x3=66)
friends[1].age=22;      // 두 번째 요소의 age에 값 22 대입
```

> 구조체 자료형으로 선언한 변수를 포인터로 사용하기

```c
Person data;    // Person 자료형으로 data 변수 선언
Person *p;      // Person 형식으로 선언한 메모리에 접근할 수 있는 포인터 선언
p = &data;      // 포인터 변수 p에 data 주소 값 저장
(*p).age = 23;  // p에 저장된 주소에 가서 age 요소에 값 23 대입
```

이 때 주소지정 연산자 * 은 요소지정 연산자 . 보다 우선순위가 낮기 때문에 괄호를 항상 써 줘야 한다. 이 불편함을 해결하기 위해 대신 → 연산자를 사용한다.

```c
p->age = 23;      // (*p).age 와 같다
```

> 구조체 문법으로 선언한 변수 초기화하기

```c
typedef struct People
{
    char name[20];
    unsigned short int age;
    float height;
} Person;

void main()
{
    Person data = {"강혜윤", 22, 169.8};    // 구조체 내 요소와 순서가 같아야 한다
}
```

# 구조체의 장점 - 배열과 비교

  *예시: 친구 정보 관리 프로그램*

1. 메인 메뉴 : main 함수

사용자가 프로그램에서 제공하는 기능을 선택할 수 있게 한다. 종료 메뉴 기능은 반복문을 빠져나옴으로써 실행되므로, 개별 기능으로 분리x

2. 친구 추가하기 메뉴 : AddFriend 함수

scanf 표준 함수 사용 > 한번에 1명씩 / 최대 5명까지 입력받기. 5명을 넘기면 오류로 처리

3. 친구 목록 보기 메뉴 : ShowFriendList 함수

입력된 친구 목록을 보여준다. 등록된 친구가 없다면 오류 메세지 출력

>배열을 사용했을 때

```c
#include <stdio.h>
#define MAX_COUNT 5
typedef char NAME_TYPE[14];     // 원래는 그냥 배열 name[14]로, 이름을 최대 14글자 받겠다는 뜻의 1차원 문자열 배열이다
                                // 그러나 사람 5명분의 이름 배열을 저장해야 하므로 2차원 배열을 사용해야 하는데
                                // 그러면 너무 복잡해지고, 포인터로 표현할때도 char (*p_name)[14]; 이런 식으로 써야 하니까 typedef해준거
                                // char name[MAX_COUNT][14]; -> NAME_TYPE name[MAX_COUNT];
                                // char (*p_name)[14] -> NAME_TYPE *p_name;
int AddFriend (NAME_TYPE *p_name, unsigned short int *p_age, float *p_height, int count)
{
    if (count < MAX_COUNT) {
        printf("\n 새로운 친구 정보 입력\n");
        printf("1. 이름: ");
        scanf("%s", &*(p_name+count));
        printf("\n2. 나이: ");
        scanf("%d", &*(p_age+count));
        printf("\n3. 키: ");
        scanf("%f", &*(p_height+count));
        printf("\n입력 완료\n");
        return 1;
    }
    else {
        printf("저장할 수 있는 친구 숫자 초과\n");
        printf("최대 %d명까지 저장 가능합니다.\n", MAX_COUNT);
        return 0;
    }
}

void ShowFriendList(NAME_TYPE *p_name, unsigned short int *p_age, float *p_height, int count)
{
    int i;
    if (count > 0) {
        printf("\n등록된 친구 목록\n");
        printf("===================================\n");
        for (i=0; i<count; i++) {
            printf("%s : %d살, %.2fcm\n", *(p_name+i), *(p_age+i), *(p_height+i));
        }
        printf("===================================\n");
    }
    else printf("입력된 친구가 없습니다\n");
}

void main()
{
    NAME_TYPE name[MAX_COUNT];
    unsigned short int age[MAX_COUNT];
    float height[MAX_COUNT];
    int count=0, num;

    while(1)
    {
        printf("    [친구 관리 시스템]  \n");
        printf("===================================\n");
        printf("1. 친구 추가\n");
        printf("2. 등록된 친구 보기\n");
        printf("3. 종료\n");
        printf("===================================\n");
        printf("메뉴 번호를 입력하세요: ");
        scanf("%d", &num);

        if (num==1) {
            if (1==AddFriend(name, age, height, count)) count++;
        }
        else if (num==2) {
            ShowFriendList(name, age, height, count);
        }
        else if (num==3) {
            break;
            printf("\n종료되었습니다.\n");
        }
        else printf("\n1~3번호만 입력 가능합니다.\n");
    }
}
```

> 구조체를 사용했을 때

```c
#include <stdio.h>
 #define MAX_COUNT 5

 typedef struct People
 {
    char name[14];
    unsigned short int age;
    float height;
 }  Person;

 int AddFriend(Person *p_friend, int count)
 {
    if (count<MAX_COUNT) {
        p_friend=p_friend+count;
        printf("\n새로운 친구의 정보 입력\n");
        printf("============================\n");
        printf("1. 이름: ");
        scanf("%s", &p_friend->name);    //&((*p_friend).name))
        printf("2. 나이: ");
        scanf("%d", &p_friend->age);     //&((*p_friend).age))
        printf("3. 키: ");
        scanf("%f", &p_friend->height);  //&((*p_friend).height))
        printf("\n입력 완료\n");
        return 1;
    }
    else {
        printf("더이상 입력 불가. 최대 입력 가능 친구 수는 %d명입니다", MAX_COUNT);
        return 0;
    }
 }

 void ShowFriendList(Person *p_friend, int count)
 {
    int i;
    if (count>0) {
        printf("\n등록된 친구 목록\n");
        printf("============================\n");
        for (i=0; i<count; i++) {
            printf("%s : %d살, %.2fcm\n", p_friend->name, p_friend->age, p_friend->height);
            p_friend++;
        }
    }
    else printf("등록된 친구가 없습니다.\n");
 }

 void main()
 {
     Person friends[MAX_COUNT];
     int count, num=0;

     while(1) {
         printf("\n[친구 정보 관리 시스템]\n");
         printf("============================\n");
         printf("1. 친구 등록하기\n");
         printf("2. 친구 정보 보기\n");
         printf("3. 종료하기\n");
         printf("메뉴 번호를 입력하세요(1,2,3): ");
         scanf("%d", &num);

        if (num==1) {
            if (1==AddFriend(friends, count)) count++;
        }
        else if (num=2) {
            ShowFriendList(friends, count);
        }
        else if (num==3) {
            break;
            printf("\n종료되었습니다.\n");
        }
        else printf("\n1~3 번호만 입력 가능\n");
     }
 }
```

배열로 했을 때보다 친구 정보를 Person자료형으로 하나로 묶어 사용하는 구조체가 더 좋다. 처리해야 할 데이터가 모두 하나로 통합되며, 매개변수도 1개로 줄어들고, 포인터 표현도 단순해짐.

# 구조체의 단점 - 메모리 낭비

## 구조체의 한계와 해결

<aside>
🚫 구조체는 다양한 크기의 메모리를 하나의 그룹으로 묶어서 사용하므로 구조체 요소를 사용할 때 실행 속도가 저하된다.

</aside>

<aside>
⭕ C언어 컴파일러에 존재하는 ‘구조체 멤버 정렬(Struct Member Alifnment) 기능이 구조체의 요소를 일정 크기를 기준으로 정렬하여 실행 속도를 향상시켜준다.

</aside>

## 구조체 멤버 정렬에 대하여

컴파일러에서 구조체 정렬 기준을 어떻게 설정하는지에 따라 구조체로 만든 자료형의 크기가 달라진다.

*1. 1바이트 정렬*

*2. 2바이트 정렬*

*3. 4바이트 정렬*

*4. 8바이트 정렬*

![12 구조체메모리낭비](https://user-images.githubusercontent.com/97890886/162206356-ac6e54fe-5462-4155-a277-c0e09b1e2ce1.png)


다양한 바이트 정렬 방식이 있지만, 애석하게도 요즘의 컴파일러들은 8바이트 정렬-메모리 낭비가 큰 편-을 기본값으로 하기 때문에 메모리 낭비를 최소화하기 위해서는 프로그래머의 스킬이 필요하다.

- *구조체의 요소는 같은 크기끼리 모아줘라*
- *동적 메모리 할당시 구조체의 크기를 직접 계산x 자료형의 크기를 계산해주는 sizeof 연산자를 사용하는 것이 안전하다*