# 클로저

> 함수와 그 함수가 선언된 렉시컬 환경과의 조합

클로저(closure)는 자바스크립트 고유의 특성이 아닌, 함수형 프로그래밍 언어에서 사용되는 중요한 개념이다. 정의만 보면 상당히 난해하므로, 차근차근 알아가보자.


# 렉시컬 스코프

자바스크립트 엔진은 함수를 `어디서 호출`했느냐가 아니라, `어디서 정의`했느냐에 따라 상위 스코프를 결정하는데 이를 **렉시컬 스코프(정적 스코프)**라고 한다.

```jsx
const x = 1;

function foo() {
    const x = 10;
    // goo는 전역 코드에서 정의되었다
    // 어디서 호출되든간에 전역 스코프에 속해있다
    // 10(foo함수 지역 스코프)이 아닌 1이 나온다
    goo();
}

// 이미 상위 코드(전역 코드) 평가 시점에 평가됨
// 상위 스코프(전역 렉시컬 환경)를 [[Environment]]에 저장하여 기억
function goo() {
    console.log(x);
}

foo();    // 1
goo();    // 1
```

또한 스코프의 실체는 실행 컨텍스트의 렉시컬 환경이며, 렉시컬 환경의 ‘외부 렉시컬 환경에 대한 참조’를 통해 스코프 체인이 구현된다. 즉 렉시컬 스코프를 보다 정확하게 말하자면,

> 렉시컬 환경의 ‘외부 렉시컬 환경에 대한 참조’에 저장될 값(===상위 스코프)에 대한 참조는 함수 정의가 평가되는 시점에(런타임 이전에) `함수가 정의된 환경`으로 결정된다.
> 

## 함수 객체의 내부 슬롯 [[Environment]]

렉시컬 스코프가 뭔지는 알겠다.이제 보다 정교하게 생각해보자.

함수는 자신이 정의된 환경(===상위 스코프. 함수 자체는 지역 스코프를 가지니 자신이 정의된 환경이 상위 스코프이다.)을 어떻게 기억하는가?

함수는 `내부 슬롯 [[Environment]]`에 `running 실행 컨텍스트의 렉시컬 환경에 대한 참조 값`을 저장하여 자신이 정의된 환경을 기억한다.

- `전역`에서 정의된 함수 선언문 : 상위 코드인 전역 코드가 평가되는 시점에 함께 미리 평가되어 함수 객체 생성. 이 때 내부 슬롯에 running 실행 컨텍스트의 렉시컬 환경`(전역)` 저장
- `함수 내부`에서 정의된 함수 선언문 : 상위 코드인 외부 함수 코드가 평가되는 시점에 함께 미리 평가되어 함수 객체 생성. 이 때 내부 슬롯에 running 실행 컨텍스트의 렉시컬 환경의 참조`(외부 함수)` 저장

> 상위 코드를 평가하는 도중 함수 객체 내부 슬롯 [[Environment]]에 저장된 참조 값 = running 실행 컨텍스트의 렉시컬 환경 = (이후 생성될)본인의 실행 컨텍스트의 렉시컬 환경의 ‘외부 렉시컬 환경에 대한 참조’에 저장될 참조 값


또한 함수 객체는 이를 자신이 존재하는 한, 평생 기억한다.

## 렉시컬 스코프의 실체 정리

```jsx
// 전역 코드 평가
// var 변수와 함수 선언문 함수도 평가되어 함수 객체 생성
// 이 때 함수 객체 내부 슬롯 [[Environment]]에
// running 실행 컨텍스트의 렉시컬 환경 참조 저장

// 전역 코드 실행
const x = 1;

// 함수 코드 평가
// 이 때 함수 렉시컬 환경 中 '외부 렉시컬 환경에 대한 참조' 에는
// [[Environment]]의 값이 할당됨
function foo() {
    const x = 10;

    // 함수 코드 평가
    function goo() {
        console.log(x);    // 10
    }
    goo();
}
foo();
```

1. 전역 코드 평가

전역 실행 컨텍스트가 생성되고, 전역 렉시컬 환경이 생성되며 var 변수와 함수 선언문 함수가 평가되어 함수 객체를 만들고 전역 객체의 프로퍼티가 된다.

이 때 **함수 객체 내부 슬롯 [[Environment]] 은 running 실행 컨텍스트의 렉시컬 환경을 가리키게** 된다.(==상위 스코프 기억) 이 때의 running 실행 컨텍스트는 전역이므로 전역 렉시컬 환경의 참조값을 가지게 된다.

1. 전역 코드 실행

코드가 순차적으로 실행되다가 함수 호출문을 만나서 foo함수로 코드 제어권이 넘어간다.

1. 함수 코드 평가

함수 실행 컨텍스트가 생성되고, 함수 렉시컬 환경이 생성된다. 이 때 **함수 렉시컬 환경의 구성요소 중 ‘외부 렉시컬 환경에 대한 참조’에, (1단계에서 참조된) [[Environment]]의 참조값이 할당**된다.

이런 식으로 상위 스코프와 스코프 체인이 구현되는 것이며, 이것이 바로 `렉시컬 스코프`의 실체이다.

이제 클로저의 정의를 다시 한 번 보자.

> 함수와 그 함수가 선언된 렉시컬 환경과의 조합
> 

“함수가 선언된 렉시컬 환경”이 이제 뭔지 확실히 알았다. 이제 이를 바탕으로 클로저가 무엇인지 자세히 살펴보도록 하자.

# 클로저와 렉시컬 환경

```jsx
const x = 1;

function outer() {
    const x = 2;
    const inner = function() {
        console.log(x);
    }
    return inner;
}
// outer 함수 종료 (수명 다함)
// outer 함수 실행 컨텍스트는 실행 컨텍스트에서 pop되어 제거된다
// 지역변수 역시 같이 수명이 끝났으므로, 더이상 접근이 불가능해 보인다

// inner 함수 불러오기
// 외부 함수 outer을 호출하면 중첩 함수 inner을 반환하므로
// 중첩 함수 inner을 참조하는 표현이나 다름없다
const foo = outer();
// 이미 실행 컨텍스트 스택에서 제거된 outer 함수의 지역 변수 x가 살아있다?!
foo();    // 2
```

클로저는 함수와 그 *****함수가 선언된 렉시컬 환경과의 조합*****이라고 했다.

이는 즉 `함수`와 그 `상위 스코프`를 의미한다.

![closure](https://user-images.githubusercontent.com/97890886/165298067-09209cdc-ba37-4640-916f-b9a7bac3befb.png)

1. 자바스크립트의 모든 함수는 위에서 설명한 방식으로 상위 스코프를 기억하며, 이는 함수가 존재하는 한 계속해서 유지된다. 상위 스코프(부모)를 언제나 참조 및 변경할 수 있다.
2. 또한 실행 컨텍스트가 실행 컨텍스트 스택에서 pop된다고 하더라도 렉시컬 환경까지 같이 소멸하는 것은 아니다.

따라서, outer 함수가 자신의 할 일을 마치고 종료되어 실행 컨텍스트 스택에서 pop되어 제거된다고 하더라도 **outer 함수의 렉시컬 환경은 inner 함수의 내부 슬롯 [[Environment]]에 의해 여전히 참조되고 있다**. 그리고 가비지 컬렉션은 참조되고 있는 메모리 공간은 해제하지 않는다.

이는 곧 중첩 함수가 외부 함수보다 더 오래 유지되는 경우, 중첩 함수가 이미 생명 주기가 종료된 외부 함수의 변수를 참조할 수 있음을 의미한다. 이러한 중첩 함수를 `클로저(clousure)`라고 한다.

outer 을 호출하면 inner이 반환되므로, 결국 inner을 호출한 것과 같은데, 이렇게 inner을 호출하면

![closure2](https://user-images.githubusercontent.com/97890886/165298116-bf0b08c6-0d7f-45e8-a5f6-5b0e9cfb0b54.png)

일반 함수 실행 컨텍스트 단계처럼 진행된다

1. inner 함수의 실행 컨텍스트 생성
2. inner 함수의 렉시컬 환경 생성 : 이 때 ‘외부 렉시컬 환경에 대한 참조’에 inner 함수의 **[[Environment]]의 참조값(=outer의 렉시컬 환경)이 할당된다.**

이렇게 중첩 함수 inner은 외부 함수 outer보다 더 오래 생존했으며, 이 때 이들은 외부 함수(의 실행 컨텍스트)의 생존 여부와 상관없이, 자신이 정의된 위치에 의해 결정되었던 상위 스코프를 계속해서 기억한다. → 클로저

자바스크립트의 모든 함수는 상위 스코프를 기억하기 때문에 이론적으로는 모든 함수가 클로저지만, 클로저는 **상위 스코프의 식별자를 참조**해야 비로소 의미를 가지기 때문에 일반적으로 이런 경우에만 클로저의 본질에 부합하다. 즉

- 상위 스코프의 식별자를 참조할 것
- 외부 함수보다 오래 살아남을 것


이런 경우를 전부 만족할 경우에만 `클로저`라고 하는 것이 일반적이다.

클로저는 이론적으로는 상위 스코프를 계속해서 기억해야 하지만, 자바스크립트 엔진은 최적화가 잘 되어 있기 때문에 상위 스코프를 전부 기억하는 것이 아닌 클로저가 참조하고 있는 식별자만을 기억한다. 이 때, 이렇게 클로저에 의해 참조되는 상위 스코프의 변수를 `자유 변수`라고 한다. 즉 클로저는 자유 변수에 묶여있는(자유 변수에 의해 닫혀있는, closed) 함수인 것이다.

이러한 클로저는 자바스크립트의 강력한 기능이기 때문에 여러 군데에 사용할 수 있다.

# 클로저와 정보 은닉

> 클로저는 상태(state)를 안전하게 은닉(information hiding)하고 특정 함수에게만 상태 변경을 허용하기 위해, 즉 보안을 위해 사용한다.
> 

예를 들어, 호출한 횟수를 누적하여 출력하는 카운터에 대한 코드를 작성해보자.

```jsx
let num = 0;

const increase = function() {
    return ++num;
};

console.log(increase());    // 1
console.log(increase());    // 2
console.log(increase());    // 3
```

이는 좋은 함수가 아니다. 왜냐하면 상태(누적 횟수)를 안정적으로 체크하기 위해서는 increase가 접근하기 전까지 num 변수의 값이 변하면 안 된다. 

*상태(num 변수의 값)는 increase 함수만이 접근할 수 있어야 한다.*

그러나 위 코드의 num은 전역 변수로, 암묵적 결합에 의해 의도치 않게 상태가 변경될 수 있다.

> `문제점` : 전역 변수 → 의도치 않은 상태 변경에 의한 오류   
> `해결` :  num을 increase의 지역 변수로 만들어보자

```jsx
const increase = function() {
    let num = 0;
    return ++num;
};

console.log(increase());    // 1
console.log(increase());    // 1
console.log(increase());    // 1
```

상태 변경에 대한 위험은 해결됐다. 그러나 이번에는 원하는 값이 나오지 않는다.  왜냐하면 실행될 때 마다 지역 변수 num이 다시 선언되고 다시 0으로 초기화되기 때문이다.

> `문제점` : 상태가 변경되기 전(이전 상태)를 유지하지 못하고 있다

여기서 유용한 것이 `클로저`이다.

```jsx
const increase = (function() {
    let num = 0;
    
    return function() {
        return ++num;
    };
}());

console.log(increase());    // 1
console.log(increase());    // 2
console.log(increase());    // 3
```

- increase 외부 함수는 즉시 실행 함수로, 실행이 완료되자마자 소멸한다(실행 컨텍스트 스택에서 pop되어 제거된다)
- 그러나 렉시컬 환경은 아직 남아있고, 이 렉시컬 환경은 클로저가 참조 중이다.

*****클로저는 자신이 정의된 위치에 의해 결정된 상위 스코프를 기억한다.*****

1. 위 코드가 실행되어 increase 함수가 호출되면, increase는 `즉시 실행 함수`이므로 호출된 이후 소멸하고 `클로저`는 increase 변수에 할당되어 호출된다.
 
2. 클로저는 상위 스코프인 increase 즉시 실행 함수를 기억하고 있기 때문에 자유 변수 num을 어디서 호출하든지 참조, 변경할 수 있다.
 
3. 즉시 실행 함수는 한 번만 실행되기 때문에 2번째 코드와 같은 문제점(반복해서 초기화)은 발생하지 않는다. num 변수는 private 상태나 다름없다.

> 클로저를 사용하면 **이전 상태를 기억**한 채로 **상태를 안전하게 `은닉`**한다.  특정 함수에게만 상태를 허용하여 상태를 안전하게 변경,유지할 수 있다.

```jsx
const counter = (function() {
    let num = 0;

    return {
        increase() {
            return ++num;
        },
        decrease() {
            return num>0 ? --num : 0;
        },
    };
}());

console.log(counter.increase());    // 1
console.log(counter.increase());    // 2

console.log(counter.decrease());    // 1
console.log(counter.decrease());    // 0
```

즉시 실행 함수 내부의, 즉시 실행 함수가 반환하는 객체 리터럴은 즉시 실행 함수의 실행 단계에서 평가되어 객체가 되고 내부의 메소드도 같이 평가되어 등록된다. 이 때 객체 리터럴의 중괄호는 코드 블록이 아니므로 별도의 스코프를 생성하지 않는다.

메서드 increase와 decrease는 클로저이다. 외부 함수의 num을 자유 변수로써 참조할 수 있다.  이 메서드들의 상위 스코프는 메서드가 평가되는 시점에 running 중인 실행 컨텍스트(위에서 설명했듯이 counter)의 렉시컬 환경이기 때문이다.

이는 생성자 함수로도 표현할 수 있다.

```jsx
const Counter = (function() {
    // 상태
    // 즉시 실행 함수 내의 변수 -> private
    let num = 0;

    function Counter() {
        // 만약 상태를 프로퍼티로 표현했다면?
        // this.num = 0;
        // 생성자 함수 Counter가 생성할 인스턴스의 프로퍼티 -> public
    };

    // 클로저
    // 자신의 함수 정의가 평가되어 함수 객체가 될 때
    // running 실행 컨텍스트(즉시 실행 함수)의 렉시컬 환경을 저장
    // 즉시 실행 함수의 자유 변수 num 참조 가능
    Counter.prototype.increase = function() {
        return ++num;
    };

    // 클로저
    Counter.prototype.decrease = function() {
        return num>0 ? --num : 0;
    };

    return Counter;
}());

// 인스턴스 생성
// 생성자 함수 Counter의 프로토타입을 통해 increase, decrease 메서드를 상속받는다 
const counter = new Counter();

console.log(counter.increase());
console.log(counter.increase());

console.log(counter.decrease());
console.log(counter.decrease());
```

생성자 함수와 그에 대한 프로토타입 메서드를 선언하고 즉시 실행 함수로 묶은 구조이다. 또 즉시 실행 함수 내부에서 카운트 상태 변수를 선언하였다.

> 클로저는 외부 상태 변경이나 가변 데이터를 피하고, 불변성을 지향하는 `함수형 프로그래밍`에서 부수 효과를 억제하여 오류를 피하고 프로그램에 안정성을 높이는 데에 자주 사용된다.
> 

```jsx
// 함수를 인수로 전달받고, 함수를 반환하는 "고차 함수"
// 클로저(자유 변수 counter를 기억)를 반환한다
function makeCounter(aux) {

    // 상태를 나타내는 변수
    // private
    let counter = 0;

    // 클로저 반환
    return function() {
        // 인수로 전달받은 보조 함수에 상태 변경을 위임
        // 보조 함수에 상태(를 나타내는 변수)를 전달하여
        // 인수에 어떤 보조 함수가 오느냐에 따라 상태가 상이하게 변경된다
        counter = aux(counter);
        return counter;
    };
}

function increase(n) {
    return ++n;
}

function decrease(n) {
    return --n;
}

const increaser = makeCounter(increase);    // 함수를 인자로 전달할 때
                                            // increase [O] inscrease() [X] 
console.log(increaser());
console.log(increaser());

const decreaser = makeCounter(decrease);
console.log(decreaser());
console.log(decreaser());
```

- makeCounter 함수는 `고차 함수`다.

함수를 인자로 전달받고, 클로저(함수)를 반환한다.

- 클로저 함수

(자신이 선언되었을 때의 running 실행 컨텍스트의 렉시컬 환경인 makeCounter 함수의 스코프에 속한) 자유 변수 counter을 기억하는 함수이다.

makeCounter 함수는 인자로 전달받은 보조 함수를 합성하여 자신이 반환하는 함수의 동작을 변경할 수 있다. 쉽게 말하자면, increase를 받으면 ++counter 하여 반환할거고 decrease를 받으면 --counter해서 반환할 거다.

### 주의점

주의할 점은 이렇게 함수를 호출하여 반환할 때 마다 독립된 렉시컬 환경이 생성된다는 것이다.

+ const increaser = makeCounter(increase);  문에서 makeCounter 함수가 호출되면

  1. makeCounter 함수의 실행 컨텍스트가 생성 → 여러 과정을 지나 → 함수 실행이 끝나고(마지막 문이 함수 객체를 생성하여 반환하는 문이다)클로저를 반환하면서 소멸된다
  2. 1에서 반환된 클로저는 전역 변수 increaser에 할당된다.
  3. makeCounter 실행 컨텍스트가 삭제되어도  2에서 할당된 클로저가 내부 슬롯 Environment로 렉시컬 환경을 참조하고 있기 때문에, 계속해서 상태(자유 변수)를 참조 가능하다

+ const decreaser = makeCounter(decrease); 문이 실행되면

위와 같은 동작이 똑같이 한번 더 발생하는 것이다. 즉 계속해서 makeCounter 실행 컨텍스트가 새로 생성되고 이에 따른 렉시컬 환경이 새로 생성되고 이 각각 다른 렉시컬 환경이 각각 increaser와 decreaser라는 다른 변수에 할당되고....

그러니까 결론은 이거다.

> 함수는 호출할때마다 독립된 렉시컬 환경을 갖기 때문에 상태를 유지하기 위한 자유 변수 counter을 서로 공유하지 않는다.

increaser 2번 호출해서 1, 2 됐으면 다음에 decreaser 2번 호출해서 “그 전 값과 이어서” 1,0 되는 것이 아니라

- 1, 2 (처음부터 0에서시작)

- -1, -2 (이어서x 처음부터 0에서시작)

각각 이런 결과가 나오게 되는 것이다.

독립된 카운터가 아니라 연동하여 증감되는 카운터를 만들려면, 렉시컬 환경을 공유하는 클로저가 필요하다. 어떻게 구현할까? 간단하다. **makeCounter 함수를 여러번 호출하지 않는 것이다.**

```jsx
// 함수를 반환하는 고차 함수
// + 즉시실행함수(중복 호출 불가능. 한 번만 가능)
const counter = (function() {
    // 상태 유지를 위한 자유 변수
    let count = 0;

    // 함수를 인수로 전달받는 클로저 반환
    return function(aux) {
        // 인수로 전달받은 함수의 상태 변경 위임
        count = aux(count);
        return count;
    };
}());

// 보조 함수
function increase(n) {
    return ++n;
}
function decrease(n) {
    return --n;
}

// counter 호출 -> 함수를 인수로 전달받는 클로저 반환(호출)
// 인수로 보조 함수를 전달하며 호출
console.log(counter(increase));     // 1
console.log(counter(increase));     // 2

console.log(counter(decrease));     // 1
console.log(counter(decrease));     // 0
// 자유 변수를 공유한다.
```

# 캡슐화와 정보 은닉

캡슐화는 객체의 상태(프로퍼티)와 프로퍼티를 참조,조작하는 동작(메서드)를 하나로 묶는 것을 의미하며, 특정 프로퍼티나 메서드를 감출 목적(은닉, information hiding)으로 사용하기도 한다.

정보 은닉을 통해 → 적절치 못한 접근으로 객체 상태가 변경되는 것을 방지(정보 보호), 객체 간 상호 의존성(결합도)을 낮춘다.

대부분의 객체지향 프로그래밍 언어는 클래스의 멤버(프로퍼티,메서드)에 접근 제한자를 선언하여 공개 범위를 한정할 수 있지만, 자바스크립트는 이를 지원하지 않는다.

그리고 안타깝게도, 클로저를 아무리 적극적으로 활용해봤자 private과 public, protected와 같은 접근 제한자를 사용한 캡슐화와 정보 은닉을 완전히 흉내낼 수는 없다. 

한 번 예시를 들어 보겠다.

```jsx
// 생성자 함수 Person
function Person(name, age) {
    // public한 프로퍼티 name
    this.name = name;
    // private한 프로퍼티 age
    let a_ge = age;

    // public한 인스턴스 메서드 sayHi
    this.sayHi = function() {
        console.log(`Hi! ${this.name}, ${a_ge}`);
    };
}

// arguments를 전달하며 인스턴스 생성
const me = new Person(`kang`, 22);

// 메서드 호출
me.sayHi();    // Hi! kang, 22

// 각각의 프로퍼티에 접근합니다
console.log(me.name);   // kang
console.log(me.a_ge);   // undefined
```

> `문제` : sayHi 는 인스턴스 메서드이므로 인스턴스(객체)가 생성될 때마다 중복되어 만들어진다   
> `해결` → 프로토타입 메서드로 빼서 한 번만 만들어지게 해 보겠다

```jsx
// 생성자 함수 Person
function Person(name, age) {
    // public한 프로퍼티 name
    this.name = name;
    // private한 프로퍼티 age
    let a_ge = age;
}

Person.prototype.sayHi = function() {
    console.log(`Hi! ${this.name}, ${a_ge}`);   // ReferenceError: a_ge is not defined
};

// arguments를 전달하며 인스턴스 생성
const me = new Person(`kang`, 22);
const you = new Person(`lee`, 20);

// 메서드 호출
me.sayHi();    

// 각각의 프로퍼티에 접근합니다
console.log(me.name);   
console.log(me.a_ge);   

// 메서드 호출
you.sayHi();    

// 각각의 프로퍼티에 접근합니다
console.log(you.name); 
console.log(you.a_ge);
```

ReferenceError: a_ge is not defined


> `문제` :따로 뺐더니 생성자 함수의 지역 변수 a_ge에는 접근이 불가능해져 버렸다.   
> `해결` → 즉시 실행 함수로 묶어 참조할 수 있게 해 보겠다

```jsx
// 즉시 실행 함수
const Person = (function() {

    let a_ge = 0;    // private
        
    // 생성자 함수 Person
    function Person(name, age) {
        this.name = name;   // public
        a_ge = age;
    }

    Person.prototype.sayHi = function() {
        console.log(`Hi! ${this.name}, ${a_ge}`);   // ReferenceError: a_ge is not defined
    };

    return Person;
}());

// arguments를 전달하며 인스턴스 생성
const me = new Person(`kang`, 22);
const you = new Person(`lee`, 20);

// 메서드 호출
me.sayHi();    // Hi! kang, 20

// 각각의 프로퍼티에 접근합니다
console.log(me.name);   // kang
console.log(me.a_ge);   // undefined

// 메서드 호출
you.sayHi();    //  Hi! lee, 20

// 각각의 프로퍼티에 접근합니다
console.log(you.name);    // lee
console.log(you.a_ge);    // undefined
```

그러나 이 경우 치명적인 문제점이 있는데, 바로**값의 상태가 유지되지 않는다**는 것이다.

> `문제` : Person 생성자 함수가 여러 개의 인스턴스를 생성할 경우, a_ge의 변수의 상태가 유지되지 않는다.
> `원인` : 생성자 함수+프로토타입 메서드는 하나로 묶여 즉시 실행 함수로 단 한 번만 실행되는 클로저이다.

1. 프로토타입 메서드는 즉시 실행 함수가 호출될 때 평가되어 함수 객체로써 생성된다. 이 때 내부 슬롯 Environment에 running 실행 컨텍스트인 즉시 실행 함수의 렉시컬 환경을 저장한다.
2. 그리고 new로 생성되는 모든 인스턴스는 이 프로토타입 메서드를 공유하며, 프로토타입 메서드는 단 한 번 실행되는 클로저기 때문에 어떤 인스턴스로 호출되더라도 **하나의 동일한 상위 스코프**를 사용하게 된다. 그래서 a_ge를 각각 다루는게 아니라 지들끼리 전부 같이 돌려쓰는거다... 같은 상위 스코프를 돌려쓰니까... 이는 상당히 치명적이다.

이렇게 *자바스크립트는 정보 은닉을 완전하게 지원하지 않는다.*
(방법이 아주 없는 것은 아니다. private 클래스 필드 정의 제안을 통해 구현하는 것이다 이는 후에 공부해보겠다.)

# 클로저를 사용할 때 자주 하는 실수

```jsx
var funcs = [];

for(var i = 0; i<3; i++) {
    funcs[i] = function() {
        return i;
    }
}

for (var j = 0; j<funcs.length; j++) {
    console.log(funcs[j]());    // 3 3 3
}
```

1. for문으로 빈 배열의 요소에 순차적으로 함수를 할당한다. 이 때 이 함수는 자신의 번호를 반환하는 함수이다.
2. for문으로 함수를 순차적으로 호출한다.
3. 0 1 2 가 나오겠지? 했지만... 3 3 3이 나와버렸다. 뭔 일이야!

*<원인>*   

`var`로 선언한 i 변수는 `함수 레벨 스코프`를 따르기 때문에 `전역 변수`이다. 0 1 2 가 나오려면 각각 독립된 스코프를 보유해야 한다. 결국 전역 변수 i는 3이 할당되면서 끝나버린 것이다.

## 해결 1. 클로저 사용

```jsx
var funcs = [];

for(var i = 0; i<3; i++) {
    funcs[i] = (function(id) {
        return function() {
            return id;
        }
    }(i));
}

for (var j = 0; j<funcs.length; j++) {
    console.log(funcs[j]());    // 0 1 2
}
```

즉시 실행 함수는 전역 변수 i(arguments)를 id(parameter)로 전달받은 후, 이를 반환하는 중첩 함수를 반환하면서 종료된다.
이 때 매개변수 id는 자유변수이다.

## 해결 2. var 대신 let, const → 블록 레벨 스코프

var 대신 let을 쓰면 반복문이 실행될 때마다 고유의 렉시컬 환경이 새롭게 생성된다. 그리고 상태 유지를 위해 증감문 반영 이전의 반복문 코드 블록을 상위 스코프로 삼는다. 그리고 그 렉시컬 환경이 running 실행 컨텍스트의 새로운 렉시컬 환경이 된다(갈아끼우기). 반복문이 끝나면 다시 렉시컬 환경 원상복귀. 

그니까 풀어 말하자면, let이나 const를 사용하는 반복문은 코드 블록이 반복 실행될 때마다 새로운 렉시컬 환경을 생성하여 마치 스냅샷을 찍는 것처럼 저장한다.