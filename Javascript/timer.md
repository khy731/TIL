# 호출 스케줄링

함수를 명시적으로 호출하면 함수가 즉시 실행된다. 만약 함수를 명시적으로 호출하지 않고 일정 시간이 경과된 후 호출되도록 함수 호출을 `예약`하려면 `타이머 함수`를 사용한다. 이를 `호출 스케줄링`이라고 한다.

자바스크립트는 호출 스케줄링을 위한 다음과 같은 함수들을 제공한다:

- 타이머 생성 : setTimeout/setInterval
- 타이머 제거 : clearTimeout/clearInterval

타이머 함수는 호스트 객체이며, 일정 시간이 경과된 이후 콜백 함수가 호출되도록 타이머를 생성한다. 즉, 타이머 함수가 생성한 타이머가 만료되면 콜백 함수가 호출된다.

자바스크립트 엔진은 싱글 스레드로, 단 하나의 실행 컨텍스트 스택을 갖기 때문에 두 가지 이상의 태스크를 동시에 실행할 수 없다 : 타이머 함수는 비동기 처리 방식으로 동작하게 된다. 

# 타이머 함수

## setTimeout/clearTimeout

> 두 번째 인수로 전달받은 시간 으로 ***단 한 번*** 동작하는 타이머를 생성한다.
> 

```jsx
const timeoutId = setTimeout(fun|code[, delay, param1, param2, ...]);
```

- func : 타이머 만료 후 호출될 `콜백 함수`
    - 콜백 함수 대신 코드를 문자열로 전달할 수도 있지만(eval 함수와 유사) 권장하지 X
- delay : 타이머 만료 `시간`
    - ms 단위, 기본값 0, 최솟값 4(1~3 설정 시 4로 조정됨)
    - 테스크 큐에 콜백 함수를 등록하는 시간을 등록하는 식으로 동작하므로, 타이머 만료 후 콜백 함수가 즉시 호출된다는 보장은 **없다**
- param1, param2, … : 콜백 함수에 전달할 `인수`들

```jsx
// 1초(1000ms)후 타이머 만료 -> 콜백 함수 호출
setTimeout(()=>{console.log(`Hello, world!`)}, 1000);

// 콜백 함수에 인수 전달
setTimeout(name => {console.log(`Hello, ${name}`)}, 1000, `kang`);
```

> `고유 타이머 id`를 `claerTimeout 함수`의 인수로 전달하여 타이머를 **취소**할 수 있다.
> 

setTimeout 함수는 고유 타이머 id를 반환하는데(브라우저의 경우 숫자, Node.js 환경인 경우 객체), 이 id로 타이머를 **취소**할 수 있다.

```jsx
const myTimer = setTimeout(()=>{console.log(`Hi`)}, 2000);

// setTimeout 함수가 반환한 고유 타이머 id를 clearTimeout 함수의 인수로 전달하여 타이머 취소
// setTimeout 함수의 콜백 함수는 실행되지 않는다
clearTimeout(myTimer);
```

## setInterval/clearInterval

> 두 번째 인수로 전달받은 시간 으로 ***반복 동작***하는 타이머를 생성한다.
> 

타이머가 만료될 때 마다 콜백 함수가 반복 호출되며, 이는 타이머가 취소될 때 까지 반복된다. setTimeout과 유사하게 clearInterval에 고유 타이머 id를 인수로 전달하여 취소할 수 있다.

```jsx
let count = 1;

const myTimer = setInterval(()=>{
    console.log(count);
    count++;
    if (count>5) clearInterval(myTimer);
}, 1000);
```

# 디바운스와 스로틀

짧은 시간 간격으로 연속해서 발생하는 이벤트(mousemove 등)에 바인딩한 이벤트 핸들러는 과도하게 호출되어 성능에 문제를 일으킬 수 있다. 이 때 `디바운스`와 `스로틀`을 사용하여 이러한 이벤트들을 `그룹화`하여 이를 완화시킬 수 있다. 이들의 구현에 바로 `타이머 함수`가 사용된다.

### 디바운스와 스로틀을 사용한 예시

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>디바운스와 스로틀 활용</title>
    <style>

    </style>
</head>
<body>
    <button class="btn">Click me!</button>
    <em>이벤트 핸들러의 호출 빈도 비교</em>
    <p>일반 클릭 이벤트 카운터<span class="normal-count">0</span></p>
    <p>디바운스 클릭 이벤트 카운터<span class="debounce-count">0</span></p>
    <p>스로틀 클릭 이벤트 카운터<span class="throttle-count">0</span></p>

    <script>
        const $button = document.querySelector(`button.btn`);
        const $normalCount = document.querySelector(`span.normal-count`);
        const $debounceCount = document.querySelector(`span.debounce-count`);
        const $throttleCount = document.querySelector(`span.throttle-count`);

        const debounce = (callback, delay) => {
            let timerId;

            return event => {
                // delay 경과 전 새로운 이벤트 발생 시 -> 이전 타이머 취소 + 새 타이머 재설정
                // 설정된 delay보다 짧은 간격으로 이벤트가 발생하면 callback은 호출되지 않는다.
                if (timerId) clearTimeout(timerId);
                timerId = setTimeout(callback, delay, event);
            };
        };

        const throttle = (callback, delay) => {
            let timerId;

            return event => {
                // delay 경과 이전에 이벤트 발생 === timerId가 True === 함수 탈출, 아무 일 X
                // delay 경과 이후에 이벤트 발생 === timerId가 False === 새로운 타이머 재설정
                // -> 결과적으로 delay 간격으로 callback 호출됨
                if (timerId) return;
                timerId = setTimeout(()=> {
                    callback(event);
                    timerId = null;
                }, delay, event);
            }
        }

        $button.addEventListener(`click`, ()=> {
            $normalCount.textContent = +$normalCount.textContent + 1;
        });

        $button.addEventListener(`click`, debounce(()=> {
            $debounceCount.textContent = +$debounceCount.textContent + 1;
        }, 500));

        $button.addEventListener(`click`, throttle(()=> {
            $throttleCount.textContent = +$throttleCount.textContent + 1;
        }, 500));
    </script>
</body>
</html>
```

![ㅇㅇㅇ](https://user-images.githubusercontent.com/97890886/179215177-da7dd8f4-bbb7-48c9-9f21-6b4b69e55083.png)


## 디바운스

> 짧은 시간 간격으로 이벤트가 연속해서 발생하면 이벤트 핸들러를 호출하지 않다가 일정 시간 후에 **한 번만** 호출되도록 한다
> 

즉, 다다다다닥 발생하는 무수하는 이벤트들을 그룹화하여 마지막 단 한 번에만 이벤트 핸들러가 호출되도록 한다.

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>타이머 함수를 활용한 디바운스</title>
</head>
<body>
    <input type="text">
    <div class="msg"></div>
    <script>
        const $input = document.querySelector(`input`);
        const msg = document.querySelector(`div.msg`);

        const debounce = (callback, delay) => {
            let timerId;

            // debounce 함수는 클로저를 반환한다 : 이 클로저는 timerId를 더 오래 기억한다
            return event => {
                // delay 경과 전 새로운 이벤트 발생 시 -> 이전 타이머 취소 + 새 타이머 재설정
                // 설정된 delay보다 짧은 간격으로 이벤트가 발생하면 callback은 호출되지 않는다.
                if (timerId) clearTimeout(timerId);
                timerId = setTimeout(callback, delay, event);
            };
        };

        // debounce 함수가 반환하는 클로저가 이벤트 핸들러로 등록됨
        // 300ms보다 빠른,짧은 간격으로 input 이벤트 발생 시
        // - debounce함수의 콜백 함수는 호출되지 않는다.
        // - 300ms동안 input 이벤트가 더 이상 일어나지 않으면! 한 번만 호출된다
        $input.addEventListener(`input`, debounce(e => {
            $msg.textContent = e.target.value;
        }), 300);
    </script>
</body>
</html>
```

위 예제의 input 이벤트는 사용자가 입력 필드에 값을 입력할 때마다 연속해서 발생하므로, 이를 전부 처리하려면 상당히 부담이 된다. 사용자가 입력을 완료했을 때 한 번만 요청을 전송하는 것이 바람직하다.

사용자가 입력을 완료 했음을 어떻게 알까? 일정 시간동안 텍스트를 입력하지 않았을 때를 기준으로 하자! → 디바운스 활용 : delay동안 input 이벤트가 더 이상 발생하지 않았을 경우에만 한 번만 호출

이는 다양한 라이브 페이지 UI 구현에 활용된다. 자동완성, 버튼 중복 클릭 방지 처리, 비밀번호 실시간 검사 등… 그러나 위 예제는 이해를 위한 쉬운 ver이므로 실무에서는 `Underscore의 debounce 함수`나, `Lodash의 debounce 함수`를 사용해야 할 것이다.

## 스로틀

> 짧은 시간 간격으로 연속해서 발생하는 이벤트를 그룹화하여 일정 시간 단위로 한 번만 호출되도록 **자체 호출 추기**를 따른다.
> 

```jsx
<!DOCTYPE html>
<html lang="en">
<head>
    <title>타이머 함수를 활용한 스로틀</title>
    <style>
        #container {
            width: 300px;
            height: 300px;
            background-color: pink;
            overflow: scroll;
        }
        .content {
            width: 300px;
            height: 1000vh;
        }
    </style>
</head>
<body>
    <div id="container">
        <div class="content"></div>
    </div>
    <em>scroll 이벤트 처리 횟수</em>
    <div>일반 이벤트 핸들러<span class="normal-count">0</span></div>
    <div>스로틀 이벤트 핸들러<span class="throttle-count">0</span></div>

    <script>
        const $container = document.querySelector(`div#container`);
        const $normalCount = document.querySelector(`span.normal-count`);
        const $throttleCount = document.querySelector(`span.throttle-count`);

        const throttle = (callback, delay) => {
            let timerId;

            return event => {
                // delay 경과 이전에 이벤트 발생 === timerId가 True === 함수 탈출, 아무 일 X
                // delay 경과 이후에 이벤트 발생 === timerId가 False === 새로운 타이머 재설정
                // -> 결과적으로 delay 간격으로 callback 호출됨
                if (timerId) return;   
                timerId = setTimeout(() => {
                    callback(event);
                    timerId = null;    // delay 경과 이후 실행되는 콜백 함수 마지막 문에
                                       // if문을 False로 만들, null 할당문이 있다 
                }, delay, event);
            }
        }

        let normalCount = 0;
        $container.addEventListener(`scroll`,()=> {
            $normalCount.textContent = ++normalCount;
        })

        let throttleCount = 0;
        $container.addEventListener(`scroll`, throttle(()=> {
            $throttleCount.textContent = ++throttleCount;
        }, 100));
    </script>
</body>
</html>
```

![Honeycam 2022-07-15 14-21-03](https://user-images.githubusercontent.com/97890886/179215229-1c6389c8-c8fc-48c8-8e76-8fcb6eea2afa.gif)

