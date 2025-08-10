#\!/bin/bash
echo "Testing exit status:"
echo '/bin/false' | ./minishell
echo 'echo $?' | ./minishell
echo '/bin/true' | ./minishell
echo 'echo $?' | ./minishell
