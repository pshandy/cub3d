NAME	=	libft.a

SRCS	=	/home/pshandy/Desktop/cub/libft/ft_atoi.c \
		/home/pshandy/Desktop/cub/libft/ft_bzero.c \
/home/pshandy/Desktop/cub/libft/ft_calloc.c \
/home/pshandy/Desktop/cub/libft/ft_isalnum.c\
/home/pshandy/Desktop/cub/libft/ft_isalpha.c\
/home/pshandy/Desktop/cub/libft/ft_isascii.c\
/home/pshandy/Desktop/cub/libft/ft_isdigit.c\
/home/pshandy/Desktop/cub/libft/ft_isprint.c\
/home/pshandy/Desktop/cub/libft/ft_isspace.c\
/home/pshandy/Desktop/cub/libft/ft_itoa.c\
/home/pshandy/Desktop/cub/libft/ft_lstadd_back.c\
/home/pshandy/Desktop/cub/libft/ft_lstadd_front.c\
/home/pshandy/Desktop/cub/libft/ft_lstclear.c\
/home/pshandy/Desktop/cub/libft/ft_lstdelone.c\
/home/pshandy/Desktop/cub/libft/ft_lstiter.c\
/home/pshandy/Desktop/cub/libft/ft_lstlast.c\
/home/pshandy/Desktop/cub/libft/ft_lstmap.c\
/home/pshandy/Desktop/cub/libft/ft_lstnew.c\
/home/pshandy/Desktop/cub/libft/ft_lstsize.c\
/home/pshandy/Desktop/cub/libft/ft_memchr.c\
/home/pshandy/Desktop/cub/libft/ft_memcmp.c\
/home/pshandy/Desktop/cub/libft/ft_memcpy.c\
/home/pshandy/Desktop/cub/libft/ft_memmove.c\
/home/pshandy/Desktop/cub/libft/ft_memset.c\
/home/pshandy/Desktop/cub/libft/ft_putchar_fd.c\
/home/pshandy/Desktop/cub/libft/ft_putendl_fd.c\
/home/pshandy/Desktop/cub/libft/ft_putnbr_fd.c\
/home/pshandy/Desktop/cub/libft/ft_putstr_fd.c\
/home/pshandy/Desktop/cub/libft/ft_split.c\
/home/pshandy/Desktop/cub/libft/ft_strchr.c\
/home/pshandy/Desktop/cub/libft/ft_strcmp.c\
/home/pshandy/Desktop/cub/libft/ft_strcpy.c\
/home/pshandy/Desktop/cub/libft/ft_strdup.c\
/home/pshandy/Desktop/cub/libft/ft_striteri.c\
/home/pshandy/Desktop/cub/libft/ft_strjoin.c\
/home/pshandy/Desktop/cub/libft/ft_strlcat.c\
/home/pshandy/Desktop/cub/libft/ft_strlcpy.c\
/home/pshandy/Desktop/cub/libft/ft_strlen.c\
/home/pshandy/Desktop/cub/libft/ft_strmapi.c\
/home/pshandy/Desktop/cub/libft/ft_strncmp.c\
/home/pshandy/Desktop/cub/libft/ft_strnstr.c\
/home/pshandy/Desktop/cub/libft/ft_strrchr.c\
/home/pshandy/Desktop/cub/libft/ft_strstr.c\
/home/pshandy/Desktop/cub/libft/ft_strtrim.c\
/home/pshandy/Desktop/cub/libft/ft_substr.c\
/home/pshandy/Desktop/cub/libft/ft_tolower.c\
/home/pshandy/Desktop/cub/libft/ft_toupper.c\

HEADER	=	libft.h

OBJ	=	$(patsubst %.c, %.o, $(SRCS))

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -I$(HEADER)

.PHONY	:	all clean fclean re bonus

all	: $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	ar rcs $(NAME) $?

%.o	: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean	:
	@rm -f $(OBJ) $(OBJ_B)

fclean	:	clean
	@$(RM) $(NAME)

re		:	fclean all
