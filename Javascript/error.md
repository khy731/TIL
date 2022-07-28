# 에러 처리의 필요성

> 에러가 발생하지 않는 코드를 작성 하는 것은 불가능. 에러는 필연적, 에러에 ‘대응’해야 함.
> 

```jsx
console.log(`[start]`);

foo();  // ReferenceError: foo is not defined
// 프로그램 강제 종료됨

// 실행되지 못한다
console.log(`[end]`);
```

에러가 발생하면 프로그램이 강제 종료되므로 이를 방치하면 안 된다.

## 단축 평가와 옵셔널 체이닝 연산자

직접적으로 에러가 발생하지는 않지만, 이후 프로그램 실행에 지장을 일으키는 예외(exception)상황에 적절하게 대응한다.

querySelector 메서드로 DOM 요소 노드를 탐색하여 할당하는 과정에서 오류가 발생할 경우, 에러가 발생하지 않고 null이 할당된다.

```jsx
<!DOCTYPE html>
<html lang="ko">
<head>
</head>
<body>
    <p></p>
    <script>
        const $p = document.querySelector(`ppppp`);    // 에러 발생 X null 할당됨
        $p.textContent = `hi`;  // Uncaught TypeError: Cannot set properties of null (setting 'textContent')
    </script>
</body>
</html>
```

querySelector 메서드는 인수로 전달한 문자열이 CSS 선택자 문법에 어긋날 경우에만 에러를 발생시키고, DOM에서 요소 노드를 찾을 수 없는 경우에는 에러 대신 null을 반환한다.

이 때 if문이나 단축 평가, 옵셔널 체이닝 연산자 등을 사용하지 않으면 다음 처리가 엉망이 된다.

```jsx
$p?.textContent = `hi`;  // Uncaught SyntaxError: Invalid left-hand side in assignment
```

에러는 언제나 발생하므로, 항상 에러를 전제에 두고 이에 대응하는 코드를 작성해야 한다.

## try…catch 문

프로그램 강제 종료를 막고 계속해서 코드가 실행되게 만든다

```jsx
console.log(`start`);

try {
    foo();
} catch(e) {
    console.error(`${e}`);
}

console.log(`end`);

/* start
ReferenceError: foo is not defined
end */
```

# try…catch…finally 문

> 일반적으로 에러 처리를 구현하는 방법은 두 가지가 있다.
> 
- 예외적인 상황을 if문, 단축 평가, 옵셔널 체이닝 연산자로 확인 및 처리
- 에러 처리 코드를 미리 등록 → 에러가 발생하면 에러 처리 코드로 점프하도록 구현

try…catch…finally 문은 후자이다. 이 방법을 `에러 처리(error handing)`이라고 한다.

```jsx
try {
    // 실행할 코드 : 에러 발생 가능성이 있는 코드
} catch(err) {
    // try 블록에서 에러 발생 시 점프하여 실행될 코드
    // 인수로 try에서 발생한 Error 객체가 전달됨
} finally {
    // 에러 발생과 상관없이 반드시 한 번 실행됨
}
```

# Error 객체

`Error 생성자 함수`로 에러 객체를 생성한다. 인수로 에러 메시지를 전달할 수 있다.

## 프로퍼티

- message : 인수로 전달한 에러 메시지
- stack : 에러를 발생시킨 call stack의 호출 정보. 디버깅 목적으로 이용

자바스크립트는 Error 생성자 함수 말고도 SyntaxError, ReferenceError… 등 7가지의 에러 생성자 함수를 제공한다. 이들은 모두 `Error.prototype`을 상속받는다.

# throw 문

Error 생성자 함수로 에러 객체를 생성한다고 해서 에러가 발생하는 것은 아니다. 즉, 에러 객체 생성과 에러 발생은 애초에 의미가 다르다.

> 에러를 발생시키려면 `throw 문`으로 에러 객체를 던져야(throw) 한다.
> 

```jsx
throw expression;
```

표현식은 어떤 값이어도 상관없으나 일반적으로 에러 객체를 지정한다.

```jsx
try {
    // 에러 객체를 throw
    throw new Error(`에러 발생`);
}  catch(e) {
    console.error(e);
}
```

에러를 던짐 → 에러 발생 → catch문의 에러 변수가 생성되고 던져진 에러 객체가 할당됨 → catch문 실행

### 예제

```jsx
const repeat = function(c, n) {
    if (typeof c !== `function`) throw new TypeError(`c must be a function`);

    for(let i = 0; i < n; n++) c(i);
}

// 함수 repeat 호출문은 에러가 발생할 가능성이 있으므로
// try...catch...finally 문으로 작성한다
try {
    repeat(1,2);
} catch(e) {
    console.error(e);    // TypeError: c must be a function
}
```

# 에러 전파

에러는 호출자(Caller) 방향으로 전파된다. 즉, Call stack의 아래 방향(실행 중인 실행 컨텍스트가 push되기 **바로 직전에** push되었떤 실행 컨텍스트 방향)이다.

```jsx
const foo = () => goo();

const goo = () => zoo();

const zoo = () => {
    throw new Error(`zoo Error!`);
}

try {
    foo();
} catch(e) {
    console.error(e);
}

/* foo 호출 -> goo 호출(caller:foo) -> zoo 호출(caller:goo) -> 에러 발생
에러는 caller을 타고 거꾸로 올라가듯이 전파된다
zoo의 caller은 goo -> goo의 caller은 foo -> 에러 캐치 */
```

throw된 에러는 캐치되기 전까지 호출자 방향으로 전파된다. 어디에서든 이를 적절히 캐치하여 대응하지 않으면 프로그램은 강제 종료된다.

> 비동기 처리에서 에러 전파에 주의하라
> 

비동기 함수인 setTimeout이나 프로미스 후속 처리 메서드의 콜백 함수는 **Caller가 없다.** 이들은 task queue나 micriotask queue에 일시 저장되었다가 call stack이 비면! event loop에 의해 call stack에 push되어 실행되므로, 항상 call stack의 최하부에 위치한다 → 에러를 전파할 Caller가 없으므로 상위 스코프에서 에러를 캐치할 수 없다.

![error](https://user-images.githubusercontent.com/97890886/181495268-7c6e03ef-10cc-46fb-8a6e-312201e5802c.png)
