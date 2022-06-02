# 이벤트 드리븐 프로그래밍

처리해야 할 특정 사건이(클릭, 키보드 입력, 마우스 이동) 발생하면 브라우저는 이를 감지하여 특정한 타입의 `이벤트`를 발생시킨다.만약 이러한 이벤트에 반응하여 어떤 **일**을 하고 싶다면, 이벤트가 발생했을 때 호출될 **함수(**`이벤트 핸들러`)를 브라우저에게 알려 호출을 위임(`이벤트 핸들러 등록`)한다.

이런 (”일”을 해줄)함수, 즉 이벤트 핸들러는 언제 호출될지(사용자가 언제 버튼을 클릭할 지) 개발자는 알 수 없으므로 미리 코딩-명시적으로 정해놓기-할 수 없다. → 사용자의 동작을 감지할 수 있는 브라우저에게 위임한다.

```jsx
<!DOCTYPE html>
<html lang="ko">
<head>
    <title>button event</title>
    <style>
        button {
            width: 100px;
            margin: 0 auto;
            height: 100px;
            text-align: center;
            background-color:palevioletred;
            font-size: large;
            font-weight: bolder;
        }
    </style>
</head>
<body>
    <button>Click Me!</button>
    <script>
        const $button = document.querySelector(`button`);
        $button.onclick = () => {alert(`WoW! You Clicked Me! hahaha`);};
    </script>
</body>
</html>
```

![Animation.gif](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/f2d7e96b-a32a-4776-a353-2f04dede773b/Animation.gif)

# 이벤트 타입

약 200여가지가 있다.

- 마우스 이벤트
- 티보드 이벤트
- 포커스 이벤트
- 폼 이벤트
- 값 변경 이벤트
- DOM 뮤테이션 이벤트
- 뷰 이벤트
- 리소스 이벤트

# 이벤트 핸들러 등록

이벤트가 발생하면 브라우저에 의해 호출될 함수(이벤트 핸들러)를 등록해 보자.

## 이벤트 핸들러 어트리뷰트 방식

HTML 요소의 어트리뷰트에는 이벤트와 1:1 대응하는 `이벤트 핸들러 어트리뷰트` 가 있다. on + 이벤트 타입으로 작명되어 있으며, 이벤트 핸들러 어트리뷰트의 값으로 문(**함수 호출문** 등)을 할당함으로써 이벤트 핸들러를 등록할 수 있다.

```jsx
<!DOCTYPE html>
<html lang="ko">
<head>
    <title>event</title>
</head>
<body>
    <button onclick="sayHi(`kang`)">Click Me!</button>
    <script>
        const sayHi = function(name) {
            console.log(`Hi, ${name}!`);
        }
    </script>
</body>
</html>
```

이벤트 핸들러 등록이란 함수 호출 자체를 브라우저에 위임하는 것이기 때문에 마치 콜백함수처럼 함수의 참조를 등록해야 한다(함수 호출문을 등록하는 경우 함수를 반환하는 함수를 등록해야 동일하게 동작할 것이다). 그런데 이 방식은 참조가 아닌 호출문을 전달하고 있다. 왜일까?

> 사실 이벤트 핸들러 어트리뷰트 값으로 호출문을 전달해도, 참조를 전달한 것과 유사하게 동작한다.
> 

즉, onclick="sayHi(`kang`)" 어트리뷰트는 파싱되어

암묵적으로 이벤트 핸들러의 함수를 생성하고

```jsx
// 이벤트 핸들러 어트리뷰트 값은
// 사실 (암묵적으로 생성될) 이벤트 핸들러의 함수 몸체이다
function onclick(event) {
    sayHi(`kang`);
}
```

동일한 이름의 키 onclick 이벤트 핸들러 프로퍼티)에 할당된다.

![button.PNG](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/00977921-942c-45ab-b717-e802c5d35cf0/button.png)

> 이렇게 복잡하게 동작하는 이유는 이벤트 핸들러에 `인수`를 전달하기 위해서이다.
> 

어트리뷰트 값이 하나의 함수 몸체가 되기 때문에 여러 문을 작성할 수도 있다.

이벤트 핸들러 어트리뷰트 방식은 알아둘 필요는 있지만 상당히 구시대적이다. 프레임워크/라이브러리에선 사용할 일이 있을지도…

## 이벤트 핸들러 프로퍼티 방식

window 객체와 Document, HTMLElement 타입의 DOM 노드 객체는 이벤트의 대응하는 `이벤트 핸들러 프로퍼티`를 가지고 있다. 이름은 이전 방식과 동일하며, **프로퍼티에 함수를 바인딩**하면 이벤트 핸들러가 등록된다.

이벤트 타깃(이벤트를 발생시킬 객체, $button)과 이벤트 타입(이벤트 종류, onclick)을 지정해야 한다.

```jsx
<!DOCTYPE html>
<html lang="ko">
<head>
    <title>event</title>
</head>
<body>
    <button>클릭해보세요!</button>
    <script>
        const $button = document.querySelector(`button`);
        function sayWorld() {
            console.log(`Hello, World!`);
        }

        // 이벤트 핸들러 프로퍼티에 이벤트 핸들러 바인딩
        $button.onclick = sayWorld;

        // 여러 개의 이벤트 핸들러 할당 불가
        // 이전에 할당했던 값이 재할당에 의해 덮어씌워짐
        $button.onclick = function() {
            console.log(`hahaha`);
        }
    </script>
</body>
</html>
```

이벤트 핸들러 어트리뷰트 방식과 결과적으로 동일하다. 어트리뷰트 방식도 결국 DOM 노드 객체로 파싱되어 이벤트 핸들러 프로퍼티로 변환되기 때문이다.

- 장점 : 어트리뷰트 방식과 달리 HTML과 JS를 구분 가능함
- 단점 : 1 프로퍼티 1 이벤트 핸들러 만 가능 (여러개 못함, 중복 할당 시 덮어쓰기 취급됨)

## addEventListener 메서드 방식

DOM level 2에서 도입된(앞 두 방식은 DOM level 0에서부터 사용됐다) `EventTarget.prototype.addEventListener 메서드`를 사용하여 이벤트 핸들러를 등록한다.

```jsx
EventTarget.addEventListener(`eventType`,`functionName`,[, useCapture]);
```

- 첫 번째 매개변수 : 이벤트 타입(on 접두사 X)
- 두 번째 매개변수 : 이벤트 핸들러(함수명)
- 세 번째 매개변수 : 이벤트 전파 단계 지정(T - 캡쳐링, F - 버블링)

```jsx
<!DOCTYPE html>
<html lang="ko">
<head>
    <title>event</title>
    <style>
        div {
            width: 200px;
            height: 100px;
            margin: 0 auto;
            background-color: palegreen;
            font-weight: bold;
            text-align: center;
            line-height: 90px;
        }
    </style>
</head>
<body>
    <button>Double Click Me!</button>
    <script>
        const $button = document.querySelector(`button`);
        // 이벤트 핸들러 프로퍼티에 바인딩
        $button.onclick = function() {
            console.log(`you did it!`)
        }

        // addEventListener 메서드에 인수로 전달
        // 덮어씌어지지 않고 둘 다 호출됨
        // 하나 이상의 이벤트 핸들러 등록 가능! (호출 순서: 등록된 순서)
        $button.addEventListener(`click`, function() {
            console.log(`you did it again!`);
        })
        
    </script>
</body>
</html>
```

![Animation2.gif](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/b2591bd9-6d43-45ee-a917-111ea19144e5/Animation2.gif)

메서드 방식은 이벤트 핸들러 프로퍼티에 바인딩된 이벤트 핸들러에 아무런 영향을 주지 않으므로 다수의 이벤트 핸들러가 모두 호출된다. 즉 **여러 이벤트 핸들러를 등록 할 수 있다.**