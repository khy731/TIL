웹 문서에서 내용을 배치할 때는 각 요소를 박스 형태로 구성합니다. 이것을 CSS 박스 모델이라고 하며, 각 박스 모델은 실제 내용이 들어가는 content영역, 테두리, 그리고 여백으로 구성됩니다. 이는 CSS를 사용한 레이아웃의 기본입니다.

# CSS와 box model(박스 모델)

웹 문서의 내용을 박스 형태로 정의합니다. 박스 모델에는 마진(margin), 패딩(padding), 테두리 등 박스가 여러 겹 들어있습니다. 박스 모델은 블록 레벨(block-level) 요소인지, 인라인 레벨(in-line-level) 요소인지에 따라 나열 방법이 달라집니다.

### block-level 요소

태그를 사용하여 요소를 삽입했을 때, 한 줄을 차지하는 것 (==해당 요소의 너비는 100%). 즉 이 요소의 왼쪽이나 오른쪽에 다른 요소를 추가할 수 없다. ex) <h1>, <p>, <div>. 각 요소에 테두리를 그려서 레벨 요소를 구별해보면 전부 너비가 100%인 테두리가 그려지며 한 줄 전체를 차지하는 것을 볼 수 있다.

### in-line-level 요소

한 줄을 차지하지 않으며, 딱 컨텐츠(content)만큼만 영역을 차지하고 나머지 공간에는 다른 요소가 올 수 있다 → 한 줄에 인라인 레벨 요소를 여러 개 표시할 수 있다. ex) <span>, <img>, <strong>.

## box model의 기본 구성

앞에서 살펴봤듯이, 웹 문서의 block level 요소는 전부 박스 형태이다. style sheet에서 이렇게 박스 형태인 요소를 box model 요소라고 한다. box 모델은 여러 요소로 나뉘어지는데

- content(컨텐츠) 영역
- padding(패딩) 영역
- margin(마진) 영역

![생각보다 빨리 쓰이게 되는 이 그림](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/d9aa8485-6915-4a7c-af18-c96f82832ee4/img_css_boxmodel_padding.png)

생각보다 빨리 쓰이게 되는 이 그림

margin이나 padding은 웹 문서에서 서로 다른 컨텐츠 사이의 간격, 배치 등을 지정한다. 모든 요소는 각각 상하좌우로 나뉘어 있어 방향을 따로 설정할 수 있다.

![요소 우클릭→’검사’클릭→개발자 도구에서 ‘Conputed’클릭→요소의 box model 확인 가능. margin영역에 마우스를 댔더니 웹 브라우저 창에서 margin 영역이 어디인지 보여 줬음.(따로 지정하지는 않았고, 웹 브라우저의 기본 값)](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/a243bdc0-33a8-4e50-b8b4-d09ab9db5728/12_boxmodel.png)

요소 우클릭→’검사’클릭→개발자 도구에서 ‘Conputed’클릭→요소의 box model 확인 가능. margin영역에 마우스를 댔더니 웹 브라우저 창에서 margin 영역이 어디인지 보여 줬음.(따로 지정하지는 않았고, 웹 브라우저의 기본 값)

## content 영역의 크기 지정 : width,height 속성

각 속성에서 사용할 수 있는 값

- 크기 : 너비, 높이의 값을 px나 em 단위로 지정
- 백분율: box model을 포함하는 부모 요소를 기준으로 백분율%로 지정
- auto: content 양에 따라서 자동으로 결정됨. 기본값

크기는 말 그대로 값을 딱. 단위로 딱. 정해주는 것이기 때문에 웹 브라우저 창의 크기에 영향받지 않지만, 백분율로 은 말 그대로 상대적인 가변값이므로 창에 따라서 크기가 달라진다.

## box model의 크기 계산 : box-sizing 속성

width 속성과 height 속성은 box model에서 테두리, 여백 등을 모조리 뺀 알맹이 content 영역을 가리키기 때문에 실제 box model의 크기와는 살짝 차이가 있다. 그렇다고 매번 테두리, 여백값을 계산하는 것은 귀찮으니, box-sizing 속성을 사용하여 테두리까지 포함하여 너빗값을 지정할 것인지 content영역만 너빗값을 지정할 것인지를 선택한다.

- border-box : 테두리까지 포함하여 너빗값 지정
- content-box : content영역만 너빗값 지정. 기본값

웹 문서 레이아웃을 만들 때에는 CSS에서 box model을 사용하는데, 요소의 크기를 쉽게 계산하기 위해서는 box-sizing을 border-box로 지정해 놓는 것이 편하다.(물론, content의 너비를 정확하게 계산해야 한다면 이렇게 하지 않아도 된다. 무엇이 더 중요한 상황이느냐에 대한 차이다.)

## box model에 그림자 효과 주기 : box-shadow

```css
box-shadow: <수평 거리> <수직 거리> <흐림 정도> <번짐 정도> <색상> inset
```

- 수평 거리: 필수 속성. 그림자가 가로로 얼마나 떨어져 있는지를 나타냄.

양숫값 - 오른쪽에 그림자, 음숫값 - 왼쪽에 그림자

- 수직 거리 : 필수 속성. 그림자가 세로로 얼마나 떨어져 있는지를 나타냄.

양숫값 - 아래쪽에 그림자, 음숫값 - 위쪽에 그림자

- 흐림 정도 : 기본값은 0(가장 진함). 값이 커질수록 부드러운 그림자이다. 음숫값 사용 불가능

- 번짐 정도 : 양숫값 - 모든 방향으로 그림자가 퍼져서 크게 표시됨. 음숫값은 축소되어 보임. 기본값은 0

- inset : 안쪽 그림자로 그린다.

```css
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>BoxModel Sizing&Shadow</title>
    <style>
        .box1 {
            width: 100%;
            background: bisque;
            box-sizing: border-box;
            box-shadow: 3px 3px coral;
        }
        .box2 {
            width: 100%;
            box-sizing: border-box;
            box-shadow: 5px 5px 15px 5px blue inset;
        }
    </style>
</head>
<body>
    <div class="box1">
        <h1>든든한 점심을 먹었습니다</h1>
        <p>그래서 졸립니다...</p>
    </div>
    <div class="box2">
        <h2>커피를 마셔야겠습니다</h2>
    </div>
    
</body>
</html>
```

![간단한 예제 작성.](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/adf82795-4242-4dbd-a7aa-8c7aae72203c/12_boxmodel2.png)

간단한 예제 작성.

# 테두리(border) 스타일 지정

## 박스 모델의 방향

앞에서 말했듯이, 박스 모델은 상하좌우 4개의 방향이 있어서 테두리(border), 마진(margin), 패딩(padding)을 지정할 때 한꺼번에 똑같이 지정할 수도 있고 각각 다르게 지정할 수도 있다. 이 때 4개 방향의 예약어는 맨 위부터 시계방향 순서대로 top → right → bottom → left 이다.

![css-box_model.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/e22a3c7d-e57a-45cc-a185-87b53f7aba31/css-box_model.png)

만약 테두리 스타일을 방향별로 따로 설정하고 싶다면, 속성에 하이픈(-)으로 연결하여 지정하면 된다. ex) border-right-style, border-bottom-width. 그런데 이 작업은 너무 귀찮으니 굳이 속성을 하이픈으로 수정을 하지 않아도 속성값을 쭉 나열하면 top→right→bottom→left 순으로 적용된다.

### 방향 순서에 따른 스타일 적용

```css
/* 속성값 1개 : 4방향 전부 같은 값 적용 */
#box1 {
    border-width: thick thin;
}

/* 속성값 2개 : 위아래 & 좌우에 각각 적용 */
#box2 {
    border-style: solid double;
}

/* 속성값 3개 : 순서대로 적용 -> 생략된 값은 마주보는 값 적용 */
#box3 {
    border-width: 10px 5px 10px;
}

/* 속성값 4개 : 순서대로 적용 */
#box4 {
    border-width: mideum thin thick thin;
}
```

## 테두리 스타일 지정 : border-style 속성

기본값이 none이기 때문에(테두리가 없는 것이 베이직이기 때문에)  이 속성값을 따로 지정해야만 테두리 색상, 두께 등을 지정할 수 있다. 

- none : 테두리 없음. 기본값
- hidden : 테두리 감춤. border-collapse 속성이 collapse일 경우 다른 테두리도 같이 감춤.
- solid : 실선 테두리
- dotted : 점선 테두리
- dashed : 짧은 직선 테두리
- double : 이중선 테두리(두 선 사이의 간격은 border-width값으로 조정)
- groove : 창문 모양, 홈이 파인듯한 입체 느낌의 테두리
- ridge : 창문 모양, 튀어나온 듯한 입체 느낌의 테두리
- inset : 표에서 border-collapse 속성에 따라 달라짐

    - saperate일 경우 : 전체 박스 테두리가 창에 박혀 있는 듯한 테두리

    - collapse일 경우 : groove와 같음

- outset : 표에서 border-collapse 속성에 따라 달라짐

    - saperate일 경우 : 전체 박스 테두리가 창에서 튀어나온 듯한 테두리

    - collapse일 경우 : ridge와 같음

## 테두리 두께 지정 : border-width 속성

```css
border-width: <크기> | thin | mideum | thick
```

- 크기 : 1px, 5px 처럼 단위를 직접 입력
- 예약어 : thin, mideum, thick 中 1 택

## 테두리 색상 지정 : border-color 속성

## 테두리 스타일 묶어서 한 번에 지정하기 : border 속성

border-style, border-width, border-color 속성을 묶어서 한 번에 지정할 수 있다. 4개 방향의 스타일을 다르게 지정하고 싶다면 속성 이름에 방향을 함께 쓰면 된다. 속성값의 순서는 상관없다.

```html
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <title>BoxModel</title>
    <style>
        h1 {
            padding-bottom: 5px;
            border-bottom: 3px solid black;
        }
        p {
            padding: 10px;
            border: 3px dotted violet;
        }
    </style>
</head>
<body>
    <h1>박스 모델</h1>
    <p>박스 모델이고 뭐고 졸려 죽겠습니다.</p>
</body>
</html>
```

![12_boxmodel3.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/ef67af62-c335-45a0-91c4-871969dd2d1a/12_boxmodel3.png)

## 둥근 테두리 만들기 : border-radius 속성

box model에서 border을 표시하면 기본적으로 사각형 모양이고, 네 꼭짓점은 직각이다. 이 때 border-radius 속성으로 꼭짓점 부분에 마치 원이 있는 것 처럼 둥글게 처리된다. 이때 둥근 정도는 가상의 원의 반지름(radius)으로 표시한다.

![css_border_radius_01.jpg](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/6fefe947-3a2d-45a4-b7fe-e4e9b08e8547/css_border_radius_01.jpg)

![css_border_radius_02.jpg](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/7255a58f-e6cc-46ff-8fda-1bae4fcb2c5c/css_border_radius_02.jpg)

```css
border-radius: <크기> | <백분율>
```

- 크기 : 반지름 크기를 px, em 등의 단위로 수치로 표시합니다.
- 백분율: 현재 요소 크기를 기준으로 비율%로 지정합니다. 만약 이미지를 아예 원 형태로 만들고 싶다면, 이미지 요소의 너비==높이 처리 후 비율을 50%로 지정해주면 됩니다. 크기로 작성 시 너비, 높이의 절반 값으로 하면 되겠죠.

### 네 꼭짓점 각각 따로 둥글게 만들기

속성명에 방향을 같이 적어 처리한다.

![css-border-radius.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/1521801f-909a-4f3f-8878-d50c88c3fb44/css-border-radius.png)

### 타원모양 테두리 만들기

간단하다. 세로 반지름과 가로 반지름을 구분하면 된다. 슬래시(/)로 구분한다.

```css
border-radius: <가로 반지름> / <세로 반지름>;
border-top-left-radius: <가로 반지름> <세로 반지름>;
```

## 나만의 예제

```css
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <title>나만의 예제</title>
    <style>
        h1 {
            width: 100%;
            height: 70px;
            line-height: 70px;
            background-color: lightblue;
            color: midnightblue;
            font-style: italic;
            text-align: center;
        }
        div {
            border: 1px solid black;
            border-collapse: collapse;
        }
        #container {
            border: none;
            width: 600px;
        }
        table{
            border: 1px solid black;
            caption-side: bottom;
            border-spacing: 10px;
            border-collapse: collapse;
        }
        td, th {
            border: 1px dotted black;
            padding: 10px;
        }
    </style>
</head>
<body>
    <div id="container">
        <div>
            <h1>아침</h1>
            <p>두유 한 팩을 먹으면서 하루를 시작했습니다.</p>
            <p>늦게 일어난 바람에 조금 급하게 준비했지만 제 시간에 나가는 데 성공했습니다.</p>
            <p>운동을 조지고 돌아와서 씻었습니다</p>
        </div>
        <div>
            <h1>점심</h1>
            <p><b>학식 메뉴: </b>탕수육, 짜장 떡볶이, 볶음밥, 샐러드, 유부국, 김치</p>
            <ul>
                <legend>먹고 싶었던 메뉴</legend>
                <li>갈비짬뽕</li>
                <li>회와 초밥</li>
                <li>생맥주 한 잔</li>
            </ul>
        </div>
        <div>
            <h1>저녁</h1>
            <table>
                <caption>예상되는 저녁 루틴</caption>
                <colgroup">
                    <col style="background-color: antiquewhite;">
                    <col>
                    <col>
                </colgroup>
                <tr>
                    <th>시간</th>
                    <th>할 일</th>
                    <th>감정</th>
                </tr>
                <tr>
                    <td>6시</td>
                    <td>밥 먹기</td>
                    <td rowspan="2">행복</td>
                </tr>
                <tr>
                    <td>8시</td>
                    <td>귀가 하기</td>

                </tr>
            </table>
        </div>
    </div>
</body>
</html>
```

![12_borderEx.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/aa910a94-a172-4da0-8bbb-922a31cfe09c/12_borderEx.png)

아씨 지금까지 배운거 욕심섞어서 하려니까 존나 한계옴.

그리고 타입선택자, 인라인선택자, 클래스선택자 왔다갔다하니까 존나 헷갈림

CSS 파일 분리하는 이유를 예제를 하면서 깨닫다...ㅋㅋㅋ

# 여백(margin, padding) 조절

margin : 박스 모델 사이의 여백(가장 바깥쪽)

padding : 컨텐츠와 테두리 사이의 여백

# 요소 주변의 여백 : margin 속성

```css
margin: <크기> | <백분율> | auto
```

- 크기 : 너빗값, 높잇값을 px, em 수치로 지정
- 백분율 : box model을 포함한 부모 요소를 기준으로 퍼센트%로 지정
- auto : display 속성에서 지정한 값에 맞게 적절한 값을 자동으로 지정

```css
        /* 네 방향 전부 50px의 여백 */
        #margin1 {
            margin: 50px;                   
        }
        /* 위아래는 30px, 좌우는 50px의 여백 */
        #margin2 {
            margin: 30px 50px;
        }
        /* 순서대로 적용 -> 생략한 left는 마주보는 속성값으로 */
        #margin3 {
            margin: 30px 50px 30px;
        }
        /* 순서대로 적용 */
        #margin4 {
            margin: 30px 50px 30px 50px;
        }
```

## margin 속성으로 웹 문서 가운데 정렬

웹 문서에서 텍스트 요소를 배치할 때에는 text-align 속성을 사용했다. 만약 웹 문서 전체를 화면 중앙에 배치하려면 어떻게 해야 할까? 이 때 margin 속성이 유용하다.

1. 배치할 요소의 너빗값을 지정한다.
2. margin 속성의 좌우(margin-left와 margin-right)을 auto로 지정

<aside>
❕ 이렇게 하면 CSS는 웹 브라우저 화면의 전체 너비에서 요소 너빗값을 뺀 나머지 영역을 좌우 마진으로 자동 계산하여 결과적으로 가운데 정렬이 된다

</aside>

![13_margin.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/a8ec7ddd-3878-4c34-8e5c-817eef296b06/13_margin.png)

1. 웹 문서 전체를 하나로 묶은 div 태그에 #container 스타일 적용

        → #container 스타일

- 웹 문서의 너비를 600px로 정하고 background-color를 흰색으로
- 위아래 margin은 20px(사진에는 보이지 않지만 스크롤이 있으니 위아래 공백 있는거 맞다)
- 좌우 margin은 auto

1. 브라우저 전체의 배경은 body 태그에 타입 스타일로 회색 지정 (웹 문서의 중앙정렬을 뚜렷하게 확인하기 위함)

## 마진 중첩(margin overlap/collapse)

요소를 세로로 배치한 경우, 각 요소의 마진들이 서로 만나면 마진이 존나 커지는 것을 대비해서 마진을 중첩하여 작은 쪽이 상쇄되고 큰 쪽만 살아남는다.

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>마진 중첩</title>
    <style>
        div {
            width: 200px;
            height: 100px;
            margin: 30px;
        }
        #box1 {
            background-color: blue;
            margin: 100px 30px;
        }
        #box2 {
            background-color: coral;
        }
        #box3 {
            background-color: hotpink;
        }
    </style>
</head>
<body>
    <div id="box1"></div>
    <div id="box2"></div>
    <div id="box3"></div>
</body>
</html>
```

![30px끼리 상쇄됨. 100px가 30px 덮어씌움.](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/94098d46-1630-4b09-a759-7f8fcf8fa801/13_marginoverlap.png)

30px끼리 상쇄됨. 100px가 30px 덮어씌움.

# 컨텐츠와 테두리 사이의 여백: padding 속성

패딩과 마진은 여백의 위치만 다를 뿐, 박스 모델에서 패딩을 지정하는 방법은 마진과 아주 유사하다.

ㅇㅇ 그냥 똑같음

## 나만의 예제 - 발전+ ver.

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/6d60e345-319e-49f3-8c6b-b1d3125dd482/Untitled.png)

## 공백 이해를 위한 예제

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Document</title>
    <style>
        div {
            border: 2px solid black;
            padding: 20px;
            margin: 30px;
        }
        #container {
            width: 600px;
            margin: 0 auto;
            border: none;
        }
    </style>
</head>
<body>
    <div id="container">
        <div>
            <h1>문서 1</h1>
            <p>내용 1</p>
        </div>
        <div>
            <h1>문서 2</h1>
            <p>내용 2</p>
        </div>
        <div>
            <h1>문서 3</h1>
            <p>내용 3</p>
        </div>
    </div>
</body>
</html>
```

### Q. 선택자 우선순위에 관한 이야기

타입 선택자인 div보다 인라인 선택자인 #container이 우선순위가 높다==같은 속성이 있다면 덮어쓸 것이다. div에 border 속성으로 1px짜리 실선 검은색 테두리를 설정하고, #container에 border로 none으로 테두리를 없애줬는데 왜 겉에 있던 선이 사라지나? 상속의 원리가 적용되면 안에있는게 사라져야 하는거 아닌가?

### A. 아마도 내 생각에는...

div는 의미 없는 태그가 아니다. 의미가 없다는 말은 정말 의미가 없다는 뜻이 아니라, 태그 자체가 의미를 갖는다기 보다는 다른 요소들을 묶어주는 역할이 더 크기 때문에 그렇게 부르는 것 같다.(라기보다 이전에 배웠던 속성들이 텍스트나 폼, 표 등에만 적용 가능했기 때문에 div는 정말 묶음 역할로만 봤었고 하위 요소들에게까지 스타일을 상속해주는 의미로만 사용했다.)

즉 이제는 div라는 “묶음 공간” 자체에 (배경)색을 지정하거나, padding과 margin을 줄 수 있다는 이야기다. 그래서 스타일 우선순위 순서를 생각해보면 다음과 같겠다.

1. div 타입 선택자는 상위 div와 하위 div들에게 전부 적용된다.
2. #container 인라인 선택자는 상위 div에 지정되었다. border 속성이 겹치므로 #container의 속성으로 상쇄된다. 나머지 속성들은 타입 선택자에는 없던 설정이므로 상속되어 통째로 같이 적용된다. 

![#container 에 border: none 이 없을 때](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/1c56e6e2-88f5-4837-9973-01dbaf8ff309/14_border_none1.png)

#container 에 border: none 이 없을 때

![#container 에 border: none; 이 있을 때](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/495d25ca-ef88-45a7-bae6-9a57663d86fc/14_border_none2.png)

#container 에 border: none; 이 있을 때

## margin: 0 auto; 의 이미

중앙 정렬이다. 0은 단위가 없으니 크기나 백분율이 아니다 → 지정하지 않는다는 뜻.

실제로 위 코드에서 0 대신 30을 넣어도 동일한 결과가 나왔으며, 웹 문서에서 Computed 메뉴에서 0일때 마진을 확인해 봤더니 30이 나왔다.

![14_margin_0_auto.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/08506138-762b-4153-84cc-3d201fb0fdf5/14_margin_0_auto.png)

## 코드의 적절한 분비?

```html
<style>
        div {
            width: 600px;
            border: medium solid blue;
            padding: 20px;
            margin: 30px auto;
        }
        #container {
            border: none;
        }
    </style>
```

![Animation.gif](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/664b9473-45a7-4cae-8cd4-3d47537d0f2d/Animation.gif)

```html
<style>
        div {
            border: medium solid blue;
            padding: 20px;
            margin: 30px;
        }
        #container {
            width: 600px;
            border: none;
            margin: 0 auto;
        }
    </style>
```

![Animation2.gif](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/71617d96-6099-49e2-b08a-6ac99f92e03a/Animation2.gif)