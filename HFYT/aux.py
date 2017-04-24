import curses
from random import randint

class Screen(object):

    def __init__(self, MAX_X, MAX_Y, difficulty):
        self.MAX_X = MAX_X
        self.MAX_Y = MAX_Y
        self.exit = 0
        self.vidas = 3
        self.difficulty = difficulty
    
        
class Lists(object):
    
    def __init__(self, TAM_MAX, colunm):
        
        self.list = [' ' for x in range(TAM_MAX)]
        self.colunm = colunm
        self.tam = TAM_MAX
        self.pontos = 0
    
    def draw(self, win):
        
        [win.addch(X+1, self.colunm, self.list[X]) for X in range(0, self.tam - 1)]
        
    
    def insert(self, hard):
        
        self.list.pop()
        x = randint(0, hard)
        
        if (x == 0):
            self.list.insert(0, chr(randint(97, 122)))
        else:
            self.list.insert(0, ' ')
            
    def detector(self, key):
        
        if key in self.list:
            
            self.list[self.list.index(key)] = '*'
            self.pontos += 1
            