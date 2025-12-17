%{
#include "fin.tab.h"
#include <stdlib.h>
#include <string.h>
%}

digit   [0-9]
letter  [a-z]
id      {letter}({letter}|{digit}|-)*
number  0|-?[1-9]{digit}*

%%
[\+\-\*\/\(\)\>\<\=]   {return yytext[0];}
[\t\n\r ]              {;}


"mod"               {return yytext[0];}
"and"               {return yytext[0];}
"or"                {return yytext[0];}
"not"               {return yytext[0];}

"define"            {return DEFINE;}  
"fun"               {return FUN;}
"if"                {return IF;}

"print-num"         {return PRINT_NUM;}
"print-bool"        {return PRINT_BOOL;}

"#t"                { yylval.num = 1; return BOOL; }
"#f"                { yylval.num = 0; return BOOL; }

{number}            {
                        yylval.num = atoi(yytext);
                        return NUMBER;
                    }

{id}                {
                        yylval.id = strdup(yytext);
                        return ID;
                    }

.                   { printf("Unknown char: %s\n", yytext); }
%%
int yywrap() {
    return 1;
}