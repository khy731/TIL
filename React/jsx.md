# jsx

```jsx
const element = <h1>Hello, world!</h1>;
```

이 재미있는 태그 문법은 문자열도 HTML도 아니다.

JSX는 자바스크립트의 문법 확장이며, React “요소”를 만든다.

JSX를 리액트와 함께 사용하여 UI가 실제로 어떻게 보일지 공부해보자.

## 왜 JSX인가?

React는 렌더링 로직이 다른 UI 로직과 본질적으로 결합되어 있다. 또한 이벤트 처리, 시간에 따른 상태 변경 및 데이터 표시를 포함하고 있다.

React는 별도의 “컴포넌트”라고 부르는 느슨하게 연결된 유닛 마크업과 로직을 넣어 *기술* 을 인위적으로 분리한다.

React는 JSX 사용을 하지는 않지만, 자바스크립트 코드 내부에서 UI를 작업할 때 시각적으로 더 낫기 때문에 사용하는 것이 권장된다. 또한 React가 보다 도움이 되는 에러 및 경고 메시지를 표시해줄 수 있다.

## JSX는 자바스크립트 표현식을 포함할 수 있다

JSX 안에 [](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Expressions_and_Operators#Expressions)자바스크립트 표현식을 중괄호로 묶어서 포함시킬 수 있다.

```jsx
function formatName(user) {
  return user.firstName + ' ' + user.lastName;
}

const user = {
  firstName: 'Harper',
  lastName: 'Perez'
};

const element = (
  <h1>    Hello, {formatName(user)}!
  </h1>);

ReactDOM.render(
  element,
  document.getElementById('root')
);
```

### 자바스크립트 문법 사용하기

- 중괄호 안에 `숫자`, `문자열`, `표현식(이 평가된 값)`을 넣으면 그대로 렌더링된다.
- 불리언이나 배열 등 숫자/문자열을 제외한 데이터 타입은 렌더링되지 않으므로 주의한다.
- **삼항 연산자**를 사용하여 조건에 따라 다른 요소를 렌더링(`조건부 렌더링`)할 수 있다.

> 홀짝 조건부 렌더링
> 

```jsx
const num = 10;

    return (
        <div style={style.App}>
                <p>10은 {num % 2 === 0 ? '짝수' : '홀수'}</p>
        </div>
    );
```

## JSX 또한 표현식이다

컴파일이 끝나면, JSX 표현식은 자바스크립트 객체로 인식된다. 즉, JSX 표현식은 마치 `값`처럼 사용이 가능한 것이다. if문이나 for문, 변수 할당, 매개 변수에 인수로 전달, 함수에서 반환 등….

```jsx
function getGreeting(user) {
  if (user) {
    return <h1>Hello, {formatName(user)}!</h1>;
  }
  return <h1>Hello, Stranger.</h1>;
}
```

## 클로징 태그

반드시 모든 태그는 닫혀있어야 한다. 만약 태그가 비어있다면, XML 처럼 `/>` 를 이용해 닫아주어야 한다.

```jsx
const element = <img src={user.avatarUrl} />;
```

## 최상위 태그는 필수

JSX 태그는 자식을 가질 수 있으며, JSX로 컴포넌트를 만들어서 반환하려면 모든 태그를 감싸고 있는 단 하나의 부모 태그가 필요하다. HTML처럼 나열할 수 없고(정 하고 싶다면 React.flagment를 사용할 것) 최상위 태그를 사용해야 한다.

```jsx
const element = (
  <div>
    <h1>Hello!</h1>
    <h2>Good to see you here.</h2>
  </div>
);
```

위 예제에서는 div가 최상위 태그(부모)이다.

## 스타일 지정

### CSS

기존 js에서 css를 참조하던 것과 비슷하다. 단, 클래스를 지정할 때는 class가 이미 예약어로 등록되어 있기 때문에 대신 className을 쓴다.

### 인라인

어트리뷰트를 지정해 주거나, 객체를 따로 만들어 객체의 프로퍼티를 참조하는 식으로 스타일을 지정할 수 있다.

> 스타일 객체를 생성하여 인라인 스타일 지정하기
> 

```jsx
// import './App.css';
import MyHeader from './MyHeader';

function App() {
    const name = '강혜윤';

    const style = {
        App : {
            backgroundColor : 'aqua'
        },
        h2 : {
            color: 'violet'
        }
    };

    return (
        <div style={style.App}>
            <MyHeader />
                <h2 style={style.h2}>Hello, {name}!</h2>
        </div>
    );
}

export default App;
```

중괄호에 자바스크립트 문법(프로퍼티 참조)를 사용하여 인라인 스타일을 지정하였다.

## JSX 인젝션 공격 예방

유저 입력을 JSX 내에 포함시키는 것이 안전하다.

```jsx
const title = response.potentiallyMaliciousInput;
// This is safe:
const element = <h1>{title}</h1>;
```

기본적으로, React DOM은 렌더링 되기 전에 JSX 내에 포함된 모든 값을 이스케이프하므로 어플리케이션에 명시적으로 작성되지 않은 내용은 절대 삽입할 수 없다. 모든 것은 렌더링 되기 전에 문자열로 변환된다. 이렇게 하면 [XSS (cross-site-scripting)](https://en.wikipedia.org/wiki/Cross-site_scripting)공격을 막을 수 있다.

## JSX 객체 표현

Babel은 JSX를 `React.createElement()` 메서드 호출로 컴파일한다.

```jsx
// JSX
const element = (
  <h1 className="greeting">
    Hello, world!
  </h1>
);

// Babel에 의해 컴파일된 코드
// 위와 동일하다
const element = React.createElement(
  'h1',
  {className: 'greeting'},
  'Hello, world!'
);
```

 `React.createElement()` 메서드는 내부적으로 React elements 객체를 생성하는데, React는 이 객체를 읽어들이고 이를 이용하여 DOM을 구성하며 최신 상태로 유지한다. 화면에서 볼 수 있는 내용에 대한 설명이라고 생각하면 쉽다. 길제 정보가 담긴 객체.

```jsx
// Note: this structure is simplified
const element = {
  type: 'h1',
  props: {
    className: 'greeting',
    children: 'Hello, world'
  }
};
```