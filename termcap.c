#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include "minishell.h"
#include "term.h"

t_input		*get_input(void)
{
	static t_input	input;

	return (&input);
}

int			init_term(t_input *input)
{
	struct termios	term;
	char			*termtype;
	int				n;

	if (!(termtype = getenv("TERM")))
		return (FAILURE);
	if ((n = tgetent(NULL, termtype)) < 1)
		return (FAILURE);
	tcgetattr(STDIN_FILENO, &term);
	tcgetattr(STDIN_FILENO, &(input->backup));
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (SUCCESS);
}

void		show_new_line(void)
{
	t_input	*input;

	input = get_input();
	tputs(tgetstr("do", NULL), 1, ft_putchar);
	tputs(tgetstr("ll", NULL), 1, ft_putchar);
	ft_memset(input->buf, 0, sizeof(input->buf));
	input->x = 0;
	show_prompt();
}

void		reset_input_mode(t_input *input)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &input->backup);
}
