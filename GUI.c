#include <gtk/gtk.h>
char *filename;
GtkWidget *window;

GtkWidget *button;
GtkWidget *button_box;
void pin_up_image ()
{
  fprintf(stdout,"pinup activé, %s",filename);
  gtk_widget_destroy(button);
  gtk_widget_destroy(button_box);
  GtkWidget *image;
  GtkWidget *table;
  table = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window),table);
  image = gtk_image_new_from_file(filename);
  gtk_grid_attach(GTK_GRID (table),image,1,10,1,10);
  gtk_widget_show_all(window);
}

void open_dialog_box(GtkApplication* app, gpointer user_data)
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
void activate (GtkApplication* app, gpointer user_data)
{
  GtkWidget *label;
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "OCR");
  gtk_window_set_default_size (GTK_WINDOW (window), 1280, 720);
	
  button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add(GTK_CONTAINER(window), button_box);

  button = gtk_button_new_with_label("Importer une image");
  gtk_container_add(GTK_CONTAINER(button_box), button);
  g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(open_dialog_box), NULL);
  gtk_widget_show_all (window);
 
} /* gtk_container_remove(GTK_CONTAINER(button_box), button);*/
