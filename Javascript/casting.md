> 명시적 타입 변환 vs 암묵적 타입 변환
> 

두 변환 전부, 기존 원시 값이 직접 변경된 것은 아니다. 원시 값은 변경 불가능한  값이다. 즉, `타입 캐스팅`이란 기존 원시 값을 사용해 → 다른 타입의 새로운 원시 값을 생성하는 것이다.

# 암묵적 타입 변환 implicit coercion

- 표현식을 평가하는 도중에 자바스크립트 엔진에 의해 암묵적으로 타입이 자동 변환된다.
- 기존 변수 값을 재할당하여 변경하는 것이 아니라, 표현식을 에러 없이 평가하기 위해 피연산자의 값을 암묵적 타입 변환해 새로운 타입의 값을 만들어 단 한 번 사용하고 버린다.

```jsx
var num = 10;

// 암묵적 타입 변환
// 문자열 연결 연산자(+)가 숫자 타입 num으로 새로운 문자열을 생성
var str = num + ' ten';

console.log(typeof str, str);   // string 10 ten

// 변수의 원본이 변경된 것은 아니다
console.log(typeof num, num);   // number 10
```

## → 문자열

문자 연결 연산자(+)의 사용에 따른 변환이다.

```jsx
1 + '3';    // "13"
`2 + 5 = ${2+5}`    // "2 + 5 = 7"
```

## → 숫자

산술 연살자의 사용에 따른 변환이다.

```jsx
2 * '3';    // 6
1 / 'one';    // NaN ㅋㅋㅋ아니 이건 컴퓨터를 사람으로 아는 수준인뎈ㅋㅋㅋ
'4' > 0    // true
```

## → 불리언

자바스크립트 엔진은 불리언 타입이 아닌 값을 다음과 같이 구분한다.

> Truthly (참으로 평가되는 값)
> 

Falsy 값을 제외한 모든 값

> Falsy (거짓으로 평가되는 값)
> 

0, -0, NaN, null, undifined, false, ‘ ‘(빈 문자열), false

```jsx
if (' ') console.log('1');
if (0) console.log('2');
if (null) console.log('3');
if ('str') console.log('4');

// 4
```

불리언(ToF)값이 필요한 문맥(제어문의 조건식 등)에서 다른 데이터 타입이 있을 경우, 진짜 true와 false로 암묵적 타입 변환한다.

# 명시적 타입 변환 explicit coercion

- 개발자의 의도에 따라 값의 타입을 변환하고, 이가 코드에 명백하게 드러난다.
- 타입 캐스팅 type casting 이라고도 부른다.

```jsx
var num = 10;

// 명시적 타입 변환
// 숫자->문자 type casting
var str = num.toString();

console.log(typeof str, str);   // string 10

// 변수의 원본이 변경된 것은 아니다
console.log(typeof num, num);   // number 10
```

다양한 방법이 있다.

1. 표준 빌트인 built-in 생성자 함수(String, Number, Boolean)를 new 연산자 없이 호출
2. 빌트인 메서드 호출
3. 암묵적 타입 변환을 의도적으로 이용

## → 문자열

```jsx
// 1. String 생성자 함수를 new 연산자 없이 호출
String(1);      // "1"
String(false);  // "false"

// 2. Object.prototype.toString 메서드 사용
(1).toString();     // "1"
(false).toString(); // "false"

// 3. 문자열 연결 연산자를 이용하여 고의로 암묵적 변환
1 + '';     // "1"
false + ''; // "false"
```

## → 숫자

```jsx
// 1. Number 생성자 함수를 new 연산자 없이 호출
Number('0');    // 0
Number('true'); // 1

// 2. parseInt, parseFloat 함수 사용
// 문자열 -> 숫자 일때만 사용 가능
parseInt('-1');         // -1
parseFloat('39.25');    // 39.25

// 3. 단항 산술 연산자를 이용하여 고의로 암묵적 변환
+'0';   // 0
+true;  // 1

// 4. * 산술 연산자를 이용하여 고의로 암묵적 변환
'3' * 1;    // 3
true * 1    // 1
```

## → 불리언

```jsx
// 1. Boolean 생성자 함수를 new 연산자 없이 호출
Boolean('');        // false
Boolean(0);         // false
Boolean(NaN);       // false
Boolean(undefined); //false
Boolean(Infinity);  // true
Boolean(null);      // true
Boolean(1);         // true
Boolean({});        // true

// 2. !(NOT) 연산자를 두 번 사용하여 고의로 암묵적 변환
!!'';     // true
!!NaN;      // false

// Truthly를 두 번 뒤집음으로써 Truthly->false->truth
// Falsy를 두 번 뒤집음으로써 Falsy->true->false
// 로 만들어 주는 원리
```

# 단축 평가

논리합(&&) 또는 논리곱(||) 표현식의 평가 결과가 불리언 값이 아닌 경우, 즉 ToF가 아니라 Truthly 값과 Falsy 값이 피연산자로 사용되어 모호한 연산이 될 경우 이를 이용하여 단축 평가를 할 수 있다.

표현식을 평가하는 도중 결과가 확정되면 더 이상 평가 계산을 하지 않고 나머지 과정을 생략하는 원리를 사용한다. 즉, 논리 연산의 결과를 결정하는 피연산자를 타입 변환하지 않고 그대로 반환한다. 이를 `단축 평가 short-circuit evaluation` 라고 한다.

## AND (&&)

AND(&&)는 `두 번째 피연산자`가 결과 값을 결정한다. (둘 다 true여야 true)

```jsx
'Cat' && 'Dog';    // 표현식의 평가 결과가 불리언(ToF)이 아니다.
                   // 두 피연산자 전부 모호한(Truthly) 값이지만 true로 평가된다.
// "Dog" 가 결과이다.

0 || 'Me';
// false 가 결과이다.
```

- T && X : X
- F && X : F

첫 번째 피연산자가 T이면 두 번째 피연산자가 값이고, 첫 번째 피연산자가 F이면 F가 값이다.

<aside>
❕ *어 첫번째꺼가 T네? 그러면 두번째꺼가 결정할테니까 두번째꺼가 나와야지*

*어 첫번째꺼가 F네? 그러면 두번째꺼 봐봤자 뭐해 어차피 F지.*

</aside>

## OR (||)

OR(||)는 `첫 번째 피연산자`가 결과 값을 결정한다. (둘 중 하나만 true여도 true)

```jsx
'Cat' || 'Dog';    // 표현식의 평가 결과가 불리언(ToF)이 아니다.
                   // 두 피연산자 전부 모호한(Truthly) 값이지만 true로 평가된다.
// "Cat" 이 결과이다.

null || 'Me'
// 'Me' 가 결과이다.
```

- T || X : T
- F || X : X

<aside>
❕ *어 첫번째꺼가 F네? 그러면 두번째꺼가 결정할테니까 두번째꺼가 나와야지.*

*어 첫번째꺼가 T네? 그러면 두번째꺼 봐봤자 뭐해 어차피 T지.*

</aside>

> 단축 평가를 이용하여 if문 대체하기
> 

```jsx
// 1. AND (&&)

// if문 사용
var done = true;
var message = '완료';

if (done) console.log(message);

// 논리 연산자 &&로 단축 표현 사용
// 첫 번째 피연산자가 Truthly(true) 이므로 두 번째 피연산자 '완료'가 할당됨
message = done && '완료';
console.log(message);

// 2. OR (||)

// if문 사용
var done = false;
var message = '완료';

if (!done) console.log(message);

// 논리 연산자 ||로 단축 표현 사용
// 첫 번째 피연산자가 Falsy(false) 이므로 두 번째 피연산자 '완료'가 할당됨
message = done || '완료';
console.log(message);
```

## 단축 평가의 유용성

어느 이분법적인 경우에서 두 경우(그리고 그것이 불리언 값이 아닐 때)를 전부 고려하지 않으면 에러가 생길 때, 논리 연산자를 사용하여 단축 평가를 하면 두 경우를 전부 고려할 수 있어 편리하다.

> 1. 객체를 가리킬 변수가 null/undefined가 아닌지 확인하고 프로퍼티를 참조할 때
> 

객체를 가리키기를 기대하는 변수의 값이 객체가 아니라 null 또는 undefined일 경우, 이 객체의 프로퍼티는 참조할 수 없게 된다(타입 에러 발생).

<aside>
🚫 TypeError: Cannot read properties of null (reading 'value')

</aside>

단축 평가를 사용하면 에러가 발생하지 않는다.

```jsx
var elem = null;
var value = elem.value;

console.log(elem.value);

// elem이 Falsy 값이면 : elem(==false)으로 평가됨
// elem이 Truthly 값이면 : elem.value로 평가됨
var value = elem && elem.value
```

> 함수 매개변수에 기본값을 설정할 때
> 

함수를 호출할 때 argument(인수)를 전달하지 않으면, parameter(매개변수)에는 undefined가 할당된다. 이 때 단축 평가를 이용해 매개변수의 기본값을 설정하면 undefined로 인해 발생할 수 있는 에러를 방지할 수 있다.

```jsx
// 단축 평가 이용
function getStringLength(str) {
    str = str || '';    // str(parameter)에 argument가 전달되지 않으면
                        // str에는 undefined(false)가 자동 할당된다  
    return str.lentgh;  // str가 false여도 에러가 나지 않고 ''의 길이가 반환된다
}

// ES6의 기능
function getStringLength(str='') {
    return str.length;
}

// 결과
getStringLength();      // 0
getStringLength('Hi')   // 2
```

# 옵셔널 체이닝 연산자 [ ?. ]

ES11에서 도입되었다. 객체의 프로퍼티를 참조할 때 유용하다.

- 좌항의 피연산자가 undefined나 null인 경우 → undefined 반환
- 그렇지 않으면 →우항의 프로퍼티 참조를 이어감.

```jsx
var elem = null;

var value = elem?.value;
console.log(value);     // undifinde
```

### 단축 표현의 한계와 옵셔널 체이닝 연산자

```jsx
// 1. 단축 평가의 한계

var str = '';   // Falsly(false)

// 문자열 길이(length) 참조하기
var length = str && str.length;
console.log(length);    // str은 빈 문자열이다. 0을 반환하는 것이 가장 이상적이겠지만
                        // 안타깝게도 단축 평가는 그런거 모른다. ' '는 falsy니까.
                        // 그런데 더 안타깝게도 str이 객체로 평가되어버려 F 대신 그냥 ' '이 튀어나와 버린다.
                        // result : ' '

// 2. 옵셔널 체이닝 연산자                        

var str = '';

var length = str?.length;
console.log(length);    // 좌항이 null이나 undefined만 아니라면
                        // 우항의 프로퍼티 참조를 킵고잉한다.
                        // result : 0
```

# null 병합 연산자 [ ?? ]

ES11에서 도입되었다. 변수에 기본값을 설정할 때 유용하다.

- 좌항의 피연산자가 undefined나 null인 경우 → 우항의 피연산자 반환(하여 초깃값 할당)
- 그렇지 않으면(이미 유효한 초깃값이 있는 상태면) → 좌항의 피연산자 반환

```jsx
var foo = null ?? 'default';
console.log(foo);   // 'default'
```

### 단축 표현의 한계와 null 병합 연산자

```jsx
// foo의 기본값이 없을 경우 'default' 할당하기
// 그러나 이미 ''라는 기본값이 있는 상황

// 1. 단축 표현 : ''를 기본값으로 인식하지 못하고 F로 평가하여 재할당 해버림
var foo = '' || 'default';
console.log(foo);   // 'default'

// 2. null 병합 연산자 : 좌항의 피연산자가 F로 평가되는 falsy 값이더라도
// null 또는 undefined가 아니라면 좌항의 피연산자 그대로 반환
var foo = '' ?? 'default';
console.log(foo);   // ' '
```