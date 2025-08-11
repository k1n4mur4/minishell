export HOME=/home/ubuntu
export USER=ubuntu
echo 'Testing variable expansion in heredoc:'
cat << EOF
Hello \$USER
Your home is: \$HOME
EOF
exit
