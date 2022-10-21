# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dtran <dtran@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2022/08/31 18:10:25 by dtran         #+#    #+#                  #
#    Updated: 2022/10/21 20:55:26 by dtran         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#===============================================================================: Filename
NAME		= minishell

#===============================================================================: Source to object conversion location
OBJS		= $(subst src, objs, $(SRCS:.c=.o))

#===============================================================================: Color codes
GREEN		= \033[1;32m
RED			= \033[1;31m
BLUE		= \033[1;34m
MAGENTA		= \033[1;35m
RESET		= \033[0m

#===============================================================================: Include files
MINISHELL	= include
LIBFT		= include/libft
GNL			= include/get_next_line

#===============================================================================: Compile variables
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
READLINE	= -lreadline
BREW_DIR	= $(shell brew --prefix)
LIB_READLINE	= $(BREW_DIR)/opt/readline/lib
INCLUDE_READLINE = -I $(BREW_DIR)/opt/readline/include
READLINE_DIRS = -L $(LIB_READLINE) $(READLINE)
RM			= rm -rf
MKDIR		= mkdir -p objs
HEADERS		= -I $(LIBFT) -I $(MINISHELL) -I $(GNL)

#===============================================================================: Sourcefiles
SRCS		= $(addprefix src/, $(addsuffix .c, \
				env \
				signal \
				lexer \
				expand \
				parser \
				pre_parser \
				shelldata \
				heredoc \
				unset \
				utils \
				utils2 \
				builtin \
				lst_utils \
				main))

#===============================================================================: Make commands
all: message libft gnl $(NAME)

#===============================================================================: Main compile
$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) $(LIBFT)/libft.a $(GNL)/get_next_line.a $(READLINE_DIRS) $(READLINE) -o $(NAME)
	@printf "$(GREEN)✅Executable \"$(NAME)\" created!$(RESET)\n\n"

#===============================================================================: C file compile
objs/%.o: src/%.c
	@$(MKDIR)
	@$(CC) $(CFLAGS) $(INCLUDE_READLINE) -o $@ -c $< $(HEADERS)
ifeq ($(DB),1)
	@printf "$(GREEN)\r🔨Compiling: $(MAGENTA)$(notdir $<)$(GREEN)\r\e[35C[OK]\n$(RESET)"
endif

#===============================================================================: Executable run command
run: all
	@./$(NAME)

#===============================================================================: Build messages
message:
	@printf "$(MAGENTA)🔨Building \"$(NAME)\"\n$(RESET)\n"

#===============================================================================: Libft Compile
libft:
	@$(MAKE) -C $(LIBFT)

#===============================================================================: GNL Compile
gnl:
	@$(MAKE) -C $(GNL)

#===============================================================================: Remove all object files
clean:
	@$(RM) objs/
	@printf "$(RED)🧹Removed objects for \"$(NAME)\"!$(RESET)\n"

#===============================================================================: Remove all object files and executable
fclean:
	@$(RM) objs/
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(GNL) fclean
	@printf "$(RED)🧹Removed objects for \"$(NAME)\"!$(RESET)\n"
	@printf "$(RED)🧹Removed \"$(NAME)\"!$(RESET)\n"

#===============================================================================: Remove all object files, executable and remake executable
re: fclean all

#===============================================================================: To not confuse make
.PHONY: all, clean, fclean, re, message, run, libft, gnl