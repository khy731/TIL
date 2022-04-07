# 목록 스타일

## 불릿 모양과 번호 스타일 지정

>list-style-type 속성

- disc : 빈 원
- circle : 채운 원
- square : 빈 상자
- deciaml : 10진수 (1~)
- deciaml-leading-zero : 10진수 (0~)
- lower-roman : 로마 숫자 소문자
- upper-roman : 로마 숫자 대문자
- lower-alpha | lower-latin : 알파벳 소문자
- upper-alpha | upper-latin : 알파벳 대문자
- none : 불릿, 숫자 제거

## 불릿 대신 이미지 사용

>list-style-image 속성

list-style-type 속성의 불릿의 종류가 단순하다면? 이미지로 바꿔보자. 물론 불릿 크기만큼 작아야 한다.

```css
/* list-style-image: url(이미지 파일 경로) | none */
list-style-image: url('images/myDot.png');
```

## 불릿 들여쓰기

>list-style-position 속성

- inside : 기본 위치보다 안쪽으로 들여 씁니다.
- outside : 기본값

```html
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <title>listStyle</title>
    <style>
        .liststyle1 {
            list-style-type: square;
            list-style-position: inside;
        }
        .liststyle2 {
            list-style-type: demical-leading-zero;
            list-style-position: outside;
        }
    </style>
</head>
<body>
    <h1>저녁에 무엇을 먹을까</h1>
    <ul class="liststyle1">
        <li>제육볶음</li>
        <li>버섯구이</li>
        <li>가지튀김</li>
    </ul>
    <ul class="liststyle2">
        <li>짜장</li>
        <li>짬뽕</li>
        <li>탕수육</li>
    </ul>
</body>
</html>
```

![10_liststyle](https://user-images.githubusercontent.com/97890886/162208399-610ee665-3e99-422a-a86f-c14a3ad8ec2d.png)


## 모든 목록 속성을 한꺼번에 표시

>list-style 속성

list-style-type, list-style-image, lise-style-position 을 한꺼번에 표시 가능

```css
        .liststyle1 {
            list-style: square inside;
        }
        .liststyle2 {
            list-style: demical-leading-zero outside;
        }
```

# 표 스타일

CSS를 이용하면 표의 크기뿐만 아니라 표의 테두리, 셀의 테두리, 여러 여백 조절 등으로 표 스타일을 지정할 수 있습니다.

## 표 제목의 위치 지정

> caption-side 속성

표 제목은 caption 태그로 캡션으로 표시하는데, 캡션은 표 위쪽에 표시되는 것이 기본값이다. 이때 caption-side 속성으로 표 아래쪽으로도 옮길 수 있다.

- top : 위쪽. 기본값
- bottom : 아래쪽

```css
caption-side: top | bottom
```

## 표에 테두리 그리기

>border 속성

표 바깥 테두리와 셀 테두리를 각각 지정한다.

## 셀 사이의 여백 지정 

> border-spacing 속성

표와 셀에 따로 테두리를 지정하면 셀과 셀 사이에 여백이 조금 생기게 된다. border-spacing 속성을 사용하면 셀과 셀 사이의 여백을 조절할 수 있다. 

```css
border-spacing: 수평거리 수직거리
```

## 표와 셀 테두리를 병합

>border-collapse 속성

border 속성을 표와 셀에 각각 사용하면 표 전체에 그어지는 테두리와 셀 각각에 그어지는 테두리 때문에 줄이 두 개가 된다. 이를 그냥 둘 것인지, 합쳐서 하나로 표시할 것인지 결정하는 속성이 바로 이것이다. table 태그의 스타일에만 지정하면 된다.

- collapse : 합쳐 하나로 표시
- separate : 따로 표시. 기본값.

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Document</title>
    <style>
        h1 {
            color: deeppink;
            text-shadow: 2px 2px black;
            text-decoration: underline;
            text-align: center;
            height: 100px;
            width: 100%;
            background: bisque;
            line-height: 100px;
        }
        caption {
            caption-side: bottom;
            font-style: italic;
        }
        table {
            border: 1px solid black;
            border-collapse: collapse;
        }
        td, th {
            border: 1px dotted black;
            padding: 10px;
            text-align: center;
        }
    </style>
</head>
<body>
    <h1>상품 구성</h1>
    <table>
        <caption>선물용과 가정용 상품 구성</caption>
        <thead>
            <tr>
                <th>용도</th>
                <th>중량</th>
                <th>개수</th>
                <th>가격</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td rowspan="2">선물용</td>
                <td>3kg</td>
                <td>11~16과</td>
                <td>35000원</td>
            </tr>
            <tr>
                <td>5kg</td>
                <td>18과</td>
                <td>50000원</td>
            </tr>
            <tr>
                <td rowspan="2">가정용</td>
                <td>3kg</td>
                <td>11~16과</td>
                <td>35000원</td>
            </tr>
            <tr>
                <td>5kg</td>
                <td>18과</td>
                <td>50000원</td>
            </tr>
        </tbody>
        </table>
    </table>
</body>
</html>
```

![11_표style](https://user-images.githubusercontent.com/97890886/162208730-9838d01b-dbba-4df9-85bd-937c2bb9ab05.png)
