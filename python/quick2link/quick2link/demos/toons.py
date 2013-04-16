__author__ = 'romilly'

from quick2link.serialtransport import *
import time


scale = {'c':  261,
         'd':  294,
         'e':  329,
         'f':  349,
         'g':  392,
         'a':  440,
         'b':  493,
         'C':  523
         }

tempo = 4

class Player():
    def __init__(self, micro):
        self._micro = micro

    def play(self, notes):
        self._micro.ask(on_pin(5))
        for note in notes:
            self.play_note(note)

    def play_note(self, note):
        if note == ' ':
            time.sleep( 1/ tempo)
            return
        (repeats, semi_period) = self. _note(note)
        return self._micro.ask(repeat(repeats, digital_write(HIGH), delay_micros(semi_period), digital_write(LOW), delay_micros(semi_period)), delay_millis(10))

    def _note(self, note):
        frequency = scale[note]
        semi_period = 1000000L / frequency * 2
        repeats = frequency / tempo
        return repeats, semi_period

    def close(self):
        self._micro.close()

with closing(Player(Device())) as player:
    #ard.ask(pin(9), repeat(50, digital_write(HIGH), wait_micros(4000), digital_write(LOW), wait_micros(4000)))
    player.play('ccggaag ffeeddc')
