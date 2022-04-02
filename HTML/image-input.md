# 이미지 삽입하기

> 웹에서 사용하는 대표적인 이미지 파일 형식

웹에서 사용하는 이미지는 인터넷으로 전송해야 하므로 파일 크기가 크지 않으면서 화질이 좋아야 함 → JPG, JPEG, PNG등을 주로 사용한다. 아이콘이나 작은 로고 이미지일때는 GIF를 사용하기도 한다.

- GIF - 표시가능한 색상수 최대 256가지. 다른 이미지 파일에 비해 크기가 작음
- JPG/JPEG - GIF보다 다양하게 색상/명암 표현가능. 퍼나르다 보면 화질 저하됨.
- PNG - 네트워크용 파일형식. 다양한 색상/명암 + 투명배경 표현가능. 범용성이 좋다

# img 태그

웹 문서에 이미지를 삽입할 때 가장 기본인 태그.

```html
<img src="Kang.jpg" alt="강혜윤">
<h3>강혜윤</h3>
```

## src 속성 - 이미지 파일의 경로

`이미지 파일의 경로`를 지정하여 웹 브라우저에게 알려 준다.
> “이곳에 있는 이미지를 쓸 거야!”

이미지 파일의 경로는 웹 문서 파일의 위치를 기준으로 정해지기 때문에, 웹 문서 파일과 이미지 파일이 같은 경로에 있다면 src 속성에는 간단하게 이미지 파일의 이름만 적으면 된다.

## alt 속성 - 대체용 텍스트

`이미지를 대체할 텍스트`를 입력한다.
> “화면 낭독기 등에서 이미지 대신 표시될 거야!”

또한 alt속성을 지정하면 인터넷이 불안정하거나/이미지 파일 경로를 잘못 넣었을 때, 즉 불가피한 상황으로 이미지가 표시되지 않을 때에도 이미지의 내용을 추측할 수 있다.

## width, height 속성 - 이미지 크기 조절

- width - 너비(가로)
- height - 높이(세로)

img 태그로 이미지 파일을 삽입하면 원본 크기 그대로 표시가 된다. 만약 이미지 파일을 수정하지 않고, 웹 브라우저 창에서 보이는 이미지의 크기만 조절하고 싶다면 이 두 속성을 이용하면 된다. 둘 다 사용해도 되고, 둘 중 하나만 선택해서 사용해도 된다. 하나만 지정해줘도 나머지는 비율이 자동으로 계산되어 나타난다. 가능한 단위는 %와 px.

- % - 현재 웹 브라우저 창의 너비, 높이를 기준으로 이미지 크기를 결정
→ width를 100%로 하면 웹 브라우저 창 너비에 딱 맞출 수 있다

- px(픽셀) - 이미지의 크기(너비, 높이)를 해당 픽셀 크기만큼 표시

```html
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <title>이미지 크기 조절</title>
</head>
<body>
    <h4>원래 크기의 이미지</h4>
    <img src="cat.jpg" alt="고양이">
    <h4>width="50%", height="50%"로 지정한 이미지</h4>
    <img src="cat.jpg" alt="고양이" width="50%">
    <h4>width="150"(픽셀)로 지정한 이미지</h4>
    <img src="cat.jpg" alt="고양이" width="150">
</body>
</html>
```

![3_이미지삽입1](https://user-images.githubusercontent.com/97890886/161385316-dbc85d8b-f2cc-4397-ba19-63f30254d62d.png)

![3_이미지삽입2](https://user-images.githubusercontent.com/97890886/161385345-f8459f67-e44e-4e7b-babb-52d20f45d763.png)

# 오디오/비디오 삽입하기

## object 태그

오디오 파일뿐만 아니라 비디오, 자바 애플릿, PDF 등 다양한 멀티미디어 파일을 삽입할 때 사용한다. 웹 문서 안의 문서-다른 문서를 삽입하기-에도 사용 가능하다.

```html
<object width="너비" height="높이" data="파일"> </object>
```


## embed 태그

HTML 초기 버전부터 사용해온 태그이기 때문에 대부분의 브라우저에서 사용할 수 있다. src 속성으로 삽입할 멀티미디어 파일을 지정하고, 필요할 경우 width, height 속서으로 플레이어의 너비와 높이를 제어한다. 닫는 태그가 없다.

```html
<embed src="파일 경로" width="너비" height="높이">
```


> 웹 브라우저에서 지원하는 멀티미디어 파일

- 비디오
    - mp4
    - webm

- 오디오
    - mp3
    - m4a, mp4


## audio, video 태그

사용법/속성이 전부 비슷하므로 한꺼번에 배워도 무방하다.

```html
<audio src="오디오 파일 경로"></audio>
<vedio src="오디오 파일 경로"></vedio>
```

> 속성

- controls : 방문자가 미디어를 재생하거나 멈출 수 있도록 컨트롤 바를 나타내는 속성. width 속성을 함께 사용해 너빗값도 지정이 가능하다.
- autoplay : 자동 실행
- loop : 반복 재생
- muted : 소리 제거
- preload : 페이지를 불러올 때 미디어 파일을 어떻게 로딩할 것인지 지정하는 파일. auto/metadata/none 등의 값이 있다. 기본값은 preload=”auto”
- width, height : 플레이어의 너비, 높이 지정.
- poster : video 태그에서만 사용. 비디오가 재생되기 전까지 화면에 표시될 포스터 이미지를 지정한다. 기본 형식은 poster=”파일명”

# 하이퍼링크 삽입하기

## a 태그와 herf 속성

웹 사이트에서 `링크`의 기능은 정말 많이 사용되고, 그만큼 중요하다. 링크는 a 태그와 herf 속성으로 만들 수 있으며, 이때 텍스트를 사용하면 텍스트 링크가 되고, 이미지를 사용하면 이미지 링크가 된다.

```html
<a href="링크할 주소">텍스트 or 이미지</a>
```

## 텍스트 링크 만들기

- a와 /a 태그 사이에 링크로 만들 텍스트를 입력
- herf 속성에 ‘텍스트를 클릭 할 시 연결(link)될 문서의 경로, 파일명’ 입력

## 이미지 링크 만들기

- a와 /a 태그 사이에 링크로 만들 img 태그를 입력
- herf 속성에 ‘이미지를 클릭 할 시 연결(link)될 문서의 경로, 파일명’ 입력

## target 속성 - 링크를 새 탭에서 열기

현재 열려있는 기존 웹 페이지에서 새로운 문서로 넘어가는 것이 아니라(이 경우 뒤로가기를 해야 하므로 경우에 따라 불편함을 느낄수도 있음) target 속성에 _blank를 지정하면 새 탭에서 문서가 열린다.

```html
...

<div>
    <p><a href=".../Kang/web.html" target="blank">웹 열기</a></p>
</div>

...
```

# 마무리 예제(1)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>수습 국원 모집 사이트</title>
</head>
<body>
    <h1>수습 국원 모집</h1>
    <h2>방송에 관심 있는 새내기 여러분 환영합니다</h2>
    <p>교내 방송국에서 신입생을 대상으로 수습 국원을 모집합니다. 학부와 전공은 상관없습니다.<br>방송에 관심 있는 여러 학우의 지원 바랍니다.</p>
    <ul>
        <li><b>모집 기간 : </b>3월 2일 ~ 3월 11일</li>
        <li><b>모집 분야 : </b>아나운서, PD, 엔지니어</li>
        <li><b>지원 방식 : </b>양식 작성 후 이메일 접수<br><i>지원서 양식은 교내 방송국 홈페이지 공지 게시판에 있습니다.</i></li>
    </ul>
    <h3>혜택</h3>
    <ol type="a">
        <li>수습기자 활동 중 소정의 활동비 지급</li>
        <li>정기자로 진급하면 장학금 지급</li>
    </ol>
    <img src="cat.jpg" alt="고양이" width="40%">
</body>
</html>
```

![4_마무리예제(1)](https://user-images.githubusercontent.com/97890886/161385455-79301e0d-1553-4abf-838b-843cd25d1c65.png)

# 마무리 예제(2)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>수습 국원 지원 양식</title>
    <style>
        table, td, th {
          border:1px solid #ccc;
        }
        td, th {
          padding:10px 20px;
        }
        td:last-child{
          width:200px;
        }
      </style>
</head>
<body>
    <h1>수습 국원 지원 양식</h1>
    <table>
        <tr>
            <th rowspan="3">개인정보</th>
            <th>이름</th>
            <td></td>
        </tr>
        <tr>
            <th>학과/학번</th>
            <td></td>
        </tr>
        <tr>
            <th>연락처</th>
            <td></td>
        </tr>
        <tr>
            <th>지원 분야</th>
            <td colspan="2"></td>
        </tr>
    </table>
</body>
</html>
```

![4_마무리예제(2)](https://user-images.githubusercontent.com/97890886/161385468-df26cce5-35aa-4741-8e39-3eb50c29b65b.png)

- 잘한 점: 합친 셀 만큼 이후 셀 생략해서 쓴 것
- 개선할 점:
   - 크기로 어림짐작하지 말고 “몇 행 몇 열” 인지를 확실하게 정하고 틀을 짜고 계산하기
  - td 가 아니라 tb로 썼음...