import unittest
from quick2link.serialtransport import *

__author__ = 'romilly'


class ArduinoSerialTransportTest(unittest.TestCase):
    def testSerialTransportSendsAndReceivesFixedResponse(self):
        with closing(SerialTransport()) as transport:
            transport.send("?")
            self.assertIn("arduino", transport.receive())



if __name__ == '__main__':
    unittest.main()
