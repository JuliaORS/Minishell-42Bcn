/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:57:07 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/24 10:59:03 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/*========================== system error management ==========================*/
# define EBADF 9
# define ENOMEM 12
# define NOPERM 126
# define CMNOFOUND 127
# define FILE_MAX 255

# define MALLOC_MESS "malloc failed: Cannot allocate memory"
# define BADF_MESS  "Bad file descriptor"
# define CMNF_MESS "command not found"
# define NOPERM_MESS "Permission denied"
# define SYNTAX_MESS "syntax error near unexpected token"

/*signals mode*/
# define READ		1
# define HEREDOC	2
# define EXEC		3

/*global variable*/
int	g_exit_sig;

typedef struct s_proc {
	char			**arg;
	int				pos;
	int				fd[3];
	char			*infile;
	char			*outfile;
	char			**hd_lim;
	int				intype;
	struct s_proc	*prev;
	struct s_proc	*next;
}	t_proc;

typedef struct s_tok {
	char			*str;
	int				type;
	struct s_tok	*prev;
	struct s_tok	*next;
}	t_tok;

typedef struct s_exec {
	char	**env;
	int		**pipes;
	pid_t	*pids;
	int		total_cmd;
	char	*path;
	int		backup_stdio[2];
	int		exit[2];
	int		dir_init;
	int		in_parent;
}	t_exec;

#endif
