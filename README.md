# Texas Hold'em Win Rate Calculator
This project simply provide a C++ based win rate calculator with python interface, which provide both fast speed and ease of feature development.

# Requirements
gcc version 9.4.0
click==7.1.2
numpy==1.24.1
pkg_resources==0.0.0
python==3.9

# Setup
Locat to reoot and compile shared file:
```
cd ./Poker
g++ -o ./src/libCard.so -shared -fPIC ./src/C_card_lib.cpp
```
Install packages
```
pip install -r ./requirements.txt
```

# Usage
We denote "!" as club, "@" as diamond, "#" as heart, "$" as spade, "T" as ten and use
"_" as delimiter. You can use the following command to calculate the win rate between "club J and dimond K" and "club 3 and club 4" with board "heart A, spade 10 and club 7", which is 0.72 for hand 1, 0.26 for hand 2 and 0.01 for draw.
Command:
```
python ./src/Py_card_main.py --h1='!J_@K_#A_$T_!7' --h2='!3_!4_#A_$T_!7'
```
Output:
```
--Win rate calculator
Using time:  0.14743423461914062
0.7287
0.2614
0.0099
```
