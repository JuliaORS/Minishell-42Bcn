/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:12:32 by rjobert           #+#    #+#             */
/*   Updated: 2023/09/20 21:12:35 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	init_exec(t_exec *exec, t_proc *pcs_chain, char **env)
{
	if (!exec | !pcs_chain)
		return ; //later on do a free_chain here to clear the process_chain dble list
	exec->total_pcs = measure_list(pcs_chain);
	exec->env = env; //to replace with getenv later on
}

int	measure_list(t_proc *lst)
{
	int	n;

	n = 0;
	if (!lst)
		return (n);
	while (lst)
	{
		n++;
		lst = lst->next;
	}
	return (n);
}