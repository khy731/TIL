# 그리드 레이아웃

> 웹 사이트의 레이아웃을 정할 때 사이트 전체 디자인이나 일관성을 유지하려면 그리드 레이아웃을 사용해야 한다.

반응형 웹 사이트는 화면 너비에 따라 웹 문서의 요소를 재배치해야 하는데, 이 때 기준이 되는 레이아웃이 `그리드 레이아웃(grid layout)` 이다.

grid layout 은 웹 사이트를 여러개의 칼럼 column으로 나눈 후 메뉴,본문,이미지 등의 웹 요소를 화면에 맞게 배치한다.grid layout을 사용하면 화면을 규칙적으로 배열하여 레이아웃을 일관성 있게 유지할 수 있다.

## 그리드 레이아웃의 특징

1. `시각적으로 안정`된 디자인
2. `업데이트가 편한` 디자인 : 실제 내용을 넣지 않은 상태에서도 사이트 레이아웃을 미리 만들 수 있기 때문에, 사이트의 구조(예를 들어 영역의 너비, 각 요소의 위치 등의)를 먼저 만들어 놓고 나중에 내용을 채우고 수정하는 것이 쉽다.
3. `자유로운 요소 배치` : 단순한 block level box model을 사용하면 한 줄에 하나의 요소만 배치할 수 있지만 grid layout을 사용하면 보다 자유롭게 배치가 가능하다.

# 그리드 레이아웃 만들기


+ flexible box layout
+ CSS grid layout

# 플렉서블 박스 레이아웃

flexible box layout

> 수직(height)/수평(width) 中 한 쪽을 pivot으로 정하고 박스를 배치한다.

만약 pivot이 수평일 경우 박스를 왼→오 순서대로 배치하는데, width이 pivot수치를 초과할 경우 다음 줄(다음 height)로 넘어가서 다시 순서대로 배치하는 것을 반복한다.

![23_flexboxLayout](https://user-images.githubusercontent.com/97890886/166144913-7a46feca-4588-4f32-a379-ceba3f59b3a0.png)

## 배치 속성

플렉스 박스에는 플렉스 항목이 여러 개 있는데 이는 일괄적으로 한꺼번에 배치할 수도 있고 주축 or 교차축 기준으로 다양하게 배치할 수 있다.

- justify-content : 주축 방향의 정렬 방법
- align-items : 교차축 방향의 정렬 방법
- align-self : 교차축에 있는 개별 항목의 정렬 방법
- align-content : 교차축에서 여러 줄로 표시된 항목의 정렬 방법

## flex container 지정

> display 속성

플렉스 박스 레이아웃을 만들려면 일단 웹 콘텐츠를 전부 플렉스 컨테이너라는 가장 큰 부모 요소로 묶어줘야 한다. 이 때 이 부모 요소가 플렉스 컨테이너로써 기능하게 하기 위해 display 속성을 사용한다.

- flex : 컨테이너 안의 플렉스 항목을 블록 레벨 요소로 배치
- inline-flex : 컨테이너 안의 플렉스 항목을 인라인 레벨 요소로 배치

## flex content 방향 지정

>  flex-direction 속성

- row : 주축을 가로(수평)로 지정. 왼→오 로 배치. 기본값.
- row-reverse : row와 같지만 오→왼
- column : 주축을 세로(수직)로 지정. 위→아래로 배치.
- column-reverse : column와 같지만 아래→위

```css
.container {
    display: flex;
    width: 800px;
    border: 1px solid black;
    margin-bottom: 20px;
}
.box {
    width: 150px;
    padding: 5px 10px;
    margin: 10px;
    border: 1px solid black;
    background: gainsboro;
}
#opt1 {
    flex-direction: row;
}
#opt2 {
    flex-direction: row-reverse;
}
#opt3 {
    flex-direction: column;
}
#opt4 {
    flex-direction: column-reverse;
}
p {
    text-align: center;
    font-size: 13pt;
}
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link rel="stylesheet" href="flexbox_layout1.css">
</head>
<body>
        <section class="container" id="opt1">
            <div class="box"><p>1</p></div>
            <div class="box"><p>2</p></div>
            <div class="box"><p>3</p></div>
        </section>
        <section class="container" id="opt2">
            <div class="box"><p>1</p></div>
            <div class="box"><p>2</p></div>
            <div class="box"><p>3</p></div>
        </section>
        <section class="container" id="opt3">
            <div class="box"><p>1</p></div>
            <div class="box"><p>2</p></div>
            <div class="box"><p>3</p></div>
        </section>
        <section class="container" id="opt4">
            <div class="box"><p>1</p></div>
            <div class="box"><p>2</p></div>
            <div class="box"><p>3</p></div>
        </section>
</body>
</html>
```

![24_flex-direction](https://user-images.githubusercontent.com/97890886/166144940-b4274b12-3e43-4ba2-b9da-f2b3de68601f.png)

## flex content 줄 바꾸기

> flex-wrap 속성

- nowrap : 줄바꿈x 한 줄에 계속 쭉 표시. 기본값
- wrap : 줄바꿈o 여러 줄에 표시.
- wrap-reverse : 줄바꿈o 근데 시작점과 끝점을 바꾸어서 거꾸로 쌓아가듯이...

```css
#opt1 {
    flex-wrap: nowrap;
}
#opt2 {
    flex-wrap: wrap;
}
#opt3 {
    flex-wrap: wrap-reverse;
}
```

![25_flex-wrap](https://user-images.githubusercontent.com/97890886/166144973-495c408f-ebd7-4675-a3ba-cd3c60b71138.png)

## 두 속성을 동시에 컨트롤

> flex-flow 속성

기본값은 row nowrap

```css
#opt1 {
    flex-flow: row-reverse wrap;
}
#opt2 {
    flex-flow: column nowrap;
}
#opt3 {
    flex-flow: row-reverse wrap-reverse;
}
```

![26_flex-flow](https://user-images.githubusercontent.com/97890886/166144983-e0736ce8-98a3-404c-8016-a694229f40de.png)

## 주축 정렬 방법 지정

> justify-content 속성

main axis에서 flex content 간의 정렬 방법을 지정한다.

- flex-start : 주축의 시작점에 맞춰 배치
- flex-end : 주축의 끝점에 맞춰 배치
- center : 주축의 중앙에 맞춰 배치
- space-between : first content와 last content를 main axis의 start와 end에 각각 먼저 배치. 나머지 항목은 그 사이에 같은 간격으로 배치 (처음과 끝만 맞추고 나머지 그 안에서 중앙정렬)
- space-around : 모든 content를 main axis에 같은 간격으로 배치 (전체를 중앙정렬)

![27_justify-content](https://user-images.githubusercontent.com/97890886/166144997-cafad365-0850-436f-8a7d-eeee641ab7ca.png)

## 교차축 정렬 방법 지정

>  align-items 속성

교차축을 기준으로 플렉스 항목의 정렬을 결정한다.

- flex-start : 교차축의 시작점에 맞춰 배치
- flex-end : 교차축의 끝점에 맞춰 배치
- center : 교차축의 중앙에 배치
- baseline : 교차축의 문자 기준선에 맞춰 배치(font size 등에 따라 변함)
- stretch : 플렉스 항목을 쭉~ 늘려서 교차축에 가득 차게 배치

![28_align-items](https://user-images.githubusercontent.com/97890886/166145008-040eb2ef-1049-46c8-9161-8b53fafb96e4.png)

## 특정 항목만 정렬 방법 지정 

> align-self 속성

align-items는 말 그대로 모든 flex content 플렉스 항목을 대상으로 하므로 container에 포함되는 것이 일반적이지만, align-self는 특정 항목만 정렬 방법을 따로 지정하는 것이므로 속성값은 똑같지만 각각의 content box에 사용한다.

## 여러 줄일 때 교차축 정렬 방법 지정

>  align-content 속성

여러 줄일 때 == 주축에서 줄바꿈이 있을 때 flex content 간의 간격을 지정한다.

- flex-start : 교차축의 시작점에 맞춰 배치
- flex-end : 교차축의 끝점에 맞춰 배치
- center : 교차축의 중앙에 맞춰 배치
- space-between : 시작과 끝만 고정하고 나머지는 그 사이에 중앙배치
- space-around : 모두 중앙배치
- stretch : 항목 자체를 좍좍 늘려서 교차축에 가득 차게 배치

## flex layout 활용 : 중앙배치

지금까지는 CSS의 부가적인 속성들로 중앙배치를 해야했기 때문에 좀 까다롭고 불편했으나 이제는 항상 `정중앙 배치`를 해줄 수 있다.

```css
* {
    margin: 0;
    box-sizing: border-box;
}
.container {
    width: 100%;
    background: url(night.jpg) no-repeat left top;
    background-size: cover;
    display: flex;
    justify-content: center;
    align-items: center;
    min-height: 100vh;
}
#button {
    width: 150px;
    background: gray;
    border-radius: 20px;
    color: white;
    text-align: center;
}
```

```html
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>alwysCenter</title>
    <link rel="stylesheet" href="center.css">
</head>
<body>
    <div class="container">
        <div id="button"><p>Click!</p></div>
    </div>
</body>
</html>
```

# CSS 그리드 레이아웃

CSS grid layout

> 줄(row)과 칼럼(column)으로 웹 화면을 구성하며, 줄과 줄 사이/칼럼과 칼럼 사이의 간격을 조절하여 원하는 형태의 레이아웃을 만든다. 

소스를 최대한 간단하게 유지하면서 대부분의 기기에 대응할 수 있는 그리드 레이아웃 기법이다. 수평수직을 주축으로 했던 flexible box layout과는 달리, 마치 레고 블럭을 끼워 맞추듯이 여기저기 요소를 배치할 수 있다. 어느 한 쪽을 주축으로 삼지 않고 둘 다 사용한다. 그래서 플렉스 항목은 1차원이고 CSS 그리드 레이아웃은 2차원이라고 하기도 한다.

또한 그리드 레이아웃 제작 방법 中 가장 최신 기법이다.

![23_cssGridLayout](https://user-images.githubusercontent.com/97890886/166145070-fa6e1713-5dd5-4bbb-bbad-e95cb994408e.png)

## grid container 지정

> display 속성

- grid : 컨테이너 안의 항목을 block level 요소로 배치
- inline-grid : 컨테이너 안의 항목을 in-line level 요소로 배치

## row, column 지정

> grid-templete-columns 속성   
> grid-templete-rows 속성

컨테이너 안에 항목을 배치할 때, 칼럼과 줄의 크기(너비와 높이)와 개수를 지정한다.

```css
#wrapper {
    display: grid;
    width: 600px;
    grid-template-columns: 200px 200px 200px;
    grid-template-rows: 100px 100px;
}
.items {
    padding: 10px;
    border: 1px dotted black;
    background: white;
}
.items:nth-child(odd) {
    background: gray;
}
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>CSS grid layout</title>
    <link rel="stylesheet" href="gridlayout.css">
</head>
<body>
    <main id="wrapper">
        <div class="items"></div>
        <div class="items"></div>
        <div class="items"></div>
        <div class="items"></div>
        <div class="items"></div>
        <div class="items"></div>
    </main>
</body>
</html>
```

![29_CSS_grid_layout](https://user-images.githubusercontent.com/97890886/166145115-d9875f20-c43b-4dc7-905c-6758e985a5bb.png)

첫번째 row만 100px로 지정을 해 줬더니 두번째 row는 거의 안나오듯이 잘려 나왔다. 높이 지정을 해 줘야 하는 것이다. 그런데 만약 contents의 길이에 따라 높이를 상대적으로 정하고 싶다면?

## 상대적인 크기의 단위

> fr

당연하겠지만, 그리드 레이아웃을 만들 때 column이나 row의 크기를 지정할 때 px를 사용하면 항상 크기가 고정(절대적)되므로 반응형 웹 디자인에는 적합하지 않다. 그래서 fr(fraction)을 사용하여 비율대로 쪼개본다.

```css
grid-templete-columns: 1fr 1fr 1fr;
/* 너비가 같은 3개의 칼럼 배치 */
```

## 반복

>  repeat() 함수

px이나 fr단위를 사용하면 위 코드와 같이 column과 row의 개수만큼 똑같은 값을 여러 번 반복해야 한다. repeat()함수를 사용하면 간단하게 작성할 수 있다.

```css
grid-templete-columns: repeat(3, 1fr);
```

## 최댓값, 최솟값 지정

> minmax() 함수

위에서 줄 높이를 100px로 정했는데, 만약 내용이 너무 많아서 100px를 넘어가도록 줄바꿈이 된다면? 내용이 잘린다. 이를 보다 유연하게 하기 위해 minmax()함수를 사용해 보자.

```css
grid-templete-rows: minmax(100px, auto);
/* 줄 높이를 최소 100px, 최대 무한(정해지지 않음)으로 지정 */
```

## 자동으로 칼럼 개수 조절

> auto-fill, auto-fit 값

위에서 repeat 함수를 사용하면 column 배치를 보다 쉽게 표시할 수 있었다. 그런데 특정 화면에 column을 꽉 채우고 싶다면? 화면의 너비를 일일이 계산해야 하는 어려움이 생긴다.
auto-fill 값과 auto-fit 값은 자동으로 column의 개수를 조절해준다. repeat 함수의 첫 번째 파라미터-반복 횟수-에 이 값들을 넣어주면 된다. 그러면 화면의 너비에 따라 자동으로 칼럼 개수가 조절된다.

```css
grid-templete-columns: repeat(auto-fit, 200px)
```

- auto-fit : 화면에 꽉 찰 만큼, 남는 공간 없이 꽉 채워서(그만큼 크기를 늘려서) 지정
- auto-fill : 칼럼의 최소 너비만 표시하고 남는 공간은 그냥 둠

```css
#wrapper1 {
    width: 100%;
    display: grid;
    /* auto-fit: 화면을 꽉 채울만큼 칼럼 너비를 늘려서 표시 */
    grid-template-columns: repeat(auto-fit, minmax(150px, 1fr));
    margin-bottom: 30px;
}
#wrapper2 {
    width: 100%;
    display: grid;
    /* auto-fill: 칼럼 최소 너비만큼 채워서 표시 */
    grid-template-columns: repeat(auto-fill, minmax(150px, 1fr));
    margin-bottom: 30px;
}
.items {
    padding: 10px;
    border: 1px dotted black;
    background: white;
}
.items:nth-child(odd) {
    background: gray;
}
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>CSS grid layout</title>
    <link rel="stylesheet" href="gridlayout.css">
</head>
<body>
    <h1>auto-fit일 때</h1>
    <div id="wrapper1">
        <div class="items">aaaaaaa aaaa aaaaa aaaaa aaaaa aaaa aaaaa aaaaaaa aa aaaaa</div>
        <div class="items">bbb bbb bbb bbbb bbb bbbb bbbbb</div>
        <div class="items">cc ccccccc ccc</div>
        <div class="items">ddddd dddd d dddd dddddddddddd ddddd ddddd</div>
        <div class="items">ee eeeeeee eee eeeee eee</div>
        <div class="items">fffff fff fff fff ffff ffff ffffff ffffff ffffffffff</div>
    </div>
    <h1>auto-fill일 때</h1>
    <div id="wrapper2">
        <div class="items">aaaaaaa aaaa aaaaa aaaaa aaaaa aaaa aaaaa aaaaaaa aa aaaaa</div>
        <div class="items">bbb bbb bbb bbbb bbb bbbb bbbbb</div>
        <div class="items">cc ccccccc ccc</div>
        <div class="items">ddddd dddd d dddd dddddddddddd ddddd ddddd</div>
        <div class="items">ee eeeeeee eee eeeee eee</div>
        <div class="items">fffff fff fff fff ffff ffff ffffff ffffff ffffffffff</div>
    </div>
</body>
</html>
```


![29_CSS_grid_layout2](https://user-images.githubusercontent.com/97890886/166145180-f8fa7321-1b9a-4538-8eae-08233fea20ce.png)

## 그리드 항목의 간격 지정

> grid-gap 속성

- grid-column-gap : 칼럼과 칼럼 사이 간격 지정
- grid-row-gap : 줄과 줄 사이 간격 지정
- grid-gap : 둘을 한꺼번에 지정. 첫 번째 값은 row이고 두 번째 값은 column이다.

이 외에도 flex-box-layout에서 사용했던 justify-content(주축 정렬), align-content(교차축 정렬)로도 그리드 레이아웃의 항목을 정렬할 수 있다.

# contents 배치

## grid line을 이용

- grid-column-start : 칼럼 시작의 라인 번호 지정
- grid-column-end : 칼럼 마지막의 라인 번호 지정
- grid-column : 칼럼 시작~끝 동시 지정. 1/4 형태로 사용(나누기 아님니다...)
- grid-row-start
- grid-row-end
- grid-row

```css
#wrapper {
    width: 700px;
    display: grid;
    grid-template-columns: repeat(3, 1fr);
    grid-template-rows: repeat(4, 100px);
}
.box {
    border: 1px solid black;
}
.box1 {
    background: cornflowerblue;
    grid-column: 1/4;
    grid-row: 1/2;
}
.box2 {
    background: olivedrab;
    grid-row: 2/4;
    grid-column: 1/2;
}
.box3 {
    background: coral;
    grid-column: 2/4;
    grid-row: 2/3;
}
.box4 {
    background-color: gold;
    grid-column: 3/4;
    grid-row: 3/4;
}
```

항목을 배치할 때 column이나 row를 한 칸만 차지할 경우 start 속성으로 하나만 쓰게 함으로써  단순하게 응용할 수 있다.


![30_gridline](https://user-images.githubusercontent.com/97890886/166145201-be1ad33e-49ae-4355-b0af-1cb994b2cc0a.png)

## templete area를 이용

그런데 하나하나 줄 번호 매기는게 여간 귀찮은게 아닌 듯하다. 이렇게 grid line으로 레이아웃을 만드는 것보다, 템플릿templete 영역을 사용하여 레이아웃을 만들어 보자. 마치 표에서 칸을 선택하듯이, 하나하나 분해해서 <줄 시점>에서 만드는 것이다.


![30_gridline2](https://user-images.githubusercontent.com/97890886/166145227-ce3428d8-55b4-451c-ab14-9771e73d2bbf.png)


이런 식으로 쪼갤 것이다.

<aside>
❕ “box1 box1 box1”

“box2 box3 box3”

“box2 . box4” ;

</aside>

빈 칸은 . (마침표)로 표시한다

```css
#wrapper {
    width: 700px;
    display: grid;
    grid-template-columns: repeat(3, 1fr);
    grid-template-rows: repeat(4, 100px);
    grid-template-areas:
    "box1 box1 box1"
    "box2 box3 box3"
    "box2 . box4";
}
.box1 {
    grid-area: box1;
    background-color: cornflowerblue;
}
.box2 {
    grid-area: box2;
    background-color: greenyellow;
}
.box3 {
    grid-area: box3;
    background-color: coral;
}
.box4 {
    grid-area: box4;
    background-color: gold;
}
```

```html
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>그리드 템플릿 영역으로 배치</title>
    <link rel="stylesheet" href="grid-templete-areas.css">
</head>
<body>
    <main id="wrapper">
        <div class="box1"></div>
        <div class="box2"></div>
        <div class="box3"></div>
        <div class="box4"></div>
    </main>
</body>
</html>
```

![31_templete-areas](https://user-images.githubusercontent.com/97890886/166145248-ca505711-d78f-48f0-bda4-4551b7a29895.png)