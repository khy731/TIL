![6_css_mean](https://user-images.githubusercontent.com/97890886/161543171-fd9978ac-3333-441f-864c-d27eaca821eb.png)

# Style

웹 문서에서 `style`이란 HTML 문서에서 사용하는 여러 요소의 배치 방법 등 **문서의 겉모습**을 결정짓는 것을 의미한다. 그런데 왜 이러한 것을 HTML로 처리하지 않고 굳이 따로 style을 사용하는 것일까?

>웹 문서의 내용과 디자인을 분리하자

뼈대와 살이 같은 성분으로 되어있지 않고 분리되어 있듯이, 웹 문서의 내용과 디자인이 분리되어 있으면 내용을 수정해도 디자인에 영향을 끼치지 않고 스타일 시트로 디자인만 바꿔도 동일한 내용의 다른 느낌이 나는 문서로 바꿀 수 있다.

또한, HTML 문서는 PC 웹 브라우저 화면이 디폴트이므로 다른 기기에서 볼 때 해당 브라우저에 적합하게 웹 문서를 다시 따로 만들어야 했다. 그러나 대상 기기에 맞게 CSS만 바꿔주면 동일한 내용을 다양한 기기에서 쾌적하게 볼 수 있고, 이것이 바로 반응형 웹 디자인이다.

![6_disable_CSS_style](https://user-images.githubusercontent.com/97890886/161543405-daea2731-a741-4b2a-8cd1-fa611ecd2977.png)

CSS를 web developer 확장 프로그램을 이용해 disable 했을 때 벌어지는 일

# style의 규칙

CSS 소스에서의 한 줄==하나의 style

```css
선택자 { 속성1: 속성값1; 속성2: 속성값2; }
```

```css
/* 여러 줄 표기 */
p {
    text-align: center;
    color: aqua;
}

/* 한 줄 표기 */
p { text-align: center; color: aqua; }
```

- style을 텍스트 단락에 적용할 것이므로 선택자를 p로 지정
- 텍스트 정렬을 지정하는 text-align 속성 사용
- 글자 색을 지정하는 color 속성 사용
- 여러 줄로 표기하든, 한 줄로 표기하든 각자의 장단점이 있음.
- CSS소스의 ‘줄 바꿈’과 ‘주석’은 프로그래머, 즉 사람이 보기 편하게 하기 위해 있는 것

# Style sheet

웹 문서 안에서는 스타일 규칙을 여러 개 사용하는데, 이러한 스타일 규칙을 한 눈에 확인하고 필요할 때마다 수정하기도 쉽도록 정리하여 묶어놓은 것이 `Style sheet`이다.

![6_stylesheet_classify](https://user-images.githubusercontent.com/97890886/161543613-f59825d1-cf27-43be-8679-130543ff6b12.png)

> 브라우저 기본 스타일

웹 브라우저에 기본으로 정해져 있는 스타일. (예시: h1 태그가 다른 텍스트보다 크고 볼드체가 적용되어 있는 경우 등)

> 사용자 스타일

사이트 제작자가 만듦.

1. `인라인 스타일` : 간단한 스타일 정보일 경우, 스타일 시트를 사용하지 않고 HTML 문서에서 적용할 대상에 직접 표시하는 방식.
   
2. `내부 스타일 시트` : 웹 문서 안에서 사용할 스타일을 같은 HTML 문서(의 head 태그 안)에 정의 한 것.
   
3. `외부 스타일 시트` : 웹 문서에서 사용할 스타일을 별도 파일(.css)로 저장해 놓고 필요할때마다 사용하는 방식.

```css
<link rel="stylesheet" href="외부 스타일 시트 경로">
```

```css
/* mystyle.css */
h1 {
    padding: 10px;
    background-color: #222;
    color: #fff;
}

/* .html */
<head>
    <link rel="stylesheet" href="mystyle.css">
</head>
```

# 선택자(selecter)

웹 문서에서 ‘어느 부분’에 스타일을 적용할지 알려 주는 것. 

## 전체 선택자
> 전체 요소에 스타일을 적용

스타일을 문서의 `모든 요소`에 적용할 때 사용한다. 주로 모든 하위 요소에 스타일을 한꺼번에 적용할 때, 웹 브라우저의 기본 스타일을 초기화할 때 사용하는 것이 일반적이다.

```html
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <title>상품 소개 페이지</title>
    <style>
        * {
            margin: 0;
        }
    </style>
</head>
<body>
    <img src="cat.jpg" alt="고양이">
</body>
</html>
```

> TIP: 태그와 요소?

태그는 말 그대로 <p> 태그. 요소는 <p>태그를 적용한 단락, 문장, 코드 그 자체.

## 타입 선택자

> 특정 요소에 스타일을 적용

`특정 태그를 사용한 모든 요소`에 스타일을 적용한다.

```css
p {
    text-align: center;
    color: aqua;
}
```

## 클래스 선택자

> 특정 부분에 스타일을 적용

같은 태그라도 일부는 다른 스타일을 사용하고 싶다면 경우 등 특정 부분만 선택해서 스타일을 적용할 때 사용한다. 클래스명 앞에는 꼭 `마침표(.)`를 찍는다.

클래스 스타일(클래스 선택자를 사용해 만든 스타일) 을 적용할 때에는 <태그>안에 class=”클래스명”와 같이 class 속성을 사용해서 지정한다.

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>상품 소개 페이지</title>
    <style>
        p {
            font-style: italic;
        }
/* accent 클래스 */
        .accent {
            border: 1px solid #000;    /* 테두리 */
            padding: 0px;              /* 테두리와 내용 사이의 여백 */
        }
/* bg 클래스 */
        .bg {
            background-color: #75afdf;    /* 배경색 */
        }
    </style>
</head>
<body>
    <div>
        <h1 class="accent bg">제철과일</h1>
        <p>제철 과일이 단돈 <span class="accent">만원</span>입니다</p>
        <p>절대로 할인을 놓치지 마세요</p>
        <p><span class="bg">최대</span>할인입니다</p>
    </div>
</body>
</html>
```

![6_class_selecter](https://user-images.githubusercontent.com/97890886/161545203-bdeeeb9d-71df-4301-aab6-5062bc3818aa.png)


## id 선택자

> 특정 부분에 스타일을 한 번만 적용

클래스 선택자와 비슷하게, 웹 문서의 특정 부분을 선택해서 스타일을 지정할 때 사용한다.

- 마침표(.)기호 대신 `# 기호`를 사용
- 클래스 선택자는와 달리 `중복 불가능`하다. → 주로 문서의 레이아웃을 설정하거나 자바스크립트와 병행 사용할 때 요소를 구별할 때 사용한다.

```html
...
        #container {
            width: 500px;
            margin: 10px auto;
            padding: 10px;
            border: 1px solid rgb(221, 125, 125)
        }
    </style>
</head>
<body>
    <div id="container">
...
```

![6_id_selecter](https://user-images.githubusercontent.com/97890886/161545412-1ff6f43b-619f-4ede-b226-5f91c1a93567.png)

id 선택자로 문서를 중앙에 배치하고 테두리를 그렸다.

# 그룹 선택자

> 같은 스타일의 요소를 묶다

여러 선택자에서 같은 스타일 규칙을 사용할 때, `쉼표`로 구분하여 여러 선택자를 나열한 수 스타일 규칙을 한 번만 정의한다.

```css
h1 {
    text-align: center;
}
p {
    text-align: center;
}

/* 그룹 선택자를 사용하여 <h1>,<p> 태그를 중앙 정렬하기 */
h1, p {
    text-align: center;
}
```

# 캐스케이딩

cascading: 위에서 아래로 흐르는, 계단식, 상속/종속

> 우선순위가 있는 스타일 시트

캐스케이딩은 스타일끼리 충돌하지 않도록 막아주는 개념이다. 이 개념이 적용된 케스케이딩 스타일 시트(CSS)에서는 웹 요소에 둘 이상의 스타일을 적용할 때 우선순위에 따라 적용할 스타일을 결정한다.


## 스타일 우선순위

어떤 스타일을 먼저 적용할 것인가?

> 1. `얼마나 중요`한가?

웹 문서에서 스타일이 적용되는 순서는 다음과 같다.
1. user 사용자가 지정한 스타일
2. author 제작자가 지정한 스타일
3. browser 웹 브라우저가 기본으로 정해놓은 스타일
   
![6_style_우선순위_1](https://user-images.githubusercontent.com/97890886/161546042-de78ef8d-ccde-4d54-a007-e6fa2bf8abb2.png)

예를 들어, `브라우저 기본 스타일`에서 배경은 `흰 색`이다.
그런데 웹 문서의 배경을 회색으로 지정하는 `스타일을 제작`하여 적용했다. 그러면 배경은 흰색이 아닌 `회색`이 된다. 그런데 `사용자`가 다크모드를 적용하여 배경을 `검은색`으로 지정했다면 배경은 결국 검은색이 될 것이다.

> 2. `적용 범위`는 어디까지인가?

만약 “1. 얼마나 중요한가?” 에서 중요도가 같은 스타일로 판정이 나면 그 다음으로는 `스타일의 적용 범위`에 따라 우선순위가 정해진다. 스타일 적용 범위가 좁을수록 -이는 곧 특정 요소에 정말로 필요하다는 의미이므로- 우선순위가 높아진다. 그러나 이러한 우선순위의 흐름을 깰 명령어: `!important`은 어떤 스타일보다 우선순위를 높게 만든다.

![6_style_우선순위_2](https://user-images.githubusercontent.com/97890886/161546454-99538d03-3d59-433e-8f2c-32f7ccc5cb7c.png)

1. important
2. in-line style
3. id style 
4. class style 
5. type style

> 3. `소스 코드의 작성 순위`는 어떠한가?

만약 앞 조건들에서 전부 동점이라면, 스타일을 정의한 소스로 우선순위가 정해진다. 즉, 소스에서 나중에 작성한 스타일이 먼저 작성한 스타일을 덮어쓰게 된다.

<aside>
☝ 다음 코드를 보고 출력 결과를 예상해보자.

</aside>

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <title>명상</title>
    <style>
        p {
            color:black;
        }
        h1 {
            color:red !important;
        }
        p {
            color:aqua;
        }
    </style>
</head>
<body>
    <h1 style="color:blueviolet";>명상 하는 법</h1>
    <p style="color: gold;">공부를 합니다</p>
    <p>책을 봅니다</p>
    <p>잠이라도 자세요</p>
</body>
</html>
```

![6_style_우선순위_3](https://user-images.githubusercontent.com/97890886/161546802-9f412bd3-e512-4a81-9e09-0f33186ba0f1.png)

1. type style로 h1에 red를 지정했다. 이후 in-line style로 h1 태그에 bluviolet을 지정했다. 적용 범위에 따른 우선순위로는 in-line이 우세하나, 전자에 !important 명령어를 사용하였으므로 red가 이겼다.
2. type style로 p에 black을 지정했다. 이후 in-line style로 p 태그에 gold를 지정했다. 적용 범위에 따른 우선순위에 따라 모든 태그에 적용되는 type style보다 in-line style이 우위이므로 gold가 이겼다.
3. type style로 p에 black을 지정했다. 이후 또 type style로 p에 aqua를 지정했다. 적용 범위에 따른 우선순위가 일치하므로 나중에 쓰여진 코드인 aqua가 black을 덮어쓰면서 이겼다.

![6_style_우선순위_4](https://user-images.githubusercontent.com/97890886/161546857-111f5ce2-cafe-403b-8546-16910246880e.png)