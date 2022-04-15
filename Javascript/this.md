# 자기 참조 변수 this의 필요성

> 객체는 상태를 나타내는 프로퍼티와 동작을 나타내는 메서드를 하나의 논리적인 단위로 묶은 복합적인 자료구조다.

이 때, 메서드가 프로퍼티를 참조하려면 먼저 자신이 속한 객체(의 식별자)를 참조할 수 있어야 한다. 그거 쉬운 거 아닌가? 객체의 식별자가 circle이라면, circle.xxx 이런 형태로 참조하면 되는 거 아냐? 라고 하는 사람들을 위해, this의 필요성을 설명하겠다.

- 객체 리터럴 : 재귀적 참고

```jsx
const circle = {
    radius: 3,

    getDiameter() {
        return circle.radius * 2;
    }
};
```

메서드 내에서 자신이 속한 객체를 가리키는 식별자를 직접 재귀적으로 호출하여 참조하고 있다. 이 참조 표현식이 평가되는 시점은 메서드가 호출되어 함수 자체가 실행되는 시점이다. 이런 코드가 가능한 이유는 객체 리터럴이 변수(상수)에 할당되기 전에, 그러니까 런타임 이전에 이미 평가되어 객체가 생성되었기 때문이다.

- 생성자 함수 :  재귀적 참고 불가능

```jsx
function Circle(radius) {
    // 이 시점에는 아직 생성자 함수로 인스턴스(객체)가 생성되지 않았다
    // 생성자 함수가 생성할 인스턴스를 가리키는 식별자를 알 수 없다
    ????.radius = radius;
}

Circle.prototype.getDiameter = function() {
    // 역시 아직 알 수 없다
    return ????.radius * 2;
};

// 이제야 객체가 생성되었다
// 그러면 생성자 함수를 만들 때부터 객체를 참조하는 것은 불가능할까?
const circle = new Circle(5);
```

생성자 함수 내부에서는, 프로퍼티/메서드를 조작하기 위해선 자신이 미래에 생성하게 될 인스턴스를 참조해야 한다. 하지만 이건 완전 모순 구조이다... 생성자 함수만 정의한 시점에서는 아직 인스턴스 생성 전이므로 생성자 함수가 생성할 인스턴스를 가리키는 식별자를 알 수 없기 때문이다. 이 때, this가 나온다.

> this는 `자신이 속한 객체` 또는 `자신이 생성할 인스턴스`를 가리키는 **자기 참조 변수(self-referencing variable)**이다.
> 
- this는 자바스크립트 엔진에 의해 암묵적으로 생성되어 코드 어디서든 참조 가능하며, 마치 지역 변수처럼 사용이 가능한 변수
- 클래스 기반 언어와는 달리(이쪽의 this는 집 바라기이다. 언제나 클래스 자체가 생성한 인스턴스만을 가리킨다.) this바인딩은 `함수 호출 방식`에 의해 동적으로 결정된다. 그리고 strict mode의 유무 또한 영향을 끼친다.

```jsx
// this 는 어디서든 참조 가능하다

// 전역에서의 this : 전역 객체 window/global를 가리킴
console.log(this);

// 일반 함수에서의 this : 전역 객체 window/global를 가리킴
function foo() {
    console.log(this);
}

// 객체
const person = {
    name: `kang`,
    getName() {
        // 메서드에서의 this : 메서드를 호출한 객체를 가리킴
        console.log(this);    // { name: 'kang', getName: [Function: getName] }
        return this.name;
    },
};

console.log(person.getName());    // kang

// 생성자 함수
function Goo(age) {
    this.age = age;
    // 생성자 함수 내부에서의 this : 생성자 함수가 생성할 인스턴스를 가리킴
    console.log(this);     // Goo { age: 22 }
}

const zoo = new Goo(22);
```

위에서 봤듯이, 전역이나 일반 함수는 죄다 걍 전역 객체다. 다 똑같을 때 다른 부분만 알면 되는 것처럼,

> this는 `객체의 메서드 내부`나 `생성자 함수 내부`에서만 의미를 가진다.
this는 **객체의 프로퍼티/메서드를 참조하기 위한 자기 참조 변수**이므로 일반적으로 `객체의 메서드 내부` 또는 `생성자 함수 내부`에서만 의미가 있다. 그래서 strict mode가 적용된 일반 함수 내부의 this는 undefined가 바인딩된다. 필요가 없으니까...

# this 바인딩

> this 바인딩은 `함수 호출 방식`에 따라 동적으로 결정된다.
> 

렉시컬 스코프(lexical scope, 함수의 상위 스코프를 결정하는 방식)는 함수 정의가 평가되어 함수 객체가 생성되는 시점에 결정되지만, this 바인딩은 함수가 어떻게 호출되었는지에 따라 동적으로 결정된다.

> 함수를 호출하는 방법
> 
- 일반 함수 호출
- 메서드 호출
- 생성자 함수 호출
- Function.prototype.apply/call/bind 메서드에 의한 간접 호출

```jsx
// this 바인딩은 함수 호출 방식에 따라 동적으로 결정된다
const foo = function() {
    console.dir(this);
};

// 동일한 함수도 다양한 방식으로 호출할 수 있다

// 1. 일반 함수 호출
// foo 함수 내부의 this -> 전역 객체 window/global
foo();

// 2. 메서드 호출
// foo 함수를 객체의 프로퍼티 값으로 할당하여 호출
// foo 함수 내부의 this -> 메서드를 호출한 객체 obj
const obj = {foo};
obj.foo();

// 3. 생성자 함수 호출
// foo 함수를 new 연산자와 함께 생성자 함수로 호출
// foo 함수 내부의 this -> 생성자 함수가 생성한 인스턴스
new foo();

// 4. Function.prototype.apply/call/bind 메서드에 의한 간접 호출
// foo 함수 내부의 this -> 인수에 의해 결정됨
const zoo = {name:`zoo`};

foo.call(zoo);
foo.apply(zoo);
foo.bind(zoo)();
```

## 일반 함수 호출

`일반 함수`로 호출된 **모든 함수(중첩 함수, 콜백 함수 등 헬퍼 함수 전부 포함)** 내부의 this에는 `전역 객체`가 바인딩된다.

```jsx
// 어떤 함수든 일반 함수로 호출하면 this에는 전역 객체가 바인딩된다

// 중첩 함수 -> 일반 함수로 호출
function foo() {
    console.log(this);
    function goo() {
        console.log(this);
    }
    goo();   // window
}
foo();    // window

// strict mode가 적용된 일반 함수 내부의 this는 undefined이다
const zoo = (function() {
    'use strict';
    console.log(this);
    function joo() {
        console.log(this);
    }
    joo();  // undefined
}());   // undefined
```

> 문제 : 메서드 내의 헬퍼 함수의 this 바인딩
> 

헬퍼 함수는 외부(원본) 함수를 돕는 역할을 한다 : 외부 함수의 일부 로직을 대신하는 경우가 대부분이다. 그런데 만약, 메서드 내에서 헬퍼 함수가 사용된 경우 메서드=외부 함수와 헬퍼 함수의 this가 일치하지 않게 된다. 이러한 문제점은 중첩 함수나 콜백 함수가 헬퍼 함수로 동작하기 어렵게 만든다.

```jsx
// 메소드 내에서 헬퍼 함수를 사용하는 경우
// 외부 함수(메소드)와 헬퍼 함수의 this가 일치하지 않는 문제가 생긴다

// 메소드 내의 중첩 함수 -> 일반 함수로 호출
var value = 1;

const obj = {
    value : 10,
    foo() {
        console.log(this.value);    // 10
        function goo() {
            console.log(this.value);    // 1
        }
        goo();
    },
};

obj.foo();

// 메소드 내의 콜백 함수 -> 일반 함수로 호출
const obj2 = {
    value : 100,
    zoo() {
        console.log(this.value);    // 100
        setTimeout(function() {
            console.log(this.value);    // 1
        }, 100);
    }
};

obj2.zoo();
```

> 해결
> 
- 객체 내의 this를 변수에 할당하여 사용
- this를 명시적으로 바인딩하는 메서드 Function.prototype.apply/call/bind 사용
- 화살표 함수

```jsx
// 외부 함수=메서드와 헬퍼 함수의 this 바인딩 불일치 문제 해결

// 1. 객체 내의 this를 변수에 할당하여 사용

var value = 1;

const obj = {
    value : 10,
    foo() {
        const that = this;
        setTimeout(function() {
            console.log(that.value);    // 10
        }, 100);
    }
};

obj.foo();

// 2. 메서드 Function.prototype.apply/call/bind 사용

const obj2 = {
    value : 100,
    goo() {
        // 콜백 함수에 명시적으로 this 바인딩
        setTimeout(function() {
            console.log(this.value);    // 100
        }.bind(this), 100);
    }
};

obj2.goo();

// 3. 화살표 함수

const obj3 = {
    value : 1000,
    zoo() {
        // 화살표 함수 내부의 this는 상위 스코프의 this를 가리킴
        setTimeout(() => console.log(this.value),100);  // 1000
    }
};

obj3.zoo();
```

## 메서드 호출

메서드 내부의 this에는 **메서드를 소유한 객체**가 아닌, `메서드를 호출한 객체`(메서드를 호출할 때 .연산자 앞에 기술한 객체)가 바인딩된다.  

![this2.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/980406e7-427b-472d-a138-49c48c2fec58/this2.png)

```jsx
const person = {
    name : `kang`,
    getName() {
        return this.name;
    },
};

const anotherPerson = {
    name : `Lee`,
}

// 메서드를 다른 객체의 메서드로 할당
anotherPerson.getName = person.getName;
console.log(anotherPerson.getName());   // Lee

// 메서드를 변수에 할당
const yourName = person.getName;
console.log(yourName());    // window.name과 같다
```

getName 메서드는 Person 객체의 프로퍼티에 바인딩된 함수지만, 객체 자체에 포함된 것이 아니라 독립적으로 존재하는 별도의 함수며 getName 프로퍼티가 이 별도의 함수 객체를 가리키고 있는 것이기 때문에 다른 객체의 프로퍼티에 할당되어 다른 객체의 메서드가 될 수도 있고, 일반 변수에 할당되어 일반 함수로써 호출될 수도 있다.

메서드 내부의 this는 프로퍼티로 메서드를 가리키고 있는(메서드를 소유하고 있는) 객체와 관련이 없고 `메서드를 호출한 객체`에 바인딩된다.

```jsx
function Person(name) {
    this.name = name;
}

Person.prototype.getName = function() {
    return this.name;
}

const me = new Person(`kang`);      
// getName을 호출한 것은 me
console.log(me.getName());      // kang

Person.prototype.name = `Lee`;

// getName을 호출한 것은 Person.prototype
console.log(Person.prototype.getName());    // Lee
```

생성자 함수도 마찬가지다. 프로토타입도 객체이기 때문에 같은 취급이다.

## 생성자 함수 호출

생성자 함수 내부의 this에는 생성자 함수가 `미래에 생성할 인스턴스(객체)`가 바인딩된다.

```jsx
function Welcome(name) {
    this.name = name;
    this.getName = function() {
        return `welcome, ${this.name}!`;
    }
}

const me = new Welcome(kang);
const you = new Welcome(lee);

console.log(me.getName());      // kang
console.log(you.getName());     // lee
```

## Function.prototype.apply/call/bind 메서드에 의한 간접 호출

apply, call, bind 메서드는 전부 Function.prototype의 메서드이며, 모든 함수가 상속받아 사용할 수 있다.

> apply와 call
> 

함수를 `호출`하면서 첫 번째 인수로 전달한 객체를 this로 바인딩한다.

> bind
> 

함수를 호출하지는 않지만, 첫 번째 인수로 전달한 객체로 호출한 함수의 this 바인딩을 교체하여 함수를 새롭게 생성하여 반환한다.

bind 메서드는 메서드의 this와 헬퍼 함수의 this가 불일치하는 문제를 해결한다.

```jsx
const person = {
    name : `kang`,
    getName(f) {
        setTimeout(f, 100);
    }
};

function hello() {
    console.log(`Hi! my name is ${this.name}!`);
}

// 콜백 함수 hello는 일반 함수로써 호출되었다
// 일반 함수로써 호출된 경우 this : 전역 객체
person.getName(hello);      // Hi! my name is undefined!
```

```jsx
const person = {
    name : `kang`,
    getName(f) {
        // bind 메서드로 내부의 this 바인딩을 전달
        setTimeout(f.bind(this), 100);
    }
};

function hello() {
    console.log(`Hi! my name is ${this.name}!`);
}

// 콜백 함수 hello는 일반 함수로써 호출되었지만
// person 내부의 this 바인딩을 전달받았다
person.getName(hello);      // Hi! my name is kang!
```

지금까지의 내용을 정리하면 다음과 같다.

- 일반 함수 호출 : 전역 객체
- 메서드 호출 : 메서드를 호출한 객체
- 생성자 함수 호출 : 생성자 함수가 미래에 생성할 인스턴스
- Function.prototype.apply/call/bind : 첫 번째 인수로 전달한 객체