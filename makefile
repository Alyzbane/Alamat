alamat:	alamat.o archive.o prompt.o menu.o login.o
	g++ -Wall -o alamat alamat.o archive.o prompt.o menu.o login.o

alamat.o:	alamat.cpp
	g++ -W -c  alamat.cpp

archive.o:	archive.cpp archive.h 
	g++ -W -c archive.cpp archive.h 

prompt.o:	prompt.cpp prompt.h
	g++ -W -c prompt.cpp prompt.h

menu.o:	menu.cpp menu.h
	g++ -W -c menu.cpp menu.h

login.o: login.cpp login.h
	g++ -W -c login.cpp login.h
