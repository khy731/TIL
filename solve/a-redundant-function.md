# 중복 기능

인수로 전달받은 문자열을 반환하는 함수를 반환하는 함수를 만드시오.(함수의 반환은 문자열이 아닌 함수여야 한다.)

## 예시

```jsx
const f1 = redundant("apple")
f1() ➞ "apple"

const f2 = redundant("pear")
f2() ➞ "pear"

const f3 = redundant("")
f3() ➞ ""
```

# 시도

## 맞은 코드 1

```jsx
const redundant = function(str) {
    return function() {
        return str;
    }
};
```

반환하는 함수는 일종의 콜백 함수로, 호출됨으로써 가치를 다 하는 일반적인 함수와는 달리 인수로 넘겨지거나 반환값으로 사용된다. `매개변수`를 지정하지 않았다. **매개변수를 지정하면 undefined가 나온다.** 

## 맞은 코드 2

```jsx
const redundant = str => () => str;
```

보다 간단하게 화살표 함수로 표현하였다.

# 배운 것

```jsx
const redundant = str => str => str;
```

> 이 예제는 왜 undefined가 나올까?
> 

매개변수는 말 그대로 “매개체 역할을 하는 변수”이며, 함수마다 별개의 스코프를 가지므로 이름이 같다고 해서 연결되는 것이 아니다. 외부 함수의 매개변수 str 와 내부 함수의 매개변수 str은 이름이 같을 뿐 다른 변수이므로 외부 함수가 인수로 받은 문자열은 내부 함수의 매개변수로 들어가지 않는다. 이를 해결하기 위해서는 캐리어 역할을 하는 변수를 하나 더 선언하여 연결할 수도 있지만 이는 변수의 개수를 늘리고 번거롭기 때문에 매개변수를 비워 놓는 것이 가장 현명하다.