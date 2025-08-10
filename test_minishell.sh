#\!/bin/bash

echo "=== Minishell Compliance Test ==="

# Test 1: Basic commands
echo -e "\n[Test 1: Basic Commands]"
echo 'ls | head -3' | ./minishell
echo 'pwd' | ./minishell

# Test 2: Redirections
echo -e "\n[Test 2: Redirections]"
echo 'echo "test output" > test_file.txt' | ./minishell
echo 'cat < test_file.txt' | ./minishell
echo 'echo "append" >> test_file.txt' | ./minishell
echo 'cat test_file.txt' | ./minishell
rm -f test_file.txt

# Test 3: Environment variables
echo -e "\n[Test 3: Environment Variables]"
echo 'echo $HOME' | ./minishell
echo 'echo $USER' | ./minishell

# Test 4: Exit status
echo -e "\n[Test 4: Exit Status \$?]"
echo 'ls /nonexistent 2>/dev/null; echo $?' | ./minishell
echo 'ls /tmp > /dev/null; echo $?' | ./minishell

# Test 5: Builtins
echo -e "\n[Test 5: Builtin Commands]"
echo 'echo hello world' | ./minishell
echo 'echo -n hello' | ./minishell && echo
echo 'pwd' | ./minishell
echo 'env | grep -E "^(HOME|PATH)" | head -2' | ./minishell

# Test 6: Quotes
echo -e "\n[Test 6: Quote Handling]"
echo "echo 'single quotes \$HOME'" | ./minishell
echo 'echo "double quotes $HOME"' | ./minishell

# Test 7: Pipes
echo -e "\n[Test 7: Pipes]"
echo 'ls | grep Makefile | wc -l' | ./minishell
echo 'echo "one\ntwo\nthree" | grep two' | ./minishell

echo -e "\n=== Test Complete ==="
