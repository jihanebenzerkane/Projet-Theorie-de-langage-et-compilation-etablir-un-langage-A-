# Projet Compilation

Ce projet est un compilateur pour les automates finis deterministes (AFD).
Il permet de verifier si des mots sont acceptes par un automate definit dans un fichier texte.

Le projet supporte tous les symboles (lettres, chiffres, caracteres speciaux) et permet de verifier plusieurs mots a la fois.

## Fichiers
- `src/` : Code source (lex.l, parser.y, C)
- `exemples/` : Exemples d'automates (.afd)

## Compilation et Execution

Commandes a executer dans le terminal :

```bash
Monsieur vous pouver simplement copier les commandes suivantes dans le terminal :

****************************
make clean
make    //pour compiler et generer le fichier lex.yy.c et parser.tab.c etC...
./ensa.exe exemples/test_mots.afd   //pour verifier les mots dans le fichier mots.txt
./ensa.exe exemples/symboles.afd   //pour verifier les symboles dans le fichier symboles.txt
./ensa.exe exemples/speciaux.afd   //pour verifier les caracteres speciaux dans le fichier speciaux.txt
*******************************

vous pouvez aussi verifier directement :
le mot que vous voulez en l'ajoutant dant l'un des fichiers texte fournis dans le dossier exemples.

Exemple simple :

```
automate MonAuto {
    alphabet = {a, b};
    etats = {q0, q1};
    initial = q0;
    finaux = {q1};
    transitions = {
        q0 : a -> q1;
        q1 : b -> q0;
    };
    mots exemples/mots.txt;
}


## Auteurs

Projet realise pour le cours de Compilation (TLC)
**ENSA Al Hoceima - 2025/2026**

Je tiens à remercier sincèrement mon encadrant Prof LASSEG Walid pour son accompagnement, ses conseils précieux et sa disponibilité tout au long de ce travail.

Par: BENZERKANE JIHANE et BIHYA HANANE
