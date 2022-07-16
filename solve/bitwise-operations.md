# 비트 연산기

AND, OR, XOR 비트 연산을 하는 함수를 만드시오

## 예시

```jsx
bitwiseAND(7, 12) ➞ 4

bitwiseOR(7, 12) ➞ 15

bitwiseXOR(7, 12) ➞ 11
```

# 시도

## 틀린 코드

> `비트 연산자`에 대한 이해 부족
> 

```jsx
// AND
const bitwiseAND = (n1, n2) => parseInt(n1.toString(2) & n2.toSting(2),2)
// OR
const bitwiseOR = (n1, n2) => parseInt(n1.toString(2) | n2.toSting(2),2)
// XOR
const bitwiseXOR = (n1, n2) => parseInt(n1.toString(2) ^ n2.toSting(2),2)
```

n1&n2 값을 2진수로 변환(toString(2)) 후 → 다시 10진수로 변환(parseInt(num, 2)) 하는 코드이다.

자바스크립트 변수 메커니즘 특성 상(부동소수점만을 따름) 굳이 메서드를 사용해서 추가적으로 어렵게 갈 필요가 없으며, `비트 연산자` 사용만으로도 간단하게 구현이 가능하다.

# 해결

## 맞은 코드

> `비트 연산자` 사용
> 

```jsx
// AND
const bitwiseAND = (n1, n2) => n1 & n2;
// OR
const bitwiseOR = (n1, n2) => n1 | n2;
// XOR
const bitwiseXOR = (n1, n2) => n1 ^ n2;
```

# 배운 것

- 비트 연산자를 사용할 때, 진법 변환을 해줄 필요가 없다
- 진법 변환 시
    - 10진수 → 다른 진수 : toString(2)
    - 다른 진수 → 10진수 : parseInt( , 2)
    

### 문제 출처

[https://edabit.com/challenge/vvuAkYEAArrZvmp6X](https://edabit.com/challenge/vvuAkYEAArrZvmp6X)