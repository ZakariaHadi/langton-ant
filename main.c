#include "macro_fourmi.h"
#include "Macro.h"
#include "initialisation_fenetre.h"


void init_params(IlisiFourmi* Jeu)
{
    Jeu->iteration_precise=0;
        Jeu->play=0;
        Jeu->fourmi_test=0;
        Jeu->iter=0;
        Jeu->nbr_fourmi=0;
        Jeu->vitesse=100;
        Jeu->fourmis=NULL;
        return void;
}


    int main(int argc, char** argv)
{
        gtk_init(&argc, &argv);

        IlisiFourmi Jeu;
        init_params(&Jeu);
        init_interface(&Jeu);


        gtk_widget_show_all(Jeu.ma_fenetre->fenetre);
        gtk_main();
        return 0;
}


