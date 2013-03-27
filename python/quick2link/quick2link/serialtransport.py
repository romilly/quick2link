__author__ = 'romilly'

import time
import sys
import serial
import serial.tools.list_ports
from contextlib import contextmanager

HIGH = 1
LOW = 0
DEFAULT_PORT='/dev/ttyACM0'

def _port():
    def osx_port():
        for portname, description, id in serial.tools.list_ports.comports():
            if 'tty.usbmodem' in portname: return portname
        raise serial.SerialException('No serial port on OS/X in: ' + str(serial.tools.list_ports.comports()))

    if 'linux' in sys.platform: return DEFAULT_PORT
    if 'darwin' in sys.platform: return osx_port()
    raise serial.SerialException('No serial port for platform: ' + sys.platform)

@contextmanager
def closing(closeable):
    try:
        yield closeable
    finally:
        closeable.close()

class SerialTransportException(serial.SerialException):
    """Failure in communicating with device"""

class SerialHalfDuplexTransport:
    def __init__(self, port=_port(), baud=115200):
        self._ser = serial.Serial(port, baud)
        self._receive()

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

OK = '0'
class Arduino():
    def __init__(self, port=_port()):
        self._transport = SerialHalfDuplexTransport(port=port)
        time.sleep(0.1)

    def ask(self, *requests):
        request = _do(requests)
        return _error_checked(request, self._transport.ask(request))

    def close(self):
        self._transport.close()

def _do(requests): return "".join(requests)
def _error_checked(request, response):
    if len(response) == 0: raise SerialTransportException("Empty response from Arduino")
    if response[0] != OK: raise SerialTransportException("Error response from Arduino: '" + response + "' for '"+ request + "'")
    return response[1:]


def delay_millis(millis): return str(millis) + 'm'
def delay_micros(micros): return str(micros) + 'u'
def digital_write(value): return str(value) + 'o'
def digital_read(): return 'i'
def echo(): return '?'
def on_pin(number): return str(number) + 'd'
def print_value(): return 'p'
def repeat(count, *requests): return str(count) + '{' + _do(requests) + '}'
def whois(): return "h"


