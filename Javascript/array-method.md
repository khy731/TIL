# 배열 메서드

`Array 생성자 함수`는 다양한 빌트인 메서드(정적 메서드)를 제공하며, `Array.prototype`(배열 객체의 프로토타입)은 다양한 프로토타입 메서드를 제공한다.

> 배열 메서드는 output을 반환하는 패턴이 두 가지이다.
> 
- `mutator method` : 원본 배열(배열 메서드를 호출한 배열이자, 배열 메서드의 구현체 내부에서 this가 가리키는 객체)을 **직접 변경**하는 메서드
- `accessor method` : 원본 배열을 직접 변경하지 않고 **새로운 배열을 생성하여** 반환하는 메서드

원본 배열을 직접 변경하는 메서드는 부수 효과(외부 상태를 직접 변경)가 있으므로 accessor method의 사용을 권장한다.

```jsx
const arr = [1,2,3];

// mutator method
arr.push(4);
console.log(arr);   // [ 1, 2, 3, 4 ]

// accessor method
const result = arr.concat(5);
console.log(result);    // [ 1, 2, 3, 4, 5 ]
console.log(arr);       // [ 1, 2, 3, 4 ]
```

## Array.isArrray

> 전달된 인수가 배열이면 `true`, 배열이 아니면 `false`를 반환
> 

Array 생성자 함수의 정적 메서드.(앞에서 살펴봤던 Array.of과 Array.from도)

```jsx
// true
Array.isArray([1,2,3]);
Array.isArray([]);
Array.isArray(new Array());

// false
Array.isArray();
Array.isArray({});
Array.isArray(null);
Array.isArray(`Array`);
Array.isArray(true);
Array.isArray({ a:1, length:1 });
```

## Array.prototype.index0f

> 원본 배열에서 인수로 전달된 요소를 검색하여 `인덱스`를 반환
> 
- 중복되는 요소가 여러 개 있다면 첫 번째로 검색된 요소의 인덱스를 반환
- 요소가 존재하지 않다면 -1 반환

```jsx
const arr = [1,4,4,17,71];

arr.indexOf(1);    // 0
arr.indexOf(4);    // 1
arr.indexOf(99);   // -1

// 배열에 특정 요소가 존재하는지 확인할 때 유용
const foods = [`egg`, `tomato`, `rice`];

// 배열에 `orange`요소가 존재하는지 확인
// 존재하지 않으면 추가한다
if (foods.indexOf(`orange`) === -1) {
    foods.push(`orange`);
}

console.log(foods);    // [ 'egg', 'tomato', 'rice', 'orange' ]

// ES7의 Array.prototype.includes 메서드가 가독성이 더 좋다
if (!foods.includes(`bread`)) {
    foods.push(`bread`);
}

console.log(foods);    // [ 'egg', 'tomato', 'rice', 'orange', 'bread' ]
```

배열에 특정 요소가 존재하는지 확인할 때 유용하다. ES7에서 새로 도입된 Array.prototype.includes 메서드를 사용하면 가독성이 더 좋다.

## Array.prototype.push

> 인수로 전달받은 모든 값을 원본 배열의 마지막 요소들로 `추가`하고, 변경된 `length 프로퍼티 값`을 반환한다. **원본 배열을 직접 변경**하는 메서드이다.
> 

```jsx
const arr = [1];

// 1. push 메서드
const result = arr.push(6,18);
console.log(result);    // 3
console.log(arr);       // [ 1, 6, 18 ]

// 2. length 프로퍼티 사용
// arr.push(33)와 동일하게 동작
arr[arr.length] = 33;
console.log(arr);   // [ 1, 6, 18, 33 ]

// 3. ES6 스프레드 문법
// arr.push(45)와 동일하게 동작
const newArr = [...arr, 45];
console.log(newArr);    // [ 1, 6, 18, 33, 45 ]
```

push 메서드는 성능 면에서 떨어진다.

- 추가할 요소가 하나뿐이라면 length 프로퍼티를 사용하는 것이 더 빠르다.
- 부수 효과가 발생하기 때문에 위험하다.

—> ES6의 `스프레드 문법`을 사용하는 것을 권장한다.

## Array.prototype.pop

> 원본 배열에서 마지막 요소를 `제거`하고, `제거한 요소`를 반환한다. 원본 배열이 빈 배열일 경우 `undefined`를 반환한다. **원본 배열을 직접 변경**한다.
> 

```jsx
const arr = [1,4,11,20];

const result = arr.pop();
console.log(result);    // 20
console.log(arr);       // [ 1, 4, 11 ]
```

### push 메서드와 pop 메서드로 `stack` 구현하기

<aside>
👉 자료구조 스택(stack)

</aside>

![array-stack](https://user-images.githubusercontent.com/97890886/166225048-8a4e1368-de6d-4cab-9b1b-9472bcd64b44.png)

- 후입선출(LIFO - Last In Fist Out, 마지막에 추가된 항목이 제일 먼저 제거된다) : 쌓여있는 접시와 비슷한 원리. 맨 끝의 데이터만 조작 가능하다. 끝에만 삽입(push) 가능 / 끝의 데이터만 꺼내기(pop) 가능
- 언제나 마지막에 밀어 넣은 최신 데이터를 취득한다.

> stack을 생성자 함수로 구현하기
> 

```jsx
// 즉시실행함수(생성자 함수+프로토타입)으로 스택 구현
const Stack = (function() {

// 1. 생성자 함수
// 매개변수 기본값 설정
function Stack(array = []) {

    // 전달받은 인수가 배열이 아닐 경우 에러 처리
    if (!Array.isArray(array)) {
        throw new TypeError(`${array} is not an array.`);
    }
    this.array = array;
}

// 2. 프로토타입
Stack.prototype = {
    // 프로토타입을 교체했으므로 constructor 바인딩
    constructor : Stack,

    // 1. 스택의 끝에 데이터 삽입
    push(value) {
        return this.array.push(value);
    },
    // 2. 스택 끝의 데이터 꺼내기
    pop() {
        return this.array.pop();
    },
    // 3. 복사본 배열 반환
    entries() {
        return [...this.array];
    }
};

return Stack;
}());

const stack = new Stack([1,4,17]);

stack.push(30);
console.log(stack.entries());   // [ 1, 4, 17, 30 ]

stack.pop();
console.log(stack.entries());   // [ 1, 4, 17 ]
```

> stack을 클래스로 구현하기
> 

```jsx
class Stack {
    #array;

    constructor(array = []) {
        if (!Array.isArray(array)) {
            throw new TypeError(`${array} is not an array`)
        }
        this.#array = array;
    }

    push(value) {
        return this.#array.push(value);
    }
    pop() {
        return this.#array.pop();
    }
    entries() {
        return [...this.#array]
    }
}

const stack = new Stack([1,5,17]);

stack.push(22);
console.log(stack.entries());   // [ 1, 5, 17, 22 ]

stack.pop();
stack.pop();
console.log(stack.entries());   // [ 1, 5 ]

const obj = {
    a : 1,
    b : 2,
};

const notArray = new Stack(obj);    // TypeError: [object Object] is not an array
```

## Array.prototype.unshift

> 인수로 전달받은 모든 값을 원본 배열의 `선두에 요소로 추가`하고 `length 프로퍼티 값`을 반환한다. **원본 배열을 직접 변경**한다.
> 

```jsx
const arr = [1,5,7,];

// 1. unshift 메서드
let result = arr.unshift(33,2);
console.log(result);    // 5
console.log(arr);       // [ 33, 2, 1, 5, 7 ]

// 2. ES6 스프레드 문법
const newArr = [12, ...arr];
console.log(newArr);    // [ 12, 33, 2, 1, 5, 7 ]
```

부수 효과가 있으므로 선두에 요소를 추가할 때는 ES6의 `스프레드 문법`을 사용하는 것을 권장한다. 함수 호출 없이 표현식으로만 가능하다.

## Array.prototype.shift

> 원본 배열에서 `첫 번째 요소를 제거`하고 `제거한 요소`를 반환한다. 원본 배열이 빈 배열이면 `undefined`를 반환한다. **원본 배열을 직접 변경**한다.
> 

```jsx
const arr = [2,4,6];

let result = arr.shift();
console.log(result);    // 2
console.log(arr);       // [ 4, 6 ]
```

### push 메서드와 shift 메서드로 `Queue` 구현하기

<aside>
👉 자료구조 큐 (Queue)

</aside>

![array-queue](https://user-images.githubusercontent.com/97890886/166225084-02a38d11-bf58-4820-83b5-f219b6fea81a.png)

- 선입선출(FIFO-First In First Out, 처음에 추가된 항목이 제일 먼저 제거된다) : 대기줄과 비슷한 원리.  데이터는 큐의 끝에만 삽입 가능하고, 큐의 앞에서만 삭제할 수 있다.
- 스택과 달리, 언제나 데이터를 밀어 넣은 *순서대로* 데이터를 취득한다.

> 생성자 함수로 큐 구현
> 

```jsx
const Queue = (function() {
function Queue(array = []) {
    if (!Array.isArray(array)) {
        throw new TypeError(`${array} is not an array`);
    }
    this.array = array;
}

Queue.prototype = {
    constructor : Queue,

    enqueue(value) {
        return this.array.push(value);
    },
    dequeue() {
        return this.array.shift();
    },
    entries() {
        return [...this.array];
    }
}

return Queue;
}());

const queue = new Queue([11,22,33]);

queue.enqueue(44);
console.log(queue.entries());   // [ 11, 22, 33, 44 ]

queue.dequeue();
console.log(queue.entries());   // [ 22, 33, 44 ]
```

> 클래스로 큐 구현
> 

```jsx
class Queue {
    #array;

    constructor(array = []) {
        if (!Array.isArray(array)) {
            throw new TypeError(`${array} is not an array`);
        }
        this.#array = array;
    }

    enqueue(value) {
        return this.#array.push(value);
    }
    dequeue() {
        return this.#array.shift();
    }
    entries() {
        return [...this.#array];
    }
}

const queue = new Queue([1,2,3]);

queue.enqueue(4);
console.log(queue.entries());   // [ 1, 2, 3, 4 ]

queue.dequeue();
console.log(queue.entries());   // [ 2, 3, 4 ]
```

## Array.prototype.concat

> 인수로 전달된 값들(원시값 혹은 배열)을 원본 배열의 마지막 요소로 `추가`한 `새로운 배열`을 반환한다.  인수가 배열일 경우 배열을 해체하여 새 배열의 요소로 추가한다. 원본 배열은 변경되지 **않는다**.
> 

```jsx
const arr1 = [1,2];
const arr2 = [3,4];

// arr2를 해체하여 마지막 요소로 추가한 새로운 배열 반환
let result = arr1.concat(arr2);
// Number 5를 마지막 요소로 추가한 새로운 배열 반환
result = result.concat(5);

console.log(result);    // [ 1, 2, 3, 4, 5 ]
console.log(arr1);      // [ 1, 2 ]
```

push와 unshift는 concat 메서드로 대체 가능하다.

### push와 unshift VS concat

- pusth와 unshift는 `원본 배열`을 저장해 두어야 한다(변수에 할당받아놔야 한다).
- concat 메서드는 `반환값`을 저장해 두어야 한다.
- 인수로 전달받은 값이 배열일 경우 push와 unshift는 배열을 **그대로** 삽입하지만 concat은 **해체하여** 저장한다.

```jsx
// 1. push와 unshift
// 원본 배열을 저장해놔야 한다
const arr1 = [1,2];

arr1.push(3);
arr1.unshift(0);

// 원본 배열이 통째로 바뀌기 때문에 원본 배열을 저장해놨어야 사용 가능하다
console.log(arr1);    // [ 0, 1, 2, 3 ]

// 2. concat
// 반환값을 저장해놔야 사용 가능하다
let result = [1,2].concat(3);
console.log(result);    // [ 1, 2, 3 ]

// 3. 인수가 배열인 경우
const arr2 = [10,11];

// push와 unshift는 배열을 그대로 삽입
result = arr1.push(arr2);
console.log(arr1);     // [ 0, 1, 2, 3, [ 10, 11 ] ]

// concat은 배열을 해체하여 삽입
result = arr1.concat(arr2);
console.log(result);    // [ 0, 1, 2, 3, [ 10, 11 ], 10, 11 ]
```

그러나 이 모든 메소드들은 결국 ES6의 스프레드 문법으로 대체된다.

## Array.prototype.splice

push, pop, unshift, shift 메서드는 전부 mutator method이고 요소의 `처음`이나 `마지막`만을 다뤘다.

> splice 메서드도 mutator method이며, `배열의 중간`에 요소를 추가하거나 제거한다.
> 

### 매개변수

- `start` : **시작 인덱스**. 원본 배열의 start부터 모든 요소를 제거한다. 음수일 경우 끝에서부터 센다.
- `deleteCount` : (필수X) start부터 시작하여 **제거할 요소의 개수**
- `items` : (필수X) 제거한 위치에 삽입할 요소들의 목록.

```jsx
const arr = [1,2,3,4];

let result = arr.splice(1,2,20,30);

// 원본 배열이 변경됨
console.log(arr);       // [ 1, 20, 30, 4 ]
// 제거된 요소 반환
console.log(result);    // [ 2, 3 ]

// 두 번째 인수 생략 시 그냥 추가만 된다.
// 첫 번째 인수가 음수면 끝에서부터 카운트한다
result = arr.splice(-1,0,100);
console.log(arr);       // [ 1, 20, 30, 100, 4 ]

// 모든 인수를 생략하면 원본 배열의 복사본을 생성하여 반환한다.
const copy = arr.slice();
console.log(copy);      // [ 1, 20, 30, 100, 4 ]
// 이 때 복사는 얕은 복사(shallow copy)이다
console.log(arr === copy);    // false
console.log(arr[1] === copy[1]);    // true
```

slice 메서드에 매개변수를 생략하면 복사본을 생성하는 것(이때 복사는 얕은 복사이다)을 이용하여 유사 배열 객체를 배열로 변환할 수 있다.

```jsx
// 유사 배열 객체 -> 배열

// 1. slice 메서드 사용
function sum() {
    // 유사 배열 객체를 배열로 변환
    var arr = Array.prototype.slice.call(arguments);

    return arr.reduce(function(pre, cur) {
        return pre + cur;
    }, 0);
}

console.log(sum(1,2,3));    // 6

// 2. Array.from 메서드 사용
const array1 = Array.from(arguments);

// 3. 스프레드 문법 사용
const array2 = [...arguments];
```

arguments 객체는 유사 배열 객체이면서 이터러블 객체다. 스프레드 문법을 사용하면 아주 간단하게 배열로 변환할 수 있다.

## Array.prototype.join

> 배열의 요소를 `문자열`로 변환한다.
> 

원본 배열의 모든 요소를 문자열로 변환한 후 인수로 전달받은 문자열(구분자separator의 역할을 함, 생략 가능하며 기본값은 콤마)로 연결한 문자열을 반환한다.

```jsx
const arr = [1,6,1,52,7,];

console.log(arr.join());    // 1,6,1,52,7
console.log(arr.join(` `)); // 1 6 1 52 7
```

## Array.prototype.reverse

> 배열의 `순서를 반대로` 뒤집는다. **원본 배열이 변경**된다. 반환값은 변경된 배열이다.
> 

```jsx
const result = arr.reverse();
console.log(result);    // [ 7, 52, 1, 6, 1 ]
console.log(arr);       // [ 7, 52, 1, 6, 1 ]
```

## Array.prototype.fill

> 인수로 전달받은 값을 요소로 `배열의 처음부터 끝까지` 채운다. **원본 배열이 변경**된다. ES6 도입
> 
- 첫 인수 : 채울 값
- 둘째 인수 : 채우기 시작할 인덱스(위치)
- 셋째 인수 : 채우기 멈출 인덱스

```jsx
arr.fill(100,1,3);
console.log(arr);    // [ 7, 100, 100, 6, 1 ]
```

fill 메서드를 사용하면 배열을 생성하면서 특정 값으로 요소를 채울 수 있지만, 하나의 값만으로만 채울 수 있다는 단점이 있다. 이 때 fill 대신 Array.from을 사용하면 편하다. Array.from 메서드는 두 번째 인수로 콜백 함수를 전달하면 요소값을 만들면서 배열을 채울 수 있다.

## Array.prototype.includes

> 배열 내에 `특정 요소가 포함되어 있는지` ToF를 반환한다. ES7 도입
> 
- 첫 인수 : 검색할 대상
- 둘째 인수 : 검색을 시작할 인덱스 (음수일 경우 length과 합산하여 결정)

```jsx
console.log(arr.includes(6,2));  // true
```

index0f 메서드를 사용해도 괜찮지만 예외(반환값이 -1이거나, 배열에 NaN이 포함되어 있거나)를 확인할 수 있는 문제점이 있다.

## Array.prototype.flat

> 인수로 전달한 깊이만큼 `재귀적`으로 배열을 `평탄화`. ES10 도입
> 

```jsx
console.log([1,[2,3]].flat());  // [ 1, 2, 3 ]
```