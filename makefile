all: servidor.exe cliente.exe

servidor.exe: servidor.c
	x86_64-w64-mingw32-gcc servidor.c -o servidor.exe -g -lws2_32

cliente.exe: cliente.c
	x86_64-w64-mingw32-gcc cliente.c -o cliente.exe -g -lws2_32
