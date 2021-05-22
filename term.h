#ifndef TERM_H
# define TERM_H

# include <sys/termios.h>
# include <termcap.h>

# define BUF_SIZE 4096
# define KEY_LEFT 4479771
# define KEY_RIGHT 4414235
# define KEY_UP 4283163
# define KEY_DOWN 4348699
# define BACK_SPACE 127
# define CTRL_D 4
# define CTRL_C 3
# define CTRL_BS 28

// TODO: buf 동적배열로 변경. BUF_SIZE를 초과하는 입력에 대해 처리가 부족함.
typedef struct	s_input
{
	int				x;
	char			*buf;
}				t_input;

int				init_termios(t_input **input);
t_input			*get_input(void);

int				handle_backspace(t_input *input);
int				handle_insert(t_input *input, int c);

int				show_new_line(void);
void			reset_input_mode(void);
#endif
