%{
#include "y.tab.h"

%}
/* Regular exp*/
DIGIT           [2-9]


%%
{DIGIT}  {yylval.val=yytext[0]-'0' ;return D;}
"x"      {return yytext[0];}
"^"      {return yytext[0];}
"+"      {return yytext[0];}
"-"      {return yytext[0];}
"0"      {yylval.val=0;return zero;}
"1"      {yylval.val=1;return one;}

%%
int yywrap(){
    return 1;
}

