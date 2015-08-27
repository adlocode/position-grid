#include <gtk/gtk.h>
#include <libwnck/libwnck.h>
#include "position-grid.h"

static void clicked (GtkButton *button, GtkWidget *grid)
{

	position_grid_resize (POSITION_GRID(grid), 4, 8);	
}

static void clicked2 (GtkButton *button, GtkWidget *grid)
{

	position_grid_resize (POSITION_GRID(grid), 5, 2);	
}

int main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *pager;
	GtkWidget *hbox;
	GtkWidget *button;
	
	gtk_init (&argc, &argv);
	
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	
	grid = position_grid_new (3,3,TRUE);
	pager = wnck_pager_new (NULL);
	button= gtk_button_new ();
	
	

		
	
	gtk_widget_set_size_request (pager, 100, 100);
	gtk_widget_set_size_request (grid, 500, 400);
	gtk_widget_set_size_request (button, 20, 20);
	
	hbox = gtk_hbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER(window), hbox);
	gtk_box_pack_start (GTK_BOX (hbox), grid, TRUE, TRUE, 0);
	
	position_grid_attach (POSITION_GRID(grid), button, 1);
	
	button= gtk_button_new_with_label ("resize");
	
	position_grid_attach (POSITION_GRID(grid), button, 8);	
	
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (clicked), grid);
					
	gtk_box_pack_start (GTK_BOX (hbox), pager, FALSE, FALSE, 0);
	
	button= gtk_button_new_with_label ("resize 2");
	
	position_grid_attach (POSITION_GRID(grid), button, 10);	
	
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (clicked2), grid);
					
	
		//gtk_container_remove (GTK_CONTAINER (grid),
		//button);
	
	

	
	gtk_widget_show_all (window);
	
	//gtk_widget_hide (pager);
	
	gtk_main();
	
	return 0;
	
}
	
