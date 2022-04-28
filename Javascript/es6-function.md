# ES6 함수 추가 기능

ES6 이전의 자바스크립트의 함수는 사용 목적에 따라 명확히 구분되지 않았다.

- `일반 함수`
- new와 함께 사용하여 인스턴스를 생성하는 `생성자 함수`
- 객체에 바인딩되는 `메서드`

> ES6이전의 모든 함수는 `callable`이면서 `constructor`이다.
> 

사용 목적에 따라 명확한 구분이 없으므로 호출 방식에 제약이 없고 생성자 함수로 호출되지 않아도 스스로 프로토타입 객체를 생성하는 등 혼란스럽고 실수를 유발한다.

# ES6 함수 구분

이를 해결하기 위해 ES6에서는 함수를 사용 목적에 따라 세 가지로 명확히 구분하였다.

|  | constructor | prototype | super | arguments |
| --- | --- | --- | --- | --- |
| 일반 함수 (Normal) | O | O | X | O |
| 메서드 (Method) | X | X | O | O |
| 화살표 함수 (Arrow) | X | X | X | X |

`일반 함수`는 함수 선언문이나 함수 표현식으로 정의한 함수이다(ES6이전과 차이 X).

그러나 ES6의 `메서드`와 `화살표 함수`는 **non-constructor**로, ES6 이전과 확실한 차이가 있다.

# ES6 메서드

> ES6 사양에서 메서드란 `메서드 축약 표현`으로 정의된 함수만을 의미한다.
> 

- 인스턴스를 생성할 수 없는 `non-constructor`이다.

인스턴스를 생성할 수 없으므로 prototype 프로퍼티도 없고, 본인만의 프로토타입 체인도 없다.

- 자신을 바인딩한 객체를 가리키는 `내부 슬롯 [[HomeObject]]`를 갖는다.

super 참조는 이를 사용하여 수퍼클래스의 메서드를 참조하므로, ES6 메서드는 super 키워드를 사용할 수 있는 것이다.

```jsx
const obj = {
    x : 1,

// ES6 메서드는 메서드 축약 표현만을 인정한다

    // foo는 메서드가 아니다
    foo: function() {
        return `foo`;
    },

    // goo는 메서드다
    goo() {
        return `goo`;
    },
};

// ES6 메서드는 non-constructor이다
const foo = new obj.foo();  
const goo = new obj.goo();    // TypeError: obj.goo is not a constructor

console.log(obj.foo.hasOwnProperty(`prototype`));   // T
console.log(obj.goo.hasOwnProperty(`prototype`));   // F

// ES6 메서드만이 super 키워드를 사용할 수 있다
class Parents {
    constructor(name) {
        this.name = name;
    }

    sayHi() {
        return `Hi, ${this.name}!`;
    }
}

class Child extends Parents {
    constructor(name, age) {
        super(name);
        this.age = age;
    }

    // ES6 메서드가 아니다 (축약 표현이 아니다)
    // super 키워드 사용 불가능
    sayHi = function() {
        return `${super.sayHi()} ${this.age}}`;    // SyntaxError: 'super' keyword unexpected here
    }

    // ES6 메서드
    // super 키워드 사용 가능
    sayHello() {
        return `${super.sayHi()} ${this.age}}`;
    }
}
```

# 화살표 함수

function 키워드 대신 화살표(⇒, fat arrow)를 사용하여 보다 간략하게 함수를 정의할 수 있으며, 표현뿐만 아니라 내부 동작도 간략하다. 특히 콜백 함수 내부의 this 바인딩을 조정하는 데 유용하다.

## 정의하기

함수 선언문으로 정의할 수 없고, `함수 표현식`으로만 정의해야 한다.

## 매개변수

1. 매개변수 없을 때 : 소괄호 생략 X
2. 매개변수 하나뿐일 때 : 소괄호 생략 O
3. 매개변수 여러개일 때 : 소괄호 내에 선언

## 몸체 정의

1. 하나의 표현식인 문(값)일 때 : 중괄호 생략 O `암묵적 반환`
2. 객체 리터럴일 때 : `소괄호`로 묶어줘야 함
3. 여러개의 문일 때 : 중괄호 생략 X `명시적 반환`

## 즉시 실행 함수로 사용하기

통째로 소괄호로 묶어주고 필요 시에만 arguments 전달

```jsx
// 화살표 함수 (Arrow Function)

// 정의
const multiply = (x,y) => x * y;

// 매개변수

// 1. parameter가 없을 때 : () 생략 불가
const arrow1 = () => {};
// 2. parameter가 하나뿐일 때 : () 생략 가능
const arrow2 = x => {};
// 3. parameter 여러개 : () 안에 선언
const arrow3 = (a,b,c) => {};

// 몸체 정의

// 1-1. 함수 몸체가 하나의 표현식인 문일 때 : {} 생략 가능
// 값이 암묵적으로 반환된다
const power = x => x + 10;
console.log(power(2));     // 12

// 1-2. 하나의 문이어도 값으로 표현될 수 없는 문이라면 {}생략 불가능
/* const energy = () => const a = 1;    // SyntaxError: Unexpected token 'const'
const energy = () => {return const a = 1;};    // 위 코드는 이렇게 해석되므로 불가능 */

// 2. 객체 리터럴을 반환하는 경우
// ()로 감싸줘야 함
const create = (id, pass) => ({id, pass});
/* const create = (id, pass) => {return {id, pass};};    // 위 코드는 이렇게 해석된다 */
console.log(create(`khy731`, 731));    // { id: 'khy731', pass: 731 }

// 3. 함수 몸체가 여러 개의 문일 때 : {}생략 불가능
// 값을 명시적으로 반환해야 한다
const sum = (x,y) => {
    const result = x+y;
    return result;
};

// 즉시 실행 함수로 사용
const person = (name => ({
    sayHi() {
        return `Hi, ${name}!`;
    }
}))(`kang`);

console.log(person.sayHi());    // Hi, kang!
```

## 화살표 함수 vs 일반 함수

> 화살표 함수는 `non-constructor`이다.
> 

인스턴스를 생성할 수 없으므로 prototype 프로퍼티도 없고, 프로토타입도 생성하지 않는다.

> `중복된 parameter 이름`이 불가능하다.
> 
- 일반 함수는 허용됨(strict mode에선 불가능)
- 화살표 함수는 불가능

> 함수 자체의 this, arguments, super, [new.target] 바인딩을 갖지 **않는다**
> 

화살표 내에서 이들을 참조하면 스코프 체인을 통해 상위 스코프의 이것들을 참조한다.

## 화살표 함수의 this에 대하여

화살표 함수의 this는 일반 함수의 this와 다르게 동작한다. 이는 화살표 함수가 **콜백 함수 내부의 this 문제를 해결하기 위해 의도적으로 설계되었기 때문이다.**

> 콜백 함수 내부의 this 문제
> 

콜백 함수가 일반 함수로써 호출될 경우 내부의 this가 전역 객체 바인딩되어 외부 함수의 this와 달라져 헬퍼 함수로써의 역할이 삐끗하는 현상

```jsx
class Prefixer {
    constructor(prefix) {
        this.prefix = prefix;
    }

    // 프로토타입 메서드 add
    // 인수로 전달된 배열 arr를 순회하며 배열의 모든 요소에 prefix 추가
    add(arr) {
        return arr.map(function(item) {
            return this.prefix + item;    // TypeError: Cannot read properties of undefined (reading 'prefix')
        });
    }
}

const prefixer = new Prefixer(`webkit-`);   
console.log(prefixer.add([`user`,`select`]));
```

기대한 값 (webkit-user, webkit-select)이 나오지 않고 오류가 나는 이유?

![arrow-this](https://user-images.githubusercontent.com/97890886/165737645-96b7bd05-7b2d-4ae8-aa88-9916a0b6636b.png)

콜백 함수가 일반 함수로써 호출시 전역 객체가 this에 바인딩되는데, 클래스 내부에는 strict mode가 적용되므로 undefined가 바인딩된다. 외부 함수인 프로토타입 메서드 add의 this는 메서드로 호출시 자신을 참조하는 객체(예제에서는 prefixer)를 가리킨다.

→ `외부 함수의 this`와 `콜백 함수의 this`가 서로 다른 값을 가리키고 있기 때문에 TypeError가 발생한다.

> ES6 이전에 사용했던 해결 방법은 다음과 같다.
> 
1. 외부 함수의 this를 변수에 할당하여 회피시키고, 이후 그 변수를 this처럼 사용한다
2. 즉시 실행 함수의 두 번째 parameter로 외부 함수의 this를 전달한다
3. Function.prototype.bind 메서드(인위적 this바인딩)를 사용하여 외부 함수의 this를 바인딩한다

> ES6에서는 `화살표 함수`로 콜백 함수 내부의 this 문제를 해결할 수 있다.
> 

**화살표 함수는 자체의 this 바인딩을 갖지 않기 때문에 화살표 함수 내부에서 this를 참조하면 상위 스코프의 this를 그대로 참조한다.** 이를 `lexical this`라고 한다. 마치 렉시컬 스코프처럼, 화살표 함수의 this는 함수가 정의된 위치에 의해 결정된다. 화살표 함수는 this 바인딩이 존재하지 않는 유일한 함수로, 스코프 체인을 통해 상위 스코프에서 this를 탐색한다.

```jsx
// 화살표 함수는 상위 스코프의 this를 참조한다
() => this.x;

// 위 로직을 Function.prototype.bind로 나타낸 것
// 익명 함수에 상위 스코프의 this를 인수로 주입한다
(function() {
    return this.x;
}.bind(this));

// 화살표 함수로 콜백 함수 내부의 this 문제를 해결할 수 있다
class Prefixer {
    constructor(prefix) {
        this.prefix = prefix;
    }

    add(arr) {
        return arr.map(item => this.prefix + item);
    }
}

const prefixer = new Prefixer(`webkit-`);
console.log(prefixer.add([`user`,`select`]));   // [ 'webkit-user', 'webkit-select' ]

// foo는 화살표 함수를 반환하는 화살표 함수
// foo가 반환한 화살표 함수의 상위 스코프는 foo지만 foo도 화살표 함수이므로
// 스코프 체인 탐색을 통해 가장 가까우면서 화살표 함수가 아닌 즉시 실행 함수의 this를 가리킨다
(function() {
    const foo = () => () => console.log(this);
    foo()();
}).call({a:1});

// increase 프로퍼티에 할당된 화살표 함수
// 상위 스코프는 전역 객체
const counter = {
    num : 1,
    increase : () => ++this.num
};
console.log(counter.increase());
```

또한 call, apply, bind 메서드가 통하지 않는다. 호출은 가능하지만 화살표 함수는 자체 this 바인딩을 갖지 않고 언제나 상위 스코프의 this 바인딩 만을 참조한다.

### 주의점

> `메서드`나 `프로토타입 객체의 프로퍼티`에는 할당하는 것을 권장하지 않는다.
> 

메서드나 생성자 함수 같은 경우, this는 일반 함수처럼 상위 스코프가 아니라 자신을 참조할 객체이거나 자신이 이후 만들 인스턴스이다. 따라서 화살표 함수로 메서드나 프로토타입 겍체를 정의할 경우 이들의 체인을 따르지 않고 냅다 상의 스코프를 가리켜 문제가 생기게 된다.

```jsx
// 화살표 함수 : 1.메서드나 2.생성자 함수에 사용하는 것을 권장하지 않는다

// 1. 메서드

var age = 22;   // 전역 객체의 프로퍼티

const me = {
    age : 20,
    sayAge : () => console.log(this.age)    // 화살표 함수로 메서드 정의
};

// 화살표 함수의 this는 메서드를 참조하는 객체가 아니라 상위 스코프인 전역 객체
me.sayAge();    // 22

// 2. 프로토타입 객체의 프로퍼티

var name = `kang`   // 전역 객체의 프로퍼티

function Human(name) {
    this.name = name;
}

Human.prototype.sayName = () => console.log(this.name);    // 화살표 함수로 프로토타입 객체의 프로퍼티 정의

const person = new Human(`lee`);
// 화살표 함수의 this는 생성된 인스턴스가 아니라 상위 스코프인 전역 객체
person.sayName();     // kang
```

`메서드`를 정의할 때에는 `ES6 축약 메서드 표현`을 사용하도록 하자.

## 클래스 필드에 화살표 함수 할당하기?

클래스 필드 정의 제안을 사용하여 클래스 필드에 화살표 함수를 할당할 수도 있다.

```jsx
class Person {
    // 클래스 필드 정의 제안

    // 1. constructor 내부에 this를 사용하지 않고도 정의 가능
    // 2. 외붓값으로 초기화할 필요가 없을 때 사용
    // 3. 모든 클래스 필드는 인스턴스의 프로퍼티가 되므로 기본적으로 인스턴스 메서드이다

    name = `kang`;
    sayHi = () => console.log(`Hi ${this.name}`);

    // 위는 다음과 같은 로직이다
    /* constructor() {
        this.name = `kang`;
        this.sayHi = () => console.log(`Hi ${this.name}`);
    } */
}
```

이 때, sayHi 클래스 필드에 할당한 화살표 함수 내부의 this는 상위 스코프가 나올 것이다. 무엇일까?

직관적으로 생각하면 sayHi()는 클래스 내 프로퍼티니까(정확히 말하면 인스턴스 프로퍼티) 클래스 외부를 상위 스코프로 가져야 한다. 그런데 this를 참조하면 클래스 외부가 아닌 **클래스가 생성할 인스턴스**를 가리킨다. 즉 constructor 내부의 this 바인딩과 같은 것이다.

> 클래스 필드에 화살표 함수를 할당하여 메서드로 사용하는 것은 바람직하지 않으며, 메서드를 정의할 때는 `ES6 메서드 축약 표현`을 사용하는 것이 좋다.
> 

## super

> 화살표 함수는 자체 super 바인딩을 갖지 않으며, 상위 스코프의 super을 참조한다.
> 

super 키워드는 내부 슬롯 [[HomeObject]]를 갖는 ES6 메서드 내에서만 사용 가능한 키워드이나, 화살표 함수도 자체 super 바인딩을 갖지 않으므로 super을 참조해도 에러가 나지 않으며 constructor의 super 바인딩을 참조한다. (결국 원리대로 동작?)

## arguments

> 화살표 함수는 자체 arguments 바인딩을 갖지 않으며, 상위 스코프의 arguments를 참조한다.
> 

arguments 객체는 가변 인자 함수(함수 정의 시, 매개변수 개수 확정이 애매할 때)에 유용하지만, 화살표 함수는 argumetns를 사용할 수 없다. 상위 스코프의 argumnets를 참조할 수는 있지만 화살표 함수 자신에게 전달된 인수 목록은 확인 불가능하기 때문에 좀 쓸모가 없다.

→ 화살표 함수로 가변 인자 함수를 구현할 때에는 `Rest 파라미터` 사용한다.

# Rest 파라미터 (나머지 매개변수)

> 함수에 전달된 인수들의 목록을 배열로 전달받는다.
> 
- 매개변수 이름 앞에 `...(세 개의 점)`을 붙여 정의한다.
- 일반 매개변수와 함께 사용할 수는 있으나 먼저 선언된 매개변수에 할당된 인수를 제외한 나머지 인수들이 순차적으로 나온다.
- 단 한 번만 선언 가능하다.
- 함수 객체의 길이(length 프로퍼티)에 영향을 주지 않는다.

```jsx
// rest parameter

function foo(...rest) {
    console.log(rest);
}

foo(1,2,3,4,5);    // [ 1, 2, 3, 4, 5 ]

// 먼저 선언된 매개변수에 순차적 할당
// 나머지 인수들로 구성된 배열이 바로 Rset 파라미터이다
function goo(param1, param2, ...rest) {
    console.log(rest);
}

goo(1,2,3,4,5);     // [ 3, 4, 5 ]

// 단 한번만 선언 가능하다
/* function zoo(...rest1, ...rest2); */    // SyntaxError: Rest parameter must be last formal parameter

// 함수 객체의 length 프로퍼티에 영향을 주지 않는다
function a(...rest) {}
console.log(a.length);     // 0
```

## 화살표 함수에서는 arguments 말고 Rest 파라미터

매개변수의 개수를 확정할 수 없는 `가변 인자 함수`의 경우, 매개변수를 통해 인수를 전달받는 것이 불가능하기 때문에 arguments 객체를 통해 전달받았다.

arguments 객체는 호출 시 전달된 인수들의 정보를 담고 있는 **유사 배열 객체**이며, 함수 내부에서 지역 변수처럼 사용이 가능하다. arguments는 찐 배열이 아닌 유사 배열 객체이기 때문에 배열 메서드를 사용하려면 배열로 변환하는 추가 과정이 필요하다. 

> ES6 메서드와 달리 `화살표 함수`는 arguments 객체를 사용할 수 없으므로, 화살표 함수로 가변 인자 함수를 구현해야 할 때에는 **반드시 Rest 파라미터**를 사용해야 한다.
> 

## 매개변수 기본값

자바스크립트 엔진은 parameter의 개수와 arguments의 개수를 체크하지 않기 때문에, 둘의 개수가 일치하지 않을 때 의도치 않은 결과를 예방하기 위해 단축 표현을 통한 방어 코드가 필요했다.

ES6에서 도입된 `매개변수 기본값`을 이용하면 이를 간소화할 수 있다.

```jsx
// 의도치 않은 결과
function sum(x,y) {
    return x+y;
}
console.log(sum(1));    // NaN

// 단축표현을 통한 방어코드
// 매개변수가 전달되지 않은 매개변수(undefined)에 0 할당하여 초기화
function sum(x,y) {
    x = x || 0;
    y = y || 0;

    return x+y;
}
console.log(sum(1));    // 1

// ES6의 매개변수 기본값
// 인수 체크 및 초기화를 간소화
function sum(x=0, y=0) {
    return x+y;
}
console.log(sum(1));    // 1
```

Rest 파라미터에는 **기본값을 지정할 수 없다.** 매개변수 기본값은 length와 arguments에 아무런 영향을 주지 않는다.