# 編譯器 MiniLisp

## yacc 說明
struct node是用來存AST tree的
var是用來存變數

這裡要說明一點
我用map<string, V> var_table; 這個是用來存全域變數的
用map<string, V> fin_table; 這是用來存function他的參數的
int para[300] 用來在呼叫函式時，暫存傳入的參數值

基本運算其實很好懂，就不在這裡解釋了，重點是function部分
這部分會先把function參數放到fun_table中，先儲存會用到的參數名稱
```
FUN_IDs 
        : '(' ')' {
            fun_position = 0;
        }
        | '(' { fun_position = 0; } exps_fun ')' {
        }

    exps_fun
        : ID {
            fun_table[string($1)].name = $1;
            fun_table[string($1)].val = fun_position++;
        }
        | exps_fun ID {
            fun_table[string($2)].name = $2;
            fun_table[string($2)].val = fun_position++;
        }
```
當function參數放到fun_table存好後，會被reduce回FUN_IDs
```
FUN_EXP 
        : '(' FUN { fun_position = 0; } FUN_IDs FUN_BODY ')' {
            bind_parameters($5); // 將變數綁定為參數索引
            $$ = $5;
            fun_table.clear();   // 定義完就清空，不要留到 Call
            fun_position = 0;
        }
```
這部分是function的匿名函數(除非前面有define)，在呼叫此function前，會先將fun_position歸零，因為每個function的參數必須獨立，然後當定義完成後就要清空table

```
FUN_CALL
        : '(' FUN_EXP ')' {
            $$ = $2;
        }
        | '(' FUN_EXP PARAMS ')' {
            N* fun_body_copy = CopyTree($2);
            put_parameters(fun_body_copy);
            $$ = fun_body_copy;
            pa_position = 0;
        }
        | '(' FUN_NAME PARAMS ')' {
            string fname($2->name);
            if(var_table.find(fname) != var_table.end() && 
            var_table[fname].tree != NULL) {
                N* fun_body_copy = CopyTree(var_table[fname].tree);
                put_parameters(fun_body_copy);
                $$ = fun_body_copy;
                fun_table.clear();
                pa_position = 0;
                fun_position = 0;
            }
        }
        | '(' FUN_NAME ')' { 
            string fname($2->name);
            if(var_table.find(fname) != var_table.end() && 
            var_table[fname].tree != NULL) {
                // 直接複製函式本體，不需要 put_parameters (因為沒有參數)
                N* fun_body_copy = CopyTree(var_table[fname].tree);
                $$ = fun_body_copy;
                
                // 重置全域變數
                fun_table.clear();
                pa_position = 0;
                fun_position = 0;
            }
        }

    PARAMS  
        : PARAM {
            pa_position = 0;
            para[pa_position++] = $1;
        }
        | PARAMS PARAM {
            para[pa_position++] = $2;
        }

    PARAM   
        : exp {
            $$ = EvalueTree($1);
        }

    FUN_NAME
        : VARIABLE { 
            $$ = $1; 
        }
```
PARAMS 那邊是將function提供的input 參數先把他存到para 陣列中，然後全部提供的input被reduce回PARAMS後，就會開始把提供的參數把她放到function的參數中(put_parameters)
## 如何編譯
使用bash檔案，在linux執行
```
./testBuild.sh
```
然後輸入fin