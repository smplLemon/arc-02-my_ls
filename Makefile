# Target executable
my_ls: obj/main.o obj/ls.o obj/utils.o
	gcc -Wall -Wextra -Werror -o my_ls obj/main.o obj/ls.o obj/utils.o

# Main program object file
obj/main.o: src/main.c header/ls.h header/utils.h
	gcc -Wall -Wextra -Werror -c -Iheader src/main.c -o obj/main.o

# ls functions object file
obj/ls.o: src/ls.c header/ls.h header/utils.h
	gcc -Wall -Wextra -Werror -c -Iheader src/ls.c -o obj/ls.o

# Utility functions object file
obj/utils.o: src/utils.c header/utils.h 
	gcc -Wall -Wextra -Werror -c -Iheader src/utils.c -o obj/utils.o

# Clean the compiled object files and executable
clean:
	rm -f ./obj/*.o my_ls

fclean: clean
	rm -f ./obj/*.o my_ls

re: fclean ./obj/*.o my_ls