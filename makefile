default:
	g++ main.cpp ./src/* -I./include/ -I./include/glm-master -std=c++11 -o a.out -lSDL2 -ldl