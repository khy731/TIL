# 모듈이란?

애플리케이션을 구성하는 개별적 요소. 재사용 가능한 코드 조각. 보통 기능을 기준으로 하여 파일 단위로 분리한다. **고유한 모듈 스코프를 가진다.**

> 모듈을 선택적으로 명시적 공개 : `export`
> 

C언어의 라이브러리와 비슷한 개념이다. 자신만의 파일 스코프를 가진 모듈은 자산(기능)을 캡슐화하여 비공개 상태로 가지고 있으며, 외부에서 이를 한정적으로 사용할 수 있다 .

> 모듈을 사용 : `import`
> 

다른 사용자는 모듈이 export한 자산을 선택하여 자신의 스코프 내로 불러들여 사용할 수 있다. C언어의 #include, Java와 python의 import문 등.

> 모듈의 장점
> 
- 코드의 단위를 명확히 구분하여 애플리케이션을 구성할 수 있다
- 재사용성이 뛰어나다

# 자바스크립트의 모듈

자바스크립트는 웹페이지의 기능 보조를 위한 단순하고 제한적인 용도로 만들어졌으므로, 태생적 한계로 인해 **모듈 시스템이 지원되지 않았다.**

script 태그로 외부의 자바스크립트 파일을 로드할 수는 있지만, 파일마다 독립적인 스코프를 가지지 않으므로 결국 하나의 자바스크립트 파일 안에 있는 것 처럼 섞여서 동작한다.

그러나 JS를 클라이언트 사이드(브라우저 환경)에 국한하지 않고 사용하려는 시도로 인해 다음과 같은 방안이 제시되었다 :

- CommonJS
- AMD(Asynchronous Module Definition)

현재는 CommonJS가 de facto standard(사실상 표준이나 다름없는) 인 상황이며, JS 런타임 환경인 Node.js도 이를 채택했다. 즉, 현재 Node.js는 모듈을 지원한다. 그러면 클라이언트 측에서는?

# ES6 모듈(ESM)

클라이언트 사이드 자바스크립트에서도 동작하는 모듈 기능.

## 사용하기

```jsx
<script type="module" src="app.mjs"></script>
```

- 파일 확장자는 .mjs를 권장한다
- 기본적으로 strict mode가 적용된다

## 모듈 스코프

ESM은 독자적인 `모듈 스코프`를 갖는다.

> 모듈 X
> 

script로 분리하여 로드한 여러 개의 JS 파일은 마치 단 하나의 실행 환경 위에서 돌아가는 것 처럼 동작한다. 즉, 하나의 전역을 공유하는 것이다. 이는 마치 부수 효과와 같은 위험성을 지니고 있다.

```jsx
// foo.js
var x = `foo`;
console.log(window.x);    // foo

// goo.js
x = `goo`;     // 의도치 않은 재할당
console.log(window.x);     // goo

// script 태그로 분리하였지만
// 마치 하나의 JS 파일 내에 있는 것처럼 동작한다
```

> 모듈 O
> 

독자적인 모듈 스코프를 갖으므로, 모듈 내에서의 var 키워드로 선언한 변수는 **전역 변수가 아니며 window 객체의 프로퍼티 또한 아니다.**

```jsx
// foo.mjs
// 고유 스코프를 지니는 모듈

var x = `foo`;
console.log(x);    // foo
console.log(window.x);    // ReferenceError: window is not defined

var y = `hi`;
```

```jsx
// goo.mjs
// 고유 스코프를 지니는 모듈

var x = `goo`;
console.log(x);

console.log(y);    // ReferenceError: y is not defined
```

```html
<!DOCTYPE html>
<html lang="en">
<body>
    <script type="module" src="foo.mjs"></script>
    <script type="module" src="goo.mjs"></script>
</body>
</html>
```

## export 키워드

모듈 내부에서 선언한 모든 식별자는 기본적으로 해당 모듈 내부에서만 참조할 수 있지만, 이를 외부에 공개하여 다른 모듈들이 재사용하게 하기 위해 `export`키워드를 사용한다.

```jsx
// lib.mjs
// 변수 공개
export const pi = Math.PI;

// 함수 공개
export function square(x) {
    return x * x;
}

// 클래스 공개
export class Person {
    constructor(name) {
        this.name = name;
    }
}

// 한 번에 일괄 처리도 가능하다
export { pi, square, Person };
```

## import 키워드

다른 모듈에서 공개export한 식별자를 자신의 모듈 스코프 내부로 로드한다. ESM의 경우 파일 확장자 생략이 불가능하다.

만약 app.mjs에서 lib.mjs를 import하는 경우,

- app.mjs는 어플리케이션의 entry point진입점이다 : 최종 프로젝트를 실행할 때 필요한 메인 디쉬 파일이다 → script 태그로 반드시 로드해야 함.
- lib.mjs는 기능의 일부를 제공하기 위해 import문에게 로드되는 dependency의존성이다. → script 태그로 로그되지 않아도 됨

> 다양하게 import하기
> 

```jsx
// app.mjs
// 같은 폴더 내 lib.mjs 모듈이 export한 식별자 이름으로 import
// ESM의 경우 파일 확장자 생략 불가능

// 1. 모듈이 export한 식별자명으로 import

import { pi, square, Person } from './lib.mjs';
console.log(pi, square(2), new Person(`Jung`));
// 3.141592653589793 4 Person { name: 'Jung' }

// 2. 한 번에 하나의 이름으로 import
// as 뒤에 지정한 이름의 객체의 프로퍼티로 할당됨
import * as lib from './lib.mjs';
console.log(lib.pi, lib.square(2), new lib.Person(`Lee`));
// 3.141592653589793 4 Person { name: 'Lee' }

// 3. 식별자 이름을 변경하여 import
import {pi as pie, square as sq, Person as me} from './lib.mjs';
console.log(pie, sq(3), new me(`kang`));
// 3.141592653589793 9 Person { name: 'kang' }
```

### default 키워드

단 하나의 값만 export할 경우, default 키워드를 사용할 수 있다. 이름 없이 하나의 값만을 export한다.

```jsx
export default num => num + 1;
```

이 경우 var, let, xonst 키워드는 사용 불가능하다.

이를 import 할 때에는 임의의 이름으로 중괄호 없이 import한다.

```jsx
import piValue from './lib.mjs';

console.log(piValue);    // 3.141592653589793
```