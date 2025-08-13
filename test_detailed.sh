#!/bin/bash

# Minishell 詳細テストスクリプト

echo "=== Minishell 詳細機能テスト ==="
echo ""

# 一時ファイルの準備
echo "テスト準備中..."
echo "Hello World" > test1.txt
echo "Line 1" > test2.txt
echo "Line 2" >> test2.txt
mkdir -p testdir

echo "== 1. ビルトインコマンドテスト =="

# echo with -n
echo "Test: echo -n test"
echo 'echo -n test; echo " end"' | ./minishell
echo ""

# cd と pwd
echo "Test: cd /tmp && pwd"
echo 'cd /tmp && pwd' | ./minishell
echo ""

echo "Test: cd testdir && pwd"
echo 'cd testdir && pwd' | ./minishell
echo ""

# export と環境変数
echo "Test: export TEST=value && echo \$TEST"
echo 'export TEST=value && echo $TEST' | ./minishell
echo ""

# unset
echo "Test: export TEST=value && unset TEST && echo start\${TEST}end"
echo 'export TEST=value && unset TEST && echo start${TEST}end' | ./minishell
echo ""

echo "== 2. リダイレクト詳細テスト =="

# 入力リダイレクト
echo "Test: cat < test1.txt"
echo 'cat < test1.txt' | ./minishell
echo ""

# 出力リダイレクト
echo "Test: echo output > out.txt && cat out.txt"
echo 'echo output > out.txt' | ./minishell
cat out.txt 2>/dev/null
rm -f out.txt
echo ""

# 追記リダイレクト
echo "Test: echo first > append.txt && echo second >> append.txt && cat append.txt"
echo 'echo first > append.txt' | ./minishell
echo 'echo second >> append.txt' | ./minishell
cat append.txt 2>/dev/null
rm -f append.txt
echo ""

# ヒアドキュメント
echo "Test: cat << END"
printf 'cat << END\nHeredoc line 1\nHeredoc line 2\nEND\n' | ./minishell
echo ""

echo "== 3. パイプ詳細テスト =="

# 複数パイプ
echo "Test: echo test | cat | grep test"
echo 'echo test | cat | grep test' | ./minishell
echo ""

# パイプとリダイレクト
echo "Test: echo test | cat > pipe.txt && cat pipe.txt"
echo 'echo test | cat > pipe.txt' | ./minishell
cat pipe.txt 2>/dev/null
rm -f pipe.txt
echo ""

# ビルトインとパイプ
echo "Test: echo test | grep test"
echo 'echo test | grep test' | ./minishell
echo ""

echo "== 4. クォート詳細テスト =="

# 混合クォート
echo "Test: echo \"double \$HOME\" 'single \$HOME'"
echo 'echo "double $HOME" '"'"'single $HOME'"'" | ./minishell
echo ""

# クォート内のパイプ
echo "Test: echo \"test | not a pipe\""
echo 'echo "test | not a pipe"' | ./minishell
echo ""

# クォート内のリダイレクト
echo "Test: echo \"test > not a redirect\""
echo 'echo "test > not a redirect"' | ./minishell
echo ""

echo "== 5. 環境変数詳細テスト =="

# 複数の環境変数
echo "Test: echo \$HOME \$USER \$PATH (first 50 chars)"
echo 'echo $HOME $USER $PATH' | ./minishell | cut -c1-50
echo ""

# 終了ステータスの連続
echo "Test: false && echo \$? || echo \$?"
echo 'false; echo $?' | ./minishell
echo 'true; echo $?' | ./minishell
echo ""

# 存在しない変数
echo "Test: echo before\${NOVAR}after"
echo 'echo before${NOVAR}after' | ./minishell
echo ""

echo "== 6. 複雑な組み合わせテスト =="

# パイプ、リダイレクト、クォート
echo "Test: echo \"Hello World\" | cat > complex.txt && cat complex.txt"
echo 'echo "Hello World" | cat > complex.txt' | ./minishell
cat complex.txt 2>/dev/null
rm -f complex.txt
echo ""

# 環境変数、パイプ、リダイレクト
echo "Test: echo \$HOME | grep home > result.txt && cat result.txt"
echo 'echo $HOME | grep home > result.txt' | ./minishell
cat result.txt 2>/dev/null
rm -f result.txt
echo ""

# 複数コマンドの連続実行
echo "Test: Multiple commands"
(echo 'echo first'
 echo 'echo second'
 echo 'echo third') | ./minishell
echo ""

echo "== 7. エラーハンドリングテスト =="

# 存在しないコマンド
echo "Test: nonexistent_command"
echo 'nonexistent_command' | ./minishell 2>&1 | head -1
echo ""

# 存在しないファイル
echo "Test: cat < nonexistent.txt"
echo 'cat < nonexistent.txt' | ./minishell 2>&1 | head -1
echo ""

# パーミッションエラー（書き込み不可）
echo "Test: echo test > /etc/passwd"
echo 'echo test > /etc/passwd' | ./minishell 2>&1 | head -1
echo ""

# クリーンアップ
echo "クリーンアップ中..."
rm -rf test1.txt test2.txt testdir

echo ""
echo "=== テスト完了 ==="