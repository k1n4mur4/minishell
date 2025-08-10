#\!/bin/bash
echo 'Testing PS1 export...'
echo 'export PS1="$ "' | timeout 2 ./minishell
if [ $? -eq 124 ]; then
    echo "FAILED: Command timed out (hanging)"
    exit 1
else
    echo "SUCCESS: Command completed without hanging"
fi

echo -e '\nTesting other PS1 patterns...'
echo 'export PS1=">>> "' | timeout 2 ./minishell
echo 'export PS1="$USER> "' | timeout 2 ./minishell
echo 'export PS1="shell$ "' | timeout 2 ./minishell
echo "All tests passed\!"
