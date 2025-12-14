CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -lm
TARGET = matrix_calc
OBJS = main.o matrix.o determinant.o minors.o inverse.o utils.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

main.o: main.c matrix.h determinant.h minors.h inverse.h utils.h
	$(CC) $(CFLAGS) -c main.c

matrix.o: matrix.c matrix.h utils.h
	$(CC) $(CFLAGS) -c matrix.c

determinant.o: determinant.c determinant.h matrix.h utils.h
	$(CC) $(CFLAGS) -c determinant.c

minors.o: minors.c minors.h matrix.h determinant.h utils.h
	$(CC) $(CFLAGS) -c minors.c

inverse.o: inverse.c inverse.h matrix.h determinant.h utils.h
	$(CC) $(CFLAGS) -c inverse.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run