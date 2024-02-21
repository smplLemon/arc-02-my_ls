FLAGS = -g3 -fsanitize=address -Wall -Wextra -Werror
G = gcc
TARGET = my_ls
SRC = my_ls.c

$(TARGET) : $(SRC)
	$(G) $(FLAGS) -o $(TARGET) $(SRC)

.PHONY : fclean
fclean :
	rm -rf $(TARGET)