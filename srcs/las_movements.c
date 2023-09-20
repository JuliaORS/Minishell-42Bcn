

void find_cmd(t_cmd *lst_cmd, char *line)
{
	char	*poschr;
	char	*posstr;
	char	*str;
	size_t	i;
	char	**args;

	i = 0;
	if (lst_cmd->inf_status == 1)
	{
		poschr = ft_strchr(line, '<');
		posstr = ft_strnstr(line, lst_cmd->infile, ft_strlen(line));
		while(i < ft_strlen(lst_cmd->infile))
		{	
			posstr++;
			i++;
		}
		str = malloc (sizeof(char) * (ft_strlen(line) - ft_strlen(poschr) + 1));
		ft_strlcpy(str, line, ft_strlen(line) - ft_strlen(poschr) + 1);
		ft_strlcat(str, posstr, ft_strlen(posstr) + ft_strlen(str) + 1);
	}
	
	argc = ft_split(str, ' ');
}

void	create_node_str(t_cmd *lst_cmd, char *str, int *i)
{
	char	**cmd_line;
	t_tok	token;
	
	cmd_line = ft_split(str, ' ');

	if(!lst_cmd)
		lst_cmd = ft_lstnew_msh(0);
	else
		ft_lstadd_back(&lst_cmd, ft_lstnew_msh(0));
	token->arg = cmd_line;
	token->namefile = NULL;

}

void token_process(t_cmd *lst_cmd, char *str)
{
	t_tok	token;
	char	**process;
	int 	file;
	int 	i;
	char	**line
	char *substr;

	*i = 0;
	file = 0;
	i = 0;
	line = ft_split(str, ' ');
	while (line[i])
	{
		
		if (ft_strnstr())
		
		
		if ft_strchr(line, '<');
		
		
		if (line[i] != '>' && line[i] != '<' || line[i] != '\0')
		{
			while (line[i+j] != '>' && line[i+j] != '<' || line[i+j] != '\0')
				j++;	
			create_node_str(lst_cmd, ft_substr(line, i, j), ) // crear funcio per str
			i = i + j;
		}
		if (line[i] != '\0')
			create_node_sep(lst_cmd, line, &i);
	}
	
	
	find_infile(lst_cmd, line);
	find_outfile(lst_cmd, line);
	find_cmd(lst_cmd, line);
	printf("infile status: %i, infile name: ..%s..\n", lst_cmd->inf_status, lst_cmd->infile);
	printf("outfile status: %i, outfile name: ..%s..\n", lst_cmd->outf_status, lst_cmd->outfile);
}

void create_tokens(t_cmd *lst_cmd, char *line)
{
	char **arr_tok;
	int i;
	t_cmd	*tmp;
	
	tmp = lst_cmd;
	i = 0;
	arr_tok = ft_split(line, '|');
	while(arr_tok[i])
	{
		token_process(lst_cmd, arr_tok[i]);
		lst_cmd = lst_cmd->next;
		i++;
	}
}