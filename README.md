# SNU RTOS LAB Cloud Native 스터디

이 프로젝트는 간단한 C HTTP 서버를 활용하여 Cloud Native 방법론의 기본 요소인 **Git**, **컨테이너화**, **Kubernetes**, **CI/CD**를 학습하기 위한 스터디 과정입니다. 

## 스터디 목표
- Cloud Native 환경에서 소프트웨어 개발 및 배포 프로세스를 체험하고 이해하기
- Git 및 협업 전략, Docker 컨테이너화, Kubernetes 오케스트레이션의 기초, GitHub Actions를 활용한 CI/CD 파이프라인 구축을 습득

---

## 스터디 과정 개요

### 1~2주차: Git & Branch 전략

#### 개념
- **Version Control System (VCS)**: git의 기본 사용법 (add, commit, push 등)
- **협업 전략**: branch 관련 사용법 (branch, switch, merge 등)

#### 실습 과제
현재 있는 server.c 코드 활용하여
1. "/" 경로에서만 `Hello, World!` 응답이 나오게 하기
2. "/rtos" 경로에서만 `Hello, RTOS!` 응답이 나오게 하기
3. "/param\/\<param\>"로 접속 시엔 `Hello, <param>`<param>에 param을 print해서 보여주기
4. "/", "/rtos", "/param/" 이외 경로에선 404 Not Found page 만들기


이를 4명이 각 번호에 맞게 작업 분배, 개별 브랜치로 만들어서 push하기  
4명의 작업이 끝난 이후엔 4명의 작업을 각자가 local에서 fetch한 이후 merge 하기  
merge가 다 끝난 이후엔 `step1`이라는 이름으로 한 명이 push하기



**보충 설명**
  - [서버 코드](./server.c)를 참고하여 서버를 빌드하고 실행합니다.
  - `gcc server.c -o server && ./server`를 통해 로컬에서 http://127.0.0.1:8080 에 접속하여 서버 응답을 확인할 수 있습니다.
  - 현재는 "/" 뿐만 아니라 모든 경로에서 "Hello, World!"가 출력됩니다.
  - C언어 학습이 목표가 아니기에 AI를 써서 기능 구현을 해도 무방합니다.
  - 다른 사람의 작업 브랜치를 로컬로 가져오기 위해 `git fetch`라는 커맨드를 추가로 학습해야 합니다.
    - https://opentutorials.org/course/3842/23969
---

### 3~4주차: Docker를 통한 컨테이너화

#### 개념
- **컨테이너의 의의**: 소프트웨어 실행 환경의 표준화
- **Docker**: 컨테이너 기술의 핵심 도구

#### 실습
- Docker 기초 명령 학습
- C HTTP 서버를 Dockerfile로 컨테이너화하여 이미지 생성
- GitHub Actions 통한 빌드 및 Docker Registry 연동

---

### 5~6주차: Kubernetes와 Orchestration

#### 개념
- **Kubernetes 기본 요소**: pod, service, replicaset, deployment, ingress 등의 개념
- Kubernetes를 활용한 컨테이너 오케스트레이션

#### 실습
- Minikube를 통해 로컬 클러스터 구축
- C HTTP 서버 컨테이너를 pod로 실행
- service 및 deployment 설정을 통해 클러스터 운영

---

### 7주차: GitHub Actions를 통한 CI/CD 기본

#### 개념
- **CI/CD의 의의**: Continuous Integration과 Continuous Deployment의 차이와 의미
- **GitHub Actions의 역할**: 빌드 및 테스트 자동화 도구로서의 활용

#### 실습
- GitHub Actions 설치 및 Workflow 설정
- GitHub와 연동하여 C HTTP 서버의 빌드와 유닛 테스트 자동화
- 성공/실패 여부에 따른 알림(email, Slack)

---

### 8주차: Kubernetes(K3s)와 CICD 파이프라인 통합

#### 개념
- **Kubernetes 업데이트 전략**: Rolling Update, Blue-Green Deployment 등
- **CI/CD 파이프라인 전체 흐름**: 코드 변경 → Git push → GitHub Action 빌드 → Docker 이미지 생성 → Kubernetes 업데이트

#### 실습
- Git push 시 GitHub Action에서 빌드 → Docker Registry 등록 → Kubernetes 배포로 이어지는 파이프라인 완성

---

## 프로젝트 구조
```
├── .github/workflows # github action 관련 설정 파일
├── slides/ # 발표 슬라이드 모음
├── kubernetes/ # Kubernetes 관련 YAML 파일 
├── server.c # C HTTP 서버 코드 
├── Dockerfile # 컨테이너 이미지를 생성하기 위한 Dockerfile 
└── README.md # 프로젝트 안내 파일
```
