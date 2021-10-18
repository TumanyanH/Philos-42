NAME = philo

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror
PS_FILES = main.c \
			utils/controls.c \
			utils/philo.c \
			utils/utils.c \
			utils/utils2.c
OBJS = ${PS_FILES:.c=.o}

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o ${NAME}

clean : 
	@$(RM) ${OBJS}

fclean : clean
	$(RM) ./$(NAME)

re : fclean all