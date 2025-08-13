#!/bin/bash

# Minishell インタラクティブテストスクリプト
# 個別の機能を一つずつテストする

echo "=== Minishell インタラクティブテスト ==="
echo ""

# 1. 基本的なコマンド実行
echo "1. echo test"
echo "echo test" | ./minishell
echo ""

# 2. PWDテスト
echo "2. pwd"
echo "pwd" | ./minishell
echo ""

# 3. 環境変数展開
echo "3. echo \$HOME"
echo 'echo $HOME' | ./minishell
echo ""

# 4. 終了ステータス
echo "4. echo \$?"
echo 'echo $?' | ./minishell
echo ""

# 5. シングルクォート
echo "5. echo 'test \$HOME test'"
echo "echo 'test \$HOME test'" | ./minishell
echo ""

# 6. ダブルクォート
echo "6. echo \"Home is \$HOME\""
echo 'echo "Home is $HOME"' | ./minishell
echo ""

# 7. パイプ
echo "7. echo test | cat"
echo "echo test | cat" | ./minishell
echo ""

# 8. 出力リダイレクト
echo "8. echo test > test_output.txt && cat test_output.txt"
echo "echo test > test_output.txt" | ./minishell
cat test_output.txt 2>/dev/null
rm -f test_output.txt
echo ""

# 9. ビルトインenv
echo "9. env (最初の5行)"
echo "env" | ./minishell | head -5
echo ""

# 10. exit
echo "10. exit"
echo "exit" | ./minishell
echo "Exit status: $?"
echo ""