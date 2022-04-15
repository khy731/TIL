# 자바스크립트는 프로토타입 기반의 OOP 언어

자바스크립트는 명령형 imperative, 함수형 functional, 프로토타입 기반 prototype-based 객체지향 프로그래밍 OOP; object oriented programming 을 지원하는 멀티 페러다임 프로그래밍 언어다. 즉, **자바스크립트를 이루고 있는 거의 모든 것이 객체**이며 원시 타입의 값을 제외한 나머지 값들-함수, 배열, 정규 표현식 등을 포함하여-은 전부 객체이다.

# OOP

명령형, 절차지향형 프로그래밍에서 벗어나 여러개의 독립적 단위(객체)의 집합으로 프로그래밍을 표현하는 것.

- 다양한 속성 중 프로그램에서 필요한 속성만 간추려 내는 `추상화`를 사용
- 속성을 통해 여러 개의 값을 하나의 단위로 구성한 복합적인 자료구조인 `객체` 사용

객체에는 상태를 나타내는 데이터(프로퍼티)와 상태 데이터를 조작하는 동작(메서드)가 있다. 결국 객체는 상태 데이터와 동작을 하나의 논리적인 단위로 묶은 복합적인 자료구조이다.

# 상속, 프로토타입

상속 inheritance은 OOP의 핵심 개념으로, 자바스크립트는 프로토타입을 기반으로 상속을 구현하여 불필요한 중복을 제거한다. - 이는 곧 코드 재사용이며 유지 보수에 유리하다.

예를 들어 생성자 함수를 봤을 때, 중복된 동작을 줄일 수 있어 일반 함수보다는 유용해 보였으나 이들은 new 연산자와 함께 호출될 때마다 인스턴스(객체)를 새로 만들기 때문에 모든 인스턴스에 동일한 내용의 메서드가 중복 생성되게 된다. 이는 메모리적으로 낭비이며, 퍼포먼스에도 악영향이다.

그러나 프로토타입 기반의 상속으로 이 기능을 구현하면 이 문제가 해결된다.

```jsx
// 생성자 함수
function Circle(radius) {
    this.radius = radius;
}

// prototype은 Circle 생성자 함수의 prototype 프로퍼티에 바인딩되어 있다
// Circle 생성자 함수가 생성한 모든 인스턴스(객체)의 부모가 된다
Circle.prototype.getDiameter = function() {
    return Math.PI * 2 * this.radius;
};

// 인스턴스(객체) 생성
const circle = new Circle(5);
const circle2 = new Circle(10);

// Circle 생성자 함수가 생성한 모든 인스턴스는
// prototype(부모 객체)의 getDiameter 메서드를 공유한다
console.log(circle.getDiameter === circle2.getDiameter);    // true

console.log(circle.getDiameter());      // 10
console.log(circle2.getDiameter());     // 20
```

Circle 생성자 함수가 생성한 모든 인스턴스는 자신의 프로토타입(상위-부모 객체) 역할을 하는 Circle.prototype의 모든 프로퍼티와 메서드를 상속받는다. 이때 이 부모 객체의 메서드는 단 한 번만 생성되어 Circle.prototype의 메서드로 이미 할당되어 있기 때문에 자식들은 상속을 통해 공유하며 사용한다.

# 프로토타입 객체

상속을 구현하는 데에 사용된다. 자바스크립트는 프로토타입을 기반으로 상속을 구현하는데, 프로토타입은 어떤 객체의 부모 객체 의 역할을 하는 객체로써 다른 객체에 공유 프로퍼티/메서드를 제공한다.

> 모든 객체는 [[prototype]]이라는 내부 슬롯을 가지며, 이 내부 슬롯의 값은 `프로토타입의 참조`다.
> 

여기 저장되는 프로토타입은 객체 생성 방식에 의해 결정된다. 예를 들어,

- 객체 리터럴로 생성한 객체의 프로토타입 : Object.prototype
- 함수에 의해 생성된 객체의 프로토타입 : 생성자 함수의 prototype 프로퍼티에 바인딩 되어있는 객체이다(위에 Circle.prototype 과 같은 경우를 말하는 것이다)

모든 프로토타입은 생성자 함수와 연결되어 있으며, 생성자 함수에 의해 생성된 모든 객체(인스턴스)는 하나의 프로토타입을 갖는다.

![prototype1](https://user-images.githubusercontent.com/97890886/163559160-f41135b7-42b8-47f4-9846-dc2cee8bdd31.png)


- 생성자 함수는 prototype 프로퍼티를 통해 프로토타입에 접근 가능
- 프로토타입은 constructor 프로퍼티를 통해 생성자 함수에 접근 가능
- 객체는 내부 슬롯인 [[prototype]] 에는 직접적으로 접근할 수 없지만, __proto__ 접근자 프로퍼티를 통해 [[prototype]] 내부 슬롯의 값(===[[prototype]] 내부 슬롯이 가리키는 프로토타입)에 적븐 가능

# __proto__

모든 객체는 이 접근자 프로퍼티를 통해 자신의 프로토타입([[prototype]] 내부 슬롯)에 간접적으로 접근 가능하다.

## 접근자 프로퍼티로써의 역할

`내부 슬롯`은 프로퍼티가 아니라 내부 로직 동작을 설명한 것이기 때문에([프로퍼티 어트리뷰트](https://github.com/KangHyeYoon/TIL/blob/main/Javascript/property-attribute.md 참고) 원칙적으로는 내부 슬롯과 내부 메서드에 직접적인 접근, 호출이 불가능하다. __proto__는 간접적으로 내부 슬롯의 값(프로토타입)에 접근할 수 있게 한다.

접근자 프로퍼티는 자체적으로는 값([[Value]] 프로퍼티 어트리뷰트)을 갖지 않는 대신 데이터 프로퍼티의 값을 읽거나 저장할 때 사용하는 `접근자 함수`([[Get]], [[Set]] 프로퍼티 어트리뷰트에 할당된 함수)를 통해 [[prototype]] 내부 슬롯의 값(프로토타입)을 취득하거나, 할당한다.

이 때 내부적 동작은 다음과 같다.

1. __proto__ 접근자 프로포티를 통해 프로토타입에 접근하면
2. 내부적으로 __proto__ 접근자 프로퍼티의 getter 함수인 [[Get]]이 호출된다.

새로운 프로퍼티를 할당할 때에도 Set으로 같은 동작이 일어난다.

## 상속을 통해 사용

__proto__ 접근자 프로퍼티는 객체가 직접 소유하는 프로퍼티가 아니라, `Object.prototype`의 프로퍼티이므로 모든 객체는 상속의 원리를 따라, Object.prototype.__proto__ 형식으로 __proto__ 접근자 프로퍼티를 사용할 수 있다.

```jsx
const me = {
    name: `kang`,
};

// 객체(자식)에 proto 접근자 프로퍼티가 존재하는 것은 아니다
console.log(me.hasOwnProperty(`__proto__`));    // false

// 모든 객체의 프로토타입 객체(부모)인 Object.prototype의 것이다
console.log(Object.getOwnPropertyDescriptor(Object.prototype, `__proto__`));
/*
{
  get: [Function: get __proto__],
  set: [Function: set __proto__],
  enumerable: false,
  configurable: true
}
*/

// 객체에 __proto__ 로 접근하는 것 === 프로토타입에 접근하는 것
// 모든 객체는 Object.prototype의 접근자 프로퍼티 __proto__ 를 상속받아 사용 가능
console.log({}.__proto__ === Object.prototype);     // true
```

## 상호 참조에 의한 비정상적인 프로토타입 체인을 방지

프로토타입은 부모 객체이다. 상속은 항상 `단방향`이어야 한다. 만약 자식이 부모를 부모삼은 후, 부모가 자식을 부모삼아서 상호 참조에 의한 비정상적인 프로토타입 체인이 만들어졌다면? 그건안됨. 

프로토타입 체인은 자식에서 부모로 올라가면서 검색하는, 검색 방향이 한쪽으로만 흐르는 단방향 linked-list인데, 이렇게 순환 참조를 하는 프로토타입이 만들어지면 체인의 종점이 없디 때문에 프로토타입을 검색하는 과정에서 무한 루프에 빠져버리게 된다.

즉, 아무런 체크 없이 상속 관계를 결정하거나 수정하는 것을 방지하기 위해 __proto__ 접근자 프로퍼티를 사용하는 것이다.

## 코드 내에서 직접 사용하는 것은 비추천

> 모든 객체가 __proto__ 접근자 프로퍼티를 사용할 수 있는 것은 아니다
> 

__proto__를 쓰려면, 모든 객체가 Object.prototype을 상속(자식)한다는 전제가 맞아야 하는데, `직접 상속`을 통해 객체를 생성하면 Object.prototype을 상속받지 않을 수 도 있다. 이 경우 다음과 같은 메서드를 사용한다.

```jsx
const obj1 = { a : 1, };
const obj2 = Object.create(null);

console.log(obj1.__proto__);    // [Object: null prototype] {}
console.log(obj2.__proto__);    // undefined

console.log(Object.getPrototypeOf(obj2));   // null
```

이 두 메서드를 사용하여 __proto__ 접근자 프로퍼티 대신 프로토타입의 참조를 취득하거나 교체할 수 있다.

```jsx
const obj1 = {};
const obj2 = { name : `kang`,}

// obj1의 프로토타입 취득(get)
Object.getPrototypeOf(obj1);

// obj1의 프로토타입으로 obj2를 지정(set)
Object.setPrototypeOf(obj1, obj2);

console.log(obj1.name);     // kang
```

이 두 메서드는 __proto__를 사용했을 때와 내부 처리 동작 과정이 정확히 일치한다.

# 함수 객체의 prototype 프로퍼티

> 함수 객체 고유의 prototype 프로퍼티는 `생성자 함수`가 생성할 인스턴스의 프로토타입을 가리킨다.
> 

이 말은 즉, non-constructor 인 함수 객체(화살표, 축약표현 메서드)는 prototype을 소유하지 않을 뿐더러 프로토타입도 생성하지 않는다는 소리이다.

모든 객체(call)는 Object.prototype을 프로토타입으로 삼지만, 함수인 객체(call이자 constructor)는 기본적으로 생성자 함수로써 동작할 가능성을 가지고 있기 때문에(선언 방식이 일반 함수와 동일하며, 화살표와 축약메서드가 아님) 애초부터 생성자 함수가 미래에 new와 함께 호출되어 생성하게 될 객체(인스턴스)의 프로토타입을 가리키게 된다.

즉, 생성자 함수를 바탕으로 이후 생성될 객체들은 자신들만의 부모를 갖게 되는데, 그 부모에 대한 참조가 바로 생성자 함수 내부에 존재한다는 소리이다. 결국 객체를 생성하지 않는 함수(선언은 constructor-일반 함수처럼- 하였으나, 생성자 함수로써 쓰이지 않는 함수) 일반 함수의 prototype 프로퍼티는 아무런 의미가 없게 된다.

![prototype2](https://user-images.githubusercontent.com/97890886/163559291-332997d5-62ca-4127-a042-775e65107956.png)


모든 객체가 가지고 있는(Object.prototype에게 상속받은) __proto__ 접근자 프로퍼티와 함수 객체만이 가지고 있는 prototype 프로퍼티는 동일한 것(프로토타입)을 가리킨다. 프로퍼티를 사용하는 주체가 생성자 함수이냐, 객체이냐에 따라 달라서 그렇지...

즉 객체 리터럴로 일반 객체를 만들면 __proto__로 자신의 프로토타입(부모)를 관리할 수 있고, constructor을 갖는 생성자 함수 객체를 만들면 prototype 프로퍼티에 접근(.prototype)하여 프로토타입(부모)을 관리할 수 있는 것이다.

```jsx
function Person(name) {
    this.name = name;
}

const me = new Person(`kang`);

console.log(Person.prototype === me.__proto__);     // true
```

## 프로토타입의 constructor 프로퍼티와 생성자 함수

모든 프로토타입은 자신을 프로토타입이라고 참조하고 있는 생성자 함수를 가리키는 프로퍼티를 갖는다 -constructor-.  이 링크는 생성자 함수가 동작하여 객체가 생성될 때 이루어진다.

```jsx
function Person(name) {
    this.name = name;
}

const me = new Person(`kang`);

console.log(me.constructor === Person);     // true
```

1. Person 생성자 함수가 me 객체 생성
2. me 객체는 프로토타입의 constructor 프로퍼티를 통해 생성자 함수와 연결됨

me 객체는 자신의 부모(프로토타입)의 constructor 프로퍼티를 (상속받아) 사용하여 자신의 생성자 함수를 알아낼 수 있다.

# 객체와 프로토타입은 한 쌍

객체를 생성하는 방법은 크게 두 가지이다.

- 객체 리터럴로 생성
- 생성자 함수로 생성

생성자 함수로 생성하는 경우의 프로토타입은 지금까지 앞에서 살펴보았다. 생성자 함수의 경우 new와 함께 인스턴스를 생성하기 때문에 매우 명시적, 직관적이며 명료했다.

그렇다면 객체 리터럴로 생성한 객체의 프로토타입(부모)은 뭘까?

```jsx
// 객체 리터럴로 일반 객체 obj 생성
const obj = {};

console.log(obj.constructor);   // [Function: Object]
```

위 예제의 obj는 생성자 함수 Object()로 생성한 객체가 아니라, 객체 리터럴에 의해 생성한 객체인데도 Object()와 constructor 프로퍼티로 연결되어 있다.

> 객체 리터럴 정의 방식은 사실 내부에서 Object() 생성자 함수로 생성되는 걸까?
> 

결론부터 말하자면, `아니오`이다. 

- 생성자 함수 Object() 구현 : 객체를 생성할 때 인수를 전달하지 않으면 내부적으로 추상 연산 OrdinaryObjectCreate를 호출하여 Object.prototype을 프로토타입으로 갖는 빈 객체를 생성
- 객체 리터럴 평가 : 추상 연산 OrdinaryObjectCreate를 호출하여 빈 객체를 생성하고 프로퍼티를 추가

둘은 유사성이 있다. 그러나 프로퍼티 추가 처리 등의 세부 내용은 엄연히 **다르다.**

함수의 경우도 비슷하다. 함수 선언문이나 리터럴 표기법에 의해 생성된 함수 객체의 constructor 프로퍼티를 확인해보면 이들의 생성자 함수는 Function 생성자 함수이다.

둘은 엄연히 다른데 왜 이러는 걸까?

> 프로토타입과 생성자 함수는 단독으로 존재하는 것이 불가능하며, 항상 한 쌍이다.
> 

결국, 둘은 분명히 다른 방법이지만 큰 틀에서 생각해 보면 어떤 방법으로 선택하든 결과(객체 그 자체)는 유사하기 때문에 그냥 받아들여야 한다. 즉, 객체가 어떻게 생성되든 결국 모든 객체는 생성자 함수와 연결되어 있다.

# 프로토타입 생성 시점

> 프로토타입은 생성자 함수가 생성되는 시점에 더불어 생성된다.
> 

앞에서 봤듯이, 생성자 함수와 프로토타입은 단독x 한 쌍이기 때문이다.

생성자 함수는 두 가지로 구분하여 생각할 수 있다.

- 사용자 정의 생성자 함수
- 빌트인 생성자 함수(자바스크립트 기본 제공 표준 함수)

## 사용자 정의 생성자 함수

내부 메서드 [[construct]]를 갖는 함수 객체에 한해서, 함수 정의가 평가되어 함수 객체를 생성하는 시점에 프로토타입도 더불어 생성된다.

즉, 함수 호이스팅에 의해 함수 선언문이 끌어올려져 런타임 이전에 선언될 때 프로토타입도 함께 생성되어 생성자 함수의 prototype 프로퍼티에 바인딩된다고 할 수 있다.

이 때 프로토타입도 객체이고, 모든 객체는 프로토타입을 가지므로 프로토타입도 자신의 프로토타입을 갖는데 이 때 이 프로토타입은 바로 `Object.prototype`이다. 프로토타입이 막 생성되어 따끈따끈할 때 가지고 있는 고유의 프로퍼티는 constructor 뿐이다.

## 빌트인 생성자 함수

얘도 똑같다. 빌트인 생성자 함수는 전역 객체의 프로퍼티이다. 전역 객체란 말 그대로 가장 큰 틀로, 코드 자체가 실행되기 이전 단계에 자바스크립트 엔진에 의해 생성되는 특수 객체-window 등-이다.

> 어떤 방법으로 생성하든, 객체가 생성되기 이전에 생성자 함수와 프로토타입은 이미 객체화되어 존재하며 이후 각각의 방법으로 객체를 생성하면 생성된 객체의 내부 슬롯 중 [[Prototype]]에 이를(미리 생성된프로토타입을) 할당한다.
> 

# 객체 생성 방식에 따른 프로토타입 결정

객체는 다양한 방식으로 생성된다. 이렇게 생성된 모든 객체는 세부적인 차이는 있으나 추상 연산 OrdinaryObjectCreate에 의해 생성된다는 공통점이 있다.

추상 연산 OrdinaryObjectCreate는 자신이 생성할 객체의 `프로토타입`을 필수 인수로 전달받기 때문에 프로토타입은 곧 이 인수에 의해 결정된다고 해도 과언이 아니다. 그리고 이 인수는 객체가 생성되는 시점에 객체 생성 방식에 의해 결정된다.

## 객체 리터럴

> arguments로 전달되는 프로토타입 : Object.prototype
> 

자바스크립트 엔진이 객체 리터럴을 평가하여 객체를 생성할 때 추상 연산 OrdinaryObjectCreate를 호출하는데, 이 때 Object.prototype가 arguments로써 전달된다.

## Object() 생성자 함수

> arguments로 전달되는 프로토타입 : Object.prototype
> 

객체 리터럴과 같다. 다른 점은 `프로퍼티를 추가하는 방식`인데,

- 객체 리터럴 : 객체 리터럴 내부에 프로퍼티 추가
- Object 생성자 함수 : 일단 빈 객체 생성(new) → 이후 프로퍼티 추가

## 생성자 함수

> arguments로 전달되는 프로토타입 :  생성자 함수의 prototype 프로퍼티에 바인딩 되어 있는 프로토타입 객체
> 

위의 두 놈들이 프로토타입으로 가지는 Object.prototype는 온갖 기능이 내재되어 있는 상당히 거대한 부모인데, 이쪽의 프로토타입은 constructor하나뿐이다(...) 그래도 어차피 프로토타입의 프로토타입이 Object.prototype이니까 결국 연결되어 있기는 하다.

프로토타입도 결국 객체이므로 프로토타입에 프로퍼티,메서드를 추가/삭제할 수 있다. 이를 통해 1차원 상속관계를 아주 간단하게 표현할 수 있다. 즉 부모를 맘대로 수정할 수 있다는 거다.


# 프로토타입 체인

> 프로토타입 체인은 상속과 프로퍼티 검색을 위한 메커니즘이다.
> 

```jsx
function Person(name) {
    this.name = name;
}

Person.prototype.sayHello = function() {
    console.log(`Hi! my name is ${this.name}`);
}

const me = new Person(`kang`);
```

- (Person 생성자 함수에 의해 생성된) me 객체의 프로토타입은 Person.prototype이다.
- Person.prototype의 프로토타입은 Obeject.prototype이다

자바스크립트는 객체의 프로퍼티에 접근할 때,

1. 해당 객체에 접근하려는 프로퍼티가 있는지 검색
2. 없다면 내부 슬롯 [[Prototype]]의 참조를 따라 프로토타입(부모 역할의 객체)를 순차적으로 검색

이것이 바로 `프로토타입 체인`이다. 이는 자바스크립트가 객체지향 프로그래밍의 `상속`을 구현하는 메커니즘이다.

예를 들어, me 객체에서 Object.prototype에만 존재하는 어떤 메소드를 호출했을 때,

1. me 객체에서 검색하고, 없으면
2. 내부 슬롯 [[Prototype]]에 바인딩되어 있는 프로토타입인 Person.prototype으로 이동하여 검색하고, 없으면
3. Pesson.prototype 의 내부 슬롯 중 [[Prototype]]에 바인딩되어 있는 프로토타입인 Object.prototype으로 이동하여 검색하고 찾으면 메소드를 호출한다. 이 때 이 메서드의 this에는 me 객체가 바인딩된다.

> Object.prototype은 프로토타입 체인의 종점 (End of prototype chain) 이다.
> 

Object.prototype의 [[Prototype]] 내부 슬롯의 값은 `null`이다. 만약 종점까지 와서도 프로퍼티를 검색할 수 없는 경우, 에러가 발생하지 않고 undefined를 반환함에 주의하자.

> 프로토타입 체인은 상속과 프로퍼티 검색을 위한 메커니즘이다.
> 

프로퍼티가 아닌 식별자는 `scope chain`에서 검색한다. 스코프 체인(유효범위 상속)은 함수의 중첩 관계로 이루어졌기 때문에 스코프 체인과 프로토타입 체인은 다음과 같은 관계를 갖는다

1. 스코프 체인에서 me 식별자를 검색
2. me 식별자는 전역에서 선언되었으므로, 전역 스코프에서 검색됨.
3. 프로토타입 체인 검색은 이 이후에 이루어지며, 위와 동일한 과정을 거침.

즉, 스코프 체인과 프로토타입 체인은 별도의 동작이 아닌 `식별자와 프로퍼티 검색`을 위한 협력 관계이다.

# 오버라이딩과 프로퍼티 섀도잉

> 오버라이딩
> 

상위 클래스가 가지고 있는 메서드를 하위 클래스가 재정의하여 사용

> 오버로딩
> 

이름이 동일한 함수가 있고 메서드를 호출할 때, 매개변수의 타입 또는 개수로 메서드를 구별하여 호출하는 방식. 자바스크립트는 이를 지원하지는 않지만 arguments 객체로 구현할 수는 있다.

만약 Person.prototype에서 메서드 sayHello(프로토타입 프로퍼티)를 정의했는데, 이후 me 에서 동일한 이름의 sayHello(인스턴스 프로퍼티)를 인스턴스에 추가하면

```jsx
const Person = (function() {
    function Person(name) {
        this.name = name;
    }
    
    Person.prototype.sayHello() = function() {
        console.log(`Hello, I'm ${this.name}!`);
    }

    return Person;
}());

const me = new Person(`kang`);

me.sayHello = function() {
    console.log(`Hello, I'm ${this.name}!`);
}

me.sayHello();
```

프로토타입 체인을 따라 프로토타입 프로퍼티를 검색하여 덮는 것이 아닌, `인스턴스 프로퍼티`가 살아남는다. 이 때 인스턴스 메서드 sayHello가 프로토타입 메서드 sayHello를 `오버라이딩`했다고 하며, 이렇게 상속 관계에 의해 상위 클래스의 프로퍼티가 가려지는 현상을 `프로퍼티 섀도잉`이라고 한다.

![overriding](https://user-images.githubusercontent.com/97890886/163559697-a3b92411-7085-412f-8974-d3189cd82b94.png)

위 예제는 인스턴스 프로퍼티를 추가하였을 때 어떻게 동작하는지를 살펴본 거였는데, 만약 프로퍼티를 삭제하는 경우에는 어떨까? 당연히,

> 프로토타입 메서드가 아닌 인스턴스 메서드가 삭제된다.
> 

다시 삭제를 시도해도, 프로토타입의 프로퍼티(메서드)는 삭제되지 않는다. 즉 **하위 객체를 통해 프로토타입의 프로퍼티를 변경, 삭제하는 것은 불가능**하다. 자식은 부모를 get 할 뿐, set은 하지 못한다. 부모를 뜯어 고치려면 `프로토타입 체인`으로 접근하지 말고 프로토타입에 `직접` 접근해야 한다,

# 프로토타입 교체

> 프로토타입(부모 객체)을 동적으로 변경할 수 있다.
> 

→ 객체 간의 상속 관계를 동적으로 변경할 수 있다.

변경하는 방법은 크게 두 가지이다

- 생성자 함수
- 인스턴스

## 생성자 함수

```jsx
const Person = (function() {
    // 생성자 함수
    function Person(name) {
        this.name = name;
    }
    
    // 프로토타입을 객체 리터럴로 교체
    Person.prototype = {
        // constructor 프로퍼티와 생성자 함수 간의 연결 설정
        constructor: Person,
        sayHello() {
            console.log(`Hello, I'm ${this.name}!`);
    }}

    return Person;
}());

const me = new Person(`kang`);

// me의 생성자 함수는 Person이다(연결 완)
console.log(me.constructor === Person);     // true
```

1. 생성자 함수에서 prototype 프로퍼티에 접근하여 객체를 할당한다 (= 생성자 함수가 생성할 객체의 프로토타입을 교체)
2. 이 때 교체한 객체에는 constructor 프로퍼티가 없다.(이는 자바스크립트 엔진이 프로토타입을 생성할 때 암묵적으로 추가한 프로퍼티이기 때문이다. 이 때 constructor 프로퍼티와 생성자 함수 간의 연결은 끊어졌다고 볼 수 있다. 그러므로 이 때 me의 생성자 함수를 검색하면 Person이 아닌 Object가 나오게 된다.) 
3. 교체한 객체에 constructor 프로퍼티를 추가하여 되살린다

## 인스턴스

앞에서 배웠듯이, 프로토타입에 접근하는 방법은

1. 생성자 함수의 프로퍼티

2. 인스턴스의 __proto__ 접근자 프로퍼티

생성자 함수의 prototype 프로퍼티에 다른 임의의 객체를 바인딩하는 것은 뼈대를 수정하는 것이나 다름없다. 즉 미래에 생성될 모든 인스턴스에 대해서 프로토타입을 변경하는 것이다.

그런데 2번은 이미 생성된 인스턴스에 대해서만 프로토타입을 교체한다.

```jsx
function Person(name) {
    this.name = name;
}

const me = new Person(`kang`);

const parent = {
    // constructor 프로퍼티와 생성자 함수 간의 연결 설정
    constructor: Person,
    sayHello() {
        console.log(`Hello, I'm ${this.name}!`)
    },
}

// 생성자 함수의 prototype 프로퍼티와 프로토타입 간의 연결 설정
Person.prototype = parent;

// me 객체의 프로토타입을 parent 객체로 변경
// me.__proto__ = parent; 와 동일하게 동작한다
Object.setPrototypeOf(me, parent);

console.log(me.constructor === Person);     // true
```

생성자 함수와 인스턴스 두 가지 방법의 차이점은, 생성자 함수와 프로토타입의 연결에 대해 깊게 연관되어 있다.

- 생성자 함수는 prototype 프로퍼티를 통해 프로토타입을 가리킨다
- 프로토타입은 constructor 프로퍼티를 통해 프로토타입을 가리킨다

두 방법 다 후자는 동일하게 박살났기 때문에 me.constructor === Person 문이 false가 나온다. me의 생성자 함수는 더이상 Person이 아니라 Object이다. 그러나 미묘하게 다른 점은, 생성자 함수는 전자는 만족시키고 있다는 것이고 인스턴스는 둘 다 개박살을 냈다는 것이다. 그래서 인스턴스는 두 작업을 전부 다 해줘야 한다.

이처럼, 프로토타입 교체를 통해 객체 간 상속 관계를 동적으로 변경하는 것은 굉장히 번거롭다. 프로토타입을 직접 교체하지 않는 것을 권장한다. 인위적으로 설정하려면 `직접 상속`이나 `클래스(ES6도입)`을  사용하는 것이 더 편리하고 안전하다.

# instanceof

> 상속 관계를 판별하는 이항 연산자
> 

```jsx
객체 instanceof 생성자 함수
```

 `생성자 함수`의 prototype 프로퍼티에 바인딩된 객체가 `객체`의 프로토타입 체인 상에 존재하는지를 판별하여 ToF 값으로 평가된다.

```jsx
function Person(name) {
    this.name = name;
}

const me = new Person(`kang`);

const tof = me instanceof Person;
console.log(tof);   // true
```

프로토타입을 교체해보자

```jsx
function Person(name) {
    this.name = name;
}

// 프로토타입으로 교체할 객체
const parent = {
};

const me = new Person(`kang`);
//  프로토타입 교체
Object.setPrototypeOf(me, parent);

// 생성자 함수와 프로토타입 객체 연결 확인
console.log(Person.prototype === parent);      // false
console.log(parent.constructor === Person);    // false

// 생성자 함수와 객체 연결 확인
console.log(me instanceof Person);    // false
console.log(me instanceof Object);    // true
```

me 객체에 대하여 :

- 프로토타입이 교체되어 생성자 함수와 프로토타입 객체의 연결은 파괴되었지만,
- Person 생성자 함수에 의해 생성된 인스턴스임은 틀림없다.

그런데 왜 false가 뜨는걸까?

> Person.prototype이 me 객체의 프로토타입 체인 상에 존재하지 않기 때문
> 

쉽게 말하면 상속 관계 확인이지만, 보다 정확히 말하면 instanceof 연산자는 프로토타입의 `constructor` 프로퍼티가 가리키는 생성자 함수를 찾는 것이 아닌, 생성자 함수의 `prototype` 에 바인딩된 객체가 프로토타입 체인 상에 존재하는지 확인한다.

![instanceof](https://user-images.githubusercontent.com/97890886/163559729-8724dfd3-32f3-4fbc-9fc6-5bc3d37ead98.png)

- 생성자 함수로 프로토타입 객체 교체한 경우 : constructor로 인한 연결은 파괴되었으나, 생성자 함수 Person은 여전히 prototype 프로퍼티로 me의 prototype chain 내의 프로토타입을 가리키고 있다. 생성자 함수로 프로토타입을 교체하면 instance 연산자가 true가 나온다.
- 객체 리터럴로 프로토타입 객체 교체한 경우 : 둘 다 파괴되었으므로, 재연결 해주지 않는 이상 false가 나온다.

# 직접 상속

## Object.create

Ocject.create 메서드는 명시적으로 프로토타입을 지정하면서 객체를 새롭게 생성한다. 다른 객체 생성 방식과 마찬가지로, 추상 연산 OrdinaryObjectCreate를 호출하여 만든다.

> Ocject.create 메서드는 첫 번째 매개변수에 전달한 객체의 `프로토타입 체인 속하는 객체`를 생성한다. 에 즉 객체를 생성하면서 직접적으로 상속을 구현하는 것이다.
> 

- `첫 번째 매개변수`로 생성할 객체의 `프로토타입`으로 지정할 객체를 전달하고,
- `두 번째 매개변수`로 생성할 객체를 반환한다 : 프로퍼티 키, 프로퍼티 디스크립터로 이뤄진 형식

두 번째 매개변수의 형식은 Object.defineProperties 메서드의 두 번째 인수와 동일하며, 옵션이므로 생략이 가능하다. 

```jsx
// 프로토타입이 null인 객체 생성
// 직접 상속은 Object.prototype를 상속받지 않는다
// obj -> null
let obj = Object.create(null);

// obj -> Object.prototype -> null
obj = Object.create(Object.prototype);

const myProto = {
    a : 1,
}

// 객체 리터럴에 의해 생성된 임의의 객체 상속
// obj -> myProto -> Object.prototype -> null
obj = Object.create(myProto);

function Person(name) {
    this.name = name;
}

// obj = new Person(`kang); 과 동일
// obj -> Person.prototype -> Object.prototype -> null
obj = Object.create(Person.prototype);
obj.name = `kang`;
```

> 장점
> 
1. new 연산자 없이도 객체 생성 가능
2. 프로토타입을 직접 지정하면서 객체 생성 가능
3. 객체 리터럴에 의해 생성된 객체도 상속 가능

Object.prototype은 모든 객체 프로토타입 체인의 종점이므로, 가장 하위에 있는 자식놈인 obj도 쓸 수 있다. 그러나 Object.prototype의 빌트인 메서드를 객체가 직접 호출하는 것은 `ESLint`에서 권장하지 않는다. 왜냐하면, null로 생성했을 경우 ([220410](https://www.notion.so/220410-4042ec57c716436e9aa338c3ecb27fad) 참고) 이를 참고하지 못하기 때문이다. 혹시 모를 위험을 방지하기 위해 `간접 호출`하는 것이 좋다.

```jsx
const obj = Object.create(null);
obj.a = 1;

// Object.prototype의 빌트인 메서드 hasOwnProperty 직접 사용
obj.hasOwnProperty(`a`);    // TypeError: obj.hasOwnProperty is not a function

// 객체로 직접 사용하지 않고 간접 사용
Object.prototype.hasOwnProperty.call(obj, `a`);
```

## 객체 리터럴 내부의 __proto__

```jsx
const proto = {
    a : 1,
};

// 객체 직접 상속받음
// o -> proto -> Object.prototype -> null
const o = {
    b : 2,
    __proto__: proto,
};
```

# 정적 프로퍼티/메서드

> 생성자 함수 자체의 프로퍼티/메서드는 생성자 함수가 생성한 인스턴스에서 참조/호출 할 수 없다. 이런 의미에서 `정적` 프로퍼티/메서드 라고 한다.
> 

```jsx
function Person(name) {
    this.name = name;
}

Person.staticAge = 22;
Person.staticMessage = function() {
    console.log(`Hello, ${this.name}!`);
};

const me = new Person(`kang`);

console.log(me.staticAge);          // undefined
console.log(me.staticMessage());    // TypeError: me.staticMessage is not a function

console.log(Person.staticAge);          // 22
console.log(Person.staticMessage());    // Hello, Person!
```

생성자 함수가 생성한 인스턴스는 자신의 프로토타입 체인에 속한 객체의 프로퍼티/메서드에 접근할 수 있는데, 생성자 함수 고유의 프로퍼티/메서드는 프로토타입 체인에 속해있지 않으므로 접근이 불가능한 것이다.

위에서 배웠던 Object.create 역시 Object 생성자 함수의 정적 메서드기 때문에 객체로 호출이 불가능하다.

이를 유용하게 사용하는 경우는 다음과 같다.

```jsx
function Parent() {
};

// 만약 어떤 메서드를 상속으로 구현하여 호출하고 싶을 때,

// 1. 프로토타입 메서드로 구현하면 인스턴스를 생성(new)해야 한다.
Parent.prototype.hello = function() {
    console.log(`Hello!`);
}

const child = new Parent(); 

child.hello();    // Hello!

// 2. this 연산자가 없는 경우 정적 메서드로 구현하면
// 1처럼 인스턴스를 따로 생성하지 않고도 호출이 가능하다.
Parent.hello = function() {
    console.log(`Hello!`);
}

Parent.hello();    // Hello!
```

이 둘을 구별하는 방법은, 표기법부터 다르기 때문에 아주 쉽다(프로토타입 메서드의 경우 걍 .prototype이 중간에 들어가 있으니까). 또한, prototype 일일이 쓰는게 귀찮았는지 그냥 #로 때우기도 한다.

# 프로퍼티 관련 연산자

## 프로퍼티 존재 확인

> in 연산자
> 

```jsx
key in object
// key : 프로퍼티 키 (문자열)
// object : 객체로 평가되는 표현식
```

주의할 점은,  in 연산자는 확인 대상 객체의 프로퍼티 뿐만 아니라 객체가 상속받은 모든 프로토타입의 프로퍼티를 확인한다는 것이다.

ES6에 도입된 Reflect.has 메서드를 대신 사용할 수도 있다. in 연산자와 동일하게 동작한다.

> Object.prototype.hasOwnProperty 메서드
> 

객체 고유의 프로퍼티 키인 경우에만 true를 반환하며, 상속받은 프로토타입의 프로퍼티 키인 경우 false를 반환한다.

```jsx
const Person = {
    name: `kang`,
};

const me = Object.create(Person);
me.age = 22;

console.log(`age` in me);   // true
// 프로토타입 체인 상에 존재하는 모든 프로토타입에서 프로퍼티 검색
console.log(`name` in me);  // true
console.log(Reflect.has(me, `toString`));   // true

// 객체 고유의 프로퍼티만 검색
console.log(Object.prototype.hasOwnProperty(`age`));    // false
console.log(Object.prototype.hasOwnProperty(`name`));   // false
```

## 프로퍼티 열거

> for...in 문
> 

객체의 모든 프로퍼티를 순회하며 열거 enumeration 하려면 for...in 문을 사용한다.

```jsx
for (변수선언문 in 객체) {...}
```

1. 객체의 프로퍼티 개수만큼 순회
2. 변수 선언문에서 선언한 변수(보통의 반복문에서는 i의 역할을 하는)에 프로퍼티 키를 할당
3. 코드 블록(반복문) 실행

이 때 객체의 프로토타입 체인 상에 존재하는 모든 프로토타입 프로퍼티를 대상으로 하지만, 프로퍼티 어트리뷰트 `[[Enumerable]]` (열거 가능)의 값이 `true`인 프로퍼티에 한한다.

```jsx
const Person = {
    name: `kang`,
};

const me = Object.create(Person);
me.age = 22;

// for...in 문
// 프로퍼티를 순회하며 열거
for (key in me) {
    console.log(`${key} : ${me[key]}`);
}
/*
age : 22
name : kang
*/

// [[Enumerable]] 가 false인 프로퍼티는 열거할 수 없다
console.log(Object.getOwnPropertyDescriptor(Object.prototype, `toString`));
/*
{
  value: [Function: toString],
  writable: true,
  enumerable: false,
  configurable: true
}
*/
```

프로퍼티 키가 심벌인 프로퍼티는 열거하지 않는다

객체 자신의 고유 프로퍼티만 열거하려면 조건문을 추가

```jsx
const sym = Symbol();

const Person = {
    name: `kang`,
    // 프로퍼티 키가 심벌인 프로퍼티는 열거하지 않음
    [sym] : 10,
};

const me = Object.create(Person);
me.age = 22;

// for...in 문
// 프로퍼티를 순회하며 열거
for (key in me) {
    // 객체 고유의 프로퍼티만 열거
    if (!me.hasOwnProperty(key)) continue;
    console.log(`${key} : ${me[key]}`);
}

// age : 22
```

for..in문은 앵간해서는 순서를 지키지만, 배열에는 for...in 보다 for...of 또는 Array.prototype.forEach 메서드를 사용하는 것을 권장한다.

> object.keys/values/entries 메서드
> 

객체 자신의 고유 프로퍼티를 열거하기 위해서는 for...in 문과 조건문을 사용하는 것보다 이 메소드들을 사용하는 것을 권장한다.

- Object.keys 메서드

객체 자신의 `열거 가능한 enumerable 프로퍼티 키`를 배열로 반환

- Object.values 메서드 (ES8 도입)

객체 자신의 `열거 가능한 프로퍼티 값`을 배열로 반환

- Object.entries 메서드 (ES8 도입)

객체 자신의 열거 가능한 프로퍼티 `키+값 쌍`의 배열을 배열에 담아 반환