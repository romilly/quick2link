from contextlib import closing
import unittest
from quick2link.serialtransport import *

__author__ = 'romilly'


class SerialHalfDuplexTransportTest(unittest.TestCase):
    def testSerial_transport_asks_for_result(self):
        with closing(SerialHalfDuplexTransport()) as transport:
            self.assertIn("arduino", transport.ask('h'))

BAD_REQUEST = '`'

class ArduinoTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.transport = SerialHalfDuplexTransport()

    @classmethod
    def tearDownClass(cls):
        if cls.transport is not None: cls.transport.close()

    def setUp(self):
        self.arduino = Device(self.__class__.transport)

    def testRespondsWithIdentifier(self):
        self.assertEqual("arduino x=13, digitalPin=13", self.arduino.ask(on_pin(13), whois()))

    def testFailsWithUnknownCommand(self):
        with self.assertRaises(SerialTransportException) as cm:
            self.arduino.ask(BAD_REQUEST)
        exception_message = str(cm.exception)
        self.assertIn("'1" + BAD_REQUEST + "'", exception_message)

    def testPrintsCurrentNumber(self):
        self.assertEqual("234>?234p", self.arduino.ask(echo(), "234", print_value()))

    def testDigitalPinSettingPersistsBetweenRequest(self):
        self.assertIn("digitalPin=7", self.arduino.ask(on_pin(7), whois()))
        self.assertIn("digitalPin=7", self.arduino.ask(whois()))

    def testEchoesProcessedCharacters(self):
        self.assertEqual(
            "arduino x=7, digitalPin=7>?h",
            self.arduino.ask(on_pin(7), echo(), whois()))

    def testIgnoresSpaces(self):
        self.assertEqual("00>?  p  p", self.arduino.ask(echo(), "  p  p"))

    def testAcceptsDelayRequests(self):
        self.assertEqual("16>?16mp", self.arduino.ask(echo(), delay_millis(16), print_value()))
        self.assertEqual("75>?75up", self.arduino.ask(echo(), delay_micros(75), print_value()))

    def testRepeatsInstructions(self):
        # connect digital pins 11 <-> 12
        self.arduino.ask(on_pin(12), digital_write(HIGH))
        self.assertEqual("111>?11d2{ip}ip}ip}p",
            self.arduino.ask( echo(),
                on_pin(11),
                repeat(2, digital_read(), print_value()),
                print_value()))

    def testWritesAndReadsDigitalPin(self):
        # connect digital pins 11 <-> 12
        self.assertEqual("1>?12d1o11dip",
            self.arduino.ask(
                echo(),
                on_pin(12), digital_write(HIGH),
                on_pin(11), digital_read(), print_value()))
        self.assertEqual("0>?12d0o11dip",
            self.arduino.ask(
                echo(),
                on_pin(12), digital_write(LOW),
                on_pin(11), digital_read(), print_value()))

    def testReadsAnalogPin(self):
        # connect digital pin 7 to analog pin 0
        self.checkAnalogReadResponse(HIGH, 1021, 1023, "?7d1o0dsp")
        self.checkAnalogReadResponse(LOW, 0, 2, "?7d0o0dsp")

    def askForAnalogInput(self, LEVEL):
        return self.arduino.ask(
            echo(),
            on_pin(7), digital_write(LEVEL),
            on_pin(0), analog_read(), print_value())

    def checkAnalogReadResponse(self, level, low, high, expected_text):
        response = self.askForAnalogInput(level)
        self.assertTrue('>' in response, 'unexpected response without > %s' % response)
        (analog_reading, echoed) = response.split('>')
        value = int(analog_reading)
        self.assertTrue(low <= value & value <= high, "analogue value %i should be between %i and %i" % (value, low, high))
        self.assertEqual(echoed, expected_text)


if __name__ == '__main__':
    unittest.main()
