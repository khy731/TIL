# 클래스

자바스크립트는 클래스가 필요 없는 class free 프로토타입 기반 prototype based 객체지향 프로그래밍 언어이다. 그런데, ES6에서 도입된 클래스를 사용하여 자바와 C#와 비슷한 클래스 기반 객체지향 프로그래밍을 할 수 있다.

## 자바스크립트의 클래스는 문법적 설탕(syntactic sugar)

사실 자바스크립트의 클래스는 함수이며, 기존 프로토타입 기반 패턴(생성자 함수)을 클래스 패턴처럼 사용할 수 있게 하는 문법적 설탕이다.

클래스와 생성자 함수는 프로토타입 기반의 인스턴스를 생성한다는 점에서는 동일하지만, 몇 가지 차이가 있다.

1. 클래스는 new 연산자가 필수이다.(안 쓸 시 error 발생) 자바스크립트는 new 없으면 그냥 일반 함수로써 동작한다.
2. 클래스는 extends, super라는 키워드로 상속을 지원한다. 생성자 함수는 지원하지 않는다.
3. 클래스는 호이스팅이 발생하지 않는 것처럼 동작한다. 생성자 함수는 함수 선언문 : 함수 호이스팅, 함수 표현식 : 변수 호이스팅이 발생한다.
4. 클래스 내 모든 코드에는 암묵적으로 strict mode가 적용되며, 이는 해제할 수 없다.
5. 클래스의 구성 멤버는 전부 열거 불가능하다 ([[Enumerable]]이 false이다)

클래스는 생성자 함수 기반의 객체지향보다 견고하고 명료하다(우월하다는 뜻은 아니다!)

> 클래스는 문법적 설탕이라기 보다는 `새로운 객체 생성 메커니즘`이다.
> 

# 클래스 정의

```jsx
// 일반적인 클래스 선언문
class Person {}

// 표현식으로 클래스 선언하기
// 일반적이지는 않지만, 이 경우 익명 or 가명 선택 가능
const Person = class {};
const Person = class myClass {};

// 표현식으로 정의 가능 = 값으로 사용 가능 = 일급 객체
// 클래스는 (함수이므로) 일급 객체이다.
```

**클래스는 함수**이다. 그러므로 클래스는 `일급 객체`이다.

- 런타임에 생성 가능 (무명의 리터럴로 생성 가능)
- 변수, 자료구조(객체나 배열 등)에 저장 가능
- 함수의 parameter에 전달 가능
- 함수의 반환값으로 사용 가능

즉시 실행 함수에 생성자 함수, 프로토타입과 private을 때려박고 감싼 형태와 비슷하다. 즉 클래스와 생성자 함수의 정의 방식은 형태적인 면에서 상당히 유사하다.

### 생성자 함수

```jsx
// 생성자 함수 (ES5)

// 즉시 실행 함수로 묶는다
const Person = (function() {

    // private
    let a_ge = 0;

    // 생성자 함수 (클로저)
    function Person(name, a_ge) {
        this.name = name;
        age = a_ge;
    };

    // 프로토타입 메서드 (클로저)
    Person.prototype.sayHi = function() {
        console.log(`Hi, ${this.name}, ${age}!`);
    };

    // 정적 메서드
    // private
    Person.sayHello = function() {
        console.log(`Hello, world!`);
    };
    
    // 생성자 함수 반환
    return Person;
}());

const me = new Person(`kang`, 22);
me.sayHi();     // Hi, kang, 22!
Person.sayHello();     // Hello, world!
```

### 클래스

```jsx
class Person {
    
    // 생성자
    constructor(name) {
        this.name = name;
    }

    // 프로토타입 메서드
    sayHi() {
        console.log(`Hi, ${this.name}!`);
    }

    // 정적 메서드
    static sayHello() {
        console.log(`Hello, world!`);
    }
}

const me = new Person(`Yoon`);    
me.sayHi();    // Hi, Yoon!
Person.sayHello();    // Hello, world!
```

# 클래스 호이스팅

클래스는 함수로 평가되며, const나 let처럼 호이스팅된다. 호이스팅 되지만 TDZ(일시적 사각지대)에 빠져 호이스팅이 발생하지 않는 것처럼 동작할 뿐이다.

```jsx
const Person = `kang`;
{
    // ReferenceError: Cannot access 'Person' before initialization
    // 클래스 호이스팅이 일어나지 않는다면
    // kang이 나왔어야 한다
    console.log(Person);
    class Person {}
    // 
}
```

# 인스턴스 생성

클래스는 생성자 함수이며, new연산자와 함께 호출되어 인스턴스(객체)를 생성한다.

함수는 new 여부에 따라 생성자 함수 or 일반 함수로 호출되지만, 클래스는 용도가 인스턴스 생성 뿐이므로 반드시! new와 함께 호출하여야 한다. (아니면 에러 발생)

만약 클래스를 표현식으로 정의한 경우, 클래스를 가리키는 식별자가 아닌 안에 있는 함수명으로 부르면 에러가 난다. 이건 외부 코드에서 접근 불가능한 값이기 때문이다(익명의 경우 자바스크립트 엔진이 암묵적으로 생성해주는것만 봐도...)

```jsx
// 클래스
class Person{}

// new 빼먹으면 오류 남
const me2 = Person();   // TypeError: Class constructor Person cannot be invoked without 'new'
const me = new Person();

// 인스턴스 생성 : 표현법 (가명)
const Cat = class kitty {};

// 클래스를 가리키는 식별자로만 인스턴스 생성 가능
const cat = new Cat();
// 클래스 이름(kitty)는 클래스 몸체 내부에서만 유일한 식별자이다
const cat2 = new kitty();   // ReferenceError: kitty is not defined
```

# 메서드

클래스 몸체에는 `메서드`만 정의 가능하며(인스턴스 프로퍼티는 반드시 constructor 내부에서 정의해야 한다. 현재는 개선됐지만 이후에 자세히 알아보자), 정의할 수 있는 메서드는 다음과 같다.

1. constructor (생성자)
2. 프로토타입 메서드
3. 정적 메서드

```jsx
// 클래스 몸체에서 정의할 수 있는 메서드
// 1. constructor (생성자)
// 2. 프로토타입 메서드
// 3. 정적 메서드

class Person {
    // 생성자
    // 인스턴스 생성 및 초기화 역할
    constructor(name) {
        this.name = name;
    }

    // 프로토타입 메서드
    sayHi() {
        console.log(`Hi! my name is ${this.name}`);
    }

    // 정적 메서드
    static sayHello() {
        console.log(`Hello~`);
    }
}

const me = new Person(`kang`);

console.log(me.name);   // kang
me.sayHi();             // Hi! my name is kang
Person.sayHello();      // Hello~

// static은 private이므로 접근 불가능
me.sayHello();      // TypeError: me.sayHello is not a function
```

## constructor

> 인스턴스를 생성 & 초기화하는 특수 메서드이다. 이름을 변경할 수 없다.
> 

생성자 함수와 마찬가지로

- constructor 내부의 this는 클래스가 생성할 인스턴스를 가리키고, this에 추가한 프로퍼티는 `인스턴스 프로퍼티`가 된다
- 함수 객체로 평가되어 프로토타입과 함수 객체 고유의 프로퍼티를 가지고 있으며, 본인의 프로토타입과 prototype - constructor 로 이어져 있다

```jsx
// 클래스
class Person {

    // 생성자
    constructor(name) {
        // 인스턴스 생성 및 초기화
        this.name = name;
    }
}

// 생성자 함수
function Person(name) {
    // 인스턴스 생성 및 초기화
    this.name = name;
}
```

![class1](https://user-images.githubusercontent.com/97890886/165515780-cc10b695-5fb5-4e15-9f2f-c6e5757356c5.png)

그런데, 클래스가 평가되어 생성된 함수 객체나 클래스가 생성한 인스턴스 중 어디에도, 그 내부 프로퍼티 어트리뷰트를 까 봤을 때 constructor 메서드는 없다. 즉 constructor은 단순한 메서드가 아니다. 

> constructor은 메서드가 아니라, 클래스가 평가되어 생성된 `함수 객체 코드의 일부`가 된다. 즉 클래스가 평가되면 constructor의 동작을 하는 클래스(함수 객체)가 생성되는 것이다.
> 

### constructor이 생성자 함수와 다른 점

1. 클래스 내에 한 개만 존재 가능 : 2개 이상이면 SyntaxError
2. 생략 가능 : 생략 시 클래스에 빈 constructor가 암묵적 정의됨. 단, 외부에서 초깃값을 전달하여 인스턴스를 (프로퍼티 추가를 통해)초기화하려면 반드시 constructor 내부에 해야 하므로 이 경우에는 생략 불가능

이 외에는 별도의 객체 변환문을 가지면 안 된다는 점은 똑같다.(암묵적 this 반환이 이루어질텐데 망침) return 문은 반드시 생략하도록 !!!

## 프로토타입 메서드

명시적으로 선언(Person.prototype.sayHi() 처럼)해야 했던 생성자 함수의 프로토타입 메서드와는 달리, 클래스 내부에서 정의한 메서드는 **기본적으로** 클래스의 프로토타입 메서드가 된다.

클래스가 생성한 인스턴스는 프로토타입 체인의 일원이 되며, 생성된 인스턴스는 프로토타입 메서드를 상속받아 사용할 수 있다. 즉 결국,

> `클래스`는 인스턴스를 생성하는 `생성자 함수`이며 프로토타입 기반의 `객체 생성 메커니즘`이다.
> 

## 정적 메서드

정적 static 메서드는 `인스턴스를 생성하지 않아도` 호출할 수 있는 메서드를 의미하며, 생성자 함수의 경우 명시적으로 생성자 함수의 프로퍼티로써 메서드를 추가하지만 클래스의 경우 클래스 몸체에서 static 키워드를 붙여 정의한다.

정적 메서드는 프로토타입 메서드처럼 인스턴스로 호출하지 못한다. (정적 메서드는 클래스의 프로퍼티로써 바인딩되며, 인스턴스의 프로토타입 체인에 존재하지 않기 때문) 클래스 자체로 호출한다.

## 프로토타입 메서드 vs 정적 메서드

> 프로토타입 메서드와 정적 메서드의 차이점
> 
1. 속해 있는 프로토타입 체인이 다르다
2. 프로토타입 메서드 : `인스턴스`로 호출 / 정적 메소드 : `클래스`로 호출
3. 프로토타입 메서드 → 인스턴스 프로퍼티 참조 가능 / 정적 메서드 → 불가능

아니 이건 당연한건데

프로토타입 메서드는 이후에 생성될 인스턴스가 상속받아 사용할, 인스턴스를 위한 메서드이고 걔네랑 프로토타입 체인을 결성함. public이지. 인스턴스로 호출해야 함

정적 메서드는 생성자 함수 자체의 프로퍼티기 때문에 private임. 즉 생성자 함수만이 다룰 수 있다는 소리이고 프로토타입 체인에 포함되지 않으니 인스턴스랑도 연관이 없지.

즉 애초부터 둘 내부의 `this바인딩`이 다름

- 인스턴스 프로퍼티를 참조해야 한다면 프로토타입 메서드를 사용한다
- 정적 메서드를 하나의 네임스페이스(클래스 or 생성자 함수)에 모아놓으면 이름 충돌도 막고 관련된 함수들끼리 구조화할 수 있음. 예를 들어,표준 빌트인 객체(Number, Object, Math 등)는 다양한 정적 메서드를 가지고 있으며 전역 유틸리티 함수로써 꽤나 유용함.

## 클래스에서 정의한 메서드의 특징

1. 메서드 축약 표현 사용 (function 키워드 생략)
2. 콤마 필요 x
3. 암묵적으로 strict mode로 실행됨
4. 열거 불가능
5. non-structor임 (new와 함께 호출 불가능)

## 클래스의 인스턴스 생성 과정

new 연산자와 함께 클래스를 호출하면 내부 메서드 [[Constructor]]가 호출되며, 다음과 같은 과정을 거쳐 인스턴스가 생성된다. (생성자 함수와 상당히 유사하다.)

```jsx
// 클래스
class Person {
    // 생성자
    constructor(name) {
        // 1. 암묵적으로 인스턴스(완성되지 않은, 미래에 생성될 빈 객체)생성 + this 바인딩
        console.log(this);
        console.log(Object.getPrototypeOf(this) === Person.prototype);
    
        // 2. this 에 바인딩된 인스턴스 초기화
        this.name = name;
    }
    // 3. 완성된 인스턴스가 바인딩된 this가 암묵적으로 반환됨
}
```

1. 인스턴스 생성 + this 바인딩

new 연산자와 함께 클래스 호출 → 내부 코드 실행에 앞서 암묵적으로 빈 객체(완성되지는 않았지만, 클래스가 생성한 인스턴스) 생성 → 클래스가 생성한 인스턴스의 프로토타입 설정(prototype 프로퍼티가 가리키는 객체 설정) → this 바인딩(constructor 내부의 this가 생성된 인스턴스 가리킴)

1. 인스턴스 초기화

constructor 내부 코드가 실행되어 this에 바인딩되어 있는 인스턴스 초기화 (프로퍼티 초기화 or 인수로 전달받은 초기값으로 프로퍼티 초기화) constructor가 생략되었다면 이 단계는 생략

1. 인스턴스 반환

완성된 인스턴스가 바인딩된 this가 암묵적 반환됨

# 프로퍼티

## 인스턴스 프로퍼티

> `constructor 내부`에서 정의해야 한다.
> 

바로 앞에서 살펴보았듯이, constructor 내부 코드가 실행되기 전 constructor 내부의 this에는 이미 클래스가 생성할 인스턴스(빈 객체)가 바인딩되어 있다. constructor 내부의 this에 인스턴스 프로퍼티를 추가하면 인스턴스가 초기화된다.

- constructor 내부에서 this에 추가한 프로퍼티는 항상 `클래스가 생성한 인스턴스의 프로퍼티`이다.
- 인스턴스 프로퍼티는 항상 `public`하다. 접근 제한자를 지원하지 않기 때문이다.

## 접근자 프로퍼티

자체적으로 값(내부 슬롯 [[Value]])을 갖지 않고, 다른 데이터 프로퍼티의 값을 읽거나 저장할 때 사용되는 `접근자 함수(accerssor function)`로 구성된 프로퍼티

```jsx
// 인스턴스 프로퍼티
class Person {
    constructor(name) {
        this.name = name;   // public
    }
}

const me = new Person(`kang`);
console.log(me.name);   // kang

// 접근자 프로퍼티
class Human {
    constructor(firstName, lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
    }

    // 접근자 프로퍼티 fullName
    // 접근자 함수로 구성되어 있다

    // getter 함수
    get fullName() {
        return `${this.firstName} ${this.lastName}`;
    }

    // setter 함수
    set fullName(name) {
        [this.firstName, this.lastName] = name.split(` `);
    }
}

// 초깃값을 artguments로 전달하며 인스턴스 생성
const human = new Human(`jung`, `woo`);

// 데이터 프로퍼티로 프로퍼티 값 참조
console.log(`${me.firstName} ${me.lastName}`);

// 접근자 프로퍼티로 프로퍼티 값 참조

// 접근자 프로퍼티 fullName에 값 저장 -> setter 함수 호출
me.fullName(`mark lee`);
// 접근자 프로퍼티 fullName에 접근 -> getter 함수 호출
console.log(me.fullName);
```

- 인스턴스 프로퍼티에 접근할 때 마다 별도의 행위를 추가로(프로퍼티 값을 조작하는 등) 해야할 때 사용되며, `getter 함수`와 `setter 함수`로 이루어져 있다.
- getter와 setter은 명시적으로 호출하는 것이 아닌, 각각 `get`과 `set` 키워드를 메서드 앞에 붙여 호출하며, 사용시에도 참조 시 내부적으로 호출되는 식으로 사용된다.
- `getter`은 반드시 무언가를 **반환**해야 하고, `setter`은 반드시 **매개변수**가 있어야(외부에서 값을 받아 프로퍼티에 할당해야 하므로) 한다
- 클래스의 메서드는 static으로 선언하지 않는 이상 기본적으로 프로토타입 메서드가 되므로, 클래스의 접근자 프로퍼티 또한 인스턴스 프로퍼티가 아닌 `프로토타입 프로퍼티`이다.