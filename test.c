#include "./includes/ft.h"

static void	print_power(int pos, t_dict *dict, int size)
{
	char	*pow;
	char	*label;

	pow = create_power_string(pos);
	if (!pow)
		return ;
	label = get_word_for_number(dict, size, pow);
	if (label)
		ft_putstr(ft_strcat(label, " "));
	else
		break_down_large_power(pow, dict, size);
	free(pow);
}

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
		return (ft_putstr(
				ft_strcat(get_word_for_number(dict, size, input), "\n")));
	group = (len + 2) / 3 - 1;
	i = 0;
	while (i < len)
	{
		if (i == 0 && len % 3)
			chunk_size = len % 3;
		else
			chunk_size = 3;
		process_chunk(input, i, chunk_size, dict, size, group);
		i += chunk_size;
		group--;
	}
	ft_putstr("\n");
}
