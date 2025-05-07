# TouhouScarletDevilClone

## 프로젝트 소개

이 프로젝트는 동방 프로젝트의 6번째 작품인 동방홍마향(Touhou Koumakyou ~ the Embodiment of Scarlet Devil)을 모작한 탄막 슈팅 게임입니다. WinAPI와 C++를 사용하여 개발되었으며, 원작의 주요 게임 메커니즘과 구조를 충실히 재현하는 것을 목표로 합니다.

## 개발 환경 및 기술 스택

- 언어: C++
- 그래픽 API: Direct2D
- 사운드 API : FMod Studio
- 개발 환경: Visual Studio
- 버전 관리: Git

## 게임 구조
### 1. 로비
- 게임 시작 및 나가기
![LobbyImage](https://raw.githubusercontent.com/alzseven/TouhouScarletDevilClone/refs/heads/master/TouhouScarletDevilClone/thsdclone_screenshot00.png)

### 2. 난이도 및 캐릭터 선택 
- 플레이 가능한 캐릭터 선택 
![SelectionImage](https://raw.githubusercontent.com/alzseven/TouhouScarletDevilClone/refs/heads/master/TouhouScarletDevilClone/thsdclone_screenshot01.png)

### 3. 게임 플레이 
- 탄막 슈팅 핵심 게임플레이 
- 스테이지 진행 및 보스전 
- 점수 시스템
![IngameImage](https://raw.githubusercontent.com/alzseven/TouhouScarletDevilClone/refs/heads/master/TouhouScarletDevilClone/thsdclone_screenshot02.png)

### 4. 엔딩
- 보스 격파 후 엔딩 이미지 표시
![EndingImage](https://raw.githubusercontent.com/alzseven/TouhouScarletDevilClone/refs/heads/master/TouhouScarletDevilClone/thsdclone_screenshot03.png)

## 게임 컨텐츠 

### 캐릭터 시스템 
- **단일 캐릭터 플레이**: 선택한 캐릭터로 전체 게임 진행, 현재 캐릭터 1개 구현 
- **파워업 시스템**: 아이템 수집을 통한 캐릭터 강화 
- 공격력 증가 
- 탄막 패턴 변화

### 적 구성 
- **잡몹 시스템**: 다수의 페이즈로(현재는 3페이즈 구현) 구성된 다양한 잡몹

### 보스 시스템 
- **3페이즈 보스전**: - 체력의 감소에 따라 단계별로 변화하는 보스 패턴, 현재는 3가지 패턴 구현

## 설치 및 실행 방법

1. 저장소를 클론합니다:
    ```
    git clone https://github.com/alzseven/TouhouScarletDevilClone.git
    ```
2. Visual Studio에서 프로젝트를 엽니다.
3. 프로젝트를 빌드하고 실행합니다.

## 조작 방법

- 다음, 메뉴 선택 : 방향키 + 엔터  
- 일반공격 : z
- 필살기 : x
- 이동 : 방향키
- 천천히 움직이기 : shift

## 팀원 및 역할 분담

- [**alz7**](https://github.com/alzseven) : 게임 시스템 제작, 적 & 미사일 패턴 시스템 제작
- [**CobaltBru**](https://github.com/CobaltBru): Direct2D 기반 이미지 라이브러리 제작, 이펙트 매니저 제작, 사운드 매니저 제작, 게임 내 리소스 제작
- [**0175077**](https://github.com/0175077): 게임 전체 UI 제작, 게임 아이템 시스템 제작, 게임 씬 매니저 제작
