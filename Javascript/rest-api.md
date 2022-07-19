## REST(REpressnational State Transfer)

`HTTP`를 기반으로 클라이언트가 서버의 리소스에 접근하는 방식을 규정한 아키텍처. 클라이언트가 서버 데이터에 액세스하는 데 사용할 수 있는 GET, PUT, DELETE 등의 함수 집합을 정의한다. REST의 기본 원칙을 충실히 지킨 서비스 디자인을 “RESTful”하다고 한다.

## REST API

`REST`를 기반으로 서비스 `API`를 구현한 것.

- 오늘날 웹에서 볼 수 있는 가장 많이 사용되고 유연한 API이다
- 클라이언트가 서버에 요청을 데이터로 전송 → 서버가 이 클라이언트 입력을 사용하여 내부 함수를 호출 → 출력 데이터를 다시 클라이언트에 반환

### API

API는 정의 및 프로토콜 집합을 사용하여 두 소프트웨어 구성 요소가 서로 통신할 수 있게 하는 메커니즘. 컴퓨터와 인간을 연결시키는 사용자 인터페이스와 반대로, API는 **컴퓨터나 소프트웨어를 서로 연결**한다.

예를 들어, 기상청의 소프트웨어 시스템에 일일 기상 데이터가 들어 있다면 휴대폰의 날씨 앱은 API를 통해 이 시스템과 "대화"하고 휴대폰에 매일 최신 날씨 정보를 표시한다.

# REST API 구성

- `자원` resource

URI(엔드포인트)로 표현한다.

- `행위` verb

자원에 대한 행위. HTTP 요청 메서드로 표현한다. 

- `표현` representations

자원에 대한 행위의 구체적 내용. 페이로드로 표현한다.

> REST API는 자체 표현 구조(self-descriptveness)로 구성되었기 때문에 RESP API만으로도 HTTP 요청의 내용을 전부 이해할 수 있다.
> 

# REST API 설계 원칙

## `URI`는 리소스를 확실하게 표현할 것

URI는 리소스를 표현하는 데 집중해야 한다. 식별자명은 동사보다는 명사를 사용한다. (행위에 대한 표현은 권장하지 않는다)

```bash
# bad
GET /getTodos/1
GET /todos/show/1

# good
GET /todos/1
```

## 행위에 대한 정의는 `HTTP 요청 메서드`로 할 것

클라이언트는 `HTTP 요청 메서드`를 통해 서버에게 요청의 종류/목적(리소스에 대한 행위)을 알린다. 보통 5가지 메서드를 사용하여 CRUD를 구현한다.

### GET

index/retrieve. 모든/특정 리소스를 취득한다.

### POST

create. 리소스를 생성한다.

### PUT

replace. 리소스 전체를 교체한다.

### PACTH

modify. 리소스 일부를 수정한다.

### DELETE

delete. 모든.특정 리소스를 삭제한다.

```bash
# bad
GET /myData/delete/1

# good
DELETE /myData/1
```

즉, “데이터 자체”에 대한 표현과 “데이터를 처리하는 일”에 대한 표현을 명확하게 구분하라는 뜻이다. 

# JSON Server를 통한 REST API 실습

JSON Server를 사용해 가상 REST API 서버를 구축하여 HTTP 요청을 전송/응답을 수신해보자.

## JSON Server 설치

json 파일로 Virtual REST API 서버를 구축할 수 있는 툴. npm으로 설치한다.

```bash
# 디렉토리 생성 및 디렉토리 경로를 새로 생성된 폴더로 변경
$ mkdir json-server-test && cd json-server-test

# (npm으로 동작하는) 프로젝트를 초기화
# package.json이 생성된다
# -y : 어떠한 추가 질문도 하지 말고(yes) -> default 값의 package.json가 생성됨
$ npm init -y

# JSON Server 설치
# -g : 전역
# --save-dev : 프로젝트에 필요한 모듈(여기서는 JSON Server)을 관리하기 위한 일종의 백업 작업
$ npm install json-server -g --save-dev
```

## 테스트 파일 만들기(db.json)

리소스를 제공하는 데이터베이스 역할을 하는 db.json 테스트 파일을 만들어보자.

```json
{
    "todos" : [
        {
            "id" : 1,
            "content" : "7:00 wake up",
            "completed" : true
        },
        {
            "id" : 2,
            "content" : "8:00 running",
            "completed" : true
        },        
        {
            "id" : 3,
            "content" : "9:00 breakfast",
            "completed" : false
        }
    ]
}
```

## JSON Server 실행

`watch`옵션을 추가하여 db.json의 변경을 감지하게끔 JSON Server을 실행해보자.

```bash
# 기본 포트(3000) 사용
# watch 옵션 : 특정 파일의 변경을 감지
$ json-server --watch db.json
```

혹시 포트를 변경하고 싶을 때에는 `port` 옵션을 추가하면 된다.

```bash
# 포트 변경
$ json-server --watch db.json --port 5000
```

매번 명령어를 입력하는 번거로움을 줄이기 위해 `package.json` 파일을 수정하여 초기 단계를 줄여보자.

```json
// start라는 코드에 명령어를 치환
"scripts": {
    "start": "json-server --watch db.json",
  },

// 프로젝트 내 모듈들의 리스트
"dependencies": {
    "json-server" : "^0.17.0",
}
```

> `package.json`이란?
> 

개발자가 배포한 패키지에 대해, 다른 사람들이 관리하고 설치하기 쉽게 하기 위한 문서 파일. npm에 패키지를 배포/npm registry에 업로드하기 위해서는 반드시 필요하다.

- 자신의 프로젝트가 의존하는 패키지의 리스트
- 자신의 프로젝트의 버전을 명시
- 다른 환경에서도 빌드를 재생 가능하게 만들어, 다른 개발자가 사용하기 쉽게끔 함

즉, npm이라는 오픈소스 패키지 생태계를 사용하기 위한 명세이자, 프로젝트의 의존성 관리 및 배포를 위한 필수 지침서나 다름없다.

![1](https://user-images.githubusercontent.com/97890886/179755986-41fa72cc-ff44-4207-ae65-ad823514fc66.png)


## GET 요청

todos 데이터베이스(리소스)에서 모든 todo를 index(취득)한다.

1. JSON Server의 루트 폴더(/json-server-test)에 public 폴더를 생성
2. JSOM Server을 재실행
3. public 폴더에 get_index.html을 추가 → 브라우저에서 접속

### get.index_html

```jsx
<!DOCTYPE html>
<html lang="ko">
<head>
    <title>todos 리소스의 모든 todo를 index</title>
</head>
<body>
    <pre></pre>
    <script>
        // XMLHttpRequest 객체 생성
        const xhr = new XMLHttpRequest();

        // HTTP 요청 초기화
        // todos 리소스에서 모든 todo를 index(취득)
        xhr.open(`GET`, `/todos`);

        // HTTP 요청 전송
        xhr.send();

        // 응답된 데이터 취득
        // HTTP 요청이 성공적으로 완료된 경우 발생하는 load 이벤트에 이벤트 핸들러 할당
        xhr.addEventListener(`load`, () => {
            if (xhr.status === 200) document.querySelector(`pre`).textContent = xhr.response;
            else console.error(`Error`, xhr.status, xhr.statusText);
        });
    </script>    
</body>
</html>
```

![get-resources](https://user-images.githubusercontent.com/97890886/179756099-720cd1e5-1ba0-4b69-9d1d-d2cb8dac4c55.png)

todo 리소스에서 id를 사용하여 특정 todo만을 index해보자.

### get_retrieve.html

```jsx
// HTTP 요청 초기화
// todos 리소스에서 id를 사용하여 특정 todo만을 retrieve(취득)
xhr.open(`GET`, `/todos/3`);
```

![get-resource](https://user-images.githubusercontent.com/97890886/179756285-57d22eb3-c3dd-4313-a62b-837b6f13b8e5.png)

## POST 요청

todo 리소스에 새로운 todo를 생성한다. setRequestsHeader 메서드를 사용해야 한다: 요청 body에 (서버에 전송할)페이로드의 MIME 타입을 지정해야 한다.

public 폴더에 post.html을 생성하고 접속해보자.

### post.html

```jsx
<!DOCTYPE html>
<html lang="ko">
<head>
    <title>todos 리소스에 새로운 todo를 추가</title>
</head>
<body>
    <pre></pre>
    <script>
        // XMLHttpRequest 객체 생성
        const xhr = new XMLHttpRequest();

        // HTTP 요청 초기화
        // todos 리소스에 새로운 todo 생성
        xhr.open(`POST`, `/todos`);

        // 요청 body에 담아 서버로 전송할 페이로드의 MIME 타입 지정
        xhr.setRequestHeader(`content-type`, `application/json`);

        // HTTP 요청 전송
        // 페이로드를 서버에 전송한다
        xhr.send(JSON.stringify({id:4, content:`22:00 sleep`, completed:false}));

        // load 이벤트에 이벤트 핸들러 바인딩
        xhr.addEventListener(`load`, () => {
            if (xhr.status === 200 || xhr.status === 201) document.querySelector(`pre`).textContent = xhr.response;
            else console.error(`Error`, xhr.status, xhr.statusText);
            })
    </script>    
</body>
</html>
```

## PUT 요청

특정 리소스 `전체`를 교체한다. todos 리소스에서 id로 todo를 특정하여 id를 제외한 리소스 전체를 교체해보자. 역시 setRequestHeader 메서드를 사용해야 한다.

### put.html

```jsx
<!DOCTYPE html>
<html lang="ko">
<head>
    <title>id로 todo를 특정하여 리소스 전체를 교체</title>
</head>
<body>
    <pre></pre>
    <script>
        // XMLHttpRequest 객체 생성
        const xhr = new XMLHttpRequest();

        // HTTP 요청 초기화
        // todos 리소스에서 id로 todo를 측정하여 리소스 전체를 교체
        xhr.open(`PUT`, `/todos/4`);

        // 요청 body에 담아 서버로 전송할 페이로드의 MIME 타입 지정
        xhr.setRequestHeader(`content-type`, `application/json`);

        // HTTP 요청 전송
        // 페이로드를 서버에 전송한다 : 리소스 전체를 교체
        // id만 유지하고 나머지만 전부 바꿔보자
        xhr.send(JSON.stringify({id:4, content:`19:00 dinner`, completed:true}));

        // load 이벤트에 이벤트 핸들러 바인딩
        xhr.addEventListener(`load`, () => {
            if (xhr.status === 200) document.querySelector(`pre`).textContent = xhr.response;
            else console.error(`Error`, xhr.status, xhr.statusText);
            })
    </script>    
</body>
</html>
```

![get-resource2](https://user-images.githubusercontent.com/97890886/179756365-755d98f2-48c5-46b1-a800-ad001b26ed5d.png)


## PATCH 요청

특정 리소스의 `일부`를 수정한다. todos 리소스의 id로 todo를 특정하여 completed만 수정한다. setRequestHeader 메서드를 사용한다.

### patch.html

```jsx
<!DOCTYPE html>
<html lang="ko">
<head>
    <title>id로 todo를 특정하여 리소스 일부를 수정</title>
</head>
<body>
    <pre></pre>
    <script>
        // XMLHttpRequest 객체 생성
        const xhr = new XMLHttpRequest();

        // HTTP 요청 초기화
        // todos 리소스에서 id로 todo를 측정하여 리소스 일부를 수정
        xhr.open(`PATCH`, `/todos/4`);

        // 요청 body에 담아 서버로 전송할 페이로드의 MIME 타입 지정
        xhr.setRequestHeader(`content-type`, `application/json`);

        // HTTP 요청 전송
        // 리소스 일부 수정을 위해페이로드를 서버에 전송한다
        xhr.send(JSON.stringify({content:`shower`}));

        // load 이벤트에 이벤트 핸들러 바인딩
        xhr.addEventListener(`load`, () => {
            if (xhr.status === 200) document.querySelector(`pre`).textContent = xhr.response;
            else console.error(`Error`, xhr.status, xhr.statusText);
            })
    </script>    
</body>
</html>
```

![patch](https://user-images.githubusercontent.com/97890886/179756473-62b13347-790d-4582-b15c-123957e3f16e.png)


## DELETE 요청

todos 리소스에서 id를 사용하여 todo를 삭제한다.

### delete.html

```jsx
<!DOCTYPE html>
<html lang="ko">
<head>
    <title>id를 이용하여 todo를 삭제</title>
</head>
<body>
    <pre></pre>
    <script>
        // XMLHttpRequest 객체 생성
        const xhr = new XMLHttpRequest();

        // HTTP 요청 초기화
        // todos 리소스에서 id로 todo를 특정하여 삭제
        xhr.open(`DELETE`, `/todos/4`);

        // HTTP 요청 전송
        xhr.send();

        // load 이벤트에 이벤트 핸들러 바인딩
        xhr.addEventListener(`load`, () => {
            if (xhr.status === 200) document.querySelector(`pre`).textContent = xhr.response;
            else console.error(`Error`, xhr.status, xhr.statusText);
            })
    </script>    
</body>
</html>
```


![2](https://user-images.githubusercontent.com/97890886/179756618-801a574a-0453-442f-8a87-38ae601a4ae5.png)
