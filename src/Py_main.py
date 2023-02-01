__author__ = 'xidui'

import ctypes
so = ctypes.cdll.LoadLibrary
lib = so('./libTest.so')

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
dArr=[1.2,5.3,5.3,5.3,5.3]
lib.passDoubleArr.restype = ctypes.c_double
# lib.passDoubleArr.argtypes = [(ctypes.c_double*5)]
print(str(lib.passDoubleArr((ctypes.c_double*5)(*dArr))) + ' in python')
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