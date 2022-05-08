# 배열 고차 함수

> 고차 함수(Higher-Order Function)
> 

함수를 인수로 전달받거나 함수를 반환하는 함수. 외부 상태의 변경이나 가변(mutable)데이터를 피하고 `불변성(immutability)`을 지향하는 함수형 프로그래밍에 기반을 두고 있다.

함수형 프로그래밍은

- **조건문과 반복문을 제거**하여 복잡성을 해결하고
- **변수의 사용을 억제**하여 상태 변경을 피한다.

자바스크립트는 고차 함수를 다수 지원하며, 특히 배열은 매우 유용한 고차 함수를 제공한다.

# Array.prototype.sort

> 배열의 요소를 `정렬`하여 `정렬된 배열`을 반환한다. **원본 배열을 직접 변경**한다.
> 
- 기본적으로 문자열을 정렬하므로 *배열의 요소가 문자열이 아닐 경우 콜백 함수(비교 함수)를 인수로 전달*해야 동일하게 동작한다.
- `오름차순` 정렬이 기본값이다. 내림차순의 경우 sort로 정렬 → reverse로 뒤집어야 한다.

### 문자열

```jsx
// 1. 영어

const foods = [`rice`, `chicken`, `pasta`];
// 오름차순(ascending) 정렬
foods.sort();
// 원본 배열을 직접 변경
console.log(foods);    // [ 'chicken', 'pasta', 'rice' ]

// 2. 한글

const fruits = [`사과`, `바나나`, `멜론`];
console.log(fruits.sort());    // [ '멜론', '바나나', '사과' ]
```

### 숫자

sort 메서드는 `유니코드 코드 포인트`의 순서를 따른다. 배열의 요소가 **숫자 타입일 경우 일시적으로 문자열로 변환 후** 정렬한다. 이 때 예기치 못한 결과가 나온다. 100이 2보다 작은 유니코드 코드 포인트를 갖기 때문이다.

```jsx
// 3. 숫자

// 문자열 변환 ->유니코드 코드 포인트 기준 정렬
// 예기치 못한 결과
console.log([40,100,1,2,5].sort());    // [ 1, 100, 2, 40, 5 ]
```

> `정렬 순서를 정의하는**비교 함수**`를 인수로 전달하여 문자열 때와 동일하게 동작하도록 해결한다.
> 

반환값이

- 0보다 작을 경우 : 첫 번째 인수를 우선 정렬
- 0보다 큰 경우 : 두 번째 인수를 우선 정렬

하는 비교 함수를 전달한다.

```jsx
const points = [40,100,1,2,5];

// 오름차순 : 반환값이 0보다 작으면 a 우선 정렬
points.sort((a,b) => a-b);
console.log(points);    // [ 1, 2, 5, 40, 100 ]

// 내림차순 : 반환값이 0보다 크면 b 우선 정렬
points.sort((a,b) => b-a);
console.log(points);    // [ 100, 40, 5, 2, 1 ]
```

### 객체

배열의 요소가 객체일 경우, 특정 프로퍼티 키를 기준으로 정렬할 수 있다. 밑의 예제에서는 id를 정렬할 것인지 content를 정렬할 것인지 프로퍼티 키를 인수로 넘겨줌으로써 정렬할 수 있다.

```jsx
// 4. 객체

const obj = [
    {id : 3, content : `b`},
    {id : 1, content : `c`},
    {id : 2, content : `a`},
]
// 비교 함수 (매개변수는 프로퍼티 키)
function compare(key) {
    // 프로퍼티 값이 문자열일 경우 산술 연산으로 비교 불가(NaN 나옴)
    // 어차피 비교 함수는 1/0/-1만 뱉으면 되므로 대신 비교 연산을 사용한다
    return(a,b) => (a[key] > b[key] ? 1 : (a[key] < b[key] ? -1 : 0));
}

// 프로퍼티 키 `id`를 기준으로 오름차순 정렬
obj.sort(compare(`id`));
console.log(obj);
/* [
    { id: 1, content: 'c' },
    { id: 2, content: 'a' },
    { id: 3, content: 'b' }
] */

// 프로퍼티 키 `user`을 기준으로 오름차순 정렬
obj.sort(compare(`content`));
console.log(obj);
/* [
    { id: 2, content: 'a' },
    { id: 3, content: 'b' },
    { id: 1, content: 'c' }
] */
```

## Array.prototype.forEach

조건문이나 반복문은 로직의 흐름을 이해하기 어렵게 한다. forEach 메서드는 `for문을 대체`할 수 있는 고차 함수이다.

> forEach 메서드는 반복문을 추상화한 고차 함수이다. 내부에서 반복문을 통해 자신을 호출한 배열을 순회하면서 수행해야 할 작업을 *콜백 함수* 로 전달받아 반복 호출한다.
> 
- 첫 번째 매개변수 : 콜백 함수
- 두 번째 매개변수 : 콜백 함수 내부에서 this로 사용할 객체 (선택사항)

```jsx
// 1. for문을 사용하는 경우

const numbers = [1,2,3];
const pows = [];

for(let i =0; i<numbers.length; i++) {
    pows.push(numbers[i] ** 2);
}

console.log(pows);    // [ 1, 4, 9 ]

// 2. forEach 메서드를 사용하는 경우

const numbers2 = [1,2,3];
const pows2 = [];

numbers2.forEach(item => pows2.push(item ** 2));
console.log(pows2);    // [ 1, 4, 9 ]
```

예를 들어, 위 예제에서 forEach 메서드는 numbers 배열의 모든 요소를 순회하며 콜백 함수를 반복해서 호출한다.

- 1이라는 요소 하나에 콜백 함수 한 번
- 2라는 요소에 콜백 함수 한 번
- 3이라는 요소에 콜백 함수 한 번

numbers 배열의 요소가 3개이므로 콜백 함수도 3번 호출된다.

### 콜백 함수에 인수 전달하기

애초에 forEach 메서드로 들어오는 인수가 콜백 함수지만은, 콜백 함수 자체에도 인수를 전달하며 넘길 수 있다.

1. forEach 메서드를 호출한 배열의 `요소 값`
2. forEach 메서드를 호출한 배열의 `인덱스`
3. forEach 메서드를 호출한 배열 그 자체(`this`)

위 예제는 두 번째 인수와 세 번째 인수를 생략하여 요소 값만 변경했었다.

```jsx
[1,2,3].forEach((item, index, arrThis) => {
    console.log(`요소 값 : ${item}\n인덱스 : ${index}\nthis : ${JSON.stringify(arrThis)}\n`);
});

/* 요소 값 : 1
인덱스 : 0
this : [1,2,3]

요소 값 : 2
인덱스 : 1
this : [1,2,3]

요소 값 : 3
인덱스 : 2
this : [1,2,3] */
```

### 콜백함수 내부의 this 지정하기

> forEach 메서드의 두 번째 인수로 콜백 함수 내부에서 this로 사용할 객체를 전달할 수 있다.
> 

콜백 함수의 this는 항상 이슈가 되는 문제로, 콜백 함수가 일반 함수로 호출될 경우 콜백 함수 내부의 this와 고차 함수의 this가 일치하지 않는 현상이 발생한다. 이를 두 번째 매개변수에 this를 직접 전달하면서 해결해보겠다.

```jsx
// 콜백 함수 내부 this 문제

class Numbers {
    numberArray = [];

    multiply(arr) {
        arr.forEach(function(item) {
            this.numberArray.push(item*item);   // TypeError: Cannot read properties of undefined (reading 'numberArray')
        });
    }
}

// forEach 두 번째 매개변수에 multiply 메서드 내부의 this를 전달하며 해결

class Numbers2 {
    numberArray = [];

    multiply(arr) {
        arr.forEach((function(item) {
            this.numberArray.push(item*item);  
        }),this);
    }
}

const numbers = new Numbers2();
numbers.multiply([1,2,3]);
console.log(numbers.numberArray);   // [ 1, 4, 9 ]
```

당연하겠지만 ES6의 화살표 함수를 사용하는 편이 더 낫다.

```jsx
// 화살표 함수
multiply(arr) {
    arr.forEach(item => this.numberArray.push(item * item));
}
```

### forEach 메서드의 내부 로직

폴리필(polyfill, 저사양 브라우저를 위해 최신 사양 기능을 이전 버전의 코드로 구현하여 추가) 을 통해 forEach 메서드의 동작을 알아보자 : 

```jsx
// Array.prototype에 forEach 메서드가 존재하지 않는 경우, 폴리필을 추가
if (!Array.prototype.forEach) {
    Array.prototype.forEach = function(callback, thisArg) {

        // 첫 번째 인수가 함수가 아니면 TypeError
        if (typeof callback !== `function`) {
            throw new TypeError(`${callback} is not a function`);
        }
        // 두 번째 인수(대체할 this)를 받지 못하면 전역 객체를 this로 사용
        thisArg = thisArg || window;
        
        // for문으로 배열을 순회하면서 콜백 함수를 호출
        for(var i = 0; i<this.length; i++) {
            
        // call 메서드로 thisArg(대체할 this)를 전달하면서 콜백 함수를 호출
        // 인수 : 1. 배열 요소 2. 인덱스 3. 배열 자체(this)
            callback.call(thisArg, this[i], i, this);
        }
    };
}
```

forEach 메서드도 내부적으로는 for문을 통해 배열을 순회하지만 이를 내부로 은닉하여 로직의 흐름을 이해하기 쉽게 *보이게*한다는 것에 의미가 있다.

### 기타 특징

- forEach 메서드는 for문과 달리 break나 continue 문을 사용할 수 없다. (배열의 모든 요소를 빠짐없이 계속해서 순회해야만 한다.)

```jsx
// break문 사용 불가
[1,2,3].forEach(item => {
    console.log(item);
    if (item > 1) break;    // SyntaxError: Illegal break statement
})

// continue 문 사용 불가
[1,2,3].forEach(item => {
    console.log(item);
    if (item > 1) continue;    // SyntaxError: Illegal continue statement: no surrounding iteration statement
})
```

- 희소 배열일 경우 ‘빈 요소’는 순회 대상에서 제외된다.

```jsx
// forEach 메서드는 (희소 배열의 경우)존재하지 않는 요소를 순회 대상에서 제외한다

const arr = [1, ,2]

for (var i = 0; i < arr.length; i++) {
    console.log(arr[i]);    // 1, undefined, 2
}

arr.forEach(item => console.log(item));    // 1,2
```

forEach 메서드는 for문에 비해 성능은 별로지만 **가독성이 좋다**. 따라서 엄청나게 스케일이 큰 배열이 아니라면 forEach 메서드를 사용하는 것이 더 좋다.

## Array.prototype.map

> 자신을 호출한 배열의 모든 요소를 순회하면서 인수로 전달받은 콜백 함수를 반복 호출하여 **콜백 함수의 반환값들로 구성된 `새로운 배열`을 반환**한다. **원본 배열은 변경되지 않는다.**
> 

```jsx
const numbers = [1,4,7,12,44];

// 콜백 함수의 반환값들로 구성된 새로운 배열을 반환
const roots = numbers.map(item => item * item);
console.log(roots);    // [ 1, 16, 49, 144, 1936 ]

// 원본 배열을 변경하지 않는다
console.log(numbers);   // [ 1, 4, 7, 12, 44 ]
```

![map](https://user-images.githubusercontent.com/97890886/166671194-38f438e8-df5b-41fa-88b9-b49d7087cb82.png)


**map 메서드를 호출한 배열의 length 프로퍼티 값은 map 메서드가 생성하여 반환하는 배열의 length 프로퍼티 값과 같다. (1:1 mapping의 산물)**

### 콜백 함수에 인수 전달하기

map 메서드의 콜백 함수는 map 메서드를 호출한 배열의 `요소값`, `인덱스`, `this`를 순차적으로 전달받을 수 있다. (매개변수를 세 개 갖는다)

```jsx
[`a`,10,-1].map((item,index,arr) => {
    console.log(`요소값: ${item}, 인덱스: ${index}, this:${JSON.stringify(arr)}`);
    return item;    // forEach와는 다르게 반환값이 있음
})

/* 요소값: a, 인덱스: 0, this:["a",10,-1]
요소값: 10, 인덱스: 1, this:["a",10,-1]
요소값: -1, 인덱스: 2, this:["a",10,-1] */
```

### 콜백 함수 내부의 this 지정하기

```jsx
class Prefix {
    constructor(value) {
        this.value = value;
    }
   
    add(arr) {
        // this를 지정해 주지 않는 경우 이 내부의 this는 undefined
        return arr.map(function(item) {
            return this.value +`-`+ item;
        }, this);
    }
}

const prerix = new Prefix(`webkit`);
const result = prerix.add([`user`, `select`]);
console.log(result);    // [ 'webkit-user', 'webkit-select' ]
```

물론 화살표 함수를 쓰는 것이 베스트이긴 하다.

### forEach VS map?

- 공통점 : 둘 다 자신을 호출한 배열의 모든 요소를 순회하면서 인수로 전달받은 콜백 함수를 호출
- 차이점 :
    - forEach의 반환값은 항상 undefined이다 → 단순히 반복문 로직을 대체하기 위한 고차 함수
    - map은 콜백 함수의 반환값들로 구성된 새로운 배열을 반환한다 → 요소값을 다른 값으로 mapping한 `새로운 배열을 생성`하기 위한 고차 함수
    

## Array.prototype.filter

> 자신을 호출한 배열의 모든 요소를 순회하면서 인수로 전달받은 콜백 함수를 반복 호출하되, **콜백 함수의 반환값이 `true`인 요소로만 구성된 새로운 배열**을 반환한다. **원본 배열은 변경되지 않는다.**
> 

콜백 함수에 인수 전달하기, 콜백 함수 내부의 this 지정하기는 위 2개와 겹치므로 패스하겠다.

```jsx
const numbers = [1,2,3,4,5];

// item을 2로 나눈 나머지를 반환하는 콜백 함수
// 홀수의 경우 1이 반환됨 -> 1은 true 취급 -> 홀수만 필터링됨
const odds = numbers.filter(item => item % 2);
console.log(odds);    // [ 1, 3, 5 ]
```

![filter](https://user-images.githubusercontent.com/97890886/166671241-d85a11d3-099f-496e-a25a-30711c732f4e.png)


filter 메서드가 생성하여 반환한 새로운 배열의 length 프로퍼티 값은 filter 메서드를 호출한 배열의 length 프로퍼티 값과 `같거나` `작다`.

### 자신을 호출한 배열에서 특정 요소 제거하기

filter은 forEach, map 메서드와 마찬가지로 동작하지만 forEach는 단순 로직(반환값x), map은 결과를 반환, filter은 말 그대로 필터처럼 작동한다-true값만 반환한다-. 즉 조건을 걸어 그 조건에 맞는 것만 걸러낼 수 있다는 소리다-반대로 말하면 조건에 맞지 않는 것을 제거할 수 있다-.

```jsx
class User {
    constructor() {
        this.users = [
            {id : 1, name : `kang`},
            {id : 2, name : `lee`},
            {id : 3, name : `nya`}
        ];
    }

    // 전달받은 id에 맞는 요소 추출
    findId(id) {
        // id가 일치하는 경우(true)만 반환
        return this.users.filter(u => u.id === id)
    }

    // 전달받은 id를 제거후 남은 요소 추출
    removeId(id) {
        // id가 불일치하는 경우(true) = 그 id 빼고 = 그 id를 제거하고 반환
        this.users = this.users.filter(u => u.id !== id)
        return this.users;
    }
}

const user = new User();

let me = user.findId(1);
console.log(me);    // [ { id: 1, name: 'kang' } ]

me = user.removeId(3);
console.log(me);    // [ { id: 1, name: 'kang' }, { id: 2, name: 'lee' } ]
```

filter 메서드로 특정 요소를 제거할 경우, **중복된 모든 요소가 제거**된다. 하나만 제거하려면

1. index0f 메서드로 특정 요소의 인덱스를 먼저 취득한 후
2. splice 메서드를 사용

## Array.prototype.reduce

> 자신을 호출한 배열의 모든 요소를 순회하며 인수로 전달받은 콜백 함수를 반복 호출하고, 콜백 함수의 반환값을 다음 순회 시에 콜백 함수의 첫 번째 인수로 전달하면서 결과적으로 **하나의 결과값**을 만들어 반환한다.
> 

```jsx
// reduce 메서드
// 첫 번째 매개변수 : 콜백 함수
// 두 번째 매개변수 : 초깃값 (초깃값이 주어지지 않은 경우 배열의 첫 요소와 둘 요소를 동시에 데려옴)

// 콜백 함수
// 첫 번째 매개변수 : 초깃값 / 이전 반환값
// 두 번째 매개변수 : reduce 메서드를 호출한 배열의 요소값
// 세 번째 매개변수 : 인덱스
// 네 번째 매개변수 : 배열 자체(this)

const sum = [1,2,3,4].reduce((accumulator,currentValue)=>accumulator+currentValue, 0);

console.log(sum);
```

내부 작동을 자세히 서술하면 대충 다음과 같다.

1. 초깃값과 배열의 첫 번째 요소값(인덱스0)을 콜백 함수에게 인수로 전달하면서 호출
2. 1의 반환값과 배열의 두 번째 요소값(인덱스1)을 콜백 함수에게 인수로 전달하면서 호

![reduce](https://user-images.githubusercontent.com/97890886/167278583-f22f0fec-f921-40f5-bbd2-65ebbdf620f0.png)

결과적으로 하나의 결과값을 반환한다. → 자신을 호출한 배열의 모든 요소를 순회하며 하나의 결과값을 구해야 할 때 사용한다.

> 모든 배열의 고차 함수(map, filter, every, find 등)는 reduce로 구현할 수 있다.
> 

### 평균 구하기

```jsx
// 평균 구하기
// 마지막 순회일 경우 누적값의 평균 반환, 아닐 경우 누적값 반환
const values = [1,2,3,4,5,6]
const avg = values.reduce((acc,cur,i,{length}) => {
    return i === length - 1 ? (acc+cur) / length : acc+cur; 
})
```

### 최댓값 구하기

```jsx
// 최대값 구하기
const max = values.reduce((acc,cur) => acc>cur ? acc : cur);
// Math.max 메서드를 권장
```

### 요소의 중복 횟수 구하기

```jsx
// 요소의 중복 횟수 구하기
const obj = [`apple`, `banana`, `rice`, `apple`,`apple`, `rice`];
const count = obj.reduce((acc,cur) => {
    // 첫 번째 순회 : 초깃값(acc)은 빈 객체 {} 현 요소(cur)는 `apple`
    // 빈 객체 {}에 cur이 프로퍼티 키로 동적 할당 {apple: }
    // apple 프로퍼티는 아직 존재하지 않으므로 undefined(false) -> 단축 표현에 의해 0됨 => +1로 초기화됨
    // 결과적으로 {apple : 1}이 됨
    
    // 네 번째 순회 : 초깃값(acc)은 {apple:1, banana:1, rice:1}, 현 요소(cur)은 `apple`
    // apple 프로퍼티가 존재(1, true) -> 단축 표현에 의해 1+1로 2됨
    // 결과적으로 {apple:2, banana:1, rice:1} 이 됨
    return count = acc[cur] = (acc[cur] || 0) + 1
}, {});
```

### 중첩 배열 평탄화

```jsx
// 중첩 배열 평탄화
// concat은 요소가 배열일 경우 해체하여 추가한다
const flatten = values.reduce((acc, cur) => acc.concat(cur), []);
// flat 메서드를 권장
```

### 중복 요소 제거하기

```jsx
// 중복 요소 제거
// 배열 자체의 인덱스와 순회중인 요소의 인덱스가 같으면 -> 처음 순회하는 중복X 값 : 누산기 unnique에 추가
// 이런식으로 unique(초깃값 [])에 처음 순회하는 값만 담아 반환
const result = values.reduce((unique, val, i, _values) => {
    _values.indexOf(val) === i ? [...unique, val] : unique
}, []);

// filter 메서드를 권장
const result2 = values.filter((val, i, _values) => _values.indexOf(val) ===i);

// Set(중복되지 않는 유일한 값들의 집합) 사용을 권장
const result3 = [...new Set(values)];
```

> reduce 메서드의 초깃값(둘째 인수)은 생략 가능하지만, `생략하지 않고 전달`하는 것을 권장한다
> 

```jsx
// 초깃값 생략
const sum = [].reduce((acc,cur) => acc+cur);
console.log(sum);   // TypeError: Reduce of empty array with no initial value

// 초깃값 생략하지 않고 전달
const sum2 = [].reduce((acc,cur) => acc+cur, 0);
console.log(sum2);  // 0
```

```jsx
// 객체의 특정 프로퍼티 값을 합산
const products = [
    {id: 1, price: 100,},
    {id: 2, price: 200,},
    {id: 3, price: 300,},
];

const priceSum = products.reduce((acc, cur) => acc.price + cur.price);
// 첫 번째 순회 : acc는 {id: 1, price: 100,}, cur은 {id: 2, price: 200,}
// 두 번째 순회 : acc는 300, cur은 {id: 3, price: 300,}
// 두 번째 순회에서 acc가 숫자 값이기 때문에 . 연산자로 접근이 불가능 - undefined

console.log(priceSum);    // NaN

const priceSum2 = products.reduce((acc, cur) => acc + cur.price, 0);
// 첫 번째 순회 : acc는 0, cur은 {id: 1, price: 100,}
// 두 번째 순회 : acc는 100, cur은 {id: 2, price: 200,}
// 세 번째 순회 : acc는 300, cur은 {id: 3, price: 300,}

console.log(priceSum2);    // 600

// 즉, 아다리가 맞게 해 줘라
```

## Array.prototype.some

> 자신을 호출한 배열의 요소를 순회하면서 인수로 전달된 콜백 함수를 호출하되, 콜백 함수는 `조건`이 정의되어 있으며 이 조건을 만족하는 요소가 하나라도 있으면(반환값이 한 번이라도 `true`면) `true`를 반환한다.
> 

forEach, map, filter와 마찬가지로 콜백 함수는 요소값, 인덱스, this를 인수로 받는다.

```jsx
const arr = [1,5,17,-200,50];
const obj = [`kang`, `lee`, `kim`];
const data = [
    {id:1, pass:0000},
    {id:2, pass:0001},
    {id:3, pass:0002},
]

// 배열의 요소 중 10보다 큰 요소가 1개 이상 존재하는지 확인
console.log(arr.some(item => item>10));    // t

// 배열의 요소 중 `kang`이 1개 이상 존재하는지 확인
console.log(obj.some(item => item === `kang`));    // t

// 배열의 요소 중 특정 프로퍼티 값이 존재하는지 확인
console.log(data.some(item => item.pass === 0000));    // t

// 빈 배열에게 호출됐을 경우 언제나 false
console.log([].some(item => item %2));    // f
```

OR과 같은 원리네

## Array.prototype.every

> 콜백 함수의 반환값이 모두 참이어야만 `true`를 반환한다. 빈 배열일 경우 언제나 true임에 주의하라.
> 

## Array.prototype.find

ES6 도입

> 콜백 함수의 반환값이 `true인 첫 번째 요소`를 반환한다.
> 

filter 메서드는 true인 요소만 추출하여 새로운 **배열**을 만들어 반환하지만, find는 단 하나의 요소값만을 반환한다. 즉 filter의 return값은 언제나 배열이고 find는 값이다.

## Array.prototype.findIndex

ES6 도입

> 콜백 함수의 반환값이 true인 첫 번째 요소의 `인덱스`를 반환한다
> 

## Array.prorotype.flatMap

Es10 도입

> map 매서드를 통해 생성된 새로운 배열을 평탄화한다. (map과 flat을 순차적으로 실행한것과 동일효과)
> 

단, flat 메서드처럼 인수를 전달하여 평탄화의 깊이를 지정할 수는 없고 한 단계만 평탄화 한다.

```jsx
const arr = [`Hello`, `World`];

// map만 실행 : 배열 내 배열 생김(고차원)
console.log(arr.map(x => x.split(``)));
// [ [ 'H', 'e', 'l', 'l', 'o' ], [ 'W', 'o', 'r', 'l', 'd' ] ]

// map과 flat을 순차적으로 실행
console.log(arr.map(x => x.split(``)).flat());
// ['H', 'e', 'l', 'l', 'o', 'W', 'o', 'r','l', 'd']

// flatMap 실행
console.log(arr.flatMap(item => item.split(``)));
// ['H', 'e', 'l', 'l', 'o', 'W', 'o', 'r','l', 'd']
```