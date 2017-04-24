import curses
from curses import KEY_RIGHT, KEY_LEFT, KEY_UP, KEY_DOWN # @UnresolvedImport
from ball import *
import time

tela = Screen(24, 80)

PLAYER_TAM = 3

curses.initscr()
win = curses.newwin(tela.MAX_X, tela.MAX_Y, 0, 0)   # @UndefinedVariable
win.keypad(1)
curses.noecho()                     # @UndefinedVariable
curses.curs_set(0)                  # @UndefinedVariable
win.border(0)
win.nodelay(1)

key = KEY_RIGHT                                                    
score1 = 0
score2 = 0

ball = Ball(12, 45, 'NE', tela)
PLAYER1 = Player('l', win, tela)
PLAYER2 = Player('r', win, tela)


while key != 32:                                                   
    win.border(0)
    win.addstr(1, tela.MAX_Y/2 - 3,str(score1))
    win.addstr(1, tela.MAX_Y/2 + 3,str(score2))
    win.addstr(0, tela.MAX_Y/2, 'PONG')
    win.addstr(tela.MAX_X -1, 3, ' Press SPACE to return ... ')                

    win.addch(ball.x, ball.y, ' ')
    ball.move()
    win.addch(ball.x, ball.y, '0')
#     win.addstr(0, 0, 'x:' + str(ball.x) + ' Y:' + str(ball.y))
    time.sleep(0.09)
     
    PLAYER1.draw(ball)
    PLAYER2.draw(ball)
     
    key = win.getch()

    [win.addch(X, tela.MAX_Y/2, ':') for X in range(1, tela.MAX_X - 1)] 
    
   
curses.endwin()              # @UndefinedVariable
print("OBRIGADO POR JOGAR!")





















