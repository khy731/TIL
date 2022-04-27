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

# 클래스 필드 정의 제안

> 클래스 필드(class field)란?
> 

클래스 필드(클래스 멤버)란, 클래스 기반 객체지향 언어에서 클래스가 생성할 인스턴스의 프로퍼티를 가리킨다. 자바 등의 언어에서는 이를 변수처럼 사용할 수 있지만 자바스크립트의 경우 반드시 클래스 내부의 constuctor 내부의 this로만 조작이 가능하다. 또한 자바스크립트의 클래스는 메서드만 정의 가능하기 때문에 자바처럼 클래스 필드를 선언하면 에러가 뜬다. 그런데...

## 클래스 필드 정의 제안 Clss field declarations

자바스크립트에서도 인스턴스 프로퍼티를 마치 클래스 기반 객체지향 언어의 클래스 필드처럼 정의할 수 있는 새로운 표준 사양. 아직 정식 표준 사양으로 승급되지는 않았지만, 거의 확정된 사항이기 때문에 최신 브라우저와 Node.js에서는 선제적으로 미리 구현해놓은 상태이다.

즉, 1. constructor 내부에 2. `**this` 를 사용하지 않고도 인스턴스 프로퍼티 추가가 가능**하다!

```jsx
class Person {
    // 클래스 필드
    // constructor 내부의 this를 참조하지 않고도 인스턴스 프로퍼티 접근 가능

    // 초깃값 有
    name = `kang`;
    // 초깃값 無
    age;

    // constructor 외부이므로 this는 사용 불가
    /* this.name = `kang`; */

    constructor() {
        // 참조할 때는 this를 꼭 사용해야 한다
        /* console.log(name); */    // ReferenceError: name is not defined

        console.log(this.name);    // kang
        console.log(this.age);     // undefined
    }

}

new Person();
```

- 외부값으로 초기화를 해야 하는 경우에는 쓸모가 없다

인스턴스를 생성할 때, 외부에서 arguments로 받은 값으로 클래스 필드를 초기화해야 한다면 constructor에서 this를 사용해서 해야 한다. 즉, 외붓값으로 초기화 하고 싶으면 굳이 constuctor 밖에서 클래스 필드를 정의할 필요가 없다(...)

- 클래스 필드에서 메서드의 기본값은 프로토타입 메서드가 아닌 `인스턴스 메서드`이다

모든 클래스 필드는 인스턴스 프로퍼티가 되기 때문에, 클래스 필드에 함수를 할당하는 것은 권장하지 않는다 (this.name이 아니라 name을 참조하는 메서드는 클래스 필드의 메서드이다)

```jsx
class Person {
    // 클래스 필드에 문자열 할당
    name = `kang`;

    // 클래스 필드에 함수 할당
    // 생성자 함수의 기본값(프로토타입 메서드)와 달리
    // 기본값이 인스턴스 메서드이다
    getName = function() {
        return this.name;
    }
    // 화살표 함수 표현
    // getName = () => this.name;
}

const me = new Person();
console.log(me);    // Person { name: 'kang', getName: [Function: getName] }
console.log(me.getName());     // kang
```

> `클래스 필드 정의 제안`은 인스턴스 프로퍼티를 정의하는 새로운 방식이다.
> 

인스턴스 생성 시 외부 초기값으로 클래스 필드 초기화가

- 필요한 경우 → 기존 방식 (contructor 내부 this)
- 불필요한 경우 → 클래스 필드 정의 제안 (그냥 쓰기)

## private 필드 정의 제안

자바스크립트는 캡슐화(정보 은닉)를 완전하게 지원하지 않고, 이는 클래스 필드에서도 마찬가지다. 인스턴스 프로퍼티와 클래스 필드 둘 다 기본적으로 public이다. 그러나 `private 필드 정의 제안`을 사용하면 이를 구현할 수 있다.

> private 필드의 선두에는 `#`을 붙이며, private 필드를 참조할 때도 `#`를 붙인다.
> 

 

```jsx
// 기존 방법 (public)
class Person1 {
    constructor(name) {
        this.name = name;   // public
    }
}
const me1 = new Person1();
console.log(me1.name);

// 클래스 필드 정의 제안 (public)
class Person2 {
    name = `kang`;    // public
}
const me2 = new Person2();
console.log(me2.name);

// private 필드 정의 제안
class Person3 {
    #name = ` `;

    constructor(name) {
        this.#name = name;
    }
}
const me3 = new Person3();

// 외부 접근 불가능
console.log(me3.#name);    // SyntaxError: Private field '#name' must be declared in an enclosing class
```

private 필드는 오직 `클래스 내부`에서만 참조 가능하며, 자식 클래스나 클래스 인스턴스 그 누구도 참조 불가능하다.

단, `접근자 프로퍼티`를 사용하여 간접적으로 접근할 수는 있다.

## static 필드 정의 제안

클래스는 static 키워드를 사용하여 `정적 메서드`를 정의할 수는 있지만 `정적 필드`는 정의할 수 없었다. 그러나 최신 표준 사양에서

> static 필드는 `static`키워드로 구현 가능하다
> 

```jsx
class myMath {
    // static public 필드 정의
    static PI = 22/7;

    // static private 필드 정의
    static #num = 10;

    // static 메서드
    static increment() {
        return ++myMath.#num;
    }
}

// 정적(static) 필드는 인스턴스로 접근 불가능
// 클래스로 직접 접근한다
console.log(myMath.PI);    // 3.142857142857143
console.log(myMath.increment());    // 11
```

# 상속 : 클래스 확장

프로토타입 기반 상속이 프로토타입 체인을 통해 다른 객체의 자산을 상속받는 개념이라면, 상속에 의한 클래스 확장은 `기존 클래스를 상속받아 새로운 클래스를 확장(extends)`하여 정의한다.

```jsx
class Animal {
    constructor(name, age) {
        this.name = name;
        this.age = age;
    }
    eat() {
        return `eat`;
    }
    mobe() {
        return `move`;
    }
}

class Dog extends Animal {
    sleep() {
        return `sleep`;
    }
}

const dog = new Dog();
```

![inheritance-prototype-chain](https://user-images.githubusercontent.com/97890886/165516363-4b74ac38-0db0-49f1-8818-b82e725cadf9.png)


## extends

상속받을 클래스를 지정한다. 슈퍼 클래스와 서브 클래스 간의 상속 관계를 설정한다. 

```jsx
// super, base, 부모 클래스
class Base { }

// sub, derived, 자식 클래스
class Derived extends Base { }
```

- 서브 클래스 : 상속을 통해 확장된 클래스
- 슈퍼 클래스 : 서브 클래스에게 상속된 클래스

클래스도 프로토타입 체인을 통해 상속 관계를 구현하며, 클래스 간의 상속은 `인스턴스`의 프로토타입 체인뿐만 아니라 `클래스`간의 프로토타입 체인도 생성한다.

![class-chain](https://user-images.githubusercontent.com/97890886/165516439-0069ee36-d39e-49ea-9624-9ade849b456c.png)

## 동적 상속

extends 키워드 다음에는 클래스뿐만 아니라 [[constructor]] 내부 메서드를 갖는, 함수 객체로 평가될 수 있는 모든 표현식을 사용할 수 있다. 이를 이용하여 동적으로 상속받을 대상을 결정해보자.

```jsx
// 슈퍼 클래스 1
function Base1();
// 슈퍼 클래스 2
class Base2 {}

// 조건
let condition = true;

// 서브 클래스
// 조건에 따라 동적으로 상속 대상을 결정
class Derived extends (condition ? Base1 : Base2) {}

const derived = new Derived();
console.log(derived);
```

## 서브 클래스의 constructor

클래스에서 constructor을 생략하면 비어 있는 constructor가 암묵적으로 정의된다.

```jsx
constructor() { }
```

서브 클래스의 constructor을 생략하면 다음과 같이 암묵적으로 정의된다.

```jsx
constructor(...args) {super(...args);}
```

- ... : Rest 파라미터, 함수에 전달된 인수들의 목록을 배열로 전달받는다
- args : new 연산자와 함께 클래스를 호출할 때 전달한 인수의 리스트
- super() : 슈퍼 클래스의 constructor(super-constructor)를 호출하여 인스턴스 생성

## super 키워드

함수처럼 호출할 수도 있고, 식별자처럼 참조할(마치 this처럼) 수도 있는 특수한 키워드.

### super 호출

> super 호출 → 슈퍼 클래스의 constructor(super-constructor) 호출
> 

일종의 프로퍼티 내려받기 개념 (constructor 내부)

```jsx
// new 연산자와 함께 서브 클래스를 호출하면서 전달한 인수는
// constructor의 super 호출을 통해 수퍼클래스의 constructor에 전달됨
// 즉, 인스턴스 초기화를 위해 전달한 인수는 수퍼클래스와 서브클래스에 분배되고
// 상속 관계의 두 클래스가 서로 협력해서 인스턴스를 만든다고 할 수 있음
// 인수 전달과 함께 클래스를 new로 호출 -> 서브 클래스의 constructor에 전달 -> 내부의 super 호출 -> 수퍼 클래스의 constructor

// 수퍼 클래스의 constructor 내부 프로퍼티를 그대로 갖는 인스턴스
// - constructor 생략 가능 (암묵적 생성됨)
class Base1 {
    constructor(a,b) {
        this.a = a;
        this.b = b;
    }
}

class Derived1 extends Base1 {
}

const derived1 = new Derived1(0,0);
console.log(derived1);    // Derived1 { a: 0, b: 0 }

// 수퍼 클래스의 프로퍼티와 서브 클래스의 프로퍼티를 갖는 인스턴스
// - constructor 생략 불가능
class Base2 {
    constructor(a,b) {
        this.a = a;
        this.b = b;
    }
}

class Derived2 extends Base2 {
    constructor(a,b,c) {
        super(a,b);
        this.c = c;
    }
}

const derived2 = new Derived2(1,2,3);
console.log(derived2);    // Derived2 { a: 1, b: 2, c: 3 }
```

수퍼 클래스의 constructor 내부에 추가한 프로퍼티를 그대로 갖기만 하는 복제품 인스턴스를 생성한다면 서브클래스의 constructor을 생략할 수 있다. (위에서 봤던 대로)

그러나, 추가로 뭔갈 더 얹어서 만들고 싶다면 당연하게도 서브 클래스의 constructor 내부에 프로퍼티를 추가해야 할 것이다. 이 때 수퍼 클래스의 프로퍼티들을 상속받는 것을 명시해주는 것이 바로 super 키워드이다.

- **서브 클래스에서 constructor을 생략하지 않는 경우,** 서브 클래스의 constructor에서는 **반드시 super을 호출**해야 한다.
- 서브 클래스의 constructor에서 super을 호출하기 전에는 this 참조가 불가능하다
- super은 반드시 **서브 클래스의 constructor**에서만 호출한다. 다른 곳에서는 Error 뜬다

### super 참조

> 메서드 내에서 super 참조 → 수퍼 클래스의 메서드 호출 가능
> 

일종의 메서드 내려받기 개념 (프로토타입 메서드)

```jsx
class Base {
    constructor(name) {
        this.name = name;
    }
    sayHi() {
        return `Hi, ${this.name}!`;
    }
}

class Derived extends Base {
    sayHi() {
        // super 참조
        // super.sayHi는 수퍼 클래스의 프로토타입 메서드이다
        return `${super.sayHi()} what's up?`;
    }
}

const hello = new Derived(`kang`);
console.log(hello.sayHi());    // Hi, kang! what's up?
```

- super은 자신을 참조하고 있는 메서드(Derived의 sayHi)가 바인딩되어있는 객체(Derived.prototype) -메서드 sayHi는 static으로 선언하지 않았으므로 기본적으로 프로토타입 메서드이다- 의 프로토타입(Base.prototype) -위 그림에서 인스턴스 프로토타입 체인 참고-을 가리킨다.

> 즉, `super.sayHi`는 `Base.prototype.sayHi`를 가리킨다.
> 

이 로직을 super를 사용하지 않고 나타내면 다음과 같다.

```jsx
class Animal {
    constructor(gender) {
        this.gender = gender; 
    }

    sheOrHe() {
        return `my animal is ${this.gender}`;
    }
}

class Cat extends Animal {
    myAnimal() {
        // super 키워드와 동일하게 동작한다
        // super은 자신을 참조하는 메서드(프로토타입 메서드)가 바인딩된 객체(서브클래스의 프로토타입)의 프로토타입(수퍼클래스의 프로토타입)을 가리킨다
        // __super도 서브클래스의 프로토타입의 프로토타입 === 수퍼 클래스의 프로토타입을 가리킨다
        const __super = Object.getPrototypeOf(Cat.prototype);   // === Animal.prototype
        return `${__super.sheOrHe.call(this)}, and so cute!`;
    }
}

const cat = new Cat(`she/her`);
console.log(cat.myAnimal());    // my animal is she/her, and so cute!
```

이 때 call 메서드와 함께 this를 전달하지 않고 그냥 Animal.prototype.sheOrHe()를 그대로 호출하면 sheOrHe()내부의 this는 Animal.prototype만을 가리키게 되므로(더이상 인스턴스를 가리키지 않으므로) 반드시 자신을 바인딩하고 있는 객체를 기억하고, 그 객체의 프로토타입을 찾을 수 있어야 한다.

> 메서드 내부 슬롯 [[HomeObject]] 를 사용 : 자신을 바인딩하고 있는 객체를 가리킴
> 

즉, `super 참조`의 의사 코드는 다음과 같다.

```jsx
super = Object.getProtoytype([[HomeObject]])
```

단, **ES6 메서드 축약 표현으로 정의된 함수만이 내부 슬롯 [[HomeObject]]를 갖는다**.

[[HomeObject]]를 갖는 함수만이 super 참조를 할 수 있기 때문에 ES6 메서드 축약표현으로 정의된 함수만이 super 참조를 할 수 있다고 보면 되겠다. 그러니까 한마디로 말하자면 `서브클래스의 메서드`에서 `수퍼클래스의 메서드`를 참조할 때 써라! (정적 메서드도 가능하다!)

super 참조는 클래스만의 전유물이 아니며, 객체 리터럴에서도 가능하다. 물론 ES6 메서드 축약표현으로 정의된 함수만.

# 상속 클래스의 인스턴스 생성 과정

클래스의 인스턴스 생성 과정은 생성자 함수와 유사하고 간단했다. 상속 관계의 두 클래스는 어떻게 협력하며 인스턴스를 생성하는가?

```jsx
// 직사각형을 추상화한 Rectangle
// 상속으로 클래스 확장 : ColorRectangle

// 수퍼 클래스
class Rectangle {
    constructor(width, height) {
        this.width = width;
        this.height = height;
    }

    getArea() {
        return this.width * this.height;
    }

    toString() {
        return `너비 = ${this.width}, 높이 = ${this.height}`;
    }
}

// 서브 클래스
class ColorRectangle extends Rectangle {
    constructor(width, height, color) {
        super(width, height);
        this.color = color;
    }
    
    // 메서드 오버라이딩
    toString() {
        return `너비 = ${this.width}, 높이 = ${this.height}, 색 = ${this.color}`;
    }
}

const colorRectangle = new ColorRectangle(10,20,`yellow`);
console.log(colorRectangle.toString());    // 너비 = 10, 높이 = 20, 색 = yellow
```

서브클래스 ColorRactangle이 new 연산자와 함께 호출되어 인스턴스를 생성하는 과정을 알아보자.

## 1. 서브클래스의 super 호출

자바스크립트 엔진은 수퍼클래스와 서브클래스를 `내부 슬롯 [[ConstructokrKind]]`으로 구분한다.

- 다른 클래스를 상속받지 않는 클래스(와 생성자 함수) : base
- 다른 클래스를 상속받는 클래스 : derived

전자 (`수퍼 클래스`)는 new 연산자와 함께 호출될 경우 암묵적으로 빈 객체(인스턴스)를 생성하고 이를 this에 바인딩하여 반환한다. 그러나

> **서브 클래스는 자신이 직접 인스턴스를 생성하지 않고 수퍼 클래스에게 이를 위임한다.**
> 

이는 곧 서브 클래스의 constructor에 반드시 super을 호출해야 하는 이유이다.

1. 서브클래스가 new 연산자와 함께 호출
2. 서브클래스 constructor 내부의 super 키워드가 (마치 함수처럼)호출
3. 수퍼클래스의 constructor이 호출됨(평가되어 함수 몸체의 코드 실행됨)

## 2. 수퍼클래스의 인스턴스 생성 & this 바인딩

수퍼클래스의 constructor 내부 코드가 실행되기 전 암묵적으로 빈 객체(미완성이지만 클래스가 미래에 생성할 녀석)를 생성하고 이를 this에 바인딩한다.

> 실질적인인스턴스는 수퍼클래스가 생성하지만, new 연산자와 함께 호출된 클래스가 서브클래스일 경우 **서브클래스가 생성한 것으로 처리**된다.
> 

생성된 인스턴스의 프로토타입은 수퍼클래스의 prototype 프로퍼티가 가리키는 객체가 아닌, 서브클래스의 prototype 프로퍼티가 가리키는 객체다.

## 3. 수퍼클래스 인스턴스 초기화

수퍼클래스의 constructor이 실행되어 this에 바인딩되어 있는 인스턴스를 초기화한다.  프로퍼티를 추가하고 constructor가 인수로 전달받은 초깃값 등으로 초기화.

## 4. 서브클래스 constructor로의 복귀 & this 바인딩

super 호출 종료. 제어 흐름이 수퍼클래스 constructor → 서브클래스 constructor로 돌아온다.

> super가 반환한 인스턴스가 this에 바인딩된다. 서브클래스는 인스턴스를 생성하지 않으며 이를 그대로 쓴다.
> 

**super이 호출되지 않으면 인스턴스가 생성되지 않으며, this바인딩도 불가능하다.** 서브클래스 constructor에서 super 호출 전까지 this 참조가 불가능한 이유가 바로 이것이다.

## 5. 서브클래스 인스턴스 초기화

서브클래스의 constructor이 실행되어 this에 바인딩되어 있는 인스턴스를 초기화한다. 프로퍼티를 추가하고 constructor가 인수로 전달받은 초깃값 등으로 초기화.

## 6. 인스턴스 반환

클래스의 모든 처리가 끝나면 완성된 인스턴스가 바인딩된 this가 암묵적으로 반환된다.

```jsx
class Rectangle {
    // 3. 수퍼 클래스가 실행되기 전 암묵적으로 빈 객체가 평가되어 생성되고
    // this에 바인딩된다
    constructor(width, height) {
        // 4. 인스턴스가 초기화된다
        this.width = width;
        this.height = height;
    }

    getArea() {
        return this.width * this.height;
    }

    toString() {
        return `너비 = ${this.width}, 높이 = ${this.height}`;
    }
}

class ColorRectangle extends Rectangle {
    constructor(width, height, color) {
        // 2. 서브 클래스 constructor이 실행되기 전 super가 호출된다
        // 제어 흐름 : 서브 클래스 constructor -> 수퍼 클래스 constructor
        super(width, height);

        // 5. super 호출이 끝나고 super가 반환한 인스턴스를 this에 바인딩에 그대로 사용한다

        // 6. 인스턴스 초기화
        this.color = color;
    }
    
    // 메서드 오버라이딩
    toString() {
        return `너비 = ${this.width}, 높이 = ${this.height}, 색 = ${this.color}`;
    }

    // 7. 완성된 인스턴스가 바인딩된 this가 암묵적 반환된다
}

// 1. 서브 클래스가 new 연산자와 함께 호출된다
const colorRectangle = new ColorRectangle(10,20,`yellow`);
console.log(colorRectangle.toString());    // 너비 = 10, 높이 = 20, 색 = yellow
```

# 표준 빌트인 생성자 함수 확장

extends 키워드 다음에는 클래스뿐만 아니라 내부 메서드 [[Construct]] 를 갖는 함수 객체로 평가되는 모든 표현식이 올 수 있다. 다음과 같은 표준 빌트인 생성자 함수도 가능하다 :

- String
- Number
- Array

즉, 기본적이고 폭넓으며 강력한 기능을 제공하는 표준 빌트인 생성자 함수에 부가 기능을 추가하여 클래스 상속으로 확장시킨다는 것.

```jsx
// 표준 빌트인 생성자 함수 Array()를 상속받아 확장한 서브 클래스 MyArray
class MyArray extends Array {
    // 중복 배열 요소를 제거하고 반환
    uniq() {
        return this.filter((v,i,self) => self.indexOf(v) === i);
    }
    // 모든 배열 요소의 평균 반환
    averge() {
        return this.reduce((pre,cur) => pre+cur)/this.length;
    }
}

const myarray = new MyArray(1,1,2,3);
console.log(myarray.uniq());    // MyArray(3) [ 1, 2, 3 ]
console.log(myarray.averge());  // 1.75
```

Array 생성자 함수를 상속받아 확장한 MyArray 클래스가 생성한 인스턴스는 Array.prototype과 MyArray.prototype의 모든 메서드를 사용 가능하다.