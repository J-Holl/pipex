NAME = pipex

# Compile
CC = clang
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
INC = -I$(INC_DIR)
HEADER = $(INC_DIR)/pipex.h

# Location
SRC_DIR = src
INC_DIR = inc

# Source files
MAIN = pipex.c access_command.c 
INIT = init.c 
EXIT = exit_error.c
UTILS = ft_split.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_substr.c free.c \
		ft_strlcat.c ft_strlcpy.c ft_putstr_fd.c
SRC = $(addprefix src/, $(MAIN)) \
	  $(addprefix src/misc/, $(MISC)) \
	  $(addprefix src/init/, $(INIT)) \
	  $(addprefix src/utils/, $(UTILS)) \
	  $(addprefix src/exit/, $(EXIT)) 

# Object files
OBJ = $(SRC:.c=.o)

# Patern rule 
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c ${HEADER}
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
