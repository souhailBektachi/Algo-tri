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
// ----------------------------------------------------------------------------------------
void trie_a_bul(int *tab,int taille)
{
   int i,j,temp,m;
   do{
    m=0;
   for(i=0;i<taille-1;i++)
   {
    if(tab[i+1]<tab[i])
    {
      temp=tab[i];
      tab[i]=tab[i+1];
      tab[i+1]=temp;
      m=1;
    }
   }
   }while(m!=0);
}
// ----------------------------------------------------------------------------------------

// Fonction qui mesure le temps d'exécution d'une autre fonction
double mesureTemps(void (*fonction)(),int taille,int *tab) 
{
    // int *tab;
    // tab=(int*)malloc(taille*sizeof(int));

    clock_t start, end;
    double cpu_time_used;

    // Enregistrez le moment où vous démarrez la mesure du temps
    start = clock();

    // Appelez la fonction dont vous souhaitez mesurer le temps
    fonction(tab,taille);
    // Enregistrez le moment où la fonction a terminé
    end = clock();
    // Calculez le temps d'exécution en secondes
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}
// ----------------------------------------------------------------------------------------
void func()
{
    int i,j=0;
    for(i=0;i<1000000;i++){j*=j;}
}
// ----------------------------------------------------------------------------------------
void remplir_matrice_temp(double M[2][10])
{
    int i,j,taille=1000,*tab;
    double t;
    tab=(int*)malloc(taille*sizeof(int));
    random_v(tab,taille);
    for(i=0;i<10;i++)
    {
            M[0][i]=mesureTemps(trie_a_bul,taille,tab);
            M[1][i]=mesureTemps(trie_par_selection,taille,tab);
            taille+=3000;
            tab=(int*)realloc(tab, taille * sizeof(int));
            random_v(tab,taille);
    }
}
// ----------------------------------------------------------------------------------------
void affiche_matrice(double M[2][10])
{
    int i,j,taille=1000;
    for(i=0;i<2;i++)
    {
        printf("\n");
        for(j=0;j<10;j++)
        {
            printf("   %lf",M[i][j]);
        }
    }

}