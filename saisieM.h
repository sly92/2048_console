#ifndef SAISIE_M_H
#define SAISIE_M_H



/*
 * Touches du clavier correspondant aux flÃ¨ches (haut, bas, gauche, droite) + touche echap + autre touche
 */ 
typedef enum
{
	NO_KEY,
	KEY_ESCAPE,
	KEY_UP,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT
} Key;

/*
 * DÃ©but du mode saisie "sans retour chariot" : 
 * Il n'est pas nÃ©cessaire d'appuyer sur la touche entrÃ©e pour saisir une valeur.
 * La valeur saisie ne s'affiche pas.
 */
int debutTerminalSansR();

/*
 * Fin du mode saisie "sans retour chariot" : on revient Ã  la normale
 */
void finTerminalSansR();

/*
 * Lecture d'une touche. La fonction renvoie :
 *   - KEY_UP, KEY_DOWN, KEY_LEFT ou KEY_RIGHT si l'utilisateur appuie sur une des flÃ¨ches
 *   - KEY_ESCAPE si l'utilisateur appuie sur la touche Echap
 *   - NO_KEY si l'utilisateur appuie sur une autre touche
 */
Key lectureFleche();


#endif