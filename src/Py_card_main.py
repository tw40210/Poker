import ctypes
import click
from time import time
so = ctypes.cdll.LoadLibrary
lib = so('./src/libCard.so')

def get_indexed_array(cards_str):
    def get_indexed_num(s):
        o=-1
        if s[0]=="!": f=0
        elif s[0]=="@": f=1
        elif s[0]=="#": f=2
        elif s[0]=="$": f=3
        else:
            raise ValueError(f"Unmatched card:{s}")
        if s[1]=="T": o=8
        elif s[1]=="J": o=9
        elif s[1]=="Q": o=10
        elif s[1]=="K": o=11
        elif s[1]=="A": o=12
        else:
            o=int(s[1])-2
        return f*13+o
    ret=[]
    cards_list=cards_str.split("_")
    for s in cards_list:
        ret.append(get_indexed_num(s))
    return ret

@click.command()
@click.option('--h1',  prompt='Cards including board and hand of player 1.', help='Cards including board and hand of player 1. ex:"!J_@K_#A_$T_!7"')
@click.option('--h2',  prompt='Cards including board and hand of player 2.', help='Cards including board and hand of player 2. ex:"!J_@K_#A_$T_!7"')
def main(h1,h2):
    ''' We denote "!" as club, "@" as diamond, "#" as heart, "$" as spade and use "_" as delimiter '''
    print('--Win rate calculator')
    i1=get_indexed_array(h1)
    i2=get_indexed_array(h2)

    card_num=len(i1)
    ret_num=3
    lib.checkWinRate.restype = ctypes.POINTER(ctypes.c_double * ret_num)
    lib.checkWinRate.argtypes = [(ctypes.c_double*ret_num), (ctypes.c_int*card_num), (ctypes.c_int*card_num), ctypes.c_int]

    time0= time()
    for i in range(1):
        ret=(ctypes.c_double*ret_num)(*[0.0,0.0,0.0])
        p=lib.checkWinRate(ret,(ctypes.c_int*card_num)(*i1), (ctypes.c_int*card_num)(*i2), card_num)
    time1= time()
    print("Using time: ", time1-time0)
    for i in p.contents: print(i)

if __name__ == "__main__":
    main()
