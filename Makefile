CC = g++
CFLAGS = -Wall -Werror -std=c++11

INCLUDE_DIR = ./include
SRC_DIR = ./src
BIN_DIR = ./bin
LOG_DIR = ./logs
DATA_DIR = ./data

TARGET = $(BIN_DIR)/simulation

OBJS = $(SRC_DIR)/main.o $(SRC_DIR)/LoadBalancer.o $(SRC_DIR)/Request.o $(SRC_DIR)/RequestQueue.o $(SRC_DIR)/WebServer.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(SRC_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/LoadBalancer.h $(INCLUDE_DIR)/Request.h $(INCLUDE_DIR)/RequestQueue.h $(INCLUDE_DIR)/WebServer.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -I$(INCLUDE_DIR) -o $(SRC_DIR)/main.o

$(SRC_DIR)/LoadBalancer.o: $(SRC_DIR)/LoadBalancer.cpp $(INCLUDE_DIR)/LoadBalancer.h $(INCLUDE_DIR)/RequestQueue.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/LoadBalancer.cpp -I$(INCLUDE_DIR) -o $(SRC_DIR)/LoadBalancer.o

$(SRC_DIR)/Request.o: $(SRC_DIR)/Request.cpp $(INCLUDE_DIR)/Request.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Request.cpp -I$(INCLUDE_DIR) -o $(SRC_DIR)/Request.o

$(SRC_DIR)/RequestQueue.o: $(SRC_DIR)/RequestQueue.cpp $(INCLUDE_DIR)/RequestQueue.h $(INCLUDE_DIR)/Request.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/RequestQueue.cpp -I$(INCLUDE_DIR) -o $(SRC_DIR)/RequestQueue.o

$(SRC_DIR)/WebServer.o: $(SRC_DIR)/WebServer.cpp $(INCLUDE_DIR)/WebServer.h $(INCLUDE_DIR)/Request.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/WebServer.cpp -I$(INCLUDE_DIR) -o $(SRC_DIR)/WebServer.o

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

run: all
	@./$(TARGET); \
	id=$$(ls $(LOG_DIR)/simulation_log_*.txt | tail -n 1 | sed 's/.*simulation_log_\(.*\)\.txt/\1/'); \
	echo "Simulation completed with ID: $$id"

start: all
	@echo "10\n10000" | ./$(TARGET); \
	id=$$(ls $(LOG_DIR)/simulation_log_*.txt | tail -n 1 | sed 's/.*simulation_log_\(.*\)\.txt/\1/'); \
	echo "Simulation completed with ID: $$id"

.PHONY: docs
docs:
	rm -rf ./docs/html ./docs/latex
	doxygen Doxyfile