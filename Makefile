all:
	@cd ft_printf && make all
	@cd libft && make all
	@gcc -Wall -Wextra -Werror server.c ft_printf/libftprintf.a libft/libft.a -o server
	@gcc -Wall -Wextra -Werror client.c ft_printf/libftprintf.a libft/libft.a -o client

clean:
	@cd ft_printf && make clean
	@cd libft && make clean
	@rm -f server
	@rm -f client

fclean: clean
	@cd ft_printf && make fclean
	@cd libft && make fclean

re: fclean all