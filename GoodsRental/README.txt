보드A(초음파센서)에서 초음파센서 값이 10cm 이하면 (10cm이하면 릴레이on, 초과면 off)
esp/test토픽으로 pub, influxdb에 올릴 초음파센서 값은 esp/allultra토픽으로 모든값을 전달

보드B(로터리엔코더, OLED)에서 보드A가 esp/test토픽으로 pub한 메세지를 esp/test토픽으로 sub한다.
sub하게되면 callback(자동으로 sub되면 불려짐 내가부르는것이 아님)이 실행되어 매개변수에 저장이 된다.
payload에 저장된 값을 읽어 msg로 저장시킨다. (콜백이불려질때마다 payload값이 바뀌기때문에 payload에 저장되는 것이 아님)

msg길이가 0보다 크면 OLED활성화 후 사용 중or사용가능상태 띄운다.

우분투환경들어간 후 docker exec -it myPy /bin/bash -> myPy docker속으로 들어간 후(?)
python influx.py를 실행하면 influxdb로 지정한 토픽의 값을 올림




