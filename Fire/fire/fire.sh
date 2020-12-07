insmod fpga_led_driver.ko
insmod fpga_dot_driver.ko
insmod fpga_text_lcd_driver.ko
insmod fpga_buzzer_driver.ko
insmod fpga_fnd_driver.ko
insmod fpga_push_switch_driver.ko
insmod fpga_step_motor_driver.ko
insmod f_driver.ko
mknod /dev/fpga_led c 260 0
mknod /dev/fpga_fnd c 261 0
mknod /dev/fpga_dot c 262 0
mknod /dev/fpga_text_lcd c 263 0
mknod /dev/fpga_buzzer c 264 0
mknod /dev/fpga_push_switch c 265 0
mknod /dev/fpga_step_motor c 267 0
mknod /dev/ext_fire_sens c 246 0
