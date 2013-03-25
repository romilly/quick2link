import unittest
from quick2link.serialtransport import *

__author__ = 'romilly'


class ArduinoSerialTransportTest(unittest.TestCase):
    def testSerial_transport_sends_a_line_and_receives_a_line(self):
        with closing(SerialTransport()) as transport:
            transport.send("?")
            self.assertEqual("0arduino", transport.receive().strip())
    def testSerial_transport_asks_for_result(self):
        with closing(SerialTransport()) as transport:
            self.assertEqual("0arduino", transport.ask('?').strip())


if __name__ == '__main__':
    unittest.main()
