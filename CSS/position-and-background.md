# 웹 요소의 위치 지정하기

position 속성을 사용하여 웹 문서에서 요소의 위치를 자유롭게 정해보자. position 속성은 자주 사용하는 속성이지만, 그만큼 실수하기 쉽다.

## 위치 지정 : left, right, top, bottom 속성

position으로 기준 위치를 정한 후, 그 기준 위치로부터 어느 방향에서 얼만큼 떨어져 있는지를 지정해야 한다. 그 방향에 대한 속성이 바로 이 속성들이다.

## 배치 방법 지정 : position 속성

웹 문서 안의 요소를 자유자재로 배치해 준다. position으로 요소를 나란히 배치할 수도 있고, 원하는 위치를 선택할 수도 있다.

### 속성값들

- `static` : 웹 문서의 흐름에 맞춰 위→아래로 자연스럽게 배치됨. 기본값

- `relative` : static과 같이 웹 문서에 흐름에 맞춰 배치한다. 다른 점은, relative는 static과는 달리 위칫값을 지정할 수 있다. 요소를 **원래 위치(static)** 기준으로 상대적(relative)으로 배치해준다고 생각하면 된다.

- `absolute` :  absolute 속성값은 부모 요소를 기준으로 배치하는데, 이 부모 요소가 relative로 지정되는 것이 일반적이다.

- `fixed` : 브라우저 창을 기준으로 위치 지정해 배치. 즉 웹 브라우저에서 스크롤을 하더라도 항상 같은 위치에 나타나게 된다.

```css
p {
    background: gray;
    box-sizing: border-box;
    width: 200px;
    height: 150px;
    border: 5px solid red;
}
#fixed {
    position: fixed;
    background: black;
    width: 100px;
    height: 100px;
    top: 30px;
    right: 30px;
}
#static {
    position: static;
}
#relative1 {
    position: relative;
}
#relative2 {
    position: relative;
    left: 100px;
    bottom: 200px;
}
#absolute {
    position: absolute;
    left: 300px;
}
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>position</title>
    <link rel="stylesheet" href="position1.css"
</head>
<body>
    <p id="static">static</p>
    <p id="fixed">fixed</p>
    <p id="relative1">relative1</p>
    <p id="relative2">relative2</p>
    <p id="absolute">absolute</p>
</html>
```


## 예제 : 특정 요소를 기준으로 요소 배치하기 - absolute

```css
* {
    box-sizing: border-box;
    margin: 0;
    padding: 0;
}
#content {
    width: 800px;
    height: 500px;
    margin: 0 auto;
    background: url("cat.jpg") no-repeat;
    background-size: cover;

    position: relative;
}
h1 {
    font-size: 120px;
    color: indianred;
    text-shadow: 3px 3px gray;

    position: absolute;
    bottom: 100px;
    right: 200px;
}
```

```html
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <title>position2</title>
    <link rel="stylesheet" href="position2.css"
</head>
<body>
    <div id="content">
        <h1>CAT</h1>
    </div>
</body>
</html>
```

### absolute에 대하여

absolute는 부모 요소(relative)를 기준으로, “부모 요소(relative) 안에서” 움직인다. 단 주의할 점은, CSS뿐만 아니라 HTML 소스 내에서도 상속 관계여야 한다.

```html
<body>
    <div id="content"></div>
    <h1>CAT</h1>
</body>
```

이게 아니라

```html
<body>
    <div id="content">
        <h1>CAT</h1>
    </div>
</body>
```

이렇게 써 줘야 한다.


# 배경 꾸미기

# 배경색과 배경범위 지정하기

## 배경색 지정 : background-color 속성

하나 주의할 점은, background 값은 **스타일 상속에 영향을 받지 않는다**는 점이다. 글꼴이나 글자 크기 등은 문서 전체에 상속되지만,  background-color는 예외이다. 배경색을 지정했을 때 웹 전체에도 그 색이 적용된 것처럼 보이지만, 이는 대부분의 요소들이 기본적으로 투명하기 때문에 그렇게 보이는 것일 뿐, 배경 스타일이 상속된 것은 아니다.

## 배경색 적용 범위 조절 : background-clip 속성

box model 관점에서 배경의 적용 범위를 지정할 수 있다.

- border-box
- padding-box
- content-box

# 배경 이미지 지정하기

## 웹 요소에 배경 이미지 넣기 : background-image 속성

요소보다 이미지 크기가 작을 경우, 이미지가 `반복`해서 넣어지면서 요소의 배경을 가득 채운다.

```css
background-img: url('이미지 파일 경로')
```

## 배경 이미지의 반복 방법 지정 : background-repeat 속성

- `repeat` : 요소에 가득 찰 때까지 가로와 세로로 반복. 기본값
- `repeat-x` : 요소에 가득 찰 때까지 가로로 반복.
- `repeat-y` : 요소에 가득 찰 때까지 세로로 반복.
- `no-repeat` : 한 번만 표시, 반복 x

## 배경 이미지 위치 조절 : background-position 속성

```css
background-position: <수평 위치> <수직 위치> ;

/*
수평 위치: left | center | right | <백분율> | <길이 값>
수직 위치: top | center | bottom | <백분율> | <길이 값>
*/
```

속성값을 2개 지정한다면 순서대로 수평, 수직 위치의 값이 된다. 1개만 지정했으면 그 값을 수평 위칫값으로 간주하여 나머지 수직 위칫값은 center/50%로 대충 간주한다.

1. 키워드 : left, center, right / top, center, bottom
2. 백분율: 예를 들어 30% 60%라면 이미지를 넣을 요소의 왼쪽 모서리부터 가로 30%, 세로 60% 위치에 배경 이미지의 가로세로가 30%, 60%인 위치를 맞춘다.
3. 크기 : px 등을 사용. 예를 들어 30px 20px 이라면 가로 30픽셀 세로 20픽셀 위치에 배경 이미지의 왼쪽 상단 모서리를 맞춘다.

## 배경 이미지의 적용 범위 조절 : background-origin 속성

box model에 padding이나 border가 있다면, 배경 이미지를 어디까지 표시할 지 지정할 수 있다.

- content-box : 내용 부분까지
- padding-box : 패딩 부분까지
- border-box : 테두리 부분까지

## 배경 이미지를 고정 : background-attachment 속성

배경 이미지가 있는 웹 문서를 웹 브라우저에서 열고 스크롤 막대를 위아래로 조절하면 문서 전체가 움직이므로 배경 이미지도 함께 이동한다. 이때 고정할 수도 있다.

- scroll : 기본값
- fixed : 고정

## background 속성 하나로 전부 제어하기

순서 상관없이 그냥 속성값만 써주면 된다.

## 배경 이미지 크기 조절 : background-size 속성

배경을 채울 요소 크기에 비해 이미지가 너무 작거나 클 경우, 이미지 크기를 미리 조절할 수 있다. 특히 화면에 배경 이미지를 가득 채워야 할 경우에 유용하다.

- 키워드

  - auto : 원래 배경 이미지 크기만큼 표시. 기본값
  - contain : 요소 안에 배경 이미지를 전부 포함하도록-그러니까 이미지가 전부 보여야 하기 때문에 요소 공간을 최대한 활용하여 이미지 전체를 보여줘야 함-이미지를 조절(확대/축소)
  - cover : 배경 이미지로 요소를 모두 덮도록-그러니까 요소에 빈 자리가 없어야 하고 그걸 이미지로 전부 커버함- 이미지를 조절(확대/축소)

- 직접 지정

  - 크기 : 이미지의 너비, 높이 지정. 하나만 주어질 경우 너빗값으로 인식하여 높잇값은 자동 계산
  - 백분율 :  배경 이미지가 들어갈 요소의 크기를 기준으로 백분율 지정.

```css
.box {
    float: left;
    width: 300px;
    height: 300px;
    margin: 30px;
    border: 2px solid black;

    line-height: 300px;
    text-align: center;
    color: palevioletred;
    text-shadow: 2px 2px black;

    background: url('cat.jpg') no-repeat left top;
}
#container {
    width: 1100px;
    margin: 50px auto;
}
#box1 {
    background-size: auto;
}
#box2 {
    background-size: contain;
}
#box3 {
    background-size: cover;
}
#box4 {
    background-size: 50%;
}
#box5 {
    background-size: 100% 100%;
}
```

```html
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <title>이미지 크기 조절</title>
    <link rel="stylesheet" href="background.css"
</head>
<body>
    <div id="container">
        <div class="box" id="box1"><h1>auto</h1></div>
        <div class="box" id="box2"><h1>contain</h1></div>
        <div class="box" id="box3"><h1>cover</h1></div>
        <div class="box" id="box4"><h1>50%</h1></div>
        <div class="box" id="box5"><h1>100% 100%</h1></div>
    </div>
</body>
</html>
```

![17_background](https://user-images.githubusercontent.com/97890886/165299708-4e7c84f6-6ec8-4973-a144-ccac9e13891a.png)
