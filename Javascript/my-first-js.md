프로그래밍 언어를 새로 배울 때 가장 효과적인 start는 직접 만들어 보는 것입니다. 한 번 zero base로라도 어플리케이션을 만들어 봅시다.

# 1. javascript, CSS, HTML 파일 만들기

```jsx
console.log('Hello.js loaded');
```

```css
/* 스타일 */
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <link rel="stylesheet" href="Hello.css">
</head>
<body>
    <h1>my first applicaition</h1>
    <p>Welcome!</p>
    <script src="Hello.js"></script>
</body>
</html>
```

## 자바스크립트 콘솔

console.log(’Hello.js is loaded’); 코드의 의미는 무엇일까?

parameters로 설정한 값을 브라우저에 탑재되어 있는 개발자 도구의 디버거 콘솔에 표시하는 함수로, 기본적이고 간단한 자바스크립트 디버깅 방법이다. 지금까지 배웠던 컴파일 타입 언어와 상당히 상이한 것을 볼 수 있다.

## 컴파일 언어 vs 인터프리터 언어

### 컴파일 언어

> 고급 언어(프로그래머 작성) → 기계어 변환[컴파일] → 실행
> 

### 인터프리터 언어

> 고급 언어(프로그래머 작성) → 한줄한줄 해석 → 실행
> 

### 차이점

1. 실행 단계 : 컴파일 언어만 컴파일러 동작 단계를 필요로 한다.
2. 생산 속도 : 컴파일 과정이 없고 번역과 실행이 동시에 일어나므로 인터프리터 언어가 생산이 빠르다.
3. 실행 속도 : 컴파일 한 뒤 생성된 파일에 의해 실행되는 컴파일 언어가 더 실행이 빠르다.
4. 소스 코드 작성의 제약 : 컴파일 언어가 스크립트 언어보다 제약사항이 많다.
5. 디버깅 : 인터프리터 언어는 소스 코드 실행 전까지 버그를 인지하는 것이 상대적으로 느리다.

자바스크립트 언어는 대표적인 인터프리터 방식으로, 응용 소프트웨어와 상호작용하며 제어한다. 기존 프로그램(웹)을 전제로 사용된다.

# 2. 제이쿼리(****jQuery) 사용하기****

인기 있는 클라이언트 스크립트 라이브러리인 제이쿼리를 인터넷 url을 통해 사용해보자.

```html
<!-- 제이쿼리 라이브러리 링크-->
<script src="https://code.jquery.com/jquery-2.2.4.js" integrity="sha256-iT6Q9iMJYuQiMWNd9lDyBUStIq/8PuOW33aOqmvFpqI=" crossorigin="anonymous"></script>
```

이제 자바스크립트 파일을 수정하여 제이쿼리를 활용해보자.

```jsx
$(document).ready(function() {
    'user strict';
    console.log('Hello.js loaded');
)};
```

자바스크립트 코드 실행 전, 브라우저가 HTML을 성공적으로 로드했는지 체크하는 간단하지만 복잡한 코드이다. 2행은 자바스크립트 인터프리터에서 코드를 더 엄격하게 처리하라는 명령이다.

# 3. 단순 그래픽 그리기

그래픽 라이브러리 Paper.js를 사용해서 HTML 캔버스로 단순한 도형을 그려보자. HTML 파일의 body 태그에 canvas 태그를 추가하여 캔버스 요소를 먼저 준비한다.

```html
<canvas id="helloCanvas"></canvas>
```

캔버스 요소가 웹 페이지에서 잘 보이도록 너비와 높이, 테두리를 추가하여 css 파일을 수정한다.

```css
#helloCanvas {
    width: 400px;
    height: 400px;
    border: solid 1px black;
}
```

이제 캔버스 기능을 도와줄 Paper.js 라이브러리를 링크한다. jQuery를 링크한 코드 바로 다음에 추가하겠다.

```html
<!-- 그래픽 라이브러리 Paper.js 를 링크-->
<script src="https://cdnjs.cloudflare.com/ajax/libs/paper.js/0.12.2/paper-core.min.js"></script>
```

자바스크립트 파일에 템플릿(또는 boilerplate)을 추가한다. 템플릿은 임의의 작업 전, 항상 먼저 실행해야 하는 코드이다. 캔버스 중앙에 녹색 원을 그려보자.

```jsx
paper.install(window);    // Paper.js를 전역 스코프에 설치
paper.setup(document.getElementById('helloCanvas'));    // Paper.js를 캔버스에 연결(paper.js가 그림을 그릴 수 있도록 준비)

var c = Shape.Circle(200,200,50);   // 원 객체 생성 : x좌표,y좌표,반지름r
c.fillColor='green';    // 채울(fill) 색깔color 지정
```

# 4. 반복 작업 자동화하기

캔버스 전체에 원을 반복하여 그리면서 바둑판 모양으로 채워보자. 2중 for문을 사용하였다.

```jsx
/* 노란색 원을 반복하여 그리는 작업을 자동화 */
    var i;
    for (var x=25; x<400; x+=50) {
        for (var y=25; y<400; y+=50) {
            i = Shape.Circle(x,y,20);
            i.fillColor='yellow';
        }
    }
```

# 5. 사용자 입력 처리하기

사용자의 입력은 '비동기적 이벤트'이다 . 이벤트가 언제 어떻게 일어날지 프로그래머는 예상할 수 없다. Paper.js는 사용자의 입력을 tool(툴)객체를 사용하여 처리한다. 마우스 클릭에 반응하여 원이 나타나는 코드를 작성해 보자.

```jsx
var tool = new Tool();

tool.onMouseDown = function(event) {
    var u = Shape.Circle(event.point.x, event.point.y, 25);    // (event.point, 25) 로도 쓸 수 있음
    u.fillColor="blue";
}
```

> tool 객체 생성 -> 이벤트 핸들러 연결 가능 : 사용자가 마우스를 클릭할 때마다 이벤트 핸들러에 연결한 함수가 호출됨
> 

> 이벤트 핸들러 onMouseDown의 역할
> 
- 마우스를 클릭할 때 코드를 실행
- 클릭 위치를 보고 보고 (→ 매개변수의 event.point 프로퍼티에 저장됨)

# 6. Hello, World

브라이언 커닝햄이 만든 가장 기본적이고 거룩한 프로그래밍의 전통! Hello, World를 출력하며 첫 애플리케이션의 마지막을 장식해 보자. 배경으로 쓸 원을 하나 더 그리고, 텍스트 객체 PointText를 만든다. 최종적으로 다양한 속성을 지정한 텍스트를 출력하며 끝낸다.

```jsx
var z = Shape.Circle(300,300,80);    // 텍스트의 배경으로 쓸 원 객체 생성
    z.fillColor = 'orange';
    var text = new PointText(300,300);   // 텍스트 객체 생성
    text.justification = 'center';
    text.fillColor = 'white';
    text.fontSize = '20';
    text.content = 'Hello, World!';
```

# 최종 코드

> Hello.html
> 

```html
<!DOCTYPE html>
<html>
<head>
    <link rel="stylesheet" href="Hello.css">
</head>
<body>
    <h1>My first application</h1>
    <p>Welcome to <i>Learning <b>JavaScript</b>, 3rd Edition.</i></p>
    <!-- paper.js 사용 : <canvas>로 #helloCanvas 스타일 로드-->
    <canvas id="helloCanvas"></canvas>

    <!-- <script>태그는 head의 복잡도를 줄이고 js의 성능 향상을 위해 body의 마지막에 쓴다-->

    <!-- 제이쿼리 라이브러리를 CDN(콘텐츠 전송 네트워크), 즉 인터넷 url을 통해 링크-->
    <script src="https://code.jquery.com/jquery-2.2.4.js" integrity="sha256-iT6Q9iMJYuQiMWNd9lDyBUStIq/8PuOW33aOqmvFpqI=" crossorigin="anonymous"></script>
    <!-- 그래픽 라이브러리 Paper.js 를 링크-->
    <script src="https://cdnjs.cloudflare.com/ajax/libs/paper.js/0.12.2/paper-core.min.js"></script>
    <!-- 자바스크립트 파일 링크-->
    <script src="Hello.js"></script>
</body>
</html>
```

> Hello.css
> 

```css
#helloCanvas {
    width: 400px;
    height: 400px;
    border: solid 1px black;
}
```

> Hello.js
> 

```jsx
/* 제이쿼리 사용하여 자바스크립트 코드 작성하기 */
$(document).ready(function() {
    'user strict';    // 자바스크립트 인터프리터에서 코드를 더 엄격하게 처리하라고 명령 (인터프리터: 컴파일러와 달리 바로실행)
    
/* 템플릿 or 보일러플레이트boilerplate
: 어떤 일을 하기 전, 기본 설정 작업처럼 항상 먼저 실행해야 하는 코드 */
    paper.install(window);    // Paper.js를 전역 스코프에 설치
    paper.setup(document.getElementById('helloCanvas'));    // Paper.js를 캔버스에 연결(paper.js가 그림을 그릴 수 있도록 준비)

/* (캔버스에) 그림을 그리는 코드 : 중앙에 초록색 원 하나 그리기 */
    var c = Shape.Circle(200,200,50);   // 원 객체 생성 : x좌표,y좌표,반지름r
    c.fillColor='green';    // 채울fill 색깔color 지정

/* 노란색 원을 반복하여 그리는 작업을 자동화 */
    var i;
    for (var x=25; x<400; x+=50) {
        for (var y=25; y<400; y+=50) {
            i = Shape.Circle(x,y,20);
            i.fillColor='yellow';
        }
    }

/* 사용자 입력 처리 */
// Paper.js는 tool 객체로 사용자 입력을 처리한다.
    var tool = new Tool();    // tool 객체 생성 -> 이벤트 핸들러 연결 가능
    tool.onMouseDown = function(event) {
        var u = Shape.Circle(event.point.x, event.point.y, 25);
        u.fillColor="blue";
    }

/* Hello, World 출력하기 */
    var z = Shape.Circle(300,300,80);    // 텍스트의 배경으로 쓸 원 객체 생성
    z.fillColor = 'orange';
    var text = new PointText(300,300);   // 텍스트 객체 생성
    text.justification = 'center';
    text.fillColor = 'white';
    text.fontSize = '20';
    text.content = 'Hello, World!';

/*     실제로 화면에 그림을 그리라는(paper.js에서 가져온 함수를 수행하라는) 명령어 */
    paper.view.draw();

/* 자바스크립트 콘솔 */
    console.log('Hello.js loaded');
})
```

## 최종 결과물을 Live Server로 확인

![Honeycam 2022-03-28 19-02-35](https://user-images.githubusercontent.com/97890886/160375935-92183da6-bcdb-493a-9720-25bb39efb3de.gif)