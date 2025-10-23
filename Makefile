NAME		= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rcs
RM		= rm -f
SRCS	= main.c \
			philo_util.c \
			philo_util2.c \
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