#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

void trie_par_selection(int *tab,int taille);
void trie_a_bul(int *tab,int taille);
void affiche_tab(int *tab,int taille);
void random_v(int *tab,int taille);
double mesureTemps(void (*fonction)(),int taille,int *tab );
void func();
void remplir_matrice_temp(double M[2][10]);
void affiche_matrice(double M[2][10]);

