# async/await

`generator`를 사용하여 `비동기`처리를 `동기`처리처럼 동작(**순차적 처리**)하도록 구현했으나 코드가 상당히 장황했었다 → ES8에서 도입된 async/await을 사용하여 해결해보자

> 프로미스의 후속 처리 메서드 없이도 마치 동기 처리처럼 프로미스가 처리 결과를 반환하도록 구현할 수 있다
> 

# async 함수

- `async` 키워드로 정의한다
- 언제나 `프로미스`를 반환한다
- `await` 키워드는 반드시 `async` 함수 내부에서 사용해야 한다.

```jsx
// async

// 함수 선언문
async function foo(n) {
    return n;
}
foo(1).then(console.log);

// 함수 표현식
const goo = async function(n) {
    return n;
}
goo(2).then(console.log);

// 화살표 함수
const zoo = async n => n;

// 메서드
const obj = {
    key : `value`,
    async method(par) {
        return par;
    }
}

// 클래스 메서드
class MyClass {
    async fun(n) {
        return n;
    }
}
const myClass = new MyClass();
myClass.fun(10).then(console.log);
```

단, 클래스의 constructor 메서드는 async 메서드가 될 수 없는데, constructor은 인스턴스의 기본 설정을 담은, 이후에 인스턴스를 반환할 메서드이기 때문이다. async 함수는 언제나 프로미스만을 반환해야 하므로 엇갈린다.

# await 키워드

> 프로미스가 `settled`가 될때까지 대기 → `settled`가 되면 프로미스가 `resolve`한 처리 결과를 반환
> 

즉, 프로미스가 비동기 처리를 마칠 때까지 기다리고 비동기 처리가 완료되면 성공한 결과를 반환한다는 뜻이다.

await 키워드는 다음 코드 실행을 일시 중지 시켰다가, 프로미스가 settled가 되면 다시 재개한다.

제너레이터는 next와 yield를 통해 재귀 호출을 반복함으로써 이를 구현했었다면, 이 쪽은 훨씬 간단하다.

 반드시 프로미스 앞에서 사용해야 한다.

```jsx
const fetch = require(`node-fetch`);

const getGithubUserName = async id => {
    const result = await fetch(`https://api.github.com/users/${id}`);
    const {name} = await result.json();

    console.log(name);
}
```

fetch 함수가 수행한 HTTP 응답이 도착하여, fetch 함수가 반환하는 프로미스가 settled가 될 때까지 대기 → settled되면 result에 할당 → result.json 작업 → 성공적으로 완료 시 디스트럭처링으로 할당

## 과한 사용은 지양

모든 프로미스에 await 키워드를 사용하는 것은 좋지 않다. 유사 동기 처리===순서가 보장되어야 한다는 뜻이므로, 서로 연관이 없이 개별적으로 수행되는 비동기 처리의 경우는 순차적으로 처리할 필요가 없다.

```jsx
// 서로 연관이 없는 비동기 처리

async function foo() {
    const a = await new Promise(resolve => setTimeout(() => resolve(1)), 3 * 1000);
    const b = await new Promise(resolve => setTimeout(() => resolve(1)), 2 * 1000);
    const c = await new Promise(resolve => setTimeout(() => resolve(1)), 1 * 1000);
}
// 약 6초 소요

// 이렇게 처리하는 것이 좋다
async function foo() {
    const res = await Promise.all([
        new Promise(resolve => setTimeout(() => resolve(1)), 3 * 1000),
        new Promise(resolve => setTimeout(() => resolve(1)), 2 * 1000),
        new Promise(resolve => setTimeout(() => resolve(1)), 1 * 1000),
    ]);
}
// 약 3초 소요
```

앞선 비동기 처리가 완료될 때까지 다음 비동기 처리들은 대기 상태이므로, 시간 비효율적으로 소비된다.

앞선 비동기 처리의 결과를 가지고 다음 비동기 처리를 해야할 경우(연쇄성)는 비동기 처리가 보장되어야 하므로 모든 프로미스에 await 키워드를 쓴다.

```jsx
// 앞선 비동기 처리 결과로 다음 비동기 처리를 해야 하는 경우

async function goo(num) {
    // 어쩔 수 없이 모든 프로미스에 await 키워드를 사용하여 순차적 처리를 한다
    const first = await new Promise(res => setTimeout(() => res(num)), 3000);
    const second = await new Promise(res => setTimeout(() => res(first+1)), 3000);
    const third = await new Promise(res => setTimeout(() => res(second+2)), 3000);

    console.log(third);
}

goo(10);    // 13
```

# 에러 처리

비동기 처리를 위한 콜백 패턴의 단점 중 가장 심각한 것은 에러 처리의 어려움이다. 에러는 Caller 방향으로 전파되는데, 비동기 처리 특성 상 콜백 함수의 Caller이 더 이상 비동기 함수가 아니게 되기 때문에 에러를 캐치하기 힘들다.

```jsx
try {
    setTimeout(() => {
        throw new Error(`error!`);
    }, 1000);
} catch (e) {
    console.error(`에러 ${e} 캐치`);
}   

// 에러를 캐치하지 못함

// setTimeout은 호출된 후 콜백 함수 호출 스케줄링을 하고 즉시 종료
// Call stak에서 pop되고, 이후 콜백 함수가 실행됨
// 콜백 함수가 에러를 발생시켰지만 Caller는 이미 pop되었으므로
// 마치 중간 다리가 하나 끊긴것처럼 에러가 전파되지 못함(캐치 불가)
```

> async/await 에서는 try…catch문으로 에러를 캐치할 수 있다.
> 

콜백 함수를 인수로 전달받는 콜백 패턴과는 달리, 프로미스를 반환하는 형식의 async/awit 패턴은 명시적 호출이 가능하므로 Caller가 명확하다.

```jsx
const fetch = require('node-fetch');

const errorCatch = async () => {
    try {
        const worngUrl = `hahahaha.com/com/commm`;

        const response = await fetch(worngUrl);
        const data = response.json();

        console.log(data);
    } catch (error) {
        console.error(`캐치한 에러 : ${error}`);
    }
};

errorCatch();
// 캐치한 에러 : TypeError: Only absolute URLs are supported
```

HTTP 통신에서 발생한 네트워크 에러, try 블록 내의 모든 일반적인 에러 등을 전부 캐치할 수 있다.

### async 함수 내부에서 try…catch 문으로 에러 처리를 하지 않았는데 에러가 발생한 경우

async함수는 여전히 프로미스를 반환하지만, 발생한 에러를 reject하는 프로미스를 반환한다.

외부에서 Promise.prototype.catch로 후속 처리를 할 수 있다.

```jsx
// 내부적 에러 처리를 하지 않은 경우
// async는 rejected 프로미스를 반환하므로
// 외부에서 후속 처리 메서드 catch로 에러 처리를 할 수 있다

const fetch = require('node-fetch');

const errorCatch = async () => {
    const worngUrl = `hahahaha.com/com/commm`;

    const response = await fetch(worngUrl);
    const data = response.json();

    return data;
};

errorCatch().catch(console.error);  // TypeError: Only absolute URLs are supported
```
