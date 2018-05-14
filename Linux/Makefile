all:a.out clean

a.out:main.o map.o
	g++ -o a.out main.o map.o -lpthread 
main.o:main.cpp
	g++ -c main.cpp
map.o:map.cpp
	g++ -c map.cpp  
clean:
	rm -rf *.o	
