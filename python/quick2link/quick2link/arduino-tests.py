import unittest
from quick2link.serialtransport import *

__author__ = 'romilly'


class ArduinoSerialTransportTest(unittest.TestCase):
    def testSerialTransportSendsAndReceivesFixedResponse(self):
        transport = SerialTransport()
        try:
            transport.send("?")
            self.assertIn("arduino", transport.receive())
        finally:
            transport.close()


    def xtestSerialTransportSendsAndReceives(self):
        arduino = Arduino()
        try:
            arduino.ask(pin(12), digital_write(HIGH), wait_millis(10))
            arduino_ask = arduino.ask(pin(11), digital_read(), print_value())
            self.assertEquals(HIGH, int(arduino_ask))
        finally:
            arduino.close()


if __name__ == '__main__':
    unittest.main()
