#include"algo_trie.h"
// trie par selection 
void  trie_par_selection(int *tab,int taille)
{
   int i,j,temp,i_min;
   for (i=0;i<=taille-2;i++)
   {
    i_min=i;
     for(j=i+1;j<taille;j++)
     {
        if (tab[j]<tab[i_min])
            i_min=j;
     }
    temp=tab[i];
    tab[i]=tab[i_min];
    tab[i_min]=temp;
   }
}

void affiche_tab(int *tab,int taille)
{
   int i;
   printf("\n (");
   for( i=0;i<taille; i++)
   {
       printf(" %d,",tab[i]);
   }
   printf(" /)");
}
void random_v(int *tab,int taille)
{
    int i;
    for(i=0;i<taille;i++)
    {
        tab[i]=rand() %100;
    }
}