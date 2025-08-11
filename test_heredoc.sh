Test variable: $USER=$(whoami)
echo "Testing heredoc with variable expansion:"
./minishell << EOF
Hello $USER
This should expand: $HOME
EOF
