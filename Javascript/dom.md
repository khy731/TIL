# DOM(Document Object Model)

> HTML 문서의 계층적 구조와 정보를 표현하고 이를 제어할 수 있는 API(프로퍼티와 메서드)를 제공하는 트리 자료구조.
> 

브라우저 렌더링 과정에서 단순한 텍스트 HTML 문서를 파싱(문자열→토큰→노드→DOM)하여 브라우저가 이해할 수 있는 자료구조(DOM)을 생성한다는 것을 배웠다. DOM에 대해 자세히 알아보자.

# 노드

## 노드 객체

![DOM](https://user-images.githubusercontent.com/97890886/170254138-6522b530-5110-4d8a-95cb-f1b26e4935f4.png)

HTML문서는 HTML 요소들의 집합으로 이뤄지고, HTML 요소들은 서로 중첩 관계를 갖으며 이 중첩 관계에 의해 계층적인 부자(상속)관계 parent-child 가 형성된다. HTML 요소를 이러한 상속 관계를 반영하여 객체화한 것이 바로 노드 객체이다. 그리고 모든 노드 객체들로 구성된 `트리 자료구조`가 바로 DOM이며, 이러한 특성 때문에 DOM을 `DOM 트리`라고 부르기도 한다.

### 트리 자료구조(tree data structure)

부모 노드(parent code)와 자식 노드(child node)간의 계층적 구조(부모/형제)를 표현하는 비선형 자료구조. 단 하나의 루트 노드(root node, 더 이상 부모 노드가 없는 최상위 노드)에서 시작하며 루트 노드는 0개 이상의 자식 노드를 갖는다. 자식 노드가 0개(없음)인 경우 리프 노드(leaf node)라고 한다.

## 노드 객체의 타입

### 문서 노드 (document node)

DOM 트리의 최상위에 존재하는 루트 노드(document 객체). document 객체는 브라우저가 렌더링한 HTML 문서 전체를 가리키며, 전역 객체의 document 프로퍼티에 바인딩되어 있다.

> 하나의 HTML 문서당 document 객체는 **유일**하다.
> 

브라우저 환경의 모든 JS 코드는 (script 태그에 의해)분리되어 있어도 하나의 전역 객체를 공유하므로, 결과적으로 전역 객체의 document 프로퍼티에 바인딩되어있는 하나의 document 객체만을 바라보게 된다.

> 문서 노드(document 객체)는 루트 노드이므로 진입점(entry point)역할을 한다.
> 

요소 노드, 어트리뷰트 노드, 텍스트 노드에 접근하려면 문서 노드를 통해야 한다.

### 요소 노드(element node)

> 문서의 구조를 표현한다
> 

요소 노드는 HTML 요소(태그)를 가리키는 객체로, HTML 요소 간 상속 관계를 구현하여 정보를 구조화하므로 문서의 구조(부모관계)를 표현한다.

### 어트리뷰트 노드(attribute node)

HTML 요소의(태그) 어트리뷰트(속성)을 가리키는 객체. 요소 노드와 연결되어 있다.

부모 요소와 연결된 요소 노드(문서 노드나 또 다른 요소 노드)와는 달리 부모 요소를 갖지 않으며 요소 노드에게 짝처럼 연결되어 있기 때문에 **요소 노드의 형제는 아니다. 즉, 어트리뷰트 노드에 접근하기 위에서는 필연적으로 요소 노드에 접근해야 한다.**

### 텍스트 노드(text node)

HTML 요소의 텍스트(내용, 컨텐츠)를 가리키는 객체. 요소 노드가 구조 표현이라면, 실제 문서의 내용(정보)를 표현한다.

> DOM 트리의 `최종단`이다.
> 

요소 노드의 자식 노드이며, 더이상 밑으로 뻗을 수 없는 `리프 노드`이다.  즉, 텍스트 노드에 접근하려면 필연적으로 요소 노드에 접근해야 한다.

위 네 타입 말고도 Comment node(주석), Document Type node(DOTYPE), DocumentFragment node(복수의 노드를 생성하여 추가) 등 총 12가지의 노드 타입이 존재한다.

## 노드 객체의 상속 구조

DOM을 구성하는 노드 객체는 자신의 구조와 정보를 제어할 수 있는 DOM API를 사용할 수 있다. 즉, 노드 객체는 DOM API를 사용하여 자신의 부모, 형제, 자식을 탐색할 수 있으며 자신의 어트리뷰트와 텍스트를 조작할 수 있다.

노드 객체는 표준 빌트인 객체(ECMAScript 사양에 정의됨)가 아닌 호스트 객체(브라우저 환경에서 추가 제공)이다. 그러나 노드 객체도 자바스크립트 객체이므로 `프로토타입`에 의한 상속 구조를 갖는다.

<노드 객체의 상속 구조>

- 모든 노드 객체는 Object, EventTarget, Node 인터페이스를 상속받는다(이를 프로토타입 체인 관점에서 살펴볼 경우, 모든 객체는 각 인터페이스에 바인딩되어 있는 프로토타입 객체-그러니까 플어 말하자면 Object.prototpye, EventTarget.prototype, Node.prototype-를 상속받는다. 즉 프로토타입 체인에 있는 모든 프로퍼티나 메서드를 사용 가능하다.)
- 공통된 기능일수록 프로토타입 체인의 상위에, 세분화된 개별적 고유 기능일수록 프로토타입 체인의 하위에 프로토타입 체인을 구축하여 → 타입별 노드 객체에 필요한 기능(프로퍼티와 메서드)을 제공한다.
    
    예를 들어 모든 노드 객체는 공통적으로 인터페이스 EventTarget를 상속받아 이벤트를 발생시킬 수 있으며, 트리 자료구조의 노드로써 Node를 상속받아 트리 탐색 기능이나 노드 정보 제공 기능을 갖지만, 요소 노드 객체는 HTMLElement 인터페이스를 혼자 추가로 상속받아 요소의 스타일을 관리한다.
    

## 요소 노드 취득

아까 노드 객체 타입에서 어트리뷰트(속성) 노드 객체와 텍스트(컨텐츠) 노드 객체는 전부 요소(태그) 노드 객체와 이어져 있기 때문에 이들에게 접근하려면 먼저 요소 노드에 접근해야 한다고 했다. 이제부터 본격적으로 자바스크립트에서 DOM API를 사용하여 웹을 조작할 건데, 글씨의 색을 바꾼다던가 출력되는 텍스트를 바꾼다던가 하는건 전부 어트리뷰트, 텍스트 노드 객체를 다뤄야 하고 이를 위해서는 일단! 요소 노드 객체에 접근해야 한다. 그럼 이제부터 요소 노드를 취득해보자.

### id로 취득하기

> Document.prototype.getElementById 메서드
> 

인수로 전달한 `id 어트리뷰트 값`을 갖는 하나의 요소 노드를 탐색하여 반환. Document.prototype의 프로퍼티이기 때문에 문서 노드(document 객체)를 통해 호출해야 한다.

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <title>Document.prototpye.getElementId</title>
</head>
<body>
    <ul>
        <li id="1">Apple</li>
        <li id="1">Banana</li>
        <li id="3">Orange</li>
    </ul>
</body>
<script>
    const $elem = document.getElementById(`1`);
    $elem.style.color = `red`;
</script>
</html>
```

- 단 하나의 반환값만을 가지며, 중복된 id값을 갖는 요소가 여러 개 존재할 경우 첫 번째 요소 노드만 반환한다
- 인수로 전달된 id값을 갖는 HTML 요소가 존재하지 않는 경우 null 반환
- 부수 효과가 있다

```html
<!DOCTYPE html>
<html lang="en">
<body>
    <div id="foo"></div>
    <script>
        // 선언되지 않은 변수 foo로 뭔가를 하려고 할 때
        // id값과 동일한 이름의 전역 변수가 암묵적으로 선언되고 해당 노드 객체가 할당됨
        // 암묵적으로 생성된 전역 프로퍼티는 삭제되지만 전역 변수는 삭제되지 않음
        delete foo;
        console.log(foo);   // <div id="foo"></div>
    </script>
</body>
</html>
```

### 태그로 취득하기

> Document/Elemenets.prototype.getElementsByTagName 메서드
> 

인수로 전달한 태그 이름을 갖는 모든 요소 노드들을 탐색하여 반환한다. 여러 개의 노드 객체를 갖는 DOM 컬렉션 객체인 `HTMLCollection 객체`(유사 배열 객체이자 이터러블) 형태로 반환한다.

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>getElementByTagName</title>
</head>
<body>
    <ul id="user">
        <li>Kang</li>
        <li>Lee</li>
        <li>Jung</li>
    </ul>
    <ul>
        <li>hi</li>
        <li>world</li>
    </ul>
    <script>
        // Document.prototype
        const $lisFromDoc = document.getElementsByTagName(`li`);
        
        // Elements.prototype
        const $user = document.getElementById(`user`);
        const $lisFromgUser = $user.getElementsByTagName(`li`);

        // HTMLCollection은 유사 객체이면서 이터러블
        [...$user].forEach(v=>{v.style.color = `yellow`});
    </script>
</body>
</html>
```

- HTML 문서의 모든 요소 노드를 취득하려면 인수로 `*`를 전달한다.
- Document.prototype VS Elements.prototype
    - Document.prototype에 정의된 메서드 : 문서 노드(document, DOM의 루트 노드)를 통해 호출되어 **DOM 전체**에서 탐색해 반환
    - Elements.prototype에 정의된 메서드 : 특정 요소 노드를 통해 호출되어 **특정 요소 노드의 자손 노드 중**에서 탐색해 반환
- 인수로 전달된 태그 이름을 갖는 요소가 존재하지 않을 경우 빈 HTMLCollection 객체를 반환

### class로 취득하기

> Document/Elements.protoytpe.getElementByClassName 메서드
> 

인수로 전달한 class 어트리뷰트 값을 갖는 모든 노드를 탐색하여 HTMLCollection 메서드로 반환하며, class 값을 공백으로 구분하여 여러 개의 class를 지정할 수 있다.

```html
<!DOCTYPE html>
<html lang="en">
<head>
</head>
<body>
    <ul id="user">
        <li class="kang">kang</li>
        <li class="jung">jung</li>
        <li class="woo">woo</li>
    </ul>
    <ul>
        <li class="jung">j</li>
        <li class="woo">w</li>
    </ul>
    <script>
        // 취득한 요소의 CSS color 프로퍼티 값 변경하기
        const $kang = document.getElementsByClassName(`kang`);
        [...$user].forEach(v=> {v.style.color = `red`});

        // documents
        const $name = document.getElementsByClassName(`jung`);
        // Elements
        const $user = document.getElementById(`user`);
        const $userName = $user.getElementsByClassName(`jung`);
    </script>
</body>
</html>
```

### CSS 선택자로 취득하기

> Document/Element.prototype.querySelector 메서드
> 

인수로 전달한 CSS 선택자를 만족시키는 `하나의 요소 노드`를 탐색하여 반환.

```html
<!DOCTYPE html>
<html lang="en">
<head>
<body>
    <ul id="user">
        <li class="Kang">Kang</li>
        <li class="Lee">Lee</li>
        <li class="Jung">Jung</li>
    </ul>
    <ul>
        <li>Jung</li>
        <li>Woo</li>
    </ul>
    <script>
        const $kang = document.querySelector(`.kang`);
        $kang.style.color = `red`;
    </script>
</body>
</html>
```

- 여러 개(중복)인 경우 첫 번째 요소 노드만 반환
- 존재하지 않는 경우 null 반환
- CSS 선택자가 문법에 맞지 않는 경우 DOMException 에러 발생

> Document/Element.prototype.querySelectorAll 메서드
> 

인수로 전달한 CSS 선택자를 만족시키는 유사 배열 객체이면서 이터러블인 `NodeList 객체`를 반환한다.

```html
<!DOCTYPE html>
<html lang="en">
<head>
<body>
    <ul id="user">
        <li class="Kang">Kang</li>
        <li class="Lee">Lee</li>
        <li class="Jung">Jung</li>
    </ul>
    <ul>
        <li>Jung</li>
        <li>Woo</li>
    </ul>
    <script>
        const $name = document.querySelectorAll(`ul>li`);
        $name.forEach(v=>{v.style.color = `blue`;});
    </script>
</body>
</html>
```

CSS selector 문법을 사용하는 위 두 메서드는 getElementsBy*** 메서드보다 다소 느리지만, 보다 구체적이고 일관된 방식으로 요소 노드를 취득할 수 있으므로 권장된다.

- id 어트리뷰트가 있는 경우 getElementById 메서드 사용 권장
- 그 외의 경우 querySelector, querySelectorAll 메서드 사용 권장

## 특정 요소 노드 취득 가능 여부 확인

> Element.prototype.matches 메서드
> 

인수로 전달한 CSS 선택자를 통해 특정 요소 노드를 취득할 수 있는지 확인

```html
<!DOCTYPE html>
<html lang="en">
<head>
<body>
    <ul id="user">
        <li class="Kang">Kang</li>
        <li class="Lee">Lee</li>
        <li class="Jung">Jung</li>
    </ul>
    <ul>
        <li>Jung</li>
        <li>Woo</li>
    </ul>
    <script>
        const $name = document.querySelector(`.Kang`);

        // $name은 #user > li.Kang 으로 취득할 수 있다
        $name.matches(`#user > li.Kang`);    // T
    </script>
</body>
</html>
```
## HTMLCollection, NodeList

> DOM API가 여러 개의 결과값을 반환하기 위한 `DOM 컬렉션 객체`
> 
- 유사 배열이면서 이터러블이다 → for…of문, 스프레드 문법, 디스트럭처링 사용 가능
- `살아 있는(live) 객체`이다 → 노드 객체의 상태 변화를 **실시간**으로 반영한다. (여기에 대해서는 두 객체 간 차이가 있다. 추후에 설명하겠다)

### HTMLCollection

`live DOM 컬렉션 객체`. TagName, ClassName 메서드가 반환한다.

> 문제점
> 

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <title>HTMLCollection</title>
    <style>
        #container {
            font-size: large;
            font-style: italic;
        }
        .red {
            color: red;
        }
        .blue {
            color: blue;
        }
    </style>
</head>
<body>
    <ul id="container">
        <li class="red">first</li>
        <li class="red">second</li>
        <li class="red">third</li>
    </ul>
    <script>
        const $elem = document.getElementsByClassName(`red`);
        console.log($elem);   // HTMLCollection(3) [li.red, li.red, li.red]

        for (i=0; i<$elem.length; i++) {
            $elem[i].className = `blue`;
        }
        console.log($elem);    // // HTMLCollection(1) [li.red]
    </script>
</body>
</html>
```

위 코드는 클래스 네임이 red인 요소 노드 객체를 모두 취득하고, 취득된 모든 요소 노드 객체가 담겨있는 HTMLCollection 객체를 for문으로 순회하며 className 프로퍼티를 사용하여 class 값을 blue로 변경한다.

![HTMLCollection PNG](https://user-images.githubusercontent.com/97890886/170255006-d9b4eabc-738e-4a41-bf2d-9d2039e6898b.png)

그러나 이를 실행해 보면 예상대로 동작하지 않는다.

이는 HTMLCollection 객체가 실시간으로 노드 객체의 상태 변경을 반영하기 때문이다. 다음은 for문의 로직이다:

1. 첫 번째 반복(i===0) : $elem[0]이 blue로 변경되어 $elem에서 실시간으로 제거된다.
2. 두 번째 반복(i===1) : 첫 번째 li 요소는 이미 이전 단계에서 $[elem]에서 제거되었기 때문에 $elem[1]은 세 번째 li 요소가 되고, 이도 실시간으로 제거된다.
3. 세 번째 반복(i===2) : 이전 단계에서 두 요소가 제거되었으므로 $elem.length는 1이며 이는 반복문의 조건에 어긋나기 때문에 반복이 종료된다. **아직 남아있는 $elem의 두 번째 요소의 class 값은 변경되지 않는다.**

> 해결법
> 
- 역방향 for문으로 회피한다

```jsx
// 역방향 for 문
        for (let i=$elem.length-1; i>-1; i--) {
            $elem[i].className = `blue`;
        }
```

- while문 → HTMLCollection 객체에 노드 객체가 남아있지 않을 때까지 무한 반복한다

```jsx
// while(무한반복)문
        let j = 0;
        while(j<$elem.length) {
            $elem[j].className = `red`;
            j++;
        }
```

- **HTMLCollection 객체를 날것으로 직접 사용하지 않는다.** 이는 유사 배열 객체이자 이터러블이므로, 이를 배열로 변환하면 유용하고 다양한 고차 함수를 사용할 수 있다.

```jsx
// HTMLCollection 객체는 유사 배열 객체이자 리터러블이다
        // 배열로 변환하여 순회
        [...$elem].forEach(v=>v.className = `blue`);
```

### NodeList

HTMLCollection 객체의 부작용을 해결하기 위해 TagName, className 메서드 대신 querySeletorAll 메서드를 사용한다 → NodeList 객체를 반환한다. NodeList는 실시간으로 노드 객체의 상태 변경을 반영하지 않는 `Non-Live DOM 컬렉션 객체`이다.

- NodeList.prototype을 상속받는다

forEach, item, entries, keys, values 등의 메서드를 제공받는다.

```jsx
const $elem = document.querySelectorAll(`#container > li.red`);
        // Node.prototype.forEach를 상속받는다
        $elem.forEach(v=>v.className = `blue`);
```

- NodeList 객체는 대부분의 경우 non-live 객체로 동작하지만, 간혹 예상과 다르게 동작할 때가 있다 예를 들어, **childNodes 프로퍼티가 반환하는 NodeList 객체는 HTMLCollection처럼 live로 동작한다.**

```jsx
const $num = document.getElementById(`number`);
        const {childNodes} = $num;

        // removeChild 메서드가 호출될 때마다 childNodes가 실시간으로 변경됨
        // 1,3,5번째 요소만 삭제되는 부작용 발생
        // 예상과 다륵 ㅔ$num의 모든 자식 노드가 삭제되지 않음
        for (let i=0; i<num.length; i++) {
            $num.removeChild(childNodes[i]);
        }
```

HTMLCollection과 NodeList는 이처럼 예상과 다르게 동작할 때가 있기 때문에 다루기 굉장히 까다롭고 실수하기 쉽다. 노드 객체의 상태 변경과 상관없이 안전하게 DOM 컬렉션을 사용하려면 **배열로 변환하여** 사용하는 것을 권장한다. 기존보다 더 많은 메서드(특히 고차 함수)를 제공받을 수 있다는 장점도 있다. 두 객체는 모두 유사 배열 객체이면서 이터러블이기 때문에 스프레드 문법, Array.from으로 간단하게 배열로 변환이 가능하다.

```jsx
// 스프레드 문법으로 배열로 변환
        [...childNodes].forEach(v=>$num.removeChild(v));
```

# 노드 탐색

요소 노드를 취득했다면, 이제 취득한 요소 노드를 기점으로 DOM 트리를 옮겨 다니며 부모, 형제, 자식을 `탐색(traversing, node warking)`해야 한다.

```html
<ul id="number">
        <li class="red">first</li>
        <li class="red">second</li>
        <li class="red">third</li>
</ul>
```

- ul#fruits 요소는 3개의 자식 요소를 갖는다
- li.banana 요소는 1개의 부모 요소, 2개의 형제 요소를 갖는다

> Node, Element 인터페이스는 DOM 트리 상의 노드를 탐색할 수 있도록 `트리(노드) 탐색 프로퍼티`를 제공한다.
> 
- Node.prototype : parentNode, previousSibling, childNodes 프로퍼티 제공
- Element.prototype : previousElementSibling, nextElementSibling, children 프로퍼티 제공

노드 탐색 프로퍼티는 모두 `접근자 프로퍼티`지만, setter 없이 getter만 존재하는 read only이다. 즉 값을 할당하는 행위를 하더라도 에러 없이 무시된다.

> 노드 탐색 시, `공백 텍스트 노드`에 주의해야 한다.
> 

공백 텍스트 노드란 HTML 요소 사이의 스페이스, 탭, 뉴라인 등의 white space 문자가 생성하는 텍스트 노드이다. 이 역시 파싱되어 DOM에 포함된다.

## 자식 노드 탐색

> Node.prototype.childNodes
> 

자식 노드를 모두 탐색하여 NodeList에 담아 반환. **텍스트 노드도 포함되어 있을 수 있다.**

> Element.prototype.children
> 

자식 노드 중 요소 노드만 탐색하여 HTMLCollection에 담아 반환. **텍스트 노드가 포함되지 않는다.**

> Node.prototype.firstChild
> 

첫 번째 자식 노드(요소/텍스트)를 반환.

> Node.prototype.lastChild
> 

마지막 자식 노드(요소/텍스트)를 반환.

> Element.prototype.firstElementChild
> 

첫 번째 자식 노드(요소)를 반환.

> Element.prototype.lastElementChild
> 

마지막 자식 노드(요소)를 반환.

## 자식 노드 존재 확인

> Node.prototype.hasChildNodes 메서드
> 

```jsx
const $num = document.getElementById(`number`);

        // #number 요소에 자식 노드가 존재하는지 확인

        // hasChildNodes 메서드
        // 텍스트 노드 포함
        console.log($num.hasChildNodes());    // T
```

> children.length 또는 Element.prototype.childElementCount 메서드
> 

```jsx
// #number 요소의 자식 노드 중 텍스트 노드가 아닌 요소 노드가 존재하는지 확인

        // 2. childern.length
        // 텍스트 노드 제외
        console.log(!!$num.children.length);    // F (0)

        // 3. childElementCount
        // 텍스트 노드 제외
        console.log(!!$num.childElementCount);  // F (0)
```

## 요소 노드의 텍스트 노트 탐색

> firstChild 프로퍼티
> 

요소 노드의 텍스트 노드는 요소 노드의 자식 노드이므로(요소-텍스트는 부모자식 관계) `firstChild 프로퍼티`로 접근 가능하다.

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <title>node-warking</title>
</head>
<body>
    <div id="foo">Hello, World!</div>
    <script>
        // 요소 노드의 텍스트 노드는 firstChilld 프로퍼티로 접근 가능하다
        console.log(document.getElementById(`foo`).firstChild);
    </script>
</body>
</html>
```

## 부모 노드 탐색

> Node.prototype.parentNode 프로퍼티
> 

단, `텍스트 노드`는 `리프 노드(leaf node, DOM 트리의 최종 노드)`이므로 부모 노드가 텍스트 노드인 경우는 없다.

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <title>node-warking</title>
</head>
<body>
    <ul id="goo">
        <li class="first">Kang</li>
        <li class="second">Jung</li>
    </ul>
    <script>
        // 부모 노드는 parentNode 프로퍼티로 접근 가능하다
        console.log(document.querySelector(`li.first`).parentNode);
    </script>
</body>
</html>
```

## 형제 노드 탐색

단, `어트리뷰트 노드`는 요소 노드와 연결만 되어있을 뿐 형제 노드는 아니기 때문에(부모 노드가 같지 않다) 반환되지 않는다 → `텍스트 노드` or `요소 노드`만 형제 노드로써 반환된다.

> Node.prototype.previousSibling
> 

형제 노드 中 자신의 이전 형제 노드를 탐색해 반환 (텍스트 노드/요소 노드)

> Node.prototype.nextSibling
> 

형제 노드 中 자신의 다음 형제 노드를 탐색해 반환 (텍스트 노드/요소 노드)

```jsx
// 형제 노드 탐색
        const $elem = document.querySelector(`ul#goo`);

        // 텍스트 노드, 요소 노드
        const { firstChild } = $elem;    // #text
        const { nextSibling } = firstChild;    // li.first
```

> element.prototype.previousElementSibling
> 

형제 노드 中 자신의 다음 형제 노드를 탐색해 반환 (요소 노드)

> element.prototype.nextElementSibling
> 

형제 노드 中 자신의 다음 형제 노드를 탐색해 반환 (요소 노드)

```jsx
// 요소 노드만
        const { lastElementChild } = $elem;    // li.third
        const { previousElementSibling } = lastElementChild;   // li.second
```

## 노드 정보 취득

> Node.prototype.nodeType
> 

노드 타입을 나타내는 `상수` 반환.

- 1 : 요소 노드 타입(Node.ELEMENT_NODE)
- 3 : 텍스트 노드 타입(Node.TEXT_NODE)
- 9 : 문서 노드 타입(Node.DOCUMENT_NODE)

> Node.prototype.nodeName
> 

노드의 이름을 `문자열`로 반환.

- 요소 노드 타입 : 대문자로 태그 이름 반환
- 텍스트 노드 타입 : #text 반환
- 문서 노드 타입 : #document 반환

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>node-warking</title>
</head>
<body>
    <div id="foo">Hello, World!</div>
    <script>
        // 문서 노드 정보 취득
        console.log(document.nodeType);    // 9
        console.log(document.nodeName);    // #document

        // 요소 노드 정보 취득
        const $foo = document.getElementById(`foo`);
        console.log($foo.nodeType);    // 1
        console.log($foo.nodeName);    // DIV

        // 텍스트 노드 정보 취득
        const $text = $foo.firstChild;
        console.log($text.nodeType);    // 3
        console.log($text.nodeName);    // #text
    </script>
</body>
</html>
```

# 요소 노드의 텍스트 조작하기

## nodeValue

> 텍스트 노드의 텍스트 자체(노드 객체의 값)를 취득
> 
- setter와 getter이 전부 존재하는 접근자 프로퍼티로서 `참조`와 `할당`이 전부 가능하다.
- 문서 노드나 요소 노드의 nodeValue 프로퍼티를 참조하면 `null`을 반환한다.

```jsx
<!DOCTYPE html>
<html lang="en">
<body>
    <div id="user">JungWoo</div>
    <script>
        // 문서 노드
        console.log(document.nodeValue);    // null

        // 요소 노드
        const $user = document.getElementById(`user`);
        console.log($user.nodeValue);    // null

        // 텍스트 노드
        const $name = $user.firstChild;
        console.log($name.nodeValue);   // JungWoo
    </script>
</body>
</html>
```

- nodeValue 프로퍼티에 값을 할당하여 텍스트 노드의 값(텍스트)을 변경하고 싶은 경우 다음과 같은 순서를 따라야 한다.
    1. 텍스트를 변경할 요소 노드 취득
    2. 요소 노드의 텍스트 노드 탐색(firstChild 프로퍼티 사용)
    3. 탐색한 텍스트 노드의 nodeValue 프로퍼티를 사용하여 값 변경
    

## textContent

> 요소 노드의 텍스트와 모든 자손 노드의 텍스트를 취득
> 

요소 노드의 textContent 프로퍼티를 참조하면 요소 노드의 콘텐츠 영역(시작 태그~종료 태그)내의 모든 텍스트가 반환된다. 단, 이 때 HTML 마크업은 무시된다.

```jsx
<!DOCTYPE html>
<html lang="en">
<body>
    <div id="user">Mark<span>JungWoo</span></div>
    <script>
        console.log(document.getElementById(`user`).textContent);   // MarkJungWoo
    </script>
</body>
</html>
```

- 요소 노드의 textcontent 프로퍼티에 문자열을 할당하면 요소 노드의 **모든 자식 노드가 제거**되고 할당한 문자열이 텍스트로 추가된다. 이 때 HTML 마크업은 파싱되지 않으므로 HTML 문법을 텍스트로 추가해도 의미가 없다.
- 유사한 동작을 하는 innerText 프로퍼티도 있지만 innerText 프로퍼티는 CSS에 순종적이고 상대적으로 속도가 느리므로 textContent 프로퍼티를 더 권장한다.

### nodeValue VS textContent

nodeValue나 textcontent나 텍스트를 취득할 수 있는 점은 똑같지만, nodeValue는 텍스트 노드를 참조할 때만 의미가 있으므로 textcontent를 사용할 때보다 코드가 복잡하다. 만약 요소 노드의 콘텐츠 영역에 자식 요소 노드가 없고 오직 텍스트만 존재할 경우 두 프로퍼티의 반환값은 같다.

# DOM 조작(DOM manipulation)

새로운 노드를 생성하여 DOM에 추가하거나 기존 노드를 삭제, 교체하는 것. 리플로우와 리페인트가 발생하는 원인이 되기 때문에 다룰 때 주의해야 한다. 

## innerHTML 프로퍼티

> 요소 노드의 HTML 마크업을 취득하거나 변경한다
> 

```html
<!DOCTYPE html>
<html lang="en">
<body>
    <ul id="user">Mark<span>JungWoo</span></ul>
    <script>
        const $name = document.getElementById(`user`).innerHTML;
        console.log($name); // Mark<span>JungWoo</span>
    </script>
</body>
</html>
```

- Element.prototype.innerHTML 프로퍼티는 getter, setter 모두 존재하는 접근자 프로퍼티이다.

요소 노드의 innerHTML 프로퍼티를 참조하면 요소 노드의 컨텐츠 영역(태그 시작~끝 사이)내에 포함된 모든 HTML 마크업을 문자열로 반환한다.

### innerHTML VS textContent

- textContent는 HTML 마크업을 무시하고 오로지 텍스트만 반환하지만 innerHTML은 `HTML 마크업이 포함된 문자열`을 그대로 반환한다는 점에서 차이가 있다.
- 문자열을 할당하면 요소 노드의 모든 자식 노드가 제거되고 재할당되는데, 이 때 textContent와 다르게 요소 노드의 innerHTML에 할당한 `HTML 마크업 문자열`은 렌더링 엔진에 의해 파싱되어 요소 노드의 자식으로 DOM에 반영된다.

```jsx
        // HTML 마크업이 파싱되어 DOM에 반영됨

        // 노드 교체
        $name.innerHTML = `Hi<span>there!</span>`;

        // 노드 추가
        $name.innerHTML += `<li>nct127</li>`;

        // 노드 삭제
        $name.innerHTML = ``;
```

### innerHTML 프로퍼티는 권장되지 않는다.

> innerHTML 프로퍼티를 사용한 DOM 조작은 구현이 간단하고 직관적이지만, **위험하다**.
> 
- 사용자로부터 입력받은 데이터(untrusted input data)를 요소 노드의 innerHTML 프로퍼티 그대로 할당할 경우 `크로스 사이트 스크립팅 공격`(XSS: Cross-Site Scripting Attacks)에 취약하므로 위험하다. HTML 마크업 내에 자바스크립트 악성 코드가 포함되어 있어도 이를 거르지 못하고 파싱 과정에서 그대로 실행되어버릴 수 있기 때문이다.

```jsx
<!DOCTYPE html>
<html lang="en">
<body>
    <div id="foo">hello</div>
    <script>
        // innerHTML 프로퍼티로 script 태그를 삽입하여 자바스크립트 코드가 실행되도록 함
        const $hi = document.getElementById(`foo`).innerHTML;
        $hi = `<script>alert(document.cookie)<\/script>`;
    </script>
</body>
</html>
```

다행히도 HTML5는 innerHTML 프로퍼티로 삽입된 자바스크립트 코드(<script>태그 내부)를 실행하지 않는다. 그러나 script 태그 없이도 공격은 가능하다.

```jsx
// 에러를 강제로 발생시켜 자바스크립트 코드가 실행되도록 함
        $hi = `<img src="x" onerror="alert(document.cookie)">`;
```

- 또한 innerHTML 프로퍼티로 DOM을 조작할 경우, 동작이 `비효율적`이다.

```jsx
<!DOCTYPE html>
<html lang="en">
<body>
    <ul id ="user">
        <li class="first">first</li>
    </ul>
</body>
<script>
    const $me = document.getElementById(`user`);
    $me.innerHTML += `<li class='second'>second</li>` ;
</script>
</html>
```

이 코드는 #user 요소에 자식 요소 li.second를 추가하는데, 이 때 li.first는 아무런 변경이 없으므로 다시 생성할 필요가 없다. 위 코드는 얼핏 보면 그냥 기존 문에 새로운 문을 얹는 것 처럼 보이지만, 사실 내부적으로는 **모든 자식 노드를 제거하고 li.first와 li.second를 생성하여 추가**하며 이는 상당히 낭비이다.

```jsx
$me.innerHTML = $me.innerHTML + `<li class='second'>second</li>` ;
```

즉, 유지되어도 상관 없는 기존 자식 노드까지 지워버리고 처음부터 새롭게 자식 노드를 생성하여  DOM에 반영하는 것이다.

- `삽입 위치 지정이 불가능`하다

```jsx
<!DOCTYPE html>
<html lang="en">
<body>
    <ul id ="user">
        <li class="first">first</li>
        <li class="third">third</li>
    </ul>
</body>
</html>
```

만약 이 코드에서 li.first 요소와 li.third 요소 사이에 새 요소를 삽입하고 싶은 경우 innerHTML 프로퍼티를 사용하면 삽입 위치를 지정할 수 없다. innerHTML은 아주 간단한 작업에서는 유용하지만, 기존 요소를 제거하고 위치를 제거할 수 없으므로 사용에 주의가 필요하다.

## insertAdjacentHTML 메서드

> 기존 요소를 제거하지 않으면서 위치를 지정해 새로운 요소를 삽입한다.
> 
- 첫 번째 인수 : position(위치)
    - beforebegin
    - afterbegin
    - beforeend
    - afterend
- 두 번째 인수 : DOMString(HTML 마크업 문자열)

```jsx
<!DOCTYPE html>
<html lang="en">
<body>
    <!-- beforebegin -->
    <div id="foo">
    <!-- afterbegin -->
    text
    <!-- beforeend     -->
    </div>
    <!-- afterend -->
</body>
<script>
    const $foo = document.getElementById(`foo`);
    
    $foo.insertAdjacentHTML(`beforebegin`, `<p>text</p>`);
    $foo.insertAdjacentHTML(`beforeend`, `<p>text</p>`);
</script>
</html>
```

기존 요소에는 영향을 주지 않고 새롭게 삽입될 요소만을 파싱하여 자식 노드에 추가하므로 innerHTML프로퍼티보다 효율적이고 빠르지만 크로스 사이트 스크립팅 공격에 취약하다는 점은 여전하다.

 

## 노드 생성과 추가

innerHTML 프로퍼티와 insertAdjacentHTML 메서드는 HTML 마크업 문자열을 파싱하여 노드를 생성하고 이를 DOM에 반영하는 구조였다.

다행히도, DOM은 노드를 직접 생성/삽입/삭제/치환하는 메서드를 제공한다.

### 요소 노드 생성

> Document.prototype.createElement(tagName) 메서드
> 
- 요소 노드를 생성하여 반환한다. 인수로는 태그 이름을 문자열로 전달한다.
- 이때 생성된 요소 노드는 단순히 ‘생성’만 됐을 뿐, 상속 관계에 결합되어 DOM 트리에 포함되지는 않는다. 생성된 요소 노드를 DOM에 포함되게끔 하는 `추가적인 절차`가 필요하다.

생성된 요소 노드는 아무런 자식 노드를 가지고 있지 않으므로 텍스트 노드도 없는 상태이다. 텍스트 노드를 생성해 보자.

### 텍스트 노드 생성

> Document.prototype.createTextNode(text) 메서드
> 
- 텍스트 노드를 생성하여 반환한다. 인수로는 텍스트 노드의 값(컨텐츠)을 전달한다.
- 이 때 생성된 텍스트 노드 역시 단순히 생성만 됐을 뿐, 요소 노드의 자식 노드로 추가되어 DOM 트리에 포함되지 못한 상태이다.

생성된 텍스트 노드를 요소 노드에 추가해보자.

### 텍스트 노드를 요소 노드의 자식 노드로 추가

> Node.prototype.appendChild(childNode) 메서드
> 

메서드를 호출한 노드의 마지막 자식 노드로 인수로 전달된 노드를 추가한다. 메서드의 인수로 텍스트 노드를 전달하여 요소 노드의 자식으로 추가하면 된다.

그러나 텍스트 노드와 요소 노드는 상속 관계로 연결되었어도, 아직 DOM에 추가되지는 않은 상태다. 지금까지의 예제처럼 요소 노드에 자식 노드가 하나도 없는 경우 노드를 추가하고 싶다면 textContent 프로퍼티를 사용하는 편이 편하다(물론 덮어쓰기 되는 건 조심해야 한다)

### 요소 노드를 DOM에 추가

> Node.prototype.appendChild 메서드
> 

텍스트 노드와 부자 관계로 연결한 요소 노드를 #fruits 요소 노드의 마지막 자식 요소로 추가한다.

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>DOM 조작</title>
</head>
<body>
    <ul id="user">
        <li class="first">kang</li>
    </ul>
</body>
<script>
    // 직접 노드를 생성하기

    // a. 요소 노드 생성
    const $node = document.createElement(`li`);
    // b. 텍스트 노드 생성
    const text = document.createTextNode(`Lee`);

    // c. 요소 노드와 텍스트 노드를 상속 관계로 연결
    $node.appendChild(text);
    // $node처럼 자식 노드가 하나도 없는 경우 textContent를 사용하면 편하다
    // $node.textContent = `Lee`;

    // d. 요소 노드를 DOM 트리에 추가
    $user.appendChild($node);
</script>
</html>
```

단 하나의 요소 노드를 생성하여 DOM에 한 번 추가하므로 **DOM은 한 번 변경**되며, 리플로우와 리페인트 또한 한 번 일어난다. 만약 여러 개의 노드를 생성하여 DOM을 조작한다면 어떨까?

## 복수의 노드 생성과 추가

### 반복문 사용

단일 요소 노드 생성 과정을 forEach문을 통해 반복하였다

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>DOM 조작</title>
</head>
<body>
    <ul id="fruit">
        <li>cherry</li>
    </ul>
</body>
<script>
    // 여러 개의 노드를 생성 및 추가하기
    const $fruit = document.getElementById(`fruit`);

    const fruit = [`apple`, `banana`, `mellon`];
    fruit.forEach(v=> {
        const $node = document.createElement(`li`);
        const text = document.createTextNode(v);

        $node.appendChild(text);
        $fruit.appendChild($node);
    })
</script>
</html>
```

이러한 방식은 3개의 요소 노드를 생성하여 DOM에 3번 추가하기 때문에 **DOM이 3번 변경된다.** DOM 변경은 비용이 많이 들기 때문에 최대한 적은 것이 좋으므로 본 방식은 비효율적이다.

### 임시 컨테이너 사용

3개의 요소 노드를 하나의 컨테이너 요소에 담아 컨테이너 요소를 DOM에 1번만 추가하여 횟수를 줄인다

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>DOM 조작</title>
</head>
<body>
    <ul id="fruit">
        <li>cherry</li>
    </ul>
</body>
<script>
    // 여러 개의 노드를 DOM에 추가하기
    const $fruit = document.getElementById(`fruit`);
    const fruit = [`blueberry`, `orange`, `tomato`];

    // 임시 컨테이너 사용
    const $container = document.createElement(`div`)

    fruit.forEach(v=> {
        const $node = document.createElement(`li`);
        const text = document.createTextNode(v);

        $node.appendChild(text);
        $container.appendChild($node);
    })

    $fruit.appendChild($container);
</script>
</html>
```

아까보다 성능 면에선 유리할지 몰라도 컨테이너 요소 자체가 불필요한 요소기 때문에 바람직하지 않다.

### DocumentFragment 노드 사용

노드 객체 타입 중 하나로, 부모 노드가 없으므로 기존 DOM과는 별도로 존재하므로 컨테이너 역할에 제격이다. 또한 DocumentFragment 노드를 DOM에 추가하면 **자신은 제거되고 자식 노드만이 DOM에 추가된다.**

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>DOM 조작</title>
</head>
<body>
    <ul id="fruit">
        <li>cherry</li>
    </ul>
</body>
<script>
    // 여러 개의 노드를 DOM에 추가하기
    const $fruit = document.getElementById(`fruit`);
    const fruit = [`blueberry`, `orange`, `tomato`];

    // DocumentFragment 노드 사용
    const $fragment = document.createDocumentFragment();

    fruit.forEach(v=> {
        const $node = document.createElement(`li`);
        const text = document.createTextNode(v);

        $node.appendChild(text);
        $fragment.appendChild($node);
    })

    $fruit.appendChild($fragment);
</script>
</html>
```

여러 개의 요소 노드를 DOM에 추가해야 하는 경우, DocumentFragment 노드를 활용한 반복문을 사용하면 된다.

 

## 노드 삽입

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>DOM 조작</title>
</head>
<body>
    <ul id="fruit">
        <li>cherry</li>
    </ul>
</body>
<script>
    // 노드 삽입

    const $fruit = document.getElementById(`fruit`);

    // 마지막 노드로 삽입
    const $newNode = document.createElement(`li`);
    $newNode.textContent = `grape`;
    $fruit.appendChild($newNode);

    // 지정한 위치에 삽입
    const $newNode2 = document.createElement(`li`);
    $newNode2.textContent = `apple`;
    $fruit.insertBefore($newNode2, $fruit.firstElementChild);
</script>
</html>
```

### 일반적인 노드 삽입(마지막 요소로 추가)

> Node.prototype.appendChild() 메서드
> 

인수로 전달받은 노드를 자신을 호출한 노드의 마지막 자식 노드로 DOM에 추가한다.

```jsx
// 노드 삽입

    const $fruit = document.getElementById(`fruit`);

    // 마지막 노드로 삽입
    const $newNode = document.createElement(`li`);
    $newNode.textContent = `grape`;
    $fruit.appendChild($newNode);
```

### 지정한 위치에 노드 삽입

> Node.prototype.insertBefore(newNode, childNode) 메서드
> 

첫 번째 인수로 전달받은 노드를 두 번째 인수로 전달받은 노드 앞에 삽입한다. 당연히 위치 역할을 하는 두 번째 인수는 호출한 노드의 자식이어야 한다. 그렇지 않으면 DOMException 에러가 발생한다. 두 번째 인수가 null이면 appenChild와 동일하게 동작한다.

```jsx
// 지정한 위치에 삽입
    const $newNode2 = document.createElement(`li`);
    $newNode2.textContent = `apple`;
    $fruit.insertBefore($newNode2, $fruit.firstElementChild);
```

![nodeappend PNG](https://user-images.githubusercontent.com/97890886/170255396-1cd8fe7c-027d-49e7-a183-1ed49bc8283c.png)

## 노드 이동

appendChild나 insertBefore 메서드를 사용하여 **이미 존재하는 노드를 DOM에 다시 추가** → 기존 위치에서 그 노드가 제거되고 새로운 위치에 동일한 노드가 추가된다. 이런 식으로 노드를 “이동”시킬 수 있다.

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <title>DOM 조작</title>
</head>
<body>
    <ul id="fruits">
        <li>cherry</li>
        <li>orange</li>
        <li>banana</li>
    </ul>
</body>
<script>
    const $fruits = document.getElementById(`fruits`);
    
    // 이미 존재하는 요소를 취득
    const [$cherry, $orange, $banana] = $fruits.children;

    // 노드 이동
    // 마지막 노드로 이동
    $fruits.appendChild($cherry);   // orange - banana - cherry

    // 위치를 지정하여 이동(마지막 자식 노드 앞으로)
    $fruits.insertBefore($orange, $fruits.lastElementChild);    // banana - orange - cherry
</script>
</html>
```

## 노드 복사

> Node.prototype.cloneNode([deep: true | false]) 메서드
> 

노드의 사본을 생성하여 반환하되,

- 인수로 true를 전달 : 깊은 복사(해당 노드의 자손 노드까지 포함사여 사본 생성)
- 인수로 false를 전달 : 얕은 복사(해당 노드만의 사본 생성)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <title>DOM 조작</title>
</head>
<body>
    <ul id="fruits">
        <li>tomato</li>
    </ul>
</body>
<script>
    const $fruits = document.getElementById(`fruits`);
    const $tomato = $fruits.firstElementChild;

    // 노드 복사

    // 얕은 복사
    // 텍스트(자식) 노드가 없는 빈 사본이 생성됨
    const $shallowClone = $tomato.cloneNode();
    $shallowClone.textContent = `melon`;
    $fruits.appendChild($shallowClone);

    // 깊은 복사
    // 자식 노드가 포함된 사본이 생성됨
    const $deepClone = $fruits.cloneNode(true);
    $fruits.appendChild($deepClone);
</script>
</html>
```

![nodecopy PNG](https://user-images.githubusercontent.com/97890886/170255505-cb52b1d7-5b4c-4795-ba05-cd598f39b20f.png)

## 노드 교체

> Node.prototype.replaceChild(newChild, oldChild) 메서드
> 

자신을 호출한 노드의 자식 노드(oldChild)를 다른 노드(newChlid)로 교체한다.

- 첫 번째 인수 : 교체할 새로운 인수
- 두 번째 인수 : 교체될 기존 인수

oldChlid 노드는 DOM에서 제거된다.

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <title>DOM 조작</title>
</head>
<body>
    <ul id="fruits">
        <li>peach</li>
    </ul>
</body>
<script>
    // 노드 교체
    const $fruit = document.getElementById(`fruits`);
    const $peach = $fruit.firstElementChild;

    // 교체할 노드 생성
    const $mango = $peach.cloneNode();
    $mango.textContent = `mango`;

    $fruit.replaceChild($mango, $peach);
</script>
</html>
```

## 노드 삭제

> Node.prototype.removeChild(child) 메서드
> 

인수로 전달받은 자식 노드를 DOM에서 삭제한다. 둘은 상속 관계여야 한다 당연하지만

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <title>DOM 조작</title>
</head>
<body>
    <ul id="foods">
        <li>yogurt</li>
        <li>chocolate</li>
    </ul>
</body>
<script>
    const $foods = document.getElementById(`foods`);
    const $yogurt = $foods.firstElementChild;

    $foods.removeChild($yogurt);
</script>
</html>
```