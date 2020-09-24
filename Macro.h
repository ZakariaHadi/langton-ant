#ifndef INTERFACE_MACRO_H_INCLUDED
#define INTERFACE_MACRO_H_INCLUDED

#include "struct_macro.h"
#include "macro_fourmi.h"


#include <windows.h>

/**********************************************************
 Nom de la fonction: INITIALISER L INTERFACE

 Entr�es: int argc, char *argv[]
 Sorties: void
 But:initialiser l'interface gtk+3
 **********************************************************/
void initialiser_interface( int argc, char *argv[] )
{
    gtk_init(&argc, &argv);
}//Fin de la fonction initialiser_interface


/**********************************************************
 Nom de la fonction: afficher

 Entr�es: un widget
 Sorties: void
 But:afficher dans l 'ecran le widget (fenetre)
 **********************************************************/
void afficher(GtkWidget *wid)
{
    gtk_widget_show(wid);
}//Fin de la fonction afficher

/**********************************************************
 Nom de la fonction: afficher_tout

 Entr�es: un widget
 Sorties: void
 But:afficher dans l 'ecran le widget (fenetre) et tous ses descendants
 **********************************************************/
void afficher_tout(GtkWidget *wid)
{
    gtk_widget_show_all(wid);
}//Fin de la fonction afficher


/**********************************************************
 Nom de la fonction: Creer_fenetre

 Entr�es: la taille, la position(au centre par default),le titre,boolean pour indiquer (resizable ou Non)
          le chemin de l'icon de la fenetre
 Sorties: un widget du type fenetre
 But:initialiser une fenetre
 **********************************************************/
Fenetre* Creer_fenetre(char *titre, Taille taille,int resizable)
{
//d�claration d'une nouvelle Fenetre
    Fenetre *fenetre= (Fenetre*)malloc(sizeof(Fenetre));
    if(!fenetre)
    {
        printf("\nEchec d'allocation (Fonction : creer_fenetre)");
        exit(EXIT_FAILURE);
    }// fin du if(!fenetre)

    // creation de la fenetre
    fenetre->fenetre= gtk_window_new (GTK_WINDOW_TOPLEVEL);
    //initialisation des param�tres de la fen�tre

    //taille

    gtk_widget_set_size_request(fenetre->fenetre,taille.largeur,taille.hauteur);
    gtk_window_set_resizable(fenetre->fenetre,resizable);

    //titre
    strcpy(fenetre->fTitre,titre);
    gtk_window_set_title(fenetre->fenetre,titre);
    //type
    //fenetre->fType=GTK_WINDOW_TOPLEVEL;
    //pos debut
    //fenetre->fPosDebut= GTK_WIN_POS_CENTER;
    gtk_window_set_position(fenetre->fenetre,GTK_WIN_POS_CENTER);
    //l'icon de la fenetre
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(".//images//icon.png", &error);
    gtk_window_set_icon(fenetre->fenetre,pixbuf);
    //initialiser la boite verticale qui va contenir les elements qui contient la fenetre
    fenetre->fBox=gtk_vbox_new(0,0);
    //gtk_container_add(fenetre->fenetre,fenetre->fBox);
    //position
    fenetre->fPos.x=-1;
    fenetre->fPos.y=-1;
    //icone

//    fenetre->icone=NULL;

    return ((Fenetre*)fenetre);
}// fin de la fonction Creer_fenetre


/**********************************************************
 Nom de la fonction: Creer_simpe_BOUTTON

 Entr�es: taille du boutton,
 Sorties: un widget du type boutton
 But:creer un boutton simple est vide
 **********************************************************/
Bouton *creer_simple_boutton(Taille taill,int image,const char *chemin)
{
    //d�claration de la variable
    Bouton *button=malloc(sizeof(Bouton));

    //test sur l'allocation
    if(!button)
    {
        printf("\nEchec d'allocation (Fonction : initialiser_bouton)") ;
        exit(EXIT_FAILURE);
    }//Fin if(!button)

    //Initialisation des param�tres
    //le boutton
    if(!image)
    button->Bouton=gtk_button_new();
    else
    { GtkWidget *image=gtk_image_new_from_file(chemin);
      button->Bouton=gtk_button_new();
      gtk_container_add(GTK_CONTAINER(button->Bouton),image);
    }
    //position
    button->bPos.x= -1;
    button->bPos.y= -1;
    //taille
    button->bTaille.hauteur = taill.hauteur;
    button->bTaille.largeur = taill.largeur;
//    gtk_widget_set_size_request(GTK_WIDGET(button->Bouton),
//                                        button->bTaille.largeur,button->bTaille.hauteur);
gtk_widget_set_size_request(button->Bouton,50,50);

    //on retourne le bouton cre�
    return ((Bouton*)button);
}// fin de la fonction creer_simple_boutton


/**********************************************************
 Nom de la fonction: Creer_texte_BOUTTON

 Entr�es: taille du boutton, le texte du boutton, boolean avec MNEMONIC ou pas
 Sorties: un widget du type boutton
 But:creer une boutton qui contient un texte
 **********************************************************/
Bouton* creer_texte_boutton(Taille taill,char *texte,int mnemonic)
{
    //d�claration de la variable
    Bouton *button=malloc(sizeof(Bouton));

    //test sur l'allocation
    if(!button)
    {
        printf("\nEchec d'allocation (Fonction : creer_bouton)") ;
        exit(EXIT_FAILURE);
    }//Fin if(!button)

    //Initialisation des param�tres
    //le boutton
    if(!mnemonic)
    button->Bouton=gtk_button_new_with_label(texte);
    else button->Bouton=gtk_button_new_with_mnemonic(texte);

    //taille
    //s'il contient une image, on ne d�finit pas la taille,
        //elle sera d�t�rmin�e selon la taille de l'image
        if(button->bType != BIMAGE)
    {
       button->bTaille.hauteur = taill.hauteur;
       button->bTaille.largeur = taill.largeur;
       gtk_widget_set_size_request(GTK_WIDGET(button->Bouton),
                                        button->bTaille.largeur,button->bTaille.hauteur);
    }
    gtk_widget_set_size_request(button->Bouton,50,50);
    //on retourne le bouton cre�
    return ((Bouton*)button);
}// fin de la fonction

/**********************************************************
 Nom de la fonction: mettre_type_boutton

 Entr�es: le boutton, le type du boutton (image,de type define NEW/SAVE/EXIT/OK/CANCE/...,file chooser etc)
 Sorties: void
 But:modifier le boutton selon son type
 **********************************************************/

void mettre_type_boutton(Bouton *button,int type)
{
    //la cr�ation d'un bouton, selon le type du boutton
    switch(button->bType)
    {

    //type bouton avec image
//    case BIMAGE :
//        //cr�ation de l'image
//        button->bImg.Image=gtk_image_new_from_file(button->bImg.chemin);
//        //ins�rtion de l'image dans le bouton
//        gtk_button_set_image(GTK_BUTTON(button->Bouton),
//                             button->bImg.idImage
//                            );
//        break;

    //le type bouton pr�d�fini du stock (image + nom + raccourci)
    //cas d'un bouton ajout
    case BADD:
        button->Bouton = gtk_button_new_from_stock(GTK_STOCK_ADD);
        break;
    //cas d'un bouton suppression
    case BDELETE:
        button->Bouton = gtk_button_new_from_stock(GTK_STOCK_DELETE);
        break;
    //cas d'un bouton ouverture
    case BOPEN:
        button->Bouton = gtk_button_new_from_stock(GTK_STOCK_OPEN);
        break;
    //cas d'un bouton fermeture
    case BCLOSE:
        button->Bouton = gtk_button_new_from_stock(GTK_STOCK_CLOSE);
        break;
    //cas d'un bouton information
    case BABOUT:
        button->Bouton = gtk_button_new_from_stock(GTK_STOCK_ABOUT);
        break;
    //cas d'un boutton "choisir fichier"
    case BFILECH:
        button->Bouton = gtk_file_chooser_button_new("Parcourir ...",
                           GTK_FILE_CHOOSER_ACTION_OPEN);
        break;
     //cas d'un boutton choisir couleur
    case BCOLOR:
        button->Bouton = gtk_color_button_new();
        break;

    }
    //Fin switch(button->bType)

}// fin de la fonction mettre_type_boutton


/**********************************************************
 Nom de la fonction: associer_element

 Entr�es: GtkWidget *conteneur : le conteneur o� sera plac� le widget
          GtkWidget *elem : le widget � ins�rer dans le conteneur
          pos : position du widget � ins�rer
 Sorties: void
 But:fonction permet d'ins�rer un widget dans un conteneur de type fixe

 **********************************************************/
void associer_element(GtkWidget *conteneur,GtkWidget *elem)
{
    gtk_container_add(GTK_CONTAINER(conteneur),elem);

}//Fin de la fonction associer_element

/**********************************************************
 Nom de la fonction: creer_combo_box

 Entr�es: ComboBox *comboBox: variable qui va contenir la combboox
 Sorties: ComboBox *comboBox : nouvelle combobox
 But:Cette fonction permet de cr�er une variable  de type ComboBox
 **********************************************************/
ComboBox *creer_combo_box()
{
    ComboBox *combo;
    combo=(ComboBox *)malloc(sizeof(ComboBox));
    combo->ComboBox=gtk_combo_box_text_new();
    return (ComboBox *)combo;

}//Fin de la fonction creer_combo_box


/**********************************************************
 Nom de la fonction: ajouter_element_combo_box

 Entr�es: ComboBox *comboBox: la combobox dans laquelle on veut ins�rer un elmt
          char *element : l'�lement � ins�rer
 Sorties: ComboBox *comboBox : notre combobox
 But:     Cette fonction permet d ajouter un �l�ment dans une combobox
 **********************************************************/
void ajouter_element_combo_box(ComboBox *comboBox,char *element)
{
    gtk_combo_box_text_append_text(GTK_COMBO_BOX(comboBox->ComboBox),element);

}//Fin de la fonction ajouter_element_combo_box

/***************************INITIALISATION BOUTON RADIO*******************************
 Nom de la fonction: init_bouton_radio
 Entr�es: pas d'entrees
 sortie : BoutonRadio * : widget initialiser de type boutton radio*/
 BoutonRadio *init_bouton_radio()
 {
     BoutonRadio *boutton;
     boutton=(BoutonRadio *)malloc(sizeof(BoutonRadio));
     boutton->hbox=gtk_vbox_new(1,1);
     return ((BoutonRadio *)boutton);
 }
/***************************CREATION BOUTON RADIO*******************************
 Nom de la fonction: creer_bouton_radio

 Entr�es: BoutonRadio *radioButtonGrp : le radio bouton initial, permet de
                    d�terminer le groupe auquel appartient un bouton radio

          BoutonRadio *radioButton : le radio bouton � ins�rer
          char *element : le label du bouton radio

 Sorties: BoutonRadio *radioButton  le nouveau boutton radio

 But:     Cette fonction permet de cr�er un nouveau bouton radio.
      -       Si le param�tre radioButtonGrp est �gal � NULL, on cr�e un nouveau
          un nouveau group de radio bouton sera cr�e, avec en tete
          l'�l�ment qu'on aura ins�r�.
      -       Si le param�tre n'est pas NULL, on r�cup�re le groupe du bouton
          et c'est dans ce dernier que le nouveau bouton radio sera ins�r�
 **********************************************************/
void creer_bouton_radio(BoutonRadio *radioButtonGrp,
                        BoutonRadio *radioButton,
                        char *element)
{
//Si radioButtonGrp est �gale � NULL, �a veut dire qu'on cr�e un nouveau
//groupe de bouton radio
    if(radioButtonGrp == NULL)
        radioButton->BoutonRadio=gtk_radio_button_new_with_label(NULL,element);
//sinon on insert dans le groupe represent� par radioButtonGrp
    else
        radioButton->BoutonRadio=gtk_radio_button_new_with_label_from_widget
                                   (GTK_RADIO_BUTTON
                                    (radioButtonGrp->BoutonRadio),
                                    element
                                   );
    gtk_box_pack_start(radioButton->hbox,radioButton->BoutonRadio,0,0,0);
}//Fin de la fonction creer_bouton_radio

/***************************INITIALISATION CHECK BOX*******************************
 Nom de la fonction: init_checkbox

 Entr�es: pas d'entree
 Sorties: nouvelle checkbox initialiser

 But:     Cette fonction permet d'initialiser une variable  de type CheckBox
 **********************************************************/
 CheckBox *init_checkbox()
 {
     CheckBox *checkboite;
     checkboite=(CheckBox *)malloc(sizeof(CheckBox));
     checkboite->v_box=gtk_vbox_new(0,0);
     return ((CheckBox *)checkboite);
 }
/***************************CREATION CHECK BOX*******************************
 Nom de la fonction: creer_checkbox

 Entr�es: variable qui va contenir la checkbox
 Sorties: nouvelle checkbox

 But:     Cette fonction permet de cr�er une variable  de type CheckBox
 **********************************************************/
void creer_checkbox(CheckBox *checkbox,char *elem)
{
//cr�ation de la checkbox
    checkbox->Check=gtk_check_button_new_with_label(elem);
}//fin de la fonction creer_checkbox


/***************************CREATION DUNE BOITE*******************************
 Nom de la fonction: creer_box

 Entr�es: Box *box : variable qui va contenir la box
 Sorties: void
 But:     Cette fonction permet de cr�er un conteneur de type box (horizontal
          ou bien vertical)
 **********************************************************/
Box *creer_box(int type)
{
    Box *box=(Box *)malloc(sizeof(Box));
    //on cr�e une box selon le type souhait�
    //cr�ation d'une box verticale
    if(type == VERTICAL)
        box->Box=gtk_vbox_new(0,0);
    //cr�ation d'une box horizontale
    if(type == HORIZONTAL)
        box->Box=gtk_hbox_new(0,0);
    //taille de la box
    //gtk_widget_set_size_request(box->Box,box->bTaille.largeur,
                                //box->bTaille.hauteur);

    return (Box *)box;
}//Fin de la fonction creer_box


/***************************AJOUTER ELEMENT BOX*******************************
 Nom de la fonction:  ajouter_element_box(GtkWidget *box,GtkWidget *element,int position,
                         int expand,int fill,int padding)

 Entr�es: GtkWidget *box : la box o� on veut ins�rer un widget
        GtkWidget *element : le widget � ins�rer
        int position : position o� on veut ins�rer (debut,fin)
        int expand : si le widget va occupper toute l'espace disponible
        int fill  : si le widget va remplir toute l'espace qui lui est r�s�rv�
        int padding : parge int�rieur
 Sorties: notre boite
 But:     Cette fonction permet d ajouter un nouveau element dans la boite
 **********************************************************/

void ajouter_element_box(GtkWidget *box,GtkWidget *element,int position,
                         int expand,int fill,int padding)
{
    //on place l'�l�ment selon la position souhait�e
    //on place ici l'element en debut de box
    if(position == 1)
        gtk_box_pack_start(GTK_BOX(box),element,expand,fill,padding);
    //on place ici l'element en fin de box
    if(position == 2)
        gtk_box_pack_end(GTK_BOX(box),element,expand,fill,padding);
}//fin de la fonction inserer_element_box

/************************INITIALISATION DU "SCROLLED" FENETRE***********************
Nom de la fonction : init_scrolled_window()
Entrees : pas d entrees
Sortie  : ScrollBar *Scrollbar : variable de type scrollbare
But     : permet d'initialiser une nouvelle variable de type Scrrolled_bare
/**************************************************************************************/
ScrollBar *init_scrolled_window()
{
    ScrollBar *S_bare=(ScrollBar *)malloc(sizeof(ScrollBar));
    if(!S_bare)
    {
        printf("Erreur de reservation de memoire - Scroll Bar ! ");
        exit(-1);
    }
    //1:ALWAYS cad meme si la taille de la fenetre permet d afficher tous le contenu , la bare existe
    //2:AUTOMATIC cad quand le contenu depasse la taille de la fenetre , la "scroll" bare s'apparaitra
    //3:NEVER la "scrolled" bare n'existe pas
    S_bare->bottomBar=1;
    S_bare->sideBar=1;
    S_bare->sw=NULL;
    return ((ScrollBar*)S_bare);
}

/************************CREATION DU "SCROLLED" FENETRE***********************
Nom de la fonction : creer_scrolled_window(ScrollBar *sw)
Entrees : ScrollBar *sw : variable de type ScrollBar
Sortie  : pas de sortie
But     : permet de creer une nouvelle fenetre qui contient une bare defilement
/**************************************************************************************/
void creer_scrollBar(ScrollBar *sw)
{
    GtkPolicyType tab[2];
    sw->sw=gtk_scrolled_window_new(NULL,NULL);
    switch(sw->sideBar)
    {
     case 1:tab[0]=GTK_POLICY_ALWAYS;break;
     case 2:tab[0]=GTK_POLICY_AUTOMATIC;break;
     case 3:tab[0]=GTK_POLICY_NEVER;break;
     default:tab[0]=GTK_POLICY_ALWAYS;break;
    }
    switch(sw->bottomBar)
    {
     case 1:tab[1]=GTK_POLICY_ALWAYS;break;
     case 2:tab[1]=GTK_POLICY_AUTOMATIC;break;
     case 3:tab[1]=GTK_POLICY_NEVER;break;
     default:tab[1]=GTK_POLICY_ALWAYS;break;
    }
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(sw->sw),tab[1],tab[0]);
    gtk_widget_set_size_request(sw->sw,180,600);
}

void associer_element_scroll(ScrollBar *sw,GtkWidget *elem)
{
   //gtk_container_add(GTK_CONTAINER(elem), sw->Idsw);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(sw->sw),elem);
}
/**********************************************************************************************

/************************ Creer un Echelle ***************************/
void creer_echelle(IlisiFourmi *Jeu,int val_min,int val_max,int pas,int val_default)
{
    GtkAdjustment *Adj=gtk_adjustment_new(val_default,val_min,val_max,pas,pas,0);
         Jeu->Echelle.scale=gtk_hscale_new(Adj);
         g_signal_connect(Jeu->Echelle.scale,"value-changed",G_CALLBACK(changer_vitesse),Jeu);
         return;
}
/************************ Creer une barre d'outils  ****************/
void  creer_toolbar(IlisiFourmi *Jeu)
{
    Jeu->toolbar.toolbar=gtk_toolbar_new();
    Jeu->toolbar.toolitem = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
    g_signal_connect(G_OBJECT(Jeu->toolbar.toolitem), "clicked",
                     G_CALLBACK(New_game), Jeu);
    gtk_toolbar_insert(GTK_TOOLBAR(Jeu->toolbar.toolbar), Jeu->toolbar.toolitem, 0);
    Jeu->toolbar.toolitem = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
    g_signal_connect(G_OBJECT(Jeu->toolbar.toolitem), "clicked",
                     G_CALLBACK(save_game), Jeu);
    gtk_toolbar_insert(GTK_TOOLBAR(Jeu->toolbar.toolbar), Jeu->toolbar.toolitem, 1);
    Jeu->toolbar.toolitem = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
    g_signal_connect(G_OBJECT(Jeu->toolbar.toolitem), "clicked",
                     G_CALLBACK(open_game), Jeu);
    gtk_toolbar_insert(GTK_TOOLBAR(Jeu->toolbar.toolbar), Jeu->toolbar.toolitem, 2);
    Jeu->toolbar.separator = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(Jeu->toolbar.toolbar), Jeu->toolbar.separator, 3);

    Jeu->toolbar.toolitem = gtk_tool_button_new_from_stock(GTK_STOCK_MEDIA_PREVIOUS);
    g_signal_connect(G_OBJECT(Jeu->toolbar.toolitem), "clicked",
                     G_CALLBACK(iter_precedente), Jeu);
    gtk_toolbar_insert(GTK_TOOLBAR(Jeu->toolbar.toolbar), Jeu->toolbar.toolitem, 4);
    Jeu->toolbar.toolitem = gtk_tool_button_new_from_stock(GTK_STOCK_MEDIA_PLAY);
    g_signal_connect(G_OBJECT(Jeu->toolbar.toolitem), "clicked",
                     G_CALLBACK(start_game), Jeu);
    gtk_toolbar_insert(GTK_TOOLBAR(Jeu->toolbar.toolbar), Jeu->toolbar.toolitem, 5);
    Jeu->toolbar.toolitem = gtk_tool_button_new_from_stock(GTK_STOCK_MEDIA_NEXT);
    g_signal_connect(G_OBJECT(Jeu->toolbar.toolitem), "clicked",
                     G_CALLBACK(iter_suivante), Jeu);
    gtk_toolbar_insert(GTK_TOOLBAR(Jeu->toolbar.toolbar), Jeu->toolbar.toolitem, 6);
    Jeu->toolbar.separator = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(Jeu->toolbar.toolbar), Jeu->toolbar.separator,7);

    Jeu->toolbar.toolitem = gtk_tool_button_new_from_stock(GTK_STOCK_ABOUT);
    g_signal_connect(G_OBJECT(Jeu->toolbar.toolitem), "clicked",
                     G_CALLBACK(afficher_msg_about), NULL);
    gtk_toolbar_insert(GTK_TOOLBAR(Jeu->toolbar.toolbar), Jeu->toolbar.toolitem, 8);

    return ;
}


/************************ initialisation d'UNE BLOC_NOTE  ****************/
Bloc_note *init_bloc_note(int nbr_page,GtkPositionType position_onglet)
{
    Bloc_note *B_note;
    B_note=(Bloc_note *)malloc(sizeof(Bloc_note));
    B_note->bloc_note=gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(B_note->bloc_note),position_onglet);
    B_note->nbr_page=nbr_page;
    //B_note->pos_onglet=position_onglet;
    return ((Bloc_note *) B_note);
}
/************************ METTRE UNE NV PAGE DANS UNE BLOC_NOTE  ****************/
void mettre_page_Bnote(Bloc_note *ma_bloc_note,char *titre_page,GtkWidget *contenu_du_page)
{
    GtkWidget *label=gtk_label_new(titre_page);
    gtk_notebook_append_page(ma_bloc_note->bloc_note,contenu_du_page,label);
}




/************************ Creation des zones de saisies  ****************/
/***************************FONCTION INITIALISATION D'UNE GRANDE ZONE DE SAISIR D'UN TEXTE*******************************/
text_view *init_text_view(int hauteur,int largeur)
{
    text_view *mon_text;
    mon_text=(text_view *)malloc(sizeof(text_view));
    mon_text->texte=gtk_text_view_new();
    mon_text->taiile_texte.hauteur=hauteur;
    mon_text->taiile_texte.largeur=largeur;
    gtk_widget_set_size_request(mon_text->texte,largeur,hauteur);
    return (text_view *)mon_text;
}
/***************************FONCTION INITIALISATION ZONE SAISI*******************************
 Nom de la fonction:  initialiser_entry()

 Entr�es: Pas d'entr�es
 Sorties: ZoneSaisi *entry : une variable de type ZoneSaisi initialis�e
 But:     Cette fonction permet d'initialiser une variable de type ZoneSaisi
 **********************************************************/
zoneSaisi* initialiser_entry()
{
    //d�claration de la variable
    zoneSaisi *entry=(zoneSaisi*)malloc(sizeof(zoneSaisi));

    //test sur l'allocation
    if(!entry)
    {
        printf("\nEchec d'allocation (Fonction : initialiser_entry)") ;
        exit(EXIT_FAILURE);
    }//Fin if(!entry)
    //initialisation des param�tres
    //text pr�sent initialement dans la zone (il n ya pas encore du texte)
    entry->zText = NULL;
    //position
    entry->zPos.x=0;
    entry->zPos.y=0;
    //taille
    entry->zTaille.hauteur =20;
    entry->zTaille.largeur =100;
    //visibilit� du texte
    entry->zVisible = 1;
    //nombre de caract�res max
    entry->zMaxlenght=6;
    //position du curseur
    entry->zCursorposition=0;
    //caract�re affich� si visibilit� � 0
    entry->zTremp='*';

    //on retourne la variable initialis�e
    return ((zoneSaisi*)entry);
}// fin de la fonction initialiser_entry

/******************FONCTION CREER ZONE SAISI  **************************
 Nom de la fonction:  creer_entry

 Entr�es: variable de type ZoneSaisi contenant les param�tres
 Sorties: une nouvelle zone de saisi
 But:     Cette fonction permet de cr�er une variable param�tr�e de type ZoneSaisi
 **********************************************************/
void creer_entry(zoneSaisi *zone)
{
    //cr�ation de la zone de saisie, avec la taille max en param�tre
    zone->zone=gtk_entry_new();
    gtk_entry_set_max_length(zone->zone,zone->zMaxlenght);
    gtk_widget_set_size_request(zone->zone,10,10);
    //texte pr�sent initialement dans la zone
    if(zone->zText)
        gtk_entry_set_text(GTK_ENTRY(zone->zone),zone->zText);
    //Fin if(zone->zText)
    //taille de la zone
    gtk_widget_set_size_request(GTK_WIDGET(zone->zone),zone->zTaille.largeur,
                                zone->zTaille.hauteur);
    //si le texte saisi doit �tre affich� ou pas
    if(zone->zVisible == 0)
    {
        gtk_entry_set_visibility(GTK_ENTRY(zone->zone),FALSE);
        gtk_entry_set_invisible_char(GTK_ENTRY(zone->zone),zone->zTremp);
    }//fin if(zone->zVisible == 0)

    //alignement du texte
    gtk_entry_set_alignment(GTK_ENTRY(zone->zone),zone->zCursorposition);

    //texte initial dans la zone
    gtk_entry_set_placeholder_text(GTK_ENTRY(zone->zone),"aller a une iteration");
}// fin de la fonction creer_entry


/************************* FONCTION CREER SPIN ***************************
 Nom de la fonction: creer_bouton_spin

 Entr�es: la taille du boutton spin,le niveau min, le niveau max, le pas(step)
 Sorties: nouvelle variable du type spin boutton

 But:     Cette fonction permet de cr�er une variable  de type spin boutton
 **********************************************************/
BoutonSpin *creer_bouton_spin(Taille taille,int Smax,int Smin,int pas)
{
    BoutonSpin *spin;
    spin->sMax=Smax;
    spin->sMin=Smin;
    spin->sPas=pas;
    spin->Spin = gtk_spin_button_new_with_range(Smin,Smax,
                   pas);
    gtk_widget_set_size_request(spin->Spin, spin->sTaille.largeur, spin->sTaille.hauteur);
    return((BoutonSpin *)spin);
}


/********** FONCTIONS CREATION MENU ***************/
MenuBar* nouveau_menu_bar ()
{
    MenuBar *nMenuBar=malloc(sizeof(MenuBar));

    if(!nMenuBar)
    {
        printf("\nEchec de l'allocation.");
        exit(EXIT_FAILURE);
    }

    nMenuBar->menuBar=gtk_menu_bar_new();
    nMenuBar->listeMenu=NULL;

    return ((MenuBar*)nMenuBar);
}

void inserer_menu (MenuBar *menuBar, char *label)
{
    Menu *courant=menuBar->listeMenu;
    Menu *elem=malloc(sizeof(Menu));

    strcpy(elem->label,label);
    elem->listeMenuItem=NULL;
    elem->suivant=NULL;

    if(!courant)
        menuBar->listeMenu=elem;
    else
    {
        while(courant->suivant)
            courant=courant->suivant;
        courant->suivant=elem;
    }
}//Fin de la fonction inserer_menu

void  inserer_menu_item (Menu *menu,char *labelMenu,MenuItem *mI)
{
    Menu *courant=menu;
    MenuItem *parcours;
//   MenuItem *menuItem=malloc(sizeof(MenuItem));/** FAIRE TEST ALLOCATION **/
    int existe=0;

    //On v�rifie que le labelMenu entr�e existe bien, pour
    // ensuite ins�rer le menuItem
    while(courant)
    {
        if( !strcmp(courant->label,labelMenu))
        {
            existe=1;     //Fin if( !strcmp(courant->label,labelMenu))
            break;
        }
        courant=courant->suivant;
    }//Fin while(courant)

    if(existe)
    {
        if(!mI->type)
            mI->menuItem = gtk_menu_item_new_with_label(mI->label);
        if(mI->type)
            mI->menuItem = gtk_menu_item_new_with_mnemonic(mI->label);

        mI->sous_menu=NULL;
        mI->suivant=NULL;

        parcours=courant->listeMenuItem;

        if(!parcours)
            courant->listeMenuItem=mI;
        else
        {
            while(parcours->suivant)
                parcours=parcours->suivant;
            parcours->suivant=mI;
        }

    }//Fin if(existe)

}//Fin de la fonction inserer_menu_item

void creer_menu (MenuBar *menuBar)
{
    GtkWidget *pMenu;
    GtkWidget *pMenuItem;
    GtkWidget *separateur;

    Menu *courantMenu=menuBar->listeMenu;
    MenuItem *courantMenuItem;


    while(courantMenu)
    {
        courantMenuItem=courantMenu->listeMenuItem;

        pMenu = gtk_menu_new();

        pMenuItem = gtk_menu_item_new_with_label(courantMenu->label);

        gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
        gtk_menu_shell_append(GTK_MENU_SHELL(menuBar->menuBar), pMenuItem);


        while(courantMenuItem)
        {
            //si s�parateur
            if(courantMenuItem->separateur)
            {
                separateur=gtk_separator_menu_item_new();
                gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), separateur);
            }

            gtk_menu_shell_append(GTK_MENU_SHELL(pMenu),
                                  courantMenuItem->menuItem);
            courantMenuItem=courantMenuItem->suivant;
        }//Fin while(courantMenuItem)

        courantMenu=courantMenu->suivant;
    }//Fin while(courantMenu)

}//Fin de la fonction creer_menu





/****************************** CREATION LABEL **************************/
/***                    FONCTION INITIALISATION LABEL                 ***
 Nom de la fonction: initialiser_label

 Entr�es: pas d'entree
 Sorties: Label *label : une variable de type Label initialis�e

 But:     Cette fonction permet d'initialiser une variable de type Label
 **********************************************************/
Label* initialiser_label()
{
    //d�claration de la variable
    Label *label;
    label= (Label*)malloc(sizeof(Label));
    //test sur l'allocation
    if(!label)
    {
        printf("\nEchec d'allocation (Fonction : initialiser_label)") ;
        exit(EXIT_FAILURE);
    }//Fin if(!label)
    label->label=gtk_label_new("");
    //param�trage
    //texte du label
    //label->lTexte = NULL
    label->lStyle=0;
    //position
    label->lPos.x = 0;
    label->lPos.y = 0;
    label->lJustify=LEFT;


    //on retourne la variable initialis�e
    return ((Label*)label);
}// fin de la fonction intialiser_label

/***                    FONCTION CREER LABEL                 ***
 Nom de la fonction: creer_label

 Entr�es: Label *label : variable de type Label contenant les param�tres
 Sorties: Label *label : un nouveau label param�tr�

 But:     Cette fonction permet de cr�er une variable param�tr�e de type Label
 **********************************************************/
void creer_label(Label *label,char *texte)
{
    //Alignement du texte
    gtk_label_set_justify(GTK_LABEL(label->label),label->lJustify);
    // utiliser du format ou  pas
    //Si le texte est selectionnable
    gtk_label_set_selectable(GTK_WIDGET(label->label),label->selectionnable);
    //si un format n'a pas �t� demand�, on cr�e le label
    if(!(label->lStyle))
    {
        gtk_label_set_label(GTK_WIDGET(label->label),texte);
    }//Fin if(!(label->lStyle))

    //Sinon on affecte le format au text et on cr�e le label





    // fin if (label->lstyle == 1)

}// fin de la fonction creer_label


/****************************** INITIALISER IMAGE **************************
 Nom de la fonction: initialiser_image

 Entr�es: pas d'entree
 Sorties:  une variable de type Image initialis�e

 But:     Cette fonction permet d'initialiser une variable de type Image
 **********************************************************/
Image *initialiser_image()
{
    Image *img;
    img=(Image*)malloc(sizeof(Image));
    //initialisation du chemin
    img->chemin=NULL;//on a pas encore du chemin pour les images
    //initialisation de la position
    img->iPos.x = 0;
    img->iPos.y = 0;
    img->itype=0;//cad on tire l'image du chemin
}//fin de la fonction initialiser_image

/***                        FONCTION CREER IMAGE                      ***/
void creer_image(Image *img)
{
    //on r�cup�re l'image � partir du chemin en param�tre de la variable
    //et on cr�e l'image
    switch(img->itype)
    {
    case 0:
        img->Image = gtk_image_new_from_file(img->chemin);
        break;
    case 1:
        img->Image = gtk_image_new_from_stock(GTK_STOCK_QUIT,
                                                GTK_ICON_SIZE_LARGE_TOOLBAR);
        break;
    }
}// fin de la fonction creer_image


/******************************* FONCTION CREATION CADRE ****************/
/***                  FONCTION INITIALISATION CADRE                   ***
 Nom de la fonction: initialiser_cadre()

 Entr�es: pas d'entree
 Sorties: Cadre *cadre: une variable de type Cadre initialis�e

 But:     Cette fonction permet d'initialiser une variable de type Cadre
 **********************************************************/
Cadre* initialiser_cadre()
{
    //d�claration de la variable
    Cadre *cadre=(Cadre*)malloc(sizeof(Cadre));

    //test sur l'allocation
    if(!cadre)
    {
        printf("\nEchec d'allocation (Fonction : initialiser_cadre)");
        exit(EXIT_FAILURE);
    }//Fin if(!cadre)

    //d�finition du label
    cadre->Cadre=gtk_frame_new("Cadre");
    //initialisation des autres parametres
    //cadre->cLabel=NULL;
    //couleur
    cadre->cCouleur.blue=0xcccc;
    cadre->cCouleur.red=0xcccc;
    cadre->cCouleur.green=0xcccc;
    //position du texte
    cadre->cPoslabelX=0.0;
    cadre->cPoslabelY=0.5;
    //style du cadre
    cadre->cStyle=C_SHADOW_ETCHED_IN_OUT;
    //taille du cadre
    cadre->cTaille.hauteur=100;
    cadre->cTaille.largeur=100;

    //on retourne la variable initialis�e
    return ((Cadre*)cadre);
}//Fin de la fonction initialiser_cadre

/**************                FONCTION CREER CADRE                      ******
 Nom de la fonction: creer_cadre(Cadre *Moncadre)

 Entr�es:Cadre *Moncadre : variable de type Cadre contenant les param�tres
 Sorties: Cadre *cadre : un nouveau cadre param�tr�

 But:    Cette fonction permet de cr�er une variable param�tr�e de type Cadre
 **********************************************************/
void creer_cadre(Cadre *Moncadre)
{
    //label du cadre
    gtk_frame_set_label(GTK_FRAME(Moncadre->Cadre),Moncadre->cLabel);
    //style du cadre
    gtk_frame_set_shadow_type(GTK_FRAME(Moncadre->Cadre),Moncadre->cStyle);
    //position du texte
    gtk_frame_set_label_align(GTK_FRAME(Moncadre->Cadre),
                              Moncadre->cPoslabelX,Moncadre->cPoslabelY
                             );
    //d�finition de la taille
//    //gtk_widget_set_size_request(Moncadre->cFixed,Moncadre->cTaille.largeur,
//                                Moncadre->cTaille.hauteur
//                               );
}//Fin de la fonction creer cadre


/**************                FONCTION CREER SEPARATEUR                      ******
 Nom de la fonction: creer_separateur(Separateur *separateur)

 Entr�es:  variable de type Separateur contenant les param�tres
 Sorties:  pas de sortie

 But:    Cette fonction permet de cr�er une variable param�tr�e de type Separateur
 **********************************************************/
void creer_separateur (Separateur *separateur)
{
    //on d�finit le type de s�parateur demand�
    if(!separateur->type)//horizontal
        separateur->Separateur=gtk_hseparator_new();
    else//vertical
        separateur->Separateur=gtk_vseparator_new();
    //on d�finit la taille du s�parateur
    gtk_widget_set_size_request(separateur->Separateur,
                                separateur->sTaille.largeur,separateur->sTaille.hauteur
                               );
}//Fin de la fonction creer_separateur
static void menu_event(GtkWidget *source, IlisiFourmi *Jeu)
{
    if(!strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(source)),"New"))
     New_game(NULL,Jeu);
    if(!strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(source)),"Open"))
    open_game(NULL,Jeu);
    if(!strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(source)),"Save as"))
    save_game(NULL,Jeu);
    if(!strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(source)),"Exit"))
        QUITTER(Jeu->ma_fenetre->fenetre,Jeu);
    if(!strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(source)),"About"))
        afficher_msg_about(NULL,NULL);


return ;
}
void creer_Menu(Le_Menu *menu,IlisiFourmi *Jeu)
{
    const char* file[] = {"New","Open","Save as","Exit"};
     const char* help[] = {"About"};

    GtkWidget *hbox,*separator,*menuu;
        menuu=gtk_menu_new();
        menu->Menu_bar=gtk_menu_bar_new();
        menu->Menu_champ=gtk_menu_item_new_with_mnemonic("_File");


        for(int i=0;i<4;i++)
        {
                menu->sous_menu=gtk_menu_item_new_with_label(file[i]);
                gtk_menu_shell_append(GTK_MENU_SHELL(menuu),menu->sous_menu);
                g_signal_connect(menu->sous_menu,"activate",G_CALLBACK(menu_event),(IlisiFourmi*)Jeu);
        }
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->Menu_champ),menuu);
        gtk_menu_shell_append(GTK_MENU_SHELL(menu->Menu_bar),menu->Menu_champ);
        menuu=gtk_menu_new();
        menu->Menu_champ=gtk_menu_item_new_with_mnemonic("_Help");
        for(int i=0;i<1;i++)
        {
                menu->sous_menu=gtk_menu_item_new_with_label(help[i]);
                gtk_menu_shell_append(GTK_MENU_SHELL(menuu),menu->sous_menu);
                g_signal_connect(menu->sous_menu,"activate",G_CALLBACK(menu_event),NULL);
        }
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->Menu_champ),menuu);
        gtk_menu_shell_append(GTK_MENU_SHELL(menu->Menu_bar),menu->Menu_champ);
        gtk_box_pack_start(GTK_BOX(Jeu->ma_fenetre->fBox),menu->Menu_bar,0,0,0);

}

#endif // INTERFACE_MACRO_H_INCLUDED
