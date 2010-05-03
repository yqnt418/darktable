/*
    This file is part of darktable,
    copyright (c) 2009--2010 johannes hanika.

    darktable is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    darktable is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with darktable.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "common/darktable.h"
#include "control/control.h"
#include "gui/gtk.h"
#include "libs/lib.h"
#include "control/jobs.h"
#include <stdlib.h>
#include <gtk/gtk.h>
#include <glade/glade.h>

DT_MODULE(1)

typedef struct dt_lib_image_t
{
}
dt_lib_image_t;

const char*
name ()
{
  return _("selected image[s]");
}

uint32_t views() 
{
  return DT_LIGHTTABLE_VIEW;
}

void
gui_reset (dt_lib_module_t *self)
{
}

static void
button_clicked(GtkWidget *widget, gpointer user_data)
{
  long int i = (long int)user_data;
  if     (i == 0) dt_control_remove_images();
  else if(i == 1) dt_control_delete_images();
  else if(i == 2) dt_control_write_dt_files();
  else if(i == 3) dt_control_duplicate_images();
  dt_control_queue_draw_all();
}

int
position ()
{
  return 700;
}

void
gui_init (dt_lib_module_t *self)
{
  // dt_lib_image_t *d = (dt_lib_image_t *)malloc(sizeof(dt_lib_image_t));
  // self->data = (void *)d;
  self->widget = gtk_vbox_new(TRUE, 5);
  GtkBox *hbox;
  GtkWidget *button;
  hbox = GTK_BOX(gtk_hbox_new(TRUE, 5));

  button = gtk_button_new_with_label(_("remove"));
  gtk_object_set(GTK_OBJECT(button), "tooltip-text", _("remove from the collection"), NULL);
  gtk_box_pack_start(hbox, button, TRUE, TRUE, 0);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(button_clicked), (gpointer)0);

  button = gtk_button_new_with_label(_("delete"));
  gtk_object_set(GTK_OBJECT(button), "tooltip-text", _("physically delete from disk"), NULL);
  gtk_box_pack_start(hbox, button, TRUE, TRUE, 0);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(button_clicked), (gpointer)1);

  gtk_box_pack_start(GTK_BOX(self->widget), GTK_WIDGET(hbox), TRUE, TRUE, 0);
  hbox = GTK_BOX(gtk_hbox_new(TRUE, 5));

  button = gtk_button_new_with_label(_("write dt files"));
  gtk_object_set(GTK_OBJECT(button), "tooltip-text", _("write history stack and tags to sidecar files"), NULL);
  gtk_box_pack_start(hbox, button, TRUE, TRUE, 0);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(button_clicked), (gpointer)2);

  button = gtk_button_new_with_label(_("duplicate"));
  gtk_object_set(GTK_OBJECT(button), "tooltip-text", _("add a duplicate to the collection"), NULL);
  gtk_box_pack_start(hbox, button, TRUE, TRUE, 0);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(button_clicked), (gpointer)3);

  gtk_box_pack_start(GTK_BOX(self->widget), GTK_WIDGET(hbox), TRUE, TRUE, 0);
}

void
gui_cleanup (dt_lib_module_t *self)
{
  // free(self->data);
  // self->data = NULL;
}

