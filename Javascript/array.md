# 배열

> 여러 개의 값을 순차적으로 나열한 자료구조
> 

배열은 사용 빈도가 매우 높은 가장 기본적인 자료구조이다. 

- 요소 (Element) : 배열의 값
- 인덱스 (Index) : 배열에서 요소의 위치를 나타내는 0 이상의 정수. 요소에 접근할 때 사용

배열은 data type이 아니며, `객체`이다. 그러나 객체와 다른 점으로는

1.  index로 표현되는 값의 순서를 갖는다
2. length 프로퍼티를 갖는다 → **반복문으로 순차적으로 값에 접근 가능**

```jsx
// 배열 리터럴을 통한 배열 생성
const arr = [`apple`, `banana`, `orange`];

// 대괄호 표기법으로 인덱스를 지정하여 요소에 접근
arr[0]
arr[1]
arr[2]

// 배열의 길이(요소의 개수)를 나타내는 length 프로퍼티
arr.length

// for문으로 순차적 접근 가능
for (let i=0; i<arr.length; i++) {
    console.log(arr[i]);
}
```

> 배열 생성 방법
> 
- 배열 리터럴
- Array 생성자 함수
- Array.of, Array.from 메서드

배열의 생성자 함수는 `Array`이며, 배열의 프로토타입 객체는 `Array.prototype`이고 이는 배열을 위한 다양한 빌트인 메서드를 제공한다.

# 자바스크립트의 배열은 배열이 아니다

## 일반적인 배열

- 밀집 배열(dense array) : 자료구조(data structure)에서 말하는 일반적인 배열
- 동일한 크기의 메모리 공간이 빈틈없이 연속적으로 나열된 자료구조. 배열의 요소는 하나의 data type으로 통일된다.

> `장점` : 인덱스를 통해 단 한 번의 연산으로 요소에 접근할 수 있어 효율적이다.
> 
> 
> `단점` : 요소 검색, 삽입, 삭제 시 비효율적이다.
> 

## 자바스크립트의 배열

- 해시 테이블로 구현된 **일반적인 배열의 동작을 흉내낸 특수한 객체.** 즉 배열의 요소는 사실 프로퍼티 값이며 어떤 타입이라도 요소가 될 수 있는 이유가 바로 이것이다.
- 희소 배열 (sparse array)을 문법적으로 허용한다 : 각각의 메모리 공간은 동일한 크기를 갖지 않거나 연속적으로 이어져 있지 않을 수 있다.

> `장점` : 요소 검색, 삽입, 삭제 시 효율적이다.
> 
> 
> `단점` : 인덱스로 요소에 접근하는 경우 상대적으로 비효율적이다.
> 

자바스크립트 배열은 인덱스 연산자를 통한 접근의 성능을 버리고, 탐색+삽입+삭제의 성능을 선택했다. 또한 접근 시 속도를 보완하기 위해 보다 *배열처럼 동작하도록* 일반 객체와 차별화된 구조를 구현했다.

## length 프로퍼티

- 배열의 길이(요소의 개수)를 나타내는 0 이상의 정수. 인덱스 + 1
- 배열에 요소를 push/pop 시 자동 갱신
- 명시적으로 임의의 값 할당 가능 (보다 작은 값 할당시 실제로 줄어듬. 큰 값 할당시 변화없음)

```jsx
const arr = [1,2,3];

// 요소 변경(추가)
arr.push(4);
console.log(arr.length);    // 4

// length 프로퍼티 값 명시적 할당
// 프로퍼티 값 자체는 성공적으로 변경된다.

// 1. 더 큰 값 : 실제 배열에는 변화가 없다. 빈 요소를 위해 메모리 공간을 확보하지 않는다.
arr.length = 6;
console.log(arr);   // [ 1, 2, 3, 4, <2 empty items> ]

// 2. 더 작은 값 : 배열의 길이가 줄어든다.
arr.length = 2;
console.log(arr);   // [ 1, 2 ]

// 희소 배열은 허용되지만 권장하지 않는다
const sparse = [ , 2, 3, , 5];
console.log(sparse.length);     // 5
```

- **희소 배열의 경우 (불연속적이므로=중간에 빈칸이 있으므로) 배열 요소의 개수보다 length 값이 항상 크다**

→ 자바스크립트는 희소 배열을 허용하지만 이는 배열의 본질을 해치므로, 사용을 권장하지 않는다. **배열은 `같은 타입`의 요소를 `연속적`으로 위치시킨 자료구조이다.**

# 배열 생성

## 배열 리터럴

가장 간단한 방법. 객체 리터럴과 달리 프로퍼티 키가 없고, `프로퍼티 값`만 존재한다.

```jsx
// 1. 배열 리터럴
let arr = [1,2,3];
arr = [];         // 빈 배열
arr = [1, , 3]    // 희소 배열(요소 생략)
```

## Array 생성자 함수

Object 생성자 함수로 객체 생성하듯이, Array 생성자 함수로 배열 생성 가능. `arguments의 개수`에 따라 다르게 동작한다. (애초에 그렇게 parameter가 설계되어 있다)

```jsx
// 2. Array 생성자 함수

// 2-1. arguments 1개 : 배열의 길이(length)로 인식
const array = new Array(10);
console.log(array);    // [ <10 empty items> ]

// 2-2. arguments 여러개 : 배열의 요소(elements)로 인식
const array2 = new Array(10,20,30);
console.log(array2);    // [ 10, 20, 30 ]

// Array 생성자 함수 내부에 new.target 확인 동작이 존재
// new 연산자와 함께 호출하지 않아도(일반 함수로써 호출해도) 정상 동작(배열 생성)
console.log(Array(3,6,9));    // [ 3, 6, 9 ]
```

## Array.of 메서드

ES6의 신기능. 전달된 arguments를 요소로 갖는 배열 생성. Array 생성자 함수와 달리 arguments가 1개더라도 length가 아닌 elements로 인식한다.

```jsx
// 3. Array.of
// arguments의 개수에 상관없이 elements로 인식
const arr1 = Array.of(10);
console.log(arr1);    // [ 10 ]
```

## Array.from 메서드

ES6의 신기능. 유사 배열 객체(array-like object)나 이터러블 객체(iterable object)를 인수로 전달받아 `배열로 변환`하여 반환한다.

```jsx
// 4. Array.from

// 4-1. array-like object -> array 변환
const obj = {
    length : 2,
    0 : `a`,
    1 : `b`,
}
console.log(Array.from(obj));   // [ 'a', 'b' ]

// 4-2. iterable object -> array 변환
console.log(Array.from(`Hi, X!`));    // [ 'H', 'i', ',', ' ', 'X', '!' ]

// 두 번째 arguments로 콜백 함수를 전달하면 값을 만들면서 배열의 요소를 채울 수 있다.
// 콜백 함수에 생성된 배열의 요소값과 인덱스를 순차적으로 전달하면서 호출 -> 반환값(완성된 배열)
console.log(Array.from({length:3}));    // [ undefined, undefined, undefined ]
console.log(Array.from({length:3}, (_, i) => i));    // [ 0, 1, 2 ]
```

> `유사 배열 객체`와 `이터러블 객체`
> 
- 유사 배열 객체

배열처럼 인덱스로 프로퍼티 값에 접근할 수 있고, length 프로퍼티 갖는 객체. for문으로 순회도 가능

- 이터러블 객체

Symbol.iterator 메서드로 for...of 문으로 순회 가능하고 스프레드 문법과 배열 디스트럭처링 할당의 대상으로 사용할 수 있는 객체. ES6의 빌트인 이터러블은 다음 등이 있다: Array, String, Map, Set...

# 배열 요소 참조

대괄호([ ])표기법을 사용한다. 배열은 인덱스를 나타내는 문자열을 프로퍼티 키로 갖는 객체이므로, 존재하지 않는 요소를 참조하면 undefined를 반환한다.

```jsx
const arr = [1,2,3,4,5];

// 배열 요소 참조
console.log(arr[2]);    // 3

// 존재하지 않는 요소 참조 시 undefined
console.log(arr[6]);    // undefined
```

# 배열 요소 추가/갱신

- 요소를 `동적`으로 추가할 수 있다.

존재하지 않는 index로 값을 할당하면 새로운 요소가 추가되며, length 프로퍼티 값이 자동 갱신된다. 단, 본래 배열의 length보다 큰 인덱스로 추가할 경우 가운데가 비어 희소 배열이 된다.

- 이미 존재하는 요소에 값을 재할당하면 요소가 `갱신`된다.
- index에 정수 이외의 다른 타입의 값을 사용하면 **요소가 생성되지 않고 프로퍼티가 생성되며, 이는 요소로 치지 않기 때문에 length에도 영향을 주지 않는다.** index는 반드시 0 이상의 정수(또는 정수 형태의 문자열)만 사용하도록 하자.

```jsx
// 배열 요소 동적 추가
arr[5] = 6;
console.log(arr[5]);        // 6
console.log(arr.length);    // 6

// 본래 length보다 큰 인덱스로 동적 추가
// 희소 배열. 권장하지 않는다
arr[100] = 100;
console.log(arr);   // [ 1, 2, 3, 4, 5, 6, <94 empty items>, 100 ]

// 요소에 재할당하여 값 갱신
arr[1] = 22;
console.log(arr);   // [ 1, 22, 3, 4, 5, 6, <94 empty items>, 100 ]

// 인덱스에 정수(or 정수 형태의 문자열)를 사용하지 않으면 요소가 아닌 프로퍼티가 생성된다
arr[`foo`] = 10;
console.log(arr);           // [ 1, 22, 3, 4, 5, 6, <94 empty items>, 100, foo: 10 ]
console.log(arr.length);    // 요소가 아니므로 배열 길이에 영향을 주지 않는다
```

# 배열 요소 삭제

배열도 객체이므로, delete 연산자를 사용하여 요소를 삭제할 수 있다. 그러나 이 경우 배열은 희소 배열이 되기 때문에(또 length도 갱신되지 않는다) 사용하지 않는 것이 좋다. 희소 배열을 피하면서 배열의 요소를 삭제하려면 `Array.prototype.splice` 메서드를 사용한다.

```jsx
// delete로 배열의 특정 요소 삭제
delete arr[1];
console.log(arr);           // [ 1, <1 empty item>, 3, 4, 5, 6, <94 empty items>, 100, foo: 10 ]
console.log(arr.length);    // 영향X. 희소 배열이 된다

// Array.prototype.slice로 배열의 특정 요소 삭제
//(삭제를 시작할 인덱스, 삭제할 요소 수)
arr.splice(2,50);    // arr[2]부터 1개의 요소를 제거
console.log(arr);    // [ 1, <49 empty items>, 100, foo: 10 ]
```