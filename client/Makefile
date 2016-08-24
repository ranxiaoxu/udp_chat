ROOT_PATH=$(shell pwd)
COMM_PATH=$(ROOT_PATH)/../comm
JSON_PATH=$(ROOT_PATH)/../lib
WINDOW_PATH=$(ROOT_PATH)/../window

LIB_PATH=-L$(JSON_PATH)/lib
LIB=-ljsonlib -lncurses -lpthread 

BIN=udp_client
CC=g++

SRC=$(shell ls *.cpp)
SRC+=$(shell cd $(COMM_PATH); ls *.cpp)
SRC+=$(shell cd $(WINDOW_PATH); ls *.cpp)
OBJ=$(SRC:.cpp=.o)

$(BIN):$(OBJ)
	$(CC) -o $@ $^ $(LIB) $(LIB_PATH) 
%.o:$(COMM_PATH)/%.cpp
	$(CC) -c $< 
%.o:$(WINDOW_PATH)/%.cpp
	$(CC) -c $< 
%.o:%.cpp
	$(CC) -c $<

.PHONY:debug
debug:
	echo $(OBJ)
	echo $(SRC)

.PHONY:clean
clean:
	rm -f $(BIN) *.o
