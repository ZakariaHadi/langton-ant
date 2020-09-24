#ifndef MACRO_FOURMI_H_INCLUDED
#define MACRO_FOURMI_H_INCLUDED


#include "structures_fourmi.h"


static gboolean on_draw_event(GtkWidget *widget,cairo_t *cr,IlisiFourmi *jeu);

void initialiser_grid_dessinable(Grid *zone,int lignes, int collones , int case_taille)
{
    for(int ind=0;ind<120;ind++)
        for(int jnd=0;jnd<200;jnd++) zone->grid[ind][jnd]='B';//les cellules sont toutes blanches au premiers temps

    //creation de la zone dessinable du grid
            zone->zone_dessinable=gtk_drawing_area_new();
            gtk_widget_set_size_request(GTK_DRAWING_AREA(zone->zone_dessinable), collones*case_taille, lignes*case_taille);

            zone->debut_coll=75;//l indice correspond au collone du debut de notre grid
            zone->fin_coll=125; // l'indice correspond au collone fin de notre grid dessinable
            zone->debut_ligne=45; // l indice correspond au ligne du debut
            zone->fin_ligne=75;   // l indice correspond au ligne du fin
            zone->case_taille=case_taille; // la taille de chaque case du grid
            return ;
}

static gboolean on_draw_event(GtkWidget *widget,cairo_t *cr,IlisiFourmi *jeu)
{
     dessiner_grid(&jeu->grid_zone,cr,jeu);
    return FALSE;
//    do_drawing(cr);
}
/**********************************************************
Nom de la fonction : dessiner_grid
Entreés : la grille complete
          un pointeur (cairo) qui dessine sur la zone
          la variable Jeu de type IlisiFourmi qui contient touts les infos du jeu
Sorties : pas de sortie
But  : dessiner la zone en suivant les informations qui ont été remplies dans la grille logique
************************************************************/
void dessiner_grid(Grid *zone,cairo_t *cr,IlisiFourmi *Jeu)
{
    /**definir la largeur et la hauteur complete de la grille*/
    int largeur = (zone->fin_coll - zone->debut_coll) * zone->case_taille;
    int hauteur = (zone->fin_ligne - zone->debut_ligne) * zone->case_taille;
    int ind1=0,ind2=0;
    /**coulorer la grille au debut par le blanc */
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, 0, 0,largeur,hauteur);
    cairo_fill(cr);

    for(int i=zone->debut_ligne; i<zone->fin_ligne;i++)
    { ind1=0;
        for(int j=zone->debut_coll;j<zone->fin_coll;j++)
        {
            if(zone->grid[i][j]=='N')//selectionner la couleur noire
            cairo_set_source_rgb(cr, 0, 0, 0);
            //selectionner la couleur blanche
            else if (zone->grid[i][j]=='B') cairo_set_source_rgb(cr, 1, 1, 1);
            /**dessiner un rectangle d'une cellule */
            cairo_rectangle(cr, ind1*zone->case_taille+ 1, ind2*zone->case_taille+ 1,
                            zone->case_taille-1, zone->case_taille-1);
            cairo_fill(cr);
            ind1++;
         }
         ind2++;
    }
    if(Jeu->nbr_fourmi)
    {
    /*********dessiner la/les fourmi**********/
    cairo_set_source_rgb(cr, Jeu->fourmi_couleur.red, Jeu->fourmi_couleur.green, Jeu->fourmi_couleur.blue);
int ind=0;
    fourmi_info *crt=Jeu->fourmis;
    while(crt)
    {
         if(!ind) {
                cairo_set_source_rgb(cr, Jeu->fourmi_couleur.red, Jeu->fourmi_couleur.green, Jeu->fourmi_couleur.blue);
         ind++;
         }
         else  cairo_set_source_rgb(cr, Jeu->fourmi_couleur1.red, Jeu->fourmi_couleur1.green, Jeu->fourmi_couleur1.blue);
    cairo_rectangle(
                    cr, ((crt->pos_fourmi.x - zone->debut_coll) * zone->case_taille)+1,
                        ((crt->pos_fourmi.y-zone->debut_ligne) * zone->case_taille) +1,
                        zone->case_taille-1, zone->case_taille-1
                   );
    cairo_fill(cr);
    crt=crt->suiv;
    }
    free(crt);
}

}


static gboolean sourie_clicked(GtkWidget *widget, GdkEventButton *event,
                               IlisiFourmi *Jeu)
{
   int x,y,a,b;
    if (event->button == 1) //si le boutton cliqué est le boutton droit de sourie
    {
        if(Jeu->fourmi_test==1)
        {
            x=(int)event->x;
            y=(int)event->y;
            a= Jeu->grid_zone.debut_ligne + y/Jeu->grid_zone.case_taille;
            b= Jeu->grid_zone.debut_coll +  x/Jeu->grid_zone.case_taille;
            if(!Jeu->nbr_fourmi)
            {
                Jeu->fourmis=(fourmi_info*)malloc(sizeof(fourmi_info));
                Jeu->fourmis->pos_fourmi.x=b;
                Jeu->fourmis->pos_fourmi.y=a;
                Jeu->fourmis->direction=1;
                Jeu->fourmis->suiv=NULL;
            }
            else
            {
                fourmi_info *crt=Jeu->fourmis;
                while(crt->suiv) crt=crt->suiv;
                crt->suiv=(fourmi_info*)malloc(sizeof(fourmi_info));
                crt->suiv->pos_fourmi.x=b;
                crt->suiv->pos_fourmi.y=a;
                crt->suiv->direction=1;
                crt->suiv->suiv=NULL;
            }
            Jeu->nbr_fourmi++;
            Jeu->fourmi_test=0;
        }

        else if(Jeu->fourmi_test==2)
        {
            x=(int)event->x;
            y=(int)event->y;
            a= Jeu->grid_zone.debut_ligne + y/Jeu->grid_zone.case_taille;
            b= Jeu->grid_zone.debut_coll +  x/Jeu->grid_zone.case_taille;
            if(Jeu->fourmis->pos_fourmi.x==b && Jeu->fourmis->pos_fourmi.y==a)
                {Jeu->fourmis=Jeu->fourmis->suiv;
                 Jeu->fourmi_test=0;
                 Jeu->nbr_fourmi--;
                 gtk_widget_queue_draw(widget);
                 return TRUE;
                 }
            fourmi_info *crt=Jeu->fourmis;
            fourmi_info *pcd=crt;
            while(crt)
            {
                if(crt->pos_fourmi.x==b && crt->pos_fourmi.y==a)
                    {pcd->suiv=crt->suiv;
                     free(crt);
                     Jeu->nbr_fourmi--;

                     break;
                    }
                pcd=crt;
                crt=crt->suiv;
            }
            Jeu->fourmi_test=0;
        }

        else
        {
        x=(int)event->x;
        y=(int)event->y;
        a= Jeu->grid_zone.debut_ligne + y/Jeu->grid_zone.case_taille;
        b= Jeu->grid_zone.debut_coll +  x/Jeu->grid_zone.case_taille;
        if(Jeu->grid_zone.grid[a][b]=='B')
        Jeu->grid_zone.grid[a][b]='N';
        else Jeu->grid_zone.grid[a][b]='B';
        }
       gtk_widget_queue_draw(widget);
    }
    return TRUE;
}

/**********************************************************
Nom de la fonction : zoomer_grid
Entreés : la grille complete
Sorties : pas de sortie
But  : appliquer un zoom sur la zone
************************************************************/
void zoomer_grid(Grid *zone)
{
    /**retrancher 5 pixels de taille du case*/
    zone->case_taille=zone->case_taille-5;
    int nv_nbr_case;
    /********pour les colonnes**********/
    nv_nbr_case=1000/zone->case_taille;/*determiner le nouveau nbr des cases (largeur)*/
    /**determiner le debut et la fin de la representation
    de la zone dessinable dans notre grille logique (matrice)*/
    zone->debut_coll=(200-nv_nbr_case)/2;
    zone->fin_coll=200-zone->debut_coll;

    /*******pour les lignes**********/
    nv_nbr_case=600/zone->case_taille;/*determiner le nouveau nbr des cases (hauteur)*/
    zone->debut_ligne=(120-nv_nbr_case)/2;
    zone->fin_ligne=120-zone->debut_ligne;
    return ;
}

static gboolean commencer_jeu(IlisiFourmi *Jeu)
{

    fourmi_info *crt=Jeu->fourmis;
    /**Parcourir la liste de toutes les fourmis et faire les testes pour les deplacer*/
    while(crt)
    {
        /**si la zone de la fourmi est blanche*/
    if(Jeu->grid_zone.grid[crt->pos_fourmi.y][crt->pos_fourmi.x]=='B')
    {
        Jeu->grid_zone.grid[crt->pos_fourmi.y][crt->pos_fourmi.x]='N';
        switch (crt->direction)
        {
            case 1:  crt->pos_fourmi.x++;  break;
            case 2 : crt->pos_fourmi.y++;      break;
            case 3 : crt->pos_fourmi.x--;   break;
            case 4 : crt->pos_fourmi.y--;     break;
            }
            if(crt->direction==4) crt->direction=1;
            else crt->direction++;
    }
        else if (Jeu->grid_zone.grid[crt->pos_fourmi.y][crt->pos_fourmi.x]=='N')
        {
           Jeu->grid_zone.grid[crt->pos_fourmi.y][crt->pos_fourmi.x]='B';
            switch(crt->direction)
            {
                case 1 : crt->pos_fourmi.x--;  break;
                case 2 : crt->pos_fourmi.y--;    break;
                case 3 : crt->pos_fourmi.x++;  break;
                case 4 : crt->pos_fourmi.y++;     break;
            }
            if(crt->direction==1) crt->direction=4;
            else crt->direction--;
        }
        if(crt->pos_fourmi.x<0) crt->pos_fourmi.x=199;
        else if(crt->pos_fourmi.x>=200) crt->pos_fourmi.x=0;
        else if(crt->pos_fourmi.y<0) crt->pos_fourmi.y=119;
        else if(crt->pos_fourmi.y>=120) crt->pos_fourmi.y=0;

        else if(   crt->pos_fourmi.x<Jeu->grid_zone.debut_coll || crt->pos_fourmi.x>=Jeu->grid_zone.fin_coll
           || crt->pos_fourmi.y<Jeu->grid_zone.debut_ligne || crt->pos_fourmi.y>=Jeu->grid_zone.fin_ligne
          )
          zoomer_grid(&Jeu->grid_zone);

          crt=crt->suiv;
    }

gtk_widget_queue_draw(Jeu->grid_zone.zone_dessinable);

         /*********Modifier les iterations dnas le status barre***********/
           Jeu->iter++;
           afficher_statu_iteration(Jeu);
           /******************************************************************/

        if(!Jeu->iteration_precise) return TRUE;
        else if(Jeu->iteration_precise==1)
            {Jeu->iteration_precise--; return FALSE;}

        Jeu->iteration_precise--;
        return TRUE;
}
void afficher_statu_iteration(IlisiFourmi *Jeu)
{
    /*********Modifier les iterations dnas le status barre***********/
           int id = gtk_statusbar_get_context_id (GTK_STATUSBAR(Jeu->statu.statubare), "iteration");
           gtk_statusbar_pop (GTK_STATUSBAR(Jeu->statu.statubare), id);
           char iter[20];
           sprintf(iter,"iteration : %d",Jeu->iter);
           gtk_statusbar_push (GTK_STATUSBAR(Jeu->statu.statubare), id, iter);
           /******************************************************************/
           return;
}
void afficher_message_fourmi_existe_pas()
{
    GtkWidget *window,*label;
        label=gtk_label_new("veuillez placer votre fourmi");
        window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window),"pas encore !!");
        GdkPixbuf *pixbuf;
        //GError *error = NULL;
        pixbuf = gdk_pixbuf_new_from_file(".//images//icon1.png", NULL);
        gtk_window_set_icon(window,pixbuf);
        gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
        gtk_widget_set_size_request(window,250,50);
        gtk_container_add(GTK_CONTAINER(window),label);
        gtk_widget_show_all(window);
        return ;
}
void Placer_fourmi(GtkWidget *b,IlisiFourmi *Jeu)
{
    //ici puisque la fonction se lance apres un evenement (click button)
    // donc on doit obligatoirement faire appel a la fonction pour modifier la variable
   Jeu->fourmi_test=1;
   return;
}
void supp_fourmi(GtkWidget *b,IlisiFourmi *Jeu)
{
    //ici puisque la fonction se lance apres un evenement (click button)
    // donc on doit obligatoirement faire appel a la fonction pour modifier la variable
    if(Jeu->play) pause_game(gtk_toolbar_get_nth_item(Jeu->toolbar.toolbar,5),Jeu);
   if(Jeu->nbr_fourmi) Jeu->fourmi_test=2;
   return;
}
void couleur_fourmi(GtkWidget *b,IlisiFourmi *Jeu)
{
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(b),&Jeu->fourmi_couleur);
    gtk_widget_queue_draw(Jeu->grid_zone.zone_dessinable);
}
void couleur_fourmi1(GtkWidget *b,IlisiFourmi *Jeu)
{
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(b),&Jeu->fourmi_couleur1);
    gtk_widget_queue_draw(Jeu->grid_zone.zone_dessinable);
}
void changer_vitesse(GtkWidget *scale,IlisiFourmi *Jeu)
{
    Jeu->vitesse=(int)1001-gtk_range_get_value(scale);
    return;
}
void iter_suivante(GtkWidget *entry,IlisiFourmi *Jeu)
{
    if(Jeu->nbr_fourmi)
    {commencer_jeu(Jeu); return;}
    afficher_message_fourmi_existe_pas();
    return;
}
void iter_precedente(GtkWidget *entry,IlisiFourmi *Jeu)
{
    if(Jeu->iter)
    {
    /*********Modifier les iterations dnas le status barre***********/
           Jeu->iter--;
           afficher_statu_iteration(Jeu);

    fourmi_info *crt=Jeu->fourmis;
    while(crt)
    {
    if(crt->direction==1)
    {
        if(Jeu->grid_zone.grid[++crt->pos_fourmi.y][crt->pos_fourmi.x]=='B')
        {crt->direction=2;
         Jeu->grid_zone.grid[crt->pos_fourmi.y][crt->pos_fourmi.x]='N';
        }
        else { crt->direction=4;Jeu->grid_zone.grid[crt->pos_fourmi.y][crt->pos_fourmi.x]='B';}
    }

    else if (crt->direction==2)
    {
        if(Jeu->grid_zone.grid[crt->pos_fourmi.y][--crt->pos_fourmi.x]=='B')
        {
          crt->direction=3;
          Jeu->grid_zone.grid[crt->pos_fourmi.y][crt->pos_fourmi.x]='N';
        }
        else
        {crt->direction=1; Jeu->grid_zone.grid[crt->pos_fourmi.y][crt->pos_fourmi.x]='B';}
    }

    else if (crt->direction==3)
        {
           if(Jeu->grid_zone.grid[--crt->pos_fourmi.y][crt->pos_fourmi.x]=='B')
           {
               crt->direction=4;
               Jeu->grid_zone.grid[crt->pos_fourmi.y][crt->pos_fourmi.x]='N';
           }
           else
            {
              crt->direction=2;
               Jeu->grid_zone.grid[crt->pos_fourmi.y][crt->pos_fourmi.x]='B';
            }
        }
        else
        {
           if(Jeu->grid_zone.grid[crt->pos_fourmi.y][++crt->pos_fourmi.x]=='B')
           {
               crt->direction=1;
               Jeu->grid_zone.grid[crt->pos_fourmi.y][crt->pos_fourmi.x]='N';
           }
           else
            {
              crt->direction=3;
               Jeu->grid_zone.grid[crt->pos_fourmi.y][crt->pos_fourmi.x]='B';
            }
        }
        crt=crt->suiv;
      }//fin de while(crt);
      gtk_widget_queue_draw(Jeu->grid_zone.zone_dessinable);
}
}
void aller_iteration(GtkWidget *entry,IlisiFourmi *Jeu)
{
    if(!Jeu->nbr_fourmi) {afficher_message_fourmi_existe_pas(); return;}
    int var=atoi(gtk_entry_get_text(entry));
    if(var)
    {
        Jeu->iteration_precise=var;
        g_timeout_add(0.9,(GSourceFunc)commencer_jeu,(IlisiFourmi*)Jeu);
    }
    return;
}

Image *initialiser_image();
void afficher_msg_about(GtkWidget *tooll,gpointer data)
{
    GtkWidget *content_area,*dialog=gtk_dialog_new_with_buttons("About",NULL,GTK_DIALOG_MODAL,GTK_STOCK_OK,
                                                  GTK_RESPONSE_OK,NULL);
    content_area=gtk_dialog_get_content_area(dialog);
    Image *image_about=initialiser_image();
    image_about->chemin=".\\images\\about_frm.png";
    creer_image(image_about);
    gtk_widget_set_size_request(dialog,300,300);
    gtk_window_set_position(dialog,GTK_WIN_POS_CENTER);
    associer_element(content_area,image_about->Image);
    afficher_tout(dialog);
    gint reponse=gtk_dialog_run(dialog);
    gtk_widget_destroy(dialog);
}
/**********************************************************
Nom de la fonction : New_game
Entreés : variable de type IlisiFourmi qui contient toutes les variables du jeu
          le boutton New qui reinitialise completement le jeu
Sorties : pas de sortie
But  : reinitialiser le Jeu en effacant toutes les fourmis et renouvler la grille.
************************************************************/
void New_game(GtkWidget *tooll,IlisiFourmi *Jeu)
{
    /***************** initialiser le nombre d'iteration dans le status barre **************************/
    Jeu->iter=0;
    afficher_statu_iteration(Jeu);
    /***************************************************************************************/
    if(Jeu->play)pause_game(gtk_toolbar_get_nth_item(Jeu->toolbar.toolbar,5),Jeu);
    for(int ind=0;ind<120;ind++)
        for(int jnd=0;jnd<200;jnd++) Jeu->grid_zone.grid[ind][jnd]='B';//les cellules sont toutes blanches
                                                                       //au premiers temps
            Jeu->grid_zone.debut_coll=75;//l indice correspond au collone du debut de notre grid
            Jeu->grid_zone.fin_coll=125; // l'indice correspond au collone fin de notre grid dessinable
            Jeu->grid_zone.debut_ligne=45; // l indice correspond au ligne du debut
            Jeu->grid_zone.fin_ligne=75;   // l indice correspond au ligne du fin
            Jeu->grid_zone.case_taille=20; // la taille de chaque case du grid
            Jeu->nbr_fourmi=0;
            Jeu->fourmis=NULL;
            gtk_widget_queue_draw(Jeu->grid_zone.zone_dessinable);
            return ;

}

void save_game(GtkWidget *tooll,IlisiFourmi *Jeu)
{
    if(Jeu->play) pause_game(gtk_toolbar_get_nth_item(Jeu->toolbar.toolbar,5),Jeu);
GtkWidget *dialog;
GtkFileChooser *chooser;
gint res;

dialog = gtk_file_chooser_dialog_new ("Save File",
                                      Jeu->ma_fenetre->fenetre,
                                      GTK_FILE_CHOOSER_ACTION_SAVE,
                                      "_Cancel",
                                      GTK_RESPONSE_CANCEL,
                                      "_Save",
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);
chooser = GTK_FILE_CHOOSER (dialog);

gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);

  gtk_file_chooser_set_current_name (chooser,"fourmi.ilisi");


res = gtk_dialog_run (GTK_DIALOG (dialog));
if (res == GTK_RESPONSE_ACCEPT)
  {
    char *filename;
    int i,j;
    fourmi_info *crt=Jeu->fourmis;
    filename = gtk_file_chooser_get_filename (chooser);
    FILE *f = fopen(filename,"w");
    fprintf(f,"%d\t%d\n",Jeu->iter,Jeu->nbr_fourmi);
    for(i=0;i<Jeu->nbr_fourmi;i++)
    {
      fprintf(f,"%d\t%d\t%d\n",crt->pos_fourmi.x,crt->pos_fourmi.y,crt->direction);
      crt=crt->suiv;
    }
    fprintf(f,"%d\t%d\t%d\t%d\t%d\n",Jeu->grid_zone.case_taille,Jeu->grid_zone.debut_ligne,
                                    Jeu->grid_zone.debut_coll,Jeu->grid_zone.fin_ligne,Jeu->grid_zone.fin_coll);
    for( i=0;i<120;i++)
       for( j=0;j<200;j++)
           fprintf(f,"%c",Jeu->grid_zone.grid[i][j]);
    fclose(f);
   g_free (filename);
   g_free (crt);
  }

gtk_widget_destroy (dialog);
}


void open_game(GtkWidget *tooll,IlisiFourmi *Jeu)
{
    if(Jeu->play) pause_game(gtk_toolbar_get_nth_item(Jeu->toolbar.toolbar,5),Jeu);
    GtkWidget *dialog;
gint res;

dialog = gtk_file_chooser_dialog_new ("Open File",
                                      Jeu->ma_fenetre->fenetre,
                                      GTK_FILE_CHOOSER_ACTION_OPEN,
                                      "_Cancel",
                                      GTK_RESPONSE_CANCEL,
                                      "_Open",
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);

res = gtk_dialog_run (GTK_DIALOG (dialog));
if (res == GTK_RESPONSE_ACCEPT)
  {
    char *filename;int i,j;
    fourmi_info *crt,*pcd;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    filename = gtk_file_chooser_get_filename (chooser);

    FILE *f = fopen(filename,"r");
    fscanf(f,"%d\t%d\n",&Jeu->iter,&Jeu->nbr_fourmi);
    for(i=0;i<Jeu->nbr_fourmi;i++)
    {
      crt=(fourmi_info*)malloc(sizeof(fourmi_info));
      fscanf(f,"%d\t%d\t%d\n",&crt->pos_fourmi.x,&crt->pos_fourmi.y,&crt->direction);
      if(!i)  Jeu->fourmis=crt;
      else pcd->suiv=crt;
      crt->suiv=NULL;
      printf("%d",crt->direction);
      pcd=crt;
      crt=crt->suiv;
     }
    fscanf(f,"%d\t%d\t%d\t%d\t%d\n",&Jeu->grid_zone.case_taille,&Jeu->grid_zone.debut_ligne,
                                    &Jeu->grid_zone.debut_coll,&Jeu->grid_zone.fin_ligne,&Jeu->grid_zone.fin_coll);
    for( i=0;i<120;i++)
       for( j=0;j<200;j++)
           fscanf(f,"%c",&Jeu->grid_zone.grid[i][j]);
           fclose(f);
    g_free (filename);

  }
   afficher_statu_iteration(Jeu);
  gtk_widget_queue_draw(Jeu->grid_zone.zone_dessinable);

gtk_widget_destroy (dialog);
}

/**********************************************************
Nom de la fonction : start_game
Entreés : variable de type IlisiFourmi qui contient toutes les variables du jeu
          le boutton play qui lance le jeu
Sorties : pas de sortie
But  : lancer le Jeu
************************************************************/
void start_game(GtkWidget *boutton,IlisiFourmi *Jeu);
void pause_game(GtkWidget *boutton,IlisiFourmi *Jeu)
          {
              Jeu->play=0;
              gtk_tool_button_set_stock_id(GTK_TOOL_BUTTON(boutton),GTK_STOCK_MEDIA_PLAY);
              g_signal_handlers_destroy(GTK_TOOL_BUTTON(boutton));
              g_source_remove(Jeu->a);
              g_signal_connect(boutton,"clicked",G_CALLBACK(start_game),Jeu);
          }
void start_game(GtkWidget *boutton,IlisiFourmi *Jeu)
{

    if(!Jeu->nbr_fourmi)
    {
            afficher_message_fourmi_existe_pas();
            return;
    }
    Jeu->play=1;
    gtk_tool_button_set_stock_id(boutton,GTK_STOCK_MEDIA_PAUSE);
    g_signal_handlers_destroy(GTK_TOOL_BUTTON(boutton));
    g_signal_connect(boutton,"clicked",G_CALLBACK(pause_game),Jeu);
    Jeu->a=g_timeout_add(Jeu->vitesse,(GSourceFunc)commencer_jeu,(IlisiFourmi*)Jeu);
}
#endif // MACRO_FOURMI_H_INCLUDED
