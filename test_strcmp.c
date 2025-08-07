#include <stdio.h>
#include "libft/includes/libft.h"

int main()
{
    printf("ft_strcmp(NULL, \"test\") = %d\n", ft_strcmp(NULL, "test"));
    printf("ft_strcmp(\"test\", NULL) = %d\n", ft_strcmp("test", NULL));
    printf("ft_strcmp(\"test\", \"test\") = %d\n", ft_strcmp("test", "test"));
    printf("ft_strcmp(\"test\", \"test2\") = %d\n", ft_strcmp("test", "test2"));
    return 0;
}