CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC_DIR = src
OBJ_DIR = obj

all: $(OBJ_DIR) server client

server: $(OBJ_DIR)/server.o $(OBJ_DIR)/func.o
	$(CC) $(CFLAGS) -o server $(OBJ_DIR)/server.o $(OBJ_DIR)/func.o

client: $(OBJ_DIR)/client.o $(OBJ_DIR)/func.o
	$(CC) $(CFLAGS) -o client $(OBJ_DIR)/client.o $(OBJ_DIR)/func.o

$(OBJ_DIR)/server.o: $(SRC_DIR)/server.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/server.c -o $(OBJ_DIR)/server.o

$(OBJ_DIR)/client.o: $(SRC_DIR)/client.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/client.c -o $(OBJ_DIR)/client.o

$(OBJ_DIR)/func.o: $(SRC_DIR)/func.c $(SRC_DIR)/func.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/func.c -o $(OBJ_DIR)/func.o

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf server client $(OBJ_DIR)
