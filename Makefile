# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asanni <asanni@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 16:50:05 by asanni            #+#    #+#              #
#    Updated: 2024/03/09 15:38:36 by asanni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#--------------FLAGS----------------------------#
CFLAGS = -Wall -Werror -Wextra -g3
#--------------PATHS----------------------------#

OBJFOLDER = objs/
SOURCES = sources/

P_LIBFT = libft/
LIBFT = $(P_LIBFT)libft.a
LINCLUDES = -L./libft -lft
RL = readline
#--------------FILES----------------------------#
SRC = sources/main.c \
sources/get_path.c \
sources/input_verif.c \
sources/error_functions.c\
sources/adjust_spaces.c\
sources/normalize_input.c\
sources/make_token.c\
sources/make_cmds.c\
sources/make_cmds_utils.c\
sources/delete_later.c\
sources/free_functions.c\
sources/pipes.c\
sources/heredoc_init.c\
sources/heredoc_utils.c\
sources/heredoc_new_file.c\
sources/signal.c\
sources/make_env_list.c\
sources/expand_var_utils.c\
sources/expand_var.c\


#--------------RULES----------------------------#

OBJFILES = $(subst $(SOURCES),$(OBJFOLDER),$(SRC:.c=.o))

all: comp_lib $(OBJFOLDER) $(NAME)

v: all
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --trace-children-skip='*/bin/*,*/sbin/*' --keep-debuginfo=yes \
	--suppressions=leak_readline --track-fds=yes -s ./$(NAME)

comp_lib:
	@$(MAKE) -sC $(P_LIBFT)

$(OBJFOLDER):
	@mkdir $(OBJFOLDER)

$(NAME): $(OBJFILES)
	$(CC) $(OBJFILES) $(H_LIB) $(LIBFT) $(LINCLUDES) $(CFLAGS) -o $(NAME) -g -l $(RL)

$(OBJFOLDER)%.o : $(SOURCES)%.c
	cc $(CFLAGS) -c $< -o $@ -g 

#----------------CLEAN--------------------------#

clean:
	rm -f $(OBJFILES) -r $(OBJFOLDER)
	@make clean -C libft

fclean: clean
	rm -f $(NAME)
	@make fclean -C libft

re: fclean all
.PHONY: all clean fclean re
