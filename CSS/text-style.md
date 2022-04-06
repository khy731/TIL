# 글꼴과 관련된 다양한 스타일

# 글꼴

> font-family 속성

```css
body {font-family: "D2Coding", 돋움, 굴림}
```

웹 문서의 텍스트는 사용자 시스템의 글꼴을 이용해 웹 브라우저 화면에 표시되는데, 지정한 글꼴이 설치되어 있지 않다면 글자가 깨지기 때문에 웹 문서에서 글꼴을 지정할 때에는 여분 글꼴도 넣어줘야 한다.

> TIP : 기본형 기호 - W3C 표준 규약

```css
font-size: 값1 | 값2 | 값3
```

나열한 옵션 中 하나가 값이 되어야 한다는 뜻. (OR 기호)

```css
font-variant: narmal | small-caps
```

키워드는 값1, 값2 처럼 추상화하지 않고 있는 그대로 나열한다. (font-variant 속성은 narmal이나 small-caps라는 값만 사용한다) 

```css
font-size: <절대 크기> | <상대 크기> | <크기> | <백분율>
```

속성값 나열 시, 값이 아닌 유형이라면 <>로 묶는다.

```css
font: <font-style><font-variant><font-weight>
```

같은 <>지만 이쪽은 위와 같은 예시처럼 추상화되지 않고 있는 그대로 나열되어 있다→ 나열 값 자체를 속성값으로 사용한다. 유형x

# 글자 크기

> font-size 속성

단위는 px(픽셀), pt(포인트), %(백분율)

```css
font-size: <절대 크기> | <상대 크기> | <크기> | <백분율>
```

1. 절대 크기: 브라우저에서 지정한 글자 크기
2. 상대 크기: 부모 요소의 글자 크기를 기준으로 상대적인 글자 크기를 지정
3. 크기: 브라우저와 상관없이 글자 크기를 직접 지정
4. 백분율: 부모 요소의 글자 크기를 기준으로 백분율로 표시

## 키워드 사용

xx-small < x-small < small < medium < large < x-large < xx-large

## 단위 사용

- em : 부모 요소에서 지정한 글꼴의 대문자 M의 너비를 기준(1em)으로 비율값 지정
- rem : 문서 시작 부분(root)에서 지정한 크기를 기준(1rem)으로 비율값 지정
- ex : 해당 글꼴의 소문자 x의 높이를 기준(1ex)으로 비율값 지정
- px : 모니터의 1픽셀을 기준(1px)으로 비율값 지정
- pt : 한글,워드에서 나오는 그 포인트. 일반 문서에서 많이 사용

## 백분율 사용

부모 요소의 글자 크기를 기준으로 계산하여 지정. 단, 부모 요소의 글자 크기가 단위로 표시되어 있어야 사용 가능.

# 이탤릭체

> font-style 속성

```css
font-style: normal | italic | oblique
```

1. normal : 기본값. 일반적인 형태로 표시
2. italic : 이탤릭체. 웹에선 주로 이쪽을 쓴다
3. oblique : 이탤릭체.

# 글자 굵기 지정

> font-weight 속성

```css
font-wheight : normal | bold | bolder | lighter | 100 | 200 | ... | 800 | 900
```

1. normal : 기본값. 보통 굵기
2. bold : 굵게
3. bolder : 더 굵게
4. lighter : 얇게
5. 100~900 : 말 그대로 숫자만큼의 굵기 표현. 100(가장 가늘게)~900(가장 굵게)

# 웹 폰트

웹 문서의 텍스트는 사용자 시스템에 설치된 글꼴을 사용해 화면에 표시된다. 그런데 내가 표시하고 싶은 폰트가 모든 사용자의 시스템에 설치되어 있지는 않을 것이다. 이처럼 사용자 시스템에 없는 글꼴을 그대로 동일하게 보여주려면 `웹 폰트`를 이용하면 된다.

> 웹 폰트 사용하기

- 웹 문서를 서버에 업로드할 때 웹 폰트 파일도 함께 업로드하여 사용자가 사이트에 접속하면서 웹 문서 뿐만 아니라 웹 폰트도 다운로드 할 수 있게 한다.
- 보통은 링크를 통해 웹 폰트를 사용하며, TTF는 파일 크기가 커서 웹에서 사용하기엔 부적합하므로 추가 과정이 필요하다.

## TTF 사용하기

1. font-family 속성으로 글꼴 이름 생성
2. local()문으로 사용자 시스템에 해당 글꼴이 있는지 확인할 것
- 있다면 → src 속성으로 사용할 글꼴 파일 경로 명시
- 없다면 → WOFF 포맷으로 된 글꼴 다운로드
1. 포맷 : TTF는 용량이 크기 때문에 WOFF 포맷을 먼저 선언 → 이후 TTF 포맷 선언

```css
<!DOCTYPE html>
<html lang="en">
<head>
    <style>
        @font-face {
            font-family: 'D2Coding';
            src: local('D2coding') 
            url('fonts/D2Coding.woff') format('woff'),
            url('fonts/D2coding.ttf') format('truetype'),
            url('fonts/D2coding.svg') format('svg');
        }
        .wfont {
            font-family: 'D2coding', sans-serif;
        }
        p {
            font-size: 30px;
        }
    </style>
</head>
<body>
    <p>Using Default Fonts</p>
    <p class="wfont">Using web Fonts</p>
</body>
</html>
```

## 구글 폰트 사용하기

```css
/* 구글에서 통째로 긁어온 부분 */
<style>
    @import url('~~~~~')
</style>

/* 이후 구글에서 통째로 긁어온 부분2 를 선택자에 적절하게 사용 */
h1 {
    font-family: 'font1', cursive;
}
```

# 글자 색 지정

> color 속성

color에서 사용할 수 있는 속성값은 16진수와 rgb(또는 rgba), hsl(또는 hsla) 등이 있다.

1. 16진수 : 6자리의 16진수로 RGB의 비율을 표시. 

       ex) #RRGGBB → #ffff00

2. hsl (hue색상 saturation채도 lightness명도 + alpha불투명도) : 원 모양 색상환을 기준으로 각각의 요소를 표시

       ex) hsla(0,100%, 50%, 0.5) → 절반쯤 투명해진 빨간색 

3. 영문명 : white, black 등

4. rgb로 표시 : 0~255까지 각각 R,G,B가 들어 있는 양 만큼의 값 표시. CSS에서 주로 사용됨.

    ```css
    h1 { color : rgb(0,0,255); }
    ```

## TIP: **text-align 속성**

`text-align` 속성은 텍스트의 정렬 방향을 의미한다.

- `left`: 왼쪽 정렬
- `right`: 오른쪽 정렬
- `center`: 중앙 정렬
- `justify`: 양쪽 정렬 (자동 줄바꿈시 오른쪽 경계선 부분 정리)

# 줄 간격 조절

> line-height 속성
>

```css
p {
            font-size: 12px; line-height: 24px;
        }
p {
            font-size: 12px; line-height: 2.0;
        }
p {
            font-size: 12px; line-height: 200%;
        }
```

1. 정확한 단위로 크깃값을 지정

글자 크기는 12px, 줄 간격은 24px (==글자 크기의 2배)

2. 문단의 글자 크기를 기준으로 몇 배수인지 실수, 백분율로 지정

글자 크기는 12px, 줄 간격은 글자 크기의 2.0배 / 글자 크기의 200% (== 24px)

> 제목의 세로 정렬에 유용

제목에 사용할 스타일 시트를 작성하면서 .heading이라는 클래스를 만들고, 그 내에 있는 제목 영역의 높이 height 속성을 100px로 했을 때 line-height 속성도 100px로 해주면 편안하게 중앙정렬된다.

```html
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <title>HMTL</title>
    <style>
        .heading {
            height: 100px;
            width: 100%;
            background: chartreuse;
            color: deeppink;
            text-align: center;
            line-height: 100px;
        }
    </style>
</head>
<body>
    <h1 class="heading">HTML</h1>
</body>
</html>
```

![7_font_height2](https://user-images.githubusercontent.com/97890886/161969997-c33a160b-b8f5-46db-8fc8-01057471be9d.png)

line-height 속성을 사용하지 않았을 때


![7_font_height3](https://user-images.githubusercontent.com/97890886/161970042-84008bcd-0a64-485d-9939-8d7100c41dc2.png)


line-height 속성을 사용했을 때

# 텍스트 밑줄, 윗줄, 취소선

>text-decoration 속성

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <title>text-decoration</title>
</head>
<body>
    <h1>text-decoration 속성</h1>
    <p style="text-decoration: none;">none</p>
    <p style="text-decoration: underline;">underline</p>
    <p style="text-decoration: overline;">overline</p>
    <p style="text-decoration: line-through;">line-through</p>

    <p style="text-decoration: solid;">solid</p>
    <p style="text-decoration: dashed;">dashed</p>
    <p style="text-decoration: dotted;">dotted</p>
    <p style="text-decoration: blueviolet;">color</p>
</body>
</html>
```

- none : 텍스트에 줄을 표시하지 않음 (하이퍼링크 같은 기본으로 줄이 생기는 요소에 사용하면 좋다)
- underline : 밑줄
- overline : 윗줄
- line-through : 취소선


![8_text-decoraition](https://user-images.githubusercontent.com/97890886/161970094-3a4321ca-50de-4eb8-879c-02b953fc54e8.png)


## 텍스트에 그림자 효과 추가

>text-shadow 속성

```css
text-shadow: none | <가로 거리> <세로 거리> <번짐 정도> <색상>
```

- 가로 거리 : 필수 속성.

    - 양숫값 :오른쪽에 그림자를 만든다.

    - 음숫값 - 왼쪽에 그림자를 만든다.

- 세로 거리 : 필수 속성.

    - 양숫값 : 아래쪽에 그림자를 만든다.

    - 음숫값 : 위쪽에 그림자를 만든다.

- 번짐 정도 : 그림자가 번지는 정도. 기본값==0

    - 양숫값 : 그림자가 모든 방향으로 퍼져 나가므로 그림자가 크게 표시됨

    - 음숫값 : 그림자가 모든 방향으로 축소되어 보임

- 색상 : 그림자 색상 지정. 한 가지만 지정할 수 있고, 공백으로 구분하여 여러 색상을 지정할 수도 있음. 기본값==현재 글자의 색

```css
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <title>text-shadow</title>
    <style>
        .shadow1 {
            color: red;
            text-shadow: 2px 2px black;
        }
        .shadow2 {
            color: black;
            text-shadow: 4px 4px 3px rgb(192, 148, 4) ;
        }
        .shadow3 {
            color: rgb(99, 147, 189);
            text-shadow: 7px -7px 20px violet;
        }
    </style>
</head>
<body>
    <h1 class="shadow1">HTML</h1>
    <h1 class="shadow2">CSS</h1>
    <h1 class="shadow3">javascript</h1>
</body>
</html>
```


![9_textShadow](https://user-images.githubusercontent.com/97890886/161970179-b0b71854-1519-4d66-bb88-984a044f915d.png)

# 텍스트의 대소문자 변환

> text-transform 속성

- none : 줄을 표시하지 않음
- capitalize : 첫 번째 글자를 대문자로 변환
- uppercase : 모든 글자를 대문자로 변환
- lowercase : 모든 글자를 소문자로 변환
- full-width : 가능한 모든 문자를 전각 문자(가로세로 비율 1:1로 같은 문자. 1:2와 같은 늘씬한 글씨는 반각문자이다.)로 변환

# 글자 간격 조절

> letter-spacing, word-spacing 속성

글자와 글자 사이의 간격을 조절한다. word-spacing 속성은 단어와 단어 사이의 간격을 조절하는데,  CSS 에서는 letter-spacing을 주로 사용하여 자간(글자와 글자 사이의 간격. 글꼴이나 글자의 크기 등에 상관없이 정적인 개념이다)을 조절한다. px,em같은 단위나 %로 크깃값을 조절한다.