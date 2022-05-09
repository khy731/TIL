# Date

Date는 날짜와 시간을 위한 메서드를 제공하는 `표준 빌트인 객체`이면서 `생성자 함수`다.

# Date 생성자 함수

Date 생성자 함수로 생성한 인스턴스는 내부적으로 날짜와 시간을 나타내는 정수값(UTC 1970/01/02 기준)을 갖는다. 기본값은 현재 날짜와 시간이기 때문에 다른 날짜와 시간을 다루고 싶은 경우 명시적으로 인수를 지정해야 한다.

## new Date()

> 현재 날짜와 시간을 갖는 Date 객체 반환
> 

new연산자 없이 호출 시 Date 객체가 아닌, 날짜와 시간 정보를 나타내는 문자열을 반환

## new Date(milliseconds)

숫자 타입의 밀리초를 인수로 전달한다.

> UTC를 기점으로 인수로 전달된 밀리초만큼 경과한 날짜와 시간을 나타내는 Date 객체 반환
> 

## new Date(dateString)

특정 날짜와 시간을 나타내는 문자열(Date.parse 메서드로 해석 가능한 형식만)을 인수로 전달한다.

> 지정된 날짜와 시간을 나타내는 Date 객체 반환
> 

## new Date(year,month[,day,h,min,sec,ms])

연,월,일,시,분,초,밀리초를 의미하는 숫자를 인수로 전달한다. 연,월은 필수 매개변수이다.

> 지정된 날짜와 시간을 나타내는 Date 객체 반환
> 

# Date 메서드

## Date.now

UTC를 기점으로 현재 시간까지 경과한 밀리초를 숫자로 반환

## Date.parse

UTC를 기점으로 인수로 전달된 지정 시간까지의 밀리초를 숫자로 반환(new Date(dateString)와 같은 형식이다)

## Date.UTC

UTC를 기점으로 인수로 전달된 지정 시간까지의 밀리초를 숫자로 반환 (new Date(year,month[,day,h,min,sec,ms])와 같은 형식이다)

## Date.prototype.get/setFullYear

- Date 객체(Date 생성자 함수 new에 의해 생성된 인스턴스)의 연도를 나타내는 정수를 반환
- Date 객체에 연도를 나타내는 정수를 설정. 월, 일도 다음 매개변수로 설정 가능(옵션)

## Date.prototype.get/setMonth

- Date 객체의 월을 나타내는 **0~11**의 정수를 반환. 1~12가 아니라 0~11임에 주의하자.
- Date 객체에 월을 나타내는 0~11 정수 설정. 일은 옵션으로 가능

## Date.prototype.get/setDate

- Date 객체의 날짜(1~31)를 나타내는 정수 반환
- Date 객체에 날짜(1~31)를 나타내는 정수 설정

## Date.prototype.getDay

Date 객체의 요일(0~6) 반환

## Date.prototype.get/set Hours, Minutes, Seconds, Milliseconds

Hours는 0~23, min와 sec는 0~59, ms는 0~999

## Date.prototype.get/setTime

UTC를 기점으로 Date 객체의 시간까지 경과된 밀리초를 반환/설정   

## Date.prototype.getTimezone0ffet

UTC와 Date 객체에 저장된 locale(로캘)시간과의 차이를 분 단위로 반환. 우리는 KST다 항상.

## Date.prototype.toDate/Time/IS0/Locale/LocaleTimeString

사람이 읽을 수 있는 형식의 문자열로 Date객체의 날짜/시간/ISO 8601 형식의 날짜와 시간/로캘 기준으로 날짜와 시간/로캘 기준으로 시간을 표현한 문자열을 반환

# Date를 활용한 시계 예제

현재 날짜와 시간을 초 단위로 출력한다.

```jsx
function printNow() {
    const today = new Date();

    const dayNames = [
        `(Sun)`,
        `(Mon)`,
        `(Tue)`,
        `(Wed)`,
        `(Thu)`,
        `(Fri)`,
        `(Sat)`,
    ];

    const day = dayNames[today.getDay()];

    const year = today.getFullYear();
    const month = today.getMonth();
    const date = today.getDate();
    let hour = today.getHours();
    let minute = today.getMinutes();
    let second = today.getSeconds();

    const ampm = hour >= 12 ? `PM` : `AM`; 

    // 12시간제로 변경
    hour %= 12;
    hour = hour || 12;  // hour이 0(F)이면 12를 재할당

    // 10 미만인 분과 초를 2자리로 변경
    minute = minute < 10 ? `0`+minute : minute;
    second = second < 10 ? `0`+second : second;

    const now = `${year}년 ${month}월 ${date}일 ${hour}시 ${minute}분 ${second}초`;

    return now;
}

console.log(printNow());
```