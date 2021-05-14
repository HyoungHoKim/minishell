#include "minishell.h"

void		handle_signal(int signo)
{
    pid_t	pid;
    int		status;

	// waitpid에서 첫번째 인자를 -1로 두고, WNOHANG을 옵션으로 두면 임의의 프로세스 중 어떤 프로세스라도
	// 종료되거나 멈추지 않았더라도 즉시 리턴하라는 의미
	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		// waitpid의 리턴값이 -1이면 자식 프로세스가 존재하지 않거나, 인터럽트시 반환
		if (pid == -1)
		{
			ft_putstr_fd("\b\b \b\b\n", STDIN);
			show_prompt();
		}
		else
			ft_putstr_fd("\n", STDIN);
	}
	else if (signo == SIGQUIT)
	{
		if (pid == -1)
			ft_putstr_fd("\b\b \b\b\n", STDIN);
		else
			ft_putstr_fd("Quit...\n", STDIN);
	}
}