#include "minishell.h"

bool is_digit(char c) {
  return (c >= '0' && c <= '9');
}

bool is_alpha(char c) {
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool is_alnum(char c) {
  return (is_digit(c) || is_alpha(c));
}

bool is_valid_dollar(char *data, int64_t i) {
  return (data[i] == '$' &&
          (is_alpha(data[i + 1]) || data[i] == '0' || data[i] == '?'));
}

extern char **environ;

char *get_dollar_value(char *key)
{
	int64_t	i;
	int64_t	key_len;
	char	*value;

	i = 0;

	value = NULL;
	while (environ[i])
	{
    	key_len = ft_strlen(key);
    	if (ft_strncmp(environ[i], key, key_len) == 0 && environ[i][key_len] == '=')
		{
			value = ft_strdup(&environ[i][key_len + 1]);
			if (!value)
				(void)i; // todo(hkizrak-): handle
		}
   		i++;
	}
	return (value);
}

void extract_dollar_key_values(char *data) {
  int64_t	flag_single_quote;
  int64_t	i;
  int64_t	start;
  char		*key;
  char		*value;

  if (!data)
    return;
  i = 0;
  flag_single_quote = 0;
  while (data[i])
  {
    flag_single_quote = get_in_quote(flag_single_quote, data[i]);
    if (flag_single_quote != '\'' && is_valid_dollar(data, i))
	{
		start = i + 1;
		if (data[i + 1] == '0' || data[i + 1] == '?')
		{
			// todo(hkizrak-): handle
			i += 2;
		}
		else
			while (is_alnum(data[i]))
				i++;
		key = ft_substr(data, start, i - start);
		if (!key)
			(void)i;// todo(hkizrak-): handle
		value = get_dollar_value(key);
		if (!value)
			(void)i;// todo(hkizrak-): handle
	}
    i++;
  }
}

// rrrr$a"dacdc"33"$b"$b

// take the length of the string for $ sign, then calculate the length
// of the value and the length of the string after $ and key.
// allocate the string with calculated total length
// copy the chars respectively
// delete the old data and put the new data
