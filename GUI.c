#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Segmentation.h"
char *filename;
GtkWidget *window;
GtkWidget *button;
GtkWidget *button_box;
GtkWidget *image;
GtkWidget *button_Validate;
GtkWidget *button_auto;
GtkWidget *button_corrected;
GtkWidget *table;
GtkWidget *entry;
GtkWidget *label;
GtkWidget *texte;
GtkWidget *registe;
int angle = 0;

//Display the new image that have been create after the rotation
void pin_up_angle_image()
{
 gtk_widget_destroy(image);
 SDL_Surface *img_a = IMG_Load("angle.png");
  int h = img_a->h;
  int w = img_a->w;
  free(img_a);
 GdkPixbuf *dest;
 dest = gdk_pixbuf_new_from_file("angle.png",NULL);
 dest = gdk_pixbuf_scale_simple(dest,w/2,h/2,GDK_INTERP_BILINEAR);
 image = gtk_image_new_from_pixbuf(dest);
 gtk_grid_attach(GTK_GRID(table),image,0,0,2,1);
 gtk_widget_show_all(table); 
}

// function activated when user click on the button "Valider". 
// Destroys all widgets and print the angle from the entry
void validate(){
 const gchar *agle =  gtk_entry_get_text(GTK_ENTRY(entry));
 angle = atoi(agle);
 printf("Valider");
 Segmentation(filename,angle,0);
 gtk_widget_destroy(entry);
 entry = gtk_entry_new();
 gtk_grid_attach(GTK_GRID(table),entry,0,2,2,1);
 pin_up_angle_image();
 printf("angle : %d\n",angle);
}
//Destroy some useless widgets and call the function Segmentation that will do the 
//automatic rotation
void automatic(){
 Segmentation(filename,angle,1);
 pin_up_angle_image();
}

/*void save(){
 const gchar *text_final =  gtk_entry_get_tabs(GTK_ENTRY(texte));
 printf("%s\n",text_final);
 printf("coucou");
 //ajouter le texte dans le fichier.
}*/
//Call when the button button_corrected is "clicked".
//It is destroying the useless widgets and call the neural network
void correct(){
 gtk_widget_destroy(button_Validate);
 gtk_widget_destroy(button_auto);
 gtk_widget_destroy(image);
 gtk_widget_destroy(label);
 gtk_widget_destroy(entry);
 gtk_widget_destroy(button_corrected);
 //function to call the neurone network
 registe = gtk_button_new_with_label("Regiter");
 gtk_grid_attach(GTK_GRID(table),registe,0,1,2,1);
 texte = gtk_text_view_new();
 //g_signal_connect(G_OBJECT(registe),"clicked",G_CALLBACK(save),NULL);
 gtk_grid_attach(GTK_GRID(table),texte,0,0,2,1);
 gtk_widget_show_all(table);
}

//function activated after clicking on "Ouvrir" in dialog box
//it creates a gtk tabkle which contain the image, a label, an entry and a button
void pin_up_image ()
{
  gtk_widget_destroy(button);
  gtk_widget_destroy(button_box);
  
  table = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window),table);

  SDL_Surface *img = IMG_Load(filename);
  int h = img->h;
  int w = img->w;
  free(img);
  GdkPixbuf *dest;
  dest = gdk_pixbuf_new_from_file(filename,NULL);
  dest = gdk_pixbuf_scale_simple(dest,w/2,h/2,GDK_INTERP_BILINEAR);
  image = gtk_image_new_from_pixbuf(dest);
  label = gtk_label_new("Enter the rotation angle of the image :");
  entry = gtk_entry_new();
  button_Validate = gtk_button_new_with_label("Validate");
  button_auto = gtk_button_new_with_label("Automatic recovery");
  button_corrected = gtk_button_new_with_label("Angle corrected");
  gtk_grid_attach(GTK_GRID(table),entry,0,2,2,1);
  gtk_grid_attach(GTK_GRID(table),label,0,1,2,1);
  gtk_grid_attach(GTK_GRID(table),image,0,0,2,1);
  gtk_grid_attach(GTK_GRID(table),button_Validate,0,3,2,1);
  gtk_grid_attach(GTK_GRID(table),button_auto,0,4,2,1);
  gtk_grid_attach(GTK_GRID(table),button_corrected,0,5,2,1);
  g_signal_connect(G_OBJECT(button_auto),"clicked",G_CALLBACK(automatic),NULL);
  g_signal_connect(G_OBJECT(button_Validate),"clicked",G_CALLBACK(validate),NULL);
  g_signal_connect(G_OBJECT(button_corrected),"clicked",G_CALLBACK(correct),NULL);
  gtk_widget_show_all(window);
}

//function activated with the button "Importer une image"
//this function creates a dialog box and create a link with the function "pin_up_image" and the button "Ouvrir"
void open_dialog_box()
{
 GtkWidget *dialog;
 GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
 gint res;

 dialog = gtk_file_chooser_dialog_new("Ouvrir fichier", NULL, action,"Annuler",GTK_RESPONSE_CANCEL,"Ouvrir", GTK_RESPONSE_ACCEPT, NULL);
 
 res = gtk_dialog_run(GTK_DIALOG(dialog));
 if(res == GTK_RESPONSE_ACCEPT)
  {
   GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
   filename = gtk_file_chooser_get_filename(chooser);
   gtk_widget_destroy(dialog);
   pin_up_image();
  }
 if(res == GTK_RESPONSE_CANCEL)
 {
   gtk_widget_destroy(dialog);
 }
}
// function called just after openning the application in main
// it creates a button and link it with "open_dialog_box"
void activate (GtkApplication* app)
{
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "OCR");
  gtk_window_set_default_size (GTK_WINDOW (window), 100, 100);
	
  button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add(GTK_CONTAINER(window), button_box);

  button = gtk_button_new_with_label("Importer une image");
  gtk_container_add(GTK_CONTAINER(button_box), button);
  g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(open_dialog_box), NULL);
  gtk_widget_show_all (window);
 
}
