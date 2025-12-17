#!/bin/bash
set -e
echo "請輸入要 compile 的 lex和yacc 檔案名稱(只要前綴且前綴必須一樣)"
echo "lex 檔案裡面的import要是 y.tab.h"
read -e prefix
if [ ! -f "$prefix.l" ]; then
    echo "檔案不存在: $prefix.l"
    exit 1
fi

if [ ! -f "$prefix.y" ]; then
    echo "檔案不存在: $prefix.y"
    exit 1
fi

echo "開始編譯並執行"

bison -d -o "$prefix.tab.c" "$prefix.y"
gcc -c -g -I.. "$prefix.tab.c"
flex -o lex.yy.c "$prefix.l"
gcc -c -g -I.. lex.yy.c
gcc -o "$prefix" "$prefix.tab.o" lex.yy.o -ll

./"$prefix" < input.txt