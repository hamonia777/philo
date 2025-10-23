NAME		= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=thread 
AR		= ar rcs
RM		= rm -f
TSAN_LIB = /usr/lib/x86_64-linux-gnu/libtsan.so.0
SRCS	= main.c \
			philo_util.c \
			philo_init.c \
			philo_action.c \
			philo_life.c \
			philo_monitor.c

OBJS	= $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -I.

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : clean all

.PHONY : all clean fclean re