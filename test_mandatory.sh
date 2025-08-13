#!/bin/bash

# Minishell Mandatory要件テストスクリプト
# 使用法: ./test_mandatory.sh

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

PASS_COUNT=0
FAIL_COUNT=0

# テスト結果を記録
test_result() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}✓ PASS${NC}: $2"
        ((PASS_COUNT++))
    else
        echo -e "${RED}✗ FAIL${NC}: $2"
        ((FAIL_COUNT++))
    fi
}

# テストファイルの準備
echo "テストファイルを準備中..."
mkdir -p test_dir
echo "test content" > test_file.txt
echo "line1" > input.txt
echo "line2" >> input.txt

echo "=== Minishell Mandatory要件テスト ==="
echo ""

# 1. プロンプト表示テスト
echo -e "${YELLOW}1. プロンプト表示テスト${NC}"
timeout 1 ./minishell < /dev/null 2>&1 | grep -q "minishell"
test_result $? "プロンプト表示"

# 2. 基本コマンド実行テスト
echo -e "\n${YELLOW}2. コマンド実行テスト${NC}"

# PATH経由
echo "ls" | ./minishell 2>/dev/null | grep -q "test_file.txt"
test_result $? "PATH経由のコマンド実行 (ls)"

# 絶対パス
echo "/bin/echo test" | ./minishell 2>/dev/null | grep -q "test"
test_result $? "絶対パスのコマンド実行 (/bin/echo)"

# 相対パス
echo "./minishell --version" | ./minishell 2>/dev/null | grep -q "minishell"
test_result $? "相対パスのコマンド実行 (./minishell)"

# 3. クォート処理テスト
echo -e "\n${YELLOW}3. クォート処理テスト${NC}"

# シングルクォート
echo "echo 'test \$HOME test'" | ./minishell 2>/dev/null | grep -q 'test $HOME test'
test_result $? "シングルクォート内の変数非展開"

# ダブルクォート
echo 'echo "Home is $HOME"' | ./minishell 2>/dev/null | grep -q "/home"
test_result $? "ダブルクォート内の変数展開"

# クォートの組み合わせ
echo 'echo "test'"'"'test" '"'"'test"test'"'" | ./minishell 2>/dev/null | grep -q "test'test test\"test"
test_result $? "クォートの組み合わせ"

# 4. リダイレクトテスト
echo -e "\n${YELLOW}4. リダイレクトテスト${NC}"

# 出力リダイレクト
echo "echo test > output.txt" | ./minishell 2>/dev/null
[ -f output.txt ] && grep -q "test" output.txt
test_result $? "出力リダイレクト (>)"

# 追記リダイレクト
echo "echo append >> output.txt" | ./minishell 2>/dev/null
grep -q "append" output.txt
test_result $? "追記リダイレクト (>>)"

# 入力リダイレクト
echo "cat < input.txt" | ./minishell 2>/dev/null | grep -q "line1"
test_result $? "入力リダイレクト (<)"

# ヒアドキュメント
echo -e "cat << EOF\nheredoc test\nEOF" | ./minishell 2>/dev/null | grep -q "heredoc test"
test_result $? "ヒアドキュメント (<<)"

# 5. パイプテスト
echo -e "\n${YELLOW}5. パイプテスト${NC}"

# 単純なパイプ
echo "echo test | cat" | ./minishell 2>/dev/null | grep -q "test"
test_result $? "単純なパイプ"

# 多段パイプ
echo "echo test | cat | grep test" | ./minishell 2>/dev/null | grep -q "test"
test_result $? "多段パイプ"

# パイプとリダイレクトの組み合わせ
echo "echo test | cat > pipe_output.txt" | ./minishell 2>/dev/null
[ -f pipe_output.txt ] && grep -q "test" pipe_output.txt
test_result $? "パイプとリダイレクトの組み合わせ"

# 6. 環境変数展開テスト
echo -e "\n${YELLOW}6. 環境変数展開テスト${NC}"

# 通常の環境変数
echo 'echo $HOME' | ./minishell 2>/dev/null | grep -q "/home"
test_result $? "環境変数展開 (\$HOME)"

# 終了ステータス
echo 'false; echo $?' | ./minishell 2>/dev/null | grep -q "1"
test_result $? "終了ステータス (\$?)"

# 存在しない変数
echo 'echo start${NONEXISTENT}end' | ./minishell 2>/dev/null | grep -q "startend"
test_result $? "存在しない変数の展開"

# 7. ビルトインコマンドテスト
echo -e "\n${YELLOW}7. ビルトインコマンドテスト${NC}"

# echo
echo 'echo test' | ./minishell 2>/dev/null | grep -q "test"
test_result $? "echo コマンド"

# echo -n
echo 'echo -n test' | ./minishell 2>/dev/null | grep -v "test$" | grep -q "test"
test_result $? "echo -n オプション"

# pwd
echo 'pwd' | ./minishell 2>/dev/null | grep -q "/"
test_result $? "pwd コマンド"

# cd
echo 'cd /tmp; pwd' | ./minishell 2>/dev/null | grep -q "/tmp"
test_result $? "cd コマンド（絶対パス）"

echo 'cd test_dir; pwd' | ./minishell 2>/dev/null | grep -q "test_dir"
test_result $? "cd コマンド（相対パス）"

# export
echo 'export TEST_VAR=test_value; echo $TEST_VAR' | ./minishell 2>/dev/null | grep -q "test_value"
test_result $? "export コマンド"

# unset
echo 'export TEST_VAR=test; unset TEST_VAR; echo start${TEST_VAR}end' | ./minishell 2>/dev/null | grep -q "startend"
test_result $? "unset コマンド"

# env
echo 'env' | ./minishell 2>/dev/null | grep -q "PATH="
test_result $? "env コマンド"

# exit
echo 'exit 42' | ./minishell 2>/dev/null
echo 'echo test; exit 0; echo should_not_appear' | ./minishell 2>/dev/null | grep -qv "should_not_appear"
test_result $? "exit コマンド"

# 8. 組み合わせテスト
echo -e "\n${YELLOW}8. 組み合わせテスト${NC}"

# パイプ + リダイレクト + クォート
echo 'echo "test data" | cat > combined.txt' | ./minishell 2>/dev/null
[ -f combined.txt ] && grep -q "test data" combined.txt
test_result $? "パイプ + リダイレクト + クォート"

# 環境変数 + クォート + パイプ
echo 'echo "$HOME/test" | grep home' | ./minishell 2>/dev/null | grep -q "home"
test_result $? "環境変数 + クォート + パイプ"

# ビルトイン + リダイレクト
echo 'pwd > pwd_output.txt' | ./minishell 2>/dev/null
[ -f pwd_output.txt ] && grep -q "/" pwd_output.txt
test_result $? "ビルトイン + リダイレクト"

# 複雑な組み合わせ
echo 'export VAR=test; echo "$VAR" | cat | grep test > complex.txt' | ./minishell 2>/dev/null
[ -f complex.txt ] && grep -q "test" complex.txt
test_result $? "複雑な組み合わせ"

# 9. エラー処理テスト
echo -e "\n${YELLOW}9. エラー処理テスト${NC}"

# 存在しないコマンド
echo 'nonexistentcommand' | ./minishell 2>&1 | grep -q "No such file or directory\|command not found"
test_result $? "存在しないコマンドのエラー"

# 閉じていないクォート
echo 'echo "unclosed' | ./minishell 2>&1 | grep -q "error\|quote"
test_result $? "閉じていないクォートのエラー"

# 無効なリダイレクト
echo 'cat < nonexistent_file.txt' | ./minishell 2>&1 | grep -q "No such file or directory"
test_result $? "無効な入力リダイレクトのエラー"

# クリーンアップ
echo -e "\n${YELLOW}クリーンアップ中...${NC}"
rm -rf test_dir test_file.txt input.txt output.txt pipe_output.txt combined.txt pwd_output.txt complex.txt

# 結果サマリー
echo ""
echo "===================="
echo "テスト結果サマリー"
echo "===================="
echo -e "${GREEN}成功: $PASS_COUNT${NC}"
echo -e "${RED}失敗: $FAIL_COUNT${NC}"
TOTAL=$((PASS_COUNT + FAIL_COUNT))
PERCENTAGE=$((PASS_COUNT * 100 / TOTAL))
echo "成功率: ${PERCENTAGE}%"

if [ $FAIL_COUNT -eq 0 ]; then
    echo -e "\n${GREEN}すべてのテストが成功しました！${NC}"
    exit 0
else
    echo -e "\n${RED}いくつかのテストが失敗しました。${NC}"
    exit 1
fi