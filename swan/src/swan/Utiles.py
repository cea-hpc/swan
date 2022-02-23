import os
import glob

def format(u):
    return str(u)

def slice(u):
    return u[0:500]

def x(u):
    x = []
    for record in u:
        x.append(record[0])
    return x

def getSliceX(u):
    return format(x(slice(u)))[1:-1]

def getSlice(u):
    return format(slice(u))[1:-1]

def escapeDot(s):
    return str(s).replace('.','')

def clean(s):
    fileList = glob.glob(s)
    for filePath in fileList:
        try:
            os.remove(filePath)
        except:
            return("Error while deleting file : ", filePath)

def dump(f, h):
    fic = open(f,'/home/oudotmp/workspaces/swan/swan/src/swan/dumpH.csv')

    fic.write(str(h))
    fic.write("\n")
        
    fic.flush()