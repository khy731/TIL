# 웹 문서의 레이아웃 만들기

박스 모델의 블록 레벨, 인라인 레벨을 이해했다면 웹 문서의 레이아웃을 만들어 보자.

# 배치 방법을 결정 : display 속성

`display` 속성은 요소를 어떻게 보여줄지를 결정합니다.

HTML의 모든 요소는 각각의 기본 display 속성값을 가지고 있다. display 속성으로 block-level 요소와 in-line-level 요소를 서로 바꿔서 사용할 수 있다. 그러나, display 속성값을 변경해도, 실제로 해당 요소가 완전히 다른 타입의 요소로 바뀌는 것은 아니다; 말 그대로 보여주는 방식(display)이 바뀐 것 뿐. 즉, display 속성값을 인라인에서 블록으로 변경했더라도, 변경된 요소는 내부에 다른 요소를 포함할 수 없다. 왜냐하면, 처음부터 display 속성값이 블록인 요소만이 내부에 다른 요소를 포함할 수 있기 때문이다.

## ***block***

- ***가로 영역을 모두 채우며**, block 요소 다음에 등장하는 태그는 줄바꿈이 된 것처럼 보입니다. 해당 라인의 모든 너비를 차지합니다. `block` 요소 뒤에 등장하는 태그는 **항상 다음 줄**에 렌더링됩니다.*
- `*width`, `height` 속성을 지정 할 수 있습니다.*

## ***inline***

- `*block` 과 달리 줄 바꿈이 되지 않고, 볼드, 이탤릭, 색상, 밑줄 등 **글자나 문장에 효과를 주기 위해 존재하는 단위**라고 할 수 있습니다. 요소의 너비도 해당 라인 전체가 아닌 해당 HTML 요소의 내용(content)만큼만 차지합니다. `inline` 요소 뒤에 나오는 태그는 줄바꿈 되지 않고 바로 오른쪽에 표시됩니다.*
- *`width`와 `height`를 지정 할 수 없습니다.*

# inline-block

display 속성값이 인라인-블록으로 설정된 요소.

- 요소 자체는 인라인(inline) 요소처럼 동작합니다.
- 하지만 요소 내부에서는 블록(block) 요소처럼 동작합니다.

→  블록 요소처럼 weight와 height으로 너비와 높이를 설정할 수 있으며 margin과 padding으로 여백을 지정할 수 있습니다. 그리고 인라인 요소처럼 가로로 늘어서게 됩니다. 

## display의 속성값들

- block : 인라인 레벨 요소 → 블록 레벨 요소
- inline : 블록 레벨 요소 → 인라인 레벨 요소
- inline-block : 두 요소의 속성을 모두 가지고 있음. margin과 padding을 지정 가능
- none : 해당 요소를 화면에 표시하지 않음

## 수평 nav(메뉴) 만들기

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>DisplayNav</title>
    <style>
        * {box-sizing: border-box;}     /* 모든 요소에 테두리까지 포함한 너빗값 지정 */
        nav ul {
            list-style: none;           /* 불릿이나 숫자 번호 없앰 */
        }
        nav ul li {
            display: inline-block;      /* 블록과 인라인 레벨 요소 모두 지정 */
            margin: 0 30px;
            padding: 20px;
            border: 1px solid blueviolet;
        }
        #container {
            width: 600px;
            margin: 0 auto;             /* 중앙정렬 (width로 너비 먼저 선언해야 가능) */
        }
    </style>
</head>
<body>
    <div id="container">
    <nav>
        <ul>
            <li>menu1</li>
            <li>menu2</li>
            <li>menu3</li>
        </ul>
    </nav>
    </div>
</body>
</html>
```

![15_display_nav](https://user-images.githubusercontent.com/97890886/163704733-c314f95c-3b2b-4624-ac75-0e4749887899.png)

![15_display_nav2](https://user-images.githubusercontent.com/97890886/163704741-7598b4c1-067e-4091-9d2b-3b3dfabcfc62.png)


style을 작성하기 전 모양.

# 왼쪽/오른쪽 배치 : float 속성

flaot속성으로 이미지를 표시하고 그 주변을 텍스트가 둘러싸듯이 할 수 있습니다. float 속성은 웹 요소를 문서 위에 떠 있게 만듭니다. ‘떠 있다’는 말은 요소가 왼쪽 구석이나 오른쪽 구석에 배치된다는 것을 의미합니다.

속성값들

- left : 해당 요소를 문서의 왼쪽에 배치합니다
- right : 해당 요소를 문서의 오른쪽의 배치합니다
- none : 좌우 어느쪽에도 배치X. 기본값

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>텍스트 왼쪽에 이미지 배치하기</title>
    <style>
        img {
            float: left;    /* 왼쪽에 떠 있게 */
            margin-right: 40px;    /* 오른쪽 마진 */
        }
    </style>
</head>
<body>
    <img src="cat.jpg" alt="고양이">
    <p>고양이는 인류로 부터 오랫동안 반려동물로 사랑받아 왔다. 실례로 고대 이집트의 벽화에는 고양이를 새 사냥에 이용하는 그림이 있다. 고양이와 인간의 공생관계는 농경의 발달로 이집트 문명이 발생했을 무렵 곡식을 저장하는 창고에 모여든 쥐를 따라온 것이 시작으로 알려져 있다. 때문에 고양이는 길들여진 동물인 가축의 특성을 전혀 지니고 있지 않으며, 가축이라기보다는 인간과 공생관계라고 보는 것이 맞다. 이 후 아라비아 상인들의 실크로드를 통해 유럽과 아시아 전역으로 퍼져나갔으며, 항해를 하는 데에도 도움이 되어 인간과 함께 항해를 동행하면서 전 세계로 퍼져나갔다. 중국의 십이지에는 포함되어 있지 않지만 베트남과 네팔에서는 토끼 대신 고양이가 십이지 중 하나다.</p>
</body>
</html>
```

![15_float](https://user-images.githubusercontent.com/97890886/163704758-45be9b59-749b-4f92-90b2-a1a428b528d1.png)

# float 속성을 해제 : clear 속성

float 속성으로 웹의 요소를 왼or오에 배치하면 그 다음으로 넣는 다른 요소에도 같은 속성이 전달되는데, 이를 해제하는 것이 clear 속성이다.

- left - float : left를 해제
- right - float : right를 해제
- both - 둘 다 해제

```html
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <title>Float 연습</title>
    <style>
        div {
            margin: 30px;
            padding: 20px;

        }
        #box1 {
            background-color: blueviolet;
            float: left;
        }
        #box2 {
            background-color: coral;
            float: right;
        }
        #box3 {
            background-color: aqua;
        }
        #box4 {
            background-color: chartreuse;
            clear: both;
        }
        #container {
            width: 500px;
            margin: 0 auto;
        }
    </style>
</head>
<body>
    <div id="container">
        <div id="box1">box1</div>
        <div id="box2">box2</div>
        <div id="box3">box3</div>
        <div id="box4">box4</div>
    </div>
</body>
</html>
```


![15_float2](https://user-images.githubusercontent.com/97890886/163704772-9accab9f-15fc-4dbe-b96f-a39d3268c82b.png)

### TIP : 가로 정렬에 있어서 display : inline-block과 float : left 의 차이

마진과 패딩 유무의 차이. 전자는 기본 마진과 패딩이 있지만, 후자는 보다시피 없어서 요소마다 따로 지정해줘야 한다. 그리고 후자는 clear로 해제도 해줘야 한다.