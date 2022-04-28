# 가상 클래스 : 사용자의 동작에 반응하다

사용자가 웹 요소를 클릭하거나, 마우스 포인터를 올려놓는 등 특정 `동작을 할 때 스타일이 바뀌도록` 할 수 있다. 콜론(:) 1개가 붙는다.

## :link 가상 클래스 선택자

웹 문서의 링크 중 사용자가 아직 `방문하지 않은 링크`에 스타일을 적용. 이러한 텍스트 링크의 기본값은 파란색 글자+밑줄이지만, 이를 바꾸고 싶을 때 이 선택자를 이용한다.

## :visited 가상 클래스 선택자

웹 문서의 링크 중 한 번 이상 `방문한 링크`에 스타일을 적용. 보라색이 기본값.

## :hover 가상 클래스 선택자

웹 요소 위로 `마우스 포인터`를 올려놓을 때 스타일을 적용. 이를 잘 활용하면 이미지 위로 마우스 포인터를 올려놓았을 때 

## :active 가상 클래스 선택자

웹 요소의 `링크나 이미지 등을 활성화`했을 때==클릭했을 때의 스타일을 지정. 예를 들면 어떤 웹 요소의 링크를 클릭하는 순간! 의 스타일을 지정할 수 있다.

## :focus 가상 클래스 선택자

웹 요소에 `초점`이 맞추어졌을 때 스타일 적용. 예를 들어 텍스트 필드 안에 마우스 포인터를 올려놓거나, 웹 문서에서 Tab을 눌러 입력 커서를 이동했을 때 스타일을 지정.

> 메뉴 링크에서 가상 클래스 선택자 사용하기

순서를 지켜야 한다.

1. :link
2. :visited 
3. :hover
4. :active

```css
#container {
    width: 1000px;
    margin: 0 auto;
}
.menu {
    width: 1000px;
    height: 200;
    padding: 0;
}
.menu ul li {
    float: left;
    width: 200px;
    list-style: none;
    padding-top: 5px;
    padding-bottom: 10px;
    border-bottom: 1px solid black;
}
.menu a:link, a:visited {
    text-decoration: none;
    text-align: center;
    display: block;
    padding-top: 5px;
    padding-bottom: 10px;
    color: black;
}
.menu a:hover, a:focus {
    background-color: dimgrey;
    color: white;
}
.menu a:active {
    background: indianred;
}
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>virtualClass</title>
    <link rel="stylesheet" href="virtualClass.css">
</head>
<body>
    <nav class="menu" id="container">
        <ul>
            <li><a href="#">이용 안내</a></li>
            <li><a href="#">요금표</a></li>
            <li><a href="#">오시는 길</a></li>
            <li><a href="#">예약하기</a></li>
        </ul>
    </nav>
</body>
</html>
```

![Honeycam 2022-03-19 17-15-12](https://user-images.githubusercontent.com/97890886/165737748-2ef9b256-ab2e-4835-9184-382e84596b2a.gif)


# 요소 상태에 따른 가상 클래스

요소의 상태에 따라 스타일을 적용할때 또한 가상 클래스 선택자를 사용합니다.

## :target 가상 클래스 선택자

웹 문서에서 다른 문서(예를 들면 특정 사이트의 페이지)로 이동할 때에는 `링크`를 사용하고, 같은 문서 내에서 다른 위치로 이동할 때에는 `anchor`를 사용한다. a태그의 속성 중 `target`은 클릭으로 링크를 오픈할 때 어디에서 오픈할지 정하는 속성인데, 이때 anchor의 목적지가 되는 부분의 스타일을 **:target 가상 클래스 선택자**로 쉽게 선택할 수 있다.

```css
#container {
    width: 1000px;
    margin: 0 auto;
}
.menu {
    width: 1000px;
    height: 200;
    margin-bottom: 30px;
}
.menu ul li {
    text-align: center;
    display: inline-block;
    width: 200px;
    font-size: 15px;
    list-style: none;
    border-bottom: 1px solid black;
    padding: 30px 0;
}
.menu a:link, a:visited {
    text-decoration: none;
    color: black;
    padding: 10px 20px;
}
.menu a:hover, a:focus {
    background-color: dimgrey;
    color: white;
}
.menu a:active {
    background: indianred;
}
.contents {
    width: 400px;
    height: 130px;
    border: 1px solid black;
    border-radius: 5px;
    margin: 30px auto;
    padding: 20px;
}
#intro:target {
    background-color: dodgerblue;
    color: white;
}
#money:target {
    background-color: goldenrod;
    color: white;
}
#way:target {
    background-color: violet;
    color:white;
}
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>virtualClass</title>
    <link rel="stylesheet" href="virtualClass.css">
</head>
<body>
    <nav class="menu" id="container">
        <ul>
            <li><a href="#intro">이용 안내</a></li>
            <li><a href="#money">요금 안내</a></li>
            <li><a href="#way">오시는 길</a></li>
            <li><a href="#rev">예약하기</a></li>
        </ul>
    </nav>
    <div id="intro" class="contents">
        <h3>이용 안내</h1>
        <p>아름다운 서해바다 낙조를 보면서 힐링하실 수 있는 캠핑장입니다. 바비큐, 수영장, 매점, 주차장 등 다양한 시설과 서비스를 제공합니다</p>
    </div>
    <div id="money" class="contents">
        <h3>요금 안내</h1>
        <p>삼성페이로 결제 시 50% 할인됩니다.</p>
    </div>
    <div id="way" class="contents">
        <h3>오시는 길</h1>
        <p>차량으로 오시는 것을 추천합니다.</p>
    </div>
</body>
</html>
```

![Honeycam 2022-03-19 18-12-03](https://user-images.githubusercontent.com/97890886/165737977-e33e93d5-2e7c-4d12-8a8c-70954ffda10d.gif)


## :enabled, :disabled 가상 클래스 선택자

- :enabled - 해당 요소가 사용할 수 있는 상태일 때의 스타일을 지정
- :disabled - 해당 요소가 사용할 수 없는 상태일 때의 스타일을 지정

예를 들면, 텍스트 영역 필드(textarea)를 사용한 회원 약관을 보여 줄 때가 있다. 이 때는 사용자가 입력할 수 없도록 disabled 속성을 지정해야 하는데, 이 때의 스타일을 가상 클래스 선택자로 지정하면 된다.

## :checked 가상 클래스 선택자

폼의 라디오 박스나 체크 박스에서 선택된 항목에는 checked라는 속성이 추가되는데, 이렇게 checked 속성이 있는 요소의 스타일을 지정하는 데에 편리합니다. 조금 생각해야 할 점은, 만약 글씨에 스타일을 지정하고 싶을 때에는 adjacent sibling selector를 사용하여 “input:checked” 내의 “label”을 선택해 줘야 한다는 점입니다.

```css
.form {
    padding: 10px;
    margin: 10px auto;
}
.form ul {
    padding: 10px;
}
.form ul li {
    list-style: none;
    padding: 10px;
}
#check input:checked + label {
    color: red;
    font-weight: bold;
}
```

```html
<div id="rev" class="contents" style="height: 350px;">
        <h3>예약하기</h3>
        <form>
            <fieldset class="form">
                <legend>개인 정보</legend>
                <ul>
                    <li>
                        <label for="userName">이름</label>
                        <input id="userName" type="text">
                    </li>
                    <li>
                        <label for="userCall">연락처</label>
                        <input id="userCall" type="del">
                    </li>
                </ul>
            </fieldset>
            <fieldset class="form" id="check">
                <legend>객실 형태</legend>
                <input type="radio" id="basic" name="room" value="1">
                <label for="basic">기본형</label>
                <input type="radio" id="family" name="room" value="2">
                <label for="family">가족형</label>
            </fieldset>
        </form>
    </div>
```

![Honeycam 2022-03-19 18-51-48](https://user-images.githubusercontent.com/97890886/165738057-68d8de97-6240-45c2-8f7a-ce9875b4d26e.gif)

## :not 가상 클래스 선택자

괄호 안에 있는 요소를 제외한다. 속성 선택자를 사용하여 괄호 안에 있는 요소만을 선택할 수도 있지만, 여러개 중 하나만을 제외해야 한다면 일일이 속성 선택자를 사용하는 것 보다 이게 편할수도 있다.

```css
#signup input:not([type=radio]) {
    padding: 3px;
}
```

# 구조 가상 클래스

웹 문서의 구조를 기준으로 특정 위치에 있는 요소를 찾아 스타일을 적용한다.

## 특정 위치의 자식 선택하기

원래 웹 문서의 특정 요소에 스타일을 적용하려면 보통 class나 id를 사용하는 것이 일반적이나, 요소가 나열식으로 되어있는 경우 굳이 이를 사용하지 않고 “몇 번째 요소에 스타일을 지정하라”라고 명령할 수 있습니다.

```css
.contents :nth-child(3) {
    background-color: palevioletred
}
.contents p:nth-of-type(3) {
    background-color: palegreen
}
```

헷갈리기 쉬운 두 선택자

- :nth-child() - 부모 요소 중 n번째
- A:nth-child() - 부모 요소 중 A 요소 중 n번째

```html
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <title>virtualClass2</title>
    <link rel="stylesheet" href="virtualClass2.css">
</head>
<body>
    <div class="contents">
        <h2>제목</h2>
        <p>본문1</p>
        <p>본문2</p>
        <h2>소제목</h2>
        <p>본문3</p>
    </div>
</body>
</html>
```


![22_virtualClass](https://user-images.githubusercontent.com/97890886/165738199-37c22842-22c7-4e8e-8fac-f3bb97784bbd.png)

> TIP : 방금 배운 구조 가상 클래스 선택자를 유용하게 사용했다!

![22_virtualClass2](https://user-images.githubusercontent.com/97890886/165738246-2f9183d4-74e2-44e7-9fe2-19c29b81c10c.png)

만든 예제를 보면 알 수 있듯이, 모든 div 의 스타일이 동일한데 마지막 구간만 높이가 다르다. 이를 만들기 위해서 따로 class나 id를 만들기는 비효율적이라 판단되어 인라인 스타일로 그냥 html에 때려박았는데, 상당히 마음에 들지 않았다.

이 때 A:last-of-type을 사용하여 “부모 안에 있는 A요소 중에서 마지막 요소만을 선택” 해보겠다.

```css
.box div:last-of-type {
    height: 350px;
}
```

그러나 이는 적용되지 않았다. 당연하지만, 이 코드는 ‘부모 요소(box 클래스를 사용한 요소) 안에 있는 div 요소 중에서 마지막 요소’를 선택하는 코드이다. 코드 자체는 잘 썼으나, 이제 box 클래스를 어디에 사용했느냐가 문제다. 확인해보니, 그냥 마지막 div에 저걸 썼더라. 그러면 차원이 맞지 않는다. 그래서 div 4개로 나뉘어진 전체 코드를 또 하나의 div로 묶어 상속시키고, 가장 부모 차원의 div에 box클래스를 사용하였더니 적용되었다.

## 위치를 수식화, 키워드화하기

위 예시처럼 특정 위치를 선택자로 그냥 적어줄 수 있지만, 만약 이러한 구조가 계속해서 반복된다면 홀수번째, 짝수번째 등의 위치는 아주 단순하게 나타낼 수 있습니다.

```css
/* 홀수 */
div p:nth-of-type(odd) {
}
div p:nth-of-type(2n+1) {
}

/* 짝수 */
div p:nth-of-type(even) {
}
div p:nth-of-type(2n) {
}
```

# 가상 요소

> 가상 클래스

기존 클래스위 에 가상으로 웹 문서의 여러 요소 중에서 원하는 요소를 선택할 수 있게 해 준다.

>가상 요소

원하는 특정 부분에 스타일을 적용하기 위해 가상으로 만든 요소이다.

화면에 보이는 부분을 꾸밀 때 불필요한 태그를 사용하지 않도록 하기 위해 사용된다. 가상 요소는 가상 클래스와 구별하도록 콜론 2개를 붙여 사용된다.

## ::first-line, ::first-letter 요소

말 그대로, 각각 첫 번째 줄, 첫 번째 글자에 스타일을 적용한다. 단, 첫 번째 글자의 경우 꼭 첫 번째 줄에 존재해야 한다. 

## ::before 요소, ::after 요소

지정한 요소의 내용 앞뒤에 스타일을 넣을 수 있다. 만약, 제품 목록에 대한 코드를 작성하고, 새로운 제품이 출시될 때마다 신제품 목록 옆에 new! 표시를 넣고 싶다면? 그냥 코드 내에 추가할 수도 있지만, 신제품은 계속 갱신될 것이고 코드를 계속해서 수정하는 것은 비효율적이다. 이것도 약간 OOP의 원리가 적용되는 듯. ::after를 사용하여 “목록 요소 뒤”를 선택하는 코드를 작성하면, 이 코드만 ctrl+x ctrl+v하여 쉽게 신제품 표시를 바꿀 수 있다.