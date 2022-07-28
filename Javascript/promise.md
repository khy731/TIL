자바스크립트는 비동기 처리를 위해 사용하는 `콜백 함수`의 한계를 극복하기 위해 `프로미스(Promise)`를 ES6부터 도입하였다. 

# 비동기 처리 콜백 패턴의 한계

## 비동기 처리 결과는 외부로 반환하거나 상위 스코프 변수에 할당할 수 없다

> 비동기 함수는 처리 결과를 `반환`하거나 상위 스코프 변수에 `할당`할 수 없다.
> 

REST API 실습에서 배웠던 GET 요청을 위한 함수를 코딩해 보자.

```jsx
<!DOCTYPE html>
<html lang="ko">
<head>
    <title>GET 요청을 위한 비동기 함수</title>
</head>
<body>
    <script>
        // 매개변수가 HTTP 요청을 전송할 url
        const get = url => {
            const xhr = new XMLHttpRequest();
            // 모든 리소스를 취득하는 GET
            xhr.open(`GET`, url);
            xhr.send();
    
            xhr.addEventListener(`load`, () => {
                if (xhr.status === 200) console.log(JSON.stringify(xhr.response));
                else console.error(`${xhr.status} ${xhr.statusText}`);
            });
        }

        // id가 1인 post를 취득
        get(`https://jsonplaceholder.typicode.com/posts/1`);
    </script>    
</body>
</html>
```

get은 `비동기 함수`다 : 함수 내부에 비동기로 동작하는 코드를 포함한다.

비동기 함수는 자신 내부의 비동기 동작 코드가 완료되지 않아도 기다리지 않고 **즉시 종료**된다. 즉 비동기 동작 코드는 자신의 상위 스코프인 비동기 함수가 종료된 후에야 완료되는 것이나 다름없다. 

결국 비동기 처리 결과(위 예제에서는 서버의 응답 결과)를 외부로 반환하거나 상위 스코프 변수에 할당하면 원하는대로 동작하지 않는다.

![callback-hell1](https://user-images.githubusercontent.com/97890886/181024608-c20b4359-a90c-47a6-9669-67b36782c5ed.png)

> 비동기 함수 setTimeout가 동작하는 과정
> 


![callback-hell2](https://user-images.githubusercontent.com/97890886/181024624-9b187625-b337-469d-8076-78b6446c077e.png)

1. 비동기 함수 setTimeout을 호출
2. 콜백 함수를 스케줄링하고 타이머 id를 반환한 후 **즉시 종료됨**
3. 비동기 처리인 콜백 함수는 이제서야 호출되어 작업을 처리함
4. 함수 몸체가 이미 종료되었으므로 콜백 함수는 처리 결과를 
    - 외부로 `반환`할 수 없음(스코프 체인에서 중간 다리가 하나 끊긴 거나 마찬가지).
    - 상위 스코프의 변수에 `할당`할 수 없음(이미 함수 몸체가 타이머id를 반환하고 종료되었으므로 콜백 함수의 반환값은 사실상 무의미함)
    
    ```jsx
    // 비동기(처리 코드를 가진)함수인 setTimeout 함수
    // 콜백 함수(비동기 처리)의 결과를 반환하거나, 상위 스코프의 변수에 할당하지 못한다
    
    let g = 0;
    
    setTimeout(() => { g = 100; }, 0);
    
    console.log(g);    // 0
    ```
    
    즉, 그냥 비동기 처리가 일어날 뿐 이 결과를 “값”처럼 사용할 수가 없다.
    

위 예제에서 만들었던, GET 요청을 전송하고 서버의 응답을 전달받는 get함수도 비동기 함수다. **get함수 내부의 이벤트 핸들러가 비동기로 동작하기 때문이다.**

```jsx
<!DOCTYPE html>
<html lang="ko">
<head>
    <title>GET 요청을 위한 비동기 함수</title>
</head>
<body>
    <script>
        const get = url => {
            const xhr = new XMLHttpRequest();
            xhr.open(`GET`, url);
            xhr.send();
            
            // 처리값인 서버의 응답을 "반환"함
            // get함수의 반환문 역할을 하지 못함.
            xhr.addEventListener(`load`, () => {
                if (xhr.status === 200) return JSON.stringify(xhr.response);
                else console.error(`${xhr.status} ${xhr.statusText}`);
            });
        }

        // 이벤트 핸들러의 반환값을 취득하고자 함
        const result = get(`https://jsonplaceholder.typicode.com/posts/1`);
        console.log(result);    // undefined
    </script>    
</body>
</html>
```

1. get 함수 호출 → XMLHttpRequest 객체 생성 → HTTP 요청 초기화 및 전송
2. 이벤트 핸들러 등록 → **즉시 종료됨 →** 명시된 반환문이 없으므로 undefined 반환
3. 이벤트 핸들러(비동기)가 실행됨

> 처리 결과 반환 불가
> 

load 이벤트에 등록한 이벤트 핸들러의 반환문은 get함수의 반환문이 **아니다**.

함수의 반환값은 명시적으로 호출한 후에만 캐치할 수 있으므로  get 함수가 이벤트 핸들러를 호출할 수 있다면 이벤트 핸들러의 반환값을 get 함수가 캐치하여 다시 반환하는 식으로 트릭을 짤 수 있겠지만, 비동기 처리를 하는 이벤트 핸들러는 get 함수가 호출하지 않기 때문에(브라우저 담당) 결국 이벤트 핸들러의 반환문은 그 누구도 캐치할 수 없게 된다.

```jsx
<!DOCTYPE html>
<html lang="ko">
<head>
    <title>콜백 함수의 반환값은 의미가 없다</title>
</head>
<body>
    <input type="text">
    <script>
        // 반환 불가
        document.querySelector(`input`).oninput = function() {
            // 이벤트 핸들러(콜백 함수)에서의 반환은 의미가 없다
            return this.value;
        }
    </script>
</body>
</html>
```

> 처리 결과 상위 스코프 변수에 바인딩 불가
> 

```jsx
// 상위 스코프에 할당 불가
        let serverResult;

        const get = url => {
            const xhr = new XMLHttpRequest();

            xhr.open(`GET`, url);
            xhr.send();

            xhr.onload = () => {
                if (xhr.status === 200) serverResult = JSON.stringify(xhr.status);
                else console.error(`Error`, xhr.status, xhr.statusText);
            }
        }

        get(`https://jsonplaceholder.typicode.com/posts/1`);
        console.log(severResult);   // undefined
```

이벤트 핸들러(비동기 처리를 하는 콜백 함수)는 항상 get 함수가 종료(마지막 문인 console.log까지 실행 완료)된 후에야 호출된다. 즉, 상위 스코프의 변수에 바인딩한다 하더라도 처리 순서가 보장되지 않는다.

1. get 함수 호출 → 실행 컨텍스트가 call stack에 push됨 → console.log문을 실행하고 즉시 종료됨
2. console.log가 호출되기 전에 load 이벤트가 발생했더라도 **이벤트 핸들러는 절대로 console.log문보다 먼저 실행되지 못함**
3. 서버로부터 응답이 도착하여 load 이벤트가 발생 → 이벤트 핸들러는 즉시 실행되지 않고 일단 task queue에 저장되어 대기하다가, call stack이 비면(console.log문이 끝나면) push되어 실행된다.

즉, 이벤트 핸들러 내부에서 상위 스코프 변수에 자신의 처리 값을 할당하기 이전에 console.log문이 필연적으로 항상 먼저 실행되므로 undefined가 출력되는 것이다.

## 콜백 헬

결국 비동기 처리 결과가 의미를 갖으려면(비동기 함수를 범용적으로 사용하려면) 이를 비동기 함수 내부에서 수행해야만 한다. 이 때 이러한 후속 처리를 수행하는 `콜백 함수`를 전달하는 것이 일반적이다 : 비동기 처리가 성공/실패했을 때 호출될 콜백 함수를 필요에 따라 전달할 수 있다.

```jsx
let severResult;

const get = (url, sucsessCallback, failureCallback) => {
    const xhr = new XMLHttpRequest();

    xhr.open(`GET`, url);
    xhr.send();

    xhr.onload = () => {
        // 비동기 처리 결과에 대한 후속 처리를 콜백 함수에 위임
        if (xhr.status === 200) severResult = sucsessCallback(JSON.stringify(xhr.response));
        else failureCallback(JSON.stringify(xhr.status));
    }
}

get(`https://jsonplaceholder.typicode.com/posts/1`, console.log, console.error);
console.log(severResult);   // 잘 나온다
```

그러나 비동기 함수가 비동기 처리 결과를 가지고 비동기 함수를 호출하는 이러한 구조는 마치 콜백 함수가 중첩된 모습으로, 코드의 복잡도를 높이는 한계를 가지고 있다. 이것이 바로 `콜백 헬(callback hell)`이다.

예를 들어, 비동기 처리 결과 결과값을 이용해서 또 다른 비동기 처리를 해야 하는 경우를 알아보자.

서버의 응답을 항상 1:1로 사용하는 경우는 드물 것이다. 서버에서 a라는 응답을 그대로 받아 바로 다음 작업을 해야하는 경우, 그러니까,

카테고리가 일상 > 여행 > 부산여행 인 포스트를 취득하고 싶은 경우, 일상 카테고리를 GET → 여행 카테고리를 GET → 부산여행 포스트를 GET해야 한다면?

```jsx
get(`step1`, a => {
    get(`step2`, b => {
        get(`step3`, c => {
            console.log(d);
        });
    });
});
```

이런 식으로 하게 된다. 보기만 해도 끔찍

## 에러 처리의 한계

콜백 패턴의 또 다른 문제점 중에서 가장 심각한 것은 `에러 처리`를 하기 힘들다는 것이다. 즉, 콜백 패턴 내부에서 Error을 던져도 외부에선 결국 이를 캐치하지 못하게 되는 것이다.

```jsx
try {
    setTimeout(()=> {throw new Error(`에러 발생!`);}, 1000);
} catch(error) {
    console.error(`캐치한 에러: `, error);
}
```

try 코드 블록 내에서 호출한 setTimeout 비동기 함수는 1초 후 에러를 발생시키는 콜백 함수가 실행되는 호출 스케줄링을 하고 즉시 소멸된다. setTimeout이 종료되고 delay가 끝나면 콜백 함수가 에러를 발생시킨다.


![callback-hell3](https://user-images.githubusercontent.com/97890886/181024630-8a36200b-2517-4c0f-9d63-dc9814a44fae.png)



1. setTimeout은 비동기 함수이므로 콜백 함수가 호출되는 것을 기다리지 않고 바로 종료된다.
2. 콜백 함수가 실행될 때 setTimeout 함수는 이미 call stack에서 제거된 상태다.
    
    → 이는 곧 콜백 함수의 caller가 setTimeout함수가 아니게 되었다는 것을 의미한다. (부른 놈이 이미 없어져 있다면 이 시점에서 그냥 애초부터 부른 놈이 없었던 것처럼 되는 것이다)
    
3. 에러는 caller 방향으로 전파되므로(실행 중인 실행 컨텍스트가 push되기 직전에 push된 컨텍스트 방향 쪽으로, 즉 상위 스코프 방향으로)
4. setTimeout의 콜백 함수가 발생시킨 에러는 catch블록(setTimeout의 문)에서 캐치하지 못한다.

다음과 같이, 비동기 처리를 위한 콜백 패턴은 `콜백 헬`이나 `에러 처리가 힘들다`는 문제가 있다. 이를 극복하기 위해 ES6에서 도입된 것이 바로 `Promise(프로미스)`이다.

# 프로미스 생성하기

프로미스는 ES6에서 도입된 표준 빌트인 객체로, Promise 생성자 함수를 new 연산자와 함께 호출하여 promise 객체를 생성한다.

```jsx
const promise = new Promise((resolve, reject) => {
    if (/* 비동기 처리 성공 */) resolve(`result`);
    else reject(`Error reason`);
});
```

Promise 생성자 함수가 인수로 전달받은 콜백 함수 내부에서 비동기 처리를 수행한다.

- 비동기 처리 성공 → 처리 결과를 resolve 함수에 인수로 전달하면서 호출
- 비동기 처리 실패 → 에러를 reject 함수에 인수로 전달하면서 호출

앞의 예제 비동기 함수 get을 프로미스로 다시 구현해 보자.

비동기 함수 promiseGet은 함수 내부에서 프로미스를 생성 및 반환한다.

```jsx
const promiseGet = url => {
    return new Promise((resolve, reject) => {
        const xhr = new XMLHttpRequest();
        xhr.open(`GET`, url);
        xhr.send();
    
        xhr.onload = () => {
            // 비동기 처리 성공 -> resolve 함수 호출
            if (xhr.status === 200) resolve(JSON.stringify(xhr.response));
            // 비동기 처리 실패 -> reject 함수 호출(에러 처리)
            else reject(new Error(xhr.status));
        }
    });
};

// 프로미스를 반환한다
promiseGet(`https://jsonplaceholder.typicode.com/posts/1`);
```

## 프로미스의 상태(state)

- `pending` : 비동기 처리가 아직 수행되지 않은 상태
- `fulfilled` : 비동기 처리가 수행된 상태(성공)
- `rejected` : 비동기 처리가 수행된 상태(실패)

생성 직후 프로미스는 기본적으로 `pending` 상태이지만, **resolve 함수를 호출하면 `fulfilled`, reject 함수를 호출하면 `rejected` 상태로 변경된다.**

이렇게 비동기 처리 결과에 따라 함수가 호출되면 상태가 settled(fulfilled 또는 rejected)로 변환되는데, settled에서는 더는 다른 상태로 변환되지 않는다.

> 프로미스는 비동기 처리 `상태`와 처리 `결과`를 관리하는 객체이다
> 

프로미스는 비동기 처리 상태와 더불어 처리 결과 또한 상태로 갖는다. 다음 코드를 보자.

```jsx
// fulfilled된 프로미스
const fulfilled = new Promise(resolve => resolve(1));

// rejected된 프로미스
const rejected = new Promise((_,reject) => reject(new Error(`error occurred`)));
```

비동기 처리가

- 성공하면 프로미스의 `상태`는 pending → fulfilled, `처리 결과`로 1을 갖는다
- 실패하면 프로미스의 `상태`는 pending → rejected, `처리 결과`로 Error 객체를 갖는다

# 프로미스 후속 처리 메서드

프로미스는 ‘상태’를 기준으로 ‘일’을 한다.

콜백 패턴에서 xhr.status===200이면 콜백 함수를 호출하여 console.log(xhr.response)를 하고 200이 아니면 에러 처리를 했던 것처럼, 프로미스는 상태가 `fulfilled`면 프로미스의 처리 결과로 무언가 일을 하고 `rejected` 상태가 되면 처리 결과(에러)를 가지고 에러 처리를 해야 한다.

이를 위해 프로미스는 후속 메서드 `then`, `catch`, `finally`를 제공한다. **프로미스의 비동기 처리 상태가 변화하면 후속 처리 메서드에 인수로 전달한 콜백 함수가 선택적으로 호출된다.** 모든 후속 처리 메서드는 프로미스를 반환하며, 비동기로 동작한다.

## Promise.prototype.then()

> 두 콜백 함수를 인수로 전달받아 프로미스를 반환한다.
> 
- 첫 번째 인수(콜백 함수)
    - 성공 처리(fulfilled, resolve)
    - 프로미스의 비동기 처리 결과를 인수로 전달받음
- 두 번째 인수(콜백 함수)
    - 실패 처리(rejected, reject)
    - 프로미스의 에러를 인수로 전달받음

```jsx
// fulfilled
new Promise(resolve => resolve(`clear`)).then(v=> console.log(v), e=> console.error(e));    // clear
// rejected
new Promise((_,reject) => reject(new Error(`에러 발생`)).then(v=> console.log(v), e=> console.error(e)));    // Error: 에러 발생
```

## Promise.prototype.catch

> 하나의 콜백 함수를 인수로 전달받아 프로미스를 반환한다. rejected 상태에만 동작한다.
> 

사실상 then(undefined, onRejected)와 동일하게 동작한다.

## Promise.prototype.finally

> 하나의 콜백 함수를 인수로 전달받아 프로미스를 반환한다. finally의 콜백 함수는 프로미스의 성공/실패에 상관없이 무조건 **한 번** 호출되며, 프로미스 상태와 무관하게 수행해야 할 공통 작업이 있을 때 유용하다.
> 

```jsx
// 프로미스로 구현한 비동기 함수 get

const promiseGet = url => {
    return new Promise((resolve, rejected) => {
        const xhr = new XMLHttpRequest();
        xhr.open(`GET`, url);
        xhr.send();

        xhr.addEventListener(`load`, () => {
            if (xhr.status === 200) resolve(JSON.parse(xhr.response));
            else rejected(new Error(xhr.status));
        })
    })
}

// 후속 처리 메서드

promiseGet(`어쩌구저쩌구`)
    .then(res => console.log(res))
    .catch(err => console.error(err))
    .finally(() => console.log(`bye`));
```

# 프로미스의 에러 처리

프로미스는 비동기 처리를 위한 콜백 패턴과는 달리. 비동기 처리 결과에 대한 후속 처리를 자체적으로 제공하여 수행하므로 then 메서드의 두 번째 콜백 함수나 catch로 처리한다. catch는 따지고 보면 내부적으로 then과 유사하게 처리되는데, then의 두 번째 콜백 함수(실패 에러 처리)는 가독성이 떨어지고 첫 번째 콜백 함수의 에러를 캐치하지 못하므로 모든 then 메서드를 호출한 후 catch를 호출하는 편이 좋다.

```jsx
// 프로미스를 반환한다
promiseGet(`https://jsonplaceholder.typicode.com/posts/1`)
    .then(res => console.xxx(res))
    // 바로 앞 then 문에서 발생한 에러도 캐치할 수 있다
    // 가독성도 훨씬 낫다
    .catch(err => console.error(err));    // TypeError: console.xxx is not a function
```

# 프로미스 체이닝

> 후속 처리 메서드는 언제나 프로미스를 반환하므로, 연속적으로 호출할 수 있다.
> 

```jsx
const url = `https://kanghyeyoon.github.io/`;

// id가 1인 post를 취득
promiseGet(`${url}/posts/1`)
    // 취득한 post의 userId로(디스트럭처링) user 정보를 취득(promiseGet 호출)
    .then(({userId}) => promiseGet(`${url}/users/${userId}`))
    // userInfo는 순전한 매개변수. 앞 후속 처리 메서드의 값(프로미스)을 그대로 인수로 받는다
    // 콘솔에 출력하는 일(console.log)만 함
    .then(userInfo => console.log(userInfo))
    // 에러 캐치
    .catch(err => console.error(err));
```

프로미스는 프로미스 체이닝을 통해 비동기 처리 결과를 전달받아 후속 처리를 하므로 콜백 헬을 해결한다. 그러나 결국 프로미스도 콜백 패턴을 사용하므로 한계가 있다. → ES8의 async/await을 통해 해결 가능

# 정적 메서드

Promise는 주로 생성자 함수로 사용되지만, 함수도 객체이기 때문에 프로퍼티/메서드를 가질 수 있다.

## Promise.resolve/Promise.reject

이미 존재하는 값을 wrapping하여 프로미스를 생성한다.

- 인수로 받은 값을 resolve하는 프로미스를 생성한다.

```jsx
const wrappedSolve = Promise.resolve([1,2,3]);
wrappedSolve.then(console.log);    // [ 1, 2, 3 ]

// 다음과 같다
const wrappedSolve2 = new Promise(resolve => resolve([1,2,3]));
wrappedSolve2.then(console.log);    // [ 1, 2, 3 ]
```

- 인수로 받은 값을 reject하는 프로미스를 생성한다.

```jsx
const wrappedReject = Promise.reject(new Error(`Error!`));
const wrappedReject2 = new Promise((_,reject) => reject(new Error(`Error!`)));
wrappedReject.catch(console.log);   // Error: Error!
wrappedReject2.then(undefined, console.log);    // Error: Error!
```

## promise.all

> 여러 개의 비동기 처리를 모두 `병렬`처리
> 

- 세 개의 비동기 처리를 순차적으로 처리하는 경우

```jsx
const requestData1 = () =>
    new Promise(resolve => setTimeout(() => resolve(1), 3 * 1000))

// 프로미스의 형태는 정말 복잡하구나...
/* 맨 처음에 배웠을 때에는 get 함수(마치 틀 같은, 프로미스를 찍어내는 함수)가 예제였어서
resolve와 rejected가 걍 쌩으로 매개변수고 딱히 명시되어 있지 않았는데
requestData1는 호출 시 프로미스를 반환하는데, 그 프로미스는 resolve함수만 있고(성공했을 경우만 명시하고 있고)
resolve 함수를 그대로 또 보여주고 있음
즉 비동기 처리 작업이 성공했을 경우, 어떤 '일'을 해서 만들어지는 명확하게 변환하는 함수임 */

const requestData2 = () =>
    new Promise(resolve => setTimeout(() => resolve(2), 2 * 1000))
const requestData3 = () =>
    new Promise(resolve => setTimeout(() => resolve(3), 1 * 1000))

// 세 개의 비동기 처리를 순차적으로 처리
const result = [];
requestData1()
    .then(value => {
        result.push(value);
        return requestData2();
    })
    .then(value => {
        result.push(value);
        return requestData3();
    })
    .then(value => {
        result.push(value);
        console.log(result);    // [ 1, 2, 3 ] 약 6초 소요
    })
    .catch(console.error);
```

첫 번째 비동기 처리에 3초, 두 번째에 2초, 마지막에 1초 : 총 약 6초가 소요된다.

그러나 위 예제의 비동기 처리는 서로 의존하지 않고 개별적으로 처리되기 때문에(앞 비동기 처리의 결과가 뒷 비동기 처리에 영향을 주지 않음) 굳이 이렇게 할 필요가 없다.

`Promise.all`을 사용해 세 개의 비동기 처리를 `병렬`로 처리해보자.

```jsx
const requestData1 = () =>
    new Promise(resolve => setTimeout(() => resolve(1), 3 * 1000))
const requestData2 = () =>
    new Promise(resolve => setTimeout(() => resolve(2), 2 * 1000))
const requestData3 = () =>
    new Promise(resolve => setTimeout(() => resolve(3), 1 * 1000))

// 세 개의 비동기 처리를 병렬로 처리
Promise.all([requestData1(), requestData2(), requestData3()])
    .then(console.log)    // [ 1, 2, 3 ] 약 3초 소요
    .catch(console.error);
```

- `인수`로 `이터러블`을 전달받는다(주로 프로미스를 요소로 갖는 배열 등)
- 전달받은 모든 프로미스가 fulfilled가 되면 resolve 된 처리 결과를 배열에 저장해 그 배열을 resolve하는 새로운 `프로미스`를 `반환`한다 → 즉, 작업에 소요되는 시간은 가장 늦게 fulfilled가 되는 프로미스의 처리 시간 + @
- 처리 순서가 보장된다 : 위 예제처럼 첫 번째 프로미스가 가장 늦게 fulfilled 상태가 되어도, 첫 번째 프로미스의 처리 결과부터 차례대로 저장해 반환한다
- 인수로 전달받은 배열의 프로미스가 **하나라도 rejected상태가 될 경우** **즉시 종료**한다. 다른 프로미스 기다리지 않는다.  위 예제를 에러 예제로 바뀌면 Error 3이 뜰 것이다(1초로 젤 빠르니까)
- 인수로 전달받은 이터러블의 요소가 프로미스가 아니어도 Promise.resolve로 암묵적 wrapping하여 작업한다.

```jsx
Promise.all([
    1,  // Promise.resolve(1)
    2,  // Promise.resolve(2)
    3,  // Promise.resolve(3)
])
    .then(console.log)
    .catch(console.error);
```

> 깃허브 아이디로 깃허브 사용자 이름 취득하기 (3개의 비동기 → 병렬 처리) 예제
> 

```jsx
// GET 요청을 위한 비동기 함수
const getUserInfo = url => {
    return new Promise((resolve, rejected) => {
        const xhr = new XMLHttpRequest();
        xhr.open(`GET`, url);
        xhr.send();

        xhr.addEventListener(`load`, () => {
            if (xhr.status === 200) resolve(JSON.parse(xhr.response));
            else rejected(new Error(xhr.status));
        });
    });
};

const githubIds = [`Mark`, `JungWoo`, `Kang`];

// in : map으로 각 요소를 순회하며 getUserInfo로부터 3개의 프로미스를 받아옴 
// out : 모든 프로미스가 resolve(비동기 처리 성공)가 되면 각 user의 정보가 담긴 객체로 이루어진 배열을 프로미스로 반환 
Promise.all(githubIds.map(id => getUserInfo(`https://api.github.com/users/${id}`)))
    // in : 3개의 user 객체
    // out : map으로 각 요소를 순회하여 이름(name 프로퍼티)만을 추출 -> 배열에 저장해 새로운 프로미스로 반환
    .then(users => users.map(user => user.name))
    .then(console.log)
```

## Promise.race

> 가장 먼저 `fulfilled 상태`(resolve 호출됨)가 된 프로미스의 처리 결과만을 resolve하는 새로운 프로미스를 반환
> 
- all 메서드와 동일하게 프로미스가 요소인 이터러블을 인수로 받는다
- 하나라도 rejected가 되면 에러를 rejected하는 새로운 프로미스를 즉시 반환한다

## Promise.allSettled

> 전달 받은 프로미스가 모두 `settled`(fulfilled든 rejected든 완료만 되면 OK)가 되면 처리 결과를 배열로 반환
> 
- 성공/실패와는 상관없이 모든 프로미스들의 처리 결과가 담겨있다.

```jsx
Promise.allSettled([
    new Promise(resolve => setTimeout(() => resolve(1), 2 * 1000)),
    new Promise((_, rejected) => setTimeout(() => rejected(new Error(`Error!`)), 1 * 1000)),
])
    .then(console.log);

/*     [
        { status: 'fulfilled', value: 1 },
        {
          status: 'rejected',
          reason: Error: Error!
              at Timeout._onTimeout (c:\Users\khy00\Documents\javascript\220726\promise-allsettled.js:3:60)
              at listOnTimeout (node:internal/timers:559:17)
              at processTimers (node:internal/timers:502:7)
        }
      ] */
```

# 마이크로태스크 큐

> 프로미스의 후속 처리 메서드의 콜백 함수는 태스크 큐가 아닌 `마이크로태스크 큐`에 일시 저장되며, 이는 태스크 큐보다 우선순위가 높으므로 프로미스 후속 처리 메서드가 더 먼저 실행된다.
> 

```jsx
// 비동기 프로그래밍이란, 블로킹 없는 일차선 도로이다

Promise.resolve()
    .then(() => console.log(2))
    .then(() => console.log(3));
// 프로미스 후속 처리 메서드를 통한 연쇄 작업
// 2 출력 -> 3 출력

setTimeout(() => console.log(`a`));

Promise.resolve()
    .then(() => console.log(`b`))
    .then(() => console.log(`c`));
// 출력 순서 예상 : a -> b -> c
// 실제 출력 : b -> c -> a

// 같은 비동기 처리에도 우선 순위가 있다
// 비동기 처리는 비동기 함수 호출(call stack) -> 콜백 함수 호출(task queue -> call stack) 과정이 일반적인데
// 프로미스는 task queue가 아닌 microtask queue/job queue에 저장된다
// microtask queue는 task queue보다 우선순위가 높다
// event loop는 call stack이 비면 microtask queue -> task queue 순으로 함수를 가져와 실행한다
```

# fetch

> **HTTP 응답을 나타내는 Response 객체를 wrapping한 Promise 객체를 반환**하는 Web API
> 

XMLHttpRequest 객체와 유사하게 HTTP 요청 전송 기능을 제공하는데

- 보다 사용법이 간단함
- 프로미스를 지원 → 콜백 패턴의 단점(콜백 헬, 에러 처리 힘듦)에서 자유로움

```jsx
fetch(url, [, options])
```

### fetch 함수로 GET 요청 전송하기

첫 번째 인수로 url만 전달하면 끝.

```jsx
fetch(`http://블라블라`)
    .then(response => console.log(response));
```

fetch는 Response 객체(HTTP 응답)를 래핑한 `프로미스`를 반환하므로 `then`을 통해 프로미스가 resolve한 Response객체를 전달받을 수 있다.

이 Response 객체는

- HTTP 응답에 대한 다양한 정적 프로퍼티를 제공한다.
- HTTP 응답 몸체를 위한 다양한 프로토타입 메서드를 제공한다.
    - Response.prototype.json : Response 객체에서 HTTP 응답 몸체만을 취득하여 역직렬화함 (XMLHttpRequest에서는 따로 메서드까지 써가면서 application/json 인수로 보냈어야 가능)




```jsx
fetch(`https://jsonplaceholder.typicode.com/posts/1`)
    // in : fetch의 out : HTTP 응답이 담긴 Response 객체
    // out : json 메서드를 사용 -> HTTP 응답 몸체만을 취득하여 역직렬화
    .then(response => response.json())
    .then(console.log);
```

![fetch](https://user-images.githubusercontent.com/97890886/181025208-1812860c-265e-40ae-87eb-cc6ac5aca17a.png)


### 에러 처리에 주의하라

fetch가 반환하는 프로미스는 기본적으로 HTTP 에러를 **쌩깐다**. 에러를 reject하지 않고 Response.ok가 false인 Response 객체를 resolve한다. 아주 근본적인 네트워크 장애(오프라인) 등에만 reject한다. 즉, HTTP 요청이 실패해도(잘못된 URL 전달로 인한 404 Not Found 에러 등) 에러 처리를 하지 않는다는 것이다.

```jsx
// fetch는 HTTP 에러를 캐치하지 못한다
worngUrl = `hahahaha.com.XXX`;

fetch(webkitURL)
    .then(console.log(`good`))
    .catch(console.error(`bad`));
// good
```

> fetch 함수 사용 시, 반환한 프로미스의 ok 프로퍼티의 불리언 값을 확인하여 **명시적으로 에러를 처리**해야 한다.
> 

```jsx
// 명시적 에러 처리
fetch(worngUrl)
    .then(response => {
        if(!response.ok) throw new Error(response.statusText);
        return response.json();
    })
    .then(console.log)
    .catch(console.error);
```

> `axios`를 대신 사용해도 된다.
> 

모든 HTTP 에러를 reject하는 프로미스를 반환하기 때문에 모든 에러를 catch에서 처리할 수 있어 편리하다. fetch보다 다양한 기능을 지원한다.

### fetch함수로 HTTP 요청 전송하기

```jsx
const request = {
    get(url) {
        return fetch(url);
    },
    post(url, payload) {
        return fetch(url, {
            method: `POST`,
            headers: { 'Content-Type': `application/json` },
            body: JSON.stringify(payload)
        });
    },
    patch(url, payload) {
        return fetch(url, {
            method: `PATCH`,
            headers: { 'Content-Type': `application/json` },
            body: JSON.stringify(payload)
        });
    },
    delete(url) {
        return fetch(url, { method: `DELETE`});
    }
};

request.get(`https://jsonplaceholder.typicode.com/posts/1`)
    .then(res => {
        if (!res.ok) throw new Error(res.statusText);
        return res.json();
    })
    .then(console.log)
    .catch(console.error);

request.post(`https://jsonplaceholder.typicode.com/posts/`, {
    userId : 1,
    title : `Hi`,
    content : `good morning!`
})
    .then(res => {
        if (!res.ok) throw new Error(res.statusText);
        return res.json();
    })
    .then(console.log)
    .catch(console.error);

request.patch(`https://jsonplaceholder.typicode.com/posts/1`), {
    title: `yo`
}
    .then(res => {
        if (!res.ok) throw new Error(res.statusText);
        return res.json();
    })
    .then(console.log)
    .catch(console.error);

request.delete(`https://jsonplaceholder.typicode.com/posts/1`)
    .then(res => {
        if (!res.ok) throw new Error(res.statusText);
        return res.json();
    })
    .then(console.log)
    .catch(console.error);
```