#ifndef TERM_H
# define TERM_H

# include <sys/termios.h>
# include <termcap.h>

# define BUF_SIZE 4096
# define LEFT_ARW 4479771
# define RIGHT_ARW 4414235
# define BACK_SPACE 127
# define CTRL_D 4
# define CTRL_C 3
# define CTRL_BS 28

// TODO: buf 동적배열로 변경. BUF_SIZE를 초과하는 입력에 대해 처리가 부족함.
typedef struct	s_input
{
	int				x;
	struct termios	backup;
	char			buf[BUF_SIZE];
}				t_input;

int				init_term(t_input *input);
t_input			*get_input(void);

void			handle_backspace(t_input *input);
void			handle_move_left(t_input *input);
void			handle_move_right(t_input *input);
void			handle_insert(t_input *input, int c);

void			show_new_line(void);
void			reset_input_mode(t_input *input);
#endif
