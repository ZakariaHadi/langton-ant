#ifndef INITIALISATION_FENETRE_H_INCLUDED
#define INITIALISATION_FENETRE_H_INCLUDED

#include "macro_fourmi.h"
#include "Macro.h"

void QUITTER(GtkWidget *widget,gpointer data)
{
    gtk_widget_destroy(widget);
    system(".\\bin\\Debug\\menu.exe");
}
void init_interface(IlisiFourmi *Jeu)
{

          initialiser_grid_dessinable(&Jeu->grid_zone,30,50,20);
          Taille taille;
          taille.hauteur=600;
          taille.largeur=1000;

          Jeu->ma_fenetre=Creer_fenetre("fourmi",taille,0);

          Box *Hboite=creer_box(HORIZONTAL),*Vboite=creer_box(VERTICAL),*Vboite1=creer_box(VERTICAL);
          //*****************LE MENU***********
          Le_Menu menuu;
          creer_Menu(&menuu,Jeu);
          /*************barre d outils*************/
           creer_toolbar((IlisiFourmi*)Jeu);

          /*********** Statu barre *********/

           Jeu->statu.statubare=gtk_statusbar_new ();
           int id = gtk_statusbar_get_context_id (GTK_STATUSBAR(Jeu->statu.statubare), "iteration");
           gtk_statusbar_push (GTK_STATUSBAR(Jeu->statu.statubare), id, "iteration : 0");

         /********scrolled bar (les informations de jeu)************/
         ScrollBar *S=init_scrolled_window();
         creer_scrollBar(S);

         GtkWidget *label=gtk_label_new("Placer Fourmi ");
         gtk_widget_set_size_request(label,10,50);
         ajouter_element_box(Vboite1->Box,label,1,0,0,0);
         Bouton *boutton_fourmi=creer_simple_boutton(taille,1,".\\images\\fourmi.png");
         g_signal_connect(boutton_fourmi->Bouton,"clicked",G_CALLBACK(Placer_fourmi),Jeu);
         ajouter_element_box(Vboite1->Box,boutton_fourmi->Bouton,1,0,0,0);

         Bouton *boutton_supp_fourmi=creer_simple_boutton(taille,1,".\\images\\no_fourmi.png");
         g_signal_connect(boutton_supp_fourmi->Bouton,"clicked",G_CALLBACK(supp_fourmi),Jeu);
         ajouter_element_box(Vboite1->Box,boutton_supp_fourmi->Bouton,1,0,0,20);

         label=gtk_label_new("Vitesse");
         gtk_widget_set_size_request(label,10,50);
         ajouter_element_box(Vboite1->Box,label,1,0,0,0);

         creer_echelle(Jeu,1,1000,10,500);

         ajouter_element_box(Vboite1->Box,Jeu->Echelle.scale,1,0,0,0);

         label=gtk_label_new("   preciser \nune iteration");
         gtk_widget_set_size_request(label,10,50);
         ajouter_element_box(Vboite1->Box,label,1,0,0,0);

         zoneSaisi *nvzone=initialiser_entry();
         creer_entry(nvzone);
         g_signal_connect(nvzone->zone,"activate",G_CALLBACK(aller_iteration),Jeu);
         ajouter_element_box(Vboite1->Box,nvzone->zone,1,0,0,0);

         label=gtk_label_new("\tchanger \nla couleur de fourmi");
         gtk_widget_set_size_request(label,10,50);
         ajouter_element_box(Vboite1->Box,label,1,0,0,0);
        /*********definition des couleurs initiales*************/
         Jeu->fourmi_couleur.green=1;
         Jeu->fourmi_couleur.red=0;
         Jeu->fourmi_couleur.blue=0;
         Jeu->fourmi_couleur1.green=0;
         Jeu->fourmi_couleur1.red=1;
         Jeu->fourmi_couleur1.blue=0;
         GtkWidget *couleur_boutton=gtk_color_button_new_with_rgba(&Jeu->fourmi_couleur);
         gtk_widget_set_size_request(couleur_boutton,100,20);
         g_signal_connect(couleur_boutton,"color-set",G_CALLBACK(couleur_fourmi),Jeu);
         ajouter_element_box(Vboite1->Box,couleur_boutton,1,0,0,0);

         GtkWidget *couleur_boutton1=gtk_color_button_new_with_rgba(&Jeu->fourmi_couleur1);
         gtk_widget_set_size_request(couleur_boutton1,100,20);
         g_signal_connect(couleur_boutton1,"color-set",G_CALLBACK(couleur_fourmi),Jeu);
         ajouter_element_box(Vboite1->Box,couleur_boutton1,1,0,0,0);

         GtkWidget *Fixed=gtk_fixed_new();
         //****************L'IMAGE***********
         Image *image=initialiser_image();
         image->chemin=".\\images\\nature.jpg";
         creer_image(image);

         gtk_fixed_put(Fixed,image->Image,0,0);
         gtk_fixed_put(Fixed,Vboite1->Box,5,11);

         //associer_element_scroll(S,Vboite1->Box);
         associer_element_scroll(S,Fixed);

          ajouter_element_box(Vboite->Box,Jeu->toolbar.toolbar,1,1,1,0);
          ajouter_element_box(Vboite->Box,Jeu->grid_zone.zone_dessinable,1,1,1,0);
          ajouter_element_box(Vboite->Box,Jeu->statu.statubare,1,1,1,0);

          ajouter_element_box(Hboite->Box,S->sw,1,1,1,0);
          ajouter_element_box(Hboite->Box,Vboite->Box,1,1,1,0);
          ajouter_element_box(Jeu->ma_fenetre->fBox,Hboite->Box,1,1,1,0);

          gtk_container_add(GTK_CONTAINER(Jeu->ma_fenetre->fenetre),Jeu->ma_fenetre->fBox);
          gtk_widget_add_events(Jeu->grid_zone.zone_dessinable, GDK_BUTTON_PRESS_MASK);

        g_signal_connect(G_OBJECT(Jeu->grid_zone.zone_dessinable), "draw",
                     G_CALLBACK(on_draw_event), Jeu);
        g_signal_connect(Jeu->grid_zone.zone_dessinable, "button-press-event",
                     G_CALLBACK(sourie_clicked), Jeu);
                     g_signal_connect(Jeu->ma_fenetre->fenetre, "delete-event",
                     G_CALLBACK(QUITTER), NULL);
                     gtk_widget_show_all(Jeu->ma_fenetre->fenetre);

}

#endif // INITIALISATION_FENETRE_H_INCLUDED
