%code requires { #include "AST.h" }
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantique.h"
// construction de l'arbre
extern int nb_ligne;  // pour les erreurs
extern FILE *yyin;   

int yylex();
void yyerror(const char *msg);

AST* racine;
%}


%union {
  char *sval;        // pour les strings et identifiants
  char cval;         // pour les symboles de l'alphabet
  AST* noeud;        // pour les noeuds de l'AST
}

// les tokens
%token AUTOMATE ALPHABET ETATS TOK_INITIAL FINAL TRANSITIONS MOTS
%token ACCOLADE_O ACCOLADE_F VIRGULE FLECHE DEUX_POINTS POINT_VIRGULE
%token VERIFIER
%token EGAL  

%token <sval> IDENT CHAINE  
%token <cval> SYMBOLE    

// tout ça sa renvoi un noeud
%type <noeud> programme automation_def cmds commande liste_dec declaration l_symb symbole_val l_etats liste_finaux l_trans transition l_mots

%%

// GRAMMAIRE

// c'est le programme principal
programme:
    automation_def { racine = $1; }
    | automation_def cmds { racine = creer_noeud(NODE_PROG, NULL, 0); ajoute_fils(racine, $1); ajoute_fils(racine, $2); }
    ;

// on défini l'automate ici
automation_def:
    AUTOMATE IDENT ACCOLADE_O liste_dec ACCOLADE_F
    {
        $$ = creer_noeud(NODE_DEC, $2, 0);
        ajoute_fils($$, $4);  // ajouter les declarations comme enfants
    };

// les commandes a faire
cmds:
    commande { $$ = $1; }
    | cmds commande { $$ = ajoute_frere($1, $2); };
// pour verifier les mots
commande: VERIFIER IDENT l_mots POINT_VIRGULE {
    AST *cur = $3;
    AST *first = NULL;
    AST *last = NULL;
    
    while (cur) {
        // on fait une commande verif pour chaque mot
        AST *verif_node = creer_noeud(NODE_VERIF, $2, 0); // node verif avec nom automate
        AST *mot_node = creer_noeud(NODE_CHAINE, cur->val, 0); // node mot
        ajoute_fils(verif_node, mot_node);
        if (!first) first = verif_node;
        else ajoute_frere(last, verif_node);
        
        last = verif_node;
        cur = cur->droite;
    }
    $$ = first;};
l_mots:
    CHAINE { $$ = creer_noeud(NODE_CHAINE, $1, 0); }
    | l_mots VIRGULE CHAINE { 
        AST *n = creer_noeud(NODE_CHAINE, $3, 0);
        $$ = ajoute_frere($1, n); 
    };

// liste de tout sque y'a dans l'automate
liste_dec: 
    declaration { $$ = $1; }
    | liste_dec declaration { $$ = ajoute_frere($1, $2); }
    ;
declaration:
    ALPHABET EGAL ACCOLADE_O l_symb ACCOLADE_F POINT_VIRGULE { $$ = creer_noeud(NODE_ALPHABET, NULL, 0); ajoute_fils($$, $4); }
    | ALPHABET ACCOLADE_O l_symb ACCOLADE_F POINT_VIRGULE { $$ = creer_noeud(NODE_ALPHABET, NULL, 0); ajoute_fils($$, $3); }
    | ETATS EGAL ACCOLADE_O l_etats ACCOLADE_F POINT_VIRGULE { $$ = creer_noeud(NODE_ETATS, NULL, 0); ajoute_fils($$, $4); }
    | ETATS ACCOLADE_O l_etats ACCOLADE_F POINT_VIRGULE { $$ = creer_noeud(NODE_ETATS, NULL, 0); ajoute_fils($$, $3); }
    | TOK_INITIAL EGAL IDENT POINT_VIRGULE { $$ = creer_noeud(NODE_INIT, $3, 0); }
    | TOK_INITIAL IDENT POINT_VIRGULE { $$ = creer_noeud(NODE_INIT, $2, 0); }
    | FINAL EGAL ACCOLADE_O liste_finaux ACCOLADE_F POINT_VIRGULE { $$ = creer_noeud(NODE_FINAUX, NULL, 0); ajoute_fils($$, $4); }
    | FINAL ACCOLADE_O liste_finaux ACCOLADE_F POINT_VIRGULE { $$ = creer_noeud(NODE_FINAUX, NULL, 0); ajoute_fils($$, $3); }
    | TRANSITIONS EGAL ACCOLADE_O l_trans ACCOLADE_F POINT_VIRGULE { $$ = creer_noeud(NODE_TRANS, NULL, 0); ajoute_fils($$, $4); }
    | TRANSITIONS ACCOLADE_O l_trans ACCOLADE_F POINT_VIRGULE { $$ = creer_noeud(NODE_TRANS, NULL, 0); ajoute_fils($$, $3); }
    | MOTS IDENT POINT_VIRGULE { $$ = creer_noeud(NODE_MOTS, $2, 0); }
    ;

// les symboles
l_symb:
    symbole_val { $$ = $1; }
    | l_symb VIRGULE symbole_val { $$ = ajoute_frere($1, $3); };
symbole_val:
    SYMBOLE { $$ = creer_noeud(NODE_SYMBOLE, NULL, $1); }
    | IDENT { 
        if(strlen($1) > 1) {
             printf("Attention ligne %d: symbole '%s' trop long, seul '%c' utilise.\n", nb_ligne, $1, $1[0]);}
        $$ = creer_noeud(NODE_SYMBOLE, NULL, $1[0]); };
// les etats
l_etats:
    IDENT { $$ = creer_noeud(NODE_IDENT, $1, 0); }
    | l_etats VIRGULE IDENT { $$ = ajoute_frere($1, creer_noeud(NODE_IDENT, $3, 0)); };
// les etats de la fin
liste_finaux:
    IDENT { $$ = creer_noeud(NODE_IDENT, $1, 0); }
    | liste_finaux VIRGULE IDENT { $$ = ajoute_frere($1, creer_noeud(NODE_IDENT, $3, 0)); };
// les transitions
l_trans:
    transition { $$ = $1; }
    | l_trans transition { $$ = ajoute_frere($1, $2); };
transition:
    IDENT DEUX_POINTS symbole_val FLECHE IDENT POINT_VIRGULE
    {
        $$ = creer_noeud(NODE_TRANS_LIST, $1, 0);  // etat depart
        ajoute_fils($$, $3);  // symbole
        ajoute_fils($$, creer_noeud(NODE_IDENT, $5, 0));  // etat arrivee
    }
    | IDENT VIRGULE symbole_val FLECHE IDENT VIRGULE
    {
        $$ = creer_noeud(NODE_TRANS_LIST, $1, 0);  
        ajoute_fils($$, $3);  
        ajoute_fils($$, creer_noeud(NODE_IDENT, $5, 0));  
    }
    | IDENT VIRGULE symbole_val FLECHE IDENT
    {
        $$ = creer_noeud(NODE_TRANS_LIST, $1, 0);  
        ajoute_fils($$, $3);  
        ajoute_fils($$, creer_noeud(NODE_IDENT, $5, 0));  
    }
    ;

%%

// si y'a une erreur sa vient la
void yyerror(const char *msg) {
    printf("Erreur ligne %d: %s\n", nb_ligne, msg);
}

// MAIN 
int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            printf("Erreur fichier\n"); return 1;
        }
    }
  
    init_acc();  // initialiser les structures
    if (yyparse() == 0) {
        analyser_ast(racine);  // traverser l'arbre
    }
    
    return 0;
}

