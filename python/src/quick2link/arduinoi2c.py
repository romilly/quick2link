from quick2wire.i2c import I2CMaster, writing, reading

arduino_address = 0x04
buffer_size = 64

class ArduinoI2cTransport:
    def __init__(self, address=arduino_address):
        self.master = I2CMaster()
        self.address = address

    def ask(self, text):
        reply = self.master.transaction(
            writing(self.address, text.encode('utf-8')),
            reading(self.address, buffer_size))
        reply_length = reply[0][0]
        return reply[0][1:reply_length + 1].decode('utf-8')
        

    def close(self):
        self.master.close()
