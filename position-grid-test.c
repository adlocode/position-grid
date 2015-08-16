#include <gtk/gtk.h>
#include <libwnck/libwnck.h>
#include "position-grid.h"


static void 
button_enter_notify 
(GtkWidget *widget, GdkEvent *event, GtkWidget *pager)
{
	gtk_widget_show (pager);
	gtk_widget_hide (widget);
}

static void 
drag_begin_handl 
(GtkWidget *widget, GtkWidget *pager)
{
	gtk_widget_show (pager);
}

static void 
pager_leave_notify 
(GtkWidget *widget, GdkEvent *event, GtkWidget *button)
{
	gtk_widget_show (button);
	gtk_widget_hide (widget);
}

int main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *tasklist;
	GtkWidget *pager;
	GtkWidget *hbox;
	GtkWidget *button;
	
	gtk_init (&argc, &argv);
	
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	
	tasklist = position_grid_new (3,3,TRUE);
	pager = wnck_pager_new (NULL);
	button= gtk_button_new ();
	
	

		
	
	gtk_widget_set_size_request (pager, 100, 100);
	gtk_widget_set_size_request (tasklist, 500, 400);
	gtk_widget_set_size_request (button, 20, 20);
	
	hbox = gtk_hbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER(window), hbox);
	gtk_box_pack_start (GTK_BOX (hbox), tasklist, TRUE, TRUE, 0);
	
	gtk_table_attach_defaults (GTK_TABLE(tasklist), button, 0,1,0,1);
	
	button= gtk_button_new ();
	
	position_grid_attach_defaults (POSITION_GRID(tasklist), button, 7);	
					
	gtk_box_pack_start (GTK_BOX (hbox), pager, FALSE, FALSE, 0);

	
	gtk_widget_show_all (window);
	
	//gtk_widget_hide (pager);
	
	gtk_main();
	
	return 0;
	
}
	
