import unittest
from quick2link.serialtransport import *

__author__ = 'romilly'


class SerialHalfDuplexTransportTest(unittest.TestCase):
    def testSerial_transport_asks_for_result(self):
        with closing(SerialHalfDuplexTransport()) as transport:
            self.assertIn("arduino", transport.ask('?'))

BAD_REQUEST='`'
class ArduinoTest(unittest.TestCase):
    def setUp(self):
        self.arduino = Arduino()
    def tearDown(self):
        if self.arduino is not None: self.arduino.close()

    def testRespondsWithIdentifier(self):
        self.assertEqual("arduino", self.arduino.ask(whois()))

    def testFailsWithUnknownCommand(self):
        with self.assertRaises(SerialTransportException) as cm:
            self.arduino.ask(BAD_REQUEST)
        self.assertIn(BAD_REQUEST, str(cm.exception))

if __name__ == '__main__':
    unittest.main()
