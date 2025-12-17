%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
void yyerror(const char *s);

/* AST 節點類型 */
typedef enum {
    AST_NUM, AST_BOOL, AST_VAR, AST_OP, AST_IF, AST_FUN, AST_CALL
} ASTType;

/* AST 節點 */
typedef struct ASTNode {
    ASTType type;
    union {
        int num;
        int bool_val;
        char *var;
        struct {
            char *op;
            struct ASTNode **args;
            int arg_count;
        } op;
        struct {
            struct ASTNode *cond;
            struct ASTNode *then_exp;
            struct ASTNode *else_exp;
        } if_node;
        struct {
            char **params;
            int param_count;
            struct ASTNode *body;
        } fun;
        struct {
            struct ASTNode *func;
            struct ASTNode **args;
            int arg_count;
        } call;
    } data;
} ASTNode;

/* 運行時值 */
typedef struct Value {
    enum { VAL_NUM, VAL_BOOL, VAL_FUNC } type;
    union {
        int num;
        int bool_val;
        struct {
            char **params;
            int param_count;
            ASTNode *body;
            struct Env *closure;
        } func;
    } data;
} Value;

/* 環境 */
typedef struct Env {
    char *name;
    Value *value;
    struct Env *next;
} Env;

Env *global_env = NULL;

/* 函式宣告 */
ASTNode* make_num(int n);
ASTNode* make_bool(int b);
ASTNode* make_var(char *name);
ASTNode* make_op(char *op, ASTNode **args, int count);
ASTNode* make_if(ASTNode *cond, ASTNode *then_exp, ASTNode *else_exp);
ASTNode* make_fun(char **params, int count, ASTNode *body);
ASTNode* make_call(ASTNode *func, ASTNode **args, int count);
Value* eval(ASTNode *ast, Env *env);
void define_var(Env **env, char *name, Value *val);
Value* lookup_var(Env *env, char *name);

%}

%union {
    int num_val;
    int bool_val;
    char *string;
    struct ASTNode *ast;
    struct {
        struct ASTNode **items;
        int count;
    } ast_list;
    struct {
        char **items;
        int count;
    } str_list;
}

%token <num_val> NUMBER
%token <bool_val> BOOL_VAL
%token <string> ID
%token PRINT_NUM PRINT_BOOL
%token MOD AND OR NOT
%token DEFINE FUN IF

%type <ast> EXP NUM_OP LOGICAL_OP FUN_EXP FUN_CALL IF_EXP
%type <ast> PLUS MINUS MULTIPLY DIVIDE MODULUS
%type <ast> GREATER SMALLER EQUAL
%type <ast> AND_OP OR_OP NOT_OP
%type <ast_list> EXPS PARAMS
%type <str_list> FUN_IDS IDS

%%

PROGRAM: STMTS
    ;

STMTS: STMT
    | STMTS STMT
    ;

STMT: EXP { 
        /* 表達式求值但不輸出 - 這是正確的行為 */
        /* 如果要看結果，必須使用 print-num 或 print-bool */
    }
    | DEF_STMT
    | PRINT_STMT
    ;

PRINT_STMT: '(' PRINT_NUM EXP ')' {
        Value *v = eval($3, global_env);
        if (v->type == VAL_NUM) {
            printf("%d\n", v->data.num);
        }
    }
    | '(' PRINT_BOOL EXP ')' {
        Value *v = eval($3, global_env);
        if (v->type == VAL_BOOL) {
            printf("%s\n", v->data.bool_val ? "#t" : "#f");
        }
    }
    ;

EXP: BOOL_VAL { 
        $$ = make_bool($1);
    }
    | NUMBER {
        $$ = make_num($1);
    }
    | ID {
        $$ = make_var($1);
    }
    | NUM_OP
    | LOGICAL_OP
    | FUN_EXP
    | FUN_CALL
    | IF_EXP
    ;

NUM_OP: PLUS | MINUS | MULTIPLY | DIVIDE | MODULUS
    | GREATER | SMALLER | EQUAL
    ;

PLUS: '(' '+' EXPS ')' {
        $$ = make_op("+", $3.items, $3.count);
    }
    ;

MINUS: '(' '-' EXP EXP ')' {
        ASTNode **args = malloc(sizeof(ASTNode*) * 2);
        args[0] = $3;
        args[1] = $4;
        $$ = make_op("-", args, 2);
    }
    ;

MULTIPLY: '(' '*' EXPS ')' {
        $$ = make_op("*", $3.items, $3.count);
    }
    ;

DIVIDE: '(' '/' EXP EXP ')' {
        ASTNode **args = malloc(sizeof(ASTNode*) * 2);
        args[0] = $3;
        args[1] = $4;
        $$ = make_op("/", args, 2);
    }
    ;

MODULUS: '(' MOD EXP EXP ')' {
        ASTNode **args = malloc(sizeof(ASTNode*) * 2);
        args[0] = $3;
        args[1] = $4;
        $$ = make_op("mod", args, 2);
    }
    ;

GREATER: '(' '>' EXP EXP ')' {
        ASTNode **args = malloc(sizeof(ASTNode*) * 2);
        args[0] = $3;
        args[1] = $4;
        $$ = make_op(">", args, 2);
    }
    ;

SMALLER: '(' '<' EXP EXP ')' {
        ASTNode **args = malloc(sizeof(ASTNode*) * 2);
        args[0] = $3;
        args[1] = $4;
        $$ = make_op("<", args, 2);
    }
    ;

EQUAL: '(' '=' EXPS ')' {
        $$ = make_op("=", $3.items, $3.count);
    }
    ;

LOGICAL_OP: AND_OP | OR_OP | NOT_OP
    ;

AND_OP: '(' AND EXPS ')' {
        $$ = make_op("and", $3.items, $3.count);
    }
    ;

OR_OP: '(' OR EXPS ')' {
        $$ = make_op("or", $3.items, $3.count);
    }
    ;

NOT_OP: '(' NOT EXP ')' {
        ASTNode **args = malloc(sizeof(ASTNode*));
        args[0] = $3;
        $$ = make_op("not", args, 1);
    }
    ;

DEF_STMT: '(' DEFINE ID EXP ')' {
        /* 先建立一個佔位符，讓遞迴函式可以引用自己 */
        Value *placeholder = malloc(sizeof(Value));
        placeholder->type = VAL_NUM;  /* 暫時的型別 */
        placeholder->data.num = 0;
        
        /* 先加入環境 */
        Env *new_env = malloc(sizeof(Env));
        new_env->name = strdup($3);
        new_env->value = placeholder;
        new_env->next = global_env;
        global_env = new_env;
        
        /* 現在求值，這樣函式體就能找到這個名字 */
        Value *val = eval($4, global_env);
        
        /* 更新值 */
        new_env->value = val;
    }
    ;

FUN_EXP: '(' FUN FUN_IDS EXP ')' {
        $$ = make_fun($3.items, $3.count, $4);
    }
    ;

FUN_IDS: '(' IDS ')' { $$ = $2; }
    | '(' ')' { 
        $$.items = NULL; 
        $$.count = 0; 
    }
    ;

IDS: ID {
        $$.items = malloc(sizeof(char*));
        $$.items[0] = $1;
        $$.count = 1;
    }
    | IDS ID {
        $$.items = realloc($1.items, sizeof(char*) * ($1.count + 1));
        $$.items[$1.count] = $2;
        $$.count = $1.count + 1;
    }
    ;

FUN_CALL: '(' FUN_EXP PARAMS ')' {
        $$ = make_call($2, $3.items, $3.count);
    }
    | '(' ID PARAMS ')' {
        $$ = make_call(make_var($2), $3.items, $3.count);
    }
    ;

IF_EXP: '(' IF EXP EXP EXP ')' {
        $$ = make_if($3, $4, $5);
    }
    ;

PARAMS: { 
        $$.items = NULL; 
        $$.count = 0; 
    }
    | PARAMS EXP {
        $$.items = realloc($1.items, sizeof(ASTNode*) * ($1.count + 1));
        $$.items[$1.count] = $2;
        $$.count = $1.count + 1;
    }
    ;

EXPS: EXP {
        $$.items = malloc(sizeof(ASTNode*));
        $$.items[0] = $1;
        $$.count = 1;
    }
    | EXPS EXP {
        $$.items = realloc($1.items, sizeof(ASTNode*) * ($1.count + 1));
        $$.items[$1.count] = $2;
        $$.count = $1.count + 1;
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

/* AST 建構函式 */
ASTNode* make_num(int n) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_NUM;
    node->data.num = n;
    return node;
}

ASTNode* make_bool(int b) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_BOOL;
    node->data.bool_val = b;
    return node;
}

ASTNode* make_var(char *name) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_VAR;
    node->data.var = strdup(name);
    return node;
}

ASTNode* make_op(char *op, ASTNode **args, int count) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_OP;
    node->data.op.op = strdup(op);
    node->data.op.args = args;
    node->data.op.arg_count = count;
    return node;
}

ASTNode* make_if(ASTNode *cond, ASTNode *then_exp, ASTNode *else_exp) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_IF;
    node->data.if_node.cond = cond;
    node->data.if_node.then_exp = then_exp;
    node->data.if_node.else_exp = else_exp;
    return node;
}

ASTNode* make_fun(char **params, int count, ASTNode *body) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_FUN;
    node->data.fun.params = params;
    node->data.fun.param_count = count;
    node->data.fun.body = body;
    return node;
}

ASTNode* make_call(ASTNode *func, ASTNode **args, int count) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_CALL;
    node->data.call.func = func;
    node->data.call.args = args;
    node->data.call.arg_count = count;
    return node;
}

/* 環境操作 */
void define_var(Env **env, char *name, Value *val) {
    Env *e = *env;
    while (e) {
        if (strcmp(e->name, name) == 0) {
            fprintf(stderr, "Error: Variable '%s' already defined\n", name);
            exit(1);
        }
        e = e->next;
    }
    
    Env *new_env = malloc(sizeof(Env));
    new_env->name = strdup(name);
    new_env->value = val;
    new_env->next = *env;
    *env = new_env;
}

Value* lookup_var(Env *env, char *name) {
    while (env) {
        if (strcmp(env->name, name) == 0) {
            return env->value;
        }
        env = env->next;
    }
    fprintf(stderr, "Error: Undefined variable '%s'\n", name);
    exit(1);
}

/* 求值器 */
Value* eval(ASTNode *ast, Env *env) {
    Value *result;
    int i;
    
    if (!ast) return NULL;
    
    switch (ast->type) {
        case AST_NUM:
            result = malloc(sizeof(Value));
            result->type = VAL_NUM;
            result->data.num = ast->data.num;
            return result;
            
        case AST_BOOL:
            result = malloc(sizeof(Value));
            result->type = VAL_BOOL;
            result->data.bool_val = ast->data.bool_val;
            return result;
            
        case AST_VAR:
            return lookup_var(env, ast->data.var);
            
        case AST_OP: {
            char *op = ast->data.op.op;
            
            if (strcmp(op, "+") == 0) {
                int sum = 0;
                for (i = 0; i < ast->data.op.arg_count; i++) {
                    Value *v = eval(ast->data.op.args[i], env);
                    if (v->type != VAL_NUM) {
                        fprintf(stderr, "Type error!\n");
                        exit(1);
                    }
                    sum += v->data.num;
                }
                result = malloc(sizeof(Value));
                result->type = VAL_NUM;
                result->data.num = sum;
                return result;
            }
            else if (strcmp(op, "-") == 0) {
                Value *v1 = eval(ast->data.op.args[0], env);
                Value *v2 = eval(ast->data.op.args[1], env);
                if (v1->type != VAL_NUM || v2->type != VAL_NUM) {
                    fprintf(stderr, "Type error!\n");
                    exit(1);
                }
                result = malloc(sizeof(Value));
                result->type = VAL_NUM;
                result->data.num = v1->data.num - v2->data.num;
                return result;
            }
            else if (strcmp(op, "*") == 0) {
                int prod = 1;
                for (i = 0; i < ast->data.op.arg_count; i++) {
                    Value *v = eval(ast->data.op.args[i], env);
                    if (v->type != VAL_NUM) {
                        fprintf(stderr, "Type error!\n");
                        exit(1);
                    }
                    prod *= v->data.num;
                }
                result = malloc(sizeof(Value));
                result->type = VAL_NUM;
                result->data.num = prod;
                return result;
            }
            else if (strcmp(op, "/") == 0) {
                Value *v1 = eval(ast->data.op.args[0], env);
                Value *v2 = eval(ast->data.op.args[1], env);
                if (v1->type != VAL_NUM || v2->type != VAL_NUM) {
                    fprintf(stderr, "Type error!\n");
                    exit(1);
                }
                result = malloc(sizeof(Value));
                result->type = VAL_NUM;
                result->data.num = v1->data.num / v2->data.num;
                return result;
            }
            else if (strcmp(op, "mod") == 0) {
                Value *v1 = eval(ast->data.op.args[0], env);
                Value *v2 = eval(ast->data.op.args[1], env);
                if (v1->type != VAL_NUM || v2->type != VAL_NUM) {
                    fprintf(stderr, "Type error!\n");
                    exit(1);
                }
                result = malloc(sizeof(Value));
                result->type = VAL_NUM;
                result->data.num = v1->data.num % v2->data.num;
                return result;
            }
            else if (strcmp(op, ">") == 0) {
                Value *v1 = eval(ast->data.op.args[0], env);
                Value *v2 = eval(ast->data.op.args[1], env);
                if (v1->type != VAL_NUM || v2->type != VAL_NUM) {
                    fprintf(stderr, "Type error!\n");
                    exit(1);
                }
                result = malloc(sizeof(Value));
                result->type = VAL_BOOL;
                result->data.bool_val = v1->data.num > v2->data.num;
                return result;
            }
            else if (strcmp(op, "<") == 0) {
                Value *v1 = eval(ast->data.op.args[0], env);
                Value *v2 = eval(ast->data.op.args[1], env);
                if (v1->type != VAL_NUM || v2->type != VAL_NUM) {
                    fprintf(stderr, "Type error!\n");
                    exit(1);
                }
                result = malloc(sizeof(Value));
                result->type = VAL_BOOL;
                result->data.bool_val = v1->data.num < v2->data.num;
                return result;
            }
            else if (strcmp(op, "=") == 0) {
                Value *first = eval(ast->data.op.args[0], env);
                if (first->type != VAL_NUM) {
                    fprintf(stderr, "Type error!\n");
                    exit(1);
                }
                int all_equal = 1;
                for (i = 1; i < ast->data.op.arg_count; i++) {
                    Value *v = eval(ast->data.op.args[i], env);
                    if (v->type != VAL_NUM) {
                        fprintf(stderr, "Type error!\n");
                        exit(1);
                    }
                    if (v->data.num != first->data.num) {
                        all_equal = 0;
                        break;
                    }
                }
                result = malloc(sizeof(Value));
                result->type = VAL_BOOL;
                result->data.bool_val = all_equal;
                return result;
            }
            else if (strcmp(op, "and") == 0) {
                int res = 1;
                for (i = 0; i < ast->data.op.arg_count; i++) {
                    Value *v = eval(ast->data.op.args[i], env);
                    if (v->type != VAL_BOOL) {
                        fprintf(stderr, "Type error!\n");
                        exit(1);
                    }
                    if (!v->data.bool_val) {
                        res = 0;
                        break;
                    }
                }
                result = malloc(sizeof(Value));
                result->type = VAL_BOOL;
                result->data.bool_val = res;
                return result;
            }
            else if (strcmp(op, "or") == 0) {
                int res = 0;
                for (i = 0; i < ast->data.op.arg_count; i++) {
                    Value *v = eval(ast->data.op.args[i], env);
                    if (v->type != VAL_BOOL) {
                        fprintf(stderr, "Type error!\n");
                        exit(1);
                    }
                    if (v->data.bool_val) {
                        res = 1;
                        break;
                    }
                }
                result = malloc(sizeof(Value));
                result->type = VAL_BOOL;
                result->data.bool_val = res;
                return result;
            }
            else if (strcmp(op, "not") == 0) {
                Value *v = eval(ast->data.op.args[0], env);
                if (v->type != VAL_BOOL) {
                    fprintf(stderr, "Type error!\n");
                    exit(1);
                }
                result = malloc(sizeof(Value));
                result->type = VAL_BOOL;
                result->data.bool_val = !v->data.bool_val;
                return result;
            }
            break;
        }
        
        case AST_IF: {
            Value *cond = eval(ast->data.if_node.cond, env);
            if (cond->data.bool_val) {
                return eval(ast->data.if_node.then_exp, env);
            } else {
                return eval(ast->data.if_node.else_exp, env);
            }
        }
        
        case AST_FUN: {
            result = malloc(sizeof(Value));
            result->type = VAL_FUNC;
            result->data.func.params = ast->data.fun.params;
            result->data.func.param_count = ast->data.fun.param_count;
            result->data.func.body = ast->data.fun.body;
            result->data.func.closure = env;
            return result;
        }
        
        case AST_CALL: {
            Value *func = eval(ast->data.call.func, env);
            
            if (func->type != VAL_FUNC) {
                fprintf(stderr, "Error: Not a function\n");
                exit(1);
            }
            
            if (func->data.func.param_count != ast->data.call.arg_count) {
                fprintf(stderr, "Error: Parameter count mismatch\n");
                exit(1);
            }
            
            /* 建立新環境 */
            Env *new_env = func->data.func.closure;
            for (i = 0; i < func->data.func.param_count; i++) {
                Value *arg_val = eval(ast->data.call.args[i], env);
                Env *binding = malloc(sizeof(Env));
                binding->name = strdup(func->data.func.params[i]);
                binding->value = arg_val;
                binding->next = new_env;
                new_env = binding;
            }
            
            /* 在新環境中求值函式體 */
            return eval(func->data.func.body, new_env);
        }
    }
    
    return NULL;
}

int main(int argc, char **argv) {
    return yyparse();
}