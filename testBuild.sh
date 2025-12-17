#!/bin/bash
set -e
# ... [省略讀取 prefix 步驟] ...

echo "開始編譯並執行 (使用 C++ 模式以支援 std::map)"
read -e prefix

bison -d -o "$prefix.tab.c" "$prefix.y"

# 使用 g++ 編譯 parser
g++ -c -g -I.. "$prefix.tab.c"

flex -o lex.yy.c "$prefix.l"

# 使用 g++ 編譯 scanner
g++ -c -g -I.. lex.yy.c

# 使用 g++ 連結所有檔案 (必須使用 g++ 才能連結 C++ 函式庫)
g++ -o "$prefix" "$prefix.tab.o" lex.yy.o -ll

for i in {1..8}; do
    for j in {1..2}; do
        echo "第 $i-$j 題目: "
        question="./public_test_data/0"$i"_"$j".lsp"
        ./"$prefix" < $question
        echo "結束"
    done
done

for i in {1..8}; do
    for j in {1..2}; do
        echo "Bonus $i-$j 題目: "
        question="./public_test_data/b"$i"_"$j".lsp"
        ./"$prefix" < $question
        echo "結束"
    done
done
