# Math

Math는 표준 빌트인 객체로서 수학적인 상수와 함수를 위한 프로퍼티, 메서드를 제공한다. **Math는 생성자 함수가 아니다.** → 즉 정적 프로퍼티와 정적 메서드만 제공한다 (인스턴스 생성 불가능, 프로토타입 메서드 없음)

# Math 프로퍼티

## Math.PI

원주율 PI 값을 반환한다.

# Math 메서드

## Math.abs

인수로 전달된 숫자의 `절대값(absolute value)`을 반환한다. 숫자가 아니거나 undefined면 NaN(Nat A Number : 잘못된 입력)을 반환한다.

## Math.round

인수로 전달된 숫자의 소수점 이하를 `반올림`한 정수를 반환한다.

## Math.ceil

인수로 전달된 숫자의 소수점 이하를 `올림`한 정수를 반환한다.

## Matr.floor

인수로 전달된 숫자의 소수점 이하를 `내림`한 정수를 반환한다. 즉 그냥 **소수점 이하를 버리는** 것

## Math.sqrt

인수로 전달된 숫자의 `제곱근`을 반환한다.

## Math.random

0 ≤ 임의의 `난수` < 1 를 반환한다.

```jsx
Math.random();    // 0이상 1미만 랜덤 실수 반환

// 1이상 10미만 랜덤 정수 취득하기

// 1. Math.random()에 10을 곱해 0이상 10미만 랜덤 실수 반환
// 2. +1을 해 1이상 10미만 랜덤 실수 반환
// 3. Math.floor로 소수점 떼어버리고 정수 반환
const rand = Math.floor((Math.random() * 10) + 1);
console.log(rand);
```

## Math.pow

첫 번째 인수를 base(밑)로, 두 번째 인수를 exponent(지수)로 거듭제곱한 결과를 반환한다.

> pow 메서드 대신 ES7 도입 `지수 연산자`를 사용하는 것을 권장한다.
> 

```jsx
Math.pow(2,3);    // 8
2 ** 3            // 8
```

## Math.max/min

전달받은 인수 중 가장 큰 수/작은 수를 반환한다.

- 인수가 전달되지 않으면 -Infinity/infinity를 반환한다.
- 인수로 배열을 보내려면 `Funtion.prototype.apply` 메서드로 간접 호출하거나 `스프레드 문법`을 사용해야 한다