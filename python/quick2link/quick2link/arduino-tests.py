import unittest
import sys
from quick2link.serialtransport import *

__author__ = 'romilly'

def port():
    if 'linux' in sys.platform: return DEFAULT_PORT
    if 'darwin' in sys.platform: return '/dev/cu.usbmodemfa131'
    raise AssertionError('No port for platform: ' + sys.platform)


class ArduinoSerialTransportTest(unittest.TestCase):
    def testSerialTransportSendsAndReceives(self):
        arduino = Arduino(port=port())
        arduino.ask(pin(12), digital_write(HIGH), wait_millis(100))
        self.assertEquals(HIGH, arduino.ask(pin(11), digital_read()))


if __name__ == '__main__':
    unittest.main()