#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantique.h"
#include "table.h"
#include "AST.h"

// on a mit ici les variables pour l'automate
char n_auto[100];
char init_e[50];
char fin_e[100][50];
int nb_f = 0;
Trans mes_trans[200];
int n_t = 0;

void init_acc() {
    nb_f = 0;
    n_t = 0;
    init_e[0] = '\0';
    vide_tables();
}

void analyser_ast(AST* r) {
    if(!r) return;
    AST* f;
switch(r->type) {case NODE_PROG:// on va parcourir tout les enfants
f = r->gauche;
while(f) {
analyser_ast(f);
f = f->droite;
}
break;
case NODE_DEC:// ici on défini l'automate
strcpy(n_auto, r->val);
printf("\n-- Automate '%s' en cours...\n", n_auto);
// on regarde tout sque y'a dedans
f = r->gauche;
while(f) {
analyser_ast(f);
f = f->droite;
}
verif_auto();
break;
case NODE_ALPHABET:// l'alphabet
f = r->gauche;
while(f) {
ins_sym(f->c);
f = f->droite;
}
break;
case NODE_ETATS://
f = r->gauche;
while(f) {
ins_etat(f->val);
f = f->droite;
}
break;
case NODE_INIT://
strcpy(init_e, r->val);
break;
case NODE_FINAUX://
f = r->gauche;
while(f) {
if(nb_f < 100) {
strcpy(fin_e[nb_f], f->val);
nb_f++;
}
f = f->droite;
            }
            break;
case NODE_TRANS:// c la liste des transitions
f = r->gauche;
while(f) {
analyser_ast(f); // on regarde chaque transition
f = f->droite;
}
break;
case NODE_TRANS_LIST:
if(n_t < 200) {
                strcpy(mes_trans[n_t].d, r->val);
                mes_trans[n_t].s = r->gauche->c;
                strcpy(mes_trans[n_t].a, r->gauche->droite->val);
                n_t++;
            }
            break;
case NODE_MOTS://
check_mots(r->val);
break;
case NODE_VERIF://
            printf("Verification mot '%s'...\n", r->gauche->val);
            simule(r->gauche->val);
            break;
default://
if(r->gauche) analyser_ast(r->gauche);
if(r->droite) analyser_ast(r->droite);
break;
    }
}

void verif_auto() {
    int e = 0;
    int i;
    
if(!check_etat(init_e)) {
printf("Erreur: etat initial '%s' n'existe pas\n", init_e);
e++;
}
    
    for(i=0; i<nb_f; i++) {
if(!check_etat(fin_e[i])) {
printf("Erreur: etat final '%s' n'existe pas\n", fin_e[i]);
e++;
}
    }
    
    for(i=0; i<n_t; i++) {
if(!check_etat(mes_trans[i].d)) e++; 
if(!check_etat(mes_trans[i].a)) e++;
if(!check_sym(mes_trans[i].s)) e++;       
if(!check_etat(mes_trans[i].d)) printf("Erreur: trans %d etat depart '%s' inconnu\n", i, mes_trans[i].d);
if(!check_etat(mes_trans[i].a)) printf("Erreur: trans %d etat arrivee '%s' inconnu\n", i, mes_trans[i].a);
if(!check_sym(mes_trans[i].s)) printf("Erreur: trans %d symbole '%c' inconnu\n", i, mes_trans[i].s);
    }
    
    // on verifie si c'est deterministe ou pas
    int j;
    for(i=0; i<n_t; i++) {
        for(j=i+1; j<n_t; j++) {
if(strcmp(mes_trans[i].d, mes_trans[j].d) == 0 && mes_trans[i].s == mes_trans[j].s) {
printf("Erreur: Non determinisme detecte! Etat '%s' a deux transitions avec '%c' (vers '%s' et '%s')\n",
                       mes_trans[i].d, mes_trans[i].s, mes_trans[i].a, mes_trans[j].a);
e++;
            }
        }
    }
    
}

int simule(char *m) {
    char actuel[50];
    int i, j, ok;
    strcpy(actuel, init_e);
    
    printf("  %s -> ", actuel);
    
    i = 0;
    while(m[i] != '\0' && m[i] != '\n') {
        char c = m[i];
        ok = 0;
        
        for(j=0; j<n_t; j++) {
if(strcmp(mes_trans[j].d, actuel) == 0 && mes_trans[j].s == c) {
strcpy(actuel, mes_trans[j].a);
ok = 1;
printf("%s -> ", actuel);
break;
            }
        }
        
        if(!ok) {
            printf("BLOQUE\n");
            return 0;
        }
        i++;
    }
    
    for(j=0; j<nb_f; j++) {
if(strcmp(fin_e[j], actuel) == 0) {
printf("OK (final)\n");
return 1;
            }
        }
    
    printf("NON (pas final)\n");
    return 0;
}

void check_mots(char *fic) {
    // printf("Debug: checking file %s\n", fic);
    FILE *f = fopen(fic, "r");
    char buff[100];
    int l;
    if(!f) {
printf("Fichier %s non trouve\n", fic);
perror("Reason");
return;
    }
    
    printf("\n---** test des mots**--\n");
    while(fgets(buff, 100, f)) {
        l = strlen(buff);
        if(l>0 && (buff[l-1] == '\n' || buff[l-1] == '\r')) buff[l-1] = '\0';
if(l>1 && (buff[l-2] == '\n' || buff[l-2] == '\r')) buff[l-2] = '\0';

if(strlen(buff) > 0) {
printf("Mot: %s\n", buff);
simule(buff);
            }
    }
    fclose(f);
}
