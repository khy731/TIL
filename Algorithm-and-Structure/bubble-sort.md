# 빅 오로 코드 속도 향상시키기

빅 오 표기법은 알고리즘의 효율성을 표현하는 훌룡한 도구로, 두 경쟁 알고리즘 중 더 빠른 알고리즘을 추려낼 수 있게 한다. 빅 오를 사용하여 새로운 알고리즘을 평가해 보고 효율성을 높이기 위해 알고리즘을 수정해 보자.

# bubble sort (버블 정렬)

> 정렬되지 않은 배열이 주어졌을 때, 어떻게 `오름차순으로 정렬`할 수 있는가?
> 

버블 정렬은 단순 정렬(simple sort)로, 이해하기는 쉽지만 비효율적이다.

## 버블 정렬의 단계

1. 배열 내에서 연속된 두 요소를 comparison(비교)한 후, 오름차순으로 정렬되어 있지 않으면 서로 swap(교환)한다.
2. 이를 배열의 끝까지/이미 정렬되어 있는 값까지 계속해서 반복한다

여기까지가 첫 정렬 사이클이다 : `Pass-Through(패스스루)`

패스 스루가 하나 끝날때마다 정렬되지 않은 가장 큰 값(버블)이 100% 정렬된다(올바른 위치-즉 맨 오른쪽에 위치하게 된다). 

## 버블 정렬의 구현

Python으로 구현되어 있는 책의 교재를 직접 JavaScript로 작성해 보았다. 정상적으로 잘 작동한다.

```jsx
// 교재의 파이썬 코드를 자바스크립트 코드로 재구성

// 버블 정렬 함수
function bubbleSort(arr) {
    // 아직 정렬되지 않은 요소들의 인덱스의 최대값
    let unsortedIndex = arr.length - 1;

    // 배열이 정렬될 때까지 계속 실행되는 루프
    while(true) {
        // 모든 인접 값 쌍을 비교하고 순서가 뒤바뀌어 있으면 교환
        for (i=0; i<unsortedIndex; i++) {
            if (arr[i] > arr[i+1]) {
                let box = 0;
                box = arr[i+1];
                arr[i+1] = arr[i];
                arr[i] = box;
            }
        }
        // 패스스루가 하나 끝날 때 마다 버블(제일 오른쪽)이 올바른 위치에 존재
        unsortedIndex -= 1;
        // 모든 요소가 종료되면 while문을 탈출
        if (unsortedIndex === 0) break;
    }

    // 정렬된 배열을 반환
    return arr;
}

console.log(bubbleSort([20, 42, 12, 8, 99, 1]));    // [ 1, 8, 12, 20, 42, 99 ]
```

## 버블 정렬의 효율성

버블 정렬은 두 가지 중요한 단계로 이루어져 있다.

- comparison(비교) : 어느 쪽이 더 큰지 두 수를 비교
- swap(교환) : 정렬을 위해 두 수를 교환

### 비교의 단계

각 패스 스루마다 이미 정렬된 버블을 제외한 나머지 원소를 전부 비교해야 한다.

즉 원소 N개가 있을 때, (N-1) + (N-2) + ... + 1 번의 비교를 수행하게 된다.

### 교환의 단계

*최악의 경우* 매 비교마다 원소를 전부 교환해야 할 것이다. 비교와 같은 단계가 소모된다.

> 버블 정렬은 원소 수가 증가할수록 단계 수가 기하급수적으로 늘어나며, 이를 빅 오 표기법으로 표현하면 `O(N^2)`이다.
> 

![bubble-sort](https://user-images.githubusercontent.com/97890886/167297003-47b23883-b85c-4df9-b174-1cddbec110c5.png)

# 이차 문제 해결

빅 오에서 `O(N^2)`는 상대적으로 느린 알고리즘이다. 이를 빠른 `O(N)`알고리즘으로 대체할 수 있을까?

> 예제 : 배열의 요소 중 중복 값이 존재하는지 확인
> 

## 이중 루프

```jsx
// 이차 문제 해결 : 이중 루프

function hasDuplicateValue(array) {
    for(let i=0; i<array.length; i++) {
        for(let j=0; j<array.length; j++) {
            if (i!==j && array[i]===array[j])
            return `${i+1}번째와 ${j+1}번째의 값이 ${array[i]}로 일치`;
        }
    }
    return `중복 값 존재하지 않음`;
}

console.log(hasDuplicateValue([1,2,3,4,5,6,5]));    // 5번째와 7번째의 값이 5로 일치
```

이중 루프를 사용하면 N번의 비교 * N번의 비교로 필연적으로 O(N^2)가 나온다.

## 선형 해결법

```jsx
// 이차 문제 해결 : 선형 해결법

function hasDuplicateValue2(array) {
    let existingNumbers = [];
    for(let i=0; i<array.length; i++) {
        if(existingNumbers === 1) return true;
        else existingNumbers[array[i]] = 1;
    }
    return false;
}

console.log(hasDuplicateValue2([1,2,3,4,5,6]));    // false
```

중첩 차원을 제거하고 평면적으로 해결해보자.

1. 배열을 순차적으로 비교하되, 처음 보는 값이면 그 값을 인덱스 삼아 새로운 배열 existintNumbers에 1을 할당한다.
2. 이후 중복된 값이 나오면 이미 그 인덱스로 1이 할당되어 있기 때문에 쉽체 찾을 수 있다. 

단계를 엄청나게 감소시켰다. 선형 해결법의 경우 **O(N)**으로 충분히 해결 가능하다!

(삽입의 단계 문제는 중요하지 않으므로 일단 제쳐둔다.) 메모리 낭비 문제가 좀 심각하지만 이건 나중에 자세히 살펴보기로 하고, 일단 단계 수를 줄였다는 사실에만 집중하자(...).

> 예제 : 배열의 요소 중 가장 큰 수 찾기
> 

## 선형 해결법

```jsx
// 배열에서 가장 큰 수 하나를 찾는 함수

function maxNum(arr) {
    let max = 0;
    for (let i=0; i<arr.length; i++) {
        if (max < arr[i]) max = arr[i];
    }
    return max;
}

console.log(maxNum([3,1,-2,7,18,0,2]));
```

# 마무리

빅 오 표기법을 명확히 이해하는 것은 보다 효율적인 알고리즘을 추려내는 데 도움이 된다. 그러나 빅 오 표기법에서 같은 속도여도, 실제로는 성능이 차이나는 경우가 있다. 이는 다음 시간에 알아보도록 하며 마무리짓겠다.