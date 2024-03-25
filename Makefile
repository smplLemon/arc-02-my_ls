CC = gcc 
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
TARGET = my_ls
OBJ = my_ls.o 
SRC = my_ls.c 

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	rm -f *.o 