# Nethack a simple game

## How to play?
1.The Nethack control is ver easy.We use </br>`w`means up
</br>`a`means down
</br>`s`means left
</br>`d`means right
</br>`q`means left & up
</br>`e`means right & up
</br>`z`means left & down
</br>`c`means right & down
That is essential operation</br>


## What is the charactor means?
`.`is floor in the room</br>
`#`is road used to link the room</br>
`|`&&`-`is the wall,you can't cross thw wall</br>
`M`is monster,and its HP is 100 attack is 30</br>
You will kill him if your attack value is higher than his HP</br>
`E`is your prop,you will increase your attack value randomly when you eat the `E`</br>
`S`is the necklace,our main goal is to achieve it


## Detail and advance option
1.The game map is randomly,and the road is randomly too</br>
2.If you find some mistake in it,don't be worry and the author will be debug in the next version</br>
3.The map have `war fog`,that means you can only see a part of the map</br>
4.high-level option can be changed in map.h
in class map</br>
```
class Map
{
#define MAX_X 100
#define MAX_Y 25
#define MAX_R 8
#define MIN_R 4
#define MAPNUM 8
#define MONSTERNUM 10
#define PROPNUM 5
#define WARFOG 10
...
}
```
you can change parameter in `#define` </br>

`eg:`if you want a large map,you can change`#define MAX_X 100` to `#define MAX_X 120` that will increase the map areo


## Version V 1.0
## Author Zhang Hao
