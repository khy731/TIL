# 제어문

조건에 따라 코드 블록을 실행(조건문), 반복 실행(반복문)한다. 위→아래 순차적인 일반적인 코드 진행 방향과는 달리, 코드의 실행 흐름을 인위적으로 제어한다. 많이 사용하면 코드의 흐름을 해치므로, 함수형 프로그래밍에서는 제어문의 사용을 억제하는 추세이다.

# 조건문

불리언 값으로 평가될 수 있는 표현식. 자바스크립트에서는 if...else 문과 switch문을 지원한다.

## if...else 문

논리적 참/거짓으로 실행할 코드 블록을 결정한다.

삼항 조건 연산자로 바꿔쓸 수 있다. 이는 표현식이므로 값처럼 사용할 수 있기 때문에 변수에 할당하는 것도 가능해진다.

## switch 문

참/거짓보다는 다양한 상황(case)에 따라 실행할 코드 블록을 결정한다.

break의 사용에 대해 주의하자. default문에서는 안 써도 된다

# 반복문

조건식의 평가 결과가 true인 경우 코드 블록을 실행한다. →를 조건식이 false일 때 까지 반복한다.

## for문

반복 횟수가 명확할 때 주로 사용한다.

```jsx
for (var i = 0; i < 6; i++ ) {
    for (var j = 0; j < 6; j++) {
        if (i + j === 5) console.log(`${i} + ${j} = 5`);
        }
    }
```

## while문

기본적으로 무한반복문이므로, 반복 횟수가 불명확할 때 주로 사용한다. 조건식의 평가 결과가 불리언 값이 아니어도 불리언 값으로 강제 변환하여 논리적 ToF를 구별한다.

```jsx
var num = 0;
var count += num;

// 무한루프
while(true) {
    console.log(count);
    num++;
    if (count > 10) break;
}
```

## do...while 문

일단 실행하고 조건식을 평가한다 → 코드 블록은 무조건 한 번 이상 실행된다.

## break 문

반복문에서 가장 가까운 코드 블록을 탈출한다. 조건식에서는 switch문에서만 사용. 또는 레이블문에서 사용한다.

> 레이블 문 label statement
> 

```jsx
foo : console.log(`foo`);
```

프로그램 실행 순서를 제어하는 데에 사용된다. (따지자면 switch도 레이블 문의 원리이다. )

## continue 문

break나 continue는 반복문 내에서 특정 조건에서 반복문을 탈출(break)하거나 그 조건에서만 반복문을 실행하지 않고 다음 조건식으로 넘어가는(continue)역할을 한다.

```jsx
let str = `Hello Wolrd`;
let search = `l`;

// continue 사용 x
for (let i = 0; i < str.length; i++) {
    if (str[i] === search) {
        count++;
    }
}

// continue 사용 o
for (let i = 0; i < str.length; i++) {
    if (str[i] !== search) continue;
    count++;
}
```

if문 이후의 코드가(그러니까 특정 조건에만 실행하게 될 문이) 복잡하지 않을 때 continue를 사용하는 것이 좋다.