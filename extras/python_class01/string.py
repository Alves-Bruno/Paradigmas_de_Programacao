import sys

def ola(name):
    
    if name == 'Bruno':
        print('Hello', name.upper() + '.')
        
    else: 
        print('You are NOT Bruno. You are', name + '.')

def full_name(name):

    espaco = name.find(' ')
    first_name = name[0:espaco]
    print('Your first name is:', first_name + '.')
    print('Your last name is:', name[espaco + 1:] + '.')

def main():

    ola('Bruno')
    full_name('Bruno Alves')
    

#Calling the main function
if __name__ == '__main__':
    main()