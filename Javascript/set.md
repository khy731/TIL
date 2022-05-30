# Set

중복되지 않는 유일한 값들의 `집합(Set)`. **수학적 집합**을 구현하기 위한 자료구조이므로 배열과 유사하지만 차이가 있으며 Set으로 교집합, 합집합, 차집합, 여집합 등을 구현할 수 있다.

### Set 객체 VS 배열

Set 객체는 배열과 달리...

- 동일한 값을 중복하여 포함할 수 없다.
- 요소 순서에 의미가 없다 → 인덱스로 요소에 접근할 수 없다.

## Set 객체 생성하기

- `Set 생성자 함수`로 생성한다.

```jsx
const set = new Set();
console.log(set);   // Set(0) {}
```

- `이터러블`을 인수로 전달받아 생성되며, 중복된 이터러블 값은 요소로 저장되지 않는다.

```jsx
// 이터러블을 인수로 전달받는다
const set1 = new Set([1,2,3,4]);
console.log(set1);  // Set(4) { 1, 2, 3, 4 }

// 중복된 값은 요소로 저장되지 않는다
console.log(new Set(`kangYoon`));   // Set(6) { 'k', 'a', 'n', 'g', 'Y', 'o' }
```

→ 이 특성을 통해 배열에서 중복된 요소를 제거할 수 있기도 하다.

```jsx
// 배열의 중복 요소 제거하기
const arrSet = arr => arr.filter((v,i,self) => self.indexOf(v) === i);

// Set을 사용하여 중복 요소 제거하기
const arrSet2 = arr => [... new Set(arr)];
```

## 요소

### 개수 확인

> Set.prototype.size 프로퍼티
> 

```jsx
// 객체 디스트럭처링으로 size 프로퍼티 값 추출
const {size} = new Set([1,2,3,3,3]);
console.log(size);  // 3
```

size 프로퍼티는 `접근자 프로퍼티`이며, setter 함수 없이, `getter 함수`만 존재한다. 즉, read only이다.

```jsx
// 객체 디스트럭처링으로 size 프로퍼티 값 추출
const {size} = new Set([1,2,3,3,3]);
console.log(size);  // 3

// size 프로퍼티는 read only이다
const set = new Set(`Hellooo`);
console.log(Object.getOwnPropertyDescriptor(Set.prototype, `size`));
/* {
    get: [Function: get size],
    set: undefined,
    enumerable: false,
    configurable: true
  } */

set.size = 100;    // 변경되지 않는다(무시됨)
console.log(set.size);  // 4
```

### 특정 요소 존재 여부 확인

> Set.prototype.has 프로퍼티
> 

```jsx
const set = new Set([1,2,3]);
console.log(set.has(2));    // T
```

### 추가

> Set.prototype.add 메서드
> 

```jsx
const set = new Set([1,2,3,3,4]);
set.add(5);
```

객체나 배열처럼 자바스크립트의 모든 값을 요소로 저장할 수 있으며, 요소가 추가된 새로운 배열을 반환하는 구조이기 때문에 연속하여 사용할 수 있다.

```jsx
set.add({name:`kang`}).add((x,y)=>x+y);
console.log(set);   // Set(7) { 1, 2, 3, 4, 5, { name: 'kang' }, [Function (anonymous)] }
```

### 삭제

> Set.prototype.delete 메서드
> 
- 인수로 인덱스가 아니라 삭제하려는 `요소 값`을 전달해야 한다. **Set 객체는 배열과 달리 순서에 의미가 없기 때문(인덱스가 없음)**이다.
- 반환값이 add처럼 새로운 배열이 아니라 `삭제 성공 여부`이기 때문에 연속적으로 사용할 수 없다.

```jsx
const set = new Set([1,2,3,4,4]);
console.log(set.delete(2));     // T
// 존재하지 않는 요소 삭제 시 에러 없이 무시됨
console.log(set.delete(`a`));   // F
```

### 일괄 삭제

> Set.prototype.clear 메서드
> 

언제나 `undefined`를 반환한다.

```jsx
set.clear();
console.log(set);   // Set(0) {}
```

### 순회

> Set.prototype.forEach 메서드
> 

콜백 함수를 인수로 전달받아 요소를 순회한다. Array.prototype.forEach와 유사하게 동작하지만 Set 객체는 순서에 의미가 없기 때문에 인덱스를 인수로 받지 않는다.(그래서 콜백 함수의 두 번째 함수가 인덱스가 아닌 현재 순회중인 요소값이다. 첫 번째 인수랑 같지만 Array.prototype.forEach와 인터페이스를 맞추기 위함이다.)

```jsx
const set = new Set([1,2,3,3]);
set.forEach((item)=>console.log(item));    // 1 2 3
```

> for...of 문
> 

**Set 객체는 `이터러블`**이기 때문에 for...of문, 스프레드 문법. 디스트럭처링의 대상이 될 수 있다.

```jsx
// Set 객체는 이터러블이다
// Symbol.iterator 메서드를 상속받는다
console.log(Symbol.iterator in set);    // T

// for...of문으로 순회 가능하다
for(const value of set) {
    console.log(`value: ${value}`);    // value: 1 value: 2 value: 3
}
// spread syntax의 대상이 될 수 있다
const mySet = [0, ...set];
console.log(mySet);     // [ 0, 1, 2, 3 ]
// array distructuring의 대상이 될 수 있다
const [a, ...rest] = mySet;
console.log(a, rest);   // 0 [ 1, 2, 3 ]
```

## 집합 연산

Set 객체는 수학적 집합을 구현하기 위한 자료구조이다. 집합 연산을 수행하는 프로토타입 메서드를 구현해보자.

### 교집합

```jsx
// 교집합
// 1
Set.prototype.intersection = function(set) {
    const result = new Set();

    for (const value of set) {
        if (this.has(value)) result.add(value);
    }
    return result;
};

const setA = new Set([1,2,3,4]);
const setB = new Set([1,3]);

console.log(setA.intersection(setB));   // Set(2) { 1, 3 }

// 2
Set.prototype.intersection = function(set) {
    return new Set([...this].filter(v=>set.has(v)));
};
```

### 합집합

```jsx
// 합집합
// 1
Set.prototype.union = function(set) {
    for (const value of set) {
        this.add(value);
    }
    return this;
}

console.log(setA.union(setB));   // Set(4) { 1, 2, 3, 4 }

// 2
Set.prototype.union = function(set) {
    return new Set([...this, ...set]);
}
```

### 차집합

```jsx
// 차집합
// 1
Set.prototype.difference = function(set) {
    const result = new Set(this);

    for (const value of set) {
        result.delete(value);
    }
    return result;
};

// 2
Set.prototype.difference = function(set) {
    return new Set([...this].filter(v=>!set.has(v)));
}
```

### 부분집합, 상위집합

```jsx
// 2
Set.prototype.difference = function(set) {
    return new Set([...this].filter(v=>!set.has(v)));
}

// 부분 집합, 상위 집합
// 1
Set.prototype.isSuperset = function(sub) {
    for (const value of sub) {
        if (!this.has(value)) return false;
    }
    return true;
}

// 2
Set.prototype.isSuperset = function(sub) {
    return [...sub].every(v=>this.has(v));
}
```