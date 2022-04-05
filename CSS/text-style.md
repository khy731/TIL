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