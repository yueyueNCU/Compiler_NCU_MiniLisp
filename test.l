%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.tab.h"

int line_num = 1;
%}

separator   [ \t\r]+
newline     \n
letter      [a-z]
digit       [0-9]

%%

{separator}   { /* ignore whitespace */ }
{newline}     { line_num++; }

"("           { return '('; }
")"           { return ')'; }

"print-num"   { return PRINT_NUM; }
"print-bool"  { return PRINT_BOOL; }

"+"           { return '+'; }
"-"           { return '-'; }
"*"           { return '*'; }
"/"           { return '/'; }
"mod"         { return MOD; }
">"           { return '>'; }
"<"           { return '<'; }
"="           { return '='; }

"and"         { return AND; }
"or"          { return OR; }
"not"         { return NOT; }

"define"      { return DEFINE; }
"fun"         { return FUN; }
"if"          { return IF; }

"#t"          { yylval.bool_val = 1; return BOOL_VAL; }
"#f"          { yylval.bool_val = 0; return BOOL_VAL; }

0|-?[1-9]{digit}*  { 
    yylval.num_val = atoi(yytext); 
    return NUMBER; 
}

{letter}({letter}|{digit}|"-")* { 
    yylval.string = strdup(yytext); 
    return ID; 
}

.             { printf("Unexpected character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}