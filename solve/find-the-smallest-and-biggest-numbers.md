# 배열의 최솟값과 최댓값 찾기

숫자 배열을 인수로 받아 최소 및 최대 값을 순서대로 반환하는 함수를 만드시오

## 예시

```jsx
minMax([1, 2, 3, 4, 5]) ➞ [1, 5]

minMax([2334454, 5]) ➞ [5, 2334454]

minMax([1]) ➞ [1, 1]
```

# 시도

## 틀린 코드 1

> 변수의 `스코프` 에 대한 이해 부족
> 

```jsx
const minMax = function(arr) {
    for(let i=0;i<arr.length; i++) {
        let min = 0, max = 0;
        if (arr[i]>arr[i+1]) max=arr[i];
        if (arr[i]<arr[i+1]) min=arr[i];
    }
    return [min, max];     // ReferenceError: min is not defined
}

console.log(minMax([1,2,3,4,5]));  
```

`let` 키워드는 `블록 레벨 스코프`를 따르므로 for문 외부에서 min변수와 max변수에 접근할 수 없다.

```jsx
 const minMax = function(arr) {
    let min = 0, max = 0;
    for(i=0;i<arr.length; i++) {
        if (arr[i]<arr[i+1]) {
            max=arr[i+1];
            min=arr[i];
        }
    }
    return [min, max];
}
```

이렇게 밖으로 빼면 된다. for문 내부에서는 max와 min에 여전히 접근 가능하다.

## 틀린 코드 2

> `if문 로직`의 외류
> 

```jsx
const minMax = function(arr) {
    let min = 0, max = 0;
    for(i=0;i<arr.length; i++) {
        if (arr[i]<arr[i+1]) {
            max=arr[i+1];
            min=arr[i];
        }
    }
    return [min, max];
}

console.log(minMax([1,2,3,4,5]));   // [ 4, 5 ]
```

배열의 `i`번째 요소와 `i+1`번째 요소를 비교하는 if문 로직을 사용하므로 허점이 많다. 위 코드는 다음과 같은 과정을 거치게 된다. 

1. 1과 2를 비교 → max는 2, min는 1
2. 2와 3을 비교 → max는 3, min는 2
3. 3과 4를 비교 → max는 4, min는 3
4. 4와 5를 비교 → max는 5, min는 4

다른 로직을 고려해야 한다.

# 해결

## 맞은 코드 1

> `Math.max` 메서드와 `Math.min` 메서드 사용
> 

```jsx
const minMax = arr => [Math.min(...arr), Math.max(...arr)];
```

배열의 요소를 비교하는 로직을 짜기보다는, Math의 정적 메서드인 `Math.max()`와 `Math.min()`를 사용하여 큰 수와 작은 수를 보다 쉽게 골라내었다. 그러나 이 메서드들은 인수로 배열을 받지 못하기 때문에 `스프레드 문법`을 사용해 주었다.  

## 맞은 코드 2

> `Array.prototype.sort()`를 사용하여 오름차순 정렬을 한 후 첫 번째 요소와 마지막 요소를 추출한다.
> 

```jsx
function minMax(arr) {
    arr.sort((a, b)=>a-b);
    return [arr[0], arr[arr.length-1]];
}
```

## 맞은 코드 3

> 틀린 코드 2의 if문의 로직을 수정하였다.
> 

i번째 요소와 i+1번째 요소를 비교하는 것이 아니라, `버블 정렬`의 원리를 이용한다.

```jsx
function minMax(arr) {
    let min = max = arr[0];

    for(let i = 0; i < arr.length; i++) {
      if(arr[i] < min) min = arr[i];
      if(arr[i] > max) max = arr[i];
    }

    return [min, max];
}

console.log(minMax([1,4,6,346,88]));    // [1, 346]
```

요소를 순회하면서 max, min변수(현 최댓값과 최솟값을 저장)와 비교하는 로직을 사용하였다.