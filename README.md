﻿# _프로젝트_
## 1. [Embeddedprocessor](https://github.com/EunJinK/Project/tree/main/Embeddedprocessor)(19.05.17~19.06.17)
- 3학년 1학기 임베디드프로세서의 기말 프로젝트 (1인1조)
- 8bit MCU ATmega 128의 기능을 사용하여 제작
- AVR Studio를 이용, C언어 기반



## 2. [FaceUnlock/lock](https://github.com/EunJinK/Project/tree/main/FaceUnlock)(19.11.22~19.12.20)
- 3학년 2학기 임베디드비전시스템의 기말 팀프로젝트(2인1조)
- Python기반 OpenCV를 이용한 자율 프로젝트
- 얼굴 인식하여 Unlock/lock표현, 인식할 얼굴을 사진찍어 저장 후 학습, 저장된 사용자가 아닐 시 비디오 촬영이 가능한 프로그램 개발



## 3. [P2P File Transfer & Chatting system](https://github.com/EunJinK/Project/tree/main/P2PFileTransferchattingsystem)(19.11.19~19.12.18)
- 3학년 2학기 임베디드운영체제의 기말 팀프로젝트(2인1조)
- 환경 : Linux, 언어 : C
- 원격 접속 터미널 Putty 사용

  - 프로젝트 내용
    - 1단계 : 간단한 서버-클라이언트 모델을 구현, 서버의 IP주소와 포트번호로 소켓 인터페이스를 이용하여 클라이언트들이 접속하여 로그인 정보를 서버로 전송
    - 2단계 : 1단계가 완료된 후 서버를 통해 클라이언트들이 그룹채팅을 함
    - 3단계 : 그룹채팅 내에서 서버를 거치지 않고 P2P로 파일을 보냄



## 4. [물품대여시스템](https://github.com/EunJinK/Project/tree/main/GoodsRental)(19.11.22~19.12.20)
- 3학년 2학기 센서응용시스템의 기말 팀프로젝트(3인1조)
- ESP-8266을 기반으로한 자율 프로젝트
- ESP와 MQTT를 이용하여 물품대여시스템을 제작
- 보드2개, 초음파센서, 로터리엔코더를 이용하여 기능수행
  - 프로젝트내용
    - [README](https://github.com/EunJinK/Project/tree/main/GoodsRental/README.txt)



## 5. [화재감지시스템](https://github.com/EunJinK/Project/tree/main/Fire/fire)(20.05.26~20.06.23)
- 4학년 1학기 고급임베디드시스템의 기말 팀프로젝트(2인1조)
- Achro.imx6q 보드를 이용하여 Linux환경에서 프로젝트 진행
- LCD, 7Segement, Push Switch, Step Motor, Buzzer, Dot Matrix, LED모듈, 화재감지 센서를 이용하여 제작

  - 프로젝트 내용
    - LCD,7 Segement에는 현재 시간과 날짜표시
    - Push Swithc를 이용하여 시간 및 날짜를 조정 가능
    - 화재감지센서를 통해 화재발생이 감지되면 LED, Dot Matrix, Buzzer를 통해 경고 표시
    - 일정시간동안 발생시스템을 끄지 않으면 2차 경고로 Motor 작동
    - [project_fire.c](https://github.com/EunJinK/Project/tree/main/Fire/fire/project_fire.c)
