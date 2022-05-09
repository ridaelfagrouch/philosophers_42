CFILES = philo_bonus.c atoi.c check_digit.c \
	creat_list.c processing.c routine.c time_print.c

OFILES = ${CFILES:.c=.o}

CC = gcc
W = -Wall -Werror -Wextra -pthread
INC = philo_bonus.h
NAME = philosopher

YELLOW=\033[1;33m
NC=\033[0m
GREEN=\033[0;32m
RED=\033[0;31m
DARKVIOLET=\033[1;5;1;36m

define HEADER_M

	██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗         ██████╗ 
	██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗        ██╔══██╗
	██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝        ██████╔╝
	██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗        ██╔══██╗
	██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████╗██████╔╝
	╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚═════╝ ${YELLOW}by rel-fagr${NC}

endef
export HEADER_M

.PHONY: all clean fclean re print_header_m

all : ${NAME}

${NAME} : print_header_b ${OFILES}
	@$(CC) $(OFILES) $(W) -o $(NAME)
	@echo "${YELLOW}$(NAME) created 👍 ${NC}"

print_header_b:
	@echo " ${DARKVIOLET}$$HEADER_M${NC} "

%.o:%.c ${INC}
	@${CC} ${W} -o $@ -c $<
	@echo "${GREEN}$@ created ✅${NC}"

clean:
	@rm -f *.o

fclean : clean
	@rm -f ${NAME}

re : fclean all