#ifndef SEMANTIQUE_H
#define SEMANTIQUE_H

#include "AST.h"
// les constantes
#define MAX_E 100  
#define MAX_S 50   

// la structure pour les transitions
typedef struct {
    char d[50];  
    char s;      
    char a[50];  
} Trans;

extern char n_auto[100];      // le nom
extern char init_e[50];       // l'etat de depart
extern char fin_e[100][50];   // les etats de la fin
extern int nb_f;              // y'en a combien
extern Trans mes_trans[200];  // la liste des transitions
extern  int n_t;

// les fonctions
void init_acc();                 // pour l'init
void verif_auto();               // on verifie si c bon
int simule(char *m);             // on test le mot
void check_mots(char *fichier);  // on regarde le fichier

// FONCTION PRINCIPALE - on parcour l'arbre
void analyser_ast(AST* r);

#endif

