# 컴포넌트와 props

## 컴포넌트

컴포넌트를 사용하여 UI를 독립적이고 재사용 가능한 부분으로 분리하고 각 부분을 독립적으로 생각할 수 있다.

컴포넌트는 임의의 입력(props라고 부른다)을 받아들이고 React 요소(어떤 것이 화면에 나타나야 하는가)를 반환한다.

## props

컴포넌트 간 데이터를 주고받을 수 있다.

부모에게서 받은 값을 매개변수로 받아와 사용할 수 있다. 부모가 값을 여러 개 보낼 수 있기 때문에 모든 값은 객체에 담겨서 전송된다. 즉, 이 값을 객체 자체로 받아왔다면 점 표기법으로 접근해야 한다.

## 컴포넌트 정의하기

### 함수형

가장 간단한 방법이며, 자바스크립트 함수로 작성한다.

```jsx
const Welcome = (props) => {
    return <h1>Hello, {props.name}!</h1>;
}
```

위 함수는 단일 props 객체 인수를 받고 React 요소를 반환하므로 유효한 함수형 React 컴포넌트이다.

### ES6 class

```jsx
class Welcome extends React.Component {
    render() {
        return <h1>Hello, {props.name}!</h1>;
    }
}
```

함수형 코드와 생김새는 다르지만, React 관점에서 보면 동일하다.

## 컴포넌트 렌더링

```jsx
const me = <div />;
```

가장 간단한, DOM 태그를 나타내는 React 요소이다.

```jsx
const myName = <Welcome name='kang' />;
```

유저가 정의한 컴포넌트를 요소에 나타낸 것이다.

React는 이 요소를 해석할 때 전달된 JSX 속성을 컴포넌트에 단일 객체로 전달하는데, 이 객체를 `props`라고 한다.

```jsx
function Welcome(props) {
  return <h1>Hello, {props.name}</h1>;
}

const element = <Welcome name="Sara" />;

ReactDOM.render(
  element,
  document.getElementById('root')
);
```

이 코드는 다음과 같은 과정을 거친다 :

1.  `<Welcome name="Sara" />` 요소로 `ReactDOM.render()` 를 호출
2. React가 `{name: 'Sara'}` 를 props로 하여 `Welcome` 컴포넌트를 호출
3. `Welcome` 컴포넌트가 그 결과로 `<h1>Hello, Sara</h1>` 요소를 반환
4. React DOM이 `<h1>Hello, Sara</h1>` 과 일치하도록 DOM을 효율적으로 업데이트

> TIP : 컴포넌트 이름은 DOM 태그와의 차별화를 위해 항상 대문자로 하는 것이 좋다.
> 

## 컴포넌트 결합

컴포넌트는 출력될 때 다른 컴포넌트를 참조할 수 있다. 이를 이용하여 모든 세부 레벨에서 동일한 `컴포넌트 추상화`를 사용할 수 있다. React 앱에서 버튼, 폼, 다이얼로그, 스크린 같은 것들은 모두 일반적으로 컴포넌트로 표현된다.

```jsx
// Hello.js
const Hello = (props) => {
    return <p>Hello,{props.name}! </p>
};

// App.js
import Hello from './Hello.js';

const App = () => {
    return (
        <div>
            <Hello name='kang'/>
            <Hello name='lee' />
            <Hello name='jung'/>
        </div>
    )
}
```

Welcome 컴포넌트를 여러 번 렌더링하는 App 컴포넌트이다.

### 전달할 값이 많다면?

prop(전달할 값)이 많아지면 제어하기 힘들어지기도 한다.

이 때, 하나의 객체로 만들어서 스프레드 연산자로 전달할 수도 있다.

```jsx
// Hello.js
const Hello = ({name}) => {
    return <p>Hello,{name}! </p>
};

// App.js
import Hello from './Hello.js';

const user = {
    name: 'kang',
    age: 22,
    job: 'student'
};

/* const App = () => {
    return (
        <div>
            <Hello name='kang'/>
            <Hello name='lee' />
            <Hello name='jung'/>
        </div>
    )
} */

const App = () => {
    return (
        <div>
            <Hello {...user}/>
        </div>
    )
}
```

또한, 디스트럭처링 할당으로 보다 간편하게 접근이 가능하다.

### defaultProps로 오류 방지하기

```jsx
// 부모 컴포넌트에서 실수로 initialValue라는 값을 넘겨주지 않아도
// 기본값을 미리 설정해놓음으로써 오류를 방지할 수 있다
Counter.defaultProps = {
    initialValue : 0
};
```

## 컴포넌트 추출

컴포넌트를 더 작은 컴포넌트로 쪼개 루트 노드를 보다 단순화하자.

## 컴포넌트는 read-only이다

컴포넌트를 어떻게 선언했건, props는 자식 컴포넌트에서 변화를 줄 수 없다. 마치 순수 함수처럼, 입력으로 받아 변경을 할 수 없는 것이다.

> **모든 React 컴포넌트는 props와 관련한 동작을 할 때 순수 함수처럼 동작해야한다.**
> 

물론 어플리케이션 UI는 동적이며 시간이 지남에 따라 변한다. 이 때 `state`를 사용한다. state는 React 컴포넌트가 이 규칙을 어기지 않고 유저 액션, 네트워크 응답, 기타 등등에 대한 응답으로 시간 경과에 따라 출력을 변경할 수 있게 한다.