#include "./includes/ft.h"

static void	print_hundreds(char *three, t_dict *dict, int size)
{
	char	one[2];

	if (three[0] == '0')
		return ;
	one[0] = three[0];
	one[1] = '\0';
	ft_putstr(get_word_for_number(dict, size, one));
	ft_putstr(" ");
	ft_putstr(get_word_for_number(dict, size, "100"));
	ft_putstr(" ");
}

static void	print_tens_units(char *three, t_dict *dict, int size)
{
	char	tmp[3];

	if (three[1] == '1' && three[2] != '0')
	{
		tmp[0] = three[1];
		tmp[1] = three[2];
		tmp[2] = '\0';
		ft_putstr(get_word_for_number(dict, size, tmp));
		ft_putstr(" ");
	}
	else
	{
		if (three[1] != '0')
		{
			tmp[0] = three[1];
			tmp[1] = '0';
			tmp[2] = '\0';
			ft_putstr(get_word_for_number(dict, size, tmp));
			ft_putstr(" ");
		}
		if (three[2] != '0')
		{
			tmp[0] = three[2];
			tmp[1] = '\0';
			ft_putstr(get_word_for_number(dict, size, tmp));
			ft_putstr(" ");
		}
	}
}

void	print_group_in_words(char *digits, t_dict *dict, int size)
{
	char	*word;
	char	*three;

	word = get_word_for_number(dict, size, digits);
	if (word)
	{
		if (ft_strcmp(word, "100") == 0)
			ft_putstr("one ");
		ft_putstr(word);
		ft_putstr(" ");
		return ;
	}
	three = format_to_three_digits(digits);
	if (!three || ft_strcmp(three, "000") == 0)
		return (free(three));
	print_hundreds(three, dict, size);
	print_tens_units(three, dict, size);
	free(three);
}
