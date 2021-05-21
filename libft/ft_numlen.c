int			ft_numlen(int n)
{
	int		l;

	l = 1;
	while (n /= 10)
		l++;
	return (l);
}

