from quick2wire.i2c import I2CMaster, writing, reading

arduino_address = 0x04
buffer_size = 64
encoding='utf-8'

def contents_of(reply):
    reply_length = reply[0]
    return reply[1:reply_length + 1].decode(encoding)
    

class ArduinoI2cTransport:
    def __init__(self, address=arduino_address):
        self.master = I2CMaster()
        self.address = address

    def _request(self, text):
        return self.master.transaction(
            writing(self.address, text.encode(encoding)),
            reading(self.address, buffer_size))[0]
        
    def ask(self, text):
        return contents_of(self._request(text))

    def close(self):
        self.master.close()
