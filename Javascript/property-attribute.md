# 내부 슬롯, 내부 메서드

internal slot, internal method. 자바스크립트 엔진의 내부 로직으로, 자바스크립트 엔진의 구현 알고리즘을 설명하기 위해 ECMAScript에서 사용하는 의사 프로퍼티이자 의사 메소드이다. 이들은 내부에서 실제로 동작하지만 개발자가 직접 접근하는 용도는 아니기 때문에 보통은 접근이 불가능하다. 일부 내부 슬롯, 메서드에 한해서 간접적으로 접근이 가능하다.

```jsx
const obj = {};

obj.[[Prototype]]   // SyntaxError: Unexpected token '['

obj.__proto__   // 일부 내부 슬롯, 메서드에 한해 간접적 접근 수단 제공
```

# 프로퍼티 어트리뷰트와 프로퍼티 디스크립터 객체

자바스크립트 엔진은 프로퍼티를 생성할 때, 프로퍼티 어트리뷰트를 기본값으로 자동 정의한다.

> 프로퍼티 어트리뷰트
> 

프로퍼티의 상태를 나타내는 내부 슬롯이다. 프로퍼티의 값(value), 갱신 가능 여부(writable), 열거 가능 여부(enumerable), 재정 가능 여부(configurable) 등...

- [[Value]], [[writable]], [[enumerable]], [[configurable]]

아까 살펴본 대로, 프로퍼티 어트리뷰트에 직접적으로 접근할 수는 없지만 간접적으로 접근하여 확인할 수 있다.

```jsx
const person = {
    name: 'kang',
};

// 프로퍼티 어트리뷰트 정보를 제공하는 프로퍼티 디스크립터 객체 반환
console.log(Object.getOwnPropertyDescriptor(person, 'name'));
// { value: 'kang', writable: true, enumerable: true, configurable: true }
```

첫 매개변수에는 객체의 참조를, 두 매개변수에는 프로퍼티 키를 문자열로 전달하였다. 이 함수는 프로퍼티 어트리뷰트 정보를 제공하는 프로퍼티 디스크립터 PropertyDescriptor 객체를 반환한다. 이는 하나의 프로퍼티에 대해서만 반환하지만, ES8 이후 저 끝에 s 붙인 함수는 모든 프로퍼티의 프로퍼티 어트리뷰트를 반환해준다.

# 데이터 프로퍼티와 접근자 프로퍼티

> 데이터 프로퍼티 vs 접근자 프로퍼티
> 
- 데이터 프로퍼티 : 키와 값으로 구성된 일반적인 프로퍼티(지금까지 본 모든 프로퍼티들)
- 접근자 프로퍼티 : 자체적으로는 값을 갖지 않고, 데이터 프로퍼티의 값을 읽거나 저장할 때 호출되는 접근자 함수로 구성된 프로퍼티.

## 데이터 프로퍼티

다음과 같은 프로퍼티 어트리뷰트를 갖는다. 자바스크립트 엔진이 프로퍼티를 생성할 때 기본값으로 자동 정의된다.

> [[Value]]
> 
- 프로퍼티 키를 통해 프로퍼티 값에 접근하면 반환되는 값
- 키를 통해 값을 변경하면 [[Value]]에 값을 재할당한다. 동적 생성으로 인한 변경(프로퍼티가 없는데 참조하여 암묵적 생성 룰을 따름)의 경우 프로퍼티를 동적 생성하고 생성한 프로퍼티의 [[Value]]에 값을 저장한다.

> [[writable]]
> 
- 프로퍼티 값의 변경 여부를 나타내는 불리언 값
- false인 경우 해당 프로퍼티의 [[Value]]를 변경할 수 없다(Readonly)

> [[enumerable]]
> 
- 프로퍼티의 열거 가능 여부를 나타내는 불리언 값
- false인 경우 for...in 문이나 Object.keys 메서드 등으로 열거할 수 없다.

> [[configurable]]
> 
- 프로퍼티의 재정의 가능 여부를 나타내는 불리언 값
- false인 경우 해당 프로퍼티의 삭제, 프로퍼티 어트리뷰트 값의 변경이 금지된다. 단, [[Value]]와 [[writable]]의 변경은 가능하다. ([[writable]]가 true인 경우에 한함)

각 프로퍼티 어트리뷰트의 기본값은

[[Value]] : 프로퍼티 값

[[writable]] : true

[[enumerable]] : true

[[configurable]] : true

로 초기화된다.

## 접근자 프로퍼티

자체적으로는 값을 갖지 않고 다른 데이터 프로퍼티의 값을 읽거나 저장할 때 사용하는 접근자 함수로 구성된 프로퍼티

> [[get]]
> 

접근자 프로퍼티를 통해 데이터 프로퍼티의 값에 접근하여 프로퍼티 어프리뷰트 [[get]]의 값(getter 함수가 호출된 결과)을 읽는 접근자

> [[set]]
> 

접근자 프로퍼티를 통해 데이터 프로퍼티의 값에 접근하여 프로퍼티 어프리뷰트 [[set]]의 값(setter 함수가 호출된 결과)을 읽는 접근자

> [[enumerable]]
> 

> [[configurable]]
> 

접근자 함수는 getter/setter 함수라고도 부르며, 둘 모두를 정의할 수도 있고 둘 중 하나만 정의 할 수도 있다. 자체적으로 값(프로퍼티 어트리뷰트 [[value]])을 가지지 않고 다만 데이터 프로퍼티의 값을 읽거나 저장할 때 관여한다.

```jsx
const person = {
    // 데이터 프로퍼티
    firstName: 'kang',
    lastName: 'yoon',

    // 접근자 프로퍼티 fullName : 접근자 함수로 이루어져 있다
    get fullName() {
        return `${this.firstName} ${this.lastName}`
    },

    set fullName(name) {
        [this.firstName, this.lastName] = name.split('');
    }
};

// 데이터 프로퍼티를 통한 프로퍼티 값의 참조
console.log(person.firstName + ' ' + person.lastName);

// 접근자 프로퍼티를 통한 프로퍼티 값의 저장 : set
person.fullName = 'woo lee';
console.log(person);

// 접근자 프로퍼티를 통한 프로퍼티 값의 참조 : get
console.log(person.fullName);

// firstName은 데이터 프로퍼티
let descriptor = Object.getOwnPropertyDescriptor(person, 'firstName');
console.log(descriptor);

// fullName은 접근자 프로퍼티
descriptor = Object.getOwnPropertyDescriptor(person,'fullName');
console.log(descriptor);
```

이렇게 접근자 프로퍼티 fullName으로 프로퍼티 값에 접근하면 내부적으로 [[get]] 내부 메서드가 호출되어 동작하는데, 이 과정을 내부 슬롯/메서드 관점에서 설명해보면

1. 프로퍼티 키가 유효(문자열 또는 심벌)한지 확인 : fullName은 문자열이므로 ㅇㅋ!
2. 프로토타입 체인에서 프로퍼티 검색 : person 객체에 fullName 프로퍼티 확인 ㅇㅋ!
3. 검색된 프로퍼티가 데이터인지 접근자인지 확인 : 접근자 ㅇㅋ!
4. 접근자 프로퍼티 fullName의 프로퍼티 어트리뷰트 [[get]]의 값 == getter 함수를 호출하여 그 결과 반환.

# 프로퍼티 정의

프로퍼티를 추가하면서 프로퍼티 어트리뷰트를 명시적으로 정의하거나, 기존 프로퍼티의 프로퍼티 어트리뷰트를 재정의해보자 : Object.defineProperty 메서드 사용

```jsx
// 프로퍼티 정의
Object.defineProperty(person, 'firstName', {
    value: 'hello',
    writable: true,
    enumerable: true,
    configurable: true,
});

Object.defineProperty(person, 'lastName', {
    value: 'wolrd',
});
```

# 객체 변경 방지

객체는 변경 가능한 값이므로 재할당 없이 값 자체를 직접 젼경 가능하다. 이는 곧 프로퍼티를 추가하거나 삭제하고, 값을 갱신할 수 있으며 위의 메서드로 재정의를 할 수 있음을 의미한다. 지금까지 배운 내용들을 활용해서 객체가 변경되는 것을 억제하고 방지할 수 있다.

## 객체 확장 금지

> Object.preventExtensions 메서드
> 

`프로퍼티 추가를 금지`한다. 동적 추가와 Object.defineProperty로 추가하는 방법 모두 금지된다.

확장이 가능한 객체인지 여부는 Object.isExtensible으로 확인 가능하다. (ToF 값 반환)

## 객체 밀봉

> Object.seal 메서드
> 

`프로퍼티 추가`및 `삭제`와 `프로퍼티 어트리뷰트 재정의`를 금지한다. 읽고 쓰기만 가능하다.

밀봉된 객체인지 여부는 Object.isSealed로 확인 가능하다

## 객체 동결

> Object.froze 메서드
> 

`프로퍼티 추가` 및 `삭제`와 `프로퍼티 어트리뷰트 재정의` , `프로퍼티 값 갱신`을 금지한다. 읽기만 가능하다.

동결된 객체이지 여부는 Object.isFrozen 로 확인 가능하다.

## 불변 객체

지금까지 살펴본 변경 방지 메소드들은 얕은 변경 방지로 직속 프로퍼티만 변경이 방지되고 중첩 객체까지는 영향을 주지 못했다. 객체의 중첩 객체까지 동결시켜 변경 불가능한 읽기 전용의 불변 객체를 구현하려면 객체를 값으로 가지고 있는 모든 프로퍼티에 대해 재귀적으로 동결 메소드를 호출해야 한다.