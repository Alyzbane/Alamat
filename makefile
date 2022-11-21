alamat:	alamat.o archive.o prompt.o menu.o login.o
	g++ -Wall -Wextra -static-libstdc++ -o alamat alamat.o archive.o prompt.o menu.o login.o entry.o user.o screen.o

alamat.o:	alamat.cpp
	g++ -Wall -Wextra -c  alamat.cpp

archive.o:	archive.cpp archive.h 
	g++ -Wall -Wextra -c archive.cpp archive.h 

prompt.o:	prompt.cpp prompt.h
	g++ -Wall -Wextra -c prompt.cpp prompt.h

menu.o:	menu.cpp menu.h
	g++ -Wall -Wextra -c menu.cpp menu.h

login.o: login.cpp login.h
	g++ -static-libstdc++ -Wall -Wextra -c login.cpp login.h

entry.o:	entry.cpp entry.h
	g++ -Wall -Wextra -c entry.cpp entry.h

user.o:	user.cpp user.h
	g++ -Wall -Wextra -static-libstdc++ -c user.cpp user.h
screen.o:	screen.cpp screen.h
	g++ -Wall -Wextra -c screen.cpp screen.h
