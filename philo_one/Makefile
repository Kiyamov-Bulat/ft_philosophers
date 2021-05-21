NAME		= philo_one
INC_DIR		= .
SRC_DIR		= .
CC			= gcc
UTILS_DIR	= ./utils
UTILS 		= destroy_threads.c error.c ft_bzero.c ft_calloc.c ft_isdigit.c \
				ft_isspace.c ft_strlen.c get_current_time_ms.c parse_args.c str_to_msec.c
SRCS		= $(addprefix $(UTILS_DIR)/, $(UTILS))
SRCS	    += init_forks.c init_philos.c pthread_locker.c print_philo_status.c \
				start_act.c wait_philo_death.c philo_is_dead.c
OBJS		= $(SRCS:.c=.o)
DEBUG		= -D DEBUG
DEPS		= philosophers.h
UTILS_DEPS	= $(UTILS_DIR)/utils.h
CFLAGS		= -Wall -Wextra -Werror -I$(INC_DIR) -I$(UTILS_DIR) -pthread
SMAKE		= make -s
AR			= ar rc
TMP_LIB		= libtemp.a

.PHONY:		all clean fclean re test

$(UTILS_DIR)/%.o:	$(UTILS_DIR)/%.c $(UTILS_DEPS)
					$(CC) $(CFLAGS) -c $< -o $@

$(SRC_DIR)/%.o:		$(SRC_DIR)/%.c $(DEPS)
					$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(TMP_LIB): $(OBJS)
			$(AR) $@ $?

$(NAME):	main.o $(TMP_LIB)
			$(CC) $(CFLAGS) $< -o $(NAME) $(TMP_LIB)

test:		CFLAGS += $(DEBUG)
test:		$(NAME)
			./$(NAME) 4 410 200 200

clean:
			rm -rf main.o
			rm -rf $(OBJS)
			rm -rf $(TMP_LIB) 

fclean:		clean
			rm -rf $(NAME)

re:			fclean all