// TABLE DES SYMBOLES
// pour stocker les etats et l'alphabet de l'automate et ne pas avoir le ^problrme de repetiotion

#ifndef TABLE_H
#define TABLE_H


void ins_etat(char* n);    // pour ajouter un etat
int check_etat(char* n);   // pour verifier si etat existe

// gestion de l'alphabet
void ins_sym(char s);      // pour ajouter un symbole
int check_sym(char s);     

// initialisation
void vide_tables();       

#endif

