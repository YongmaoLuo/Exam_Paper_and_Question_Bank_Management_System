main: main.o mainwindow.o
	g++ -o main main.o mainwindow.o
main.o: main.cpp mainwindow.h
	g++ -c main.cpp
mainwindow.o: mainwindow.cpp mainwindow.h
	g++ -c mainwindow.cpp