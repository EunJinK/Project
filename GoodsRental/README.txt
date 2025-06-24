* 보드A(초음파센서)
* 보드B(로터리엔코더, OLED)

보드A에서 초음파센서값이 10cm 이하일 경우(10cm이하면 릴레이on, 초과면 릴레이off)
esp/test토픽으로 pub, influxdb에 올릴 초음파센서 값은 esp/allultra토픽으로 모든값을 전달함

보드B에서 보드A가 esp/test토픽으로 pub한 메세지를 esp/test토픽으로 sub함
sub하게 될 시 callback이 실행되어 매개변수에 저장되고 payload에서 저장된 값을 읽어 msg 로 저장됨
(callback 시 payload값이 바뀌기 때문에 payload에 저장되는 것이 아님)

msg길이가 0보다 크면 OLED활성화 후 '사용중' 또는 '사용가능' 상태를 띄움

우분투환경의 컨테이너에 접속하여 python influx.py를 실행하면 influxdb로 지정한 토픽의 값을 올림
