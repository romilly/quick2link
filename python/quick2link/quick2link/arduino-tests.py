import unittest
from quick2link.serialtransport import *

__author__ = 'romilly'


class SerialHalfDuplexTransportTest(unittest.TestCase):
    def testSerial_transport_asks_for_result(self):
        with closing(SerialHalfDuplexTransport()) as transport:
            self.assertIn("arduino", transport.ask('?'))

class ArduinoTest(unittest.TestCase):
    def testRespondsWithIdentifier(self):
        with closing(Arduino()) as arduino:
            self.assertEqual("arduino", arduino.ask(whois()))

if __name__ == '__main__':
    unittest.main()
