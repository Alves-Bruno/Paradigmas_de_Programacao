import curses

class Ball(object):

    def __init__(self, x, y, movement, tela):
        self.x = x
        self.y = y
        self.mov = movement
        self.maxX = tela.MAX_X - 1
        self.maxY = tela.MAX_Y - 1

    def moveNorthWest(self):
        self.x -= 1
        self.y -= 1

    def moveNorthEast(self):
        self.x += 1 
        self.y -= 1

    def moveSouthEast(self):
        self.x += 1
        self.y += 1

    def moveSouthWest(self):
        self.x -= 1
        self.y += 1
    
    def moveAux(self):
        if self.mov == 'NW':
            self.moveNorthWest()
        elif self.mov == 'NE':
            self.moveNorthEast()
        elif self.mov == 'SW':
            self.moveSouthWest()
        elif self.mov == 'SE':
            self.moveSouthEast()
        else:
            self.mov = 'SE'
    
    def move(self):
        
        if self.mov == 'SE' and self.y == self.maxY -1:
            self.mov = 'NE'
        elif self.mov == 'SE' and self.x == self.maxX -1:
            self.mov = 'SW'
        elif self.mov == 'SW' and self.y == self.maxY -1:
            self.mov = 'NW'
        elif self.mov == 'SW' and self.x == 1:
            self.mov = 'SE'
        elif self.mov == 'NW' and self.y == 1:
            self.mov = 'SW'
        elif self.mov == 'NW' and self.x == 1:
            self.mov = 'NE'
        elif self.mov == 'NE' and self.x == self.maxX -1:
            self.mov = 'NW'
        elif self.mov == 'NE' and self.y == 1:
            self.mov = 'SE'
        
        self.moveAux()
        
class Player(object):
  
    def __init__(self, side, win, screen):
        self.pos = 0
        self.side = side
        self.win = win
        self.tela = screen
        self.last = 0
        
    def draw(self, ball):
         
        self.pos = ball.x
         
        self.clean()
         
        if self.side == 'l':
            
            if self.pos < 4 and ball.y < 40:
                [self.win.addch(Y, 1, '|') for Y in range(1, 4)]
                self.last=self.pos
            elif self.pos > self.tela.MAX_X - 4 and ball.y < 40:
                [self.win.addch(Y, 1, '|') for Y in range(self.tela.MAX_X - 4, self.tela.MAX_X -1)]
                self.last=self.pos
            elif ball.y < 40:
                [self.win.addch(Y, 1, '|') for Y in range(self.pos - 1, self.pos + 2)]
                self.last=self.pos
            else:
                [self.win.addch(Y, 1, '|') for Y in range(self.last, self.last + 3)]
                  
                  
        if self.side == 'r':
            
            if self.pos < 4 and ball.y > 40:
                [self.win.addch(Y, self.tela.MAX_Y -2, '|') for Y in range(1, 4)]
                self.last=self.pos
            elif self.pos > self.tela.MAX_X - 4 and ball.y > 40:
                [self.win.addch(Y, self.tela.MAX_Y -2, '|') for Y in range(self.tela.MAX_X - 4, self.tela.MAX_X -1)]
                self.last=self.pos
            elif ball.y > 40:
                [self.win.addch(Y, self.tela.MAX_Y -2, '|') for Y in range(self.pos - 1, self.pos + 2)]
                self.last=self.pos
            else:
                [self.win.addch(Y, self.tela.MAX_Y -2, '|') for Y in range(self.last, self.last + 3)]
     
    def clean(self):
        
        if self.side == 'l':
            [self.win.addch(Y, 1, ' ') for Y in range(1, self.tela.MAX_X - 1)]
   
        if self.side == 'r':
            [self.win.addch(Y, self.tela.MAX_Y -2, ' ') for Y in range(1, self.tela.MAX_X - 1)]
    
    
class Screen(object):

    def __init__(self, MAX_X, MAX_Y):
        self.MAX_X = MAX_X
        self.MAX_Y = MAX_Y
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        