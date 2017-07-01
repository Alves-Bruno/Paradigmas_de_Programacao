import sys


with open("regras.txt", "r") as ins:
    array = []
    for line in ins:
        array.append(line)

for x in array:
    teste = repr(x)
#    teste[0] = 'Ç'
#    teste[-1] = 'Ç'
#    print("\"", end="")   

    string = teste[1:-1]
    print("\"", end="") 
    for a in string:
        if a == "\"":
            print("\\\"", end="")             
        else:
            print(a, end="")

    print("\"")
#    print("\n")
        
#    print("\""+teste[1:-1]+"\"")
