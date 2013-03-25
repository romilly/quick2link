__author__ = 'romilly'

import serial, time

HIGH = 1
LOW = 0
DEFAULT_PORT='/dev/ttyACM0'

class SerialTransport:
    def __init__(self, port=DEFAULT_PORT, baud=115200):
        self._ser = serial.Serial(port, baud, timeout=None)
        self._ser.readline()

    def receive(self):
        return self._ser.readline()

    def send(self, text):
        self._ser.write(text + '\n')
        self._ser.flushOutput()

    def ask(self, text):
        self.send(text)
        back = self.receive().strip()
        return back

    def close(self):
        self._ser.close()


class Arduino():
    def __init__(self, debug=False, port='/dev/ttyACM0'):
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

# ard = Arduino()
# ard.ask(repeat(10, set(HIGH), wait_millis(1000), set(LOW), wait_millis(1000)))
# ard.close()


