# Regular Expression (정규 표현식)

일정한 패턴을 가진 문자열의 집합을 표현하기 위해 사용하는 formal language(형식 언어). 자바스크립트 고유 문법이 아니라 대부분의 프로그래밍 언어와 코드 에디터에 내장되어 있다.

문자열을 대상으로 `패턴 매칭 기능`을 제공한다 : 특정 패턴과 일치하는 문자열을 검색/추출/치환할 수 있다. 이를 사용하면 **반복문과 조건문 없이 패턴을 정의하고 간단히 테스트** 할 수 있다. 다만 주석, 공백을 허용하지 않고 기호가 뒤죽박죽이라 가독성이 좋지 않다는 단점이 있다.

```jsx
// 사용자로부터 입력받은 전화번호
const tel = `010-8764-9056`;

// 정규 표현식 리터럴로 전화번호 패턴을 정의
const regExp = /^\d{3}-\d{4}-\d{4}$/;

// tel이 패턴에 맞는지 테스트
regExp.test(tel);
```

# 정규 표현식 객체 생성

## 정규 표현식 리터럴

### 구조

![regexp](https://user-images.githubusercontent.com/97890886/167326770-a4769ba6-cf06-4adf-8502-25396328ae55.png)

`패턴`과 `플래그`로 구성된다.

### 예시

```jsx
const target = `hello my name is Kang`;

// 정규 표현식 리터럴로 정규 표현식 생성

// 패턴 : kang
// 플래그 : 대소문자 가리지 않음 (i)
const regexp = /kang/i;

console.log(regexp.test(target));   // true
```

## RegExp 생성자 함수

### 구조

```jsx
// RegExp 생성자 함수로 RegExp 객체 생성

/* pattern : 패턴
flags : 플래그 (g,i,m,u,y) */
new RegExp(pattern[, flags])
```

`RegExp 생성자 함수`로 인스턴스(RegExp 객체)를 생성할 수 있다.

### 예시

```jsx
const regexp2 = new RegExp(/name/i);    // ES6

console.log(regexp2.test(target));   // true
```

변수를 사용해 동적으로도 생성 가능하다.

```jsx
// RegExp 생성자 함수
// 변수를 사용해 동적으로 RegExp 객체를 생성하기
const count = (str, char) => (str.match(new RegExp(char, `gi`))?? []).length;

// ?? 의 의미
// undefined나 null값 들어왔을때의 default value 셋팅
// 위에서는 빈 배열이 기본값으로 되어있으니, length를 거치면 0이겠다

console.log(count(`hey heymama mamamamama`, `m`));    // 7
```

# RegExp 메서드

exec, test, match, replace, search, split 등이 있으나 일단은 exec, test, match만 알아보자.

## RegExp.prototype.exec

- 인수로 전달받은 문자열에 대해 : 정규 표현식의 패턴을 검색하여 매칭 결과를 `배열`로 반환.
- 매칭 결과가 없으면 null

```jsx
const target = `Is this all there is?`;
const regExp = /is/g;

console.log(regExp.exec(target)); 
// [ 'is', index: 5, input: 'Is this all there is?', groups: undefined ]
// 첫 번째 매칭 결과만 반환하므로 플래그의 의미 X
```

## RegExp.prototype.test

- 인수로 전달받은 문자열에 대해 : 정규 표현식의 패턴을 검색하여 매칭 결과를 `불리언`으로 반환.

```jsx
console.log(regExp.test(target));    // true
```

## String.prototype.match

- 인수로 전달받은 **정규 표현식**에 대해 : 대상 문자열과의 매칭 결과를 배열로 반환
- 첫 번째 매칭 결과만을 반환하는 exec와는 다르게 g플래그 지정 시 모든 매칭 결과를 배열로 반환

# 플래그

> 검색 방식을 설정하기 위해 사용한다.
> 
- i : 대소문자 구별X
- g : 모든 문자열 내에서 전역 검색 (’this is my bag’에서 ‘is’를 검색할 때, 하나만 찾고 끝내는 것이 아니라 문자열 **전체**를 검색하면서 **전부** 찾는다. → [’is’, ‘is’])
- m : 문자열의 행이 바뀌더라도 패턴 검색을 계속

어떤 플래그를 사용하지 않은 경우(기본값) 대소문자를 구별하며(i와 반대), 매칭값이 여러개여도 첫 번째 매칭값만 검색한다(g와 반대)

# 패턴

> 문자열의 일정한 규칙을 표현하기 위해 사용한다.
> 

 /로 열고 닫으며 문자열의 따옴표는 생략한다.(따옴표를 넣으면 따옴표도 패턴에 포함되므로 주의) 메타문자나 기호로도 표현할 수 있다.

<aside>
👉 어떤 문자열 내에 패턴과 일치하는 문자열이 존재할 때, 정규 표현식과 `매치`한다고 한다.

</aside>

## 문자열 검색

패턴에 문자/문자열을 지정할 경우, 검색 대상 문자열에서 패턴으로 지정한 문자/문자열을 검색한다. 물론 정규 표현식을 생성한다고 해서 검색이 수행되는 것은 아니고 RegExp 메서드를 사용하여 매칭 결과를 구하면 검색이 수행된다.

```jsx
const target = `nct nctdream nct127`;

const regexp = /nct/g;

console.log(target.match(regexp));    // [ 'nct', 'nct', 'nct' ]
console.log(regexp.test(target));     // true
```

## 임의의 문자열 검색

문자의 내용이 무엇이든 상관없이, (점(.) 하나는 문자 한 개를 의미한다) 자릿수가 일치하는 문자열과 모조리 매치된다.

```jsx
const regexp2 = /.../g;

console.log(target.match(regexp2));    // [ 'nct', ' nc', 'tdr', 'eam', ' nc', 't12' ]
```

## 반복 검색

- {m,n} : 앞선 패턴이 `최소 m번~최대n번` 반복되는 문자열을 검색한다.
- {n} : 앞선 패턴이 `n번` 반복되는 문자열을 검색한다. ( {n, n}과 같음 )
- {n, } : 앞선 패턴이 `최소 n번` 반복되는 문자열을 검색한다.
- + : 앞선 패턴이 `최소 한 번` 이상 반복되는 문자열을 검색한다. ( {1, }과 같음 )
- ? : 앞선 패턴이 `최대 한 번` 이상 반복되는 문자열을 검색한다. ( { , 1}과 같음 )

```jsx
// 반복 검색

// 1. {m,n}
const regexp3 = /A{1,3}/g;
console.log(target2.match(regexp3));    // AA, A, AAA, A
// 2. {n}
const regexp4 = /A{2}/g;
console.log(target2.match(regexp4));    // AA, AA
// 3. {n, }
const regexp5 = /A{2,}/g;
console.log(target2.match(regexp5));    // AA, AAA
// 4. +
const regexp6 = /A+/g;
console.log(target2.match(regexp6));    // AA, A, AAA, A
// 5. ?
const regexp7 = /nct?dream/g;
console.log(target.match(regexp7));    // nctdream
```

### 주의점

공백을 기준으로 문자열을 하나로 묶는 습관을 버려라.

```jsx
const target2 = `AA Aa AAA AB BB`;
const regexp3 = /A{1,3}/g;

console.log(target2.match(regexp3));
```

위 코드의 값을 처음에 예측해 볼 때, AA, Aa, AAA, AB로 예측했다.

정규 표현식은 쿠키 틀과 같다. A를 검색했으니 A만 빼내는게 맞다.

답은 AA, A, AAA, A 이다.

## OR 검색

```jsx
const targetChar = `A AA B BB Aa Bb`;
const targetNum = `kang money 12,345,12123$`;

// OR 검색

// 1. 문자/문자열 검색
// A 또는 B 전역 검색
const regExp = /A|B/g;    
// 분해되지 않게 +를 추가
const regExp2 = /A+|B+/g;
// 단순화
// [] 내의 문자는 OR로 동작
const regExp3 = /[AB]+/g;
// 범위 지정
// - 사용
const regExp4 = /[A-Z]+/g;
// 대소문자 구별X
const regExp5 = /[A-Za-z]+/g;

// 2. 숫자 검색
// `0` ~ `9` 가 한 번 이상 반복되는 문자열 전역 검색
const regExp6 = /[0-9]+/g;
// 쉼표 때문에 끊김 -> 쉼표도 패턴에 포함해줌
const regExp7 = /[0-9,]+/g;
// 단순화
// \d는 0-9와 같다. \D는 숫자가 아닌 문자를 의미한다(/d와 반대)
const regExp8 = /[\d,]+/g;
const regExp9 = /[\D,]+/g;
// \w는 알파벳, 숫자, 언더스코어를 의미한다 : [A-Za-z0-9_]와 같다. \W는 반대다(저거 전부 아닌 것들)
const regExp10 = /[\w,]+/g;
const regExp11 = /[\W,]+/g;
```

## NOT 검색

[...] **내부**에 `^`를 사용하여 `not`의 의미를 준다. [^0-9]는 숫자를 제외한 문자를 의미한다. (\d와도 같다)

## 시작 위치로 검색

[...] **외부**에 `^`를 사용하여 `문자열의 시작`의 의미를 준다.

## 마지막 위치로 검색

$는 `문자열의 마지막`을 의미한다.

# 자주 사용하는 정규표현식

```jsx
// 특정 단어로 시작하는지 검사
// ‘http://’ 또는 ‘https://’ 로 시작하는지 검사 (/를 쓸 때 역슬래시로 이스케이프를 사용해야 한다)
const url = `https://www.youtube.com/`;
console.log(/^http?s:\/\//.test(url));
console.log(/^(http|https):\/\//.test(url));

// 특정 단어로 끝나는지 검사
// html로 끝나는지 검사
const html = `myWeb.html`;
console.log(/html$/.test(html));

// 숫자로만 이루어진 문자열인지 검사
const num = `318312749749024`;
console.log(/^\d+$/.test(num));

// 하나 이상의 공백으로 시작하는지 검사
const space = ` hahaha`;
console.log(/^\s/.test(space));

// 아이디로 사용 가능한지 검사
// 알파벳 대소문자 또는 숫자로 시작하고 끝나며 4~10자리인지 검사
const id = 'khy731';
console.log(/^[A-Za-z0-9]{4,10}$/.test(id));

// 메일 주소 형식에 맞는지 검사
const email = `khy00731@gmail.com`
// 염병할 개길어 패스 ㅗ

// 휴대폰 번호 형식에 맞는지 검사
const call = `010-8764-9056`;
console.log(/^\d{3}-\d{3,4}-\d{4}$/.test(call));

// 특수 문자 포함 여부 검사
const emot = `abcabc#^$%&$@#`;
console.log(/[^A-Za-z0-9]/.test(emot));
// 특수 문자를 전부 나열할 경우(길어서 쓰진 않음) 선택적으로 검사할 수 있는 장점이 있다
// String.prototype.replace 메서드로 특수문자를 제거할 수 있다
```