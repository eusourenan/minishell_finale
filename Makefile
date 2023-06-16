NAME		:=	minishell

FLAGS		=	-Wall -Werror -Wextra -g
READLINE	=	-lreadline

FILES		=	env list main
#CFILES		=	$(addsuffix .c, $(FILES))
OBJS		=	$(addsuffix .o, $(FILES))
#OBJS		=	$(FILES:.c=.o)

LIBFT		=	libft/libft.a

INCLUDES	=	-I libft -I .

RM			=	rm -f

%.o: %.c
	cc -c $(FLAGS) $(INCLUDES) $< -o $@

all: libft $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	cc $(FLAGS) $(INCLUDES) $^ $(READLINE) -o $@

libft:
	@make -C libft

clean:
	$(RM) $(OBJS)
	@make -C libft clean

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re libft

v: all
	clear
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --trace-children=yes --trace-children-skip=''*/bin/*,*/sbin/*'' --suppressions=kkkkkk ./minishell 