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

![1](https://user-images.githubusercontent.com/97890886/173191381-150d1da8-c35e-49e9-9be9-70844f26db42.gif)


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

![2](https://user-images.githubusercontent.com/97890886/173191387-d84e1884-3f6b-42e2-8b22-09ff666f7f94.png)

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

![3](https://user-images.githubusercontent.com/97890886/173191395-6ad2bd74-e631-4ecc-8899-c97380286d53.gif)

메서드 방식은 이벤트 핸들러 프로퍼티에 바인딩된 이벤트 핸들러에 아무런 영향을 주지 않으므로 다수의 이벤트 핸들러가 모두 호출된다. 즉 **여러 이벤트 핸들러를 등록 할 수 있다.**

# 이벤트 핸들러 제거

> EventTarget.prototype.removeEventListener 메서드
> 

addEventListner 메서드로 등록한 이벤트 핸들러를 제거할 수 있다. 인수는 addEventListner과 일치해야 한다.

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>이벤트 핸들러 제거</title>
</head>
<body>
    <button>Click me!</button>
    <script>
        const $button = document.querySelector(`button`);
        const handleClick = () => console.log(`clicked!`);

        // 이벤트 핸들러 등록
        $button.addEventListener(`click`, handleClick);

        // 이벤트 핸들러 제거
        // 등록때와 인수가 일치해야 한다
        $button.removeEventListener(`click`, handleClick);
    </script>
</body>
</html>
```

> 무명 함수를 이벤트 핸들러로 등록한 경우, **삭제가 불가능**하다.
> 

removeEventListener 메서드에 두 번째 인수로 전달한 이벤트 핸들러(삭제할 대상)는 addEventListner 메서드의 인수와 **동일한 함수**여야 하기 때문에, 이벤트 핸들러를 제거하기 위해서는 이벤트 핸들러의 참조를 변수/자료구조에 저장하고 있어야 한다.

```jsx
// 즉, 무명 함수를 이벤트 핸들러로 등록한 경우 제거가 불가능하다
// -> 이벤트 핸들러를 이후 제거하기 위해서는 이벤트 핸들러의 참조를 변수/자료구조에 저장해야 한다
$button.addEventListener(`dbclick`, () => console.log(`double clicked!`));
// 등록된 이벤트 핸들러를 참조할 수 없음 -> 동일한 인수 X -> 제거 불가
```

> 기명 이벤트 핸들러 내부적으로 removeEventListener 메서드를 호출하여 `단 한번만 이벤트 핸들러가 호출`되도록 이벤트 핸들러를 제거할 수 있다.
> 

```jsx
// 기명 이벤트 핸들러 내부에 제거 메서드 호출
// 한 번만 호출됨
$button.addEventListener(`keypress`, function foo() {
      console.log(`foo`);
      $button.removeEventListener(`keypress`, foo);
})

// 위와 동일하게 한 번만 호출되나, 무명 이벤트 핸들러 일 때
// arguments.callee(함수 자신을 가리킴)을 사용할 수도 있다
// 코드 최적화를 방해하므로 권장되지 않는다
 $button.addEventListener(`mousedown`, function() {
      console.log(`Hi`);
      $button.removeEventListener(`mousedown`, arguments.callee);
});
```

이벤트 핸들러 프로퍼티 방식으로 등록한 이벤트 핸들러는 이 메서드로 제거할 수 없으며, 이벤트 핸들러 프로퍼티에 `null`을 할당함으로써 제거한다.

```jsx
$button.ondblclick = null;
```

# 이벤트 객체

이벤트 객체는

1. 사용자의 행위(마우스 클릭 등)에 의해 생성되고

2. 자바스크립트 코드에 의해 인위적으로 생성된다.

이벤트가 발생하면 `이벤트 객체`(이벤트에 대한 다양한 정보가 담겨 있음)가 동적으로 생성되고, 이는 이벤트 핸들러의 **첫 번째 인수**로 전달된다. 즉, 이벤트 핸들러의 인수로 이벤트 객체(이벤트 발생 그 자체)를 전달받을 수 있다.

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>이벤트 객체</title>
</head>
<body>
    <p>클릭하면 클릭한 곳의 좌표가 표시됩니다</p>
    <em class="message"></em>
    <script>
        const $msg = document.querySelector(`.message`);
        function showCoords(e) {
            $msg.textContent = `x : ${e.clientX}, y : ${e.clientY}`;
        }
        
        document.addEventListener(`click`, showCoords);
    </script>
</body>
</html>
```

![Honeycam 2022-06-16 14-26-28.gif](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/9526d39b-dd1f-472f-a81e-7dbdd9ed1080/Honeycam_2022-06-16_14-26-28.gif)

단, 이벤트 핸들러 어트리뷰트 방식에서 이벤트 객체를 인수로 전달받기 위해서는 무조건 이벤트 핸들러의 **첫 번째 배개변수 이름**을 `event`로 해야 한다. 

```jsx
<em class="message" onclick="showCoords(event)"></em>
```

위 코드는 파싱되어 다음과 같은 함수(onclick 이벤트 핸들러)를 암묵적으로 생성하여 onclick 이벤트 핸들러 프로퍼티에 할당하는데, 이때 암묵적으로 생성된 onclick 이벤트 핸들러의 첫 번째 매개변수 이름이 암묵적으로 event로 명명되므로 꼭 event를 사용해야 한다.

```jsx
function onclick(event) {
            showCoords(event);
        }
```

## 이벤트 객체의 상속 구조

이벤트 객체는 상속 구조를 갖는데, 이들은 전부 `생성자 함수`이기 때문에 생성자 함수를 호출하여 직접 이벤트 객체를 생성할 수도 있다. 이벤트가 발생하면 암묵적으로 생성되는 이벤트 객체도 이러한 생성자 함수에 의해 생성되며, 이들은 전부 프로토타입 체인의 일원이 된다.

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>이벤트 객체의 상속 구조</title>
</head>
<body>
    <script>
        // Event 생성자 함수 호출 -> foo 이벤트 타입의 Event 객체 생성
        const eventFoo = new Event(`foo`);
        console.log(eventFoo);

        // MouseEvent 생성자 함수 호출 -> click 이벤트 타입의 MouseEvent 객체 생성
        // 상속 구조에 의해 Event.prototype과 UIEvent.prototype을 상속받음
        const mouse = new MouseEvent(`click`);
        console.log(`mouse`);
    </script>
</body>
</html>
```

`Event 인터페이스`는 DOM 내에서 발생한 이벤트에 의해 생성되는 이벤트 객체이며, 모든 이벤트 객체가 공통으로 갖는 프로퍼티가 정의되어 있다. 하위 인터페이스에는 이벤트 타입에 따른 고유 프로퍼티가 정의되어 있다. 이벤트 객체(와 그 프로퍼티)는 발생한 이벤트의 타입에 따라 달라진다.

### 공통 프로퍼티

Event.prototype에 정의되어 있는 이벤트 관련 프로퍼티는 모든 파생 이벤트 객체의 상속된다.

- type : 이벤트 타입
- target : 이벤트를 발생시킨 DOM 요소
- currentTarget : 이벤트 핸들러가 바인딩된 DOM 요소
- eventPhase : 이벤트 전파 단계
- bubbles : 이벤트를 버블링으로 전파하는가 여부
- cancelable : 이벤트 기본 동작을 취소가능한가 여부
- defaultPrevented : 이벤트를 취소했는지 여부
- isTrusted : 사용자의 행위에 의해 발생한 이벤트인지 여부
- timeStamp : 이벤트가 발생한 시각

체크박스 요소의 체크 상태가 변경되면 현재 체크 상태를 출력하는 코드

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>체크박스 체크 상태 출력</title>
</head>
<body>
    <input type="checkbox">
    <em class="message">off</em>
    <script>
        const $checkbox = document.querySelector(`input[type=checkbox]`);
        const $msg = document.querySelector(`em.message`);

        // e.target : change 이벤트를 발생시킨 DOM 요소($checkbox)
        // e.target.checked : $checkbox(체크박스 요소)의 현재 체크 상태
        $checkbox.onchange = e => $msg.textContent = e.target.checked ? `on` : `off`
    </script>
</body>
</html>
```

본 예제에서는 target 프로퍼티(이벤트를 발생시킨 요소)와 currentTarget 프로퍼티(이벤트 핸들러가 바인딩된 요소)가 같은 DOM 요소($checkbox)를 가리킨다. 대부분은 이게 일반적이지만, 이벤트 위임에서는 이 둘이 다를 수도 있다.

### 마우스 정보 취득

click, dbclick, mousedown, mousemove 등의 이벤트가 발생하면 생성되는 MouseEvent 타입의 이벤트 객체가 가진 고유 프로퍼티로 마우스 정보를 취득할 수 있다.

- 마우스 포인터의 좌표 정보 : screenX/Y, clientX/Y, pageX/Y, offsetX/Y
- 버튼 정보 : altKey, ctrlKey, shiftKey, button

> 예제 : DOM 요소를 드래그하여 이동시키기
> 
- 시작 : 마우스 버튼을 누른 상태(mousedown)에서 마우스 이동(mousemove)
    
    종료 : 마우스 버튼을 뗀 상태(mouseup)
    
- 드래그가 시작되면 mousedown 이벤트가 발생했을 시점의 마우스 포인터 좌표와 mousemove 이벤트가 발생할 때마다의 마우스 포인터 좌표를 비교하여 이동 거리를 계산한다. mouseup 이벤트가 발생하면 드래그 대상 요소를 이동시키는 이벤트 핸들러를 제거하여 이동을 멈춘다.
- MouseEvent 타입의 이벤트 객체에서 제공하는 clientX/Y를 사용한다. 이는 viewport(웹페이지의 가시 영역)를 기준으로 마우스 포인터의 좌표를 나타내준다.

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>마우스 드래그 프로그램</title>
    <style>
        .box {
            width: 200px;
            height: 100px;
            border: 1px solid black;
            background-color: cornflowerblue;
            cursor: pointer;
        }
    </style>
</head>
<body>
    <div class="box"></div>
    <script>
        // 드래그 대상 요소
        const $box = document.querySelector(`div.box`);
        // 현재(드래그 시작 지점)의 마우스 포인터 위치
        const initialMousePos = {
            x : 0,
            y : 0,
        };
        // 이동할 거리
        const offset = {
            x : 0,
            y : 0,
        }
        // mousemove 이벤트 핸들러(로 쓰일 함수)
        // box를 이동시킨다
        const move = e => {
            // offset = 현재 마우스포인터 위치 - 드래그 시작 지점의 마우스포인터 위치
            offset.x = e.clientX - initialMousePos.x;
            offset.y = e.clientY - initialMousePos.y;
            // transform 어트리뷰트의 translate를 사용하여 box 이동
            $box.style.transform = `translate3d(${offset.x}px, ${offset.y}px, 0)`;
        }

        // mousedown 이벤트 핸들러
        // box의 이동 거리를 표시한다
        $box.addEventListener(`mousedown`, e => {
            // 현재 마우스 좌표 = 드래그 시작 지점의 마우스 좌표 - 이동한 상태의 마우스 좌표
            initialMousePos.x = e.clientX - offset.x;
            initialMousePos.y = e.clientY - offset.y;
            // mousedown 이벤트 상태에서 mousemove 이벤트 발생 시 box 요소 이동
            document.addEventListener(`mousemove`, move);
        });

        // mouseup 이벤트 발생 시 mousemove 이벤트를 제거 -> 이동을 멈춘다
        document.addEventListener(`mouseup`, () => {
            document.removeEventListener(`mousemove`, move);
        });
    </script>
</body>
</html>
```

![Honeycam 2022-06-21 12-22-01](https://user-images.githubusercontent.com/97890886/174812001-0525c158-108f-452a-8b69-9ec1c4472499.gif)

### 키보드 정보 취득

`KeyboardEvent` 타입의 이벤트 객체는 keydown, keyup, keypress 이벤트가 발생하면 생성되며 ctrlKey, shiftKey, metaKey, key, keyCode 등의 고유 프로퍼티를 갖는다.

 

> 예제 : input 요소의 입력 필드에 엔터 키가 입력되면 현재까지 입력 필드에 입력된 값을 출력
> 
- key 프로퍼티 : 입력한 키 값을 문자열로 반환(예시 : 엔터 키의 경우 Enter 반환)
- keydown 이벤트 : 모든 키를 눌렀을 때 발생

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>키보드 이벤트</title>
    <style>
        * {
            text-align: center;
        }
    </style>
</head>
<body>
    <input type="text"  />
    <em class="message"></em>
    <script>
        const $input = document.querySelector(`input[type=text]`);
        const $msg = document.querySelector(`em.message`);

        const printValue = e => {
            // 입력한 키가 엔터키가 아니라면 무시(return은 함수 탈출의 용도로도 쓰임)
            if (e.key !== `Enter`) return;
            // 현재까지 입력 필드에 입력된 값을 출력
            $msg.textContent = e.target.value;
            e.target.value = ``;
        }
        $input.addEventListener(`keydown`, printValue);
    </script>
</body>
</html>
```


![Honeycam 2022-06-21 12-38-28](https://user-images.githubusercontent.com/97890886/174812059-4df95fde-b2c7-440c-b6ed-64cf1479a626.gif)

# 이벤트 전파

DOM 트리 상 요소 노드에서 발생한 이벤트 객체는 이벤트를 발생시킨 event target DOM 요소를 중심으로 DOM 트리 구조를 통해 `전파`되는데, 이를 `이벤트 전파(event propagation)`이라고 한다.

이벤트 전파는 객체가 전파되는 방향에 따라 3단계로 구분된다.

- capturing 캡처링 : 상위 요소 → 하위 요소
- target : 이벤트가 이벤트 타깃에 도달
- bubbling : 하위 요소 → 상위 요소

예를 들어, 다음과 같은 코드에서 li 요소를 클릭했다고 치자.

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>이벤트 전파</title>
    <style>
        * {
            text-align: center;
        }
    </style>
</head>
<body>
    <ul id="user">
        <li id="first">kang</li>
        <li id="second">Jung</li>
        <li id="third">Mark</li>
    </ul>
    <script>
        const $ul = document.querySelector(`ul#user`);
        const $liSec = document.querySelector(`li#second`);

        $ul.onclick = () => {alert(`ul에 등록한 이벤트`)};
        $liSec.onclick = () => {alert(`두 번째 li에 등록한 이벤트`)};
    </script>
</body>
</html>
```


![Honeycam 2022-06-21 13-06-16](https://user-images.githubusercontent.com/97890886/174812120-91727068-a392-4ba7-834a-b708ddda76e4.gif)


두 번째 li만 클릭했을 뿐인데 ul에 등록한 이벤트도 발생한다. 또한, 세 번째 li를 클릭할 경우 ul의 이벤트가 발생한다.

li 요소를 클릭 → 클릭 이벤트 발생하여 클릭 이벤트 객체 생성 → **클릭된 li요소가 event target이 됨**

1. 클릭 이벤트 객체가 window부터 시작하여 이벤트 타깃 방향으로 전파되는 것이 `캡처링`
2. 이벤트 객체가 이벤트를 발생시킨 이벤트 타깃에 도달하는 것이 `타깃`
3. 이벤트 객체가 이벤트 타깃에서 시작하여 window 방향으로 전파되는 것이 `버블링`

## 버블링

> 거의 모든 이벤트는 버블링(bubbling)된다.
> 

이벤트가 하위 요소에서 상위 요소 방향으로 전파되는 것.

즉, 이벤트는 이벤트 타깃(이벤트를 발생시킨 요소)에서뿐만 아니라 이벤트 패스(event path, 이벤트가 통과하는 트리 상 경로)에 위치한 상위 DOM 요소에서도 캐치할 수 있다.

‘거의 모든’ 이벤트라고 한 이유는, 다음 이벤트들의 이벤트 객체의 공통 프로퍼티 event.bubbles 값이 전부 false이기 때문이다.

- 포커스 이벤트 : focus/blur
- 리소스 이벤트 : load/unload/abort/error
- 마우스 이벤트 : mouseenter/museleave


![bubbling](https://user-images.githubusercontent.com/97890886/174812252-cbc20e36-e3be-4d26-a976-0d16784942be.png)


상속, 중첩, 재귀 등과는 또 다른 구조이다. 이벤트가 제일 깊은 곳에 있는 요소에서 시작해 부모 요소를 거슬러 올라가며 발생하는 모양이 마치 물속 거품(bubble)과 닮았기 때문에 붙여진 이름이며, 마치 파동과 같은 움직임을 보인다. 대부분의 이벤트 전파 관련 코드는 버블링이며, 캡처링은 거의 사용되지 않는다.

addEventListener 메서드로 등록한 이벤트 핸들러는 모든 단계의 이벤트를 선별적으로 캐치할 수 있(세 번째 인수로 true를 전달해야 함)으나 이벤트 핸들러 어트리뷰트/프로퍼티 방식으로 등록한 이벤트 핸들러는 버블링과 타깃 단계만 캐치 가능하다.

> 버블링 확인 예제
> 

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>버블링</title>
    <style>

        div {
            background-color: gold;
            position: relative;
            width: 200px;
            height: 200px;
            text-align: center;
            cursor: pointer;
        }
        p {
            background-color: olivedrab;
            position: absolute;
            top: 25px;
            left: 25px;
            width: 150px;
            height: 150px;
        }  
        button {
            background-color: coral;
            position: absolute;
            top: 25px;
            left: 25px;
            width: 100px;
            height: 100px;
            line-height: 50px;
            margin: 0;
        }
          body {
            line-height: 25px;
            font-size: 16px;
        }
    </style>
</head>
<body>
    <div>div
        <p>p
            <button>button</button>
        </p>
    </div>
    <script>
        document.querySelector(`div`).addEventListener(`click`, () => {alert(`Handler for div`)});
        document.querySelector(`p`).addEventListener(`click`, () => {alert(`Handler for p`)});
        document.querySelector(`button`).addEventListener(`click`, () => {alert(`Handler for button`)});
    </script>
</body>
</html>
```


![Honeycam 2022-06-21 13-32-50](https://user-images.githubusercontent.com/97890886/174812291-37caf737-105e-4c48-941f-1b38e43c6ed3.gif)



> 캡처링 & 버블링 확인 예제
> 

```jsx
<style>
  body * {
    margin: 10px;
    border: 1px solid blue;
  }
</style>

<form>FORM
  <div>DIV
    <p>P</p>
  </div>
</form>

<script>
  for(let elem of document.querySelectorAll('*')) {
    elem.addEventListener("click", e => alert(`캡쳐링: ${elem.tagName}`), true);
    elem.addEventListener("click", e => alert(`버블링: ${elem.tagName}`));
  }
</script>
```

이 예시는 문서 내 요소 '전체’에 핸들러를 할당해서 어떤 핸들러가 동작하는지를 보여줍니다.

`<p>`를 클릭하면 다음과 같은 순서로 이벤트가 전달됩니다.

1. `HTML` → `BODY` → `FORM` → `DIV` (캡처링 단계)
2. `P` (타깃 단계, 캡쳐링과 버블링 둘 다에 리스너를 설정했기 때문에 두 번 호출됩니다.)
3. `DIV` → `FORM` → `BODY` → `HTML` (버블링 단계)

<p>를 클릭하면 이벤트가 최상위 조상에서 시작해 아래로 전파되고(캡처링 단계), 이벤트가 타깃 요소에 도착해 실행된 후(타깃 단계), 다시 위로 전파됩니다(버블링 단계). 이런 과정을 통해 요소에 할당된 이벤트 핸들러가 호출됩니다.

출처 : [https://ko.javascript.info/bubbling-and-capturing#ref-348](https://ko.javascript.info/bubbling-and-capturing#ref-348)

### 주의사항

**핸들러를 제거할 때 `removeEventListener`가 같은 단계에 있어야 합니다.**

`addEventListener(..., true)`로 핸들러를 할당해 줬다면, 핸들러를 지울 때, `removeEventListener(..., true)`를 사용해 지워야 합니다. 같은 단계에 있어야 핸들러가 지워집니다.

### 왜 버블링을 우선하는가?

캡처링 단계는 거의 쓰이지 않고, 주로 버블링 단계의 이벤트만 다뤄집니다. 이렇게 된 데는 논리적 배경이 있습니다.

현실에서 사고가 발생하면 지역 경찰이 먼저 사고를 조사합니다. 그 지역에 대해 가장 잘 아는 기관은 지역 경찰이기 때문입니다. 추가 조사가 필요하다면 그 이후에 상위 기관이 사건을 넘겨받습니다.

이벤트 핸들러도 이와 같은 논리로 만들어졌습니다. 특정 요소에 할당된 핸들러는 그 요소에 대한 자세한 사항과 무슨 일을 해야 할지 가장 잘 알고 있습니다. `<td>`에 할당된 핸들러는 `<td>`에 대한 모든 것을 알고 있기 때문에 `<td>`를 다루는데 가장 적합합니다. 따라서 `<td>`를 다룰 기회를 이 요소에 할당된 핸들러에게 가장 먼저 주는 것입니다.

버블링과 캡처링은 '이벤트 위임(event delegation)'의 토대가 됩니다.

# 이벤트 위임

여러 개의 하의 DOM 요소에 각각 이벤트 핸들러를 등록하는 대신 하나의 상위 DOM 요소에 이벤트 핸들러를 등록하는 방법이다. 이벤트 전파(이벤트는 이벤트 타깃뿐만 아니라 상위 DOM 요소에서도 캐치할 수 있음, 캐처링&버블링)을 사용한 방법이다.

이렇게 이벤트 위임을 하면 여러 개의 하위 DOM 요소에 이벤트 핸들러를 일일이 등록할 필요가 없다.

> 이벤트 위임 사용 전
> 

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>이벤트 위임 사용 전</title>
</head>
<body>
    <nav>
        <ul id="lists">
            <li id="first" class="select">first</li>
            <li id="second">second</li>
            <li id="third">third</li>
        </ul>
    </nav>
    <div>선택된 내비게이션 아이템: <strong class="message"></strong></div>
    <script>
        const $lists = document.querySelector(`ul#lists`);
        const $msg = document.querySelector(`nav.msg`);

        function activate( {target} ) {
            [...$lists.children].forEach( $list => {
                // 상위 DOM(ul) 의 자식(li) 들을 순회
                // target(event target)과 일치하는 자식(즉, 클릭 이벤트가 발생한 노드)에
                // select 클래스를 추가하고 그 외 모든 내비게이션 아이템의 select 클래스를 제거
                $list.classList.toggle(`select`, $list === target);
                // 메세지로 표시
                $msg.textContent = target.id;
            })
        }

        // 모든 하위 요소에 이벤트 핸들러 등록
        document.getElementById(`first`).onclick = activate;
        document.getElementById(`second`).onclick = activate;
        document.getElementById(`third`).onclick = activate;
    </script>
</body>
</html>
```

내부적으로 성능이 낮을 뿐더러 유지보수에도 부적합하다.

> 이벤트 위임 사용 후
> 

```jsx
const $lists = document.querySelector(`ul#lists`);
        const $msg = document.querySelector(`nav.msg`);

        function activate( {target} ) {
            // 이벤트를 발생시킨 요소(target)가 ul#lists의 자식 요소가 아니라면 무시
            if (!target.matches(`ul#lists > li`)) return;

            [...$lists.children].forEach( $list => {
                // 상위 DOM(ul) 의 자식(li) 들을 순회
                // target(event target)과 일치하는 자식(즉, 클릭 이벤트가 발생한 노드)에
                // select 클래스를 추가하고 그 외 모든 내비게이션 아이템의 select 클래스를 제거
                $list.classList.toggle(`select`, $list === target);
                // 메세지로 표시
                $msg.textContent = target.id;
            })
        }

        // 상위 요소에 이벤트 핸들러 위임
        $lists.addEventListener(`click`, activate);
```

## 특징

- `Element.prototype.matches` 메서드를 사용하여 event target을 `검사`

위 이벤트 핸들러는 ul#lists에 바인딩되어, 자기 자신은 물론 이벤트를 발생시킨 모든 본인의 하위 DOM 요소에 반응한다(버블링). 역으로 말하면 event target이 개발자가 기대한 DOM요소가 아닌 엉뚱한 요소가 될 수도 있다는 것이므로 원하는 DOM 요소에 한정하여 이벤트 핸들러가 실행되도록 이벤트 타깃을 **검사**할 필요가 있다.

- `target` 프로퍼티와 `currentTarget` 프로퍼티가 달라진다
    - taget 프로퍼티는 이벤트를 **발생**시킨 DOM 요소
    - currentTarget 프로퍼티는 이벤트 핸들러가 실제로 **바인딩**된 DOM 요소

# DOM 요소의 기본 동작 조작

## 동작 중단하기

> 이벤트 객체의 `preventDefult` 메서드
> 

a 요소를 클릭하면 href 어트리뷰트의 링크로 이동하는 등의 각 DOM 요소가 가진 기본 동작을 중단시킨다.

## 이벤트 전파 방지

> 이벤트 객체의 `stopPropagation` 메서드
> 

이벤트 전파를 중단시킨다. 주로 하위 DOM요소의 이벤트를 개별적으로 처리하기 위해 사용한다.

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>Document</title>
</head>
<body>
    <ul id="container">
        <li class="b1">Button 1</li>
        <li class="b2">Button 2</li>
        <li class="b3">Button 3</li>
    </ul>
    <script>
        // 이벤트 위임
        // 클릭 이벤트가 발생한 하위 요소의 color를 빨강으로 변경
        document.getElementById(`container`).addEventListener(`click`, ({target}) => {
            if (!target.matches(`ul#container > li`)) return;
            target.style.color = `red`;
        } );

        // 이벤트 전파 중단
        // 상위 요소에서 이벤트를 캐치할 수 없다
        // 클릭 이벤트가 발생할 경우 다른 하위 요소들과 달리 color가 파란색으로 변경된다
        document.querySelector(`li.b3`).onclick = e => {
            e.stopPropagation();
            e.target.style.color = `blue`;
        }
    </script>
</body>
</html>
```

![Honeycam 2022-06-21 15-26-34](https://user-images.githubusercontent.com/97890886/174812347-3049d9aa-f09a-4d48-b55e-a884dd0b1613.gif)

# 이벤트 핸들러 내부의 this

## 이벤트 핸들러 어트리뷰트 방식의 경우

> 전역 객체(window)
> 

이벤트 핸들러 어트리뷰트의 값으로 지정한 문자열은 사실 **암묵적으로 생성되는 이벤트 핸들러의 문**이며, 어트리뷰트 값으로 지정한 문자열(함수)은 `일반 함수`로 호출되므로 함수 내부의 this는 전역 객체를 가리키게 된다.

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>Document</title>
</head>
<body>
    <button onclick="handleClick()">Click me!</button>
    <script>
        function handleClick() {
            console.log(this);    // window
        }
    </script>
</body>
</html>
```

단, 이벤트 핸들러를 호출할 때(어트리뷰트 값으로 문자열을 넘길 때) 인수로 함께 전달한 this는 `이벤트를 바인딩한 DOM요소`이다.

밑 예제에서의 handleClick 함수에 전달한 this는 암묵적으로 생성된 이벤트 핸들러 내부의 this이며, 이는 이벤트를 바인딩한 DOM요소를 가리킨다 → 이벤트 핸들러 프로퍼티 방식과 동일

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>Document</title>
</head>
<body>
    <button onclick="handleClick(this)">Click me!</button>
    <script>
        function handleClick(x) {
            console.log(x);    //    <button onclick="handleClick(this)">Click me!</button>
        }
    </script>
</body>
</html>
```
![eventThis](https://user-images.githubusercontent.com/97890886/179008629-9a4245a8-aea8-4b42-8e52-7d8cdb52bf30.png)


## 이벤트 핸들러 프로퍼티, addEventListner 메서드 방식의 경우

> 이벤트를 바인딩한 DOM 요소
> 

즉, 이벤트 객체의 `currentTarget 프로퍼티`와 같다.

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>이벤트 핸들러 내부의 this</title>
</head>
<body>
    <button class="btn1">0</button>
    <button class="btn2">10</button>
    <script>
        const $button1 = document.querySelector(`button.btn1`);
        const $button2 = document.querySelector(`button.btn2`);

        $button1.onclick = function(e) {
            console.log(this===e.currentTarget);    // T
            ++this.textContent;
        }

        $button2.addEventListener(`click`, function(e) {
            console.log(this);    // $button2
            console.log(e.currentTarget);   // $button2
            --this.textContent;
        })
    </script>
</body>
</html>
```

단, 화살표 함수로 정의한 이벤트 핸들러 내부의 this의 경우 `상위 스코프의 this`를 가리킨다. 화살표 함수는 함수 자체의 this 바인딩을 갖지 **않기** 때문이다. 위 예제의 이벤트 핸들러 함수를 화살표 함수로 할 경우 this는 상위 스코프의 this, 즉 전역 객체인 window를 가리키게 되고 ++this.textContext에는 NaN이 할당된다(undefined + 1)

### `클래스`에서 이벤트 핸들러를 바인딩하는 경우 this에 주의하라

클래스에서 프로토타입 메서드를 정의하여 이를 (이후에 생성될)인스턴스의 이벤트 핸들러로 등록해보자.

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>클래스에서 이벤트 핸들러를 바인딩할 때 this</title>
</head>
<body>
    <button class="btn">0</button>
    <script>
        class App {
            constructor() {
                this.$button = document.querySelector(`button.btn`);
                this.count = 0;

                // 프로토타입 메서드 increase를 이벤트 핸들러로 등록
                this.$button.onclick = this.increase;
            }

            increase() {
                this.$button.textContent += this.count;
                // TypeError : cannot set property `textContent` of undefined
            }
        }
    </script>
</body>
</html>
```

그러나 이는 실행해보면 예상대로 동작하지 않는다. 왜일까?

> increase 메서드 내부의 this가 클래스가 생성할 인스턴스를 가리키지 않기 때문이다.
> 

increase 메서드 내부의 this는 `이벤트를 바인딩한 DOM 요소`를 가리키므로, 클래스가 생성할 인스턴스가 아닌 this.$button을 가리키게 된다.

이를 해결하기 위해서는 increase 메서드 내부의 this가 클래스가 생성할 인스턴스를 가리키도록 해야 한다 → increase 메서드를 이벤트 핸들러로 바인딩할 때 bind 메서드로 this 전달

> 함수를 Function.prototype.bind 메서드로 간접 호출하기
> 

첫 번째 인수로 전달한 객체로 호출한 함수의 this 바인딩을 교체하여 함수를 새롭게 생성하여 반환한다.

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>클래스에서 이벤트 핸들러를 바인딩할 때 this</title>
</head>
<body>
    <button class="btn">0</button>
    <script>
        class App {
            constructor() {
                this.$button = document.querySelector(`button.btn`);
                this.count = 0;

                // increase 메서드 내부의 this가 이후에 생성될 인스턴스를 가리키도록 한다
                this.$button.onclick = this.increase.bind(this);
            }

            increase() {
                this.$button.textContent = ++this.count;
            }
        }
    </script>
</body>
</html>
```

또는 클래스 필드에 할당한 화살표 함수를 이벤트 핸들러로 등록하여 해결할 수도 있다. (화살표 함수는 자체적인 this를 갖지 않으며 상위 스코프의 this를 따르기 때문) 다만 이 경우 이벤트 핸들러 increase는 프로토타입 메서드가 아닌 **인스턴스 메서드**가 된다.

```jsx
// 클래스 필드 정의
// increase는 인스턴스 메서드이며, this는 인스턴스 자체를 가리킨다.
increase = () => this.$button.textContent = ++this.count;
```

# 이벤트 핸들러에 인수 전달

함수에 인수를 전달하려면 호출할 때 전달하는 것이 일반적이다. 이벤트 핸들러 어트리뷰트 방식은 동작 특성상 함수 호출문을 사용할 수 있으므로 인수를 전달할 수 있지만 나머지 방식들은 이벤트 핸들러를 **브라우저가** 호출하기 때문에 호출문을 사용할 수 없다(함수 자체를 등록해야 함) 그러나 방법이 아예 없는 것은 아닌데…

> 이벤트 핸들러 내부에서 함수 호출과 동시에 인수 전달하기
> 

```jsx
<!DOCTYPE html>
<html lang="ko">
<head>
    <title>이벤트 핸들러에 인수 전달하기</title>
</head>
<body>
    <label>User Name<input type="text"></label>
    <em class="message"></em>
    <script>
        const MIN_USER_NAME_LENGTH = 3;
        const $input = document.querySelector(`label > input[type=text]`);
        const $msg = document.querySelector(`em.message`);

        const checkUserNameLength = min => { 
            $msg.textContent = $input.value.length < 3 ? `닉네임은 ${min}자 이상이어야 합니다.` : ``
        };

        // 이벤트 핸들러 내부에서 함수를 호출하면서 인수를 전달
        $input.onblur = () => {
            checkUserNameLength(MIN_USER_NAME_LENGTH);
        }
    </script>
</body>
</html>
```

![Honeycam 2022-07-14 13-11-34](https://user-images.githubusercontent.com/97890886/179008718-cc3108a3-9760-496d-9d06-f2072718621f.gif)

> 이벤트 핸들러를 반환하는 함수를 호출하면서 인수 전달하기
> 

```jsx
<!DOCTYPE html>
<html lang="ko">
<head>
    <title>이벤트 핸들러에 인수 전달하기</title>
</head>
<body>
    <label>User Name<input type="text"></label>
    <em class="message"></em>
    <script>
        const MIN_USER_NAME_LENGTH = 3;    // 이름 최소 길이(상수)
        const $input = document.querySelector(`label > input[type=text]`);
        const $msg = document.querySelector(`em.message`);

        // 이벤트 핸들러를 반환하는 함수
        const checkUserNameLength = min => e => { 
            $msg.textContent = $input.value.length < 3 ? `닉네임은 ${min}자 이상이어야 합니다.` : ``
        };

        // 이벤트 핸들러를 반환하는 함수 호출문(인수 포함)을 등록
        $input.onblur = () => checkUserNameLength(MIN_USER_NAME_LENGTH);
    </script>
</body>
</html>
```

다음과 같이 동작한다.

```jsx
function checkUserNameLength(min) {
            return function handler(e) {
                // 생략
            }
        }
```

checkUserNameLength 함수는 함수를 반환하는 중첩 구조로 되어있으므로, 이를 이벤트 핸들러로 등록하면 checkUserNameLength의 반환값(우리가 원하는 진짜 이벤트 핸들러 함수)이 등록된다.

# 커스텀 이벤트

이벤트 객체는 이벤트가 발생하면 발생한 이벤트의 종류에 따라 이벤트 타입이 자동으로 결정되어 생성되기도 하지만, 다양한 이벤트를 생성자 함수를 사용하여 개발자가 직접 생성할 수 있다. Event, UIEvent, MouseEvent 등… 이처럼 개발자가 의도적으로 만든 이벤트를 `커스텀 이벤트`라고 한다.

## 커스텀 이벤트 생성

### 첫 번째 인수 : 이벤트 타입 전달

이벤트 생성자 함수를 사용하여 이벤트 객체를 생성할 때, 첫 번째 인수로 `이벤트 타입` 문자열을 전달받는데, 이 때 `CustomEvent 생성자 함수`를 사용하면 기존 이벤트 타입뿐만 아니라 **임의의 문자열**을 사용하여 **새로운 이벤트 타입**을 지정할 수도 있다.

```jsx
// keyboardEvent 생성자 함수로 keyup 이벤트 타입의 커스텀 이벤트 객체 생성
const keyboardEvent = new KeyboardEvent(`keyup`);
console.log(keyboardEvent.type);    // keyup

// CustomEvent 생성자 함수로 새로운 임의의 foo 타입의 커스텀 이벤트 객체 생성
const customEvent = new CustomEvent(`foo`); 
console.log(customEvent.type);    // foo
```

생성된 커스텀 이벤트 객체는

- 버블링되지 않는다
- preventDefault 메서드로 취소할 수 없다

```jsx
// bubble 프로퍼티 값 false
// cancelable 프로퍼티 값 false
console.log(keyboardEvent.bubbles);       // F
console.log(customEvent.cancelable);    // F
```

이를 true로 설정하려면 두 번째 인수로 이 프로퍼티들을 갖는 객체를 함께 전달하면 된다.

### 두 번째 인수 : `프로퍼티` 값 지정

커스텀 이벤트 객체에는 다양한 고유 프로퍼티 값(이벤트 타입에 따라 달라진다)을 지정할 수 있다. screenX/Y나 ctrlKey 등… 이처럼 이벤트 객체 고유의 프로퍼티 값을 지정할 때 생성자 함수의 두 번째 인수로 `프로퍼티`를 전달한다.

```jsx
const myEvent = new MouseEvent(`click`, {
    bubbles: true,
    cancelable: true
});

console.log(myEvent.bubbles);       // T
console.log(myEvent.cancelable);    // T
```

> `isTrusted 프로퍼티`의 값은 언제나 `false`
> 

이렇게 이벤트 생성자 함수로 생성한 커스텀 이벤트는 isTrusted 프로퍼티 값이 항상 F이다. 인위적인 이벤트 말고, 원래대로 사용자의 행위에 의해 발생한 이벤트의 경우 언제나 T이다.

## 커스텀 이벤트 디스패치(dispatch, 이벤트를 발생시키는 행위)

> `dispatchEvent 메서드`에 이벤트 객체를 인수로 전달하면서 호출 시, 인수로 전달한 이벤트 타입의 이벤트가 발생한다.
> 
- 기존 이벤트 타입의 커스텀 이벤트 객체의 경우

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>커스텀 이벤트 디스패치</title>
</head>
<body>
    <button class="btn">Click me!</button>
    <script>
        const $button = document.querySelector(`button.btn`);

        // 커스텀 이벤트
        const myEvent = new MouseEvent(`click`);
        
        // 커스텀 이벤트는 동기 처리 방식으로 동작
        // 디스패치 전 이벤트 핸들러 바인딩 필수
        $button.addEventListener(`click`, e => {
            alert(`${e} is Clicked!`);
            console.log(e);
        })

        // 커스텀 이벤트 대스패치
        // -> click 이벤트 발생
        $button.dispatchEvent(myEvent);
    </script>
</body>
</html>
```

- 임의의 이벤트 타입(CustomEvent)의 커스텀 이벤트 객체의 경우

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>커스텀 이벤트 디스패치</title>
</head>
<body>
    <button class="btn">Click me!</button>
    <script>
        const $button = document.querySelector(`button.btn`);

        // 이벤트 핸들러 등록
        // 디스패치 전 필수
        $button.addEventListener(`foo`, e => {
            alert(e.detail.message);
        })

        // foo 이벤트 타입의 커스텀 이벤트 객체 생성
        const myEvent = new CustomEvent(`foo`, {
            detail: {message: `Hello, World`}
        });

        // 커스텀 이벤트 디스패치
        $button.dispatchEvent(myEvent);
    </script>
</body>
</html>
```

두 번째 인수로 객체를 전달할 수 있는데, 여기에 e.`detail`(이벤트 객체의 프로퍼티, 이벤트와 함께 전달하고픈 정보가 담겨있음)을 담아 전달할 수 있다.

또한 **addEventListener 메서드 방식만 사용 가능하다.** 이벤트 핸들러 어트리뷰트/프로퍼티 방식과 같은 “전통적인 뼈대(프로토타입 상속)”가 필요한 방식은 사용하지 못한다.

> dispatchEvent 메서드는 동기(synchronous)처리 방식으로 동작한다
> 

일반적으로 이벤트 핸들러는 비동기(asynchronous)처리 방식으로 동작하지만, 이 메서드의 경우 핸들러를 동기(synchronous)처리 방식으로 호출한다. → 커스텀 이벤트에 바인딩된 이벤트 핸들러를 **직접** 호출하는 것과 동일하게 동작 → “순차적”처리이므로, **디스패치 전 이벤트 핸들러 등록은 필수다.**