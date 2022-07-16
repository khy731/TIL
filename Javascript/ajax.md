# Asynchronous JavaScript and XML

자바스크립트를 사용하여 브라우저가 서버에게 비동기 방식으로 데이터를 요청 → 서버가 응답한 데이터를 수신하여 웹페이지를 동적으로 갱신하는 프로그래밍 방식

Wen API(브라우저 제공)인 객체 XMLHttpRequest를 기반으로 동작 : HTTP 비동기 통신을 위한 메서드, 프로퍼티를 제공

이전의 웹 : 통 html만을 이용. 화면 전환 시 html을 통째로 서버로부터 전송받아 웹페이지 전체를 처음부터 다시 렌더링해야 했음

- 변경할 필요가 없는(이전 웹페이지와 차이가 없는)부분까지 리로드 → 불필요한 데이터 통신
- 처음부터 다시 하나하나 렌더링 → 화면 전환 시 깜빡이는 현상 등 너무 무거움
- 클라이언트 ↔ 서버 간 통신은 동기 방식으로 동작하므로, 서버로부터 응답을 받기 전 다른 처리는 블로킹됨 → 렉이 일어날수도

Ajax는 변경할 필요가 있는 데이터만 비동기 방식으로 서버로부터 받아 한정적으로 렌더링한다. → 브라우저에서도 어플리케이션과 유사하게 빠른 속도, 퍼포먼스, 화면 전환이 가능

# JSON (JavaScript Object Noation)

클라이언트와 서버 간 HTTP 통신을 위한 텍스트 데이터 포맷. 자바스크립트에 종속되지 않는 언어 독립형 데이터 포맷이므로 대부분의 프로그래밍 언어에서 사용할 수 있다.

## 표기 방식

```jsx
{
    "type": "java",
    "name": "Launch Current File",
    "request": "launch",
    "mainClass": "${file}"
}
```

- JS 객체 리터럴과 유사하게 키 + 값으로 구성된 순수 텍스트 형식이다
- 문자열 사용 시 반드시 `큰따옴표`만 사용할 것(작은따옴표 xxx)

### JSON.stringify

> 객체를 JSON 포맷의 문자열로 반환
> 

클라이언트가 서버로 객체를 전송하려면 객체를 문자열화(직렬화, serializing)해야 하는데, 이 때 이 메서드를 사용한다. 객체뿐만 아니라 배열도 변환한다.

```jsx
// JSON.stringify
// 객체르 JSON 포맷의 문자열로 변환
const json = JSON.stringify(obj);
console.log(typeof json, json);
// string {"name":"Jang","age":25,"alive":true,"job":["idol","model"]}

// 들여쓰기 추가
const prettyJson = JSON.stringify(obj, null, 2);

// 값의 타입이 Number이면 필터링되서 반환되지 않는 함수
function filter(key, value) {
    return typeof value === `number` ? undefined : value;
}

// JSON.stringify 메서드에 두 번째 인수로 함수 filter를 전달
const strFilterObject = JSON.stringify(obj, filter, 2);
console.log(typeof strFilterObject, strFilterObject);
/* string {
    "name": "Jang",
    "alive": true,
    "job": [
      "idol",
      "model"
    ]
  } */

// 배열을 JSON 포맷 문자열로 반환
const todos = [
    { id : 1, content : `coding`, conpleted : true},
    { id : 2, content : `eat`, completed : false}
]
const json2 = JSON.stringify(todos, null, 2);
console.log(json2);
/* [
    {
      "id": 1,
      "content": "coding",
      "conpleted": true
    },
    {
      "id": 2,
      "content": "eat",
      "completed": false
    }
  ] */
```

### JSON.parse

> JSON 포맷의 문자열을 객체로 변환
> 

서버에서 클라이언트에게 전송된 JSOM 데이터(문자열)을 객체화하여(역직렬화, deserializing) 사용할 수 있게 만든다.

```jsx
const obj = {
    name : `kang`,
    age : 22,
    job : false
};

const arr = [
    {id : 1, pass : 0000},
    {id : 2, pass : 9999}
]

const json = JSON.stringify(obj, null, 2);
const jsonArr = JSON.stringify(arr, null, 2);

console.log(JSON.parse(json));              // { name: 'kang', age: 22, job: false }
console.log(typeof JSON.parse(jsonArr));    // object
```

# XMLHttpRequest

자바스크립트를 사용해 HTTP 요청을 전송할 때 사용하는 객체. (JS를 사용하지 않고도 주소창, HTML의 a태그 등 브라우저 기본 제공 기능도 있긴 하지만 비동기-Ajax-를 사용하려면 이걸 쓴다)

XMLHttpRequest 객체는 HTTP 요청 전송/응답 수신을 위한 다양한 메서드/프로퍼티를 제공한다.

## 생성하기

> XMLHttpRequest 생성자 함수
> 

브라우저에서 제공하는 Web API이므로 브라우저 환경에서만 사용할 수 있다.

```jsx
const xtr = new XMLHttpRequest();
```

## 프로퍼티, 메서드

### 프로토타입 프로퍼티

- redayState : HTTP 요청의 현재 상태를 나타내는 정수로, 다양한 정적 프로퍼티들을 값으로 갖는다
    - EX) UNSENT : 0, OPENED : 1, …
- status : HTTP 요청에 대한 응답 상태(HTTP 상태 코드)를 나타내는 정수.
    - EX) 200
- statusText : HTTP 요청에 대한 응답 메시지 문자열.
    - EX) “OK”
- responseType : HTTP 응답 타입
    - EX) document, JSON, text, blob, arraybuffer…
- response : HTTP 요청에 대한 응답 [몸체]. responseType에 따라 타입이 달라짐
- responseText : 서버가 전송한 HTTP 요청에 대한 응답 문자열

### 이벤트 핸들러 프로퍼티

HTTP 요청에 대한 응답을 받기 시작한 경우, 에러가 발생한 경우, 요청 시간이 경과한 경우, 또는 응답을 받는 도중 주기적으로 발생하는 이벤트 등등에 대한 이벤트 핸들러 프로퍼티.

### 메서드

- open : HTTP 요청 초기화
- send : HTTP 요청 전송
- abort : 이미 전송된 HTTP 요청 전달
- setRequestHeader : 특정 HTTP 요청 헤더의 값을 설정
- setResponseHeader : 특정 HTTP 요청 헤더의 값을 문자열로 변환

### 정적 프로퍼티

- UNSET : 0
    - 메서드 호출 이전
- OPENED : 1
    - 메서드 호출 이후
- HEADERS_RECEIVED
    - send 메서드 호출 이후
- LOADING : 3
    - 서버 응답 중(아직 미완성~)
- LOADING : 4
    - 서버 응답 완료

## HTTP 요청 전송

1. XMLHttpRequest.prototype.open 메서드로 HTTP 요청을 초기화
2. (필요한 경우에만) XMLHttpRequest.prototype.setRequestHeader 메서드로 특정 HTTP 요청의 헤더 값 설정
3. XMLHttpRequest.prototype.send 메서드로 HTTP 요청을 전송

```jsx
// XMLHttpRequest 객체 생성
const xhr = new XMLHttpRequest();

// HTTP 요청 초기화
xhr.open(`GET`, `/users`);

// HTTP 요청 헤더 설정
// 클라이언트가 서버로 전송할 데이터의 MIME 타입을 json으로 지정
xhr.setRequestHeader(`content-type`, `application/json`);

// HTTP 요청 전송
xhr.send();
```

## open

> 서버에 전송할 HTTP 요청을 초기화
> 

```jsx
xhr.open(method, url[, async]);
```

- method : HTTP 요청 메서드(”GET”, “POST”, “PUT”, “DELETE” 등)
    - GET : 모든/특정 리소스 취득
    - POST : 리소스 생성
    - PUT : 리소스의 전체 교체
    - PATCH : 리소스의 일부 수정
    - DELETE : 모든/특정 리소스 삭제
- url : HTTP 요청을 전송할 URL
- async : 비동기 요청 여부(기본값: true)

### send

> open 메서드로 초기화된 HTTP 요청을 서버에 전송
> 

서버로 전송되는 데이터는 요청 메서드에 따라 전송 방식에 차이가 있다.

- GET : 데이터를 쿼리 문자열(query string, URL의 일부분)로 전송한다
- POST : 데이터(페이로드 payload)를 요청 몸체(request body)에 담아 전송한다

요청 몸체에 담아 전송할 데이터(페이로드)를 인수로 전달할 수 있는데, 페이로드가 객체인 경우 반드시 **직렬화(JSON.stringify)**한 후 전달해야 한다.

HTTP 요청 메서드가 GET인 경우 send 메서드에 페이로드로 전달한 인수는 **무시**되고 요청 몸체는 **null**로 설정된다.

### setRequestHeader

> 특정 HTTP 요청의 헤더 값 설정
> 

반드시 **open 메서드를 호출(초기화)한 이후**에 설정해야 한다.

자주 사용하는 HTTP 요청 헤더인 Context-type과 Accpet에 대해 알아보자.

- `Content-type` : 요청 몸체(body)에 담아 전송할 데이터의 MIME 타입의 정보를 표현

<aside>
👉 MIME 타입/서브타입…

- text/plain,html,css,javascript…
- application/json…
- multipart/formed-data…
</aside>

```jsx
// XMLHttpRequest 객체 생성
const xhr = new XMLHttpRequest();

// HTTP 요청 초기화
xhr.open(`GET`, `/users`);

// HTTP 요청 헤더 설정
// 클라이언트가 서버로 전송할 데이터의 MIME 타입을 json으로 지정
xhr.setRequestHeader(`content-type`, `application/json`);

// HTTP 요청 전송
xhr.send();
```

- `Accept` : HTTP 클라이언트가 서버에 요청할 때 서버가 응답할 데이터의 MIME 타입을 지정

```jsx
// Accept로 서버가 응답할 데이터의 MIME 타입 지정
xhr.setRequestHeader(`Accept`, `application/json`);
```

## HTTP 응답 처리

서버가 전송한 응답을 처리하려면 XMLHttpRequest 객체가 발생시키는 이벤트를 캐치해야 한다.

XMLHttpRequest 객체의 이벤트 핸들러 프로퍼티를 통해 HTTP 응답을 처리할 수 있다 : redayState(HTTP 요청의 현재 상태를 나타냄)프로퍼티 값이 변경되면 발생하는 이벤트 readystatechange 이벤트를 캐치해 처리

자세히 말하자면

send로 HTTP 요청을 서버에 전송 → 응답이 언제 올 지 클라이언트는 알 수 없음

readystatechange 이벤트의 발생(HTTP 요청의 현재 상태 redayState가 바뀔 때마다 이벤트 발생)을 보면서 HTTP 요청의 현재 상태를 확인해야 함 → readystatechange에 이벤트 핸들러를 할당하여 감시 : ex) readyState가 DONE(서버가 응답을 완료함)인지 확인하는 이벤트 핸들러 → 응답이 완료되면 status(요청에 대한 응답 상태)가 200인지 확인하여 정상 처리/에러 처리 구분 → 모든게 정상처리됐다면 response에서 데이터를 최종적으로 취득함 (에러가 났다면 에러 처리 하면 됨)

```jsx
// HTTP 요청 전송/응답 수신 예제
// 실제 통신에서는 필연적으로 서버가 필요 : JSONPlaceholder에서 제공하는 REST API로 대체

// XMLHttpRequest 객체 생성
const xhr = new XMLHttpRequest();

// HTTP 요청 초기화
// fake REST API 사용
xhr.open(`GET`, `https//jsonplaceholder.typicode.com/todos/1`);

// HTTP 요청 전송
xhr.send();

// readystatechange 이벤트 핸들러 등록
// readystate 프로퍼티(HTTP 요청의 현재 상태)가 변경될 때마다 이벤트 발생 -> 호출됨
xhr.addEventListener(`readystatechange`, () => {

    // 서버 응답이 완료(DONE)되지 않았다면 아무 일도 하지 않는다
    if (xhr.readyState !== xhr.DONE) return;

    // staus 프로퍼티(응답 상태 코드)가 200이면 정상적으로 응답된 것
    // 정상 응답 -> response 프로퍼티에 서버의 응답 결과가 담겨 있다
    if (xhr.status === 200) console.log(JSON.parse(xhr.response));
    // 에러 응답 -> 에러 처리
    else console.error(`Error`, xhr.status, xhr.statusText);
});
```

readystatechange 대신 load 이벤트를 캐치해도 좋다.

load 이벤트는 HTTP 요청이 성공적으로 완료한 경우에만 발생하므로 DONE 조건문을 안 써되 된다.