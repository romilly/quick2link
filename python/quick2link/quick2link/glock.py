from quick2link.serialtransport import *

__author__ = 'romilly'


arduino = Device()
print arduino.ask(on_pin(5),servo_position(60), delay_millis(500),servo_position(0),delay_millis(500), servo_position(60), delay_millis(500), servo_position(0))
arduino.close()

