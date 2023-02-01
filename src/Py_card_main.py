__author__ = 'xidui'
import ctypes
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
a1="!T @K !7 !9 #K !K $K"
a2="@7 $7 #7 !9 !T !Q !K"
i1=get_indexed_array(a1)
i2=get_indexed_array(a2)
print(i1)

card_num=len(i1)
ret_num=3
lib.checkWinRate.restype = ctypes.POINTER(ctypes.c_double * ret_num)
lib.checkWinRate.argtypes = [(ctypes.c_double*ret_num), (ctypes.c_int*card_num), (ctypes.c_int*card_num), ctypes.c_int]
ret=(ctypes.c_double*ret_num)(*[2.0,0.0,0.0])
p=lib.checkWinRate(ret,(ctypes.c_int*card_num)(*i1), (ctypes.c_int*card_num)(*i2), card_num)
for i in p.contents: print(i)
# print(p)
# print(str(lib.checkWinRate((ctypes.c_double*3)(*[0.0,0.0,0.0]),(ctypes.c_int*card_num)(*i1), (ctypes.c_int*card_num)(*i2), card_num)) + ' in python')
print('--------------------')

# # passChar
# print('passChar')
# lib.passChar.restype = ctypes.c_char
# print(str(lib.passChar(ctypes.c_char(65))) + ' in python') # 'A'
# print(str(lib.passChar(ctypes.c_char(b'A'))) + ' in python') # 'A'
# print('--------------------')

# # passString
# print('passString')
# lib.passString.restype = ctypes.c_char_p
# print(str(lib.passString(ctypes.c_char_p(b'abcde'))) + ' in python') # 这里一定要加b
# print('--------------------')

# # passStruct
# print('passStruct')
# class Struct(ctypes.Structure):
#     _fields_ = [('name', ctypes.c_char_p),
#                 ('age', ctypes.c_int),
#                 ('score', ctypes.c_int * 3)]
# lib.passStruct.restype = Struct
# array = [1, 2, 3]
# st = lib.passStruct(Struct(b'xidui', 10, (ctypes.c_int * 3)(*array)))
# # p = lib.passStruct(Struct(b'xidui', 10, (ctypes.c_int * 3)(1, 2, 3)))
# print(str(st.name) + ' ' + str(st.age) + ' ' + str(st.score[2]) + ' in python')
# print('--------------------')

# # passStructPointer
# print('passStructPointer')
# lib.passStructPtr.restype = ctypes.POINTER(Struct)
# lib.passStructPtr.argtypes = [ctypes.POINTER(Struct)] # 这行不加，程序会宕
# p = lib.passStructPtr(Struct(b'xidui', 10, (ctypes.c_int * 3)(*array)))
# print(str(p.contents.name) + ' ' + str(p.contents.age) + ' ' + str(p.contents.score[2]) + ' in python')
# print('--------------------')

# # passStructArray
# print('passStructArray')
# lib.passStructArray.restype = ctypes.POINTER(Struct)
# lib.passStructArray.argtypes = [ctypes.ARRAY(Struct, 2), ctypes.c_int]
# array = [Struct(b'xidui1', 10, (ctypes.c_int * 3)(1, 2, 3)),
#     Struct(b'xidui2', 10, (ctypes.c_int * 3)(1, 2, 3))]
# p = lib.passStructArray(ctypes.ARRAY(Struct, 2)(*array), 2)
# print(str(p.contents.name) + ' ' + str(p.contents.age) + ' ' + str(p.contents.score[2]) + ' in python')
# print('--------------------')