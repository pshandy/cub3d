SRCS =	/home/pshandy/Desktop/parser/cub3d.c\
		/home/pshandy/Desktop/parser/all_func.c\
		/home/pshandy/Desktop/parser/gnl/get_next_line.c
LIB = libft.a
NAME = "cub3d"

all:
	cc $(SRCS) $(LIB) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
			@rm -rf $(OBJS_DIR)

fclean:	clean
			@rm -f  $(NAME)

re: fclean all

.PHONY:	clean re fclean all
