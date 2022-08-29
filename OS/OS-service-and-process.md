# 운영체제 서비스

운영체제는 HW라는 자원을 Application이 효율적으로 사용하도록 분배하고 관리하는데, 이 때 여러 종류의 management가 이를 분업한다. 프로세스 매니지먼트는 프로세스를 관리하고, 메인 메모리 매니지먼트는 메모리를 관리하고…

## Process manegement

> 프로세스란?
> 

CPU에 의해 메모리에 올라와 현재 실행되고 있는 프로그램을 말한다.

- 프로세스 생성/소멸, 중지/재개
- 프로세스 간 통신
- 프로세스 동기화
- 프로세스 교착상태(deadlock, 마치 교통 체증과 같은 상태) 해결

## Main memory manegement

- 프로세스에 메모리 할당
- 메모리 추적
- 프로그램 종료 시 메모리 회수
- 효율적인 메모리 관리

## File manegement

복잡한 `물리적 구조`의 디스크 장치를 논리적, 계층적으로 일관된 `파일` 시스템으로 사용자에게 제공한다(추상화).

- 파일, 디렉토리 관리
- open, close, read, write, create, delete…
- 디스크-파일 간 mapping
- 백업

## Secondary storge manegement

보조기억장치 관리

- 빈공간 관리(block)
- 저장공간 할당
- 디스크 스케줄링

## I/O manegement

- 장치 브라이브
- 성능 효율 향상

# System Call

> 야, 운영체제야! 이 일 좀 해 줘.
> 

OS 서비스를 받기 위한 호출. 

![system_call](https://user-images.githubusercontent.com/97890886/187198471-8d22fa1a-ad2f-4036-929e-76caa5f2fd91.png)


프로세스가 HW와 직접적으로 관련된 복잡한 일을 처리할 때 그에 알맞는 매니지먼트를 호출하여 OS가 일을 대신 처리하게끔 한다.

## Linux로 구현(Create file)

레지스터에 정보를 넣고 인터럽트를 건다.

- EAX = 8 (create file)
- ECX = file attributes (파일 속성)
- EBX = file name (파일 이름이 담긴 메모리의 주소)

# 프로세스

> 프로세스란?
> 

CPU에 의해 메모리에 올라와 현재 실행되고 있는 프로그램을 말한다.

## 프로그램 vs 프로세스

![process1](https://user-images.githubusercontent.com/97890886/187198519-3c37946c-479f-4b12-9924-1b1967de75d7.png)


- 프로그램: 아직 메모리에 적재되지 않은 상태의 프로그램. 당연히 CPU의 관리 대상도 아니고, 실행되지도 않는다.
- 프로세스: 메모리에 적재되어 CPU의 관리를 받고 비로소 프로그램으로써의 기능을 다하는, 현재 실행중인 프로그램.

## 프로세스의 상태

![process_state](https://user-images.githubusercontent.com/97890886/187198566-66cf9f86-6a65-48ea-a4c2-b5c848101734.png)


- new : 이제 막 적재됨
- ready : 실행할 준비가 완료됨
- running : CPU에 의해실행중
- waiting : I/O 장치를 만나 처리하면서 잠시 기다림. 일이 끝나면 다시 ready 상태가 된다
- terminated : 종료됨

## PCB(Process Control Block)

- 프로세스에 대한 모든 정보가 들어있다. 마치 사람의 인적정보처럼 다양한 정보들이 존재한다.

![pcb1](https://user-images.githubusercontent.com/97890886/187198603-80d8bd7e-2ef9-43fd-9fe1-84cf0ae768f1.png)


- 1 프로세스 1 PCB, 하나의 프로세스 당 하나의 PCB가 존재한다.
- O/S의 Process management 내에 위치한다.

![pcb](https://user-images.githubusercontent.com/97890886/187198627-707fc22f-f71c-4e3f-b28f-0f72ab97935c.png)


# Queue와 스케줄링

# Queue(줄)

HDD의 job들이 RAM에 적재될 때, CPU를 사용할 때, I/O 디스크 등에 접근할 때, **마치 줄을 서듯이** 기다리게 된다. 이 때의 일련의 데이터 배열이 바로 queue이다.

![queue](https://user-images.githubusercontent.com/97890886/187198686-f966e6fc-6883-4440-82e7-43801f3e2508.png)


## job queue → job scheduler

> 어떤 프로그램을 먼저 RAM에 적재하는가?
> 

HDD의 다양한 프로그램 중 어떤 프로그램을 메모리에 올릴 것인지에 대한 우선순위, 순서 등에 대한 이슈를 처리한다. 비교적 느리게 일어난다(long-term).

## cpu queue → cpu scheduler

> 어떤 프로세스부터 먼저 CPU에 의해 실행될 것인가?
> 

CPU는 여러 프로세스를 전환하면서 처리하는 switching을 아주 빠른 속도로 수행해야 하기 때문에, CPU의 우선순위 결정은 상당히 중요하다. 짧은 시간 안에 빠른 속도가 요구된다(short-term).

## device queue → device scheduler

> 어떤 프로세스부터 I/O 장치나 디스크 등을 사용할 것인가?
> 

## TIP: mideum-term도 있나요? (Swap)

컴퓨터와 유저가 서로 소통, 대화하는 방식으로 동작하는 프로그램이 mideum-term에 해당한다. (Time sharing system)

### swap

> 어떤 프로세스부터 몰아낼 것인가?
> 

메모리에 적재는 되어 있지만 실질적인 실행(일)은 되지 않고 있는 프로세스가 CPU를 계속 사용하는 것은 낭비이므로, 이를 지속적으로 감시하여 다시 HDD로 몰아낸다.(`swap out`) 일을 다시 시작하면 다시 메모리로 적재하여 실행한다.(`swap in`). 단, 이 때 메모리의 “자리”는 기존과 달라질 수도 있는데, 이는 CPU가 전부 추적하고 관리한다.
![swap](https://user-images.githubusercontent.com/97890886/187198730-73dd2aae-d51a-400a-acc6-74557705811d.png)


# 멀티 프로그래밍

메모리에 여러 개의 프로세스를 올려 처리하는 것.

프로세스는 크게 두 종류로 나눌 수 있는데,

- process I/O bound : I/O 장치를 많이 사용하는 프로세스. EX) 한컴
- process cpu bound : cpu를 많이 사용하는 프로세스. EX) 일기예보

이때 잡 스케쥴러가 이 두 프로세스를 적절히 믹스하여 비율을 맞춰 메모리에 올려야 한다. 어느 한 쪽이 과부하되거나, 놀지 않도록.