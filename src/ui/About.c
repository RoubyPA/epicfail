#include "About.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HEIGHT 400
#define WIDTH 350

/*private*/ static void on_quit (GtkWidget *w, gpointer data);
/*private*/ static void About_init_0 (About *self);
/*private*/ static void About_new_window (About *self);
/*private*/ static void About_create_image (About *self);
/*private*/ static void About_create_label (About *self);
/*private*/ static void About_connect (About *self);
/*private*/ static void About_hide (About *self);

/******************************************************************************
 * Public methode                                                             *
 ******************************************************************************/

/*public*/ GType
About_get_type (void)
{
  static GType type = 0;

  if (type == 0)
  {
    static const GTypeInfo info = {
      sizeof (AboutClass), /* class_size */
      NULL,                /* base_init */
      NULL,                /* base_finalize */
      NULL,                /* class_init */
      NULL,                /* class_finalize */
      NULL,                /* class_data */
      sizeof (About),      /* instance_size */
      0,                   /* n_preallocs */
      NULL,                /* instance_init */
      NULL                 /* value_table */
    };
    type = g_type_register_static (G_TYPE_OBJECT, "About", &info, 0);
  }
  return type;
}


/*public*/ void
About_init (About *self, Config *conf)
{
  About_init_0 (self);

  self->conf = conf;
  self->title = self->conf->dico.About_title;
}

/*public*/ void
About_create (About *self)
{
  About_new_window (self);
  About_connect (self);
}

/*public*/ void
About_show (About *self)
{
  gtk_widget_show_all(self->window);
}


/******************************************************************************
 * Private method                                                             *
 ******************************************************************************/

/*private*/ static void
on_quit (GtkWidget *w, gpointer data)
{
  About *self = (About *)data;

  self->window = w;
  About_hide (self);
}

/*private*/ static void
About_init_0 (About *self)
{
  self->title = NULL;
  
  self->window = NULL;
  self->m_vbox = NULL;
  self->label = NULL;
  self->image = NULL;
}

/*private*/ static void
About_hide (About *self)
{
  gtk_widget_hide (self->window);
}

/*private*/ static void
About_new_window (About *self)
{
  self->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title (GTK_WINDOW(self->window), self->title);
  gtk_window_set_position (GTK_WINDOW (self->window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW(self->window),
			       HEIGHT, WIDTH);
  gtk_window_set_resizable (GTK_WINDOW(self->window), FALSE);
  
  self->m_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
  self->label = gtk_label_new ("");

  About_create_image (self);
  About_create_label (self);

  gtk_container_add (GTK_CONTAINER (self->window), self->m_vbox);
  gtk_box_pack_start (GTK_BOX (self->m_vbox), self->image,
		      FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (self->m_vbox), self->label,
		      FALSE, TRUE, 0);
}

/*private*/ static void
About_create_image (About *self)
{
  char *buffer = malloc (256); /* TODO global macro */
  MALLOC_TEST_ERROR (buffer);

  strcpy(buffer, self->conf->dir);
  strcat(buffer, "/images/epicfail.png");
    
  self->image = gtk_image_new_from_file (buffer);

  free (buffer);
}


/*private*/ static void
About_create_label (About *self)
{
  gchar *buffer;
  
  buffer = g_locale_to_utf8 (self->conf->dico.About_label, -1, NULL, NULL, NULL);
  gtk_label_set_justify (GTK_LABEL (self->label), GTK_JUSTIFY_CENTER);
  gtk_label_set_markup (GTK_LABEL (self->label), buffer);
}

/*private*/ static void
About_connect (About *self)
{
  g_signal_connect( G_OBJECT(self->window), "delete-event",
                    G_CALLBACK(on_quit), (gpointer)self);
}
