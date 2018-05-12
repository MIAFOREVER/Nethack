# Report
##  代码运行方法
### 依赖的第三方库
这次实验使用了``<windows.h>``和``<conio.h>``两个外部库</br>
### 如何编译
由于使用的IDE是Windows下的 VS2017 因此只能给出.sln工程文件用于编译,但为了方便起见,同时也会给出二进制文件.</br>
文件格式为:</br>
头文件:`Map.h`</br>
源文件:`Map.cpp`</br>
主文件`main.cpp`</br>
### 如何运行
直接执行`Nethack.exe`
## 操作方法
README.md里面有详细的解释
## 设计思路
### 如何封装对象
1.所有的代码都封装在Map类中,其中所有使用的数据都被声明为`private:`</br>类中的函数都以`private:`的形式声明</br>
`run()`声明为`public`</br>
2.大量使用宏定义简化编码流程
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
并且使用者可以自行更改其中的数值,进行难度的调整,以上参数只是默认的参数表</br>
3.代码地图采取生成房间->路径->墙壁->怪物->道具->人物->传送门(或项链)的顺序
```
    produceMainMap();
	produceLink();
	produceBlock();
	produceMonster();
	produceProp();
	produceActor();
	if (layer < LAYER)
		produceTranport();
	else
		produceNecklace();
```
4.碰撞事件单独成立一个函数实现`hit(int x,int y)`以简化编码量
### 运算符重载
```
void Map::operator+(int i)
```
用来增加一个monster
## 拓展点
1.使用了战争迷雾,曼哈顿距离小于`WARFOG`可以显示出来,走过的路会直接显示</br>
2.添加了层数,并且层数可以人为调整,定义在``#define LAYER 5``
## 改进空间
1.可以添加联机功能,进行多人在线联机</br>
2.添加商店,`Money`可以用来买东西</br>
3.设置血瓶,用来回复HP</br>
