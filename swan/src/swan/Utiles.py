import os

def format(u):
    return str(u)

def dump(f, u):
    fic = open(f,'a')

    fic.write(str(u))
    fic.write("\n")
        
    fic.flush()