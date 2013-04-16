__author__ = 'romilly'

import time
import sys
import serial
from contextlib import contextmanager

HIGH = 1
LOW = 0
OK = '0'
# TODO: Windows and Mac
DEFAULT_PORT = '/dev/ttyACM0'


def _port():
    def osx_port():
        import serial.tools.list_ports
        for portname, description, port_id in serial.tools.list_ports.comports():
            if 'tty.usbmodem' in portname: return portname
        raise serial.SerialException('No serial port on OS/X in: ' + str(serial.tools.list_ports.comports()))

    if 'linux' in sys.platform: return DEFAULT_PORT
    if 'darwin' in sys.platform: return osx_port()
    raise serial.SerialException('No serial port for platform: ' + sys.platform)

class SerialTransportException(serial.SerialException):
    """Failure in communicating with device"""


class SerialHalfDuplexTransport:
    def __init__(self, port=_port(), baud=115200, timeout=5):
        self._ser = serial.Serial(port, baud, timeout=timeout)
        time.sleep(2)

    def _receive(self):
        return self._ser.readline()

    def _send(self, text):
        self._ser.write(text + '\n')
        self._ser.flush()

    def ask(self, text):
        self._send(text)
        return self._receive().strip()

    def close(self):
        self._ser.close()


class Device():
    def __init__(self, transport):
        self._transport = transport

    def ask(self, *requests):
        request = _do(requests)
        return _error_checked(request, self._transport.ask(request))

def _do(requests): return "".join(requests)
def _error_checked(request, response):
    if len(response) == 0: raise SerialTransportException("Empty response from Device")
    if response[0] != OK: raise SerialTransportException("Error response from Device: '" + response + "' for '"+ request + "'")
    return response[1:]


def delay_millis(millis): return str(millis) + 'm'
def delay_micros(micros): return str(micros) + 'u'
def digital_write(value): return str(value) + 'o'
def digital_read(): return 'i'
def analog_read(): return 's'
def servo_position(pos): return str(pos) + 't'
def echo(): return '?'
def on_pin(number): return str(number) + 'd'
def print_value(): return 'p'
def repeat(count, *requests): return str(count) + '{' + _do(requests) + '}'
def whois(): return "h"


