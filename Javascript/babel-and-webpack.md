# ES6+/ES.NEXT 개발 환경을 구축해야 하는 이유

대부분의 에버그린 브라우저(evergreen browser, 웹 표준을 준수하기 위해 지속적으로 자동 업데이트를 지원하는 모던 브라우저)는 ES6를 대부분 지원하지만, IE는(현재는 이미 죽어버렸지만…) ES6 지원율이 11%이며 ES6+과 ES.NEXT는 아직도 지원율이 브라우저마다 들쭉날쭉하다.

즉, 최신 ECMAScript 사양으로 프로젝트를 진행하려면 이것이 미지원/구형 브라우저에서도 문제없이 작동하도록 개발 환경을 구축할 필요가 있다. 모듈 로더도 비슷한 이유로 필요하다.

# Babel

> ES6+/ES.NEXT로 구현된 최신 사양의 소스코드를 ES5 사양의 소스코드로 트랜스파일링(변환)한다.
> 

## 트랜스파일링의 원리

- ES6의 화살표 함수, ES7의 지수 연산자 사용

```jsx
// ES6의 화살표 함수와 ES7의 지수 연산자 사용
[1,2,3].map(n => n ** n);
```

- ES5 사양으로 변환

```jsx
// ES5 사양으로 변환
[1,2,3].map(function(n) {
    return Math.pow(n,n);
})
```

## Babel 설치

![babel](https://user-images.githubusercontent.com/97890886/183080918-4576118e-19c0-451b-878d-d2e04fe4c714.png)

1. 프로젝트 폴더 생성
2. package.json 생성
3. babel-core, babel-cli 설치

## Babel 프리셋 설치

바벨은 파싱 및 출력만 담당할 뿐, 실질적인 트랜스파일링 작업은 플러그인이 처리하게 되므로 프리셋(함께 사용해야 하는 플러그인을 모아둔 것)의 설치는 필연적이다. Babel이 제공하는 공식 프리셋 :

- @babel/preset-env
- @babel/preset-flow
- @babel/preset-react
- @babel/preset-typescript

@babel/preset-env는 필요한 플러그인들을 프로젝트 지원 환경(Browserslist 형식으로 .browserlistrc 파일에 상세 설정 가능-생략 시 기본값으로 자동 설정됨)에 맞춰 동적으로 결정해 준다.

@babel/preset-env 를 npm으로 설치하고, 루트 폴더에 babel.config.json 설정 파일을 생성하여 프리셋 기본 설정을 작성하자.

![babel2](https://user-images.githubusercontent.com/97890886/183080913-868e7cad-06a5-471b-aa2f-ae6819822ccc.png)



```json
{
    "presets": ["@babel/preset-env"]
}
```

## 트랜스파일링

Babel을 사용하여 트랜스파일링을 해보자. Babel CLI 명령어를 사용하는 방식은 번거로우므로 npm scripts에 Babel CLI 명령어를 등록하여 사용해보도록 하자.

package.json의 scripts에 다음과 같은 문을 추가했다 :

```json
"build": "babel src/js -w -d dist/js"
```

- -w : watch 축약형. 타깃 디렉토리 내 모든 js 파일의 변경을 감지하여 트랜스파일링
- -d : --out-dir 축약형. 트랜스파일링 결과물이 저장될 폴더 지정. 지정된 폴더가 없으면 자동 생성

### 트랜스파일링 테스트를 위한 예제

- ES6+/ES.NEXT 사양으로 작성된 코드

> lib.js
> 

```jsx
export const pi = Math.PI;    // ES6 모듈

export function power(x,y) {
    return x ** y;     // ES7 지수 연산자
}

// ES6 클래스
export class Foo {
    #private = 10;    // stage 3 : 클래스 필드 정의 제안

    foo() {
        // stage 4 : 객체 Rest/Spread 프로퍼티 제안
        const {a,b, ...x} = {...{a:1, b:2}, c:3, d:4};
        return {a,b,x};
    }

    bar() {
        return this.#private;
    }
}
```

> main.js
> 

```jsx
import { pi, power, Foo } from './lib';

console.log(pi);
console.log(power(pi,pi));

const myFoo = new Foo();
console.log(myFoo.foo());
console.log(myFoo.bar());
```

- 트랜스파일링 실행

![babel3](https://user-images.githubusercontent.com/97890886/183080911-83b9ce7f-6ec1-47ef-9a39-1b99a9ccb3c8.png)


- ES5 사양으로 트랜스파일링된 결과

```
3.141592653589793
36.4621596072079
{ a: 1, b: 2, x: { c: 3, d: 4 } }
10
```

## 모듈 로딩 테스트 in 브라우저

모듈 기능은 다양한 방식에 따라 제공된다. 위 예제는 main.js와 lib.js 모듈이 Babel에 의해 트랜스파일링되어 잘 동작했는데, 이는 Node.js가 기본 지원하는 CommonJS 방식의 모듈 로딩 시스템에 따른 것이므로 브라우저에서는 제대로 동작하지 않는다.

> **/dist/js/main.js
> 

```jsx
"use strict";

var _lib = require("./lib");

console.log(_lib.pi);
console.log((0, _lib.power)(_lib.pi, _lib.pi));
var myFoo = new _lib.Foo();
console.log(myFoo.foo());
console.log(myFoo.bar());
```

브라우저는 CommonJS 방식의 require 함수를 지원하지 않으므로 에러가 발생한다.

![module-error](https://user-images.githubusercontent.com/97890886/183080909-95a4a37c-7a8b-4f5f-a948-7ceb634ab045.png)

이를 Webpack을 통해 해결해보자.

# Webpack

> 의존 관계가 있는 JS, CSS, 이미지 등의 리소스들을 하나/여러 개의 파일로 번들링해주는 모듈 번들러
> 

즉, 별도의 모듈 로더가 필요 없다. 여러 개의 자바스크립트 파일 또한 하나로 번들링하므로 script 태그로 일일이 파일을 로드하지 않아도 된다.

Webpack이 자바스크립트 파일을 번들링하기 전에 Babel을 로드하여 트랜스파일링하도록 설정해 보자.

## Webpack 설치

```bash
npm install --save-dev webpack-cli
```

## babel-loader 설치

Webpack이 모듈을 번들링할 때, ES6+/ES.NEXT를 ES5로 트랜스파일링하도록 babel-loader를 설치한다.

```bash
npm install --save-dev babel-loader
```

## npm scripts 수정

Babel 대신 Webpack을 로드하도록 package.json을 수정한다.

```json
"build": "webpack -w"
```

## webpack.config.js 설정 파일 작성

Webpack이 실행될 때 참조하는 설정 파일을 프로젝트 루트 폴더에 생성하고 작성해보자.

```bash
const path = require('path');

module.exports = {
    // entry file
    entry: './src/js/main.js',
    // filename : 번들링된 js 파일
    // path : 저장될 경로
    output: {
        path: path.resolve(__dirname, 'dist'),
        filename: 'js/bundle.js'
    },
    module: {
        rules: [
            {
                test: /\.js$/,
                include: [
                    path.resolve(__dirname, 'src/js')
                ],
                exclude: /node_modules/,
                use: {
                    loader: 'babel-loader',
                    options: {
                        presets: ['@babel/preset-env'],
                        plugins: ['@babel/plugin-proposal-class-properties']
                    }
                }
            }
        ]
    },
    devtool: 'source-map',
    mode: 'development'
};
```

이제 Webpack을 실행하여 트랜스파일링과 번들링을 해 보자.

![webpack2](https://user-images.githubusercontent.com/97890886/183080905-8c43b90b-7848-4604-bf63-5dec1e64cd76.png)


![webpack](https://user-images.githubusercontent.com/97890886/183080906-ca423a89-cf3a-4d8e-827a-87e5eaf1c967.png)

성공적으로 실행된 것을 확인할 수 있다!

## babel-polyfill 설치

Babel을 사용하여 트랜스파일링해도 브라우저가 지원하지 않는 코드가 남아있을 수도 있다. Promise, Object.assign, Array.from등은 트랜스파일링을 하더라도 ES5사양에서 대체할 수가 없기 때문이다. 이를 `@babel/polyfill`로 해결해 보자.

 이는 개발 환경에서뿐만 아니라 **실제 운영 환경에서도** 사용해야 하므로 --save-dev 옵션(devDependencies, 개발용 의존성)을 지정하지 않는다.

> main.js 수정
> 
- polyfill이 필요한 코드들을 추가

```jsx
// polyfill이 필요한 코드들

console.log(new Promise((resolve, reject) => {
    setTimeout(()=>resolve(10), 1 * 1000);
}));

console.log(Object.assign({}, {x:1}, {y:2}));

console.log(Array.from([1,2,3], v=>v+v));
```

- polyfill 설치 후 진입점의 선두에서 로드

```jsx
import "@babel/polyfill";
```

- Webpack을 사용하는 경우, webpack.config.js 파일의 entry 배열에 폴리필을 추가

```jsx
entry: ['@babel/polyfill', './src/js/main.js'],
```

다시 Webpack을 실행해보자.

![webpack3](https://user-images.githubusercontent.com/97890886/183080900-2a953bb1-5e88-4b18-aa3c-44f72ab3081e.png)


잘 실행된다