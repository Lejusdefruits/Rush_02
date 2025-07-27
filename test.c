#include "./includes/ft.h"

void	convert_number_to_words(char *input, t_dict *dict, int size)
{
	int	len;
	int	group;
	int	i;
	int	chunk_size;

	len = ft_strlen(input);
	if (len == 0)
		return ;
	if (get_word_for_number(dict, size, input))
	{
		ft_putstr(ft_strcat(get_word_for_number(dict, size, input), "\n"));
		return ;
	}
	group = (len + 2) / 3 - 1;
	i = 0;
	while (i < len)
	{
		chunk_size = (i == 0 && len % 3) ? len % 3 : 3;
		process_chunk(input, i, chunk_size, dict, size, group);
		i += chunk_size;
		group--;
	}
	ft_putstr("\n");
}


#include "./includes/ft.h"

void	process_chunk(char *input, int i, int chunk_size,
		t_dict *dict, int size, int group)
{
	char	chunk[4];
	int		j;

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
		if (group > 0)
			print_power(group, dict, size);
	}
}