# 변수


![2_변수](https://user-images.githubusercontent.com/97890886/166634185-6eaaebbf-22fc-4139-a6a1-c3d10bd39237.png)


실수형 변수는 정수형 변수와 달리 “정밀도”의 차이가 범위를 좌우한다. 즉, 소수점 이하 7자리를 넘어선 정밀한 표현이 필요하다면 double을 써야 하는 것. 빠른 연산속도를 추구한다면 float을, 정밀도를 추구한다면 double을 사용하자.

## 변수의 명명규칙

1. 대소문자 구분O, 길이 제한X

2. 예약어(프로그래밍어의 구문에 사용됨) x

3. 숫자로 시작 x

4. 허용하는 특수문자는 '_' , '$'

### 암묵적 규칙(낙타형)

1. 클래스 이름의 첫 글자는 대문자로

2. 여러 단어로 이루어진 경우 단어의 첫 글자를 대문자로

3. 상수의 이름은 all 대문자, 언더바로

## 예제1 - 변수 사용

```python
public class VarEx1 {
    public static void main(String[] args) {
        int year = 0;
        int age = 22;

        System.out.println(year);
        System.out.println(age);
    }
    
}
```

## 예제2 - 변수 값 서로 바꾸기

```python
public class VarEx2 {
    public static void main (String[] args) {
        int x = 10;
        int y = 20;
        int temp = 0;

        System.out.println("x: " + x + "\n" + "y: " + y + "\n");

        temp = x;
        x = y;
        y = temp;

        System.out.println("x: " + x + "\n" + "y: " + y + "\n");
    }
}
```

# 상수와 리터럴


![2_상수](https://user-images.githubusercontent.com/97890886/166634229-4c82d208-a5f2-47c1-b617-45197bce9b5c.png)


리터럴이 우리가 아는 숫자라면, 상수라는 “변경할 수 없는” 단 하나의 값이 저장되는 메모리 공간이다. 그런데 굳이 상수라는 개념이 왜 필요한걸까?

```java
//상수가 필요한 이유

public class VarEx3 {
    public static void main(String[] arg) {
        final int WIDTH = 20; // 길이
        final int HEIGHT = 10; // 높이

        int triangleArea = (WIDTH * HEIGHT) / 2; // 삼각형 면적 공식
        int rectangleArea = WIDTH * HEIGHT; // 사각형 면적 공식

        System.out.println(triangleArea+rectangleArea);
    }
}
```

1. 유지보수(수정) 편리: 이후 길이, 높이 값을 변경해야 할 때 편함

2. 리터럴에 의미를 붙여 줌: 코드의 의도에 대한 이해를 높여 줌

- 문자 리터럴과 문자열 리터럴

```java
class Practice {
char ch = 'A';
String str = "";
String name = "Ja" + "va";
String name_2 =  name + 8;
String one = 7+7+"";    // == 14 + "" == "14" 라는 문자열
String two = ""+7+7;    // == "7" + 7 == "77" 라는 문자열
}
```

## 변수 간단하게 입출력해보기

- Scanner - 입력 클래스

```java
import java.util.*;

public class ScannerEx {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("두자리 정수 하나 입력.>");
        String input = scanner.nextLine();
        int num = Integer.parseInt(input);

        System.out.println("입력 내용: " + input);
        System.out.printf("num=%d\n",num);
        
        scanner.close();
    }
}
```

- printf() - 형식화된 출력

```java
int finger = 1;
System.out.printf("finger=[%5d]\n", finger);    // [    1]
System.out.printf("finger=[%-5d]\n", finger);   // [1    ]
System.out.printf("finger=[%05d]\n", finger);   // [00001]

// 대부분의 지시자가 C언어와 일치한다
// %x(16진수), %o(8진수) 앞에 #를 붙이면 접두사(각각 0x, 0)가 붙는다

// 자바는 2진수의 리터럴도 사용 가능하다
// 10진수 -> 2진수로 출력해주는 지시자는 없으므로, 만약 필요하다면 '정수->2진 문자열' 변환해주는
// intger.toBinaryString(int i) 를 사용해야 한다 (정수->2진수->문자열. 이므로 %s 지시자 사용)
// C언어에서는 char 값을 "%d"로 출력 가능했으나 자바는 불가능. casting 필요
```

# Casting

<aside>
❗ 변수 또는 상수의 타입을 다른 타입으로 변환하는 것

</aside>

```java
double d = 85.4;
int score = (int)d;

// 내부 연산과정
int score = (int)d;
int score = (int)85.4;
int score = 85;
```

피연산자인 변수 d의 값은 형변환 후에도 아무런 변화가 없으며, 형변환 연산자는 그저 피연산자의 값을 읽어서 지정된 타입으로 casting하고 그 결과를 반환할 뿐이다.