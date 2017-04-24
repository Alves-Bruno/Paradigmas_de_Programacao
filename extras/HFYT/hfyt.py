import curses
from curses import KEY_RIGHT, KEY_LEFT, KEY_UP, KEY_DOWN # @UnresolvedImport
from aux import *
import time
import threading
import sys

exit_game = 0

tela = Screen(10, 9, int(sys.argv[1]))

curses.initscr()
# stdscr.clear()
# stdscr.refresh()
win = curses.newwin(tela.MAX_Y, tela.MAX_X, 0, 0)   # @UndefinedVariable
win.keypad(1)
curses.noecho()                     # @UndefinedVariable
curses.curs_set(0)                  # @UndefinedVariable
win.border(0)
win.nodelay(1)


key = KEY_DOWN
l1 = Lists(8, 3)
l2 = Lists(8, 4)
l3 = Lists(8, 6)

def init():
    
    while(tela.exit == 0):                                                   
        
        win.border(0)
        win.addstr(0, 0,'LIFES: ' + str(tela.vidas))
        win.addstr(tela.MAX_Y -1, 0,'SCORE:' + str(l1.pontos + l2.pontos + l3.pontos ))
        
        
        l1.draw(win)
        l2.draw(win)
        l3.draw(win)
        l1.insert(tela.difficulty)
        l2.insert(tela.difficulty)
        l3.insert(tela.difficulty)
        
        
        if l1.list[-1] != ' ' and l1.list[-1] != '*':
            tela.vidas -= 1
        if l2.list[-1] != ' ' and l2.list[-1] != '*':
            tela.vidas -= 1
        if l3.list[-1] != ' ' and l3.list[-1] != '*':
            tela.vidas -= 1

                
        time.sleep(0.5)
    
   
    curses.endwin()        # @UndefinedVariable
    

def key_detector():
    
    while(1):
       
        key = win.getch()
        
        if key == 32 or tela.vidas <= 0:
            tela.exit = 1
            return
        
        if key > 96 and key < 123:
        
            keyChr = chr(key)
            l1.detector(keyChr)
            l2.detector(keyChr)
            l3.detector(keyChr)


def main():
    t = threading.Thread(target=key_detector)
    t.start()
    init()
    
    

if __name__ == "__main__":
    main()
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    