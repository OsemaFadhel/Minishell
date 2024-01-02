# include "../include/minishell.h"

int	my_cd(t_prompt *p)
{
	char	**str[2];
	char	*aux;

	int g_status = 0;
	str[0] = ((t_build *)p->cmds->content)->full_cmd;
	aux = get_env("HOME", p->envp, 4);
	if (!aux)
		aux = ft_strdup("");
	str[1] = extend_matrix(NULL, aux);
	free(aux);
	aux = getcwd(NULL, 0);
	str[1] = extend_matrix(str[1], aux);
	free(aux);
	change_error(str);
	if (!g_status)
		p->envp = set_env("OLDPWD", str[1][1], p->envp, 6);
	aux = getcwd(NULL, 0);
	if (!aux)
		aux = ft_strdup("");
	str[1] = extend_matrix(str[1], aux);
	free(aux);
	p->envp = set_env("PWD", str[1][2], p->envp, 3);
	free_matrix(&str[1]);
	return (g_status);
}