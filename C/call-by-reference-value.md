# Call By Value

- 매개변수를 주어진 값을 복사하여 전달하는 방식
- 메소드 내에서 변경한 값은 메소드 밖의 변수에 영향을 주지 못함

```c
void swap(int a, int b)
{
    int t = a;
    a = b;
    b = t;
}

int main()
{
    int a = 1;
    int b = 2;
    swap(a, b);
    cout << a << " , "<< b << endl;
    return 0;
}
```

스왑이 되지 않는다. 복사의 한계

# Call By Reference

- 매개변수에 변수의 주소를 전달하는 방식
- 메소드 내에서 수정한 내용이 메소드 밖에서도 적용되게 하는 기법
- 포인터 문법

```c
void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int main()
{
    int a = 1;
    int b = 2;
    swap(&a, &b);
    cout << a << " , "<< b << endl;
    return 0;
}
```

스왑 성공.