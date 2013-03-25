__author__ = 'romilly'

import time
import sys
import serial
import serial.tools.list_ports
from contextlib import contextmanager

HIGH = 1
LOW = 0
DEFAULT_PORT='/dev/ttyACM0'

def port():
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


class SerialTransport:
    def __init__(self, port=port(), baud=115200):
        self._ser = serial.Serial(port, baud)
        self._ser.readline()

    def receive(self):
        return self._ser.readline()

    def send(self, text):
        self._ser.write(text + '\n')
        self._ser.flush()

    def ask(self, text):
        self.send(text)
        return self.receive().strip()

    def close(self):
        self._ser.close()


class Arduino():
    def __init__(self, debug=False, port=port()):
        self._debug = debug
        self._transport = SerialTransport(port=port)
        time.sleep(0.1)

    def ask(self, *requests):
        string = do(requests)
        if self._debug:
            print string
        return self._transport.ask(string)

    def close(self):
        self._transport.close()


def do(requests):
    return "".join(requests)


def command(code, number):
    return "%d%s" % (number, code)


def pin(number):
    return command('d', number)


def wait_millis(millis):
    return command('m', millis)

def wait_micros(micros):
    return command('u', micros)


def digital_write(value):
    return command('o', value)


def digital_read():
    return 'i'


def repeat(count, *requests):
    return command('{', count) + do(requests) + '}'

def print_value():
    return 'p'

