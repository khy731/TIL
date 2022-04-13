# 일급 객체

- 무명의 리터럴로 생성 가능 (런타임에 생성 가능)
- 변수, 자료구조(객체, 배열 등)에 저장 가능
- 함수의 매개변수에 전달 가능
- 함수의 반환값으로 사용 가능

> 자바스크립트의 함수는 위 조건을 모두 만족하는 `일급 객체`이다.
> 

```jsx
// 1. 함수는 무명의 리터럴로 생성할 수 있다
// 2. 함수는 변수에 저장할 수 있다
const increase = function(num) {
    return ++num;
};

const decrease = function(num) {
    return --num;
};

// 3. 함수는 객체에 저장할 수 있다
const sum = {
    increase,
    decrease,
};

// 4. 함수는 함수의 parameter에 argument로써 전달될 수 있다
const counter = function (f) {
    let num = 0;
// 5. 함수는 함수의 return 문으로 사용할 수 있다
    return function() {
        num = f(num);
        return num;
    };
};

// 4. 함수는 함수의 parameter에 argument로써 전달될 수 있다
const increaser = counter(sum.increase);
const decreaser = counter(sum.decrease);

console.log(increaser());   // 1
console.log(decreaser());   // -1

// increaser, decreaser도 함수임에 주의
// 함수를 호출하여 상수에 담은 것이기 때문에
// 호출할 때도 increaser이 아니라 increaser()로 호출해야 한다
```

함수는 객체와 동일하게 사용할 수 있다. 객체는 값이므로, 함수는 값과 동일하게 취급(변수 할당문, 객체의 프로퍼티 값, 배열의 요소, 함수 호출의 인수, 함수 반환문 등으로 사용)되며 runtime에 함수 객체로 평가된다.

이러한 다양한 특성 중 `함수의 parameter에 arguments로써 전달 가능`, `함수의 return 값으로 사용 가능`이라는 특성은 **함수형 프로그래밍**을 가능하게 하는 자바스크립트의 강점이다.

> 다만 함수가 일반 객체와 다른 점은 :
> 
- 함수 객체는 일반 객체와 다르게 `호출`이 가능하다
- 함수 객체는 일반 객체에는 없는 `함수 고유 프로퍼티`를 소유한다

# 함수 객체의 프로퍼티

함수도 객체다. 함수도 프로퍼티를 가질 수 있다. `console.dir` 메서드를 사용하면 함수 내부를 들여다볼 수 있다.

```jsx
function square(number) {
    return number * number;
}

console.dir(square);
```

![브라우저 콘솔로 확인한 결과](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/80acb7d3-fdbb-4b00-a733-7a7386f81889/function-property.png)

브라우저 콘솔로 확인한 결과

```jsx
console.log(Object.getOwnPropertyDescriptors(square));

/*
[Function: square]
{
  length: { value: 1, writable: false, enumerable: false, configurable: true },
  name: {
    value: 'square',
    writable: false,
    enumerable: false,
    configurable: true
  },
  arguments: {
    value: null,
    writable: false,
    enumerable: false,
    configurable: false
  },
  caller: {
    value: null,
    writable: false,
    enumerable: false,
    configurable: false
  },
  prototype: { value: {}, writable: true, enumerable: false, configurable: false }
}
*/
```

함수 내부에는 일반 객체에는 없는 함수 객체 고유의 `프로퍼티`가 있다.

- arguments
- caller
- lentgh
- name
- prototype

참고로, __proto__ 는 함수 객체 고유의 프로퍼티가 아니라 모든 객체를 아우르는 부모 객체인 Object.prototype 객체의 프로퍼티를 상속받은 것으로, 이는 함수뿐만 아니라 다른 모든 객체들도 상속받아 사용할 수 있는 프로퍼티이다.

## arguments

함수 객체의 arguments 프로퍼티 값은 arguments 객체를 의미한다.

```jsx
arguments: {
    value: null,
    writable: false,
    enumerable: false,
    configurable: false
},
```

- 함수 호출 시 전달된 인수들 arguments의 정보를 담고 있는 순화 가능한 iterable 유사 배열 객체이다.
- 함수 내부에서 지역 변수처럼 사용된다. (함수 외부에서 참조 불가)

매개변수는 함수 몸체 내부에서 변수와 동일하게 취급되므로, 함수가 호출되면 암묵적으로 함수 몸체 내에서 매개변수가 선언 + undefined로 초기화 + 인수가 할당 된다.

→ 매개변수와 인수의 개수가 일치하지 않아도 상관없다 (에러를 반환하지 않는다)

→ 적게 전달 시 : 남은 매개변수는 여전히 undefined이다.

    많게 전달 시 : 초과된 인수는 무시된다.

그러나, 이 때 초과된 인수가 그냥 버려지는 것은 아니다.

> 모든 인수는 암묵적으로 arguments 객체의 프로퍼티로 보관된다.
> 

arguments 객체는 인수를 프로퍼티 값으로 보관한다.

### auguments 객체의 프로퍼티

- 인수 정보

인수 순서(key) : 인수 값(value)

- callee 프로퍼티

호출되어 arguments 객체를 생성한 함수(함수 자신)

- length 프로퍼티

인수의 개수

- Symbol(Symbol.iterator) 프로퍼티

arguments 객체를 이터러블 (iterable, 순회 가능한 자료구조)로 만들기 위한 프로퍼티. Symbol.iterator 내부의 메서드를 사용하여 arguments 객체를 순회할 수 있다.

> arguments 객체는 매개변수와 인수의 갯수를 확인하는 데 유용하다.
> 

parameter와 arguments의 개수가 일치하는지 확인하지 않는 자바스크립트의 특성상, 함수가 호출되면 인수 개수를 확인하고 이에 따라 함수의 동작을 달리 정의할 필요가 있다.

### 가변 인자 함수

```jsx
function sum() {
    let num = 0;

    for (let i=0; i<arguments.length; i++) {
        num += arguments[i]
    }

    return num;
}

const result1 = sum();  
const result2 = sum(1,2);
const result3 = sum(2,4,35,3);

console.log(result1,result2,result3);   // 0 3 44
```

> arguments 객체는 `유사 배열 객체 (array-like object)`이다.
> 

배열은 아니지만, 배열 형태로 인자 정보를 담고 있으며, length 프로퍼티를 가진 객체이므로 for문으로 순회가 가능하다.

이터러블이 도입된 ES6부터 arguments는 유사 배열 객체이면서 동시에 이터러블(순회 가능한 자료구조)이 되었다. 참고!

유사 배열 객체는 배열이 아니므로, 배열 메서드를 직접 사용할 경우 에러가 발생한다. 배열 메서드를 사용하려면 간접 호출(arguments 객체를 배열로 변환해줘야 함)을 해줘야 하기 때문에 상당히 불편하고 ES6에서는 이를 해결하기 위해 `Rest 파라미터`를 도입했다.

Rest 파라미터의 도입으로 arguments 객체는 좀 한물 갔지만, 알아둘 필요는 있다.

## caller

ECMAScript 사양에 포함되지 않은 비표준 프로퍼티이다. 이후 표준화될 예정도 없는 프로퍼티다.

> 함수 자신을 호출한 함수를 가리킨다.
> 

```jsx
function foo(f) {
    return f();
}

function goo() {
    return `caller은 ${goo.caller}`;
}

console.log(foo(goo));
console.log(goo());
```

![브라우저에서 실행한 결과](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/f2d73bf5-9a1b-4301-b867-e9a8c78ef432/caller.png)

브라우저에서 실행한 결과

## length

> 함수를 정의할 때 선언한 매개변수의 개수
> 

arguments 객체의 length 프로퍼티와 함수 객체의 length 프로퍼티 값이 다를 수 있다

- `arguments 객체`의 length 프로퍼티 : 인자의 개수
- `함수 객체`의 length 프로퍼티 : 매개변수의 개수

```jsx
function foo() {
    return `매개변수의 개수 : ${foo.length}`;
}
function goo(x,y) {
    return `매개변수의 개수 : ${goo.length}`;
}
function zoo(a,b,c,d,e) {
    return `매개변수의 개수 : ${zoo.length}`;
}

console.log(foo(), goo(), zoo());   // 매개변수의 개수 : 0 매개변수의 개수 : 2 매개변수의 개수 : 5
```

## name

> 함수 이름.
> 

ES6 이후로 정식 표준이 되었다. ES5와 ES6에서 동작이 다르다.

`익명 함수 표현식`에서

- `ES5` 에서의 name 프로퍼티의 값 : 빈 문자열
- `ES6` 에서의 name 프로퍼티의 값 : 함수 객체를 가리키는 식별자

```jsx
// 1. 함수 선언문
function foo() {
    return `함수 이름 : ${foo.name}`;
}

// 2. 함수 표현식 : 가명
const goo = function bar() {
    return `함수 이름 : ${goo.name}`;
}

// // 2. 함수 표현식 : 가명
let zoo = function () {
    return `함수 이름 : ${zoo.name}`;
}

console.log(foo(), goo(), zoo());   // 함수 이름 : foo 함수 이름 : bar 함수 이름 : zoo
```

## __proto__ (접근자 프로퍼티)

> 내부 슬롯 [[Prototype]]가 가리키는 프로토타입 객체에 접근하기 위해 사용하는 접근자 프로퍼티
> 

 [[Prototype]] 는 모든 객체가 갖는 내부 슬롯으로, 객체지향 프로그래밍에서의 ‘상속’을 구현하는 프로토타입 객체를 가리킨다. 내부 슬롯에는 직접적으로 접근할 수 없기 때문에 간접적으로 접근자 프로퍼티 __progo__를 사용하여 접근한다.

```jsx
const obj = {
    a : 1,
};

// 객체 리터럴 방식으로 생성한 객체의 프로토타입 객체는 Object.prototype
console.log((obj.__proto__ === Object.prototype));    // true

//
console.log(obj.hasOwnProperty(`a`));           // true
console.log(obj.hasOwnProperty(`__proto__`));   // false
```

hasOwnProperty 메서드는 인수로 전달받은 프로퍼티 키가 객체 고유의 프로퍼티 키인 경우에만 true를 반환한다(’a’) . 상속받은 프로토타입의 프로퍼티 키인 경우 false를 반환한다. (’__proto__’)

## prototype

> 생성자 함수로 호출할 수 있는 객체 (constructor)만이 소유하는 프로퍼티.
> 

일반 객체, 일반 함수처럼 선언하지 않은 함수 등은 non-constructor 이므로 없다.

함수가 생성자 함수로 호출될 때, 생성자 함수가 생성할 인스턴스의 프로토타입 객체를 가리킨다.