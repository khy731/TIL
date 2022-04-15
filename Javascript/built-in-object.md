# 자바스크립트 객체의 분류

- 표준 빌트인 객체

ECMAScript 사양에 정의되어 실행 환경(브라우저 or Node.js)에 상관없이 사용 가능한 객체. 전역 객체의 프로퍼티 취급을 받으며(별도의 선언 없이 전역 변수처럼 언제나 참조 가능), 애플리케이션 전역의 공통 기능을 제공한다.

- 호스트 객체

ECMAScript 사양에 정의되어 있지 않지만 실행 환경에서 추가로 제공하는 객체. 브라우저는 클라이언트 사이드 Web API를, Node.js에서는 고유의 API를 제공

- 사용자 정의 객체

위 두 객체처럼 기본 제공되는 것이 아닌, 사용자가 직접 정의한 객체.

# 표준 빌트인 객체

> 자바스크립트는 다음과 같은 약 40여개의 표준 빌트인 객체를 제공한다 :
> 
- Object
- String
- Number
- Array
- Map/Set

...

Math, Reflect, JSON을 제외한 표준 빌트인 객체는 모두 인스턴스를 생성할 수 있는 `생성자 함수` 객체다. 즉, 이들은 `프로토타입 메서드`와 `정적 메서드`를 제공한다. (생성자 함수가 아닌 경우 정적 메서드만을 제공함)

생성자 함수인 표준 빌트인 객체가 생성한 인스턴스의 프로토타입은 표준 빌트인 객체의 prototype 프로퍼티에 바인딩된 객체이다.  예를 들어, 표준 빌트인 객체 String을 생성자 함수로써 호출하여 생성한 String 인스턴스의 프로토타입은 String.prototype이다.

```jsx
const str = String(`Hi`);

console.log(Object.getPrototypeOf(str) === String.prototype);   // true
```

표준 빌트인 객체는

- 다양한 기능의 빌트인 `프로토타입 메서드`를 제공 (상속받아 사용)
- 인스턴스 없이도 호출 가능한 빌트인 `정적 메서드` 제공 (인스턴스 없이도 그냥 사용)

```jsx
// 프로토타입 메서드 : 인스턴스를 생성하여 프로토타입 객체로부터 상속받아 사용
const num = Number(1.7);
console.log(num.toFixed());

// 정적 메서드 : 인스턴스 생성할 필요 없이 바로 사용
console.log(Number.isInteger(1.7));
```

# 원시 값과 래퍼 객체

대응하는 원시 값이 이미 있는데 왜 굳이 문자열 대신 String, 숫자 대신 Number 을 쓰는 걸까?

원시 값을 객체처럼 사용할 때, 자바스크립트 엔진이 일시적으로 암묵적으로 원시값을 연관된 객체를 생성하여, 생성된 객체로 프로퍼티로 접근하거나 메서드를 호출하고 다시 원시값으로 되돌린다. 그리고 이 때 생성된 임시 객체는 프로토타입 메서드를 상속받아 사용할 수 있다.

```jsx
const str = `hello`;

console.log(str.length);    // 5
console.log(str.toUpperCase());     // HELLO

// 바로 다시 원시값으로 돌아간다
console.log(typeof str);    // string
```

이를 좀 더 자세하게 설명하면 다음과 같다.

```jsx
// 원시 값을 가리키는 식별자 str
const str = `me`;

// 식별자 str은 암묵적으로 생성된 래퍼 객체를 가리킨다
// 이 때 str의 값은 래퍼 객체의 내부 슬롯 [[StringData]] 에 할당된다
str.name = `kang`;

// 식별자 str은 이제 다시 원시값(객체의 내부 슬롯 [[StringData]]의 값)을 가리킨다
// 래퍼 객체는 아무도 참조하지 않으므로 가비지 컬렉션의 대상이 된다

// 식별자 str은 "새롭게"생성된 래퍼 객체를 가리킨다
// 위의 래퍼 객체와는 다른 객체이므로, name 프로퍼티의 값이 존재하지 않기 때문에 undefined
console.log(str.name);      // undefined

// 식별자 str은 이제 다시 원시값(객체의 내부 슬롯 [[StringData]]의 값)을 가리킨다
// 래퍼 객체는 아무도 참조하지 않으므로 가비지 컬렉션의 대상이 된다

console.log(typeof str, str);   // string me
```

문자나 불리언도 각각 Number, Boolean으로 동일하게 동작한다.

`문자열`, `숫자`, `ToF`, `심벌` 값은 암묵적으로 생성되는 `래퍼 객체`에 의해 마치 객체처럼 사용할 수 있고 프로토타입을 참조할 수도 있기 때문에 생성자 함수로 new 연산자를 사용하여 인스턴스를 생성할 필요가 없다. 이 외의 원시값(null, undefined)는 래퍼 객체를 생성하지 않으므로 얘네는 예외다.

# 전역 객체

코드가 실행되기 이전 단계에, 자바스크립트 엔진에 의해 어떤 객체보다도 먼저 생성되는 특수 객체이자 어떤 객체에도 속하지 않는 `최상위 객체`.

> 자바스크립트 환경에 따라 달라진다.
> 
- 브라우저 : window
- Node.js : global

ES11에서는 이 둘을 모두 아우르는 globalThis 를 도입하였다.

> 특징
> 
- 표준 빌트인 객체, 호스트 객체, 암묵적 전역, var 키워드로 선언(let, const는 다른 곳에 존재하므로 포함되지 않는다)한 전역 변수와 전역 함수를 프로퍼티로 갖음 → 계층적 구조상 어떤 객체에도 속하지 않은 최상위 객체

여기서 주의해야 할 점은, 앞에서 보았던 프로토타입 체인의 최상위라는 것이 아닌 객체 자체의 ‘계층적 구조’상의 최상위의 의미이다. 배경 같은 느낌이랄까...

- 개발자가 의도적으로 생성 불가 (애초에 전역 객체를 생성할 수 있는 생성자 함수 X)
- 프로퍼티를 참조할 때 window나 global 생략 가능
- 브라우저 환경의 모든 자바스크립트 코드는 단 하나의 전역 객체(window)를 공유하므로, script 태그를 여러개 사용하여 코드를 분리해도 하나의 전역만을 공유한다.

## 빌트인 전역 프로퍼티

> infinity
> 

무한대를 나타내는 숫자값 infinity를 갖는 프로퍼티

> NaN
> 

숫자가 아님(Not-a-Number)을 나타내는 숫자값 NaN을 갖는 프로퍼티.

> undefined
> 

원시 타입 undifened를 값으로 갖는 프로퍼티

## 빌트인 전역 함수

> eval
> 

주어진 자바스크립트 문자열 코드를 arguments로 전달받는다.

- 표현식이라면 → 런타임에 평가하여 값 생성
- 표현식이 아닌 문이라면 → 런타임에 단순 실행

```jsx
// 표현식 O
console.log(eval('1 + 2;'));        // 3
// 표현식 X
console.log(eval('var x = 5;'));    // undefined

// eval 함수에 의해 런타임에 변수 선언문이 실행되어 x 변수가 선언됨
console.log(x);     // 5

// 객체 리터럴은 괄호로
const y = eval('({a : 1})');  
console.log(y);     // { a: 1 }

// 함수 리터럴도 괄호로
const f = eval(`(function() {return 1;})`);
console.log(f());   // 1
```

eval 함수는 자신이 호출된 위치의 기존 스코프를 런타임에 동적으로 수정한다. 

eval 함수로 사용자 입력 컨텐츠를 처리하는 것은 `보안`에 매우 취약하며,  eval 함수를 통해 실행되는 코드는 자바스크립트 엔진에 의해 최적화되지도 않는다.

<aside>
❕ eval 함수는 사용하지 않는 것이 좋다.

</aside>

> isfinite
> 

전달받는 인수가 정상적인 `유한수`인지 검사하여 boolean값을 반환한다.

arguments의 타입이 숫자가 아닌 경우 숫자 타입으로 암묵적 변환 후 반환한다. arguments가 NaN인 경우 false를 반환한다. null은 true이다.

> isNaN
> 

전달받은 인수가 NaN인지 검사하여 boolean값을 반환

> parseFloat
> 

전달받은 문자열 인수 → 부동소수점 숫자(실수)로 반환

> parseInt
> 

전달받은 문자열 인수 → 정수  반환

- 두 번째 인수로 기수(진법)를 전달 가능
- 진수 변환까지 하고 싶으면 Number.prototype.toSting 메서드 사용 : 당연하지만 컴퓨터는 16진수 리터럴만 해석할 수 있음에 주의.

```jsx
// '12'를 n진수로 해석 -> 10진수 형태로 반환
console.log(parseInt(`12`, 2));     // 1
console.log(parseInt(`12`, 8));     // 10
console.log(parseInt(`12`, 16));    // 18

const x = 12;
// 12를 n진수로 변환 -> 문자열로 반환
console.log(x.toString(2));     // 1100
console.log(x.toString(8));     // 14
console.log(x.toString(16));    // C

// 기수를 지정하지 않더라도 16진법 리터럴(만)은 잘 읽는다
console.log(parseInt('0xf'));   // 15
console.log(parseInt('0b10'));  // 0
console.log(parseInt('0o10'));  // 0
```

- 해석할 수 없는 문자열이나 공백 등은 전부 무시한다. 아예 해석할 수 없는 놈이면 NaN 반환

> encodeURI / decodeURI
> 

<aside>
❕ URI(Unifotm Resource Identifier) : 인터넷의 자원을 나타내는 유일한 주소. 하위개념 - URL, URN

</aside>

- encodeURI : URI를 문자열로 전달받아 이스케이프 처리를 위해 인코딩한다.
- decodeURI : 디코딩한다.

```jsx
const uri = `https://ko.wiktionary.org/wiki/예제`

const enc = encodeURI(uri);
console.log(enc);   // https://ko.wiktionary.org/wiki/%EC%98%88%EC%A0%9C

const dec = decodeURI(enc);
console.log(dec);   // https://ko.wiktionary.org/wiki/예제
```

인코딩 : URI의 문자들을 이스케이프 처리.

이스케이프 : 네트워크를 통해 정보를 공유할 때, 어떤 시스템에서도 읽어낼 수 있도록 아스키 문자 셋으로 변경하는 것. 알파벳, 0~9 숫자, 기본 문자들은 제외

> encodeURIComponent / decodeURIComponent
> 

URI 구성 요소(component)를 인수로 전달받아 인코딩/디코딩한다. 앞의 함수는 인수로 전달된 문자열이 `완전한 URI`라는 가정 하에 인코딩하기 때문에 쿼리 스트링 구분자(요소 문맥 구분하는 역할)는 인코딩하지 않는 반면에(문맥을 나누는 역할을 하는 기호까지 바꿔버리면 안되겟죠...) 이놈은 이미 나눠져있는 문맥을 인코딩하기 때문에 쿼리 스트링 구분자를 구분자로 보지 않고 걍 요소 중 하나로 보기 때문에 인코딩하는거.

## 암묵적 전역

이미 strict mode에서도 봤듯이, 선언하지 않은 식별자가 마치 선언된 전역 변수처럼 동작하는 현상이다.

```jsx
function foo() {
    x = 10;
}
foo();

console.log(x);
```

foo 함수 내의 x는 선언하지 않은 식별자지만, foo가 호출되면 자바스크립트 엔진은 스코프 체인에서 x를 찾아 값을 할당하려고 눈에 불을 켠다. 유연성이 지나친 광공;; 그래서 못 찾으면 마지막에 window.x=10으로 해석하여 전역 객체에 프로퍼티를 `동적 생성`해버린다.

전역변수 x와 암묵적 전역으로 인해 전역 객체의 프로퍼티로써 추가된 y의 차이에 대해 알아보자:

```jsx
// 선언되지 않은 식별자 y는 변수가 아니다
// 변수 호이스팅이 발생하지 않는다
console.log(x);     // undefined
console.log(y);     // ReferenceError: y is not defined

var x = 10;

function foo() {
    y = 20;
}
foo();

// 식별자 y는 선언하지 않았지만, 전역에서 참조가 가능하다. (암묵적 전역)
console.log(x+y);   // 30

delete x;
delete y;

console.log(globalThis.x);    // 10
console.log(globalThis.y);    // undefined
```

- y는 선언되지 않고 그저 전역 객체의 프로퍼티로써 추가되었을 뿐이므로, y는 x와 달리 **변수가 아니며 변수 호이스팅 또한 발생하지 않음**에 주의하자.
- 전역 변수 또한 전역 객체의 프로퍼티이지만, delete 연산자로 삭제할 수 없다. 그런데 변수가 아닌 단순 프로퍼티 y는 삭제가 가능하다.