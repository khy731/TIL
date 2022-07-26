# 입력받은 정수까지의 합 구하기

1부터 입력받은 정수까지의 합을 구하는 함수를 작성하시오.

## 예시

```jsx
addUp(4) ➞ 10

addUp(13) ➞ 91

addUp(600) ➞ 180300
```

# 시도

## 틀린 코드

```jsx
const addUp = num => num.reduce((pre,cur) => pre+cur);
```

인수를 배열로 착각해버렸...

# 해결

## 맞은 코드 1

```jsx
function addUp(num) {
  let sum = 0;
  for (let i = 1; i <= num; i++) {
    sum += i;
  }
  return sum;
}
```

`for문`을 활용한 가장 간단한 해법

## 맞은 코드 2

```jsx
const addUp = num => n * ++n / 2;
```

유명한 `가우스의 덧셈`알고리즘 : 1부터 n까지의 합 === (n + (n+1)) / 2 임을 이용하였다.

## 맞은 코드3

```jsx
const addUp = num => (!num) ? 0 : num + addUp(num-1);
```

`재귀 함수`를 사용하였다.

- 인수로 들어온 숫자가 0이면(false) 0을 반환
- 0이 아니면(true) 1을 뺀 값을 인수로 넘기면서 자기 자신을 호출

결론적으로 num + (num-1) + (num-2) ... + 0 과 같은 로직이 된다.