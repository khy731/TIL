# 참은 몇 개인가?

배열에 있는 참 값의 수를 반환하는 함수를 만드시오.

## 예시

```jsx
countTrue([true, false, false, true, false]) ➞ 2

countTrue([false, false, false, false]) ➞ 0

countTrue([]) ➞ 0
```

# 시도

## 해결 코드 1

> `for문`
> 

```jsx
const countTrue = function(arr) {
    let count = 0;
    for (let i=0; i<arr.length; i++) if (arr[i]===true) count++;
    return count;
}
```

배열의 요소를 순회하며 요소가 true이면 count를 증가시키는 간단한 for문을 사용하였다.

## 해결 코드 2

> 배열 고차 함수 `filter`과 `length` 프로퍼티
> 

```jsx
const countTrue = arr => arr.filter(v=>v===true).length;
```

배열 고차 함수를 사용하였다. true인 요소만 반환되어 만들어진 새로운 배열의 length 프로퍼티로 참의 개수를 반환하게끔 하였다.

## 해결 코드3

> `filter(boolean)`
> 

```jsx
const countTrue = arr => arr.filter(boolean).length;
```

filter(boolean) 트릭을 사용하여 가장 간단하게 표기할 수 있다.

# 배운 것

## filter(boolean)

```jsx
array.filter(Boolean)

// 위 코드와 동일하게 동작한다
// 가독성 있는 코드 vs 화려하고 간단한 트릭 中 원하는 것을 사용해라!
array.filter(item => Boolean(item));
```

filter(boolean)은 다음과 같이 동작한다 :

1. 배열의 각 요소를 Boolean() 빌트인 전역 객체로 전달한다
2. Boolean() 객체는 요소를 불리언 값(ToF)로 coerces(강제 변환)한다
3. 참인 값만 keep한다

자바스크립트의 배열은 일반적인 배열과는 달리, 배열처럼 동작하는 객체로, 희소 배열을 허용하기 때문에 배열 내 undefined나 null값이 숨어있다면 배열의 모든 요소에 대해 작업을 수행하려고 할 때 오류가 발생하게 된다. 이 때 filter(Boolean) 트릭을 사용하면 간단하게 배열에서 희소 항목을 빠르게 제거할 수 있다.