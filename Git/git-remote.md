# 원격(remote) 저장소

> 인터넷이나 네트워크 어딘가에 있는 저장소의 실체
> 

협업의 기초. 다른 사람들과 함께 일하기 위해 리모트 저장소를 관리하면서 데이터를 push 및 pull해야 한다. 저장소를 추가, 삭제하는 것뿐만 아니라 브랜치를 관리하고 특정 파일을 추적할지 말지 등을 관리한다.

## 리모트 저장소 확인하기

> git remote
> 

![remote1](https://user-images.githubusercontent.com/97890886/183672872-6e372b63-018a-414a-9e00-3b4067f72f10.png)

리모트 저장소의 단축 이름을 보여준다. 저장소를 clone한 경우, `origin`이라는 리모트가 기본값으로 보여진다.

-v 옵션으로 URL을 함께 볼 수 있다.

여러 개 있는 경우 전부를 보여준다.  이 때, 다른 사람이 기여한 내용(contributions)을 쉽게 pull/fetch해올 수 있다.

## 리모트 저장소 추가하기


![remote2](https://user-images.githubusercontent.com/97890886/183672881-c698decd-fbf9-4f4f-8922-8d19dcc2ef95.png)

`git clone`명령어의 경우 암묵적으로 origin 리모트 저장소를 추가하지만, 닉네임을 사용하여 리모트 저장소를 보다 자세하게 추가할 수 있다.

> git remote add <단축이름> <url>
> 

만약 kang이라는 이름으로 리모트 저장소를 추가했다면, 다른 누군가는 자신의 로컬 저장소에는 없지만 리모트 저장소에는 있는 “kang의 저장소에 있는 것”을 가져올 수 있다.

> git fetch kang
> 

## 리모트 저장소를 pull또는 fetch하기

> git fetch <remote>
> 

![remote3](https://user-images.githubusercontent.com/97890886/183672885-dc559c8d-cc5b-474d-b679-8a3a4f24070d.png)

로컬에는 없지만 리모트 저장소에는 있는 데이터를 전부 가져온다. 리모트 저장소의 모든 브랜치를 로컬에서 접근할 수 있게 된다.

저장소를 clone하면 자동으로 origin으로 추가되므로 이후 `git fetch origin`명령으로 clone 이후 수정된 것을 전부 가져올 수 있다. 

그러나 이 명령은 추가 작업을 수동으로 merge해야 한다.

> git pull
> 

리모트 저장소 브랜치에서 데이터를 가져오고, 자동으로 로컬 브랜치와 merge시킨다.

`git clone` 명령은 자동으로 로컬의 main 브랜치가 리모트의 main 브랜치를 추적하도록 하고, `git pull` 명령은 clone한 서버에서 데이터를 가져오고 그 데이터를 자동으로 현재 백업하는 코드와 merge시키는 것이다.

## 리모트 저장소에 push하기

> git push <리모트 저장소 이름> <브랜치 이름>
> 


origin 서버에 push할 경우 `git push orogin master`이라고 하면 되겠다.

이 명령은 다른 사람이 push 한 후 push하려고 할 때 불능이 된다. 먼저 pull/fetch로 이전 작업을 불러와 merge한 이후에 push할 수 있다.

## 리모트 저장소 살펴보기

> git remote show <리모트 저장소 이름>


![remote4](https://user-images.githubusercontent.com/97890886/183672887-789bf257-b89a-472f-8d68-0b4c0988801c.png)

리모트 저장소의 구체적인 정보를 확인할 수 있다. 

리모트 저장소의 url, 추적중인 브랜치, pull 명령을 실행할 시 벌어질 일(로컬의 master 브랜치와 merge할 브랜치가 무엇인지), push 명령을 실행할 시 어떤 브랜치가 어떤 브랜치로 push되는지, 아직 로컬로 가져오지 않은 리모트 저장소의 데이터, 서버(리모트)에서는 삭제됐지만 로컬에서 아직 가지고 있는 브랜치 등…

## 리모트 저장소 이름 변경 & 리모트 저장소 삭제



![remote5](https://user-images.githubusercontent.com/97890886/183672890-9c9a2d2d-75bf-484c-ae20-911123b3429f.png)


> git remote rename
> 

로컬에서 관리하던 리모트 저장소의 브랜치 이름도 바뀐다. 지금까지 kang/master로 브랜치를 사용했으면 이제는 yoon/master이다.

> git remote remove
> 

서버 정보가 바뀌었더나 더는 기여자가 활동하지 않을 때 필요한 명령어이다. 관련 모든 설정이 삭제된다.