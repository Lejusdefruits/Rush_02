/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_to_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejusdefruits <lejusdefruits@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:29:24 by lejusdefrui       #+#    #+#             */
/*   Updated: 2025/07/27 16:56:01 by lejusdefrui      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft.h"

char *get_word_for_number(t_dict *dictionary, int dict_size, char *number)
{
	int index = 0;
	while (index < dict_size)
	{
		if (ft_strcmp(dictionary[index].nbr, number) == 0)
			return (dictionary[index].str);
		index++;
	}
	return (NULL);
}

int is_all_zeros(char *text)
{
	while (*text)
	{
		if (*text != '0')
			return (0);
		text++;
	}
	return (1);
}

char *create_power_string(int group_position)
{
	char *power_string = malloc(group_position * 3 + 2);
	if (!power_string)
		return (NULL);
	power_string[0] = '1';
	int i = 1;
	while (i <= group_position * 3)
	{
		power_string[i] = '0';
		i++;
	}
	power_string[group_position * 3 + 1] = '\0';
	return (power_string);
}

char *format_to_three_digits(char *digits)
{
	char *formatted = malloc(4);
	if (!formatted)
		return (NULL);
	int length = ft_strlen(digits);
	if (length == 1)
		formatted[0] = '0', formatted[1] = '0', formatted[2] = digits[0];
	else if (length == 2)
		formatted[0] = '0', formatted[1] = digits[0], formatted[2] = digits[1];
	else
		formatted[0] = digits[0], formatted[1] = digits[1], formatted[2] = digits[2];
	formatted[3] = '\0';
	return (formatted);
}

void print_group_in_words(char *digits, t_dict *dictionary, int dict_size)
{
	char *exact_match = get_word_for_number(dictionary, dict_size, digits);
	if (exact_match)
	{
		if (ft_strcmp(exact_match, "100") == 0)
			ft_putstr("one ");
		ft_putstr(exact_match);
		ft_putstr(" ");
		return;
	}

	char *three_digits = format_to_three_digits(digits);
	if (!three_digits || ft_strcmp(three_digits, "000") == 0)
	{
		free(three_digits);
		return;
	}

	if (three_digits[0] != '0')
	{
		char hundreds[2] = {three_digits[0], '\0'};
		ft_putstr(get_word_for_number(dictionary, dict_size, hundreds));
		ft_putstr(" ");
		ft_putstr(get_word_for_number(dictionary, dict_size, "100"));
		ft_putstr(" ");
	}
	if (three_digits[1] == '1' && three_digits[2] != '0')
	{
		char teens[3] = {three_digits[1], three_digits[2], '\0'};
		ft_putstr(get_word_for_number(dictionary, dict_size, teens));
		ft_putstr(" ");
	}
	else
	{
		if (three_digits[1] != '0')
		{
			char tens[3] = {three_digits[1], '0', '\0'};
			ft_putstr(get_word_for_number(dictionary, dict_size, tens));
			ft_putstr(" ");
		}
		if (three_digits[2] != '0')
		{
			char ones[2] = {three_digits[2], '\0'};
			ft_putstr(get_word_for_number(dictionary, dict_size, ones));
			ft_putstr(" ");
		}
	}
	free(three_digits);
}

int compare_numbers_as_strings(char *a, char *b)
{
	int length_a = ft_strlen(a);
	int length_b = ft_strlen(b);
	if (length_a != length_b)
		return length_a - length_b;
	while (*a && *b)
	{
		if (*a != *b)
			return (*a - *b);
		a++;
		b++;
	}
	return 0;
}

void break_down_large_power(char *power, t_dict *dictionary, int dict_size)
{
	char *direct_label = get_word_for_number(dictionary, dict_size, power);
	if (direct_label)
	{
		ft_putstr(direct_label);
		ft_putstr(" ");
		return;
	}

	char *remaining = ft_strdup(power);
	if (!remaining)
		return;
	char *segments[MAX_PIECES];
	int segment_count = 0;

	while (compare_numbers_as_strings(remaining, "1000") >= 0)
	{
		char *best_match_key = NULL;
		char *best_match_word = NULL;
		int index = 0;
		while (index < dict_size)
		{
			if (dictionary[index].nbr[0] == '1' &&
				compare_numbers_as_strings(dictionary[index].nbr, remaining) <= 0 &&
				(!best_match_key || compare_numbers_as_strings(dictionary[index].nbr, best_match_key) > 0))
			{
				best_match_key = dictionary[index].nbr;
				best_match_word = dictionary[index].str;
			}
			index++;
		}
		if (!best_match_word)
			break;
		segments[segment_count++] = best_match_word;
		remaining[ft_strlen(remaining) - ft_strlen(best_match_key)] = '\0';
	}
	free(remaining);

	int i = segment_count - 1;
	while (i >= 0)
	{
		ft_putstr(segments[i]);
		ft_putstr(" ");
		i--;
	}
}

void convert_number_to_words(char *input, t_dict *dictionary, int dict_size)
{
	char *simple_conversion = get_word_for_number(dictionary, dict_size, input);
	if (simple_conversion)
	{
		ft_putstr(simple_conversion);
		ft_putstr("\n");
		return;
	}

	int input_length = ft_strlen(input);
	int total_parts = (input_length + 2) / 3;
	int leading_group_size = input_length % 3;
	if (leading_group_size == 0)
		leading_group_size = 3;

	int index = 0;
	int group_position = total_parts - 1;
	while (index < input_length)
	{
		int chunk_size = (index == 0) ? leading_group_size : 3;
		char chunk[4];
		int i = 0;
		while (i < chunk_size)
		{
			chunk[i] = input[index + i];
			i++;
		}
		chunk[i] = '\0';

		if (!is_all_zeros(chunk))
		{
			print_group_in_words(chunk, dictionary, dict_size);
			if (group_position > 0)
			{
				char *power_string = create_power_string(group_position);
				char *label = get_word_for_number(dictionary, dict_size, power_string);
				if (label)
				{
					ft_putstr(label);
					ft_putstr(" ");
				}
				else
					break_down_large_power(power_string, dictionary, dict_size);
				free(power_string);
			}
		}
		index += chunk_size;
		group_position--;
	}
	ft_putstr("\n");
}
