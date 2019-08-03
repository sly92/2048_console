#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <termios.h>
#include <unistd.h>

// Couleurs du terminal
  typedef enum
  {
    /*256*/BLACK,
    /*32*/RED,
    /*8*/GREEN,
    /*16*/YELLOW,
    /*128*/BLUE,
    /*64*/MAGENTA,
    /*4*/CYAN,
    /*2*/WHITE
  } COULEUR_TERMINAL;


/*
 * Fonction effacant le terminal
 */
void clear_terminal();

/*
 * Printf en couleur. Les deux premiers paramètres sont les couleurs d'écriture et de fond (mettre une des valeurs parmi : 
 * BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN et WHITE).
 * Les parmètres suivants sont comme le printf "normal" : chaine de format puis toutes les valeurs à  afficher
 */
int color_printf(COULEUR_TERMINAL fg, COULEUR_TERMINAL bg, const char * format, ...);