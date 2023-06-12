NAME	=	philo

SRC	=	action.c init.c main.c time.c philosophers_utils.c routine.c

OBJS	=	$(SRC:%.c=%.o)

CC	=	gcc -pthread
CFLAGS	=	-Wall -Wextra -Werror
RM	=	rm -rf

all: $(NAME)

$(NAME): $(OBJS) ./philosophers.h
		@echo "\033[0;33m\nCOMPILING PHILOSOPHERS......\n"
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "\033[1;32m\nPHILOSOPERS CREATED\n"

clean:
		@echo "\033[1;31m\nDELETING PHILOSOPHERS files......\n"
		@$(RM) $(OBJS)
		@echo "\033[1;32m\nDONE\n"

fclean:	clean
		@echo "\033[1;31m\nDELETING PHILOSOPHERS EXECUTABLE...\n"
		@$(RM) $(NAME)
		@echo "\033[1;32mDONE\n"

re: fclean all
