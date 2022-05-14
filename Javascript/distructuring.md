# 구조 분해 할당

구조화된 데이터를 destructuring(비구조화, 구조 파괴)하여 1개 이상의 변수에 개별적으로 할당하는 것. 배열(이터러블)이나 객체 리터럴에서 `필요한 값만 추출`하여 변수에 할당할 때 유용하다.

# 배열 디스트럭처링 할당

- ES5

인덱스 사용하여 하나하나 따로따로

```jsx
// ES5

var arr = [1,2,3];

var one = arr[0];
var two = arr[1];
var three = arr[2];

console.log(one, two, three);   // 1 2 3
```

- ES6
    - 할당문의 우변(배열 디스트럭처링 할당의 대상)은 `이터러블`이어야 하며, 배열 리터럴 형태로 변수를 선언한다. 기본값으로 초기화할 수 있다.
    - 할당 기준은 배열의 `인덱스`이다. 이 때 변수의 개수 !== 이터러블의 요소 개수 여도 상관X

```jsx
// ES6 배열 디스트럭처링 할당

const array = [1,2,3];
const [first, second, third] = array;   // 1 2 3

console.log(first, second, third);

// 변수의 개수 !== 이터러블의 요소 개수 여도 ㄱㅊ
const [a,b] = [1];
console.log(a,b);   // 1 undefined

const [c,d] = [9,8,7,6,5];
console.log(c,d);   // 9 8

// 기본값을 설정할 수 있다
const [x=0 ,y=0, z=0] = [10, 20];
console.log(x, y, z);   // 10 20 0
```

## 예제 : URL을 파싱하여 객체(protocaol, host, path 프로퍼티) 반환하기

```jsx
// url을 파싱해 protocol, host, path 프로퍼티를 갖는 객체를 반환

function parseURL(url=``) {
    // protocol, host, path 검색
    // `://` 앞의 문자열 : protocol
    // `://` ~ `/` 앞의 문자열 : host
    // `/` 뒤의 문자열 : path
    const parsedURL = url.match(/^(\w+):\/\/([^/]+)\/(.*)$/);

    if (!parseURL) return {};

    const [, protocol, host, path] = parsedURL;
    return {
        protocol,
        host,
        path
    };
}

const myParsedURL = parseURL(`https://twitter.com/home`);
console.log(myParsedURL);
// { protocol: 'https', host: 'twitter.com', path: 'home' }
```

# 객체 디스트럭처링 할당

- ES5

프로퍼티 키 사용

```jsx
const user = {
    firstName : `kang`,
    lastName : `yoon`,
};

// ES5

const fn = user.firstName;
const ln = user.lastName;
console.log(fn, ln);
```

- ES6

배열 때와 똑같지만 할당 기준이 `프로퍼티 키`라는 것만 다르다. 즉, **순서(인덱스)는 전혀 상관이 없으며 선언된 변수명과 프로퍼티 키가 일치하면** 할당된다.

```jsx
// ES6 객체 디스트럭처링 할당

// 순서 의미 X 프로퍼티 키가 기준 O
const {lastName, firstName} = user;
console.log(firstName, lastName);   // kang yoon

// 우변에는 꼭 객체, 객체로 평가될 수 있는 표현식이 와야 함
const {a,b};    // SyntaxError: Missing initializer in destructuring declaration
const {x,y} = null;    // TypeError: Cannot destructure property 'x' of 'null' as it is null.
```

여기서 좌항의 변수는 프로퍼티 축약 표현을 통해 선언된 것으로, 다음 코드와 같은 의미를 가진다.

```jsx
// 위에서 선언된 변수는 프로퍼티 축약 표현을 사용했다
// 다음 코드와 동치이다
const {
    lastName: lastName,
    firstName: firstName
} = user;
```

즉, 객체의 프로퍼티 키와 다른 이름의 변수를 사용하려면 이렇게 써야 한다.

```jsx
const {
    lastName : last,
    firstName : first,
} = user;
console.log(first, last);   // kang yoon
```

> 객체 디스트럭처링 할당은 객체에서 필요한 프로퍼티 값만 추출하여 변수에 할당하고 싶을 때 유용하다.
> 

```jsx
const str = `Hello`;

// String 래퍼 객체로부터 length 프로퍼티만 추출
const { length } = str;
console.log(length);    // 5

const todo = {
    id: `khy`,
    content: `coding`,
    completed: true,
};

const { id } = todo;
console.log(id);    // khy
```

```jsx
// 객체를 인수로 전달받는 함수에 활용하기

// ES5
function printTodo(obj) {
    return `${obj.id}님의 ${obj.content} 상태는 ${obj.completed?`완료`:`비완료`}입니다`;
}
console.log(printTodo(todo));   // khy님의 coding 상태는 완료입니다

// 객체 디스트럭처링 활용
function printTodo2({id, content, completed}) {
    return `${id}님의 ${content} 상태는 ${completed? `완료`:`비완료`}입니다`;
}
console.log(printTodo2(todo));  // khy님의 coding 상태는 완료입니다
```

> 배열의 요소가 객체인 경우 두 디스트럭처링 할당을 혼용할 수 있다.
> 

```jsx
// 배열의 요소가 객체인 경우
// 배열 디스트럭처링 + 객체 디스트럭처링 혼합

const users = [
    {id:1, pass:1234},
    {id:2, pass:5678},
    {id:3, pass:9999}
]

// 두 번째 요소(배열 디스트럭처링)
// id 프로퍼티(객체 디스트럭처링)
const [, {id}] = users;
console.log(id);    // 2
```

> 중첩 객체의 경우도 비슷하다.
> 

```jsx
const me = {
    name: `kang`,
    age: 22,
    job: {
        address: `university`,
        what: `study`
    }
};

const {job: {what}} = me;
console.log(what);  // study
```

> 객체 디스트럭처링 할당을 위한 변수에 Rest 파라미터나 Rest 프로퍼티를 사용할 수 있다
> 

```jsx
const obj = {
    one:1,
    two:2,
    three:3,
    four:4
}

const {one, ...rest} = obj;
console.log(one, rest);    // 1 { two: 2, three: 3, four: 4 }
```