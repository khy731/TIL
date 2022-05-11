# 심벌

> ES6에서 도입된 7번째 data type. 변경 불가능한 원시 타입의 값이며, **다른 값과 중복되지 않는 유일무이한 값**.
> 

주로 이름 충돌이 없는 `유일한 프로퍼티 키`를 만들기 위해 사용된다.

# 심벌 값 생성하기

## Symbol 함수

다른 원시값들은 리터럴 표기법도 가능하지만, 심벌 값은 **오직 Symbol 함수**로만 생성할 수 있다. 이 때 생성된 심벌 값은

- 외부로 노출되지 않아 확인할 수 없으며
- 다른 값과 절대 중복되지 않는 유일무이한 값이다.

```jsx
// Symbol 함수를 호출하여 유일무이한 심벌 값을 생성
const symbol = Symbol();
console.log(typeof symbol);

// 외부로 노출되지 않음 -> 확인 불가능
console.log(symbol);/
```

- new 연산자와 함께 호출하여 인스턴스를 생성할 수 없다.

```jsx
// new 연산자와 함께 호출할 수 없다
// 심벌 값은 객체(변경 가능)가 아닌 원시 값이다
new Symbol();   //TypeError: Symbol is not a constructor
```

- 인수로 전달하는 문자열은 아무 의미가 없다

```jsx
// 인수로 문자열을 전달할 수 있지만 이는 심벌 값에 대한 설명일 뿐
// 값 자체에는 영향을 주지 못한다
const mySymbol = Symbol(`kang`);
const mySymbol2 = Symbol(`kang`);
console.log(mySymbol === mySymbol2);    // F
```

- 객체처럼 접근하면 암묵적으로 래퍼 객체를 생성한다

```jsx
// 객체처럼 접근하면 암묵적으로 래퍼 객체를 생성한다
console.log(symbol.description);    // undefined
```

- 암묵적 타입 변환을 허용하지 않으나, `불리언 값` 한정으로 가능하다.

```jsx
// 암묵적 타입 변환 X
console.log(symbol + ``);   // TypeError: Cannot convert a Symbol value to a string

// 암묵적 타입 변환 : 불리언 값 으로만 casting된다
console.log(!!symbol);
if (symbol) console.log(`symbol is mot empty`);
```

# 메서드

Symbol 함수는 호출될 때마다 유일무이한 심벌 값을 생성하는데, 이는 전역 심벌 레지스트리에서 관리되지 못한다(식별자-키-가 없는 그냥 ‘값’자체이니까 뭐 어케 관리를 할 수가 없다). 이 때 특정 메서드를 사용하면 키를 지정하여 전역 심벌 레지스트리를 통해 심벌을 공유할 수 있다. (즉 심벌에 이름을 정해 줌으로써 자바스크립트 엔진이 중복된 값인지 아닌지 관리할 수 있게 한다) 

## Symbol.for

인수로 전달받은 문자열을 `키`로 사용하여 전역 심벌 레지스트리(global symbol registry, “키와 심벌 값”의 쌍들이 저장되어 있음)에서 **해당 키와 일치하는 심벌 값을 검색**한다.

- 검색에 성공 시 : `검색된 심벌 값` 반환 (새로 생성 X)
- 검색에 실패 시 : 새로운 심벌 값 생성 → 전역 심벌 레지스트리에 “인수로 전달받은 키 + 심벌 값” 형태로 저장 → `새로 생성된 심벌 값` 반환

```jsx
const s1 = Symbol.for(`kang`);    // `kang`키의 심벌이 존재하지 않음 -> 새로운 심벌 값 생성후 반환
const s2 = Symbol.for(`kang`);    // 검색 성공 시 해당 심벌 값 반환

console.log(s1 === s2);    // T
```

## Symbol.keyFor

전역 심벌 레지스트리에 저장된 심벌 값의 키를 추출한다.

```jsx
console.log(Symbol.keyFor(s1));    // kang
```

# 상수 대신 심벌

> 값에는 특별한 의미가 없고, 상수 이름 자체에만 의미가 있을 때 값에 상수 대신 심벌을 사용하면 좋다.
> 

값은 생략이 불가능한데 이 때 상수(숫자 리터럴)를 사용하면 변경되거나 다른 변수 값과 중복될 수 있기 때문에 유일무이하고 중복될 가능성이 없는 심벌을 사용한다.

```jsx
// 방향을 담은 객체
// 각 상수 이름은 방향이라는 의미를 담고 있지만 값은 사실상 없어도 무방(무의미)
const Direction = {
    UP : 1,
    DOWN : 2,
    LEFT : 3,
    RIGHT : 4,
}

// 상수 대신 심벌을 사용하면 변경/중복의 위험을 해결할 수 있다
const Direction2 = {
    UP : Symbol(`up`),
    DOWN : Symbol(`down`),
    LEFT : Symbol(`left`),
    RIGHT : Symbol(`right`),
}

const myDirection = Direction2.UP;

if (myDirection === Direction2.UP) {
    console.log(`you're going UP!`); 
}
```

## enum

> 명명된 숫자 상수(named numeric constant)의 집합. 열거형(enumerated type)이라고도 부르며, 서로 연관된 상수들의 집합이다.
> 

대부분의 프로그래밍 언어는 enum을 지원하지만 자바스크립트는 지원하지 않는다. 상위 호환인 타입스크립트는 지원함. 위의 예제를 enum으로 표현하면 정말 간단하겠지만, 자바스크립트는 이를 지원하지 않으므로 `Object.freeze`와 `심벌 값`으로 흉내낸다.

```jsx
// JavaScript enum
// Direction 객체는 1. 불면 객체이며 2. 유일무이하고 중복되지 않는 프로퍼티 값을 가진다

const Direction = Object.freeze({
    UP : Symbol(`up`),
    DOWN : Symbol(`down`),
    LEFT : Symbol(`left`),
    RIGHT : Symbol(`right`),
})

const myDirection = Direction.UP;

if (myDirection === Direction.UP) {
    console.log(`you're going UP!`); 
}
```

# 심벌과 프로퍼티

## 프로퍼티 키

심벌 값으로 프로퍼티 키를 동적 생성하여 프로퍼티를 만들려면 심벌 값에 `대괄호`를 사용해야 한다.

```jsx
const obj = {
    [Symbol.for(`name`)] : `kang`,
    [Symbol.for(`age`)] : `22`
}

console.log(obj[Symbol.for(`name`)]);   // kang
console.log(obj[Symbol.for(`age`)]);    // 22
```

## 프로퍼티 은닉

심벌 값을 프로퍼티 키로 사용하여 생성한 프로퍼티는 은닉된다(for...in 문이나 Object.getOwnPropertyNames 메서드, Object.keys 메서드 등으로 찾을 수 없다).

```jsx
// 심벌 프로퍼티 키는 은닉된다

const obj = {
    [Symbol.for(`name`)] : `kang`,
    age : 22,
}

for (const key in obj) {
    console.log(key);   // age
}

console.log(Object.keys(obj));    // [ 'age' ]
console.log(Object.getOwnPropertyNames(obj));   // [ 'age' ]
```

그러나 ES6의 `Object.getOwnPropertySymbols` 메서드로 찾을 수 있게 되었다. 은닉 불가능~

```jsx
// ES6 메서드의 등장으로 은닉 불가

console.log(Object.getOwnPropertySymbols(obj));     // [ Symbol(name) ]
console.log(Object.getOwnPropertySymbols(obj)[0]);  // Symbol(name)
```

# 표준 빌트인 객체 확장

일반적으로 표준 빌트인 객체에 사용자 정의 메서드를 직접 추가하여 확장하는 것은 권장되지 않는다. 표준 빌트인 객체는 read only로 사용하는 것이 좋다.

사용자 정의 메서드의 이름과 미래에 표준 사양으로 추가될 메서드의 이름이 **중복**될 수 있기 때문인데, Symbol 값으로 프로퍼티 키를 생성하여 확장한다면 충돌 위험 없이 안전하게 할 수 있다.

```jsx
**// 충돌 위험 O
Array.prototype.sum = function() {
    return this.reduce((acc,cur) => acc+cur, 0);
}

console.log([1,2].sum());   // 3

// 충돌 위험 X
Array.prototype[Symbol.for(`sum`)] = function() {
    return this.reduce((acc,cur) => acc+cur, 0);
}

console.log([1,2][Symbol.for(`sum`)]());    // 3**
```

# Well-known Symbol

자바스크립트가 기본으로 제공하는 빌트인 심벌 값. Symbol 함수의 프로퍼티에 할당되어 있으며, 주로 자바스크립트 엔진의 내부 알고리즘에 사용된다.

심벌은 1. 중복되지 않는 상수 값 생성 2. 기존 코드에 영향을 주지 않고 새로운 프로퍼티를 추가(하위 호환성을 보장)