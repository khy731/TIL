# Map 객체

`key와 value`의 `쌍`으로 이루어진 컬렉션.

### Map 객체 VS 객체

Map 객체는 객체와 달리...

- key 값으로 **객체를 포함하여** 모든 값을 사용할 수 있다.
- `이터러블`이다
- lentgh 프로퍼티 대신 `size 메서드`로 길이(요소의 개수)를 확인한다

## Map 객체 생성하기

- `Map 생성자 함수`로 생성한다.

```jsx
// Map 생성자 함수로 Map 객체 생성
const map = new Map();
console.log(map);   // Map(0) {}
```

- ‘**키와 값의 쌍’으로 이루어진 ‘요소’로 구성된** `이터러블`만을 인수로 전달받는다.

```jsx
// 이터러블(키와 값의 쌍으로 이루어진 요소들로 이루어짐)만을 인수로 잔달받음
const map1 = new Map([[`name`,`kang`],[`age`,22]]);
console.log(map1);  // Map(2) { 'name' => 'kang', 'age' => 22 }

const map2 = new Map([`key`,`value`]);  // TypeError: Iterator value key is not an entry object
```

- 중복된 키는 존재할 수 없다(나중의 값으로 덮어씌워진다)

```jsx
// 중복된 키 -> 덮어씌워짐
const map3 = new Map([[`breakfast`,`egg`],[`breakfast`,`rice`]]);
console.log(map3);    // Map(1) { 'breakfast' => 'rice' }
```

# 요소

## 요소 개수(길이) 확인

> Map.prototype.size 프로퍼티
> 

setter 함수 없이 getter 함수만 존재하는 `접근자 프로퍼티` → read only

```jsx
// 요소 개수(길이) 확인
console.log(map.size);  // 6
```

## 요소 추가

> Map.prototype.set() 메서드
> 
- 반환값이 새로운 배열이므로 연속 사용 가능
- 문자열과 심벌만 키로 사용할 수 있는 객체와 달리, 객체를 포함한 모든 값을 사용할 수 있음

```jsx
map.set(`banana`,`good`);
// 객체를 키로 갖는 요소 추가
const obj = {name:`kang`};
map.set(obj, `girl`);
console.log(map);   //   { name: 'kang' } => 'girl'
```

### 인수로 배열을 전달할 때 주의점

인수로 전달하고 싶은 값(키:값 한 쌍)이

- 하나일 때 → 객체
- 여러개일 때 → 배열

을 사용할 것을 권장한다.

```jsx
map.set([`rice`,`yummy`]);  //   [ 'rice', 'yummy' ] => undefined
map.set([[`rice`],[`yummy`]]);  //   [ [ 'rice' ], [ 'yummy' ] ] => undefined
map.set(`rice`,`yummy`);    //   'rice' => 'yummy'
```

## 요소 취득

> Map.prototype.get() 메서드
> 

```jsx
// 요소 취득
console.log(map.get(`apple`));  // not bad
console.log(map.get(obj));  // girl
```

## 요소 존재 여부 확인

> Map.prototype.has() 메서드
> 

```jsx
// 요소 존재 여부 확인
console.log(map.has(`banana`));
```

## 요소 삭제

> Map.prototype.delete() 메서드
> 

```jsx
// 요소 삭제
map.delete(`banana`);
console.log(map);
```

## 요소 일괄 삭제

> Map.prototype.clear() 메서드
> 

```jsx
// 요소 일괄 삭제
map.clear();
console.log(map);
```

## 요소 순회

> forEach() 메서드
> 

```jsx
const myMap = new Map([[0, `a`],[1, `b`],[2, `c`]]);

// forEach
function count(map) {
    map.forEach((v,k)=>console.log(`${k} : ${v}`));
}
count(myMap);
/*
0 : a
1 : b
2 : c
*/
```

> for...of 문
> 

```jsx
// for...of
for (value of myMap) {
    console.log(value);
}
/*
[ 0, 'a' ]
[ 1, 'b' ]
[ 2, 'c' ]
*/
```

### 홀수 key를 가진 value만 출력하는 함수 만들기

```jsx
// 홀수 key를 가진 value만 출력하기
const odd = function(map) {
    for (let i=0; i<map.size; i++) if (i%2!==0) return map.get(i);
}
console.log(odd(myMap));    // b
```

### 기본 제공 메서드

`이터러블`이면서 동시에 `이터레이터`인 객체를 반환한다.

> Map.prototype.keys
> 

`요소 키`를 값으로 갖는 객체(이터러블 && 이터레이터)를 반환한다.

```jsx
// 이터러블이면서 이터레이터인 객체 반환
// 키를 값으로 갖음
for (const key of myMap.keys()) {
    console.log(key);   // 0 1 2
}
```

> Map.prototype.values
> 

`요소 값`을 값으로 갖는 객체(이터러블 && 이터레이터)를 반환한다.

```jsx
// 값을 값으로 갖음
for (const value of myMap.values()) {
    console.log(value);    // a b c
}
```

> Map.prototype.entries
> 

`요소 키`와 `요소 값`을 값으로 갖는 객체(이터러블 && 이터레이터)를 반환한다.

```jsx
// 둘 다 값으로 갖음
for (const entry of myMap.entries()) {
    console.log(entry);
}
/*
[ 0, 'a' ]
[ 1, 'b' ]
[ 2, 'c' ]
*/
```