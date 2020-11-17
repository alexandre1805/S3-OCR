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
GtkWidget *buttonV;
GtkWidget *table;
GtkWidget *entry;
GtkWidget *label;
int angle = 0;

// function activated when user click on the button "Valider".
// Destroys all widgets and print the angle from the entry
void validate()
{
  const gchar *agle = gtk_entry_get_text(GTK_ENTRY(entry));
  angle = atoi(agle);
  gtk_widget_destroy(buttonV);
  gtk_widget_destroy(image);
  gtk_widget_destroy(label);
  gtk_widget_destroy(entry);
  gtk_widget_destroy(table);
  printf("angle : %d\n", angle);
  Segmentation(filename, angle);
}

//function activated after clicking on "Ouvrir" in dialog box
//it creates a gtk tabkle which contain the image, a label, an entry and a button
void pin_up_image()
{
  gtk_widget_destroy(button);
  gtk_widget_destroy(button_box);

  table = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), table);

  SDL_Surface *img = IMG_Load(filename);
  int h = img->h;
  int w = img->w;
  free(img);
  GdkPixbuf *dest;
  dest = gdk_pixbuf_new_from_file(filename, NULL);
  dest = gdk_pixbuf_scale_simple(dest, w / 3, h / 3, GDK_INTERP_BILINEAR);
  image = gtk_image_new_from_pixbuf(dest);

  label = gtk_label_new("Saisir l'angle de rotation de l'image :");
  entry = gtk_entry_new();
  buttonV = gtk_button_new_with_label("Valider");
  gtk_grid_attach(GTK_GRID(table), entry, 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(table), label, 0, 1, 2, 1);
  gtk_grid_attach(GTK_GRID(table), image, 0, 0, 2, 1);
  gtk_grid_attach(GTK_GRID(table), buttonV, 1, 2, 1, 1);
  g_signal_connect(G_OBJECT(buttonV), "clicked", G_CALLBACK(validate), NULL);
  gtk_widget_show_all(window);
}

//function activated with the button "Importer une image"
//this function creates a dialog box and create a link with the function "pin_up_image" and the button "Ouvrir"
void open_dialog_box()
{
  GtkWidget *dialog;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;

  dialog = gtk_file_chooser_dialog_new("Ouvrir fichier", NULL, action, "Annuler", GTK_RESPONSE_CANCEL, "Ouvrir", GTK_RESPONSE_ACCEPT, NULL);

  res = gtk_dialog_run(GTK_DIALOG(dialog));
  if (res == GTK_RESPONSE_ACCEPT)
  {
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
    filename = gtk_file_chooser_get_filename(chooser);
    gtk_widget_destroy(dialog);
    pin_up_image();
  }
  if (res == GTK_RESPONSE_CANCEL)
  {
    gtk_widget_destroy(dialog);
  }
}
// function called just after openning the application in main
// it creates a button and link it with "open_dialog_box"
void activate(GtkApplication *app)
{
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "OCR");
  gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);

  button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add(GTK_CONTAINER(window), button_box);

  button = gtk_button_new_with_label("Importer une image");
  gtk_container_add(GTK_CONTAINER(button_box), button);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(open_dialog_box), NULL);
  gtk_widget_show_all(window);
}
