ROOT_PATH=$(shell pwd)
DATA_POOL_PATH=$(ROOT_PATH)/../data_pool
BIN=udp_server
CC=g++
SRC=$(shell ls *.cpp)
SRC+=$(shell cd $(DATA_POOL_PATH); ls *.cpp)
OBJ=$(SRC:.cpp=.o)

LIB=-lpthread

$(BIN):$(OBJ)
	$(CC) -o $@ $^ $(LIB) 
%.o:$(DATA_POOL_PATH)/%.cpp 
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
