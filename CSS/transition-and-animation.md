# 트랜지션

웹 문서에서 CSS 변형을 이용하여 사용자의 동작에 반응해 텍스트, 이미지 등의 요소를 움직이게 해 봅시다.

# 변형(transform)

transform 속성과 변형 함수 이름을 함께 써 줍니다.

```css
.text { transform: translate (50px, 100px); }
```

## 2차원 변형과 3차원 변형

2차원 변형은 다들 아는대로 x축과 y축. 3차원 변형은 거기에 “원근감” z축을 추가했다고 볼 수 있다. z축은 앞뒤로 이동하며, 보는 사람 쪽으로 다가올수록 값이 커지고 뒤로 갈수록 값이 작아진다.

### 2차원 변형

함수 뒤에 대문자로 X 혹은 Y를 붙이면 둘 중 하나의 값만 변경하는 것도 가능

- translate (x,y) : 지정한 크기만큼 x,y 으로 이동
- scale (x,y) : 지정한 크기만큼 x,y로 확대, 축소
- rotate (각도) : n축을 중심으로 지정한 각도만큼 회전
- skew (ax,ay) : 지정한 각도만큼 x,y로 왜곡

### 3차원 변형

함수 뒤에 대문자로 X,Y 혹은 Z를 붙이면 셋 중 하나의 값만 변경하는 것도 가능

- translate3d (x,y,z) : 이동
- scale3d (x,y,z) : 확대, 축소
- rotate3d (x, y, z, 각도) : 회전
- perspective(길이) : 입체적으로 보일 수 있게 “깊이”의 정도를 지정.

## translate() 함수

translate, translate3d, translateX, translateY, translateZ 등의 다양한 형태가 있다. 이동할 거리를 지정하면 해당 요소가 지정한 크기만큼 이동한다. 만약 translate()에서 y값이 주어지지 않으면 0으로 간주한다.

## scale() 함수

파라미터가 1보다 크면 확대 / 1보다 작으면 축소됨 

## rotate() 함수

### 2차원인 경우

각도만 지정하면 된다. 각도만큼 돌려준다. 값의 단위는 degree(각도)에서 따온 deg나, 라디안(radian, 180/1파이) 방향은 양수 - 시계방향(오), 음수 - 반시계방향(왼)

### 3차원인 경우

말 그대로, 지정한 축을 ‘중심축’으로 삼아 돌아간다.  단 요소 자체에 입체효과기 있는 것은 아니라서 예제를 연습해 보면 모양만 보고 감이 안 올 수도 있다. 그래서 perspective 속성을 함께 사용하여 원근감을 추가해 줘도 괜찮다. (주의할 점은 perspective 속성을 사용할 때에는 적용대상 요소가 아닌 그 부모 요소에 정의해줘야 한다.)

## skew() 함수

왜곡한다. 잘 사용하면 사각형을 마름모로 만드는 등 이미지를 따로 사용하지 않고도 도형의 형태를 만들 수 있다.

```css
#content {
    width: 1000px;
    margin: 0 auto;
    padding: 10px;
    box-sizing: border-box;
}
.origin div{
    width: 200px;
    height: 200px;
    background-color: lightcoral;
    border: 1px solid black;
    display: inline-block;
    margin: 30px;
}
#transX:hover {
    transform: translateX(50px);
}
#transY:hover {
    transform: translateY(50px);
}
#transXY:hover {
    transform: translate(-50px, -50px);
}
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>translate</title>
    <link rel="stylesheet" href="translate.css">
</head>
<body>
    <div class="origin" id="content">
        <div id="transX"></div>
        <div id="transY"></div>
        <div id="transXY"></div>
    </div>
</body>
</html>
```

![Honeycam 2022-03-20 18-41-39](https://user-images.githubusercontent.com/97890886/165881432-936b21b1-64e1-4ef2-b130-1b31a0b90048.gif)


# 트랜지션 transition

요소를 이동, 회전, 왜곡시키는 단순한 변형에서 한걸음 더 나아가 보자. 트랜지션은 하나의 스타일을 완전히 다른 스타일로 바꾼다. 스타일이 바뀌는 시간까지 조절하여, 자바스크립트 없이도 애니메이션 효과를 줄 수 있다.

## 트랜지션의 대상 지정 : transition-property 속성

```html
transition-property: all | none | 속성명
```

- all : 모든 속성이 트랜지션의 대상이 됨. 기본값
- none : 트랜지션을 하는 동안 아무 속성도 바뀌지 않음
- 속성명 : background-color, width 등 원하는 대상만 골라 지정 가능. 여러개면 쉼표로 구분

## 트랜지션의 진행 시간 지정 : transition-duration 속성

지정할 수 있는 시간 단위는 s(초,sec)또는 ms(밀리초,millisec)이다.

## 트랜지션의 속도 조정 : transition-timing-function 속성

트랜지션 효과의 시작, 중간, 끝에서 속도를 지정해 마치 곡선 함수처럼 속도의 흐름을 정할 수 있다.

```html
transition-timing-function: linear | ease | ease-in | ease-out | cubic-bezier(n,n,n,n)
```

- linear : 처음에는 천천히 시작 → 점점 빨라짐 → 마지막에 다시 천천히 끝냄. 기본값
- ease : 처음부터 끝까지 동일한 속도
- ease-in : 느리게 시작
- ease-out : 느리게 끝
- cubic-bezier(n,n,n,n) : 베지에 함수(곡선 함수)를 정의하여 지정. n값은 0~1로만 표현 가능

## 트랜지션의 지연 시간 설정 : transition-delay 속성

지정한 시간민큼 기다렸다가 트랜지션이 시작됨.

## 트랜지션의 속성 한꺼번에 표시하기: transition 속성

순서는 상관 없으나, 시간값을 사용하는 속성이 2개이므로  앞에 오는 시간값이 transition-duration, 뒤에 오는 시간값이 transition-delay 이다.

```css
#container {
    width: 600px;
    margin: 0 auto;
    box-sizing: border-box;
}
.box div {
    float: left;
    width: 70px;
    height: 200px;
    margin: 30px;
    background-color: lightseagreen;
    border: 1px solid black;
}
.box div:hover {
    transition: 3s ease;
    background-color: blue;
    height: 400px;
    transform: rotate(45deg);
}
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>transition</title>
    <link rel="stylesheet" href="transition.css"
</head>
<body>
    <div id="container" class="box">
        <div></div>
        <div></div>
        <div></div>
        <div></div>
    </div>
</body>
</html>
```

![Honeycam 2022-03-20 19-57-08](https://user-images.githubusercontent.com/97890886/165881462-20ed13cf-424d-4e48-92bd-1dae137cace0.gif)

# CSS animation

animation 속성은 특정 지점에서 스타일을 바꾸면서 애니메이션을 만드는데, 이렇게 중간에 스타일이 바뀌는 지점을 키프레임 keyframe 이라고 한다. 이는 @keyframes 로 정의하고, animation 속성과 그 하위 속성을 이용해 실행 시간, 반복 여부 등을 지정한다.

## @keyframes, animation-name 속성

@keyframes로 애니메이션의 지점(시작과 끝), 상태가 바뀌는 부분 등을 지정한다. 

```css
@keyframes 이름 {
    선택자 {
        스타일
    }
}
```

@keyframes 속성의 ‘선택자’는 스타일 전환 포인트이다. 즉 스타일 속성값이 바뀌는 지점을 가리키는 것이다. 예를 들어, 애니메이션의 중간 부분에 스타일을 추가하고 싶다면 시작을 0% 끝을 100%로 놓고 50%위치에 키프레임을 추가한다. 시작과 끝만 사용하려면 %게이지 대신 from(시작)과 to(끝)만 사용해도 된다.

```css
animation-name: 이름 | none
```

웹 문서에선 애니메이션을 여러 개 정의할 수 있으므로 각 애니메이션에 이름을 붙여 이를 구분한다. animation-name 속성을 사용한다.

## animation-duration 속성

애니메이션을 재생할 시간 지정. s나 ms같은 시간 단위를 사용 가능하다.

## animation-direction 속성

애니메이션의 방향 지정. 기본적으로 from→to 순으로 진행되나, 이를 왜곡할 수 있다.

- normal : from→to. 기본값
- reverse : to→from.
- alternate : 홀수번째는 normal, 짝수번째는 reverse로.
- altaernate-reverse : 짝수번째는 normal, 홀수번째는 reverse로.

## animation-iteraction-count 속성

- 반복 횟수
- infinite

## animation-timing-function 속성

트랜지션과 마찬가지로 애니메이션의 시작,중간,끝에서 속도를 지정하여 전체 속도 곡선을 만들 수 있다.

## animation 속성으로 한꺼번에 표기하기

주의 : animation-duration 속성을 반드시 표기하라.