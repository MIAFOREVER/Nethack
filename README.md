# Nethack (a simple game)

## Description
A hero wants to a bravery journey

## Install
If you are Linux user:</br>
```
cd Linux
make 
./a.out
```
make sure ur console is full screen</br>
And if you are Windows User,please use VS to build it or </br>
run `/Windows/Release/Nethack.exe`

## How to play?
1.The Nethack control is easy.We use 
</br>`w`means up
</br>`a`means down
</br>`s`means left
</br>`d`means right
</br>`q`means left & up
</br>`e`means right & up
</br>`z`means left & down
</br>`c`means right & down
</br>Those are essential operations</br>


## What is the symbol means?
`.`is floor in the room</br>
`#`is road used to link the room</br>
`|`&&`-`is the wall,you can't cross the wall</br>
`M`is monster,and its HP is 100,and attack is 30</br>
You will kill him if your attack is higher than its HP</br>
`E`is your prop,you will increase your attack value randomly when you eat the `E`</br>
`T`is a transport machine which transport you to the next level</br>
`S`is the necklace,our main goal is to achieve it


## Detail and advance option
1.The game map is random,and the road is random too</br>
2.If you find some mistakes in it,don't be worried and the author will be debug in the next version</br>
3.The map have `war fog` mode,that means you can only see a part of the map</br>
4.If your HP is 100 and attack is 60,and monster HP is 100 and monster attack is 30,when you hit him,your HP is becoming 70 and monster HP is becoming 40,if your attack is higher than monster HP you will not be hurt and monster will be killed</br>
5.high-level option can be changed in define.h</br>
```
  #define MAX_X 100   //the length of map_x
  #define MAX_Y 25    //the length of map_y
  #define MAX_R 8     //the size of room_max
  #define MIN_R 4     //th size of room_min
  #define MAPNUM 8    //the size of room number
  #define MONSTERNUM 10  //monster number
  #define PROPNUM 5      //prop number
  #define WARFOG 10      //size of war fog
  #define LAYER 5        //the layer
```
you can change parameters in `#define` </br>

`eg:`if you want a large map,you can change`#define MAX_X 100` to `#define MAX_X 120` that will increase the map aera


## Version V 1.1
## Author Zhang Hao
