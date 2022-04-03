# 입력 양식 작성하기

입력 양식이란 특정 항목에 사용자가 뭔가를 입력할 수 있게 만든 것으로, `폼` 이라고도 한다. 정보를 얻는 데에는 이러한 입력 양식이 효과적이다.

# form 태그

폼을 만드는 가장 기본적인 태그

```html
<form 속성="속성값">폼 요소들</form>
```

몇 가지 속성을 사용해서 입력받은 자료를 `어떤 방식`으로 넘길 것인지, 그리고 서버에서는 이 정보를 `어떤 프로그램`을 이용해 처리할 것인지를 지정

## 속성

> method

사용자가 입력한 내용을 서버 쪽 프로그램으로 어떻게 넘겨줄 것인지를 지정

- get : 256 ~ 4,096 byte 데이터만 서버로 전송 가능. 주소 표시줄에 사용자가 입력한 내용이 그대로 드러나는 단점이 있음.
- post : 입력한 내용의 길이에 제한받지 않고, 사용자가 입력한 내용도 드러나지 않음.

> name

폼의 이름을 지정

> action

서버 프로그램을 지정

> target

action 속성에서 지정한 스크립트 파일을 현재 창이 아닌 다른 위치에서 열도록 지정

```html
<form action="register.java">
    /* 여러 폼 요소들 */
</form>
```

> autocomplete

자동 완성 기능. 폼에서 내용을 입력할 때, 이전에 입력한 내용을 자동으로 표시해 주는 기능. 기본값은 on이나, 보안을 위해서 off로 해 놓는 경우도 있다.

```html
<form action="" autocomplete="off">
    /* 여러 폼 요소들 */
</form>
```

# filedset, legend 태그

## filedset

하나의 폼 안에서 여러 구역을 나누어 표시 할 때 사용하는 태그

## legend

fileset 태그로 묶은 그룹에 제목을 붙여줄 수 있음

```html
<form action="">
        <fieldset>
            <legend>상품 정보</legend>
        </fieldset>
        <fieldset>
            <legend>배송 정보</legend>
        </fieldset>
```

# <label> 태그

폼 요소(실질적으로 입력을 받는, input 태그와 같은 것)에 레이블을 붙일 때 사용. 입력란 아주 가까이에 ID, PW 같이 붙여놓은 텍스트가 `레이블(lable)`이다. 폼 요소와 레이블 요소가 연결되었다는 것을 웹 브라우저에게 알려주기 위해 필요한 태그.

> 사용 방법

1. lable 태그 안에 폼 요소 넣기

```html
<lable>아이디(6자 이상)<input type="text"></label>
```

2. label 태그와 폼 요소 따로(for, id 속성 사용)   
   
폼 요소의 id 속성값을 <label> 태그의 for 속성에게 알려 주는 방법이다.

```html
<label for="user_id">아이디(6자 이상)</label>
<input type="text" id="user_id">
```

label 태그를 사용한 ‘레이블’ 과 사용자 정보를 입력받는 input이 떨어져 있더라도, 둘을 쉽게 연결할 수 있다는 장점이 있다.

# input 태그

사용자 입력을 위한 태그이다.

## text

한 줄 짜리 텍스트를 입력할 수 있는 텍스트 박스

## password

비밀번호를 입력할 수 있는 필드. 입력하는 내용을 화면에 보여주지 않는 점을 제외하고는(* 등으로 처리됨)텍스트 필드와 동일하게 동작

```html
<input type="text">
<input type="password">
```

> text, password 필드에서 사용하는 주 속성

- size : 필드의 길이(화면에 몇 글자가 보이도록 할 것인지)를 지정
- value : 필드 요소가 화면에 표시될 때 필드 부분에 직접적으로 보여지는 내용. password 필드에서는 사용하지 않는 속성이다.
- maxlength : 필드에 입력할 수 있는 최대 문자 수를 지정

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>간단한 로그인 폼</title>
</head>
<body>
    <form>
        <fieldset>
            <legend>아이디와 비밀번호 입력</legend>
            <label>ID: <input type="text" id="user_id" size="10" maxlength="10"></label>
            <label>PW: <input type="password" id="user_pw" size="10" maxlength="10"></label>
            <input type="submit" value="log-in">
        </fieldset>
</body>
</html>
```

![5_폼](https://user-images.githubusercontent.com/97890886/161420738-afbf2248-91a6-4341-8c71-ddfd3b979a0a.png)


## search: 검색

웹 브라우저 화면에서는 text 필드와 다를 게 없지만, 서버에서는 `검색을 위한 text 필드`로 인식한다.

## url: 웹 주소

웹 주소를 입력하는 필드

## email: 이메일

이메일 주소를 입력하는 필드

## del: 전화번호

전화번호를 나타내는 필드. 지역마다 형식이 다르므로 사용자가 입력한 값이 전화번호인지 아닌지를 바로 알 수는 없다.


```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>주문 - 배송</title>
</head>
<body>
    <form>
        <fieldset>
            <legend>배송 정보</legend>
            <ul>
                <li>
                    <label for="userName"><b>이름</b></label>
                    <input type="text" id="userName" size="3" maxlength="3">
                </li>
                <li>
                    <label for="userAdd"><b>주소</b></label>
                    <input type="text" id="userAdd">
                </li>
                <li>
                    <label for="userCall"><b>전화번호</b></label>
                    <input type="del" id="userCall">
                </li>
                <li>
                    <label for="userMail"><b>이메일</b></label>
                    <input type="email" id="userMail">
                </li>
            </ul>
            <input type="submit" value="확인">
        </fieldset>
    </form>
</body>
</html>
```


![5_폼2](https://user-images.githubusercontent.com/97890886/161420839-18f562b3-51fc-440f-8ca6-19e1e72f5944.png)

> 다음과 같은 text 필드에서 세분화된 필드들은 PC용 웹 브라우저에서는 큰 차이를 느끼지 못할수도 있지만, 모바일 기기에서는 필드에 따라 가상 키보드 배열이 바뀌는 것을 볼 수 있다.

## checkbox, radio : 체크 박스와 라디오 버튼

여러 항목 중에서 원하는 `항목을 선택`할 때 사용하는 폼 요소

- 1개만 선택하게 할 경우 → radio
- 2개 이상 선택하게 할 경우 → checkbox


```html
<input type="checkbox">
<input type="radio">
```

> checkbox와 radio에서 사용할 수 있는 속성

- value - 선택한 값을 서버에게 알려줄 때, 넘겨줄 값을 지정. 영문/숫자여야 하며 필수 속성이므로 생략 불가능.
- checked - 처음에 기본으로 선택해 놓고 싶은 값이 있다면 지정할 수 있다. 기본값은 당연히 아무것도 없는 상태.

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>주문하기</title>
</head>
<body>
    <form>
        <fieldset>
            <legend>상품 선택</legend>
            <p><b>주문할 상품을 선택하세요.</b></p>
            <label><input type="checkbox" value="p_3">선물용 3kg</label>
            <label><input type="checkbox" value="p_5">선물용 5kg</label>
            <label><input type="checkbox" value="f_3">가정용 3kg</label>
            <label><input type="checkbox" value="f_5">가정용 5kg</label>
            <p><b>포장 여부 선택</b></p>
            <label><input type="radio" name="gift" value="yes">포장 함</label>
            <label><input type="radio" name="gift" value="no">포장 안 함</label>
        </fieldset>
    </form>
</body>
</html>
```

![5_폼3](https://user-images.githubusercontent.com/97890886/161420916-df732ac9-9c1f-4540-bffb-bc7b012f1669.png)


## number, range: 숫자 입력 필드

### number

스핀 박스로 숫자를 선택하게 할 수 있다.

> range

range 속성을 사용하면 슬라이드 막대를 움직여 숫자를 입력할 수 있다.

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>상품 구매 세부사항</title>
</head>
<body>
    <form>
        <ul>
            <li>
                <label><input type="checkbox" value="p">선물용</label>
                <input type="number" min="0" max="5" value="1">
            </li>
            <li>
                <label><input type="checkbox" value="h">가정용</label>
                <input type="number" min="0" max="5" value="1">
            </li>
        </ul>
    </form>
</body>
</html>
```

> number
> 
![5_폼5](https://user-images.githubusercontent.com/97890886/161420983-b4efa35a-099b-4d64-bebb-1fba60675b17.png)


> range

![5_폼6](https://user-images.githubusercontent.com/97890886/161420999-3a0212de-409e-41cf-8daf-f1c28fcbcd36.png)


## date, month, week : 날짜 입력 필드

- date : yyyy-mm-dd
- month : yyyy-mm 
- week : 1월 첫 번째 주를 기준으로 몇 번째 주인지 표시

```html
<input type="date|month|week">
```

## time, datetime, datetime-local : 시간 입력 필드

- time - 시간을 입력하게 하는 필드. 오전or오후/시/분
- datetime, datetime-local - 지역에 맞는 날짜와 시간을 함께 입력 가능

```html
<input type="time|datetime|datetime-local">
```

### 날짜,시간 범위 제한 속성

- min
- max
- step
- value

```html
<input type="date" min="2022-01-01" max="2022-12-31">
```

## submit, reset : 전송, 리셋 버튼

### submit

폼에 입력한 정보를 서버로 전송. value 속성으로 버튼에 표시할 내용을 지정한다.

### reset

input 요소에 입력된 모든 정보를 재설정하여 사용자가 입력한 정보를 모두 지움. value 속성으로 버튼에 표시할 내용을 지정한다.

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>배송 정보</title>
</head>
<body>
    <h1>주문서 확인</h1>
    <form>
        <fieldset>
            <legend><b>배송 정보</b></legend>
            <ul>
                <li>
                    <label for="userName">이름</label>
                    <input type="text" id="useName">
                </li>
                <li>
                    <label for="userCall">전화번호</label>
                    <input type="del" id="userCall">
                </li>
            </ul>
        </fieldset>
        <fieldset>
            <legend>수신 동의 여부</legend>
            <label><input type="radio" name="sns" value="yes">예</label>
            <label><input type="radio" name="sns" value="no">아니오</label>
        </fieldset>
        <fieldset>
            <legend>배송 날짜 지정</legend>
            <ol>
                <li>
                    <label>배송 날짜(주문일로부터 최소 3일 이후)<input type="date" min="2022-03-13" max="2022-12-31"></label>
                </li>
                <li>
                    <label>수령 가능 시간<input type="time"></label>
                </li>
            </ol>
        </fieldset>
        <div>
            <input type="submit" value="주문하기">
            <input type="reset" value="취소하기">
        </div>
    </form>
</body>
</html>
```

![5_폼7](https://user-images.githubusercontent.com/97890886/161421077-a88d765a-6358-46ea-9f22-11e3636e576d.png)


## image : 이미지 버튼

```html
<input type="image" src="이미지 경로" alt="대체 텍스트">
```

submit 버튼과 같은 기능을 하는 이미지 버튼

## button : 기본 버튼

```html
<input type="button" value="버튼에 표시할 내용">
```

submit이나 reset과 같은 기능이 없고 오직 그냥 버튼의 기본 형태만 삽입. 주로 버튼을 클릭해서 자바스크립트를 실행할 때 사용

```html
<input type="button" value="공지 창 열기" onclick="pageOpen('notice.html')">
```

## file : 파일 첨부

폼에서 사진이나 문서를 첨부해야 하는 경우 사용

```html
<input type="file">
```

## hidden : 히든 필드 생성

화면의 폼에는 보이지 않지만 사용자가 입력을 마치면 폼과 함께 서버로 전송되는 요소. 사용자에게 굳이 보여 줄 필요는 없지만, 관리자가 알아야 하는 정보를 주로 입력한다.

```html
<input type="hidden" name="이름" value="서버로 넘길 값">
```

```html
<input type="hidden" value="사이트를 통한 직접 로그인">
<label>아이디<input type="text" value="userId" size="10"></label>
<label>비밀번호<input type="password" value="userPw" size="20"></label>
<input type="submit" value="로그인">
<input type="reset" value="취소">
```