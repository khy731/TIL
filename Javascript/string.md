# String

String 객체는 `표준 빌트인 객체`이자 `생성자 함수 객체`이며, 원시 타입인 `문자열`을 다룰 때 유용한 프로퍼티와 메서드를 제공한다.

# String() 생성자 함수

new 연산자와 함께 호출하여 String 인스턴스를 생성하면 [[StringData]] 내부 슬롯에 전달된 인수(문자열)를 할당한 `String 래퍼 객체`를 생성한다.

```jsx
// String() 생성자 함수

const strObj1 = new String();
console.log(strObj1);    // [String: '']

const strObj2 = new String(`Hello`);
console.log(strObj2);    // [String: 'Hello']
```

- String 래퍼 객체는 유사 배열 객체이다
    - `length 프로퍼티`와 `인덱스`를 프로퍼티 키로, 각 문자를 프로퍼티 값으로 갖는다
    - 순회 가능하다 (length 프로퍼티가 존재하므로)

```jsx
// String 래퍼 객체는 length 프로퍼티 값을 갖는 유사 배열 객체이다
// 프로퍼티 키 : 인덱스(를 나타내는 숫자 문자열)
// 프로퍼티 값 : 각 문자(요소)
console.log(strObj2[1]);    // e
```

- String 생성자 함수의 인수로 문자열이 아닌 값을 전달하면 강제 형변환한 후 [[StringData]] 내부 슬롯에 변환된 문자열을 할당한 String 래퍼 객체를 생성(저장)한다.

```jsx
// 인수로 문자열이 아닌 값을 전달하면 강제 타입 변환한다
const strObj3 = new String(null);    // [String: 'null']
console.log(strObj3);
```

- new 연산자와 함께 호출하지 않으면 **인스턴스가 아닌** `문자열(원시값)`을 반환한다.

→ 이를 이용하여 `명시적 타입 변환`이 가능하다!

```jsx
// new 연산자를 사용하지 않고 호출 시 인스턴스가 아닌 원시값(문자열)을 반환한다
// 이를 이용한 명시적 타입 변환
console.log(String(123));   // 123
console.log(String(true));  // true
```

# length 프로퍼티

> 문자열의 `문자 개수`를 반환한다.
> 

String 래퍼 객체는 **마치 배열처럼** length 프로퍼티를 갖는 `유사 배열 객체`이다.

```jsx
`안녕하세요123`.length;    // 8
```

# String 메서드

String 객체에는 배열과 달리 mutator method(원본 배열을 직접 변경)와 accessor method(새로운 배열을 생성하여 반환)가 구분되어 있지 않으며, 오직 accessor method만 존재한다.

> 문자열은 immutable한 **원시 값**이기 때문에, String 래퍼 객체도 언제나 read only(읽기 전용)이며 String 메서드도 전부 accessor method이다
> 

## String.prototype.index0f

> 대상 문자열에서 인수로 전달받은 문자열을 `검색`하여 `첫 번째 인덱스`를 반환한다.
> 

대상 문자열에 특정 문자열이 존재하는지 확인할 때 유용하다.  검색 실패 시 -1을 반환하며,  2번째 인수로 검색을 시작할 인덱스 지정 가능

```jsx
// index0f method

const strobj = new String(`KangHyeYoon`);
console.log(strobj.indexOf(`o`));   // 8

// 검색에 실패하면 -1 반환
console.log(strobj.indexOf(`x`));   //  -1

// 대상 문자열에 특정 문자열이 존재하는지 확인할 때 유용
if (strobj.indexOf(`z`) === -1) {
    console.log(`there is no 'z'`);    // there is no 'z'
}
```

ES6의 includes 메서드가 가독성이 더 좋다.

```jsx
// ES6의 String.prototype.includes가 가독성이 더 좋음
if (!strobj.includes(`z`)) {
    console.log(`there is no 'z'`);    // there is no 'z'
}
```

## String.prototype.search

```jsx
const strobj = new String(` https://velog.io/@KHY731`);

// String.prototype.search
console.log(strobj.search(/K/));  // 19
console.log(strobj.search(`z`));    // -1
```

## String.prototype.includes

```jsx
// String.prototype.includes
console.log(strobj.includes(`io`,3));     // T
console.log(strobj.includes(`z`));         // F
```

## String.prototype.startsWith

```jsx
// String.prototype.startsWith
console.log(strobj.startsWith(` `));       // T
console.log(strobj.startsWith(`a`));       // F
```

## String.prototype.endsWith

```jsx
// String.prototype.endsWith
console.log(strobj.endsWith(`731`));       // T
console.log(strobj.endsWith(`io`));        // F
```

## String.prototype.charAt

```jsx
// String.prototype.charAt
for(i=0; i<strobj.length; i++) {
    console.log(strobj.charAt(i));
}
```

## String.prototype.substring

```jsx
// String.prototype.substring
console.log(strobj.substring(9,14));    // velog
// 특정 문자열을 기준으로 앞뒤에 위치한 부분 문자열을 취득 가능
console.log(strobj.substring(0, strobj.indexOf(`/`)));    //  https:
```

## String.prototype.slice

```jsx
// String.prototype.slice
console.log(strobj.slice(9, 14));        // velog
console.log(strobj.slice(-5))            // HY731
```

## String.prototype.toUpperCase

```jsx
// String.prototype.toUpperCase
console.log(strobj.toUpperCase());      // HTTPS://VELOG.IO/@KHY731
```

## String.prototype.toLowerCase

```jsx
// String.prototype.toLowerCase
console.log(strobj.toLowerCase());      // https://velog.io/@khy731
```

## String.prototype.trim

```jsx
// String.prototype.trim
console.log(strobj.trim());             // 공백 제거
console.log(strobj.trinStart())         // 앞 공백 제거
console.log(strobj.trimEnd());          // 뒤 공백 제거
```

## String.prototype.repaet

```jsx
// String.prototype.repaet
console.log(strobj.repeat(2));          //  https://velog.io/@KHY731 https://velog.io/@KHY731
// 인수의 기본값 : 0 (비었을 시 자동으로 0)
console.log(strobj.repeat());           //  ''
```