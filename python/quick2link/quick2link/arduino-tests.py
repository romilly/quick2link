import unittest
from quick2link.serialtransport import *

__author__ = 'romilly'


class ArduinoSerialTransportTest(unittest.TestCase):
    def testSerialTransportSendsAndReceives(self):
        arduino = Arduino()
        arduino.ask(pin(12), digital_write(HIGH), wait_millis(100))
        self.assertEquals(HIGH, arduino.ask(pin(11), digital_read()))


if __name__ == '__main__':
    unittest.main()
