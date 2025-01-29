OBJS = $(MAIN_DIR)/main.o $(RES_DIR)/resource.o
MAIN_DIR = ./main
RES_DIR = ./resource
CFLAGS = -lwinmm
CC = gcc

# 最终生成的可执行文件
all: 五子棋.exe

五子棋.exe: $(OBJS)
	$(CC) -o 五子棋.exe $(OBJS) $(CFLAGS)

$(MAIN_DIR)/main.o: $(MAIN_DIR)/main.c $(MAIN_DIR)/config.h
	$(CC) -c $(MAIN_DIR)/main.c  -o $(MAIN_DIR)/main.o

$(RES_DIR)/resource.o: $(RES_DIR)/resource.rc
	windres $(RES_DIR)/resource.rc -O coff -o $(RES_DIR)/resource.o

clean:
	del /Q /S *.o 五子棋.exe

# 2025.01.30 by Dettweiler Wong