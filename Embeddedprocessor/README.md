## _1. alarm_
- 8bit MCU ATmega 128을 이용한 알람시계
- 기능
  - 키패드의 모드 키(M1)은 시간 설정용 키, 모드 키(M2)는 알람 설정용 키
  - 부저를 이용하여 알람음 발생
  - 모드 키(M3)는 AM/PM설정 표시
  - M2를 이용한 알람 설정 후 해당 시간이 되면 비교하여 알람음 발생


- 프로젝트 내용
  - 초기 년 월 일 시 분 초 LCD출력 후 타이머 작동으로 시간 흐름
  - 모드 키(M1)을 누르면 LCD에 "Key Setting!!" 출력, "---Insert Key---" 출력 후 년 월 일 시 분 초를 입력받음
  - 모드 키(M2)를 누르면 LCD에 "-Alarm Set Mode-" 출력, "--Insert Alarm--" 출력 후 월 일 시 분 초 입력받음
  - 총 3개의 알람을 설정하기 위해 입력받는 과정 3번 반복
  - 설정된 알람과 현재 시간이 맞으면 알람음 발생
    - 알람이 켜지자마자 설정되었던 해당 알람시간은 초기화
    - PIND.0 인터럽트 발생시 알람음 정지
- 모드 키(M3)를 이용해 AM/PM 변환 가능

- 결과사진
<div>
<img src="https://user-images.githubusercontent.com/59238838/101476857-b71b6880-3991-11eb-9b09-16907857bb66.PNG" width="300" height="300">
<img src="https://user-images.githubusercontent.com/59238838/101476854-b5ea3b80-3991-11eb-8ffe-ebac8daf2d63.PNG" width="300" height="300">	
</div>
<samp>
	초기 시간 설정(왼), 알람 시간 설정(오)
</samp>
<div>
<img src="https://user-images.githubusercontent.com/59238838/101476851-b551a500-3991-11eb-8928-4e0e03170725.PNG" width="300" height="300">
<img src="https://user-images.githubusercontent.com/59238838/101476829-acf96a00-3991-11eb-8d55-2af5c73bb3ca.PNG" width="300" height="300">
</div>
<samp>
	알람화면(왼), AM/PM 변환 화면(오)
</samp>	


## _2. safe_
- 8bit MCU ATmega 128을 이용한 금고 개폐 시스템
- 기능
  - 키패드, 부저, LCD를 이용하여 금고 만들기
  - 모드 키(M1)은 비밀번호 4자리 설정용 키
  - 키패드로 비밀번호를 입력받고 LCD로 표현
  - 부저를 통한 알람음 출력


- 프로젝트 내용
  - 모든 비밀번호 표시는 "*"로 진행
  - 초기 관리자 비밀번호 입력 후 초기상태 표시
    - LCD에 "Set M-Password" 출력 후 관리자 비밀번호를 입력받고 초기상태표시
  - 모드 키(M1)은 비밀번호 4자리 설정용 키로 LCD에 "Set Password"출력 후 비밀번호 4자리를 입력받고 "Close KPU Safe" 출력
  - 비밀번호를 맞게 입력하면 성공알림음이 울린 후 "Open KPU Safe" 출력
  - 비밀번호를 틀리게 입력하면 실패알림음이 울린 후 "---- Error! ----" 출력
  - 에러 2번 이상이면 관리자비밀번호를 받음

- 결과사진
<div>
<img src="https://user-images.githubusercontent.com/59238838/101474289-49217200-398e-11eb-908f-bc9ed99ab8c4.PNG" width="300" height="300">
<img src="https://user-images.githubusercontent.com/59238838/101474300-4fafe980-398e-11eb-811a-40383272705a.PNG" width="300" height="300">	
</div>
<samp>
	관리자 비밀번호 설정(왼), 초기 비밀번호 4자리 설정(오)
</samp>
<div>
<img src="https://user-images.githubusercontent.com/59238838/101474303-50e11680-398e-11eb-8c8d-f12058bcb446.PNG" width="300" height="300">
<img src="https://user-images.githubusercontent.com/59238838/101474311-53437080-398e-11eb-84e5-899508306e32.PNG" width="300" height="300">
</div>
<samp>
	비밀번호 입력 후 성공/실패(왼), 2번 이상의 오류로 관리자비밀번호를 입력하여 재오픈(오)
</samp>	