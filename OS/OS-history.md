# 운영체제의 역사

## 운영체제가 없던 시절

프로그래머가 종이에 쓴 코드가 전산기를 거쳐 카드 리더기로 들어가고, 별도의 컴파일러를 통해 동작하였다. 이를 처리하는 직업이 있을 정도로 상당히 귀찮고 복잡한 작업이었다.

![image](https://user-images.githubusercontent.com/97890886/183671556-6a0fa6e6-79f3-4227-83d9-9408f792c562.png)


## 일괄 처리(Batch Processing)

편리함을 위해 컴파일, 링크, 로드 등의 일련의 작업을 일괄 처리하여 주 메모리에 탑재한 것. 첫 운영체제이다.

![image](https://user-images.githubusercontent.com/97890886/183671715-1e4a86c3-02a4-4f74-8552-e0ebf929b074.png)

- 기본적으로 하나의 CPU에 하나의 메모리가 연결된 구조
- 프로그램을 실행할 때, `CPU idle`등의 한계가 있었다: CPU가 얼마나 비싼데 일을 쉬고 있네! 이걸 어떻게 해결하면 좋을까…

## 다중 프로그래밍(multi programming)

CPU가 쉬지 않게, 한 번에 여러 프로그램을 올린 구조. 어떤 프로그램을 먼저 실행시킬까에 대한 CPU 스케줄링이 처음으로 논의되었다.

![image](https://user-images.githubusercontent.com/97890886/183671901-1090c40b-0e34-4e49-81dc-e6402b31c32d.png)

- 보통 하나의 서버에 여러 모니터, 키보드들이 붙어 CPU를 공유했다.
- 어떤 사용자가 CPU를 사용할 때 다른 사용자는 CPU를 사용하지 못하고 기다려야 했다. 즉, 여러 사용자가 동시에 사용하지 못했던 것이다.

## 시공유 시스템(Time-Sharing System)

CPU가 여러 작업을 처리할 때, 한 작업을 전부 처리한 후 다음 작업에 착수하는 형식이 아닌 아주 빠른 속도의 switching으로 처리함으로써 사용자들로 하여금 CPU를 혼자 쓰고 있는 것처럼, 모든 작업이 동시에 일어나고 있는 것처럼 느끼게 한다.

![image](https://user-images.githubusercontent.com/97890886/183672095-025d3f79-a6f7-4c7d-9803-521383e1c31e.png)

- 예를 들어, User 1과 User 2, User 3을 1초에 약 300번 switching하면서 실행했다면 User 1,2,3 전부 본인의 컴퓨터가 CPU를 온전히 혼자 쓰는 것 처럼 착각하게 된다.
- 또한 서로 이어져 있다는 기본 전제 덕분에 데이터를 주고받는 등 통신이 용이하다.

## 가상 메모리(Virtual Memory)

![image](https://user-images.githubusercontent.com/97890886/183672165-f88be70f-bfc3-48ec-8c2d-f947f9aed6af.png)


보조기억장치의 일부가 마치 주기억장치인 것처럼 CPU에게 보여지게 하여 메모리 효율을 증진시킨다.

# 컴퓨터의 구분

![image](https://user-images.githubusercontent.com/97890886/183672277-27117611-7e45-4088-bd6b-0a11e72c2d5e.png)

## 규모순으로 컴퓨터를 구분

- supercomputer
- server
- work station
- PC
- Handheld
- Embeded

# 고등 운영체제

> 이후 OS의 발전 동향

![image](https://user-images.githubusercontent.com/97890886/183672369-be587e1f-4d9c-4968-bffc-7a8fb28fea81.png)


## 다중 프로세서 시스템(Multi Processor System)

- 하나의 메모리에 여러개의 COU
- 성능, 신뢰도, 가격
- 강도 높은 결합, 병렬 구조

## 분산 시스템, 다중 컴퓨터(Distuributed System)

- 한 쌍의 CPU와 메모리가 BUS에 의해 연결된 구조
- 일기 예보를 예로 들 수 있다. 같은 카테고리 안 데이터지만 약간의 분류가 필요할 때.
- 다중 프로세서 시스템과 목적, 장점 등이 유사하다. 구현이 다를 뿐.

## 실시간 시스템(Real-Time System)

시간 제약(deadline)이 있는 경우.

공장, 군사 등…

# 인터럽트 기반 시스템(Interrupt-Based System)

![image](https://user-images.githubusercontent.com/97890886/183672507-733bb219-a99f-4cbd-b4c2-2545828a4aa1.png)

현대 운영체제는 전부 인터럽트 기반 시스템이다.

> Interrupt : (말을)가로채다
> 
- 부팅이 끝난 순간, CPU와 OS는 사건(Event)을 기다리며 대기, 상주한다.
- HW Event가 발생하면 Processor가 전기 신호를 감지하여 OS의 Interrupt Service Routine을 실행
- SW Event가 발생해도 마찬가지로 ISR(운영체제 코드)실행된다.
- 인터럽트가 종료되면 다시 대기 상태나 기존에 실행중이었던 프로그램으로 복귀한다.