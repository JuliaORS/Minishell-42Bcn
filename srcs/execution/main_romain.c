/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_romain.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:38:30 by rjobert           #+#    #+#             */
/*   Updated: 2023/09/18 15:38:32 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// int main(int argc, char **argv, char **env)
// {
// 	if (argc > 100 || argv[1])
// 		return (1);
// 	t_proc *h_chain = create_chain();
// 	t_proc *chain = h_chain;
// 	while(chain)
// 	{
// 		printf("process position is  %i\n", chain->position);
// 		printf("	command is %s and flag is %s \n", chain->arg[0], chain->arg[1]);
// 		printf("	fd inputs is %i and output is %i\n", chain->fd[0], chain->fd[1]);
// 		printf("\n");
// 		chain = chain->next;
// 	}
// 	exec_machine(h_chain, env);
// 	return (0);
// }
t_proc *create_chain(void)
{
	t_proc **head;

	static char *arg1[] = {"cat", NULL};
	static char *arg2[] = {"cut", "-b", "1", NULL};
	static char *arg3[] = {"cat", "-n", NULL};
	static char *arg4[] = {"wc", NULL};
	t_proc *cmd1 = create_node(arg1, "test.txt", NULL, 0);
	t_proc *cmd2 = create_node(arg2, NULL, NULL, 1);
	t_proc *cmd3 = create_node(arg3, "midin.txt", "midout.txt", 2); //"midin.txt", "midout.txt"
	t_proc *cmd4 = create_node(arg4, NULL, "outfile_test.txt", 3);

	cmd1->next = cmd2;
	cmd1->prev = NULL;
	cmd2->next = cmd3;
	cmd2->prev = cmd1;
	cmd3->next = cmd4;
	cmd3->prev = cmd2;
	cmd4->next = NULL;
	cmd4->prev = cmd3;
	
	return (cmd1);
}
t_proc *create_node(char **cmd, char *f_input, char *f_output, int position)
{
	int fd_in, fd_out;

	t_proc *node = malloc(sizeof(t_proc));
	node->arg = cmd;
	if (f_input)
		fd_in = open(f_input, O_RDONLY, 0666);
	else
		fd_in = 0;
	if (f_output)
		fd_out = open(f_output, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else
		fd_out = 0;
	node->fd[0] = fd_in;
	node->fd[1] = fd_out;
	node->pos = position;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
