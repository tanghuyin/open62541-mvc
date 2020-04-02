server.exe: server.o myNS.o open62541.o utils.o hashmap.o
	gcc -std=c99 -o server.exe server.o myNS.o open62541.o utils.o hashmap.o
server.o: server.c myNS.o open62541.o utils.o hashmap.o
	gcc -std=c99 -c server.c -o server.o hashmap.o
myNS.o: myNS.c open62541.o myNS.h
	gcc -std=c99 -c myNS.c -o myNS.o
utils.o: open62541.o utils.c utils.h
	gcc -std=c99 -c utils.c -o utils.o
open62541.o: open62541.c
	gcc -std=c99 -c open62541.c -o open62541.o