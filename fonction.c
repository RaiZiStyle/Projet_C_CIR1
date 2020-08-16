#include "header.h"

/* ================================================= */
/*  Fonction : alloue la mémoire pour la map         */
/*                                                   */
/*  Paramèttre d'entré : -nb_colonne                 */
/*                       -nb_ligne                   */
/*                                                   */
/*  Return : la map                                  */
/* ================================================= */
char **alloc_map(int nb_colone, int nb_ligne) {
    int i;
    char **appart;
    appart = malloc(nb_ligne * sizeof(char *));
    for (i = 0; i < nb_ligne; i++) {
        appart[i] = malloc(nb_colone * sizeof(char));
    }
    return appart;
}

/* ================================================= */
/*  Fonction : Remplit la map                        */
/*             et localise le point de départ        */
/*  Paramèttre d'entré : -nb_colonne                 */
/*                       -nb_ligne                   */
/*                       -FILE *fp                   */
/*                                                   */
/*  Paramèttre d'entré/sortie :  -robot          */
/*                              -appart              */
/*  Return : rien                                    */
/* ================================================= */
void remplissage_map(char **appart, int nb_colonne, int nb_ligne, FILE *fp, Robot *robot) {
    int i, j;
    char ligne[NB_MAX];
    for (i = 0; i < nb_ligne; i++) {
        fgets(ligne, NB_MAX, fp);
        for (j = 0; j < nb_colonne; j++) {
            /* localisation du point de départ */
            if (ligne[j] == 'D') {
                robot->pos_x = j;
                robot->pos_y = i;
            }
            appart[i][j] = ligne[j];
        }
    }
}

/* ================================================= */
/*  Fonction :Affiche la map                         */
/*                                                   */
/*  Paramèttre d'entré : -nb_colonne                 */
/*                       -nb_ligne                   */
/*                                                   */
/*  Paramèttre d'entré/sortie :  -appart             */
/*                                                   */
/*  Return : rien                                    */
/* ================================================= */
void affichage_map(char **appart, int nb_colonne, int nb_ligne) {
    int i, j;
    for (i = 0; i < nb_ligne; i++) {
        for (j = 0; j < nb_colonne; j++) {
            printf("%c", appart[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* ================================================= */
/*  Fonction :Affiche le robot                       */
/*                                                   */
/*  Paramèttre d'entré : -old_robot                  */
/*                       -new_robot                  */
/*                                                   */
/*  Return : rien                                    */
/* ================================================= */
void affiche_robot(Robot old_robot, Robot new_robot) {
    SaveCursorPosition();

    // Clear l'ancienne position
    MoveCursorTo(old_robot.pos_x, old_robot.pos_y + 1);
    printf(".");

    //Affiche la nouvelle position
    MoveCursorTo(new_robot.pos_x, new_robot.pos_y + 1);
    printf("R");

    fflush(stdout);
    RestoreCursorPosition();
}

/* ================================================= */
/*  Fonction :Fait avancer le Robot                  */
/*                                                   */
/*  Paramèttre d'entré : -pas                        */
/*                                                   */
/*  Paramèttre d'entré/sortie : -new_robot           */
/*                                                   */
/*  Return : rien                                    */
/* ================================================= */
int avancer(Robot *new_robot, int pas) {
    switch (new_robot->orientation) {
        case DROITE:
            new_robot->pos_x++;
            pas++;
            break;
        case HAUT:
            new_robot->pos_y--;
            pas++;
            break;
        case GAUCHE:
            new_robot->pos_x--;
            pas++;
            break;
        case BAS:
            new_robot->pos_y++;
            pas++;
            break;
    }
    return pas;
}

/* ================================================= */
/*  Fonction :Test si il y a un mur                  */
/*                                                   */
/*  Paramèttre d'entré : -appart                     */
/*                                                   */
/*  Paramèttre d'entré/sortie : -new_robot           */
/*                                                   */
/*  Return : 1 si il y'a un mur sinon 0              */
/* ================================================= */
int mur_test(Robot *new_robot, char **appart) {
    int i = 0;
    switch (new_robot->orientation) {
        case DROITE:
            if (appart[new_robot->pos_y][new_robot->pos_x + 1] == 'x') {
                return 1;
            }
            break;
        case HAUT:
            if (appart[new_robot->pos_y - 1][new_robot->pos_x] == 'x') {
                return 1;
            }
            break;
        case GAUCHE:
            if (appart[new_robot->pos_y][new_robot->pos_x - 1] == 'x') {
                return 1;
            }
            break;
        case BAS:
            if (appart[new_robot->pos_y + 1][new_robot->pos_x] == 'x') {
                return 1;
            }
            break;
    }
    return 0;
}

/* ================================================= */
/*  Fonction :Tourne a droite                        */
/*                                                   */
/*  Paramèttre d'entré/sortie : -new_robot           */
/*                                                   */
/*  Return : rien                                    */
/* ================================================= */
void tourne_droite(Robot *new_robot) {
    new_robot->orientation++;
    if (new_robot->orientation > GAUCHE) {
        new_robot->orientation = HAUT;
    }
}

/* ================================================= */
/*  Fonction :Tourne a gauche                        */
/*                                                   */
/*  Paramèttre d'entré/sortie : -new_robot           */
/*                                                   */
/*  Return : rien                                    */
/* ================================================= */
void tourne_gauche(Robot *new_robot) {
    new_robot->orientation--;
    if (new_robot->orientation < HAUT) {
        new_robot->orientation = GAUCHE;
    }
}

/* ================================================= */
/*  Fonction :Sortie                                 */
/*                                                   */
/*  Paramèttre d'entré : -new_robot                  */
/*                       -appart                     */
/*                                                   */
/*  Return : 1 quand il a trouvée la sortie sinon 0  */
/* ================================================= */
int sortie(Robot new_robot, char **appart) {
    if (appart[new_robot.pos_y][new_robot.pos_x] == 'S') {
        return 1;
    }
    return 0;
}
