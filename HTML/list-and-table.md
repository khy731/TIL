# 목록 만들기

웹 문서에서 목록이란 단순히 어떤 항목을 나열하는 용도뿐만 아니라, CSS와 함께 사용하여 내비게이션을 만들거나 컨텐츠를 배치하는 등의 다양한 용도로 사용됩니다. 목록을 자유자재로 활용하여 봅시다.

## 순서 있는 목록

ordered list. 말 그대로 각 항목을 순서대로 나열한 것.  목록을 표시할 내용 앞뒤에 ol을 두고, 그 사이에 li를 삽입한다.

```html
<ol>
    <li>항목1</li>
    <li>항목2</li>
</ol>
```

자동으로 숫자 리스트가 함께 삽입되어 나온다.

### <ol> 태그의 속성 - type, start

type 속성을 사용하면 숫자 번호의 타입을 영문자, 로마숫자 등으로 바꿀 수 있다.
start 속성을 사용해서 시작 번호의 위치를 바꿀 수도 있다(원하는 번호부터 시작하는 경우 유용)

```html
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <title>국물닭발 레시피</title>
    <abbr title="국물닭발">존맛닭발</abbr>
</head>
<body>
    <h2>국물닭발 레시피</h2>
    <p><b>재료</b>: 토종닭,고추장,간장,소금</p>
    <p><b>술</b>: 맥주,소주,매화주</p>
    <h4>기본 조리</h4>
    <ol type = "a">
        <li>토종닭을 손질한다</li>
        <li>고추장,간장,소금으로 소스를 만든다</li>
        <li>잘 섞어서 요리한다</li>
    </ol>
    <h4>먹을 준비</h4>
    <ol type = "a" start = "4">
        <li>술을 깐다</li>
        <li>같이 맛있게 먹는다</li>
</body>
</html>
```

![1_목록만들기](https://user-images.githubusercontent.com/97890886/161257960-98d03a7d-bfed-41db-8439-34f4b2bfa5cc.png)



## 순서 없는 목록

unordered list. 항목의 순서가 중요하지 않을 때 사용한다. ul로 틀을 짜고 그 안에 li로 내용을 입력한다. 기본적으로 작은 원, 사각형으로 구분하는데 이러한 그림을 불릿bullet이라고 한다.

## 설명 목록

description list. 이름name과 값value 형태로 된 목록. 사전에서 단어명과 설명이 있는 모습을 떠올리면 될 듯. 

dl 로 틀을 짜고, 그 안에 dt로 name을, dd로 value를 넣어준다.

웹 문서에서 양이 많은 목록 형식의 컨텐츠를 넣을 때, 다른 태그들로 복잡하게 만드는 것 보다 설명 목록을 이용하면 만들기도 쉽고 보기도 좋을 것이다.

# 표 만들기


## 표의 구성

![2_표의구조](https://user-images.githubusercontent.com/97890886/161258418-0e9fa74a-2502-494b-9c67-942f5481a6cf.png)

## 표 만들기

- table : 표의 시작과 끝을 알려주는 태그. 즉 표의 뼈대/틀
- caption : 표에 제목 붙이기. <table>태그 바로 아랫줄에 사용하면 표의 위쪽 중앙에 표시된다.

## 행과 셀 만들기

table 태그는 말 그대로 표의 뼈대일 뿐, 이 태그만으로는 표가 만들어지지 않는다. <table>태그 안에 행이 몇 개인지, 각 행에 셀이 몇 개인지(==열의 역할을 하는거나 다름없음) 지정해야 한다.

- tr : 행을 지정
- td : 행 안에 있는 셀을 지정
- th :행 안에 있는 셀을 지정(볼드체, 중앙배열) : 주로 표의 제목 행에 사용

## 표의 구조 지정하기

표의 구조를 지정하면 CSS를 사용하여 표의 제목,본문,요약에 각각 다른 스타일을 적용할 수 있다. 표의 본문이 길어 한 화면을 넘어갈 경우, 자바스크립트를 사용하여 특정 부분만 스크롤하게 만들 수 있다.

표의 구조는 웹 브라우저 화면에서 보이지는 않지만, 자바스크립트나 화면 낭독기 등에서 읽어낼 수 있다.

## 행/열 합치기

여러 셀을 합치거나 나누어서 다양한 형태를 구현할 수 있다. 행/열을 합치는 작업==결국 셀을 합치는 작업 이므로 th,td태그에서 이루어진다.

```html
<td rowspan="합칠 셀의 개수">셀의 내용</td>
<td colspan="합칠 셀의 개수">셀의 내용</td>
```

![2_표셀합치기](https://user-images.githubusercontent.com/97890886/161258490-c9d590d1-5400-4235-a258-8a530b829534.png)


시작점 태그에 코드를 써 줬으면, 합칠 만큼의 셀은 패스한다. 여러 셀에 한 내용이 공통으로 구현되게 하기 위함이다. 만약 서로 다른 내용이 있는 셀들을 합쳤을 경우 합쳐진 하나의 셀에 모든 내용이 표시되게 된다.

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>과일 구매 사이트</title>
</head>
<body>
    <h2>상품 구성</h2>
    <table>
        <caption>상품 구성</caption>
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
            <td>5~10개</td>
            <td>10000원</td>
        </tr>
        <tr>
            <td>1kg</td>
            <td>7개</td>
            <td>5000원</td>
        </tr>
        <tr>
            <td rowspan="2">가정용</td>
            <td>0.5kg</td>
            <td>1개</td>
            <td>1000원</td>
        </tr>
        <tr>
            <td>5kg</td>
            <td>5개</td>
            <td>8000원</td>
        </tr>
        </tbody>
    </table>
</body>
</html>
```

![2_표만들기](https://user-images.githubusercontent.com/97890886/161258720-081106fc-01ab-4ea0-a1b8-8645772b0793.png)



## 열을 묶어 지정하기

단순히 표를 만들기만 하는 것이 아니라, 특정 열에 배경색을 넣거나 너비를 바꾸는 등이 작업을 하고 싶다면 원하는 만큼의 열을 선택할 수 있어야 한다.

- col : 열 1개 지정
- colgroup : 열 2개 이상 지정

```html
<colgroup>
<col>
<col>
<col>
</colgroup>
```

이 두 태그는 반드시 caption 태그 다음에 바로 사용해야 한다. 표의 내용이 시작되기 전에 열의 상태를 알려주기 위함이다. 또한  col 태그를 사용할 때에는 colgroup 태그 안에 포함시키는 식으로, 모든 열을 하나하나 지정해주면서 사용해야 한다. 스타일 속성을 지정해주지 않을 열은 그냥 col 로 기본값을 명시해주면 된다. 만약 연속해서 같은 스타일 속성을 가진 열이 있다면 span으로 묶어주면 된다.

```html
...

<table>
        <caption>상품 구성</caption>
        <colgroup>
            <col style="background-color:darkgray">
            <col>
            <col span="2" style="width: 100px;">
        </colgroup>

...
```

- 첫 번째 열 색 지정: 다크그레이
- 두 번째 열 생략
- 세 번째~네 번째 열 너비 지정: 100픽셀

![2_표만들기_2](https://user-images.githubusercontent.com/97890886/161258887-23d067e1-46df-4a61-b777-b780f8fe4e21.png)
