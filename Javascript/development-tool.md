# 다양한 자바스크립트 개발 도구

- Git : 프로젝트가 커져도 관리를 용이하게 하고 협업에 유용한 버전 컨트롤 도구
- Node : 브라우저 **밖에서도** 자바스크립트를 실행 가능하게 하는 도구
- Gulp : 반복적 개발 작업을 자동화하는 빌드 도구
- Babel : ES6→ES5 변환하는 트랜스컴파일러
- ESLint : 실수를 줄이고 더 나은 프로그래머가 되도록 돕는 린트 프로그램

# 터미널

터미널을 시작하면, 커서가 깜빡이는 프롬포트가 보인다. 기본 프롬포트에는 컴퓨터 이름이나 현재 디렉토리 이름이 들어가 있고, $로 끝난다.  Bash에서는 디렉토리 이름을 슬래시(/)로 구분하고, 홈 디렉토리를 ~로 표시한다.

### 현재 디렉토리의 파일 리스트 보기

> $ ls
> 

### 현재 디렉토리 경로를 출력

> $ pwd
> 

### 새 디렉토리 ‘test’ 만들기

> $ mkdir test
> 

### 다른 디렉토리로 이동하기

> $ cd test
> 

‘test’ 디렉토리로 이동하였다.

### 부모 디렉토리로 이동하기

> $ cd . .
> 

# 터미널로 Git 컨트롤하기

Git Bash로 Git을 컨트롤해보자. 

### 1. 프로젝트 루트에서 저장소를 초기화

> $ git init
> 

프로젝트 저장소를 만드는 명령으로, 이제 프로젝트 루트에 hidden 디렉토리 .git이 생성되었다.

### 2. 깃에서 추적하지 않는 파일을 추가

빌드 과정에서 생기는 파일, 임시 파일 등을 .gitignore 파일로 추적에서 제외시킬 수 있다. 프로젝트 루트에 다음 파일(파일명을 쓰지 않고 확장면만 쓴 .gitignore 파일이다)을 추가하자.

```bash
# npm 디버그 기록
npm-debug.log*

# 프로젝트 의존성
node_modules       

# macOS 폴더 속성
.DS_Store                

# 임시 파일
*.tmp                      
*~
```

### 3. 저장소의 현재 상태를 출력

> $ git status
> 

![git-status](https://user-images.githubusercontent.com/97890886/160606800-07609710-a5c8-4c3e-bbb3-b73e716f1440.png)

### 4. git에 .gitignore 파일을 add

> git add .gitignore
> 

변경사항을 한꺼번해 add하려면 git add -A 명령어를 사용하면 된다.

### 5. commit

> git commit -m “Initial commit: added .gitignored.”
> 

-m 뒤에 있는 것은 커밋 메세지이다.

# npm 패키지 관리

## npm이란?

- 설치된 패키지를 관리한다. (패키지’는 완전한 애플리케이션일 수도, 단순한 코드 샘플일 수도, 프로젝트에서 사용할 모듈 또는 라이브러리일 수도 있다.)
- 패키지를 설치 할 때, globally(전역) 이나 lacally(로컬,지역) 로 설치할 수 있다.

 — globally : 보통의 개발 과정에서 사용하는, 터미널에서 실행하는 도구들

 — locally : 각 프로젝트에 종속되는 패키지

백문이 불여일견이다. 인기 있는 underscore 패키지를 설치하여 npm의 동작 원리를 알아보자.

### 1. underscore 패키지 설치

> $ npm install underscore
> 

### 2. 의존성 관리

<aside>
❕ 의존성(dependency) : 프로젝트에 설치하고 사용하는 모듈. lacally한 패키지들.

</aside>

- 일반 의존성
- 개발 의존성 - 어플리케이션 실행 시에는 필요하지 않지만, 프로젝트를 개발할 때 필요하거나 도움이 되는 패키지

프로젝트가 성장하면서 underscore과 같은 모듈을 많이 설치하다 보면, 늘어날 필요 패키지를 간결하게 관리할 방법이 필요해진다. npm은 package.json 파일로 의존성을 관리한다. npm init 명령어로 package.json 파일을 만들어 보자

> $ npm init
> 

그리고 - - save 나 - - save - dev 플래그를 사용하여 underscore를 재설치한다. 이 플래그를 사용하면 설치와 동시에 package.json 파일에 등록된다.

> $ npm install - - save underscore
> 

이제 package.json 파일을 보면 의존성 리스트에 underscore가 있을 것이다. 이 파일에서 패키지 이름과 버전 번호를 읽고 필요한 패키지를 자동으로 다시 내려받음으로써 의존성 관리가 가능해진다.

# 빌드 도구 걸프와 트랜스컴파일러 바벨

### 1. 걸프를 globally로 설치

> npm install -g gulp
> 

개발 과정에서 필수가결적인 반복 작업을 자동화하는 빌드 도구인 걸프를 전역으로 설치한다. 또 프로젝트마다 local 걸프가 필요하므로, 프로젝트 루트에서 npm install - - save - dev gulp 를 해준다. 걸프는 최종 사용자에게는 필요 없지만 개발 과정에서 도움이 되는 개발 의존성이다.

### 2. 바벨을 locally로 설치

> npm install - - save - dev babel-preset-es2015
> 

최신 버전의 바벨은 ES6 변환 프리셋을 설치하고 바벨이 해당 프리셋을 사용하게끔 하는 구조의 트랜스컴파일러이다. 프로젝트마다 다른 문법을 사용하게 될 수 있으니(React나, Es6이나...) 본 프로젝트에서만 적용되도록 locally로 설치한다. 

```jsx
{ "presets" : ["es2015"] }
```

이후 .babelrc 파일을 만들어 프로젝트에서 바벨을 사용할 때 ES6을 사용한다는 것을 인식하게 한다.

# 프로젝트 루트 설정

![project-roote.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/c4afa88b-b479-4a3a-ba32-2e1d6cb3f4a3/project-roote.png)

- 서버(노드) 쪽 코드 : TEST/es6
- 클라이언트(브라우저) 쪽 코드 : TEST/public/es6

dist는 ES5 코드 전용 디렉토리로, ES6 코드가 gulp와 babel에 의해 ES5 코드로 변환되어 저장되는 장소이다.

# 바벨&걸프 사용하기

> 파이프라인 개념으로 바벨과 걸프에 의해 작업이 처리되는 과정
> 
1. 변환할 파일을 ("es6/**/*.js") 에 저장. 여기서 **는 포함하는 모든 디렉터리를 뜻하는 조커 →  깊이에 관계없이 es6 내의 모든 .js 파일을 선택하게 됨
2. 선택한 소스 파일들은 바벨에 파이프로 연결
3. 바벨은 ES6 코드를 ES5 코드로 변형
4. 컴파일된 ES5 코드를 dist 디렉토리에 저장

이제 실제로 직접 작성한 ES6 코드를 ES5 코드로 변환해서 dist와 public/dist에 저장되게 해 보자.

다음은 걸프 파일 gulpfile.js 내의 코드이다.

```jsx
const gulp = required('gulp');
const babel = required('gulp-babel');

gulp.task('default', function() {
    // 노드 소스
    gulp.src("es6/**/*.js")
        .pipe(babel())
        .pipe(gulp.dest("dist"));
    // 브라우저 소스
    gulp.src("public/es6/**/*.js")
    .pipe(babel())
    .pipe(gulp.dest("public/dist"));
});
```

다음은 /es6에 실제로 작성된 파일이다.

```jsx
'use strict';

// es6 기능 : 블록 스코프 변수 선언
const sentences = [
    { subject : 'JavaScript', verb : 'is', object : 'great' },
    { subject : 'I', verb : 'am', object : 'pretty' },
];

// es6 기능 : 객체 분해
function say({ subject, verb, object}) {
    // es6 기능 : 템플릿 문자열
    console.log(`${subject} ${verb} ${object}`);
}

// es6 기능 : for..of
for(let s of sentences) {
    say(s);
}
```

이제 gulp 명령을 내려 파일을 실행해보자. 다음은 실행 결과이다.

```bash
C:\Users\khy00\Documents\Test> node es6/test.js

JavaScript is great
I am pretty
```

된다.(응?) 당연하다. 이 책은 7년 전 시점에서 쓴 책이니까^^

# 린트

파티에 참석할 때, 멋지게 보이기 위해서 옷의 보푸라기(Lint)를 제거하는 것 처럼 코드를 린트해서 멋지게 보이게 할 수 있다. 린트 프로그램은 코드를 세심히 검토해서 자주 일어나는 실수를 알려주는 중요한 도구이다. 

### 1. ESLint 설치

자바스크립트 린트 프로그램인 ESLint를 설치해 보자.

> $ npm install -g eslint
> 

### 2. 설정 파일 생성

ESLint를 사용하기 전, 프로젝트마다 다른 표준이나 규칙을 사용할 수도 있으므로 특정 프로젝트에 전용으로 쓸 설정 파일 .eslintrc를 만들어 각각 다른 ESLint의 린트 규칙을 적용시킨다.

> $ eslint --init
> 

### 3. ESLint 실행

ESLint는 cmd에 직접 실행해도 되고, 에디터에 통합해도 된다. 

> $ npm install --save-dev gulp-eslint
> 

### 4. gulpfile.hs를 수정하여 걸프에 린트 추가

ESLint를 어떻게 실행하든간에, Gulpfile에는 ESLint을 추가하는 것이 좋다. 결국 빌드할 때 마다 걸프를 실행하게 되므로 그때 코드를 검토하는 것이 좋기 때문이다.

```jsx
const Eslintrc = require("./.eslintrc");

const gulp = required('gulp');
const babel = required('gulp-babel');

gulp.task('default', function() {

    //ESLint 실행
    gulp.src(["es6/**/*.js", "public/es6/**/*.js"])
        .pipe(eslint())
        .pipe(Eslintrc.format());
    // 노드 소스
    gulp.src("es6/**/*.js")
        .pipe(babel())
        .pipe(gulp.dest("dist"));
    // 브라우저 소스
    gulp.src("public/es6/**/*.js")
    .pipe(babel())
    .pipe(gulp.dest("public/dist"));
});
```

# 다양한 자바스크립트 개발 도구

- Git : 프로젝트
가 커져도 관리를 용이하게 하고 협업에 유용한 버전 컨트롤 도구
- Node : 브라우저 **밖에서도** 자바스크립트를 실행 가능하게 하는 도구
- Gulp : 반복적 개발 작업을 자동화하는 빌드 도구
- Babel : ES6→ES5 변환하는 트랜스컴파일러
- ESLint : 실수를 줄이고 더 나은 프로그래머가 되도록 돕는 린트 프로그램

# 터미널

터미널을 시작하면, 커서가 깜빡이는 프롬포트가 보인다. 기본 프롬포트에는 컴퓨터 이름이나 현재 디렉토리 이름이 들어가 있고, $로 끝난다.  Bash에서는 디렉토리 이름을 슬래시(/)로 구분하고, 홈 디렉토리를 ~로 표시한다.

### 현재 디렉토리의 파일 리스트 보기

> $ ls
> 

### 현재 디렉토리 경로를 출력

> $ pwd
> 

### 새 디렉토리 ‘test’ 만들기

> $ mkdir test
> 

### 다른 디렉토리로 이동하기

> $ cd test
> 

‘test’ 디렉토리로 이동하였다.

### 부모 디렉토리로 이동하기

> $ cd . .
> 

# 터미널로 Git 컨트롤하기

Git Bash로 Git을 컨트롤해보자. 

### 1. 프로젝트 루트에서 저장소를 초기화

> $ git init
> 

프로젝트 저장소를 만드는 명령으로, 이제 프로젝트 루트에 hidden 디렉토리 .git이 생성되었다.

### 2. 깃에서 추적하지 않는 파일을 추가

빌드 과정에서 생기는 파일, 임시 파일 등을 .gitignore 파일로 추적에서 제외시킬 수 있다. 프로젝트 루트에 다음 파일(파일명을 쓰지 않고 확장면만 쓴 .gitignore 파일이다)을 추가하자.

```bash
# npm 디버그 기록
npm-debug.log*

# 프로젝트 의존성
node_modules       

# macOS 폴더 속성
.DS_Store                

# 임시 파일
*.tmp                      
*~
```

### 3. 저장소의 현재 상태를 출력

> $ git status
> 

![git-status.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/645ab972-0e71-4c24-bd2e-80deb5f30820/git-status.png)

### 4. git에 .gitignore 파일을 add

> git add .gitignore
> 

변경사항을 한꺼번해 add하려면 git add -A 명령어를 사용하면 된다.

### 5. commit

> git commit -m “Initial commit: added .gitignored.”
> 

-m 뒤에 있는 것은 커밋 메세지이다.

# npm 패키지 관리

## npm이란?

- 설치된 패키지를 관리한다. (패키지’는 완전한 애플리케이션일 수도, 단순한 코드 샘플일 수도, 프로젝트에서 사용할 모듈 또는 라이브러리일 수도 있다.)
- 패키지를 설치 할 때, globally(전역) 이나 lacally(로컬,지역) 로 설치할 수 있다.

 — globally : 보통의 개발 과정에서 사용하는, 터미널에서 실행하는 도구들

 — locally : 각 프로젝트에 종속되는 패키지

백문이 불여일견이다. 인기 있는 underscore 패키지를 설치하여 npm의 동작 원리를 알아보자.

### 1. underscore 패키지 설치

> $ npm install underscore
> 

### 2. 의존성 관리

<aside>
❕ 의존성(dependency) : 프로젝트에 설치하고 사용하는 모듈. lacally한 패키지들.

</aside>

- 일반 의존성
- 개발 의존성 - 어플리케이션 실행 시에는 필요하지 않지만, 프로젝트를 개발할 때 필요하거나 도움이 되는 패키지

프로젝트가 성장하면서 underscore과 같은 모듈을 많이 설치하다 보면, 늘어날 필요 패키지를 간결하게 관리할 방법이 필요해진다. npm은 package.json 파일로 의존성을 관리한다. npm init 명령어로 package.json 파일을 만들어 보자

> $ npm init
> 

그리고 - - save 나 - - save - dev 플래그를 사용하여 underscore를 재설치한다. 이 플래그를 사용하면 설치와 동시에 package.json 파일에 등록된다.

> $ npm install - - save underscore
> 

이제 package.json 파일을 보면 의존성 리스트에 underscore가 있을 것이다. 이 파일에서 패키지 이름과 버전 번호를 읽고 필요한 패키지를 자동으로 다시 내려받음으로써 의존성 관리가 가능해진다.

# 빌드 도구 걸프와 트랜스컴파일러 바벨

### 1. 걸프를 globally로 설치

> npm install -g gulp
> 

개발 과정에서 필수가결적인 반복 작업을 자동화하는 빌드 도구인 걸프를 전역으로 설치한다. 또 프로젝트마다 local 걸프가 필요하므로, 프로젝트 루트에서 npm install - - save - dev gulp 를 해준다. 걸프는 최종 사용자에게는 필요 없지만 개발 과정에서 도움이 되는 개발 의존성이다.

### 2. 바벨을 locally로 설치

> npm install - - save - dev babel-preset-es2015
> 

최신 버전의 바벨은 ES6 변환 프리셋을 설치하고 바벨이 해당 프리셋을 사용하게끔 하는 구조의 트랜스컴파일러이다. 프로젝트마다 다른 문법을 사용하게 될 수 있으니(React나, Es6이나...) 본 프로젝트에서만 적용되도록 locally로 설치한다. 

```jsx
{ "presets" : ["es2015"] }
```

이후 .babelrc 파일을 만들어 프로젝트에서 바벨을 사용할 때 ES6을 사용한다는 것을 인식하게 한다.

# 프로젝트 루트 설정

![project-roote.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/c4afa88b-b479-4a3a-ba32-2e1d6cb3f4a3/project-roote.png)

- 서버(노드) 쪽 코드 : TEST/es6
- 클라이언트(브라우저) 쪽 코드 : TEST/public/es6

dist는 ES5 코드 전용 디렉토리로, ES6 코드가 gulp와 babel에 의해 ES5 코드로 변환되어 저장되는 장소이다.

# 바벨&걸프 사용하기

> 파이프라인 개념으로 바벨과 걸프에 의해 작업이 처리되는 과정
> 
1. 변환할 파일을 ("es6/**/*.js") 에 저장. 여기서 **는 포함하는 모든 디렉터리를 뜻하는 조커 →  깊이에 관계없이 es6 내의 모든 .js 파일을 선택하게 됨
2. 선택한 소스 파일들은 바벨에 파이프로 연결
3. 바벨은 ES6 코드를 ES5 코드로 변형
4. 컴파일된 ES5 코드를 dist 디렉토리에 저장

이제 실제로 직접 작성한 ES6 코드를 ES5 코드로 변환해서 dist와 public/dist에 저장되게 해 보자.

다음은 걸프 파일 gulpfile.js 내의 코드이다.

```jsx
const gulp = required('gulp');
const babel = required('gulp-babel');

gulp.task('default', function() {
    // 노드 소스
    gulp.src("es6/**/*.js")
        .pipe(babel())
        .pipe(gulp.dest("dist"));
    // 브라우저 소스
    gulp.src("public/es6/**/*.js")
    .pipe(babel())
    .pipe(gulp.dest("public/dist"));
});
```

다음은 /es6에 실제로 작성된 파일이다.

```jsx
'use strict';

// es6 기능 : 블록 스코프 변수 선언
const sentences = [
    { subject : 'JavaScript', verb : 'is', object : 'great' },
    { subject : 'I', verb : 'am', object : 'pretty' },
];

// es6 기능 : 객체 분해
function say({ subject, verb, object}) {
    // es6 기능 : 템플릿 문자열
    console.log(`${subject} ${verb} ${object}`);
}

// es6 기능 : for..of
for(let s of sentences) {
    say(s);
}
```

이제 gulp 명령을 내려 파일을 실행해보자. 다음은 실행 결과이다.

```bash
C:\Users\khy00\Documents\Test> node es6/test.js

JavaScript is great
I am pretty
```

된다.(응?) 당연하다. 이 책은 7년 전 시점에서 쓴 책이니까^^

# 린트

파티에 참석할 때, 멋지게 보이기 위해서 옷의 보푸라기(Lint)를 제거하는 것 처럼 코드를 린트해서 멋지게 보이게 할 수 있다. 린트 프로그램은 코드를 세심히 검토해서 자주 일어나는 실수를 알려주는 중요한 도구이다. 

### 1. ESLint 설치

자바스크립트 린트 프로그램인 ESLint를 설치해 보자.

> $ npm install -g eslint
> 

### 2. 설정 파일 생성

ESLint를 사용하기 전, 프로젝트마다 다른 표준이나 규칙을 사용할 수도 있으므로 특정 프로젝트에 전용으로 쓸 설정 파일 .eslintrc를 만들어 각각 다른 ESLint의 린트 규칙을 적용시킨다.

> $ eslint --init
> 

### 3. ESLint 실행

ESLint는 cmd에 직접 실행해도 되고, 에디터에 통합해도 된다. 

> $ npm install --save-dev gulp-eslint
> 

### 4. gulpfile.hs를 수정하여 걸프에 린트 추가

ESLint를 어떻게 실행하든간에, Gulpfile에는 ESLint을 추가하는 것이 좋다. 결국 빌드할 때 마다 걸프를 실행하게 되므로 그때 코드를 검토하는 것이 좋기 때문이다.

```jsx
const Eslintrc = require("./.eslintrc");

const gulp = required('gulp');
const babel = required('gulp-babel');

gulp.task('default', function() {

    //ESLint 실행
    gulp.src(["es6/**/*.js", "public/es6/**/*.js"])
        .pipe(eslint())
        .pipe(Eslintrc.format());
    // 노드 소스
    gulp.src("es6/**/*.js")
        .pipe(babel())
        .pipe(gulp.dest("dist"));
    // 브라우저 소스
    gulp.src("public/es6/**/*.js")
    .pipe(babel())
    .pipe(gulp.dest("public/dist"));
});
```