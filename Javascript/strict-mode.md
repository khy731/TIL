# 암묵적 전역(implict global)

```jsx
function foo() {
    x = 10;
}
foo();

console.log(x);
```

foo 함수 내에서 `선언하지 않은 변수` x에 값 10을 할당했을 때, 자바스크립트 엔진은 x를 스코프 체인으로 찾기 시작한다. 

1. foo() 함수의 스코프에서 x변수의 선언을 검색 → 검색 실패
2. foo 함수 컨텍스트의 상위 스코프(위 예제의 경우 전역 스코프)에서 x변수의 선언을 검색 → 검색 실패

이 때 자바스크립트 엔진은  ReferenceError을 발생시키는 대신,

> 암묵적으로 전역 객체에 x 프로퍼티를 동적 생성하여 이를 전역 변수처럼 사용한다.
> 

이처럼 의도와 상관없이 발생하는 암묵적 전역은 오류를 발생시킬 가능성이 크므로, 보다 엄격하게 개발 환경을 구축하기 위해 `엄격 모드(strict mode)`가 등장하게 되었다.

# strict mode

strict mode는 자바스크립트 언어의 문법을 좀 더 엄격히 적용하여 다음과 같은 코드에 대해 명시적인 에러를 발생시킨다.

1. 오류를 발생시킬 가능성이 높은 코드
2. 자바스크립트 엔진의 최적화 작업에 문제를 일으킬 수 있는 코드

린트 도구(ESLint 등; 정적 분석 기능으로 소스코드 실행 전 코드를 스캔하여 문법적 오류 + 잠재적 오류를 검출하고 원인을 리포팅해줌)를 사용해도 유사한 효과를 얻을 수 있다.

> strict mode 보다 `ESLint`를 사용하는 것이 더 강력하다.
> 

## strict mode 사용하기

`전역`의 선두 또는 `함수` 몸체의 선두에 다음과 같은 문을 추가한다.

```jsx
'use strict';
```

## 전역 strict mode 사용의 문제점

전역에 적용한 strict mode는 스크립트 단위로 적용되는데, 일반적인 프로젝트에는 당연하게도 스크립트가 하나가 아닌 여러 개 들어가고, 이렇게 strict mode와 non-strict mode를 혼용하는 것은 바람직하지 않다. 이 경우 `즉시 실행 함수`로 스크립트 전체를 감싸 스코프를 구분 후, 이 선두에 사용한다.

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>strict mode</title>
</head>
<body>
    <!-- non-strict mode -->
    <script>
        'use strict';
    </script>
    <script>
        x = 1;  // 에러 x
    </script>

    <!-- strict-mode -->
    <script>
        'use strict';

        y = 1;  // 에러 o
    </script>
</body>
</html>
```

## 함수 단위 strict mode 사용의 문제점

앞서 말한 바와 비슷한 맥락으로, 함수별로 strict mode와 non-strict mode를 혼용하는 것은 바람직하지 않다. 그리고 함수마다 strict mode를 사용하는 것은 번거로울 뿐더러, 만약 strict mode가 적용된 함수가 참조할 함수 외부 컨텍스트에 strict mode를 적용하지 않으면 문제가 발생한다. 역시 strict mode는 `즉시 실행 함수`로 감싼 스크립트 단위로 적용하는 것이 바람직하다.

```jsx
(function foo() {
    x = 1;

    function goo() {
        'use strict';

        y=2;    // ReferenceError: y is not defined
    }
    goo();
}());
```

# strict mode가 감지하는 에러

- 암묵적 전역

선언하지 않은 변수 참조 시 ReferenceError 발생

- 변수, 함수, 매개변수의 삭제

delete 연산자로 변수,함수,매개변수 삭제 시 syntaxError 발생

- 매개변수 이름의 중복

중복된 매개변수 이름 사용 시 syntaxError 발생

- with문의 사용

with문 사용 시 syntaxError 발생

```jsx
const f = (function() {
    'use strict';

    // 1. 암묵적 전역에 Error
    x = 1;
    console.log(x);

    // 2. 중복된 매개변수명에 Error
    function goo(a,a) {
    };
    goo();

    // 3. delete로 변수,함수,매개변수 삭제 Error
    var y = 0;
    delete y;

    function zoo(b) {
        delete b;
    }

    delete zoo();

    // 4. with 문에 Error
    with({c:5}) {
        console.log(c);
    }
}());
```

# strict mode 적용으로 인한 변화

- 일반 함수의 this

stict mode에서 함수를 일반 함수로써 호출하면 this에 undefined가 바인딩된다. (생성자 함수와 달리, 일반 함수 내부에서는 this가 필요 없기 때문). 에러는 발생하지 않는다

```jsx
const foo = (function () {
    'use strict';

    // 일반 함수의 this
    function goo() {
        console.log(this);
    }

    // 생성자 함수의 this
    function Goo() {
        console.log(this);
    }

    goo();      // undifined
    new Goo();  // Goo {}
}());
```

- arguments 객체

strict mode에서는 매개변수에 전달된 인수를 재할당하여 변경해도 arguments 객체에 반영되지 않는다.

```jsx
const f = (function(x) {
    'use strict';

    x = 10;

    console.log(arguments);     // [Arguments] { '0': 5 }
}(5));
```