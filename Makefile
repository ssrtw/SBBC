CC=g++
CFLAGS=-std=c++11 -ggdb -O3
OBJS=feistel.o
all: main

%.o: %.cpp
    # -c是不做link
	@echo "Building file: $<"
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJS)
    # 這裡不能加-c，不然不會幫我link feistel.o
	$(CC) $(CFLAGS) -o $@.exe $@.cpp $(OBJS)