#include "./includes/ft.h"

static int	get_chunk_size(char *input, int i)
{
	int	len;

	len = ft_strlen(input);
	if (i == 0 && len % 3)
		return (len % 3);
	return (3);
}

static void	fill_chunk(char *chunk, char *input, int i, int size)
{
	int	j;

	j = 0;
	while (j < size)
	{
		chunk[j] = input[i + j];
		j++;
	}
	chunk[j] = '\0';
}

void	process_chunk(char *input, int i, t_dict *dict, int size)
{
	char	chunk[4];
	int		chunk_size;
	int		group;
	int		len;

	chunk_size = get_chunk_size(input, i);
	fill_chunk(chunk, input, i, chunk_size);
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
	int	i;

	if (!input || !*input)
		return ;
	if (get_word_for_number(dict, size, input))
		return (ft_putstr(ft_strcat(get_word_for_number(dict, size, input), "\n")));
	i = 0;
	while (input[i])
	{
		process_chunk(input, i, dict, size);
		if (i == 0 && ft_strlen(input) % 3)
			i += ft_strlen(input) % 3;
		else
			i += 3;
	}
	ft_putstr("\n");
}