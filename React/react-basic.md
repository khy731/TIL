# 리액트에서 CSS 사용학이

## 인라인 스타일

객체로 전달. 카멜 케이스 사용. 잘 사용되지 않는 방법이다.

## .CSS

각 컴포넌트에 개별적으로 CSS를 import하여 스타일을 작성.

기본적으로 글로벌 네임스페이스를 공유하기 때문에 스타일이 그 컴포넌트에만 종속되지 않는다. 즉 서로 다른 CSS 파일들끼리 클래스명이 충돌하는 경우 나중에 파싱되는 자식 스타일이 기존 스타일을 덮어씌울 수 있다. → `Module CSS`로 해결할 수 있다.

## Module CSS

> 각 컴포넌트에 CSS가 온전하게, 순수하게 종속되게끔 해준다.
> 

글로벌이 아닌 컴포넌트별로 컴파일되므로 작성하기 편하고 CSS에서 가장 골치아픈 네이밍, 상수, 오버라이딩을 원컷으로 해결할 수 있다. 

1. 편의상 CSS의 파일명을 ###.module.css로 바꿔 준다.
2. 컴포넌트에서 CSS를 그냥 import 하는 것이 아닌, import `styles`로 키워드를 변경해준다.
3. 클래스 사용법도 다르다: 객체의 프로퍼티처럼 {styles.###}과 같은 형식으로 써준다

# Handling Events

## 미리 함수로 만들어놓고 전달

보기에 깔끔함. 전달할 때 식별자를 전달해야 함에 주의. 호출문을 전달할 시 반환값이 할당된다.

## 직접 작성

말 그대로 내부에다가 콜백함수를 직접 써줌. 장점은 매개변수 전달이 가능하다는 것. 미리 만들어놓고 ‘전달만’하는 경우 호출을 할 수 없음=매개변수를 전달할 수 없음. 이 방식으로는 매개변수 전달 가능

# state, useState

> state는 왜 필요한가?
> 

state가 없어도 내부적으로는 변수가 변경이 된다.(console.log에 변수를 찍어보면 변경되는 것이 보인다)그러나 **이것이 화면에 렌더링되지는 않는다.** 즉 DOM 변경이 일어나지 않는다. 실제로 바닐라JS 코드로 DOM을 수동 업데이트 해줄 경우 동작은 한다.

React 요소는 단편적이며, 마치 스냅샷이며, 한 번 생성되면 변하지 않는 상수적인 것이고 컴포넌트가 관리하는 상태값이 아니다. 단순 변수로는 React는 변수의 변화를 인지하지 못한다. → UI를 업데이트해주지 않는다.

> 이 때 useState를 사용하여 상태-state-를 제어한다.
> 

중요한 것은 동일한 컴포넌트를 여러개 호출해도, 각각의 state는 각각의 컴포넌트에 종속된다는 것.

# props

props로 받은 값은 변경할 수 없지만, props를 건네는 입장(부모 컴포넌트)에서는 그것이 state일 수 있으므로 이 경우 부모 컴포넌트의 state가 변경되면 자식의 props도 변경된다 (→ 리렌더 발생)

# react-router-dom

BrowserRouter로 전부를 감싸고 “갈아끼우고 싶은 부분”을 Router, 각 페이지를 Route로 두는 것이 라우팅의 기초이다. (페이지, 컴포넌트를 갈아끼우는 느낌)

## uesParams()

> 일종의 **동적** 페이지 라우팅. 보통 상세 페이지를 로드하는 데에 사용한다.
> 
1. 상세 페이지를 설정하고 (/word/1, /word/2)
2. 그 페이지의 params를 Route에서 콜론과 매개변수로 받아준다 (/:id) 매개변수가 받아오게 될 페이지 정보는 당연히 따로 코딩해주어야 한다.
3. 이후 페이지(컴포넌트)에서 매핑을 위해 매개변수(에 따른 상세 페이지)를 사용하고 싶으면 useParams로 받아온다.

## 쿼리 스트링

> db에서 특정 정보만 보여주고 싶을 때 아주 유용.
> 

데이터를 전부 불러와서 배열 고차 함수로 다듬는 것 보다, 가져오고 싶은 데이터만 선택적으로 가져오는 것이 편하기 때문이다.

`쿼리 스트링`이란 `url`에서 `?` 뒤에 써져있는 정보들이다. **useParams와 달리 페이지 라우팅에 영향을 끼치지 않는다. 즉 쿼리 스트링은 페이지로 인식되지 않는다. 그냥 페이지에 대한 추가 정보 같은 존재이다.**

예를 들어,

- `useParams`에서는 `home/1`과 같은 상세 페이지를 다른 작업(매개변수나 useParams 사용 등) 없이 불러올 수 없다. Route에서 :매개변수 와 usePrarms로 매핑을 해줘야한다.
- 그런데 `쿼리스트링`을 사용한`home/?mode=dark` 과 같은 주소는 그냥 `home/`으로 매핑된다. 쿼리 스트링의 정보는 `searchParams`로 꺼낼수 있다.

## useNavigate()

> 보통 컴포넌트 강제 이동이 필요할 경우 사용한다.
> 

코드 흐름의 전환이 필요 > Link로는 구현하기 힘들다 > 함수로 페이지를 이동해보자!

즉 Link의 기능(경로 옮기기) 등을 **함수**로 구현한 것이다. 예를 들어, 뒤로가기 기능은 navigate 함수에 `-1만` 인수로 넣어주면 아주 간단하게 구현이 가능하다.

# json-server, REST API

사용자가 조작을 통해 아무리 브라우저 화면을 변경해도 F5 클릭 한 번이면 다시 기존 페이지로 되돌아간다. 즉, 사용자의 입력을 **저장하고 이를 데이터베이스로 구축 및 클라이언트 측과 소통하는 `서버`**가 필요한 것. 서버를 따로 구축하기는 귀찮으니  json server를 사용해보자.

직접 만든 데이터베이스인 db.json을 json server로 띄운다.

이후 json server측에서 기본적으로 제공하는 REST API를 사용해 다양한 기능을 구현해보자.

- Create: `POST`
- Read: `GET`
- Update: `PUT`
- Delete: `DELETE`

# useEffect, fetch: PUT, DELETE, POST

- PUT (수정)

```jsx
const toggleDone = () => {
        // setDone(!done);
        fetch(`http://localhost:3001/words/${word.id}`, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                ...word,
                isDone: !done
            })
        })
        .then(res => {
            if (res.ok) setDone(!done);
        });
    };
```

체크박스 체크 여부만을 수정하는 경우이다.

- 쿼리 스트링을 전달하며 fetch 호출 → 특정 데이터만을 수신
- 스프레드 문법으로 본래 데이터와 변경된 체크박스 체크 여부를 전달

그러나 서버와의 통신으로 변경된 데이터는 **새로고침을 해야만 변경**되므로, 페이지가 바로바로 바뀌는 React의 특색(SPA)이 부각되지 않는다.

→ 수신된 데이터(res)가 정상적일 경우, fetch를 통한 API 통신 말고도 프론트엔드 상에서도 체크박스 체크 여부를 변경해준다.

- DELETE (삭제)

```jsx
const remove = () => {
        if (window.confirm('삭제하시겠습니까?')) {
            fetch(`http://localhost:3001/words/${word.id}`, {
                method: 'DELETE',
            })
            .then(res => {
                if (res.ok) setLocalWord({
                    id: 0,
                })
            });
        }
    };

if (localWord.id === 0) return null;
```

요소의 id를 0으로 만들고 **id가 0인 요소는 기존 return문(React 요소)을 만나기 전에 먼저 `null`을 반환하게끔 함**으로써 db에서 완전히 삭제한다.

- POST (추가)

```jsx
const onSubmit = () => {
        if (window.confirm('추가하시겠습니까?')) {
            fetch(`http://localhost:3001/days`, {
                method: "POST",
                headers: {
                    "Content-Type": "application/json",
                },
                body: JSON.stringify({
                    days: days.length +1
                })
            })
            .then(res => {
                if(res.ok) {
                    alert('생성 완료!');
                    navigate(`/`);
            }})
        }
    };
```

`POST` 요청은 id를 따로 명시하지 않아도 괜찮으므로 나머지 요소인 days만 증가시켜줬다.

생성이 완료된 후, `useNavigate`를 통해 **경로를 강제 이동**하여 생성된 내용을 바로 확인할 수 있게끔 하였다.

전달할 새 값은 `useRef`를 사용하여 `useRef.current.value`로 전달해줬다

# Custom Hooks

중복되는 기능을 React Hook으로 직접 만들어, 컴포넌트에서 `import`하여 사용할 수 있다.

```jsx
import { useState, useEffect } from "react";

const useFetch = (url) => {
    
    const [data, setData] = useState([]);

    const getData = async() => {
        const res = await fetch(url)
                    .then(res => res.json())
        setData(res);
    };

    useEffect(()=> {
        getData();
    },[url]);

    return data;
};

export default useFetch;
```

fetch()로 json server로부터 데이터를 받아오고 json()메서드로 적당히 가공하여, 이를 useEffect로 호출해 필요한 `초깃값`을 얻을 수 있게끔 커스텀 Hooks를 제작하였다.