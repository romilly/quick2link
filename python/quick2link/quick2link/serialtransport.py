__author__ = 'romilly'

import serial, time

HIGH = 1
LOW = 0

class SerialTransport:
    def __init__(self, port='/dev/ttyACM0', baud=38400, timeout=1):
        self._ser = serial.Serial(port, baud, timeout=timeout)

    def ser(self):
        return self._ser

    def receive(self):
        return self.ser().readline()

    def send(self, text):
        self.ser().write(text + '\n')
        self.ser().flushOutput()

    def ask(self, text):
        self.send(text)
        time.sleep(0.1)
        return self.receive()

    def close(self):
        self.ser().close()


class Arduino():
    def __init__(self, debug=False):
        self._debug = debug
        self._transport = SerialTransport()
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

def wait_millis(number):
    return command('m', number)

def set(number):
    return command('o', number)

def repeat(count, *requests):
    return command('{', count) +request_string(requests)+'}'

ard = Arduino()
ard.ask(pin(13), repeat(50, set(HIGH), wait_millis(100), set(LOW), wait_millis(200)))
ard.close()


