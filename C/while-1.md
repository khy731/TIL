# while(1)의 의미

```c
Value == 0 // false

Velue != 0 // true
```

C언어에서 0을 제외한 모든 값은 참을 의미한다.

*0이 아닌 모든 값은 참&거짓 비교를 할때 참으로 인식되므로, 다른 값을 마구잡이로 쓰는 것 보다 단순하게 1을 써놓는 것이 구분이 편하므로 보통 1을 사용한다.*

즉 *while(1)의 의미는 계속해서 while이 돌아간다는 의미이다.*

<aside>
💡 조건이 True인 한, 무한반복해서 작동하는 코드.

</aside>

*단순한 프로그램의 메뉴를 설정할때 사용하기도 하며, 종료를 위한 조건을 while 내부에  걸어주는 것이 필수이다.*