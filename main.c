#include <stdio.h>
#include "sortLib.h"
#include "funcLib.h"

int main(int argc, char const *argv[])
{
    // int taille=17,tab[17];
    // printf("\n test ... ");
    // random_v(tab,taille);
    // printf("\n test ... ");
    // printf("\n %d",tab[0]);
    // affiche_tab(tab,taille);
    // trie_par_selection(tab,taille);
    // affiche_tab(tab,taille);

    point M[8][10];
    remplir_matrice_temp(M);
    affiche_matrice(M);
}