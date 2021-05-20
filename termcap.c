#include <stdlib.h>
#include <sys/termios.h>
#include <termcap.h>
#include <unistd.h>
#include "libft/libft.h"
#include "minishell.h"

char			*cl;
char			*cm;
char			*ce;
char			*am;

int	ft_numlen(int n)
{
	int		l;

	l = 1;
	while (n /= 10)
		l++;
	return (l);
}

void	get_cursor_position(int *col, int *rows)
{
	int		a = 0;
	int		i = 1;
	char	buf[255];
	int		ret;
	int		temp;

	write(0, "\033[6n", 4);  //report cursor location
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (!ft_isdigit(buf[i]))
		i++;
	*rows = ft_atoi(&buf[i]) - 1;
	i += ft_numlen(*rows) + 1;
	*col = ft_atoi(&buf[i]) - 1;
}

int		init_term(void)
{
	struct termios	term;
	char			*termtype;
	int				n;

	if (!(termtype = getenv("TERM")))
		return (FAILURE);
	n = tgetent(NULL, termtype);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	if (n < 1)
		return (FAILURE);
	return (SUCCESS);
}

int		ft_putchar(int c)
{
	write(STDOUT_FILENO, &c, 1);
	return (EXIT_SUCCESS);
}

void	handle_backspace(int *w, int *h)
{
	if (*w != 0)
		--(*w);
	tputs(tgoto(cm, *w, *h), 1, ft_putchar);
	tputs(tgetstr("dm", NULL), 1, ft_putchar);
	tputs(tgetstr("dc", NULL), 1, ft_putchar);
	tputs(tgetstr("ed", NULL), 1, ft_putchar);
}

void	handle_move_left(int *w, int *h)
{
	if (*w != 0)
		--(*w);
	tputs(tgetstr("le", NULL), 1, ft_putchar);
}

void	handle_insert(int *w, int c)
{
}

int		main(void)
{
	int				height;
	int				width;
	int				n;
	int				c;
	char			buf[4096];

	if (init_term())
		return (1);
	cl = tgetstr("cl", NULL);
	cm = tgetstr("cm", NULL);
	ce = tgetstr("ce", NULL);
	am = tgetstr("nd", NULL);
	get_cursor_position(&width, &height);

	ft_memset(buf, 0, 4096);
	//printf("cl = |%s|\ncm = |%s|\nheight = %d\twidth = %d\n", cl, cm, height, width);
	while ((n = read(STDIN_FILENO, &c, sizeof(c))) > 0)
	{
		if (c == 4479771)
			handle_move_left(&width, &height);
		/* else if (c == 4414235) */
		/* 	handle_move_right(&width, &height); */
		else if (c == 127)
		{
			ft_memmove(buf + width - 1, buf + width, sizeof(buf));
			handle_backspace(&width, &height);
		}
		else if (ft_isprint(c) || c == 10)
		{
			tputs(tgetstr("im", NULL), 1, ft_putchar);
			tputs(tgetstr("ic", NULL), 1, ft_putchar);
			ft_putchar(c);
			tputs(tgetstr("ip", NULL), 1, ft_putchar);
			tputs(tgetstr("ei", NULL), 1, ft_putchar);
			if (c == 10)
			{
				height++;
				width = 0;
				while (buf[width])
					width++;
				buf[width] = c;
				ft_putstr_fd(buf, STDOUT_FILENO);
				width = 0;
				ft_memset(buf, 0, 4096);
			}
			else
			{
				ft_memmove(buf + width + 1, buf + width, sizeof(buf));
				buf[width] = c;
				width++;
			}
		}
		c = 0;
	}
	return (0);
}
