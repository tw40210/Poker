__author__ = 'xidui'
import ctypes
from time import time
so = ctypes.cdll.LoadLibrary
lib = so('./libCard.so')

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
    cards_list=cards_str.split()
    for s in cards_list:
        ret.append(get_indexed_num(s))
    return ret


# # passInt
# print('passInt')
# print(lib.passInt(100))
# print('--------------------')


# # passDouble
# print('passDouble')
# lib.passDouble.restype = ctypes.c_double
# print(str(lib.passDouble(ctypes.c_double(1.23))) + ' in python')
# print('--------------------')

# passDoubleArray
print('passDoubleArr')
a1="!A @A"
a2="@7 $3"
i1=get_indexed_array(a1)
i2=get_indexed_array(a2)

card_num=len(i1)
ret_num=3
lib.checkWinRate.restype = ctypes.POINTER(ctypes.c_double * ret_num)
lib.checkWinRate.argtypes = [(ctypes.c_double*ret_num), (ctypes.c_int*card_num), (ctypes.c_int*card_num), ctypes.c_int]

time0= time()
for i in range(10):
    ret=(ctypes.c_double*ret_num)(*[0.0,0.0,0.0])
    p=lib.checkWinRate(ret,(ctypes.c_int*card_num)(*i1), (ctypes.c_int*card_num)(*i2), card_num)
time1= time()
print("time: ", time1-time0)
for i in p.contents: print(i)
# print(p)
# print(str(lib.checkWinRate((ctypes.c_double*3)(*[0.0,0.0,0.0]),(ctypes.c_int*card_num)(*i1), (ctypes.c_int*card_num)(*i2), card_num)) + ' in python')
print('--------------------')
