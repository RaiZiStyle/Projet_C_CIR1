#include "header.h"

int main(int argc, char **argv) {
    /* Déclaration des variables */
    FILE *fp = NULL;
    int nb_ligne, nb_colonne, nb_pas = 0;
    char **appart;  //Tableau en 2 dimensions
    Robot new_robot, old_robot;
    old_robot.orientation, new_robot.orientation = GAUCHE;

    if (argc != 2) {
        printf("Erreur, veuillez rentrez 2 arguments \n");
        return -1;
    }

    /* ouverture du fichier */
    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("Erreur dans l'ouverture du fichier\n");
    }

    /* récuperation de la longueur & largeur de la map */
    fscanf(fp, "%d:%d\n", &nb_colonne, &nb_ligne);

    /* allocation de la mémoire pour appart */
    appart = alloc_map(nb_colonne, nb_ligne);

    remplissage_map(appart, nb_colonne, nb_ligne, fp, &new_robot);
    affichage_map(appart, nb_colonne, nb_ligne);
    printf("robot.x : %d , robot.y : %d \n", new_robot.pos_x, new_robot.pos_y);
    old_robot = new_robot;
    nb_pas = avancer(&new_robot, nb_pas);
    usleep(NORMAL_SPEED);
    affiche_robot(old_robot, new_robot);
    old_robot = new_robot;
    nb_pas = avancer(&new_robot, nb_pas);
    usleep(NORMAL_SPEED);
    affiche_robot(old_robot, new_robot);
    old_robot = new_robot;
    nb_pas = avancer(&new_robot, nb_pas);
    usleep(NORMAL_SPEED);
    affiche_robot(old_robot, new_robot);
    old_robot = new_robot;

    // tout droit tant qu'il n'y a pas de mur
    // while (!mur_test(&new_robot, appart)) {
    //     old_robot = new_robot;
    //     nb_pas = avancer(&new_robot, nb_pas);
    //     affiche_robot(old_robot, new_robot);
    //     usleep(NORMAL_SPEED);
    // }

    // while (1) {
    //     if (mur_test(&new_robot, appart)) {
    //         tourne_gauche(&new_robot);
    //     } else {
    //         old_robot = new_robot;
    //         nb_pas = avancer(&new_robot, nb_pas);
    //         tourne_droite(&new_robot);
    //         affiche_robot(old_robot, new_robot);
    //         if (sortie(new_robot, appart)) {
    //             printf("\nLe Robot a trouvé la sortie\n");
    //             break;
    //         }
    //         usleep(NORMAL_SPEED);
    //     }
    //     printf("Le nombre de pas du Robot est :%d\r", nb_pas);
    // }

    fclose(fp);
    return 0;
}
