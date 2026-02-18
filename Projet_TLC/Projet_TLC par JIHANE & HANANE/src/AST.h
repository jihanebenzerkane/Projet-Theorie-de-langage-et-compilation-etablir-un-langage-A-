#ifndef AST_H
#define AST_H
// les types de noeuds
typedef enum {
  NODE_PROG,       
  NODE_DEC,        
  NODE_ALPHABET,   
  NODE_ETATS,     
  NODE_INIT,       
  NODE_FINAUX,     
  NODE_TRANS,      
  NODE_TRANS_LIST, 
  NODE_MOTS,       
  NODE_VERIF,      // commande verifier
  NODE_CHAINE,    
  NODE_SYMBOLE,   
  NODE_IDENT      
} NodeType;

// la structure du noeud
typedef struct ast {
 NodeType type;      
 char* val;           
 char c;              
 struct ast* gauche;  
 struct ast* droite;  
} AST;

// les fonctions pour l'arbre
AST* creer_noeud(NodeType type, char* val, char c);  // fontion pour fer un nouveau noeud
AST* ajoute_fils(AST* p, AST* e);  // on rajoute un fils
AST* ajoute_frere(AST* a, AST* b);  // on rajoute un frere

#endif
