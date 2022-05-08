Number은 standard built-in object로, 원시 타입 중 숫자를 다룰 때 유용한 프로퍼티와 메서드를 제공한다. 이렇게 원시 타입의 값과 연결된 표준 빌트인 객체(생성자 함수 객체)는 래퍼 객체(원시 값을 암묵적으로 객체처럼 다룰 수 있게 함)를 생성한다.

# Number 생성자 함수

Number 객체는 `생성자 함수` 객체이므로 new연산자와 함께 호출하여 Number 인스턴스를 생성할 수 있다. 호출 시 [[NumberData]] 내부 슬롯에 Number 래퍼 객체가 생성된다.

```jsx
// 인수를 전달하지 않으면 [[NumberData]]에 0이 할당된 Number 래퍼 객체 생성
const numObj = new Number();
console.log(numObj);    // Number {0}

// 인수를 전달하면 [[NumberData]]에 값이 할당된 Number 래퍼 객체 생성
const numObj2 = new Number(10);
console.log(numObj2);   // Number {10}

// Number 생성자 함수의 인수로 숫자가 아닌 값 전달 시
// 숫자로 강제 casting 후 래퍼 객체 생성
const numObj3 = new Number(`10`);
console.log(numObj3);   // Number {10}
```

new 연산자와 함께 호출하지 않을 경우 명시적 casting에 활용할 수 있다.

```jsx
// new와 함께 사용하지 않을 시 인스턴스(래퍼 객체)가 아닌 숫자를 반환한다
// 이를 활용하여 명시적 타입 변환이 가능
const myNum = Number(`13023`);
console.log(myNum);    // 13023
```

# Number의 프로퍼티

## Number.EPSILON

> 부동소수점으로 인해 발생하는 오차를 해결한다
> 

Number.EPSILON은 1과 1보다 큰 숫자 중에서 가장 작은 숫자의 차이와 같은 값이다. 즉 부동소수점 범위 내에서 극도로 작은 수이다.

![EPSILON](https://user-images.githubusercontent.com/97890886/167278621-1a94c6a9-73de-4a69-aa7f-bc32255ae6dc.png)

0.1과 0.2를 더하면 0.3이 나와야 하는데 IEEE-754의 숙명(...)대로 괴랄한 숫자가 나와버린다. 이 필연적인 미세한 오차를 커버하기 위해 “EPSILON보다 작은 오차값이면 그냥 똑같은 거로 쳐” 라고 하는 거다.

```jsx
// 부동소수점의 산술 연산
// IEEE-754는 이진법으로 변환 시 무한소수가 되어 필연적으로 미세한 오차가 발생한다

console.log(0.1+0.2);   // 0.30000000000000004
console.log(0.1+0.2 === 0.3)    // false

// Number.EPSILON로 부동소수점 오차 완화
// 두 숫자 사이의 오차가 아주 미세하면(EPSIKON보다 작으면) 그냥 같은 거로 친다
function isEqual(x,y) {
    return Math.abs(x-y) < Number.EPSILON;
}
console.log(isEqual(0.1+0.2, 0.3));    // true
```

## Number.MAX_VALUE

JS에서 표현 가능한 값 중 `가장 큰 양수 값`이다. (약 1.79769... * 10^308) **이보다 큰 숫자는 Infinity뿐이다.**

## Number.MIN_VALUE

JS에서 표현 가능한 값 중 `가장 작은 양수 값`이다. (약 5 * 10^-324) **이보다 작은 숫자는 0뿐이다.**

## Number.MAX_SAFE_INTEGER

JS에서 안전하게 표현할 수 있는\가장 큰 정수값이다. 9007199254740991

## Number.MIN_SAFE_INTEGER

JS에서 안전하게 표현할 수 있는 가장 작은 정수값이다. -9007199254740991

## Number.POSITIVE_INFINITY

=== Infinity

## Number.NEGATIVE_INFINITY

=== -iInfinity

## Number.NaN

=== NaN

# Number 메서드

## Number.isFinite

> 인수로 전달된 숫자값이 정상적인 유한수(≠infinity ≠-infinity)인지를 검사하여 불리언 값을 반환
> 

인수가 NaN이면 언제나 False이다.

빌트인 전역 함수 isFinite와의 차이점

- isFinite는 인수를 숫자로 암묵적 타입 변환하여 검사를 수행
- Number.isFinite는 암묵적 타입 변환X : 숫자가 아닌 인수가 주어지면 반환값이 false

## Number.isInteger

> 인수로 전달된 숫자값이 정수인지 검사 후 불리언 값 반환
> 

## Number.isNaN

> 인수로 전달된 숫자값이 NaN인지 검사하여 불리언 값 반환
> 

빌트인 전역 함수 isNaN과 위와 같은 차이가 있다.

## Number.isSafeInteger

> 인수로 전달된 숫자값이 안전한 정수인지 검사 후 불리언 값 반환
> 

역시 숫자를 암묵적 타입 변환 X

## Number.prototype.toExponential

> 숫자를 지수 표기법으로 변환하여 문자열로 반환
> 

인수로 자릿수를 전달할 수 있다. 단 숫자 리터럴과 함께 호출 시 에러가 발생한다. 숫자 리터럴 뒤에 .은 의미가 모호(부동소수점 숫자의 소수 구분 기호, 객체 프로퍼티에 접근하기 위한 접근 연산자 등...)하기 때문이다.

## Number.prototype.toFixed

> 숫자를 반올림하여 문자열로 반환
> 

인수로 반올림하는 소수점 이하 자릿수를 0~20사이 정수값으로 전달할 수 있다. (기본값: 0

## Number.prototype.toPrecision

> 인수로 전달받은 전체 자릿수까지 유효하고 나머지 자릿수를 반올림하여 문자열로 반환
> 

## Number.prototype.toString

> 숫자를 문자열로 변환하여 반환
> 

진법을 나타내는 정수값을 인수로 전달 가능. 인수 생략 시 10진법으로 지정