NAME		:=	minishell

FLAGS		=	-Wall -Werror -Wextra -g
READLINE	=	-lreadline

FILES		=	0_main 1_env 2_list 3_minishell 4_input_checker\
				5_normalize_input 6_normalize_command 7_heredocs\
				8_heredocs2 9_heredoc3 10_multiple_commands\
				11_multiple_commands1 12_one_command\
				13_prepare_expansions 14_var_expansions 15_fds\
				16_check_fds 17_builtins 18_exit 19_export\
				20_export2 21_unset 22_cd 23_external_command\
				24_print_functions 25_utils 26_dup_and_close\
				27_tilde_expansion _signals _split_commands

OBJS		=	$(addsuffix .o, $(FILES))

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
	$(RM) $(NAME) $(LIBFT) supp logs

re: fclean all

.PHONY: all clean fclean re libft supp

v: supp all
	clear
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --trace-children=yes --trace-children-skip=''*/bin/*,*/sbin/*'' --suppressions=supp --track-fds=yes --log-file=logs ./minishell

supp:
	@printf "{\n\
	\t<Readline>\n\
	\tMemcheck:Leak\n\
	\tmatch-leak-kinds: reachable\n\
	\t...\n\
	\tfun:readline\n\
	\t...\n\
	}\n\
	{\n\
	\t<Readline>\n\
	\tMemcheck:Leak\n\
	\tmatch-leak-kinds: definite\n\
	\tfun:malloc\n\
	\tfun:xmalloc\n\
	\tfun:rl_add_undo\n\
	\tfun:rl_insert_text\n\
	\tfun:_rl_insert_char\n\
	\tfun:rl_insert\n\
	\tfun:_rl_dispatch_subseq\n\
	\tfun:readline_internal_char\n\
	\tfun:readline\n\
	\t...\n\
	}\n\
	{\n\
	\t<AddHistory>\n\
	\tMemcheck:Leak\n\
	\tmatch-leak-kinds: reachable\n\
	\tfun:malloc\n\
	\tfun:xmalloc\n\
	\tfun:add_history\n\
	\t...\n\
	}" > supp