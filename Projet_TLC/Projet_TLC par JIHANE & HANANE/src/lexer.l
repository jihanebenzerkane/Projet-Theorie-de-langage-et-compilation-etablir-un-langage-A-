%{
#include "parser.tab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// pour compter les lignes
int nb_ligne = 1;

%}


%%

   
"automate"      { return AUTOMATE; }
"alphabet"   { return ALPHABET; }
"etats"   { return ETATS; }
"initial"       { return TOK_INITIAL; }

"final"         { return FINAL; }
"finaux" { return FINAL; }
"transitions"   { return TRANSITIONS; }
"mots"          { return MOTS; }
"verifier"      { return VERIFIER; }

\"[^\"]*\"      { yytext[yyleng-1] = '\0'; yylval.sval = strdup(yytext+1); return CHAINE;}

[a-zA-Z][a-zA-Z0-9_./-]* { yylval.sval = strdup(yytext); return IDENT;}

"{"   { return ACCOLADE_O; }
"}"   { return ACCOLADE_F; }
","    { return VIRGULE; }
"->"    { return FLECHE; }
"="     { return EGAL; }
":"    { return DEUX_POINTS; }
";"    { return POINT_VIRGULE; }





[ \t\r]+          ; 
\n              { nb_ligne++; }

"//".*          ; 


.               { yylval.cval = yytext[0]; return SYMBOLE; }

%%

int yywrap() {
    return 1;
}
