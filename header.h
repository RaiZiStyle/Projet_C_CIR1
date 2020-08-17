#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NB_MAX 5000

#define HAUT 1
#define DROITE 2
#define BAS 3
#define GAUCHE 4

#define NORMAL_SPEED 100000000

#define MoveCursorTo(x, y) printf("\033[%d;%dH", y + 1, x + 1)
#define SaveCursorPosition() printf("\033[s")
#define RestoreCursorPosition() printf("\033[u")

typedef struct Robot {
    int pos_x;
    int pos_y;
    int orientation;
} Robot;

char **alloc_map(int nb_colonne, int nb_ligne);
void remplissage_map(char **appart, int nb_colonne, int nb_ligne, FILE *fp, Robot *old_robot);
void affichage_map(char **appart, int nb_colonne, int nb_ligne);
void affiche_robot(Robot old_robot, Robot new_robot);

int avancer(Robot *new_robot, int pas);
int mur_test(Robot *new_robot, char **appart);
void tourne_droite(Robot *new_robot);
void tourne_gauche(Robot *new_robot);
int sortie(Robot new_robot, char **appart);

#endif
