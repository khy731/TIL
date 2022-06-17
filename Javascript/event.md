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

마우스 버튼을 누른 상태(mousedown) → 마우스 이동(mousemove) → 마우스 버튼을 뗀 상태(mouseup)