#!/bin/bash

# メモリリークテストスクリプト
# Usage: ./test_leaks.sh

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo "=== Minishell Memory Leak Tests ==="
echo ""

# テストケース1: 単純なコマンド
echo -e "${GREEN}Test 1: Simple command${NC}"
echo "echo test" | valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell 2>&1 | grep -E "definitely lost|indirectly lost|possibly lost|still reachable" | grep -v "readline"
echo ""

# テストケース2: 変数展開
echo -e "${GREEN}Test 2: Variable expansion${NC}"
echo 'echo $HOME $USER $?' | valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell 2>&1 | grep -E "definitely lost|indirectly lost|possibly lost|still reachable" | grep -v "readline"
echo ""

# テストケース3: パイプライン
echo -e "${GREEN}Test 3: Pipeline${NC}"
echo "echo test | cat | grep test" | valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell 2>&1 | grep -E "definitely lost|indirectly lost|possibly lost|still reachable" | grep -v "readline"
echo ""

# テストケース4: クォート処理
echo -e "${GREEN}Test 4: Quote processing${NC}"
echo 'echo "test'"'"'test" '"'"'test"test'"'" | valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell 2>&1 | grep -E "definitely lost|indirectly lost|possibly lost|still reachable" | grep -v "readline"
echo ""

# テストケース5: Exit処理
echo -e "${GREEN}Test 5: Exit command${NC}"
echo "exit 42" | valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell 2>&1 | grep -E "definitely lost|indirectly lost|possibly lost|still reachable" | grep -v "readline"
echo ""

# テストケース6: 複数コマンド
echo -e "${GREEN}Test 6: Multiple commands${NC}"
(echo "ls"; echo "pwd"; echo "exit") | valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell 2>&1 | grep -E "definitely lost|indirectly lost|possibly lost|still reachable" | grep -v "readline"
echo ""

echo "=== Test Complete ===="