# Iteration Protocol(이터레이션 프로토콜)

> Iterable(순회 가능)한 data collection(자료 구조)을 만들기 위해 ES6에서 도입된 규칙
> 

ES6 이전의 순회 가능한 데이터 컬렉션()들은 통일된 규약 없이 각자 나름대로 다뤄졌지만(for...in 문, forEach 메서드 등), ES6 이후로 **순회 가능한 데이터 컬렉션을 이터레이션 프로토콜을 준수하는 `이터러블`로 통일**하여 `for...of`, `스프레드 문법`, `배열 디스트럭처링 할당`의 대상으로 사용하도록 일원화했다. 

이터레이션 프로토콜에는 다음 두 가지가 있다 : 이터러블 프로토콜, 이터레이터 프로토콜

## iterable protocol(이터러블 프로토콜)

> Symbol.iterator 메서드를 구현/호출하면 이터레이터 프로토콜을 준수한 `이터레이터`를 반환하도록 하는 규약.
> 

이터러블 프로토콜을 준수한 객체를 이터러블이라고 한다. 

## iterator protocol(이터레이터 프로토콜)

> 이터레이터가 소유한 next 메서드를 호출하면 `이터레이터 리절트 객체`(value, done 프로퍼티 가짐)를 반환하도록 하는 규약.
> 

이터레이터 프로토콜을 준수한 객체를 이터레이터라고 한다. 이터레이터는 이터러블의 요소를 탐색하기 위한 일종의 **포인터**이다.

## 이터레이션 프로토콜의 필요성

다양한 데이터 공급자가 각자의 순회 방식을 갖는다면 데이터 소비자(활용 영역)는 그 방식들을 전부 지원해야 하므로 비효율적이다. → 프로토콜(규약)을 정의하여 단 하나의 순회 방식을 갖는다면 데이터 소비자는 이터레이션 프로토콜만 지원하도록 구현되면 된다.

이터러블을 지원하는 데이터 소비자는 다음과 같은 순회 방식을 갖는다 :

1. 내부에서 Symbol.iterator 메서드를 소환하여 이터레이터 생성
2. next 메서드를 호출하여 이터러블을 순회하며 result 객체 반환
3. result 객체의 value/done 프로퍼티 값 취득

![iteration-protocol](https://user-images.githubusercontent.com/97890886/168004072-439b7364-e668-43ba-aaff-02fe9f6140b3.png)

이터레이션 프로토콜은 다양한 데이터가 `하나의 순회 방식`을 갖도록 규정하여 데이터 소비자가 효율적으로 데이터 공급자를 사용할 수 있도록 이들을 연결하는 `인터페이스`역할을 한다.

## 이터러블

이터러블 프로토콜을 준수한 객체.

> `Symbol.iterator`(을 프로퍼티 키로 사용한) 메서드를 직접 구현/프로토타입 체인으로 상속받은 객체
> 

```jsx
// 이터러블인지 확인하는 함수
const isIterable = v => v!== null && typeof v[Symbol.iterator] === `function`;

// 배열, 문자열, Map과 Set 등은 이터러블이다
isIterable([]);    // T
isIterable(``);    // T
isIterable(new Map());    // T
isIterable(new Set());    // T

// 일반 객체는 이터러블 프로토콜을 준수한 이터러블이 아니다 -> 밑 3가지 문법 사용 불가능
// 사용자 정의 이터러블로 이터러블 프로토콜을 준수하도록 구현할 수 있다
// 최근에는 일반 객체에도 스프레드 문법을 허용하는 제안이 있다
isIterable({})    // F
```

배열은 Array.prototype의 Symbl.iterator을 상속받으므로 이터러블이다.

```jsx
// 배열은 Array.prototype의 Symbol.iterator 메서드를 상속받는다
// -> 이터러블이다
const array = [1,2,3];
console.log(Symbol.iterator in array);  // T

// 1. for...of 문으로 순회 가능
for (const item of array) {
    console.log(item);    // 1 2 3
}
// 2. 스프레드 문법의 대상으로 사용 가능
console.log([...array]);    // [1,2,3]
// 3. 배열 디스트럭처링 할당의 대상으로 사용 가능
const [a, ...rest] = array;
console.log(a, rest);      // 1 [2,3]
```

## 이터레이터

Sumbol.ieterator 메서드가 반환한 이러테이터는 전부 next 메서드를 갖는데, 이를 이용하면 이터러블을 순차적으로 한 단계씩 순회하며 순환 결과(=== 이터레이터 리절트 객체)를 나타낼 수 있다

## 빌트인 이터러블

자바스크립트가 제공하는 이터레이션 프로토콜을 준수하는 빌트인 이터러블.

EX ) Array, String, Map, Set, TypedArray arguments, DOM컬렉션 등이 있다.

# for...of 문

```jsx
for (const item in [1,2,3]) {
    // item 변수에 순차적으로 1,2,3이 할당됨
    console.log(item);
}
```

이터러블을 순회하면서 이터러블의 요소를 변수에 할당한다.

## 내부 동작

```jsx
for (const item of [1,2,3]) {
    // item 변수에 순차적으로 1,2,3이 할당됨
    console.log(item);
}

// for...of 문의 내부 동작

// 이터러블
const iterable = [1,2,3];

// 이터레이터
// 이터러블의 Symbol.iterator 메서드를 호출하여 이터레이터 생성
const iterator = iterable[Symbol.iterator()];

for (;;) {
    // 이터레이터의 next 메서드를 호출하여 이터러블을 순회
    // next 메서드는 -> 이터레이터 리절트 객체 반환
    const result = iterator.next();

    if (result.done) break;

    const item = result.value;
    console.log(item)
}
```

1. 내부적으로 이터레이터의 next 메서드를 호출하여 이터러블을 순회
2. next 메서드가 반환한 이터레이터 리절트 객체의 value 프로퍼티 값을 for...of 문의 변수에 할당
3. done 프로퍼티의 값이 false이면 순회 계속, true이면 순회 중단

# 유사 배열 객체

- 인덱스(를 나타내는 숫자 형식의 문자열)를 프로퍼티 키로 갖음 → 인덱스로 프로퍼티 값에 접근 가능
- length 프로퍼티를 갖음 → for문으로 순회 가능

```jsx
const arrayLike = {
    // 1. 인덱스(를 나타내는 숫자 형식의 문자열)를 프로퍼티 키로 갖음
    0 : `a`,
    1 : `b`,
    2 : `c`,
    // 2. length 프로퍼티를 갖음
    length : 3
};

// 2. for문으로 순회 가능
for (let i=0; i<arrayLike.length; i++) {
    // 1. 인덱스로 프로퍼티 값에 접근 가능
    console.log(arrayLike[i]);
}
```

> `유사 배열 객체`는 **이터러블이 아닌** `일반 객체`다.
> 

유사 배열은 이터러블이 아니다 === symbol.iterator 메서드가 없다 → for...of 문으로 순회 불가능

## 유사 배열이면서 이터러블인 객체

ES6 이후 이터러블이 도입될 때 Symbol.iterator 메서드가 구현된 유사 배열 객체는 유사 배열 객체이면서 이터러블이다.

- arguments
- NodeList
- HTMLCollection

`Array.from` 메서드를 사용하면 유사 배열 객체나 이터러블을 인수로 전달받아 배열로 변환하여 반환한다.

# 사용자 정의 이터러블

이터레이션 프로토콜을 준수하지 않는 일반 객체를 수동으로 이터레이션 프로토콜을 준수하도록 구현하여 사용자 정의 이터러블로 만든다.

## 구현하기

피보나치 수열을 구현한 간단한 사용자 정의 이터러블 구현

```jsx
// 사용자 정의 이터러블 그런데 이제 피보나치 수열을 구현한

const fibonacci = {
    // Symbol.iterator 메서드를 구현해 이터러블 프로토콜을 준수
    [Symbol.iterator]() {
        let [pre, cur] = [0,1];    // 배열 디스트럭처링 할당
        const max = 10;    // 피보나치 수열의 최대값

        // Sumbol.iterator 메서드는 이터레이터(next 메서드 소유)를 반환해야 함
        return {
            next() {
                [pre, cur] = [cur, pre+cur];
                // next 메서드는 이터레이터 리절트 객체를 반환해야 함
                return {value: cur, done: cur>=max}
            }
        };
    }
};

// fibonacci 객체(이터러블)를 순회할 때마다 next 메서드가 호출됨
for (const num of fibonacci) {
    console.log(num);   // 1 2 3 5 8
}
```

## 이터러블을 생성하는 함수 만들기

위 수열은 최대값(max)이 고정되어 있다는 점에서 아쉬움이 있다.  **수열의 최대값을 외부에서 인수로 전달받아 이터러블을 반환**하는 함수를 만들어 보자.

```jsx
// 수열의 최댓값을 인수로 전달받는다
const fibonacci = function(max) {
    let [pre, cur] = [0,1];

    // Symbol.iterator 메서드를 구현한 이터러블을 반환
    return {
        [Symbol.iterator]() {
            return {
                next() {
                    [pre, cur] = [cur, pre+cur];
                    return {
                        value : cur,
                        done : cur >=max
                    }
                }
            };
        }
    };
}

for (const num of fibonacci(30)) {
    console.log(num);   // 1 2 3 5 8 13 21
}
```

## 이터러블이면서 이터레이터인 객체

fibonacci 함수는 이터러블을 반환하는 함수이다. 이터레이터를 생성하고 싶으면 Symbol.iterator 메서드를 따로 호출해야 한다.

```jsx
// fibonacci 함수는 이터러블을 반환한다
const iterable = fibonacci(20);
// 이터레이터를 반환하게 하려면 Symbol.iterator을 호출해야 한다
const iterator = iterable[Symbol.iterator]();

// 이터러블이면서 이터레이터인 객체
// 이터러블이다 : 이터레이터를 반환하는 Symbol.iterator 메서드 소유
// 이터레이터이다 : 이터레이터 리절트 객체를 반환하는next 메서드 소유
{
    [Symbol.iterator]() { return this; },
    next() {
        return { value: Any, done: Boolean };
    }
}
```

## 이터러블이면서 이터레이터인 객체를 생성하는 함수

```jsx
// 이터러블이면서 이터레이터인 객체를 생성하여 반환하는 fibonacci 함수
const fibonacci = function(max) {
    let [pre, cur] = [0,1];

    // Symbol.iterator 메서드와 next 메서드를 소유한 이터러블이면서 이터레이터인 객체를 반환
    return {
        [Symbol.iterator]() {return this;},
        next() {
            [pre, cur] = [cur, pre+cur];
            return {value:cur, done:cur >= max};
        }
    };
};

// iter은 이터러블이면서 이터레이터인 객체이다
let iter = fibonacci(20);

for (let num of iter) {
    console.log(num);
}
```

## 무한 이터러블과 지연 평가

무한 이터러블을 생성하는 함수를 정의하여 무한 수열을 간단히 구현해 보자. 이를 통해 `지연 평가`를 표현할 수 있다.

```jsx
// 무한 이터러블을 생성하는 함수
// 무한 수열을 간단하게 구현할 수 있다
const fibonacci = function() {
    let [pre, cur] = [0,1];

    return {
        [Symbol.iterator]() {return this;},
        next() {
            [pre, cur] = [cur, pre+cur]
            // 무한이므로 done 생략
            return {value:cur};
        }
    };
}

// 지연 평가
// 데이터가 필요한 시점(for...of문 등의 데이터 소비자가 실행)에 데이터를 생성하는 기법
// 평과 결과가 필요할 때까지 평가를 늦춘다 -> 효율적
for (let num of fibonacci()) {
    if (num > 10000) break;
    console.log(num);   // 1 2 3 ... 4181 6765
}
```

> `지연 평가(lazy evalution)` : 결과값이 필요할 때까지 평가를 늦추는 기법
> 

데이터 공급자인 이터러블은 보통 모든 데이터를 **먼저 메모리에 미리 확보**한 후, 데이터를 공급한다.

그러나 `지연 평가`는 데이터가 필요한 시점(for...of문 등의 데이터 소비자가 실행될 때) 전까지 데이터를 생성하지 않다가 **필요한 시점이 되면 비로소 데이터를 생성**한다.

→ 미리 불필요한 데이터 생성X 필요한 데이터만 필요한 순간에 생성 가능 : 빠른 실행 속도, 메모리 절약, 무한 표현 가능