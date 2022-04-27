# CSS 고급 선택자

간단한 웹 문서는 기본 선택자만으로도 스타일을 적용할 수 있지만, 스케일이 커지고 소스가 길어지면 class와 id가 늘어나 코드가 지저분해지게 됩니다. 연결 선택자와 속성 선택자로 소스의 위치, 속성값에 따라 특정 요소를 쉽게 선택하는 방법을 알아봅시다.


> 상속의 관계 : 부모 → 자식(하위) → 손자 → 손자의 손자... 

부모 요소가 같을 경우 형제 관계라고 한다. 그리고 이중 먼저 나오는 요소가 형, 나중에 나오는게 동생이다. 

# 연결 선택자

둘 이상의 선택자를 연결하여 스타일이 적용될 요소가 어느 부분인지 지정합니다. 선택자를 둘 이상 조합하므로 조합 선택자라고도 합니다. combination selecter

## 하위 선택자(자손 선택자) descendant selector

부모 요소에 포함된 `하위 요소를 모두 선택`한다. 
```css
section p {
    color: darkmagenta;
}
```

## 자식 선택자 child selector

하위 선택자와 달리, `오직 자식 요소에만` 스타일을 적용한다. 

```css
section > p {
    color: crimson;
}
```

## 인접 형제 선택자 adjacent selector

형제 요소 중, 형을 기준으로 `첫 번째 동생 요소만을` 선택하다.

```css
h1 + p {
    background-color: darksalmon;
}
```

## 형제 선택자 sibling selector

adjacent selector와 달리 `모든 형제 요소`에 적용한다.

```css
h1 ~ p {
    background-color: aquamarine;
}
```

# 속성 선택자

## 특정 속성이 있는 요소 선택 : [속성] 선택자

속성값의 조건에 따라 특정 부분만 선택하기 쉬우므로, 상황에 맞는 스타일을 지정하기도 쉽다.

~요소 중에서 ~속성이 있는 요소 선택. 이런 식으로 이루어진다

```css
a[href] {
    background: violet;
    border: 2px solod saddlebrown;
    text-decoration: none;
}
li {
    width: 100px;
    height: 70px;
    display: inline-block;
    list-style: none;
    margin: 30px;
    border: 2px solod saddlebrown;
    background: gray;
}
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>속성 선택자</title>
    <link rel="stylesheet" href="attr.css">
</head>
<body>
    <h1>메인 메뉴</h1>
    <ul>
        <li><a href="#">메뉴1</a></li>
        <li><a href="#">메뉴2</a></li>
        <li><a href="#">메뉴3</a></li>
        <li><a href="#">메뉴4</a></li>
    </ul>
</body>
</html>
```

![20_attr](https://user-images.githubusercontent.com/97890886/165517903-d9b9892e-dd87-4512-917d-15ad17a4fa0c.png)

a 요소 중에서 href속성(링크)이 있는 요소만 스타일을 적용하였다.

## 특정 속성값이 있는 요소 선택 : [속성 = 속성값] 선택자

말 그대로, 상위요소 中 주어진 속성과 속성값 전부 일치하는 요소만을 찾아 스타일을 지정한다.

```css
a[target=_blank] {
    background: gray;
}
```

![20_attr2](https://user-images.githubusercontent.com/97890886/165517990-78044949-9d2a-4877-bd02-b9d8ba020aa0.png)

a 요소 중 target 속성이 _blanck 속성값을 가진 요소에 지정 

## 특정 속성값이 포함된 속성 요소 선택 : [속성 ~= 값] 선택자

속성을 사용하다 보면 속성값을 여러개 넣을때가 있습니다. 예를들어 a의 class 속성 안에 button 속성값만 넣을 때도 있고, button 속성값과 flat 속성값을 함께 넣을 때도 있습니다. 이 때 특정 속성값이 포함된 속성 요소를 선택하는 selector가 바로 이 선택자입니다.

단,

- buttons 등은 단어 철자는 비슷하지만 아예 다른 속성값이기 때문에 이는 선택되지 않습니다.
- flat-button 처럼 하이픈(-)으로 연결된 단어 또한 선택되지 않습니다.

```css
[class ~= button] {
    box-shadow: 5px 5px red;
    border-radius: 10px;
}
```



![20_attr3](https://user-images.githubusercontent.com/97890886/165518047-8ba67052-1184-4edc-a852-6f07215e5d77.png)

## 특정 속성값이 포함된 속성 요소 선택 : [속성 |= 값] 선택자

위와 비슷해 보이지만, 하이픈(-)으로 연결한 단어에도 스타일을 적용합니다. 그러면 [class |=flat] 은 단순히 flat 뿐만 아니라 flat-button도 선택하겠군요.

## 특정 속성값으로 시작하는 속성 요소 선택: [속성 ^= 값] 선택자

a [title ^= eng]을 사용하면 english라는 속성값도 ok입니다

## 특정한 값으로 끝나는 속성 요소 선택: [속성 $= 값]

보통 파일의 확장자를 기준으로 할 때 편합니다.

## 일부 속성값이 일치하는 요소를 선택 : [속성 *=값]

말 그대로 단어 일부분만 일치하면 됩니다.