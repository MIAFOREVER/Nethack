all:a.out clean

a.out:main.o Map.o Actor.o Monster.o Prop.o Transport.o Game.o data.o
	g++ -o a.out main.o Map.o Actor.o Monster.o Prop.o Transport.o Game.o data.o -lpthread 
main.o:src/main.cpp inc/Game.h 
	g++ -c src/main.cpp -I inc
Map.o:src/Map.cpp 
	g++ -c src/Map.cpp -I inc
Actor.o:src/Actor.cpp 
	g++ -c src/Actor.cpp -I inc
Monster.o:src/Monster.cpp 
	g++ -c src/Monster.cpp -I inc
Prop.o:src/Prop.cpp 
	g++ -c src/Prop.cpp -I inc
Transport.o:src/Transport.cpp 
	g++ -c src/Transport.cpp -I inc
Game.o:src/Game.cpp 
	g++ -c src/Game.cpp -I inc
data.o:src/data.cpp
	g++ -c src/data.cpp -I inc
clean:
	rm -rf *.o	
