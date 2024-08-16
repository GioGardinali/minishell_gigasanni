NAME = libft.a

CFLAGS = -Wall -Werror -Wextra -g3 -I ./

OBJFOLDER =	objs/

SRC = ft_atoi.c \
 ft_atol.c \
 ft_bzero.c \
 ft_calloc.c \
 ft_isalnum.c \
 ft_isalpha.c \
 ft_isascii.c \
 ft_isblank.c \
 ft_isdigit.c \
 ft_isprint.c \
 ft_tolower.c \
 ft_toupper.c \
 ft_memchr.c \
 ft_memcmp.c \
 ft_memcpy.c \
 ft_memmove.c \
 ft_memset.c \
 ft_strdup.c\
 ft_strlcpy.c \
 ft_strlen.c \
 ft_strcmp.c \
 ft_strncmp.c \
 ft_strnstr.c \
 ft_strchr.c \
 ft_strjoin.c \
 ft_strrchr.c \
 ft_putendl_fd.c \
 ft_putnbr_fd.c \
 ft_putstr_fd.c \
 ft_putchar_fd.c \
 ft_striteri.c \
 ft_itoa.c \
 ft_strmapi.c \
 ft_substr.c \
 ft_strtrim.c \
 ft_strlcat.c \
 ft_split.c \
 get_next_line_bonus.c \
 ft_printf.c \
 ft_puthex_lower.c \
 ft_puthex_upper.c \
 ft_put_uns_dec.c \
 ft_isnum.c \
 ft_signal.c \
 ft_put_pointer.c\
 ft_lenbetween.c\

SRCB = ft_lstadd_back.c \
 ft_lstadd_front.c \
 ft_lstclear.c \
 ft_lstdelone.c \
 ft_lstiter.c \
 ft_lstlast.c \
 ft_lstmap.c \
 ft_lstnew.c \
 ft_lstsize.c \

OBJFILES = $(SRC:%.c=$(OBJFOLDER)%.o)

OBJB = $(SRCB:%.c=$(OBJFOLDER)%.o)

all: make_folder $(NAME)

$(NAME): $(OBJFILES)
	ar rcs $(NAME) $?
	echo $?

make_folder:
	@mkdir -p $(OBJFOLDER)

$(OBJFOLDER)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	ar rcs $(NAME) $@

clean:
	rm -f $(OBJFILES) $(OBJB) -r $(OBJFOLDER)

fclean: clean
	rm -f $(NAME)

re: fclean all
.PHONY: all bonus clean fclean re
