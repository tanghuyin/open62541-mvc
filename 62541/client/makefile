client.exe: client.o open62541.o Classic6dofKine.o
	gcc -std=c99 -o client.exe -lpthread client.o open62541.o Classic6dofKine.o
client.o: client.c open62541.o Classic6dofKine.o
	gcc -std=c99 -c client.c -lpthread -o client.o
open62541.o: open62541.c
	gcc -std=c99 -c open62541.c -o open62541.o