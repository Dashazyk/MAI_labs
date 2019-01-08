CC = g++
CPPFLAGS += --std=c++14
BLD = ./build

all: $(BLD) main

$(BLD): 
	mkdir -p $(BLD)

main: $(BLD)/Main.o $(BLD)/TList.o $(BLD)/TListItem.o $(BLD)/Triangle.o $(BLD)/Quadrate.o $(BLD)/Rectangle.o
	$(CC) $(CPPFLAGS) $(BLD)/*.o -o main

$(BLD)/Main.o: Main.cpp
	$(CC) $(CPPFLAGS) -c Main.cpp -o $(BLD)/Main.o

$(BLD)/TList.o: TList.cpp
	$(CC) $(CPPFLAGS) -c TList.cpp -o $(BLD)/TList.o

$(BLD)/TListItem.o: TListItem.cpp
	$(CC) $(CPPFLAGS) -c TListItem.cpp -o $(BLD)/TListItem.o

$(BLD)/Triangle.o: Triangle.cpp
	$(CC) $(CPPFLAGS) -c Triangle.cpp -o $(BLD)/Triangle.o

$(BLD)/Quadrate.o: Quadrate.cpp
	$(CC) $(CPPFLAGS) -c Quadrate.cpp -o $(BLD)/Quadrate.o
	
$(BLD)/Rectangle.o: Rectangle.cpp
	$(CC) $(CPPFLAGS) -c Rectangle.cpp -o $(BLD)/Rectangle.o

clean: 
	rm -f ./build/*.o
	rm -f main
