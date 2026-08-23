# TouhouScarletDevilClone

## 프로젝트 소개

이 프로젝트는 동방 프로젝트의 6번째 작품인  
**동방홍마향(Touhou Koumakyou ~ the Embodiment of Scarlet Devil)**을 모작한 C++ 기반 탄막 슈팅 게임입니다.

WinAPI와 Direct2D를 사용하여 개발했으며, 원작의 탄막 슈팅 플레이를 구성하는 주요 메커니즘을 구현하는 것을 목표로 했습니다.

팀 프로젝트 종료 이후에는 기존 코드의 객체 생명 주기, 세션 전환, 일부 소유권 및 실행 흐름을 개인적으로 정리하고 안정화했습니다.

> 비상업적 학습 목적으로 제작된 팬 프로젝트입니다.

---

## 개발 환경 및 기술 스택

- 언어: C++
- 그래픽 API: Direct2D
- 사운드 API: FMOD Studio API
- 플랫폼: Windows / WinAPI
- 개발 환경: Visual Studio
- 버전 관리: Git

---

## 게임 구조

### 1. 로비

- 게임 시작 및 나가기

![LobbyImage](https://raw.githubusercontent.com/alzseven/TouhouScarletDevilClone/refs/heads/master/TouhouScarletDevilClone/thsdclone_screenshot00.png)

### 2. 난이도 및 캐릭터 선택

- 플레이 가능한 캐릭터 선택
- 난이도 선택

![SelectionImage](https://raw.githubusercontent.com/alzseven/TouhouScarletDevilClone/refs/heads/master/TouhouScarletDevilClone/thsdclone_screenshot01.png)

### 3. 게임 플레이

- 탄막 슈팅 핵심 게임플레이
- 스테이지 및 웨이브 진행
- 아이템 / 파워업 시스템
- 보스전
- 점수 시스템

![IngameImage](https://raw.githubusercontent.com/alzseven/TouhouScarletDevilClone/refs/heads/master/TouhouScarletDevilClone/thsdclone_screenshot02.png)

### 4. 클리어

- 보스 격파 후 결과 화면 표시

![EndingImage](https://raw.githubusercontent.com/alzseven/TouhouScarletDevilClone/refs/heads/master/TouhouScarletDevilClone/thsdclone_screenshot03.png)

---

## 게임 콘텐츠

### 캐릭터 시스템

- **단일 캐릭터 플레이**: 현재 1개 캐릭터 구현
- **파워업 시스템**: 아이템 수집을 통한 캐릭터 강화
  - 공격 성능 변화
  - 탄막 패턴 변화
- 일반 공격 및 필살기 구현

### 적 구성

- 여러 Wave로 구성된 일반 적 출현
- 이동 및 탄막 패턴을 조합한 적 행동 구성

### 보스 시스템

- 체력 및 진행 상황에 따라 변화하는 보스 패턴
- 여러 종류의 이동 / 발사 Action을 조합한 보스 행동
- 보스 체력 및 전투 UI 표시

---

## 주요 시스템

### Object Pool

반복적으로 생성되는 적과 탄환을 재사용하기 위해 템플릿 기반 Object Pool을 사용합니다.

Enemy, Boss, Bullet 객체는 Pool을 통해 관리하며, 현재 사용 중인 객체와 재사용 가능한 객체를 구분하여 관리합니다.

### Collision System

충돌 가능한 객체는 Layer를 통해 구분하며, 상호작용 가능한 Layer 조합만 실제 충돌 검사를 수행합니다.

현재 주요 충돌 관계는 다음과 같습니다.

- `PLAYER ↔ ENEMY_BULLET`
- `ENEMY ↔ PLAYER_BULLET`
- `PLAYER ↔ ITEM`

Boss는 별도 Layer가 아니라 `ENEMY` Layer를 사용합니다.

### Enemy / Bullet Pattern

적의 이동과 공격을 독립적인 Action으로 구성했습니다.

대표적인 패턴:

- 직선 이동
- 직선 발사
- 부채꼴 발사
- 원형 발사
- 나선형 발사

여러 Action을 시간에 따라 조합하여 Enemy와 Boss의 행동을 구성합니다.

### Stage / Wave System

스테이지의 적 생성과 진행을 Wave 단위로 구성했습니다.

각 Wave는 적 생성 시점과 위치, 적용할 행동 패턴 및 진행 시간을 정의하며, `StageWaveManager`가 전체 스테이지 진행을 관리합니다.

---

## 이후 개인 안정화 작업

팀 프로젝트 종료 이후 기존 코드를 다시 검토하면서 다음 부분을 정리했습니다.

- Player의 중복 Update / Render 호출 제거
- Update / Collision 이후 별도 Cleanup 단계에서 객체를 제거하도록 실행 순서 정리
- Object Pool의 active 객체와 프레임별 Update 대상을 구분
- Enemy / Boss / Action / Wave의 소유권 및 해제 책임 정리
- Clear / GameOver 이후 이전 Session 객체가 남지 않도록 Gameplay Session 정리
- Player 및 GameState 초기화 흐름 정리
- Scene 전환 시 BGM 상태 안정화

---

## 시연 영상

https://youtu.be/mOR_P9XFVhE

---

## 설치 및 실행 방법

프로젝트를 빌드하기 위해서는 Microsoft Visual Studio와 FMOD Studio API가 필요합니다.

> FMOD SDK / Runtime과 일부 Image / Sound 리소스는 저장소에 포함되어 있지 않습니다.  
> Visual Studio Project의 FMOD Include / Library 경로는 개발 환경의 로컬 SDK 설치 위치를 기준으로 설정되어 있으므로, 다른 환경에서는 경로 수정이 필요할 수 있습니다.

1. 이 저장소를 로컬 환경에 Clone합니다.
2. Visual Studio에서 `.sln` 파일을 엽니다.
3. FMOD Studio API의 Include / Library 경로를 로컬 설치 위치에 맞게 설정합니다.
4. 필요한 `Image`, `Sound` 리소스를 프로젝트 실행 환경에 배치합니다.
5. 솔루션 구성을 `x64 Release` 또는 `Debug`로 설정한 뒤 빌드합니다.
6. 실행 파일이 위치한 환경에 해당 버전의 `fmod.dll`을 배치합니다.
7. 생성된 실행 파일을 실행합니다.

---

## 조작 방법

- 메뉴 이동: 방향키
- 메뉴 선택: `Enter`
- 일반 공격: `Z`
- 필살기: `X`
- 이동: 방향키
- 저속 이동: `Shift`

---

## 팀원 및 역할 분담

### alzseven

GitHub: https://github.com/alzseven

- 게임 시스템 제작
- 적 / 탄막 패턴 시스템 제작
- Stage / Wave 시스템 제작
- 팀 프로젝트 종료 이후 개인 안정화 작업
  - 객체 생명 주기
  - Gameplay Session 정리
  - Action / Wave 소유권
  - Player 실행 흐름
  - Clear / GameOver 처리

### CobaltBru

GitHub: https://github.com/CobaltBru

- Direct2D 기반 이미지 라이브러리 제작
- Effect Manager 제작
- Sound Manager 제작
- 게임 내 리소스 제작

### 0175077

GitHub: https://github.com/0175077

- 게임 전체 UI 제작
- 게임 아이템 시스템 제작
- 초기 Scene 관련 구현