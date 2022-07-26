# 비동기 프로그래밍
자바스크립트 엔진은 single thread지만, 브라우저에서 별도의 API와 이벤트 루프, 태스크 큐 등을 통해 비동기적 asynchronous 처리를 거치게 된다.

# 자바스크립트 엔진은 싱글 스레드이며 동기 처리 방식으로 동작한다

> 자바스크립트 엔진은 한 번에 하나의 태스크만 실행할 수 있으며 동시에 2개 이상의 함수를 실행할 수 없고, 현재 실행 중인 실행 컨텍스트들은 전부 “대기중”상태이다.
> 

자바스크립트에서 함수를 호출하면 다음과 같은 과정을 거친다.

1. 함수 코드가 평가되어 함수 실행 컨텍스트가 생성됨
2. Call Stack에 함수 실행 컨텍스트가 push되고, 함수 코드가 실행됨
3. 함수 코드 실행이 종료되면 함수 실행 컨텍스트는 Call Stack에서 pop되어 제거됨

즉, Call Stack는 코드의 전반적인 실행 **순서**를 관리하며 함수는 호출된 순서대로 Call Stack에 push 및 pop된다.(LIFO)

## 동기 VS 비동기

![blocking](https://user-images.githubusercontent.com/97890886/179215335-66377509-bef6-4e45-99a7-cfaed282f124.png)

- 동기 처리 방식 : 실행 순서가 보장되지만 블로킹이 일어난다
- 비동기 처리 방식 : 실행 순서가 보장되지 않지만 블로킹이 발생하지 않는다

### 블로킹(blocking)

> 동기 처리 방식에서 발생하는 작업 중단
> 

single thread 방식에서 동기(synchronous) 처리 방식으로 작업을 처리할 경우 현재 실행 중인 태스크가 종료될 때까지 다음에 실행될 태스크가 대기하는데, 이 때 필연적으로 블로킹이 발생한다.

```jsx
function foo() {
    console.log(`foo`);
}

function goo() {
    console.log(`goo`);
}

// 함수 sleep은 일정 시간(delay)만큼 경과한 이후 콜백 함수(func)를 호출한다
function sleep(func, delay) {
    // Date.now()는 현재 시간을 ms로 반환한다
    const delayUntil = Date.now() + delay;

    while (delayUntil > Date.now()) {
        func();
    }
}

// sleep 함수는 3초 동안 실행된다
// 이 때 goo 함수는 의도치 않게 3초 이상 블로킹된다
sleep(foo, 3 * 1000);
goo();
```

### 비동기(asynchronous)는 블로킹이 발생하지 않는다

> 현재 실행 중인 태스크가 종료되지 않은 상태라 하더라도 다음 태스크가 곧바로 실행된다
> 

```jsx
// 타이머 함수 setTimeout는 일정 시간(3초)이 경과한 후에 콜백 함수 (foo)를 호출한다
// 비동기적으로 동작한다 -> 함수 goo를 블로킹하지 않는다
setTimeout(foo, 3 * 1000);
goo();
```

타이머 함수 setTimeout과 setInterval, HTTP 요청, 이벤트 핸들러 등이 비동기 방식으로 동작한다.

# 브라우저가 자바스크립트의 동시성을 지원한다

자바스크립트는 싱글 스레드지만 평소 웹에서는 그 한계가 명확히 느껴지지 않는다 : 자바스크립트 엔진을 구동하는 환경(브라우저 또는 Node.js)이 자바스크립트의 동시성(concurrency)을 지원하기 때문이다.

![asynchronous](https://user-images.githubusercontent.com/97890886/179215346-27ea743b-8ce3-4698-a0a7-bbc042949a24.png)

## 자바스크립트 엔진의 구조

### Call Stack

실행 컨텍스트 스택. 소스코드 평가 과정에서 생성된 실행 컨텍스트가 push 및 pop 되는 스택 자료구조. 자바스크립트 엔진은 single thread 이므로 최상위(실행 중인) 실행 컨텍스트가 종료되어 pop되기 전까지는 다른 어떤 작업도 실행되지 못한다.

### Heap

객체를 저장하는 메모리 공간으로, 크기가 정해져 있지 않은 데이터 타입인 객체의 특성상 런타임 도중 동적 메모리 할당이 필연적이므로 스택과 달리 구조화되어있지 않다. 마치 자유로운 빈 창고.

## 브라우저의 비동기 처리

비동기 처리에서 자바스크립트 엔진은 태스크가 요청되면 콜 스택으로 순차적으로 처리할(소스코드의 평가 및 실행) 뿐,  실질적인 모든 처리는 브라우저 또는 Node.js가 담당한다. 예를 들어 setTimeout의 비동기 처리의 경우 :

- 자바스크립트 엔진이 하는 일 : 콜백 함수의 평가와 실행
- 브라우저 환경이 하는 일 : 호출 스케줄링을 위한 타이머 설정, 콜백 함수의 등록 등…

> 브라우저 환경은 이를 위해 `태스크 큐`와 `이벤트 루프`를 제공한다.
> 

### 태스크 큐 task queue / event queue / callback queue

비동기 함수의 콜백 함수나 이벤트 핸들러가 일시적으로 보관되는 영역.

### 이벤트 루프 event loop

JS 엔진(콜 스택과 힙)과 태스크 큐를 빙빙 돌면서 “코드가 굴러가는 꼬라지”를 감시한다. 콜 스택이 비어 있고 태스크 큐에 대기 중인 함수가 있다면 이벤트 루프가 FIFO으로 대기 중인 함수를 순차적으로 콜 스택으로 데려간다.