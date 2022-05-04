# 배열

같은 타입의 여러 변수를 하나의 묶음으로 다루는 것

# 배열과 선언과 메모리 할당

```java
/* 배열의 선언*/
int[] data;    // 타입[] 변수이름;
int data[];    // 타입 변수이름[];

/* 메모리 할당*/
data = new int[5];    // 변수이름 = new 타입[길이];

/* 선언과 메모리 할당을 동시에 */
int score[] = new int[5];
```

# 배열의 초기화

기본적으로 자바의 배열은 생성과 동시에 초기화되므로 따로 초기화할 필요는 없지만, 원하는 초깃값을 따로 대입하고 싶을 때는 각 요소마다 값을 지정해 주어야 한다. 이는 for문으로도 가능하지만 중괄호{}를 이용하면 보다 쉽게 초기화를 할 수 있다.

```java
int[] score = new int[] {10,20,30,40,50};    // 배열의 생성과 초기화를 동시에
int[] score = {10,20,30,40,50};    // new int[]를 생략

int[] score;
score = {10,20,30,40,50} // error! 생성과 초기화를 구분하는 경우 new 연산자 생략 불가

int add(int[] arr) {  /* 내용 생략 */  }    // 매개변수로 int 배열을 받는 add 메서드
int result = add({10,20,30,40,50});    // error! new 연산자 생략 불가
```

# 배열의 길이

## 길이가 0인 배열

```java
int arr[] = new int[0];    // 길이가 0인 배열도 생성 가능
```

## 배열의 길이에 대한 정보 얻기

```java
int arr[] = new int[5];
int tmp = arr.length;    // 배열이름.length로 길이를 알 수 있다
```

- 배열은 한 번 생성하면 길이를 변경 할 수 없음 → 이미 생성된 배열의 길이 또한 변하지 않는다.
- 즉, ‘배열이름.length’ 라는 값은 상수이다

### .length 함수의 유용성

모든 경우에 배열의 길이를 직접 적어주는 것보다, 이를 함수화된 상수로 적어주는 것이 좋다.

## 배열 길이 변경하기

1. 더 큰 배열을 새로 생성
2. 기존 배열의 elements를 새로운 배열로 복사

→ 비용이 많이 드는 작업이기 때문에 처음부터 배열의 길이를 넉넉하게 잡는 것이 좋다. 그러나 또 너무 크게 잡으면 메모리가 낭비되기 때문에 2배정도가 좋다.

# 배열의 출력

배열을 초기화하는 가장 원초적인 방법이 for문을 사용하는 것이었듯이, 배열에 저장된 값을 확인할 때에도 for문을 사용하지만, Arrays.toString(배열명) 메서드를 사용하면 편리하다.

```java
int[] iArr = (10,20,30,40,50);
System.out.println(Arrays.toString(iArr));    // 배열 iArr의 모든 요소 출력

/* 결과 */
[10,20,30,40,50,]    // 이런 식으로 출력됨
```

### 배열 변수는 참조변수이다

만약 배열 변수 iArr을 바로 출력하면? → iArr은 ‘배열 변수’, 즉 실제로 배열의 값들이 저장되어 있는 메모리를 가리키는 참조 변수기 때문에 배열의 주소가 출력될 것 같지만, 타입@주소 형태의 값이 출력된다. (예외적으로 char 배열을 동일한 방법으로 출력 시도할 시, 각 요소가 구분자 없이 그대로 출력된다. for문이 없이도 배열에 저장된 모든 문자를 출력할 수 있다.)

```java
int[] iArr = {10,20,30,40};
System.out.println(iArr);    // I@14318bb 같은 형식의 문자열 출력

char[] chArr = {'a', 'b', 'c', 'd'};
System.out.println(chArr);    // abcd 그대로 출력
```

# 배열의 복사

- for문을 사용하여 복사하기


![4_배열_복사](https://user-images.githubusercontent.com/97890886/166634266-56663be5-7725-4bf2-9277-e0ee6977435a.png)



```java
public class ArrayEx3 {
    public static void main(String[] args) {
        int[] arr = new int[5];
        for (int i=0; i<arr.length; i++) {
            arr[i] = i+1;
        }

        System.out.println("before: " + Arrays.toString(arr));

        int[] tmp = new int[arr.length * 2];
        
        for (int i=0; i<arr.length; i++) {
            tmp[i] = arr[i];
        }
        arr = tmp;

        System.out.println("later: " + Arrays.toString(arr));
    }
}
```

- System.arraycopy() 메서드를 사용하여 복사하기

```java
/*
for (int i=0; i<arr.length; i++) {
            tmp[i] = arr[i];
}
*/

System.arraycopy(arr, 0, tmp, 0, arr.length);
// arr[0] 에서 tmp[0] 으로 arr.length개의 데이터를 복사
// 여유공간 부족 시 error!
```