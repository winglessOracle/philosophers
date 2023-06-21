# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: carlo <carlo@student.42.fr>                  +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/10 09:28:26 by cwesseli      #+#    #+#                  #
#    Updated: 2023/06/21 14:28:56 by wingessorac   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#//= Colors =//#
BOLD	:=	\033[1m
GREEN	:=	\033[32;1m
BLUE	:=	\033[34;1m
YELLOW	:=	\033[33;1m
RESET	:=	\033[0m

#//= Variables = //#
TARGET		 =	philo
CC			 ?=	clang
CFLAGS		 =	-Wall -Wextra -Werror -pthread

#//= Locations =//#
HEADERS		=	-I ./include
OBJ_FILES	=	$(addprefix obj/, philosophers.o checks.o init.o utils.o thread_ops.o atol.o)

#//= Modifiable =//#
all: $(TARGET)
	
$(TARGET): $(OBJ_FILES)
	@$(CC) $(OBJ_FILES) -o $(TARGET) $(CFLAGS)

$(OBJ_FILES): obj/%.o: src/%.c 
	@mkdir -p $(dir $@)
	@echo -e "$(GREEN)Compiling Philosophers:$(RESET) $(notdir $<)"
	@$(CC) -c $(CFLAGS) $(HEADERS) -o $@ $<

clean:
	@echo -e "$(BLUE)Remoning OBJ files$(RESET)"
	@rm -rf obj/

fclean: clean
	@echo -e "$(BLUE)Removing Target$(RESET)"
	@rm -rf $(TARGET)

debug: CFLAGS = -Wall -Wextra
debug: re
	@echo -e "$(YELLOW)\nCOMPILED IN DEBUG MODE\n$(RESET)"

thread: CFLAGS += -fsanitize=thread -g
thread: re
	@echo -e "$(YELLOW)\nCOMPILED WITH THREAD SANITIZER\n$(RESET)"

address: CFLAGS += -fsanitize=address -g
address: re
	@echo -e "$(YELLOW)\nCOMPILED WITH ADDRESS SANITIZER\n$(RESET)"

re: fclean all

.PHONY:	all clean fclean re debug thread address
