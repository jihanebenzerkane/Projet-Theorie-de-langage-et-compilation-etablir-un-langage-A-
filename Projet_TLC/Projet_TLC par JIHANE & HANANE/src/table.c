#include <stdio.h>
#include <string.h>
#include "table.h"

char tab_etats[100][50];  // max 100 etats
int nb_e = 0;  // nombre d'etats

char tab_alpha[50];  // alphabet symbols
int nb_s = 0;

// insert un etat dans la table
void ins_etat(char* n) {
    if(nb_e < 100 && !check_etat(n)) {  // verifier qu'il existe pas deja
        strcpy(tab_etats[nb_e], n);
        nb_e++;
    }
}

// ici on verifie si un etat existe already
int check_etat(char* n) {
    int i;
    for(i=0; i<nb_e; i++) {
        if(strcmp(tab_etats[i], n) == 0) return 1;  // trouve
    }
    return 0;  // pas trouve
}

// ajouter un symbole dans l'alphabet
void ins_sym(char s) {
    if(nb_s < 50 && !check_sym(s)) {
        tab_alpha[nb_s] = s;
        nb_s++;
    }
}

// check si symbole est dans alphabet
int check_sym(char s) {
    int i;
    for(i=0; i<nb_s; i++) {
        if(tab_alpha[i] == s) return 1;
    }
    return 0;
}

// reset tout pour un nouvel automate
void vide_tables() {
    nb_e = 0;
    nb_s = 0;
}

