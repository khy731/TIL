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

- forEach 메서드는 for문과 달리 break나 continue 문을 사용할 수 없다. (배열의 모든 요소를 빠짐없이 계속해서 순회해야만 한다.) 희소 배열일 경우 ‘빈 요소’는 순회 대상에서 제외된다.
- forEach 메서드는 for문에 비해 성능은 별로지만 **가독성이 좋다**. 따라서 엄청나게 스케일이 큰 배열이 아니라면 forEach 메서드를 사용하는 것이 더 좋다.