alamat:	alamat.o archive.o prompt.o menu.o
	g++ -W -o alamat alamat.o archive.o prompt.o menu.o

alamat.o:	alamat.cc
	g++ -W -c  alamat.cc

archive.o:	archive.cpp archive.hh 
	g++ -W -c archive.cpp archive.hh

prompt.o:	prompt.cpp prompt.h
	g++ -W -c prompt.cpp prompt.h

menu.o:	menu.cpp menu.h
	g++ -W -c menu.cpp menu.h
