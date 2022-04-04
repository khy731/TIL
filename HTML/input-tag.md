# input 태그의 속성

단순히 내용을 입력받을 뿐만 아니라, 입력란에 커서나 힌트를 표시할 수도 있고, 꼭 입력해야 하는 필드도 지정할 수 있다. 예전에는 javascript를 이용해야 했던 것들을 이제는 input 태그의 속성만으로도 처리할 수 있게 되었다.

## autofocus

> 자동으로 입력 커서 조정

페이지를 불러오자마자 폼에서 원하는 요소에 마우스 포인터를 표시할 수 있다.

## placeholder

> 힌트 표시

로그인 창에서 볼 수 있는 옅은 회색 글씨의 "아이디를 입력하세요."와 같이 사용자에게 해당 필드에 어떤 내용을 입력해야 할 지 알려준다. 사용자가 입력을 하면 사라진다.

## readonly

> 읽기 전용 필드 생성

사용자가 입력하지는 못하고 읽을 수 있게만 하는 읽기 전용 필드를 만든다.

## required

> 필수 입력 필드 지정

필수로 입력해야하는 사항에 사용하는 속성. 지정한 필드를 채우지 않으면 오류 메세지를 띄워준다.

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <title>배송정보 확인 사이트</title>
</head>
<body>
    <form>
        <fieldset>
            <legend>배송 정보</legend>
            <ul>
                <li>
                    <label for="user-product">주문 상품</label>
                    <input type="text" value="무뼈닭발 5kg" id="user-produxt" readonly>
                </li>
                <li>
                    <label for="user-name">이름</label>
                    <input type="text" id="user-name" autofocus required>
                </li>
                <li>
                    <label for="user-call">전화번호</label>
                    <input type="del" id="user-call" placeholder="- 빼고 입력해 주세요." required>
                </li>
                <li>
                    <label>배송 날짜 지정<input type="date" min="2022-03-13" max="2022-12-31">(배송일로부터 최소 3일 이후)</label>
                </li>
            </ul>
        </fieldset>
        <div>
            <input type="submit" value="주문하기">
            <input type="reset" value="취소하기">
        </div>
    </form>
</body>
</html>
```

![5_폼8](https://user-images.githubusercontent.com/97890886/161542710-fe3be4d4-932e-4ed5-b9dc-766b9600abc3.png)

# 폼에서 사용하는 기타 태그들

## textarea 태그

> 여러 줄을 입력하는 텍스트 필드

폼에서 텍스트를 여러 줄 입력하는 영역. 게시판에서 글을 입력하거나, 회원 가입 양식에서 사용자 약관을 표시할 때 주로 사용한다.

- cols : 텍스트 영역의 가로 너비를 문자 단위로 지정
- rows : 텍스트 영역의 세로 너비를 줄 단위로 지정. 지정한 값보다 줄 개수가 많아지면 스크롤 막대가 생김

```html
<label for="memo">메모</label>
<textarea id="memo" cols="40" rows="4">기본값</textarea>
```

## select, option 태그

> 드롭다운 목록 생성

사용자가 내용을 직접 입력하지 않고 여러 옵션 중에서 선택하게 하는 것. 드롭다운이라는 이름이 붙은 이유는, 목록을 클릭했을 때 옵션들이 요소 아래쪽으로 주루룩 펼쳐지는 식으로 되어 있어서 붙여진 것.


```html
<select>
    <option value="값1">항목1</option>
    <option value="값2">항목2</option>
</select>
```

- select 태그의 속성
  - size : 화면에 표시할 드롭다운 항목의 개수 지정
  - multiple : 드롭다운 목록에서 둘 이상의 항목을 선택할 때 사용   


- option 태그의 속성
  - value : 해당 항목을 선택할 경우, 서버로 넘겨줄 값 지정
  - selected : 드롭다운 메뉴를 삽입할 때 디폴트로 선택될 항목 지정

## datalist, option 태그

> 데이터 목록 사용하기

데이터 목록을 사용하여, 텍스트 필드에 값을 직접 입력하지 않고 미리 만들어 놓은 값 중에서 선택하도록 한다. select와 다른 점이라면 직접 입력도 가능하다는 점이다. 구조는 select와 같다.

```html
<input type="text" list="데이터 목록의 id">
<datalist id="데이터 목록의 id">
    <option value="서버로 넘길 값1">항목1</option>
    <option value="서버로 넘길 값2">항목2</option>
</datalist>
```

## button 태그

> 버튼 만들기

```html
<button type="submit|reset|button">내용</button>
```

폼 뿐만 아니라 버튼이 필요한 웹 문서에서 어디서든지 다양하게 활용이 가능하다. 다른 컨텐츠를 포함할 수 있기 때문에 아이콘을 포함하거나 CSS로 이쁘게 꾸밀 수도 있어 더 범용성 있고, 디자인적으로 자유롭다.