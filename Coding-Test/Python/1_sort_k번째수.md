# 문제

## 문제 설명

배열 array의 i번째 숫자부터 j번째 숫자까지 자르고 정렬했을 때, k번째에 있는 수를 구하려 합니다.

예를 들어 array가 [1, 5, 2, 6, 3, 7, 4], i = 2, j = 5, k = 3이라면

array의 2번째부터 5번째까지 자르면 [5, 2, 6, 3]입니다.
1에서 나온 배열을 정렬하면 [2, 3, 5, 6]입니다.
2에서 나온 배열의 3번째 숫자는 5입니다.
배열 array, [i, j, k]를 원소로 가진 2차원 배열 commands가 매개변수로 주어질 때, commands의 모든 원소에 대해 앞서 설명한 연산을 적용했을 때 나온 결과를 배열에 담아 return 하도록 solution 함수를 작성해주세요.

## 입출력 예
array	commands	return
[1, 5, 2, 6, 3, 7, 4]	[[2, 5, 3], [4, 4, 1], [1, 7, 3]]	[5, 6, 3]

## 입출력 예 설명
[1, 5, 2, 6, 3, 7, 4]를 2번째부터 5번째까지 자른 후 정렬합니다. [2, 3, 5, 6]의 세 번째 숫자는 5입니다.
[1, 5, 2, 6, 3, 7, 4]를 4번째부터 4번째까지 자른 후 정렬합니다. [6]의 첫 번째 숫자는 6입니다.
[1, 5, 2, 6, 3, 7, 4]를 1번째부터 7번째까지 자릅니다. [1, 2, 3, 4, 5, 6, 7]의 세 번째 숫자는 3입니다.

# 논리 작성
 
![image](https://github.com/KangHyeYoon/TIL/assets/97890886/b2b1d14a-0cc4-4d59-9d1a-45ca81bcb81d)

![image](https://github.com/KangHyeYoon/TIL/assets/97890886/7f9f1e8d-f99d-49be-a172-0fb5e94ecaee)


# 최종 코드

``` py
def solution(array, commands):
    answer = []
    
    for x in commands:
        new_arr = []
        
        i = x[0] - 1

        j = x[1]        
        k = x[2] - 1
        
        if (i == j):
            new_arr = [array[i]]
        else:
            new_arr = sorted(array[i : j])
        print(new_arr)
        
        answer.append(new_arr[k])
    
    return answer
```


# 개선한 오류

## if문으로 예외 처리

>> indexerror: list index out of range

- 배열을 결정하는 `i`나 `j`, 혹은 `k`가 잘못되었음을 느꼈다.
- print 함수로 중간에 i,j,k값과 new_arr을 검사해본 결과 commands가 4,4,1일때 빈 배열이 나오는 것을 발견하였다.
- i와 j가 같으면 리스트를 자르는 명령(new_arr[i:j])가 잘 동작하지 않는 `예외`가 생긴 것이다.

```py
        if (i == j):
            new_arr = [array[i]]
        else:
            new_arr = sorted(array[i : j])
        print(new_arr)
```

if문으로 i와 j가 같을 때의 예외처리를 해 주었다.

## j 범위 수정

>> 기대했던 값 [5,6,3]과 다르게, [6,6,3]이 나와 오류가 생겼다.

- 이는 배열을 결정하는 i나 j가 잘못된 것이라고 생각하였다.
- 리스트를 자를 때, i부터 j-1까지 자르는 명령을 사용하였다. 즉 j는 `-1을 또 해줄 필요가 없었다.`

```py
        i = x[0] - 1
        # j는 리스트를 자를때 [i:j] 형태로 쓰이는데, 이는 "i부터 j-1까지" 라는 뜻
        # 즉 이미 j는 -1인 채로 동작하므로, 굳이 안 빼줘도 됨
        j = x[1]        
        k = x[2] - 1
```

## 리스트는 push 대신 append

```py
    # 리스트는 push 안되고 append
    answer.append(new_arr[k])
```

