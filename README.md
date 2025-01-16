# SNU RTOS LAB Cloud Native 교육

이 프로젝트는 간단한 C HTTP 서버를 활용하여 Cloud Native 방법론의 기본 요소인 **Git**, **CI/CD**, **컨테이너화**, 그리고 **Kubernetes**를 학습하기 위한 교육 과정입니다. 

## 교육 목표
- Cloud Native 환경에서 소프트웨어 개발 및 배포 프로세스를 체험하고 이해하기
- Git 및 협업 전략, Jenkins를 이용한 CI/CD 파이프라인, Docker 컨테이너화, Kubernetes 오케스트레이션의 기초를 습득

---

## 교육 과정 개요

### 1~2주차: Git & Branch 전략

#### 개념
- **Version Control System (VCS)**: git의 기본 사용법 (stage, commit, push 등)
- **협업 전략**: branch, tag, GitHub flow, GitLab flow 등

#### 실습
- C HTTP 서버 코드를 활용하여 3명이 각자 기능을 구현하고 Pull Request를 통해 병합하는 협업 연습

---

### 3~4주차: Docker를 통한 컨테이너화

#### 개념
- **컨테이너의 의의**: 소프트웨어 실행 환경의 표준화
- **Docker**: 컨테이너 기술의 핵심 도구

#### 실습
- Docker 기초 명령 학습
- C HTTP 서버를 Dockerfile로 컨테이너화하여 이미지 생성
- Jenkins를 통한 빌드 및 Docker Registry 연동

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

## 사용법

1. **C HTTP 서버 실행**
   - [서버 코드](./server.c)를 참고하여 서버를 빌드하고 실행합니다.
   - `gcc server.c -o server && ./server`를 통해 로컬에서 서버를 확인할 수 있습니다.

2. **실습 환경 준비**
   - Docker 및 Kubernetes 설치: [Docker 설치 가이드](https://docs.docker.com/get-docker/), [Minikube 설치 가이드](https://minikube.sigs.k8s.io/docs/start/)

3. **교육 진행**
   - 각 실습 내용을 참고하여 Git, CI/CD, Docker, Kubernetes 등을 체험합니다.
   - 각 과정의 실습과제를 수행하며 Cloud Native 개발 환경을 이해합니다.

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
