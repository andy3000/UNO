a.out: main.o stringLibrary.o classes.o listP.o queueP.o StackP.o
	g++ StackP.o queueP.o listP.o stringLibrary.o classes.o main.o
	
main.o: StackP.cpp StackP.h queueP.cpp queueP.h listP.cpp listP.h stringLibrary.cpp stringLibrary.h classes.cpp classes.h main.cpp
	g++ -c main.cpp stringLibrary.cpp classes.cpp listP.cpp StackP.cpp queueP.cpp
	
stringLibrary.o: stringLibrary.cpp stringLibrary.h
	g++ -c stringLibrary.cpp
	
classes.o: classes.cpp classes.h
	g++ -c classes.cpp

listP.o: listP.cpp listP.h
	g++ -c listP.cpp

queueP.o: queueP.cpp queueP.h
	g++ -c queueP.cpp

StackP.o: StackP.cpp StackP.h
	g++ -c StackP.cpp
	
clean:
	rm a.out StackP.o queueP.o listP.o stringLibrary.o classes.o main.o
