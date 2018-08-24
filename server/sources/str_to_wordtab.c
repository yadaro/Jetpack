/*
** EPITECH PROJECT, 2018
** jetpack
** File description:
** str_to_wordtab
*/

#include <stdlib.h>
#include "server.h"

static int	len(const char *s, char param)
{
	int	i = 0;

	while (s[i] && s[i] != param)
		++i;
	return (i + 1);
}

static int	nb_param(const char *s, char param)
{
	int	i = 0;
	int	r = 1;

	while (s[i]) {
		if (s[i] == param &&
		i > 1 && s[i - 1] &&
		s[i - 1] != param)
			++r;
		++i;
	}
	return (r + 2);
}

static char	**free_and_ret(t_wd *vr)
{
	char	**temp;

	temp = vr->tab;
	free(vr);
	return (temp);
}


static void	make_wordtab(t_wd *vr, char *s, char param)
{
	while (s[vr->i] != param && s[vr->i] != '\0') {
		vr->tab[vr->y][vr->x] = s[vr->i];
		++vr->x;
		++vr->i;
	}
	while (s[vr->i] && s[vr->i] == param)
		++vr->i;
	vr->tab[vr->y][vr->x] = '\0';
	vr->x = 0;
	++vr->y;
}

char	**str_to_wordtab(char *s, char param)
{
	t_wd	*vr;

	if ((vr = malloc(sizeof(t_wd))) == NULL ||
	(vr->tab = malloc(sizeof(char *) * (nb_param(s, param) + 1))) == NULL)
		return (NULL);
	init_wd(vr);
	while (s[vr->i] != '\0') {
		if ((vr->tab[vr->y] = malloc(sizeof(char) *
			(len(&s[vr->i], param)))) == NULL)
	return (NULL);
		make_wordtab(vr, s, param);
	}
	vr->tab[vr->y] = NULL;
	return (free_and_ret(vr));
}
