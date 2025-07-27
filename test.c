void	process_chunk(char *input, int i, int chunk_size,
		t_dict *dict, int size)
{
	char	chunk[4];
	int		j;
	int		group;
	int		len;

	j = 0;
	while (j < chunk_size)
	{
		chunk[j] = input[i + j];
		j++;
	}
	chunk[j] = '\0';
	if (!is_all_zeros(chunk))
	{
		print_group_in_words(chunk, dict, size);
		len = ft_strlen(input);
		group = ((len + 2) / 3 - 1) - (i / 3);
		if (i == 0 && len % 3)
			group = (len + 2) / 3 - 1;
		if (group > 0)
			print_power(group, dict, size);
	}
}

void	convert_number_to_words(char *input, t_dict *dict, int size)
{
	int	len;
	int	i;
	int	chunk_size;

	len = ft_strlen(input);
	if (len == 0)
		return ;
	if (get_word_for_number(dict, size, input))
		return (ft_putstr(ft_strcat(get_word_for_number(dict, size, input), "\n")));
	i = 0;
	while (i < len)
	{
		chunk_size = (i == 0 && len % 3) ? len % 3 : 3;
		process_chunk(input, i, chunk_size, dict, size);
		i += chunk_size;
	}
	ft_putstr("\n");
}
