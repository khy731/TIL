## preemptive VS non-preemtive

> 선점 vs 비선점

- 실행 중인 프로세스가 종료되거나 I/O 등의 이벤트 없이 중단될 수 있다 vs 없다

## scheduling criteria(스케줄링 척도, 기준)

- CPU Utillzation(CPU 이용률) : CPU가 얼마나 열심히 일하는가?(0~100%)
- Throughput(처리율) : 시간당 효율
- Turnarround Time(반환시간) : 한 task를 마치는(term, ready queue에서 대기하여 cpu 위에 올라가고 실행되다가 I/O 이벤트를 만나 I/O queue에서 대기하고 다시 ready queue에서 대기하고 cpu에 올라가고 하는 일련의 과정...) 시간
- Wating Time(대기시간) : CPU에 올라가기 전 까지(ready queue에서 **처음으로** cpu에 올라가기 전 까지다) 걸리는 시간
- Response Time(응답시간) : interective한 system에서 중요. 첫 응답까지 걸리는 시간
  
다양한 알고리즘을 각 척도의 수치로 비교해보자.

## First Come, First Served

> 먼저 온 놈부터 먼저 전부 실행! 순차적으로 처리한다

- simple & fair
- non-preemtive
- WT을 척도로 하여 봤을 때 효율이 떨어진다

## SJF(Shortest Job First)

> Burst Time이 가장 짧은 놈부터 처리!

- WT를 척도로 하여 봤을 때, FCFS에 비해 확실히 효율적이지만
- Not Realistic : 현실에서는 각 프로세스의 정확한 Burst Time(실행 완료까지 걸리는 시간)을 알 수 없고 추측에 의존해야 한다.
- Gantt Chart에서 preemtive VS non-preemtive
  - non-preemtive SJF : 도중에 cut되지 않는다
  - Shortest-Remaining-Time-First(preemtive SJF) : 시간의 흐름에 따라 계속해서 달라지는 잔여 Burst Time이 적은 쪽을 우선한다. 잔여 시간이 적은 놈이 먼저!

## Priority scheduling

> priority(우선 순위)가 높은 놈이 먼저!

typically, in Unix/Linux, `priority` is `an integer number`. and **lower number means higher priority.**

- `priority`는 어떻게 정해지는가?

  - Internal : time limit(처리 시간), memory request(메모리 요구량), I/O to CPU burst(I/O와 CPU 중 어느 것을 더 많이 사용하는지)등...
  - External : 돈 and 정치.

- 문제점: `Indefinite blocking` - starvation(기아)
  - 우선순위가 낮은 프로세스는 **영원히** 실행되지 않을 수도 있다...
  - aging(나이를 먹다)으로 해결 가능 : 오래 머무는 프로세스를 잠재적으로 우선순위를 올려줌으로써 영원히 실행되지 않는 일이 없도록 한다.
  
## Round-Robbin

> 시분할 시스템. 마치 빙빙 도는 수건돌리기처럼...

- 프로세스가 종료되든 말든 정해진 `time quantum(시간 양자, 시간 분할)`이 끝나면 바로 다음 프로세스를 실행한다.
- 즉, 시간을 분할하여 프로세스를 정형적으로 실행하는 방식으로 **`time quantum`에 상당히 의존적**이다. 적절한 `time quantum`을 잡는 것이 아주 중요하다.
- `time quantum`을 0에 수렴시킬 경우 마치 여러 프로세스가 동시에 동작하는 것 처럼 보이지만 `context switching overhead`가 발생하므로 주의하자.

