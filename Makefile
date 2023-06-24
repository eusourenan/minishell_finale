NAME		:=	minishell

FLAGS		=	-Wall -Werror -Wextra -g
READLINE	=	-lreadline

FILES		=	0_-_main 1_-_env 2_-_list 3_-_minishell 4_-_input_checker\
				5_-_normalize_input 6_-_normalize_command 7_-_heredocs\
				8_-_heredocs2 9_-_heredoc3 10_-_multiple_commands\
				11_-_multiple_commands1 12_-_one_command\
				13_-_prepare_expansions 14_-_var_expansions 15_-_fds\
				16_-_check_fds 17_-_builtins 18_-_exit 19_-_export\
				20_-_export2 21_-_unset 22_-_cd 23_-_external_command\
				24_-_print_functions 25_-_utils 26_-_dup_and_close\
				27_-_tilde_expansion _signals _split_commands

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
	$(RM) $(NAME) $(LIBFT) supp feedback

re: fclean all

.PHONY: all clean fclean re libft supp

v: supp all
	clear
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --trace-children=yes --trace-children-skip=''*/bin/*,*/sbin/*'' --suppressions=supp --track-fds=yes --log-file=feedback ./minishell

file:
	@echo '#include "minishell.h"' '\n' > '$(f)' && code '$(f)'

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