# 생성자 함수로 객체 생성하기

객체 리터럴에 의한 객체 생성은 가장 일반적이고 간단한 객체 생성 방식이다. 그러나 자바스크립트가 제공하는 빌트인(built-in) 생성자 함수 Object()를 사용하여 객체를 생성할 수도 있다.

```jsx
// 빈 객체 생성
const person = new Object();

// 프로퍼티 추가
person.name = 'kang';
person.sayHello = function() {
    console.log(`Hi! my name is ${person.name}!`);
};

console.log(person);    // { name: 'kang', sayHello: [Function (anonymous)] }
person.sayHello();      // Hi! my name is kang!
```

> 생성자 함수 constructor
> 

`new` 연산자와 함께 호출하여 객체(인스턴스)를 생성하는 함수. 생성자 함수에 의해 생성된 객체를 인스턴스라고 하는 것이다. 자바스크립트는 Object()외에도 다양한 빌트인 생성자 함수를 제공한다.

> 왜 객체 리터럴이 아닌 생성자 함수를 사용하는가?
> 

객체 리터럴로 객체를 생성하는 것이 더 편리하다. 그렇다면 왜 이걸 쓰지? Object 생성자 함수로 객체를 생성하는 방식은 특별한 경우에 사용한다.

# 생성자 함수를 사용하는 경우

## 객체 리터럴 방식의 문제점

> 객체 리터럴에 의한 객체 생성 방식은 직관적이고 간편하나, `단 하나의 객체`만 생성한다.
> 

객체는

- `프로퍼티`를 통해 객체 고유의 상태를 표현하고,
- `메서드`를 통해 상태 데이터(프로퍼티)를 조작하는 `동작`을 표현한다.

객체마다 프로퍼티 값이 다를 수 있지만, 위와 같이 메서드는 내용이 동일한 경우 프로퍼티 구조가 동일함에도 매번 같은 프로퍼티와 메서드를 표기해야 해서 불편하다. 

```jsx
const circle = {
    radius: 5,
    getDiameter() {
        return this.radius * 2;
    },
};

const circle2 = {
    radius: 10,
    getDiameter() {
        return this.radius * 2;
    },
};
```

## 생성자 함수 방식의 장점

생성자 함수는 마치 객체(인스턴스)를 생성하기 위한 템플릿(클래스)처럼 동작한다. 즉 틀, 뼈대를 먼저 짜 놓는다고 할 수 있다.

> 프로퍼티 구조가 동일한 객체 여러 개를 간편하게 생성할 수 있다.
> 

```jsx
// 생성자 함수
// 메서드: 동일, 프로퍼티: 유동적
function Circle(radius) {
    this.radius = radius;
    this.getDiameter = function() {
        return 2 * this.radius;
    };
}

// 인스턴스(객체) 생성
const circle = new Circle(5);
const circle2 = new Circle(10);

console.log(circle.getDiameter());      // 10
console.log(circle2.getDiameter());     // 20
```

> this
> 

자기 참조 변수 (self-referencing variable). 함수 호출 방식에 따라 동적으로 바인딩된다.

- 일반 함수로써 호출 : 전역 객체
- 메서드로써 호출 : 메서드를 호출한 객체
- 생성자 함수로써 호출 : 생성자 함수가 (미래에) 생성할 인스턴스

```jsx
function foo() {
    console.log(this);
}

// 일반적인 함수로써 호출
foo();      // window

// 메서드로써 호출
const obj = { foo };
obj.foo();      // obj

// 생성자 함수로써 호출
const inst = new foo();     // inst
```

생성자 함수는 말 그대로 객체(인스턴스)를 생성하는 함수지만, 자바와 같은 클래스 기반 객체지향 언어와는 달리 형식이 정해져 있는 것이 아닌, `일반 함수`와 동일한 방법으로 정의하여 생성한다. 이를 생성자 함수로써 동작시키기 위해서는 `new` 연산자와 함께 호출하면 된다. new 연산자와 함께 생성자 함수를 호출하지 않으면 그냥 일반 함수로 동작함에 주의하자.

```jsx
// new 연산자를 사용하지 않았을 때
const circle3 = Circle(20);
// 일반 함수로 동작 : 반환문을 찾지 못함
console.log(circle3)    // undefined
// 일반 함수로 동작 : this는 전역 객체를 가리킴.
console.log(radius);    // 20
```

# 생생자 함수의 인스턴스 생성 과정

> 생성자 함수의 목적(역할)
> 

프로퍼티 구조가 동일한 인스턴스를 생성하기 위한 템플릿(클래스)으로써 동작하여

- 인스턴스를 생성
- 생성된 인스터스를 초기화 : 인스턴트 프로퍼티 추가, 초깃값 할당

한다. 전자는 필수, 후자는 선택이다.

```jsx
// 생성자 함수
function Sum(num) {
    // 인스턴스 초기화
    this.num = num;
    this.result = function () {
        if (this.num%2) {
            return ++this.num;
        }
        return this.num;
    };
}

// 인스턴스(객체) 생성
const sum1 = new Sum(1);    // num이 1인 Sum 객체 생성
const sum2 = new Sum(2);    // num이 2인 Sum 객체 생성

console.log(sum1.result());     // 2
console.log(sum2.result());     // 2
```

코드 자체는 간단해 보인다. 생성자 함수 내부의 this에 프로퍼티를 추가하고, 필요에 따라 전달된 인수를 프로퍼티의 초깃값으로써 할당하여 인스턴스를 `초기화`한다. 그리고 이후 new 연산자와 함께 생성자를 호출하면 자바스크립트가 암묵적으로 인스턴스를 생성+초기화+반환 해준다.

## 자바스크립트 엔진의 인스턴트 암묵적 생성 과정

### 1. 인스턴스 생성과 this 바인딩

암묵적으로 빈 객체(인스턴스)가 생성자 함수에 의해 생성되고 this에 바인딩된다. (이제 이 함수 내부에서 this를 사용할 경우, this 키워드-따지고보면 식별자 역할을 하는 것이나 다름없다-는 이미 바인딩(자신이 가리킬 객체를 이미 정했음) 완료했기 때문에 이 미완성체인 인스턴스를 가리키게 된다.)

 아직 객체가 완성되지 않았음에도 불구하고(new 연산자와 함께 호출되어 완성되지 않은 상태) 생성자 함수 내부의 this가 이를 가리키는 이유가 바로 이것이다. 왜냐하면

본 과정은 함수 런타임 이전에 자바스크립트 엔진이 실행하기 때문이다.

### 2. 인스턴스 초기화

함수 런타임에 this에 바인딩되어 있는 인스턴스를 `초기화`한다. 이는 곧 다음과 같은 행위들을 의미한다:

- 프로퍼티, 메서드를 추가
- 생성자 함수가 인수로 전달받은 초깃값을 인스턴트 프로퍼티에 할당하여 초기화 or 고정값 할당

본 과정은 개발자가 기술한다.

### 3. 인스턴스 반환

생성자 함수 내부의 모든 처리가 끝나면 완성된 인스턴스가 바인딩된 상태의 this가 암묵적으로 반환된다. 

> this가 아닌 다른 값을 명시적으로 반환문으로 지정했을 경우
> 
- 객체 : 암묵적인 this 반환이 무시되고 return에 명시된 객체가 반환됨
- 원시 값 : 원시 값 반환이 무시되고 암묵적으로 this가 반환됨

생성자 함수 내부에서 명시적으로 this가 아닌 다른 값을 반환하는 것은 생성자 함수의 기본 동작을 훼손하므로, 생성자 함수 내부에서는 `return문을 생략`하는 것을 권장한다.

```jsx
// 생성자 함수
function Sum(num) {
    // 1. 인스턴스 생성 : this로 즉시 암묵적 바인딩 됨

    // 2. 인스턴스 초기화 : 개발자 기술 코드 순차적 실행
    this.num = num;
    this.result = function () {
        if (this.num%2) {
            return ++this.num;
        }
        return this.num;
    };

    // 3. 인스턴스 반환 : 암묵적으로 this 반환
    return 10;  // 무시된다.
    return {};  // 무시되진 않지만 사용을 권장하지 않는다.
}
```

# 객체, 함수, 생성자 함수

함수도 객체이므로, (함수 선언문 혹은 함수 표현식으로 선언된)는 일반 객체 ordinary object와 동일하게 동작할 수 있다. 함수 객체는 일반 객체가 가지고 있는 내부 슬롯, 내부 메서드를 전부 가지고 있다.

일반 객체와 함수의 차이점 :

> `함수`는 호출이 가능하고 `일반 객체`는 불가능하다.
> 

`함수`는 일반 객체의 내부 슬롯과 내부 메서드 말고도

- 내부 슬롯 : [[Enviroment]], [[FormalParameters]]
- 내부 메서드 : [[Call]], [[Construct]]

등을 추가로 가지고 있다.

## [[Call]]

> `일반 함수`로써 호출될 경우 호출되는 함수 객체의 내부 메서드
> 

내부 메서드 [[Call]]을 갖는 함수 객체를 `callable` (호출할 수 있는 객체 - 일반 함수)이라고 한다.

## [[Construct]]

> `new 연산자`와 함께 `생성자 함수`로써 호출된 경우 호출되는 함수 객체의 내부 메서드
> 
- 내부 메서드 [[Construct]]을 갖는 함수 객체를 `constructor` (생성자 함수)이라고 한다.
- 내부 메서드 [[Construct]]을 갖지 않는 함수 객체를 `non-constructor` (논 생성자 함수)이라고 한다.

객체는 callable이 아니다.

함수는 callable이다.

그중에서도 생성자 함수는 callable이자 constructor이고, 일반 함수는 callable이자 non-constructor이다.

## 자바스크립트 엔진이 생성자 함수를 구별하는 방법

자바스크립트 엔진은 어떻게 `constructor`과 `non-constructor`을 구분할까?

- constructor : 함수 선언문, 함수 표현식, 클래스(클래스도 함수다)
- non-constructor : 메서드(ES6 메서드 축약 표현), 화살표 함수

> 즉, 생성자 함수로써 호출(사용)하려면 `일반 함수` (`constructor`)로 정의해야 한다.
> 

메서드나 화살표 함수로 정의하면 non-constructor로 인식되어 new 연산자와 함께 생성자 함수로 사용할 수 없다. 그러나 주의할 점은, 자바스크립트 엔진이 메서드를 인식하는 기준이 굉장히 까다롭다는 것이다.

```jsx
// 일반 함수 : 함수 선언문
function foo() {
}

// 일반 함수 : 함수 표현식
const goo = function() {
}

// 메서드
const z = {
    zoo: function() {
    },
};

// 화살표 함수
const arrow = () => {};

// ES6 메서드 축악 표현
const obj = {
    f() {}
};

const a = new foo();    // foo{}
const b = new goo();    // goo{}
const c = new z.zoo();  // zoo{}
const d = new arrow();  // TypeError: arrow is not a constructor
const e = new obj.f();  // TypeError: obj.f is not a constructor

console.log(a,b,c,d,e);
```

> 주의사항
> 
- ECMAScript 샤양에서는 ES6의 메서드 축약 표현만을 메서드로 정의한다. 본 예제에서 z.zoo()도 객체 내부에 있는 메서드지만, 일반 함수와 같이 constructor로 인식되었다.
- non-constructor인 함수 객체를 생성자 함수로써 호출하면 에러가 발생한다.
- **생성자 함수로써 호출될 것을 기대하지 않은 일반 함수를 new 연산자와 함께 호출하면 생성자 함수로 동작**한다.

자바스크립트 엔진은 이를구분하지 못하기 때문에(일반 함수와 생성자 함수가 선언 방식이 동일하므로 개발자가 신경써야 하는 것이다;;) 주의해야 한다.

## new 연산자와 주의사항

> 생성자 함수로 사용할 의도가 없는  `일반 함수` 를 new를 사용하여 호출
> 

`constructor` 함수에 한해서, 반환문 값의 데이터 타입과 상관없이 Call이 아닌 Construct가 호출된다. (`non-constructor`은 애초에 에러가 난다)

- 원시 값 반환문 : 무시된다
- 객체 값 반환문 : *객체가 반환된다*

```jsx
// 생성자 함수가 아닌 일반 함수 선언
function sum (x,y) {
    // 원시 값 반환
    return x+y;
}

const inst = new sum();

// 객체를 반환하지 않았으므로 반환문 무시. 빈 객체가 생성되어 반환됨
console.log(inst);      // sum {}

// 생성자 함수가 아닌 일반 함수 선언
function createUser(name, role) {
    // 객체 값 반환
    return {
        name:'kang',
        role:'student',
    };
}

const inst2 = new createUser();

// 함수가 생성한 객체를 반환
console.log(inst2);     // { name: 'kang', role: 'student' }
```

> `생성자 함수`를 new를 사용하지 않고(까먹고) 호출
> 

연산자 new가 없으니 일반 함수로 호출되며, Construct가 아닌 Call이 호출된다. 

```jsx
function Print(num) {
    this.num = num;
    this.pr = function() {
        return this.num * 10;
    };

}

const myNum = /* new */ Print(3);

console.log(myNum);    // undefined

console.log(num);       // 3
console.log(pr());      // 30

myName.pr();    // TypeError: Cannot read properties of undefined (reading 'pr')
```

Print()가 new가 없으므로 생성자 함수가 아닌 일반 함수로 호출되었다. 이 때 this는 전역 객체가 되므로 num과 pr()이 전역 객체의 프로퍼티와 메서드가 된다. 

일반 함수와 생성자 함수 간에 형식적 차이가 없으므로, 표기법(생성자는 파스칼)으로 차별화를 두도록 하자.

## new.target

생성자 함수가 new 연산자 없이 호출되는 것을 방지하기 위해, 표기법을 차별화한다 하더라도 실수할 수도 있다. 이러한 위험성을 해결하기 위해 ES6에서는 `new.target`을 제공한다.

- this와 유사하게 constructor인 모든 함수 내부에서 암묵적인 지역 변수와 함께 사용됨
- 일명 메타 프로퍼티
- 함수 내부에 new.target을 사용하면 new 연산자를 사용하였는지 체크를 할 수 있다.

> new.target의 값은 함수가 new 연산자와 함께 생성자 함수로 호출될때만 함수 자신이다.
> 

new 연산자를 까먹고 일반 함수처럼 호출했을 경우 new.target은 undefined이다.

→ 함수 내부에서 new.target을 사용하여 함수를 생성자 함수로써(new 연산자와 함께) 호출했는지 체크하고, 실수했을 시 new 연산자와 함께 재귀 호출을 하여 문제를 해결한다.

```jsx
function Print(num) {
    if (!new.target) {
        return new Print(num);
    }
    this.num = num;
    this.pr = function() {
        return this.num * 10;
    };

}

const myNum = Print(3);

console.log(myNum.pr());    // 30
```

ES6을 지원하지 않는 상황이라면, 스코프 세이프 생성자 패턴을 사용할 수 있다.

[new.target](http://new.target) 대신에 this instanceof Print 를 사용하면 된다~

new 연산자와 함께 생성자 함수에 의해 생성된 객체(인스턴스) -여기서는 myNum-는 프로토타입에 의해 생성자 함수와 연결된다. 이를 이용하여 new연산자와 함께 호출되었는지 유무를 확인할 수 있다.

빌트인 생성자 함수 중 Object와 Function 함수는 new 연산자 없이 호출해도, 내부적으로 알아서 new 연산자와 함께 호출되었는지를 확인하고 지가 알아서 new 있을때와 동일하게 동작한다.

나머지들은 new와 함께 하면 객체를 생성하여 반환하지만 new 없으면 각각 대응하는 원시 값을 반환한다(String의 경우 문자열). 이를 교묘하게 이용하여 데이터 타입을 변환하기도 한다.