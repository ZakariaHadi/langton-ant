#ifndef STRUCTURES_FOURMI_H_INCLUDED
#define STRUCTURES_FOURMI_H_INCLUDED

#include <cairo.h>
#include "struct_macro.h"

typedef struct
{
    int x;
    int y;
}pos;


typedef struct fourmi_info
{
  pos pos_fourmi;  // la position de fourmi
  short int direction; // contient la direction de fourmi
                // 1: Haut  2: Droite  3: Bas  4: Gauche
  struct fourmi_info *suiv;
}fourmi_info;

typedef struct
{
    GtkWidget *zone_dessinable; // notre zone qui contient le grid
    char grid[120][200];//tableau de deux dimentions contient les informations sur le grid
                // chaque case correspond a une cellule dans le grid
                // 'N' : la cellule est Noire
                // 'B' : la cellule est blanche
                // 'F' : elle contient la fourmi
    int case_taille; // la taille de chaque cellule
    int debut_ligne; //l indice du debut des lignes qu'on affiche dans le grid
    int fin_ligne; //l indice de fin des lignes qu'on affiche dans le grid
    int debut_coll;  //l indice du debut des colonnes qu'on affiche dans le grid
    int fin_coll;  // l indice de fin des colonnes qu'on affiche dans le grid

}Grid;

typedef struct
{
    fourmi_info *fourmis; /**structure qui contient les infos de la fourmi*/
    short int nbr_fourmi;/** indique le nbr des fourmis dans le jeu*/
    Grid grid_zone; /**la structure de la grille*/
    Fenetre *ma_fenetre; /**la fenetre du jeu*/
    Toolbar toolbar;/**la barre des outils*/
    Statubare statu;/** la barre du statuu*/
    Scale Echelle; /**l'echelle de la vitesse*/
    int iter;    /** numero d'iteration*/
    int vitesse;  /** la vitesse de la fourmi*/
    GdkRGBA fourmi_couleur; /** la couleur de la fourmi */
    GdkRGBA fourmi_couleur1; /** la couleur de la fourmi */
    guint a;   /** indicateur de la fct qui tourne le jeu.*/
    short int fourmi_test,play; /** indicateur si le jeu est demarré ou non (play or pause)*/
    int iteration_precise; /** pour indiquer une iteration precise.*/
}IlisiFourmi;






#endif // STRUCTURES_FOURMI_H_INCLUDED
