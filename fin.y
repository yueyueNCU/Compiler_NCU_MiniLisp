    %{
    #include <stdio.h>
    #include <stdlib.h>
    #include <map>
    #include <string>
    #include <string.h>
    using namespace std;

    int yylex();
    void yyerror(const char* message);

    enum headTypes {
        plu_op, sub_op, mut_op, div_op, mod_op,
        and_op, or_op, not_op, equ_op, gre_op, sma_op, num_no, 
        var_no, param_no, nothing,
        fun_call_op
    };

    typedef struct node{
        enum headTypes type;
        char *name;
        int val;
        struct node *l;
        struct node *r;
    } N;

    typedef struct var{
        char* name;
        int val;
        struct node *tree;
    } V;

    N *CreateNode(enum headTypes NodeType, int V, char *Name);
    N *CopyTree(N *tree);  // 新增: 複製樹
    void bind_parameters(N *tree);
    int EvalueTree(N *tree);
    void put_parameters(N *tree);

    map<string, V> var_table;
    map<string, V> fun_table;
    int para[300];
    int pa_position = 0;
    int fun_position = 0;
    %}

    %union{
        int num;
        char* id;
        struct node *nd;
    }

    %start program
    %token <num> NUMBER
    %token <num> BOOL
    %token <id> ID
    %token DEFINE FUN IF
    %token PRINT_NUM PRINT_BOOL

    %type <nd> exp VARIABLE NUM_OP LOGICAL_OP IF_EXP TEST_EXP THEN_EXP ELSE_EXP 
    %type <nd> FUN_EXP FUN_CALL FUN_BODY FUN_NAME
    %type <nd> PLUS exps_p MINUS MULTIPLY exps_mu DIVIDE MOD GREATER SMALLER EQUALL
    %type <nd> AND_OP exps_and OR_OP exps_or NOT_OP
    %type <num> PARAMS PARAM

    %%
    program
        : stmt_list
        ;

    stmt_list
        : stmt
        | stmt_list stmt
        ;

    stmt
        : exp {}
        | print_stmt {}
        | def_stmt {}
        ;

    print_stmt 
        : '(' PRINT_NUM exp ')' {
            printf("%d\n", EvalueTree($3));
        }
        | '(' PRINT_BOOL exp ')' {
            int result = EvalueTree($3);
            if(result == 0) printf("#f\n");
            else printf("#t\n");
        }

    def_stmt    
        : '(' DEFINE VARIABLE exp ')' {
            string name($3->name);
            var_table[name].name = $3->name;
            var_table[name].tree = $4;  // 儲存表達式樹
        }

    exp
        : NUMBER {
            N *newNode = CreateNode(num_no, $1, "");
            $$ = newNode;
        }
        | BOOL {
            N *newNode = CreateNode(num_no, $1, "");
            $$ = newNode;
        }
        | VARIABLE      { $$ = $1; }
        | NUM_OP        { $$ = $1; }
        | LOGICAL_OP    { $$ = $1; }
        | IF_EXP        { $$ = $1; }
        | FUN_EXP       { $$ = $1; }
        | FUN_CALL      { $$ = $1; } 

    VARIABLE 
        : ID {
            N *newNode = CreateNode(var_no, 0, $1);
            $$ = newNode;
        }

    NUM_OP  
        : PLUS      { $$ = $1; }
        | MINUS     { $$ = $1; }
        | MULTIPLY  { $$ = $1; }
        | DIVIDE    { $$ = $1; }
        | MOD       { $$ = $1; }
        | GREATER   { $$ = $1; }
        | SMALLER   { $$ = $1; }
        | EQUALL    { $$ = $1; }

    PLUS 
        : '(' '+' exp exps_p ')' {
            N *newNode = CreateNode(plu_op, 0, "");
            newNode->l = $3;
            newNode->r = $4;
            $$ = newNode;
        }

    exps_p  
        : exp { $$ = $1; }
        | exps_p exp {
            N *newNode = CreateNode(plu_op, 0, "");
            newNode->l = $1;
            newNode->r = $2;
            $$ = newNode;
        }

    MINUS 
        : '(' '-' exp exp ')' {
            N *newNode = CreateNode(sub_op, 0, "");
            newNode->l = $3;
            newNode->r = $4;
            $$ = newNode;
        }

    MULTIPLY
        : '(' '*' exp exps_mu ')' {
            N *newNode = CreateNode(mut_op, 0, "");
            newNode->l = $3;
            newNode->r = $4;
            $$ = newNode;
        }

    exps_mu 
        : exp { $$ = $1; }
        | exps_mu exp {
            N *newNode = CreateNode(mut_op, 0, "");
            newNode->l = $1;
            newNode->r = $2;
            $$ = newNode;
        }

    DIVIDE  
        : '(' '/' exp exp ')' {
            N *newNode = CreateNode(div_op, 0, "");
            newNode->l = $3;
            newNode->r = $4;
            $$ = newNode;
        }

    MOD  
        : '(' 'm' exp exp ')' {
            N *newNode = CreateNode(mod_op, 0, "");
            newNode->l = $3;
            newNode->r = $4;
            $$ = newNode;
        }

    GREATER  
        : '(' '>' exp exp ')' {
            N *newNode = CreateNode(gre_op, 0, "");
            newNode->l = $3;
            newNode->r = $4;
            $$ = newNode;
        }

    SMALLER  
        : '(' '<' exp exp ')' {
            N *newNode = CreateNode(sma_op, 0, "");
            newNode->l = $3;
            newNode->r = $4;
            $$ = newNode;
        }

    EQUALL  
        : '(' '=' exp exp ')' {
            N *newNode = CreateNode(equ_op, 0, "");
            newNode->l = $3;
            newNode->r = $4;
            $$ = newNode;
        }

    LOGICAL_OP  
        : AND_OP    { $$ = $1; }
        | OR_OP     { $$ = $1; }
        | NOT_OP    { $$ = $1; }

    AND_OP  
        : '(' 'a' exp exps_and ')' {
            N *newNode = CreateNode(and_op, 0, "");
            newNode->l = $3;
            newNode->r = $4;
            $$ = newNode;
        }

    exps_and    
        : exp { $$ = $1; }
        | exps_and exp {
            N *newNode = CreateNode(and_op, 0, "");
            newNode->l = $1;
            newNode->r = $2;
            $$ = newNode;
        }

    OR_OP  
        : '(' 'o' exp exps_or ')' {
            N *newNode = CreateNode(or_op, 0, "");
            newNode->l = $3;
            newNode->r = $4;
            $$ = newNode;
        }

    exps_or     
        : exp { $$ = $1; }
        | exps_or exp {
            N *newNode = CreateNode(or_op, 0, "");
            newNode->l = $1;
            newNode->r = $2;
            $$ = newNode;
        }

    NOT_OP  
        : '(' 'n' exp ')' {
            N *newNode = CreateNode(not_op, 0, "");
            newNode->l = $3;
            $$ = newNode;
        }

    IF_EXP  
        : '(' IF TEST_EXP THEN_EXP ELSE_EXP ')' {
            if(EvalueTree($3) == 1) {
                $$ = $4;
            } else {
                $$ = $5;
            } 
        }

    TEST_EXP : exp { $$ = $1; }
    THEN_EXP : exp { $$ = $1; }
    ELSE_EXP : exp { $$ = $1; }

    FUN_EXP 
        : '(' FUN { fun_position = 0; } FUN_IDs FUN_BODY ')' {
            bind_parameters($5); // <--- 將變數綁定為參數索引
            $$ = $5;
            fun_table.clear();   // <--- 定義完就清空，不要留到 Call
            fun_position = 0;
        }

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

    FUN_BODY
        : exp { 
            $$ = $1; 
        }

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

    %%

    N* CreateNode(enum headTypes NodeType, int V, char *Name) {
        N* NewNode = (N*) malloc(sizeof(N));
        NewNode->type = NodeType;
        NewNode->val = V;
        NewNode->name = Name;
        NewNode->l = NULL;
        NewNode->r = NULL;
        return NewNode;
    }

    // 新增: 複製樹的函數
    N* CopyTree(N* tree) {
        if(tree == NULL) return NULL;
        
        N* newNode = (N*) malloc(sizeof(N));
        newNode->type = tree->type;
        newNode->val = tree->val;
        
        // 複製字串
        if(tree->name != NULL && strlen(tree->name) > 0) {
            newNode->name = (char*)malloc(strlen(tree->name) + 1);
            strcpy(newNode->name, tree->name);
        } else {
            newNode->name = tree->name;
        }
        
        newNode->l = CopyTree(tree->l);
        newNode->r = CopyTree(tree->r);
        
        return newNode;
    }

    int EvalueTree(N* tree) {
        if(tree == NULL) return 0;
        
        // 處理運算符
        if(tree->type >= 0 && tree->type <= 10) {
            int left = 0, right = 0;
            left = EvalueTree(tree->l);
            right = EvalueTree(tree->r);

            switch(tree->type) {
                case plu_op: return left + right;
                case sub_op: return left - right;
                case mut_op: return left * right;
                case div_op: return left / right;
                case mod_op: return left % right;
                case and_op: return left && right;
                case or_op:  return left || right;
                case not_op: return !left;
                case equ_op: return left == right;
                case gre_op: return left > right;
                case sma_op: return left < right;
                default: return 0;
            }
        }
        // 處理數字
        else if(tree->type == num_no) {
            return tree->val;
        }
        // 處理變數
        else if(tree->type == var_no) {
            string var_name(tree->name);
            
            // 先檢查是否為函數參數
            if(fun_table.find(var_name) != fun_table.end()) {
                int param_pos = fun_table[var_name].val;
                return para[param_pos];
            }
            
            // 再檢查全域變數表
            if(var_table.find(var_name) != var_table.end()) {
                // 如果有表達式樹,就計算它
                if(var_table[var_name].tree != NULL) {
                    return EvalueTree(var_table[var_name].tree);
                }
                // 否則返回值
                return var_table[var_name].val;
            }
            
            return 0;
        }
        
        return 0;
    }

    void bind_parameters(N *tree) {
        if (tree == NULL) return;
        
        // 如果是變數，檢查它是否為參數
        if (tree->type == var_no) {
            string name(tree->name);
            if (fun_table.find(name) != fun_table.end()) {
                // 找到對應，將節點類型改為參數引用
                tree->type = param_no;
                tree->val = fun_table[name].val; // 直接存入它是第幾個參數(index)
            }
        }
        
        bind_parameters(tree->l);
        bind_parameters(tree->r);
    }

    void put_parameters(N *tree) {
        if(tree == NULL) return;
        
        // 如果是參數引用節點
        if(tree->type == param_no) {
            // 把它變成數字節點，數值取自參數堆疊
            tree->type = num_no;
            tree->val = para[tree->val]; // tree->val 已經存了 index
        }
        
        put_parameters(tree->l);
        put_parameters(tree->r);
    }

    void yyerror(const char *s) {
        printf("%s\n", s);
    }

    int main() {
        yyparse();
        return 0;
    }