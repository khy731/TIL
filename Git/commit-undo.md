# 커밋 되돌리기

되돌리는(undo) 것은 복구할 수 없으므로 주의해야 한다. Git에서는 실수는 언제든 만회할 수 있지만, 되돌린 것은 복구가 어렵다.

## 1. --amend 옵션

너무 일찍/성급하게 커밋했거나, 함께 커밋할 어떤 파일을 빼먹었거나, 커밋 메시지를 잘못 적었을 때 등의 상황에 **다시 커밋** 할 수 있게 하는 옵션.

- 이전의 커밋을 완전히 새로 고쳐서 새 커밋으로 변경한다. 이전의 커밋은 일어나지 않은 일이 되고, 히스토리에도 남지 않는다.
- 실수에 대처하기에 좋다 : “아차~ 까먹음~” 이런 커밋을 만들지 않아도 된다.

### 완료한 커밋을 수정해야 할 때

1. 파일 수정 작업을 하고 Staging Area에 추가한다 (git add)

![amend-1](https://user-images.githubusercontent.com/97890886/183081783-d09b044b-193f-4355-a20c-b7b33393fc38.png)

1. git commit `--amend`로 커밋

![amend-2](https://user-images.githubusercontent.com/97890886/183081785-56559849-458d-4cd7-b7d2-ac8eea7cf9ed.png)

1. git log로 히스토리를 조회해 보면 수정 작업을 한 후의 커밋만 올라와 있다!

![amend](https://user-images.githubusercontent.com/97890886/183081778-3e8ab0cd-1c67-41a8-9f88-fbfecfc35b5c.png)


### 커밋을 했는데 함께 Stage하는 것을 깜빡하고 빠트린 파일이 있을 때

1. 빠트린 파일을 Stage한다
2. git commit `--amend`로 커밋

![amend-3](https://user-images.githubusercontent.com/97890886/183081792-9dfd402a-9afa-4d36-9a1b-f346ee9d4e5a.png)

1. git log로 조회 시 최종 커밋만 업로드되어 있음


![amend-4](https://user-images.githubusercontent.com/97890886/183081786-d9452110-0e99-4bba-8e34-32971b0bd942.png)

## 2. 파일 상태를 Unstage로 변경하기

Staging Area와 Working directory를 넘나드는 방법이다.

### 파일을 두 개 수정하고 따로 커밋하려고 했으나, 실수로 `git add *`했을 때(===전부 Stage 했을 때)

![restore](https://user-images.githubusercontent.com/97890886/183081793-a3e6fa43-ebf0-489d-b681-d51b2bcdf962.png)

git status에서 권장하는 명령어 `git restore -staged <file>`을 사용하였다.

본래는 reset이었으나, 새롭게 추가된 것으로 보임.

reset도 똑같은 효과를 나타내지만, 위험한 명령어이다-특히 h 옵션과 함께 사용하면 더더욱-. 옵션 없이 사용하면 다행히도 워킹 디렉토리의 파일은 건드리지 않는다.

## 3. Modified 파일 되돌리기

즉, Git에게 감시되고 있는 상태(Tracked)의 파일(Unmodified)이 수정되었을 때(Modified), 파일의 수정 내용을 되돌릴 수 있을까? 그러니까, 수정 내용을 배제한 가장 최근의 커밋으로 되돌아갈 수 있을까?

git status에서 권장하는 명령어 `git restore <file>`을 사용하였다.

본래는 checkout --<file> 이었으나, 개편된 것으로 보임.

![restore2](https://user-images.githubusercontent.com/97890886/183081853-71fbb1fe-d07e-4e88-bbd5-cfe624dfdf5e.png)



git checkout--<file>은 명령은 reset과 마찬가지로 아주, 상당히, 위험한 명령이다. **과거의 특정 파일로 덮어쓰여지는 것**이기 때문에 **수정한 내용이 전부 사라진다**.

## 더 나은 방법을 찾자

보통 커밋을 되돌릴 상황은 다음과 같다 :

1. 변경 내용을 쉽게 버릴 수는 없으나
2. 지금 당장은 되돌아가야하는 상황

이 때는 다음과 같은 방법을 사용하자 :

1. Stash
2. Branch

또한, --amend 옵션으로 대부분의 커밋을 복구할 수 있으므로 기억해 두자.