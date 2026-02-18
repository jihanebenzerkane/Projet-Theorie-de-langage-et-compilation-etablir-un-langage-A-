#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "AST.h"

// fonction qui créer un noeud
AST* creer_noeud(NodeType type, char* val, char c) {
    AST* n = (AST*)malloc(sizeof(AST));
    if(!n) return NULL;
    n->type = type;
    if(val) n->val = strdup(val);
    else n->val = NULL;
    n->c = c;
    n->gauche = NULL;
    n->droite = NULL;
    return n;
}

// on rajoute un fils a la fin
AST* ajoute_fils(AST* p, AST* e) {
    if(!p) return e;
    if(!e) return p;
    if(!p->gauche) {
        p->gauche = e;
    } else {
        AST* temp = p->gauche;
        while(temp->droite) temp = temp->droite;
        temp->droite = e;
    }
    return p;
}


AST* ajoute_frere(AST* a, AST* b) {
    if(!a) return b;
    if(!b) return a;
    AST* temp = a;
    while(temp->droite) temp = temp->droite;
    temp->droite = b;
    return a;
}
