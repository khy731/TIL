# 제너레이터(generator)

ES6 도입. 코드 블록의 실행을 일시 중지했다가 필요한 시점에 재개할 수 있는 특수한 함수.

## 제너레이터 vs 일반 함수

> 제너레이터는 함수 호출자에게 함수 실행 제어권을 양도할 수 있다
> 

런타임에서 일반 함수 호출문을 만나면 코드의 제어권이 함수에게 넘어가고 함수 코드가 실행된다. 즉, 함수 호출자caller는 함수를 호출하면 함수 실행을 제어할 수 없는 것이 일반적이다. 제너레이터 함수는 함수 실행을 caller가 제어할 수 있다 : **함수의 제어권을 함수가 독점하지 않고 함수 호출자에게 양도yield할 수 있다**

> 제너레이터는 호출자와 함수의 상태를 주고받을 수 있다
> 

일반 함수는 매개변수를 통해 함수 외부에서 값을 주입받고 함수 코드를 일괄 실행아여 결과값을 함수 외부로 반환return하는 구조로 caller와 소통한다. 즉, 함수가 실행중일 때에는 함수 외부는 함수 내부에 영향을 끼치지 못한다. 제너레이터 함수는 함수의 상태를 caller에게 전달하거나/전달받을 수 있다.

> 제너레이터 함수를 호출하면 제너레이터 객체를 반환한다
> 

일반 함수는 함수 호출 시 함수 코드를 일괄 실행하고 특정한 값을 return하지만, 제너레이터 함수는 **함수 코드를 실행하는 것이 아닌, 제너레이터 객체(이터러블이면서 이터레이터)를 반환**한다

# 제너레이터 함수 정의

- function* 키워드
- 하나 이상의 yeild 표현식

```jsx
// 제너레이터 함수 선언하기
// - function* 키워드
// - 하나 이상의 yield 표현식

// 함수 선언문
function* genDecFunc() {
    yield 1;
}

// 함수 표현식
const genExpFunc = function*() {
    yield 1;
};

// 메서드
const obj = {
    property : `value`,
    * genObjMethod() {
        yield 1;
    }
};

// 클래스 메서드
class MyClass {
    * genClsMethod() {
        yield 1;
    }
}

// 화살표 함수로 정의할 수 없다
// new 연산자와 함께 생성자 함수로 호출될 수 없다
```

# 제너레이터 객체

제너레이터 함수 호출 시 일반 함수와는 달리 함수 코드 블록 실행이 아닌 `제너레이터 객체`를 생성하여 반환하는데, 이는 iterable이면서 동시에 iterator이다.

- iterable : Symbol.iterator 객체를 상속받음
- iterator : next 메서드(value, done 프로퍼티 등을 갖은 result 객체를 반환) 소유

또한 이터레이터에는 없는 return, throw 메서드를 갖고 있다.

## 제너레이터 메서드의 동작

> next
> 
1. 제너레이터 함수의 yield 표현식까지 코드 블록 실행 
2. yield된 값을 value 프로퍼티 값, false를 done 프로퍼티 값으로 갖는 iterator-result 객체를 반환

> return
> 

인수로 전달받은 값을 value, true를 done으로 갖는 iterator-result 객체를 반환

> throw
> 
1. 인수로 전달받은 에러를 발생시킴
2. undefined를 value, true를 done으로 갖는 iterator-result 객체를 반환

```jsx
function* genFunc() {
    try {
        yield 1;
        yield 2;
        yield 3;
    } catch(e) {
        console.error(e);
    }
}

const generator = genFunc();

console.log(generator.next());      // { value: 1, done: false }
console.log(generator.return());    // { value: undefined, done: true }
console.log(generator.throw(`Error!`));    // Error!
```

# 제너레이터의 일시 중지/재개

> 제너레이터는 `yield`키워드와 `next`메서드를 통해 실행을 일시 중지하고, 필요한 시점에 재개할 수 있다.
> 

제너레이터 함수를 호출하면 코드 블록을 실행하지 않고 제너레이터 객체를 반환한다고 했다.

제너레이터 객체의 next 메서드 호출 시 제너레이터 함수의 코드 블록 실행된다. **yield 표현식까지만**.

yield는 함수 실행을 일시 중지시키거나, yield 뒤의 표현식의 평가 결과를 caller에게 반환하는 역할을 한다.

```jsx
// next 메서드에 인수를 전달할 수 있다 (yield 표현식 변수에 할당됨)
function* genFunc() {
    const x = yield 1;
    const y = yield x+10;
    return x + y;
}

const generator = genFunc();

// First next()
// 코드의 실행 순서 : 할당문이므로 우항 -> 좌항
// 즉, yield 1까지 실행된 후 종료됨
// x 는 아직 undefined
console.log(generator.next());    // { value: 1, done: false }

// Second next()
// x에 전달받은 인수가 할당됨 (const x = yield 1; 실행 완료)
// yield문 실행 후 종료됨
// y는 아직 undefined
console.log(generator.next(10));    // { value: 20, done: false }

// Third next()
// y에 전달받은 인수가 할당됨 (const y = yield x+10; 실행 완료)
// 함수가 끝까지 실행됨
// 반환문의 값 x+y는 value에 저장됨. 진짜로 활용될수 있는 값으로는 의미가 없는것이 대부분임.
// 즉, 제너레이터에서 반환문은 쓸모가 없으므로 그냥 종료의 의미로만 사용하자
console.log(generator.next(100));
```

즉, next 메서드를 반복 호출하여 yield 표현식까지 실행 & 일시 중지를 반복하는 구조
제너레이터 함수는 next 메서드와 yield 표현식으로 함수 caller와 함수 상태를 공유할 수 있다.

- caller은 next 메서드를 통해 제너레이터의 "상태"(~yield된 값)를 꺼내올 수 있다
- caller은 next 메서드에 인수를 전달하여 제너레이터에 "상태"를 밀어넣을 수 있다

-> 이를 활용하여 비동기 처리를 동기 처리처럼 구현할 수 있다.

### <정리>

![generator](https://user-images.githubusercontent.com/97890886/181190688-9941d1b2-6b20-428d-bf89-1ffb2064199e.png)

# 활용

## 이터러블 구현

기존 이터러블 구현(이터레이션 프로토콜을 준수하여 생성)보다 간단하게 이터러블을 구현할 수 있다.

yield와 next()를 활용한 **일시중지/재개** 로직을 응용한 것이다.

> 기존
> 

```jsx
// 무한 이터러블을 생성하는 함수
const infiniteFibonacci = (function() {
    let [pre, cur] = [0,1];

    // Symbol.iterator 메서드를 구현해 이터러블 프로토콜을 준수
    return {
        [Symbol.iterator]() { return this; },
        next() {
            [pre, cur] = [cur, pre + cur];
            return { value : cur };    // 무한 이터러블이므로 done 프로퍼티는 생략
        }

    }
}());

for (const num of infiniteFibonacci) {
    if (num > 1000) break;
    console.log(num);   // 1 2 3 5 ... 987
}
```


> 제너레이터 이용
> 

```jsx
// 무한 이터러블을 생성하는 제너레이터 함수

const infiniteFibonacci = (function* () {
    let [pre, cur] = [0,1];

    while(true) {
        [pre, cur] = [cur, pre+cur];
        yield cur;
    }
}());

for (const num of infiniteFibonacci) {
    if (num > 1000) break;
    console.log(num);   // 1 2 3 5 ... 987
}
```

## 비동기 처리

`yield 표현식`과 `next 메서드`로 함수 호출자와 함수의 상태를 주고받을 수 있는 제너레이터의 특성을 활용하여 프로미스를 이용한 비동기 처리를 마치 동기 처리 인 것 처럼 구현한다.

즉, 프로미스 후속 처리 메서드 then/catch/finally 없이 비동기 처리 결과를 반환하게끔 구현한다.

### 제너레이터 함수를 실행하는 제너레이터 실행기

로직 이해를 위해 간략화하였으나, 여전히 코드가 더럽다. 이는 ES8에 도입된 async/await으로 대체 가능하지만, 꼭 제너레이터 실행기를 사용해야 하는 경우 co 라이브러리를 사용하는 것을 권장한다.

```jsx
// Node.js 환경에서 window.fetch 함수를 사용하기 위한 패키지
const fetch = require(`node-fetch`);

// 제너레이터 실행기

const async = genFunc => {
    const generator = genFunc();
    const onResolved = arg => {
        const result = generator.next(arg);

    return result.done
        ? result.value
        : result.value.then(res => onResolved(res));
    }

    return onResolved;
}

// 보다 쉬운 로직 이해를 위해 분리한 코드 ver
// 원 예제는 async에 fetchFunc을 인수로 전달하며 즉시실행함수
/* function* fetchFunc() {
    const url = `블라블라`;

    const response = yield fetch(url);
    const answer = yield response.json();

    console.log(answer);
}
async(fetchFunc()); */

(async(function* fetchFunc() {
    const url = `블라블라`;

    const response = yield fetch(url);
    const answer = yield response.json();

    console.log(answer);
})());

// fetchFunc 함수가 끝까지 실행(done:true)될 때 까지 async 실행기 내에서 재귀호출(onResolved)되는 구조
```

> co 라이브러리 사용
> 

```jsx
const fetch = require(`node-fetch`);
const co = require(`co`);

co(function* fetchFunc() {
    const url = `블라블라`;

    const response = yield fetch(url);
    const answer = yield response.json();

    console.log(answer);
});
```