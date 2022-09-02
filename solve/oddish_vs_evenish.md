# 홀수 VS 짝수

인수로 받은 숫자를 각각 합하여 홀수일 경우 `Oddish`를 반환하고, 짝수일 경우 `Evenish`를 반환하는 함수를 만드시오.

## 예시

```jsx
oddishOrEvenish(43) ➞ "Oddish"
// 4 + 3 = 7
// 7은 홀수이다

oddishOrEvenish(373) ➞ "Oddish"
// 3 + 7 + 3 = 13
// 13은 홀수이다

oddishOrEvenish(4433) ➞ "Evenish"
// 4 + 4 + 3 + 3 = 14
// 14은 짝수이다
```

# 시도

## 틀린 코드 1

> 숫자 → 문자열 → 배열로 변환 후 `Array.prototype.reduce` 사용
> 
1. 인수로 받은 숫자를 `toString()`으로 문자열로 형변환 한 후 `split()`으로 한 글자씩 분리시킨다
2. 스프레드 문법을 사용하여 각 요소를 배열로 변환한다
3. `Array.prototype.reduce`를 사용해 배열의 각 요소를 더한 값을 뽑아낸다
4. %2와 삼항 연산자로 홀수와 짝수를 구분한다

```jsx
const oddishOrEvenish = v => [...(toString(v).split(``))].reduce((acc,cur)=>acc+cur) % 2 ? `Oddish` : `Evenish`
```

그러나 예상치 못한 오류가 계속해서 발생했다. (홀수인데 Evenish를 반환하는 등)

### 틀린 이유

> 자바스크립트의 `암묵적 타입 변환`에 의한 오류
> 

위 코드에 따르면 43이라는 숫자는 문자열로 변환되어 “43”이 되고, split()을 통해 “4”, “3”이 된다. 결론적으로 이를 스프레드 문법을 통해 배열로 변환하면 [”4”, “3”]이 된다. 이를 reduce를 통해 합을 구하면 **숫자가 아닌 문자열의 연산**으로 간주되어 7이 아닌 `43`이 나오게 된다.

만약 이 함수에 13과 같은 숫자를 인수로 전달하게 될 경우 원하는 값(1+3=4, 짝수)이 아닌 오류가 뜨는 것이다(”1”+”3”=”13”, 홀수).

> `toString()` 메서드 사용 오류
> 

toString() 메서드를 사용하는 방식이 잘못되었다. 인수로 변환하고자 하는 숫자를 보내는 것이 아니라 진법을 보내야 하며, 변환하고자 하는 숫자가 담긴 객체를 참조함으로써 작동된다.

## 해결 코드 1

> `String()`과 `map(Number)` 을 사용
> 

toString과 split 대신 String()과 map(Number)을 사용하면

```jsx
[...String(2555)];    // [ '2', '5', '5', '5' ]
[...String(2555)].map(Number);    // [ 2, 5, 5, 5 ]
```

정확하고 간단하게 숫자를 분리하여 배열에 담을 수 있다.

```jsx
const oddishOrEvenish = v => [...String(v)].map(Number).reduce((a,c)=>a+c, 0) % 2 ? `Oddish` : `Evenish`
```

## 해결 코드 2

%10을 하면 마지막 자릿수가 뽑아지고, /10을 하면 자릿수가 하나 줄어드는 로직을 사용한다.

단, 자바스크립트의 숫자는 항상 부동소수점 표기법을 따르므로 `Math.floor()`을 추가로 사용하여 소수점 아래를 제거해줘야 한다.

```jsx
function oddishOrEvenish(num) {
let sum = 0;

while (num) {
    sum += num % 10;
    num = Math.floor(num / 10);
}
	if(sum % 2 == 0) return 'Evenish';
	else return 'Oddish';
}
```