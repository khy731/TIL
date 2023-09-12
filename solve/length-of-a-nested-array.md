# 중첩 배열의 실질적인 요소의 개수 전부 세기

배열의 `length` 프로퍼티는 배열의 요소 수를 반환한다. 예를 들어, 아래 배열의 경우 2를 반환한다.

```
[1, [2, 3]]
// 2 elements, number 1 and array [2, 3]
```

중첩 배열에서 중첩되지 않은 총 요소 수를 반환하는 함수를 작성해보자. 예를 들어, 위 예제 [1, [2, 3]의 경우 3개의 요소 1, 2, 3이 존재하므로 length 프로퍼티 값은 3이다.

단, 빈 배열은 0을 반환해야 한다.

## 예시

```
getLength([1, [2, 3]]) ➞ 3

getLength([1, [2, [3, 4]]]) ➞ 4

getLength([1, [2, [3, [4, [5, 6]]]]]) ➞ 6

getLength([1, [2], 1, [2], 1]) ➞ 5
```

# 문제 풀이

## 시도 1

> `Array.prototype.flat` 메서드 사용
> 

```jsx
function getLength(arr) {
	return arr.flat().length;
}
```

Array.prototype.flat 메서드는 배열을 `평탄화`하는데, 이 때 인수로 전달한 깊이만큼 `재귀적`으로 평탄화한다는 사실을 간과하여 n중 중첩 배열이 포함되어 있을 경우 원하는 결과를 얻지 못했다.

## 시도 2 *(complete!)*

> 인수(평탄화의 깊이)로 `Number.MAX_SAFE_INTEGER`를 전달
> 

평탄화의 **깊이**를 어떻게 설정해야 하는 것일까? JS에서 표현 가능한 가장 큰 안전한 수인 `Number.MAX_SAFE_INTEGER`를 전달해 보았다.

```jsx
const getLength = arr => arr.flat(Number.MAX_SAFE_INTEGER).length;
```

중첩 배열 내 어떤 깊이만큼의 중첩 배열이 또 존재하더라도 완벽하게 평탄화가 되어 원하는 결과를 얻을 수 있었다.

# 타인의 코드를 보며 배우기

## 다른 해결법 1

```jsx
const getLength = arr => arr.flat(Infinity).length;
```

`Number.MAX_SAFE_INTEGER` 대신 `Infinity`를 사용하였다.

## 다른 해결법 2

```jsx
function getLength(arr) {
	let count = 0;
	arr.forEach(item => {
		if (Array.isArray(item)) {
			count += getLength(item);
		} else {
			count++;
		}
	});
	return count;
}
```

인수로 전달받은 배열의 요소를 forEach 메서드를 통해 하나씩 순회하면서, **요소가 배열인 경우(===중첩된 배열) 재귀 구조를 거치게 하고, 요소가 배열이 아닐 시(평탄화가 완료됨)에만 카운트를 증가시켜** 결과적으로 중첩 배열에서 중첩되지 않은 총 요소 수를 얻었다.

# 배운 것

## Array.prototype.flat 메서드를 사용하여 배열 평탄화하기

`Array.prototype.flat 메서드`는 ES10 도입으로, **인수로 전달한 깊이만큼** `재귀적`으로 배열을 `평탄화`한다.