## _1. alarm_
- 8bit MCU ATmega 128�� �̿��� �˶��ð�
- ���
  - Ű�е��� ��� Ű(M1)�� �ð� ������ Ű, ��� Ű(M2)�� �˶� ������ Ű
  - ������ �̿��Ͽ� �˶��� �߻�
  - ��� Ű(M3)�� AM/PM���� ǥ��
  - M2�� �̿��� �˶� ���� �� �ش� �ð��� �Ǹ� ���Ͽ� �˶��� �߻�


- ������Ʈ ����
  - �ʱ� �� �� �� �� �� �� LCD��� �� Ÿ�̸� �۵����� �ð� �帧
  - ��� Ű(M1)�� ������ LCD�� "Key Setting!!" ���, "---Insert Key---" ��� �� �� �� �� �� �� �ʸ� �Է¹���
  - ��� Ű(M2)�� ������ LCD�� "-Alarm Set Mode-" ���, "--Insert Alarm--" ��� �� �� �� �� �� �� �Է¹���
  - �� 3���� �˶��� �����ϱ� ���� �Է¹޴� ���� 3�� �ݺ�
  - ������ �˶��� ���� �ð��� ������ �˶��� �߻�
    - �˶��� �����ڸ��� �����Ǿ��� �ش� �˶��ð��� �ʱ�ȭ
    - PIND.0 ���ͷ�Ʈ �߻��� �˶��� ����
- ��� Ű(M3)�� �̿��� AM/PM ��ȯ ����

- �������
<div>
<img src="https://user-images.githubusercontent.com/59238838/101476857-b71b6880-3991-11eb-9b09-16907857bb66.PNG" width="300" height="300">
<img src="https://user-images.githubusercontent.com/59238838/101476854-b5ea3b80-3991-11eb-8ffe-ebac8daf2d63.PNG" width="300" height="300">	
</div>
<samp>
	�ʱ� �ð� ����(��), �˶� �ð� ����(��)
</samp>
<div>
<img src="https://user-images.githubusercontent.com/59238838/101476851-b551a500-3991-11eb-8928-4e0e03170725.PNG" width="300" height="300">
<img src="https://user-images.githubusercontent.com/59238838/101476829-acf96a00-3991-11eb-8d55-2af5c73bb3ca.PNG" width="300" height="300">
</div>
<samp>
	�˶�ȭ��(��), AM/PM ��ȯ ȭ��(��)
</samp>	


## _2. safe_
- 8bit MCU ATmega 128�� �̿��� �ݰ� ���� �ý���
- ���
  - Ű�е�, ����, LCD�� �̿��Ͽ� �ݰ� �����
  - ��� Ű(M1)�� ��й�ȣ 4�ڸ� ������ Ű
  - Ű�е�� ��й�ȣ�� �Է¹ް� LCD�� ǥ��
  - ������ ���� �˶��� ���


- ������Ʈ ����
  - ��� ��й�ȣ ǥ�ô� "*"�� ����
  - �ʱ� ������ ��й�ȣ �Է� �� �ʱ���� ǥ��
    - LCD�� "Set M-Password" ��� �� ������ ��й�ȣ�� �Է¹ް� �ʱ����ǥ��
  - ��� Ű(M1)�� ��й�ȣ 4�ڸ� ������ Ű�� LCD�� "Set Password"��� �� ��й�ȣ 4�ڸ��� �Է¹ް� "Close KPU Safe" ���
  - ��й�ȣ�� �°� �Է��ϸ� �����˸����� �︰ �� "Open KPU Safe" ���
  - ��й�ȣ�� Ʋ���� �Է��ϸ� ���о˸����� �︰ �� "---- Error! ----" ���
  - ���� 2�� �̻��̸� �����ں�й�ȣ�� ����

- �������
<div>
<img src="https://user-images.githubusercontent.com/59238838/101474289-49217200-398e-11eb-908f-bc9ed99ab8c4.PNG" width="300" height="300">
<img src="https://user-images.githubusercontent.com/59238838/101474300-4fafe980-398e-11eb-811a-40383272705a.PNG" width="300" height="300">	
</div>
<samp>
	������ ��й�ȣ ����(��), �ʱ� ��й�ȣ 4�ڸ� ����(��)
</samp>
<div>
<img src="https://user-images.githubusercontent.com/59238838/101474303-50e11680-398e-11eb-8c8d-f12058bcb446.PNG" width="300" height="300">
<img src="https://user-images.githubusercontent.com/59238838/101474311-53437080-398e-11eb-84e5-899508306e32.PNG" width="300" height="300">
</div>
<samp>
	��й�ȣ �Է� �� ����/����(��), 2�� �̻��� ������ �����ں�й�ȣ�� �Է��Ͽ� �����(��)
</samp>	