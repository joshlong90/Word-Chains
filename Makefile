wordchains: wordchains.o queue.o stack.o Graph.o
	gcc -o wordchains wordchains.o Graph.o queue.o stack.o

wordchains.o : wordchains.c queue.h stack.h Graph.h
	gcc -Wall -Werror -c wordchains.c

queue.o : queue.c queue.h
	gcc -Wall -Werror -c queue.c

stack.o : stack.c stack.h
	gcc -Wall -Werror -c stack.c

Graph.o : Graph.c queue.h Graph.h
	gcc -Wall -Werror -c Graph.c

clean:
	rm -f wordchains wordchains.o queue.o Graph.o stack.o core