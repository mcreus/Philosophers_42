/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <mcreus@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:49:59 by mcreus            #+#    #+#             */
/*   Updated: 2023/06/22 14:18:35 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	itoa_len(long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		len++;
	if (nb < 0)
	{
		nb *= -1;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	char	*str;
	long	n;
	int		i;

	n = nb;
	i = itoa_len(n);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
		str[0] = 48;
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (str);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

int	create_string(t_philos *philo, char *status, char **str)
{
	char	*ptr[3];
	int		reslen;
	int		i;

	ptr[0] = ft_itoa((int)(get_time() - philo->args->t_start));
	ptr[1] = ft_itoa(philo->identity);
	ptr[2] = status;
	reslen = ft_strlen(ptr[0]) + ft_strlen (ptr[1]) + ft_strlen(ptr[2]) + 4;
	*str = malloc(reslen);
	*str[0] = '\0';
	i = 0;
	while (i < 3)
	{
		ft_strcat(*str, ptr[i]);
		if (i < 2)
		{
			ft_strcat(*str, " ");
			free(ptr[i]);
		}
		i++;
	}
	ft_strcat(*str, "\n");
	return (reslen);
}

void	print_status(t_philos *philo, char *status)
{
	char	*str;
	int		len;

	pthread_mutex_lock(&philo->args->m_stop);
	if (philo->args->stop == 1)
	{
		pthread_mutex_unlock(&philo->args->m_stop);
		return ;
	}
	if (!ft_strcmp(status, "died"))
		philo->args->stop = 1;
	pthread_mutex_unlock(&philo->args->m_stop);
	len = create_string(philo, status, &str);
	write(1, str, len);
	free(str);
}
