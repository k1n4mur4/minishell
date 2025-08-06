#ifndef	CONFIG_H
# define	CONFIG_H

#include "libft.h"

# define VERSION "1.0.0"

# define MACHTYPE "unknown"

# define PROGRAM	"minishell"

char	*shell_version_string(void);
void	show_shell_version(int extended);

#endif