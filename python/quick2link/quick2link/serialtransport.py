__author__ = 'romilly'

import serial, time

HIGH = 1
LOW = 0
DEFAULT_PORT='/dev/ttyACM0'

class SerialTransport:
    def __init__(self, port=DEFAULT_PORT, baud=9600, timeout=1):
        self._ser = serial.Serial(port, baud, timeout=timeout)

    def receive(self):
        return self._ser.readline()

    def send(self, text):
        self._ser.write(text + '\n')
        self._ser.flushOutput()

    def ask(self, text):
        self.send(text)
        time.sleep(0.1)
        return self.receive()

    def close(self):
        self._ser.close()


class Arduino():
    def __init__(self, debug=False, port='/dev/ttyACM0'):
        self._debug = debug
        self._transport = SerialTransport(port=port)
        time.sleep(1)
        self._transport.receive()

    def ask(self, *requests):
        string = request_string(requests)
        if self._debug:
            print string
        self._transport.ask(string)

    def close(self):
        self._transport.close()


def request_string(requests):
    return "".join(requests)


def command(code, number):
    return "%d%s" % (number, code)


def pin(number):
    return command('d', number)


def wait_millis(millis):
    return command('m', millis)


def digital_write(value):
    return command('o', value)


def digital_read():
    return 'ip'


def repeat(count, *requests):
    return command('{', count) + request_string(requests) + '}'

# ard = Arduino()
# ard.ask(repeat(10, set(HIGH), wait_millis(1000), set(LOW), wait_millis(1000)))
# ard.close()


