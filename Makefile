tree : tree.o dirtree.o bitmask.o
	g++ tree.o dirtree.o bitmask.o \
		-o tree

tree.o : tree.cpp bitmask.h dirtree.h
	g++ -c tree.cpp

dirtree.o : dirtree.cpp dirtree.h
	g++ -c dirtree.cpp

bitmask.o : bitmask.cpp bitmask.h
	g++ -c bitmask.cpp

clean :
	rm tree tree.o dirtree.o bitmask.o

install :
	install tree /usr/bin

uninstall :
	rm /usr/bin/tree


