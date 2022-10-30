alamat:	alamat.o archive.o prompt.o menu.o
	g++ -W -o alamat alamat.o archive.o prompt.o menu.o

alamat.o:	alamat.cpp
	g++ -W -c  alamat.cpp

archive.o:	archive.cpp archive.h 
	g++ -W -c archive.cpp archive.h

prompt.o:	prompt.cpp prompt.h
	g++ -W -c prompt.cpp prompt.h

menu.o:	menu.cpp menu.h
	g++ -W -c menu.cpp menu.h
