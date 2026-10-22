CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c99 -fstack-protector -Iinlcude

SRC =	code/main.c \
		code/create_form.c \
		code/edit_form.c \
		code/view.c \
		code/quit.c \
		code/save.c \
		code/load.c \

OBJ_DIR = bin
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

NAME = projet

vpath %.c code

build: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)

.PHONY: build clean