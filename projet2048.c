#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "saisieM.c"
#include "terminalCouleur.c"
#include "math.h"
#define false 0
#define true 1

typedef struct    //on définit la structure "jeu"
{
int n;
int valMax;
int nbCasesLibres;
int * grille;
}jeu;

/*#include "Partie1.h"*/

/*fonction qui initialise un jeu : alloue la grille dynamiquement et remplis les cases par 0. */
/*
 * \param p: pointeur sur une partie de 2048
 * \param n : taille de la grille
 * \param valMax : valeur à atteindre pour gagner
*/

void initialiseJeu (jeu * p, int n, int valMax)
{    
	
	p->grille = malloc(n*n*sizeof(int));  /*on alloue dynamiquement le tableau.
						 (int*) indique explicitement le type de pointeur dans lequel on stocke l'adresse de la memoire alloué */

    int i = 0;
    for (i=0; i<n*n; i++) // la boucle permettant de parcourir la grille
    {
        p->grille[i]=0;		// la valeur de la case de la grille est 0
	}
	if(p->grille==NULL)
	printf("erreur pendant l'allocation");
    
    p->n=n;
    p->valMax=valMax;
    p->nbCasesLibres=n*n;
}

 /* on libere l'espace memoire */
void libereMemoire(jeu * p)
{
free(p->grille);
}


/*vérifie si une case de coordonnée (i,j) est bien . */
/*
 * \param p : pointeur sur la partie en cours
 * \param i : entier
 * \param j : entier 
*/

int indiceValide(jeu * p,int i, int j)
{

    if(i<p->n && i>=0 && j<p->n && j>=0)  //i et j inferieur a la taille et superieur ou egal a zero
   	return 1;
   	
    else
    return 0;


}

/*récupère une valeur dans la grille.

 * \param p : pointeur sur la partie en cours
 * \param ligne : entier correspondant au numéro de ligne
 * \param colonne : entier correspondant au numéro de colonne
*/

int getVal(jeu * p, int ligne, int colonne)
{
	int num_ligne=(ligne*(p->n));   // position de la ligne
	int position =num_ligne+colonne;  // la position du la case

    	if(indiceValide(p,ligne,colonne) == 1)	// si la fonction indice valide est verifier alors...
       	return p->grille[position];		// on affiche la valeur de la position

    	else
       	return -1;

}

/*modifie la valeurs d'une cases.

 * \param p : pointeur sur la partie en cours
 * \param ligne : entier correspondant au numéro de ligne
 * \param colonne : entier correspondant au numéro de colonne
 * \param val : entier modifiant la valeur de la case ciblée
*/

void setVal(jeu * p, int ligne, int colonne, int val)
{
	int num_ligne=(ligne*(p->n));
	int position =num_ligne+colonne;

    	if(getVal(p,ligne,colonne) != -1)
			p->grille[position]=val;	//on remplace la valeur par celle placer en parametre

	
    	else
    		printf("les positions ne sont pas valides \n");
}

/*
 * \param p : pointeur sur la partie en cours
 * \param n : entier correspondant à la taille de la grille
 * \param i : iterateur
*/


/* fonction permettant de placer les "lignes" pour l'affichage */
void tiret(jeu *p)
{
	int q=0;
	while(q<p->n)
	{
		printf("------");	// on affiche les tirets qui vont servir de ligne pour le tableau
		q=q+1;

	}
		printf("-");		// ce tiret en plus est pour que la ligne soit stable pâr rapport au tableau
}


int caseVide(jeu *p,int i,int j)
{
	if(getVal(p,i,j)==0)	// si la vaeur trouve par la fonction getVal est egal a zero alors...
	return 1;
	else
	return 0;
}



void ajouteValAlea(jeu * p)
{
        
        srand(time(NULL));

	int i=0;
	i=rand()%((p->n*p->n)-1);  // i prend une valeur aleatoire entre 0 et la taille(n*n -1)
	int j=0;                 // la variable j nous servira a afficher la vauleur 2 ou 4.
	int ok=false;

	if(p->grille[i]==0)      // si on tombe directement sur une case vide
	{
		j=rand()%2;            // j devient un nombre aleatoire en 0 et 1
		if(j==0)
			p->grille[i]=2;    // on place la valeur 2 dans la case vide.
		else
		 	p->grille[i]=4;     // on place la valeur 4 dans la case vide
			
			p->nbCasesLibres--;
	}
	else
	{
	do      // tant que p->grille[i] n'est pas egal a 0
	{
		i=rand()%((p->n*p->n)-1);     // i prend à noouveau une valeur aleatoire

		if(p->grille[i]==0)
			ok=true;
		else 
			ok=false;

		if(ok)
		{

			j=rand()%2;
		

			if(j==0)
				p->grille[i]=2;
			else
		 		p->grille[i]=4;

			p->nbCasesLibres--;


		}
	
		
	}while(!ok);

}
}

void couleurNombre(int n)
{
	char espace = ' ';
	char point = '.';
	switch (n)
  {
    case 0:
    color_printf(BLACK, WHITE, "%4c%3c", point, espace);
    break;
    case 2:
       color_printf(WHITE, YELLOW, "%4d%3c", n, espace);
       break;
    case 4:
	   color_printf(WHITE, RED, "%4d%3c", n, espace);
       break;
    case 8:
       color_printf(WHITE, BLUE, "%4d%3c", n, espace);
       break;
    case 16:
       color_printf(WHITE, GREEN, "%5d%2c", n, espace);
       break;
    case 32:
       color_printf(WHITE, MAGENTA, "%4d%3c", n, espace);
       break;
    case 64:
       color_printf(WHITE, CYAN, "%4d%3c", n, espace);
       break;
    case 128:
       color_printf(WHITE, RED, "%5d%2c", n, espace);
       break;
    case 256:
       color_printf(WHITE, BLUE, "%5d%2c", n, espace);
       break;
    case 512:
       color_printf(WHITE, GREEN, "%5d%2c", n, espace);
       break;
    case 1024:
       color_printf(RED, MAGENTA, "%6d%c", n, espace);
       break;
    case 2048:
       color_printf(RED, CYAN, "%5d%2c", n, espace);
       break;
    case 4096:
       color_printf(GREEN, RED, "%5d%2c", n, espace);
       break;
    default:
	   color_printf(WHITE, BLACK, "%4d%2c", n, espace);
       break;
  }
}

void couleurLigne(int n)
{
	char espace = ' ';
	switch (n)
  {
    case 0:
       color_printf(BLACK, WHITE, "%7c", espace);
       break;
    case 2:
       color_printf(BLACK, YELLOW, "%7c", espace);
       break;
    case 4:
	   color_printf(YELLOW, RED, "%7c", espace);
       break;
    case 8:
       color_printf(WHITE, BLUE, "%7c", espace);
       break;
    case 16:
       color_printf(WHITE, GREEN, "%7c", espace);
       break;
    case 32:
       color_printf(WHITE, MAGENTA, "%7c", espace);
       break;
    case 64:
       color_printf(WHITE, CYAN, "%7c", espace);
       break;
    case 128:
       color_printf(WHITE, RED, "%7c", espace);
       break;
    case 256:
       color_printf(WHITE, BLUE, "%7c", espace);
       break;
    case 512:
       color_printf(WHITE, GREEN, "%7c", espace);
       break;
    case 1024:
       color_printf(WHITE, MAGENTA, "%7c", espace);
       break;
    case 2048:
       color_printf(RED, CYAN, "%7c", espace);
       break;
    case 4096:
       color_printf(GREEN, RED, "%7c", espace);
       break;
    default:
	   color_printf(WHITE, BLACK, "%7c", espace);
       break;
  }
}



void affichage(jeu * p)
{

	int i = 0;
	int j = 0;
	int n = p->n;
	
	
	
	while (i < (n*n)) // Tant que i est inferieur au nombre de cases du tableau
		{

			for (j=0; j<n; j++) // Tant que j est inferieur au nombre de colonnes
				{
					int g = p->grille[i];
					couleurLigne(g);
					i++;
				}
			i = i - j;
			printf("\n");
			for (j=0; j<n; j++)
				{
					int g = p->grille[i];
					couleurNombre(g);
					i++;
				}
			i = i - j;
			printf("\n");
			for (j=0; j<n; j++)
				{
					int g = p->grille[i];
					couleurLigne(g);
					i++;
				}
			printf("\n");
		}
		printf("\n");
					
	
}

/*
 * \param p: pointeur sur une partie de 2048
 * \param i : entier
 * \param j : entier
*/


/*
 * \param p: pointeur sur une partie de 2048
 * \param i : iterateur
*/
int gagne(jeu * p)
{
int i=0;

    for (i=0 ; i < (p->n*p->n) ; i++)		//Parcourt les cases du tableau
    {
        if (p->grille[i] >= p->valMax)		// si la valeur d'une case de la grille est supèrieur à la valeur "valMax" que l'on a taper.
        return 1;
    }
return 0;
}

/*
 * \param p: pointeur sur une partie de 2048
 * \param i : iterateur
*/

int perdu (jeu *p)
 {
  int i=0;
  int j=0;

  for(i=0; i< p->n -1; i++) //Parcourt les lignes 
   {
	for(j=0; j< p->n -1; j++)	//Parcourt les colonnes
	 {
		if(p->grille[i*(p->n)+j] 
		== p->grille[i*(p->n)+j+1] 
		|| p->grille[i*(p->n)+j] 
		== p->grille[(i+1)*(p->n)+j] 
		|| caseVide(p, i, j)==1)  // Si deux cases de meme valeurs peuvent s'additionner ou si il y'a encore des cases vides, le jeu continue.
		return 0;
	 }
   }
 return 1;
 }

/*
    déplace toute les valeurs de la grille non vides horizontalement(droite ou gauche).
*/
int mouvementLigne(jeu * p,int ligne,int direction)
{
    int i=0;
    int nb_gauche=0;
    int nb_droite=0;
    int pos=ligne * (p->n);
    int j=0;
    int changement=0;

    if(direction==-1) //Pour deplacer les cases à droite
    {
           while(i<p->n) // On parcourt les lignes
           {
  				j=pos + p->n -1;   //on definit j comme étant la derniere case

           		while(j>pos)		// Permet de se déplacer sur toutes les cases
           		{
           			if(p->grille[j]==0 && p->grille[j-1]!=0)      
           			{
           			p->grille[j]= p->grille[j-1];				//remplace le 0 de droite avec le nombre de gauche
           			p->grille[j-1]=0;
           			nb_droite++;
           			}
						if(p->grille[j]==p->grille[j-1] && changement<(p->n/2))
           			{
           			p->grille[j]= p->grille[j-1]+p->grille[j];		//addition des cases adjacentes de meme valeur
           			p->grille[j-1]=0;
           			changement++;

					p->nbCasesLibres++;
           			}
           			j--;       //j se deplace d'une case à gauche
           		}
			changement=0;
           	i++;		
           }

    }

	if(direction==1)  //Pour deplacer les cases à gauche
	{
		while(i<p->n) // On parcourt les lignes
           {
  				j=pos + p->n -1;  //on definit j comme étant la derniere case

           		while(j>pos) // On parcourt les lignes
           		{
           			if(p->grille[j]!=0 && p->grille[j-1]==0)   
           			{
           			p->grille[j-1]= p->grille[j];                     //remplace le 0 de gauche avec le nombre de droite
           			p->grille[j]=0;
           			nb_gauche++;
           			}
           				if(p->grille[j-1]==p->grille[j] && changement<(p->n/2))
           			{
           			p->grille[j-1]= p->grille[j-1]+p->grille[j];		//addition des cases adjacentes de meme valeur
           			p->grille[j]=0;
           			changement++;

					p->nbCasesLibres++;
           			}

           			j--;		 //j se deplace d'une case à gauche
           		}
			changement=0;
           	i++;
           }
	}

	return(nb_gauche>0 || nb_droite>0);	// s'il y'a eu un deplacement retourne 1
}

int mouvementLignes(jeu * p, int direction) //Permet de d'effectuer mouvement ligne dans toute les lignes
{
	int i=0;
	int ligne=0;

		while(i<(p->n))  // On parcourt les lignes
		{
		mouvementLigne(p,ligne,direction); //effectue le deplacement dans la direction voulue( d ou g)
		ligne++;
		i++;
		}

	return(mouvementLigne(p,ligne,direction)); //s'il y'a eu un mouvement dans les lignes
}

int mouvementColonne(jeu * p,int colonne,int direction)
{

	int i=0;
	int nb_haut=0;
	int nb_bas=0;
	int pos=colonne * (p->n);
	int k=0;
	int changement=0;

/*if(direction==1)  //Pour deplacer les cases en haut
{
		while(i<p->n) // On parcourt les lignes
		{
			k=colonne;  //parcourir les colonnes

			while(k< (p->n* p->n)- p->n) // Pour eviter d'echanger deux fois les memes cases
			{
				if(p->grille[k]==0 && p->grille[k+p->n]!=0)  
				{
				p->grille[k]=p->grille[k+p->n];   //remplace le 0 du haut avec le nombre du bas
				p->grille[k+p->n]=0;
				nb_haut++;
				}
				if(p->grille[k]==p->grille[k+p->n] && changement<(p->n/2))
				{
				p->grille[k]=p->grille[k+p->n]+p->grille[k];
				p->grille[k+p->n]=0;
				changement++;

				p->nbCasesLibres++;
				}
				k=k+p->n;

			}
			changement=0;
			i++; 
		}
}
if(direction==-1)  //Pour deplacer les cases en bas
{
	while(i<p->n) // On parcourt les lignes
		{
			k=colonne;
			while(k< (p->n* p->n)- p->n) // eviter d'echanger deux fois les memes cases
			{
				if(p->grille[k]!=0 && p->grille[k+p->n]==0)
				{
				p->grille[k+p->n]=p->grille[k];  //remplace le 0 du bas avec le nombre du haut
				p->grille[k]=0;
				nb_bas++;
				}
				if(p->grille[k]==p->grille[k+p->n] && changement<(p->n/2))
				{
				p->grille[k+p->n]=p->grille[k]+p->grille[k+p->n];
				p->grille[k]=0;
				changement++;

				p->nbCasesLibres++;
				}
				k=k+p->n;

			}
			changement=0;
			i++;
		}
}*/
	if(direction==1) //Pour deplacer les cases en haut
    {
           while(i<p->n) // On parcourt les lignes
           {
  				k=colonne;   //on definit k comme étant la derniere case

           		while(k<(p->n* p->n)- p->n)		// Permet de se déplacer sur toutes les cases
           		{
           			if(p->grille[k]==0 && p->grille[k+p->n]!=0)      
           			{
	           			p->grille[k]= p->grille[k+p->n];	//remplace le 0 du haut avec le nombre en pos
	           			p->grille[k+p->n]=0;
	           			nb_haut++;
           			}
						
					if(p->grille[k]==p->grille[k+p->n] && changement<(p->n/2))
					{
						p->grille[k]=p->grille[k+p->n]+p->grille[k];
						p->grille[k+p->n]=0;
						changement++;
						nb_haut++;

					p->nbCasesLibres++;
           			}
           			k--;       //k se deplace d'une case en haut
           		}
			changement=0;
           	i++;		
           }

    }

	if(direction==-1)  //Pour deplacer les cases en bas
	{
		while(i<p->n) // On parcourt les lignes
           {
  				k=colonne;  //on definit k comme étant la derniere case

           		while(k< (p->n* p->n)- p->n) // eviter d'echanger deux fois les memes cases
			{
				if(p->grille[k]!=0 && p->grille[k+p->n]==0)
				{
				p->grille[k+p->n]=p->grille[k];  //remplace le 0 du bas avec le nombre du haut
				p->grille[k]=0;
				nb_bas++;
				}
				if(p->grille[k]==p->grille[k+p->n] && changement<(p->n/2))
				{
				p->grille[k+p->n]=p->grille[k]+p->grille[k+p->n];
				p->grille[k]=0;
				changement++;
				nb_bas++;

				p->nbCasesLibres++;
				}
				k=k+p->n;

			}
			changement=0;
			i++;
		}
	}


	return(nb_haut>0 || nb_bas>0);	//s'il y'a eu un déplacement retourne 1
}

 int mouvementColonnes(jeu * p,int direction)
{
	int i=0;
	int colonne=0;

		while(i<(p->n))
		{
			mouvementColonne(p,colonne,direction);	//effectue le deplacement dans la direction voulue(h ou b)
			colonne++;
			i++;
		}

	return (mouvementColonne(p,colonne,direction)); //s'il y'a eu un mouvement dans les colonnes retourne 1

}


int mouvement(jeu * p, int direction)
{
    
    switch(direction)
	{
	case 0 : return mouvementColonnes(p,-1);
	case 1 : return mouvementLignes(p,-1);
    case 2 : return mouvementColonnes(p,1); 
  	case 3 : return mouvementLignes(p,1);  

	default: return 0;
	}
       
}



int saisieD()
{
	
	
	//Debut du mode saisie des fleches ou de la touche Echap sans appuyer sur entrÃ©e pour valider
	debutTerminalSansR();

	Key touche;//Definition d'une touche

	touche = lectureFleche();//On lit une fleche (ou la touche echap)

	while ( touche != KEY_ESCAPE)//Tant que l'on n'a pas appuye sur la touche echap
	{
		//On affiche quelle fleche a ete saisie
		if (touche == KEY_UP)
			return 2;
			
		else if (touche == KEY_DOWN)
			return 0;
			
		else if (touche == KEY_LEFT)
			return 3;
			
		else if (touche == KEY_RIGHT)
			return 1;
			
		else //touche vaut la valeur NO_KEY
			printf("Pas de fleche saisie");
		printf("\n");

		touche = lectureFleche();//On lit une fleche (ou la touche echap)

	}
	return -1;

}

int finPartie(jeu * p)
{
    return(gagne(p) || perdu(p));
}

int jouer(jeu * p)
{
        	
        	int i;
		int a;
		int b;
        	
    do    //si la partie n'est pas encore gagné ou perdu 
    {
	a=saisieD();
	finTerminalSansR();

        if(a == -1)// la touche saisie est "echap" 
        {
        clear_terminal();
		return 0;
        }
		
		b = mouvement(p,a); 	
				
		if(b!= 0 && p->nbCasesLibres > 0) // s'il y'a eu un mouvement apres la saisie ajoute une valeur aléatoire
			ajouteValAlea(p);
            
		clear_terminal();	
        affichage(p);

    }while (!finPartie(p) || a!=-1);

    if (gagne(p)==1)
   		printf("\t\t vous avez gagnee !!! :) \n\n");
	else if(perdu(p))
		printf("\t\t vous avez perdu !!! :( \n\n");
	return 1;
}

/*int sauvegarde(jeu * p)
{

int i,j;
int taille=(p->n*p->n);
int valMax;
int nb;


    FILE *f;
	f=fopen("sauvegarde.txt","wt");
    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return 0;
    }
    fprintf(f,"%d  %d ",p->n,p->valMax);
    fprintf(f,"%d ",p->nbCasesLibres);
    for(i = 0 ; i < p->n ; i++)
    {
        for(j = 0 ; j < p->n ; j++)
        {
            fprintf(f,"%d\t\t\t",getVal(p,i,j));
        }
    }
    fclose(f);
    return 1;    
}

int chargement(jeu * p)
{
int i,j;
int nb;  
int taille=(p->n*p->n);
    

    FILE * f; 
	f= fopen("sauvegarde.txt","rt");
    if(f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return 0;
    }
	fscanf(f,"%d ",&p->n);
	fscanf(f,"%d ",&p->valMax);
    initialiseJeu(p,p->n,p->valMax);
    
    fscanf(f,"%d ",&p->nbCasesLibres);

   for(i = 0 ; i < p->n ; i++)
    {
        for(j = 0 ; j < p->n ; j++)
        {
            fscanf(f,"%d",&nb);
            setVal(p,i,j,nb);
        }
    }
    
    fclose(f);
    return 1;
}*/

int menu()
{
    int a = 0;
    printf(" 1 - Jouer\n 2 - Sauvegarder\n 3 - Charger\n 4 - Quitter");

    do{
	scanf("%d",&a);		//demander à l'utilisateur de saisir son choix tant qu'il n'est pas compris par le programme
	
		switch(a)
		{
			case 1: return 1;
			case 2: return 2;
			case 3: return 3;
			case 4: return 4;
			default: "Cette option n'est pas possible";
		}

	}while(a!=1 && a!=2 && a!=3 && a!=4);

}


int main() 
{
    clear_terminal();
	jeu d;
	jeu *p=NULL;
	
	int a;
	int x = menu();
	int N;
	int ok=false;

	p=&d;
	
	while(x!= 4)
	{
	    if(x == 1)
	    {
		printf("\n\n*INSTRUCTION*\n\n Utilisez les touches haut, bas, droite et gauche pour deplacer les cases respectivement vers le haut, vers la gauche, vers le bas ou vers la droite et echap pour arreter le jeu :\n\n");
    	printf("saisir la taille du tableau: ");// le joueur rentre la taille de la grille.
		scanf("%d",&p->n);
		while(p->n<= 1)
    	           {
    		            printf("Entrer une valeur comprise entre 1 et 9999: \n");
    		            scanf("%d",&p->n);
    	           }
		
		do
		{
		ok=true;
		printf("saisir la valeur a atteindre pour gagner: ");
		scanf("%d",&p->valMax);

		if(p->valMax%2!=0 || p->valMax>4096){
		printf("il faut saisir un nombre multiple de 2 et infèrieur à 4096!! : ");
		ok=false;
		}

		}while(!ok);
     
	 	initialiseJeu(p,p->n,p->valMax);
		ajouteValAlea(p);
		clear_terminal();
		affichage(p);
		jouer(p);
		}
		/*else if(x == 2)	// on sauvegarde
		sauvegarde(p);
		clear_terminal;
		printf("\t\t\tPARTIE SAUVEGARDÉE");
		if(x == 3)
		{// on charge et on joue
		chargement(p);
		clear_terminal();
		affichage(p);
		jouer(p);
		}*/
	x = menu();
	}
                clear_terminal();
                libereMemoire(p);  // libere la memoire occupé par la grille

	return 0;
}