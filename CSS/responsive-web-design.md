# 반응형 웹 responsive web design

>접속하는 디스플레이의 종류에 따라 화면 크기가 자동으로 변하도록 만든 웹 페이지를 만들어 보자.

컴퓨터 모니터부터 휴대폰 화면까지... 디스플레이의 크기는 다양해져만 가는데 그때마다 사이트를 따로따로 만드는 것은 상당히 비효율적이다. 화면 크기에 `반응`하는 화면 요소를 자동으로 바꾸어 화면 크기에 맞게 재배치하고 각 요소의 표시 방법만 바꿈으로써 반응형 웹 디자인을 실현한다

# 뷰포트 vewport

모바일 웹을 작성하게 되면 `뷰포트(viewport)`라는 것을 고려하게 된다. 뷰포트란 **웹페이지가 사용자에게 보여지는 영역**을 말하는데, 휴대폰은 PC처럼 브라우저의 크기를 변경(스크롤로 %를 조절하여 뷰포트(브라우저에 보여지는 부분)을 조절)할 수 없는 것이 일반적이다.

이렇게 고정된 크기를 가진 웹페이지를 화면이 작은 휴대폰에서 보면 한 화면에 다보이지 않게 되는 문제가 생긴다. 모바일 웹페이지가 취하는 기본 해결방법은 기존 화면 자체를 줄여서 휴대폰 화면 크기에 맞게 우겨넣는 것인데, 이런 식이다.

![반응형웹의필요성1](https://user-images.githubusercontent.com/97890886/165882117-05195452-6507-40c7-828b-cdaf6bb2321d.png)

![반응형웹의필요성2](https://user-images.githubusercontent.com/97890886/165882138-b4ce6e74-9c27-4c13-a029-42d8339eb4ac.png)

이런 화면은 상당히 가독성이 떨어진다. 그래서 우리는 웹페이지가 브라우저에 보여지는 부분===뷰포트를 조절하여(화면 크기에 반응하는 요소들을 자동으로 바꿔) 이를 보기 좋게 만들거다.

# 뷰포트 지정하기

`meta 태그`를 이용한다.

```html
<meta name="viewport" content="속성1=값1", content="속성2=값2"...>
```

## content 속성

- `width` : 뷰포트의 너비. device-width 또는 크기를 속성값으로 사용. 기본값은 브라우저 기본값
- `height` : 뷰포트의 높이.  device-height 또는 크기를 속성값으로 사용. 기본값은 브라우저 기본값
- `user-scalable` : 확대,축소 가능 여부. yes or no를 속성값으로 사용. 기본값은 Y
- `intial-scale` : 초기 확대,축소 값. 1~10을 속성값으로 사용. 기본값은 1


> 웹 페이지 뷰포트의 너비를 스마트폰 화면 너비에 맞추고 초기 화면 배율을 1로 지정한다.

```html
<meta name="viewport" content="width=device-width, initial-scale=1.0">
```

## 뷰포트 단위

viewport의 개념이 등장하기 이전에는 px, %등을 애용하였지만 이제는 뷰포트를 기준으로 하는 단위를 사용할 수도 있다.

- vw (viewport width) : 1vw 은 width의 1%와 같음
- vh (viewport height) : 1vh 은 height의 1%와 같음
- vmin (viewport minimum) : width와 height 中 작은 값의 1%와 같음
- vmax (viewport maximum) : width와 height 中 큰 값의 1%와 같음

왜 이렇게 나뉘어져 있을까? 일단, width=1000px, height=800px 인 화면이 있다고 치자. 그렇다면

1 vw = 10px

1 vh = 8px

1 vmin = 8px

1 vmax = 10px

가 된다. 그런데 만약 화면을 뒤집어서 가로와 세로(너비와 높이)가 바뀐다면? vw와 vh는 값이 swap될 것이다. 그러나 vmin과 vmax의 값은 변하지 않을 것이다.

> TIP : 크롬 브라우저의 [디바이스 모드]

viewport의 예제를 여러 기기에서 확인한답시고 컴퓨터와 휴대폰을 계속 번갈아서 사용하면 개발에 불편함이 크다. `크롬 개발자 도구`의 `디바이스 모드`를 활용하여 화면 크기를 조절하면서 확인해보도록 하자.

또한 [yesviz.com/devices.php](http://yesviz.com/devices.php) 에는 특정 기기에 맞는 미디어 쿼리를 작성하는 데 필요한 뷰포트의 크깃값이 정리되어 있다. 이 사이트에 접속한 뒤 목록에서 기기를 선택하면 화면 크기, 뷰포트 크기 등 미디어 쿼리 작성에 필요한 정보를 확인할 수 있다. 참고하면 좋다.

# 미디어 쿼리 media queries

CSS기술로 미디어 타입, 화면 크기 등을 기준으로 다른 스타일 시트를 적용할 수 있도록 해준다. 이를 이용하면 화면 크기가 변할때 스타일을 바뀌도록 하는 등의 반응형 웹을 구현할 수 있다. 즉 사용자가 어떤(크기의 디스플레이의)미디어를 사용하느냐에 따라 사이트의 형태가 바뀌게끔 CSS를 작성하는 것이 바로 `미디어 쿼리(media queries)`이다.

## @media 속성

미디어 쿼리는 @media 속성을 사용하여 어떤 미디어에서 어떤 CSS를 적용할 것인지 지정한다.

```css
@media only | not 미디어 유형 and 조건 * and 조건..
```

기본형이다.

- only : 미디어 쿼리 미지원 웹 브라우저에서는 미디어 쿼리 무시. 실행X
- not : not 다음에 지정하는 미디어 유형 제외하고 미디어 쿼리 적용
- and : 필요할 경우조건을 여러개 연결해서 추가할 수 있다.

> 미디어 유형이 screen이면서 최소너비 700px~최대너비 1400px일경우 적용할 CSS를 정의

```css
@media screen and (min-width: 700px) and (max-width : 1400px)
```


## 미디어 유형

- all : 모든 미디어 유형
- pront : 인쇄 장치
- screen : 컴퓨터 스크린, 스마트폰 스크린
- tv : 티비
- arual : 음성 합성 장치
- braille : 점자 표시 장치
- handheld : 패드류
- projection : 프로젝터
- tty : 디스플레이 기능이 제한된 장치 한정. px단위 사용 불가능
- embossed : 점자 프린터

## 웹 문서의 크기-뷰포트-를 미디어 쿼리의 조건으로 사용하기

실제 웹 문서 내용이 화면에 나타나는 영역이 바로 viewport인데, 이 viewport의 width와 height를 미디어 쿼리의 조건으로 사용할 수 있다. 위의 예제처럼, min-width나 max-width 를 조건으로 사용하는 것처럼 말이다.

```css
@media screen and (min-width: 700px) and (max-width : 1400px)
```

## 단말기의 크기를 미디어 쿼리의 조건으로 사용하기

단말기 device의 기본 물리적 width값과 height값을 체크해보자. 

```css
@media screen and (min-device-width: 300px) and (max-devide-width : 800px)
```

## 화면 회전 속성 : orientation

미디어 쿼리에서 orientation 속성을 사용하면 기기의 방향이 세로인지 가로인지 확인 가능하고, 이에 따라서 웹 사이트의 레이아웃을 바꿀 수 있다. 

- orientation : portrait - 세로 모드
- orientation : landscape - 가로 모드. 기본값

```css
@media screen and (min-device-width: 500px) and (orientation : landscape)
```

이 외에도 화면 비율, 색상당 비트 수 등 여러가지 미디어 쿼리 조건이 있다. W3 홈페이지 참고

## 미디어 쿼리의 중단점

화면 크기에 따라 서로 다른 CSS를 적용하는 것이 미디어 쿼리의 의의인데, 이 각각의 분기점이 바로 `중단점(break point)` 이다. 중단점을 어떻게 지정하느냐에 따라 정말 많은 것-예를 들면 레이아웃이나 CSS 효과가 보여지는 것 등-들이 다라지게 된다. 보통 기기의 화면 크기를 기준으로 하는데, 모든 기기를 표기할 수는 없으니 모바일/태블릿/데스크톱 정도만 써주면 준수하다.

그리고 처리 속도, 화면 크기 등등에서 다른 기기보다 모바일은 제약이 많은 편이므로 모바일의 레이아웃을 기본으로 하여 CSS를 만드는 것이 좋다. 그리고 이후 사양이 좀 더 좋고 화면도 좀 더 큰 태블릿, 데스크톱 등에 맞춰 더 많은 기능, 스타일을 추가하는 방식이 효율적이다. 이것이 바로 `모바일 퍼스트(mobile first)` 기법이다.

> 모바일 → 태블릿 → 데스크톱 으로 구분하여 중단점을 만드는 것이 일반적이다.

# 미디어 쿼리 적용하기

## 외부 CSS 파일로 연결하기

CSS 파일을 따로 떼서 작업한 후 웹 문서에 연결하는 방법. `link 태그`나 `@import 문`을 사용한다.

```html
<head>
    <link rel="stylesheet" media="tv" href="tv.css">
</head>
```

```html
<style>
    @import url("tablet.css") only screen and (mid-width: 300px) and (max-width: 500px);
</style>
```

둘 다 외부에서 CSS 파일을 가져와 사용하는 방법으로, 작업량이 적을 때에는 속도나 처리 면에서 큰 차이가 없지만 (인터넷 익스플로러에서, 자바스크립트와 @import문이 함께 있는 경우) 자바스크립트를 내려받은 후에야 @import문의 CSS를 다운로드 하기 때문에, 만약 JS파일에 style 관련 정보가 있다면 두 정보가 충돌할 수 있으므로 규모가 큰 사이트 개발에서는 link를 주로 사용한다.

## 웹 문서에 직접 정의하기

외부 CSS 파일을 따로 만들지 않고 웹 문서 html에서 미디어 쿼리를 직접 지정하는 방법이다.

```html
<style media="screen and (max-width: 320px)">
        h1 {
            background-color: aqua;
        }
</style>
```

```html
<style>
        @media screen and (max-width: 320px) {
            p {
                background-color: black;
            }
        }
</style>
```

## 예제 - 화면 크기에 따라 배경 이미지 바꾸기

```css
div {
    width: 500px;
    height: 500px;
    margin: 0 auto;
    background: url(cat1.jpg) no-repeat;
    background-size: contain;
}
@media screen and (max-width: 768px) {
    div {
        background: url(cat2.jpg) no-repeat;
        background-size: contain;
    }
}
@media screen and (max-width: 425px) {
    div {
        background: url(cat3.jpg) no-repeat;
        background-size: contain;
    }
}
@media screen and (max-width: 320px) {
    div {
        background: url(cat4.jpg) no-repeat;
        background-size: contain;
    }
}
```

```html
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>mediaqueries2</title>
    <link rel="stylesheet" href="mediaqueries2.css">
</head>
<body>
    <div></div>
</body>
</html>
```

![Honeycam 2022-03-23 12-27-51](https://user-images.githubusercontent.com/97890886/165882543-3244fe08-efda-464b-bfc0-bad0bb21e98c.gif)