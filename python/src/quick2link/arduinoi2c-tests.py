import unittest
from contextlib import closing
from arduinoi2c import ArduinoI2cTransport

class ArduinoI2CTransportTest(unittest.TestCase):
    def test_I2C_transport_asks_for_result(self):
        with closing(ArduinoI2cTransport()) as transport:
            self.assertIn("arduino", transport.ask('h'))

if __name__ == '__main__':
    unittest.main()
