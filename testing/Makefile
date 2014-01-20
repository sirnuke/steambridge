CXX = clang++
cxflags = -Wextra -Wall -pipe -m32 -I../steam -g
ldflags = -m32 -L../steam -lsteam_api -g
exe = testing


.PHONY : all clean

all : $(exe)

$(exe) : steam.o
	$(CXX) -o $(exe) $(ldflags) steam.o

steam.o : steam.cpp steam.h
	$(CXX) -c steam.cpp $(cxflags)

clean :
	rm -f $(exe) *.o
