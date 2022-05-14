# 스프레드 문법(전개 문법)

배열 메서드를 배우면서 수많이 봐 왔던 “그러나 ES6에서 도입된 스프레드 문법을 사용하는 것을 권장한다”에 대한 궁금증을 이제 풀 수 있을 것이다! lets gooooo

> `...`
> 

하나로 뭉쳐 있는 여러 값들의 집합을 펼쳐(spread) 개별적인 값들의 목록으로 만든다. **`이터러블`에서만 사용 가능**하다.

```jsx
// ... -> 이터러블을 개별 요소로 분리
console.log(...[1,2,3]);    // 1 2 3

// 문자열 === 이터러블
console.log(...`kang`);     // k a n g

// Map === 이터러블 && Set === 이터러블
console.log(...new Map([[`a`,`1`], [`b`,`2`]]));    // [ 'a', '1' ] [ 'b', '2' ]
console.log(...new Set([1,2,3]));   // 1 2 3

// 이터러블이 아니면 스프레드 문법 사용 불가
console.log(...{a:1, b:2});    // TypeError: Found non-callable @@iterator
```

> 스프레드 문법의 결과는 **값이 아니다**
> 

스프레드 문법은 피연산자를 연산하여 값을 연산하는 연산자가 아니라, 단순히 이터러블을 펼쳐 요소들을 개별적인 값들의 목록으로 만든다.

→ 값처럼 사용(변수에 할당 등)할 수 없다. `값의 목록`을 사용하는 문맥에서만 사용 가능하다.

- 함수 호출문의 `인수 목록`
- 배열 리터럴의 `요소 목록`
- 객체 리터럴의 `프로퍼티 목록`

# 함수 호출문의 인수 목록

배열을 spread하여 개별적인 값들의 목록으로 만든 후 함수의 인수 목록으로 전달해야 할 때 사용

## Math.max 메서드

Math.max 메서드는 매개변수 개수를 확정할 수 없는 `가변 인자 함수`이다. 즉, 배열을 인자로 전달할 수 없으며 (개수가 정해져 있지 않은)여러 개의 숫자를 인수로 전달받아 최댁닶을 반환한다.

- before : Function.prototype.apply를 사용하여 번거로움
- after : 스프레드 문법으로 간결! 가독성 up!

```jsx
// 배열(이터러블)
const arr = [1,2,3];

// 문제 : 숫자가 아닌 배열을 인수로 전달하면 NaN
console.log(Math.max(arr));    // NaN

// 해결 :
// 1. Funtion.prototype.apply 사용 시
console.log(Math.max.apply(null,arr));

// 2. spread 사용 시 : 권장
console.log(Math.max(...arr));  // 3
```

## Spread 문법과 Rest 파라미터는 서로 반대의 개념

Rest 파라미터는 인수들의 목록을 배열로 전달 받기 위해 매개변수 이름 앞에 붙인다 (펼쳐→뭉쳐)

스프레드 문법은 이터러블(여러 값이 하나로 뭉쳐 있음)을 펼쳐 개별적인 값들의 목록을 만든다 (뭉쳐→펼쳐)

# 배열 리터럴의 요소 목록

배열 리터럴에 스프레드 문법을 사용하면 기존(ES5)보다 더욱 간결! 가독성 좋게! 표현할 수 있다. (ES5 예제에 const 키워드 쓴 건 그냥 넘어가자 나는 var을 보면 var작을 일으킨다)

## 여러 개의 배열을 하나의 배열로 결합

- concat

```jsx
const arr1 = [1,2,3];
const arr2 = [4,5,6];

// ES5
const array1 = arr1.concat(arr2);
console.log(array1);
```

- 스프레드 문법

```jsx
// ES6(스프레드 문법)
const array2 = [...arr1, ...arr2];
console.log(array2)
```

## 배열의 중간에 다른 배열의 요소를 추가/제거

- splice

**배열 자체**가 추가되므로, 필연적으로 Function.prototype.apply 메서드를 사용하여 호출해야 한다.

```jsx
const arr1 = [1,4];
const arr2 = [2,3];

// ES5
arr1.splice(1,0,arr2);   // 1번째 인덱스부터 0개를 제거하고 그 자리에 arr2를 삽입
console.log(arr1);    // [ 1, [ 2, 3 ], 4 ]

// Function.prototype.apply를 사용해 호출해야 한다
console.log(Array.prototype.splice.apply(arr1, [1,0].concat(arr2)));    // [ 1, 2, 3, 4 ]
```

- 스프레드 문법

```jsx
// ES6(스프레드 문법)
arr1.splice(1,0,...arr2);
console.log(arr1);   // [ 1, 2, 3, 4 ]
```

## 배열 복사

- slice

```jsx
const origin = [`kang`, `hye`, `yoon`];

// ES5
const copy1 = origin.slice();
console.log(copy1);    // [ 'kang', 'hye', 'yoon' ]

// 얕은 복사임
console.log(origin === copy1);  // F
```

- 스프레드 문법

```jsx
// ES6(스프레드 문법)
const copy2 = [...origin];
console.log(copy2);    // [ 'kang', 'hye', 'yoon' ]

// 역시 얕은 복사임
console.log(origin === copy2);  // F
```

## 이터러블→배열 변환

- slice

```jsx
// ES5

// 이터러블이면서 유사 객체 arguments를 배열로 변환하여 배열 메서드를 사용하고 싶을 때
// Function.prototype.call 이나 Function.protoype.apply를 사용하여 slice 메서드 호출
function sum() {
    var args = Array.prototype.slice.call(arguments);

    return args.reduce(function(pre, cur) {
        return pre + cur;
    }, 0);
}

console.log(sum(1,2,3));    // 6

// 이터러블이 아닌 유사 객체를 배열로 변환할 때도 사용 가능한 방법이다
const arrayLike = {
    0: `kang`,
    1: `hye`,
    2: `yoon`,
    length: 3
};
const arr = Array.prototype.slice.call(arrayLike);
console.log(arr);   // [ 'kang', 'hye', 'yoon' ]
```

- 스프레드 문법

```jsx
// ES6

// 스프레드 문법
function sum2() {
    return [...arguments].reduce((pre, cur) => pre+cur, 0);
}
console.log(sum2(1,2,3));   // 6

// Rest 파라미터
const sum3 = (...arr) => arr.reduce((pre, cur) => pre+cur, 0);
console.log(sum3(1,2,3));   // 6

// 이터러블이 아닌 유사 객체는 스프레드 문법을 사용할 수 없다
// 스프레드 문법은 이터러블 한정으로 사용 가능하다
const arr2 = [...arrayLike];    // TypeError: arrayLike is not iterable

// 대신 Array.from 메서드를 사용한다
// 유사 배열 객체, 이터러블을 인수로 받아 배열로 변환해 반환하는 ES6 도입 메서드
const reArr = Array.from(arrayLike);
console.log(Array.isArray(reArr));    // true
```

# 스프레드 프로퍼티

> `객체 리터럴 내부` 에서 프로퍼티 목록으로 스프레드 문법을 사용하는 경우
> 

스프레드 프로퍼티 제안은 **일반 객체를 대상으로도 스프레드 문법의 사용을 허용**한다.

- Object.assign

```jsx
// ES5
// Object.assign
// 프로퍼티 키가 중복되는 경우 뒤의 프로퍼티가 우선권을 갖음

// 1. 객체 병합
const merged = Object.assign({}, {name:`kang`, age:22}, {name:`lee`, job:`student`});   // { name: 'lee', age: 22, job: 'student' }
console.log(merged);    

// 2. 특정 프로퍼티 변경
const changed = Object.assign({}, {name:`kang`, age:22}, {age:30});    // { name: 'kang', age: 30 }
console.log(changed);

// 3. 프로퍼티 추가
const added = Object.assign({}, {name:`kang`, age:22}, {job:`student`});   // { name: 'kang', age: 22, job: 'student' }
console.log(added);
```

- 스프레드 프로퍼티 문법

```jsx
// ES6
// 스프레드 문법
// 프로퍼티 키가 중복되는 경우 뒤의 프로퍼티가 우선권을 갖음

const user1 = {
    id: `khy`,
    pass: 731
};
const user2 = {
    id:`khy`,
    pass: 999
};

// 병합
const merged2 = {...user1, ...user2};
console.log(merged2);   // { id: 'khy', pass: 999 }

// 변경
const changed2 = {...user1, id : `lee`};
console.log(changed2);  // { id: 'lee', pass: 731 }

// 추가
const added2 = {...user1, address:`sejong`};
console.log(added2);    // { id: 'khy', pass: 731, address: 'sejong' }

// 복사
const copy = {...user1};
const copy2 = {...user2};
```