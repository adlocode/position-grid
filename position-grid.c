/* Copyright (C) 2015 adlo
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, see <http://www.gnu.org/licenses/>
 */
 
 
#include <gtk/gtk.h>
#include <stdlib.h>
#include <math.h>
#include "position-grid.h"

static void position_grid_class_init (PositionGridClass *klass);

static void position_grid_init (PositionGrid *grid);

static void gtk_table_get_child_property (GtkContainer *container,
	GtkWidget *child, guint property_id, const GValue *value,
	GParamSpec *pspec);	
void position_grid_resize (PositionGrid *position_grid, guint rows, guint columns);

void position_grid_reattach (PositionGrid *position_grid, PositionGridChild *child, guint position);

PositionGridChild * position_grid_get_child 
	(PositionGrid *position_grid, GtkWidget *widget);





GType position_grid_get_type (void)
{
	static GType position_grid_type = 0;
	
	if (!position_grid_type)
	{
		const GTypeInfo position_grid_info =
		{
			sizeof(PositionGridClass),
			NULL, /*base_init*/
			NULL, /*base_finalize*/
			(GClassInitFunc) position_grid_class_init,
			NULL, /*class_finalize*/
			NULL,
			sizeof(PositionGrid),
			0,
			(GInstanceInitFunc) position_grid_init,
		};
		position_grid_type = g_type_register_static (GTK_TYPE_TABLE, "PositionGrid", &position_grid_info, 0);
	}
	return position_grid_type;
}

static void position_grid_class_init (PositionGridClass *klass)

{	
	
}

static void position_grid_remove (GtkObject *object, PositionGrid *grid)
{
	GtkWidget *widget;
	GList *li;
	PositionGridChild *child;
	
	widget = GTK_WIDGET (object);

	for (li = grid->children; li != NULL; li = li->next)
			{
				child = li->data;
				
				g_print ("%s", "test ");
				
				if (child->widget == widget)
				{	
					g_print ("%s", "remove ");
					g_print ("%d", child->position);
	
					grid->children = g_list_remove (grid->children, child);	
	
					g_free (child);
	
					child = NULL;
					
					break;
				}	
					
			}
				
	
	

	
	
	
}
	
static void position_grid_init (PositionGrid *grid)
{
	
  grid->children = NULL;
  
          

}
/*
void position_grid_get_table_child 
	(PositionGrid *position_grid, PositionGridChild *position_grid_child, GtkWidget *widget)
{
	GList *li;
	GtkTableChild  *table_child;
	
	for (li = GTK_TABLE (position_grid)->children; li != NULL; li = li->next)
			{
				table_child = (GtkTableChild*) li->data;

				if (table_child->widget == widget)
				{
					position_grid_child->child = (GtkTableChild*) table_child;
					
					break;
				}
				
			}
}*/



GtkWidget* position_grid_new (guint rows, guint columns, gboolean homogeneous)
{
	PositionGrid *position_grid;
	
	if (rows == 0)
		rows = 1;
		
	if (columns == 0)
		columns = 1;
		
	
	position_grid = (g_object_new (position_grid_get_type (), NULL));
	
	
	GTK_TABLE  (position_grid)->homogeneous = (homogeneous ? TRUE : FALSE);
	
	gtk_table_resize (GTK_TABLE (position_grid), rows, columns);
	
	return GTK_WIDGET (position_grid);
	
	
}

void position_grid_resize (PositionGrid *position_grid, guint rows, guint columns)
{
	GList *li;
	
	PositionGridChild *position_grid_child;
	
	gtk_table_resize (GTK_TABLE(position_grid), rows, columns);
	
	for (li = position_grid->children; li != NULL; li = li->next)
			{
					position_grid_child = (PositionGridChild *)li->data;
				
					
					

					
					position_grid_reattach (position_grid, position_grid_child, 
						position_grid_child->position);
						
					
				}
}

void position_grid_reattach (PositionGrid *position_grid, PositionGridChild *child, guint position)
{
	GtkTable *table;
	guint column_number, row_number;
	
	child->reattach = TRUE;
	
	g_object_ref (child->widget);	
					
	gtk_container_remove (GTK_CONTAINER (position_grid),
		child->widget);

	
	table = GTK_TABLE (position_grid);
	
	row_number = ceil ((double)position/(double)table->ncols);
	
	column_number = position - ((row_number -1) * table->ncols);

	
	gtk_table_attach_defaults (GTK_TABLE (position_grid), child->widget, column_number -1,
		column_number, row_number - 1, row_number);
		
	g_object_unref (child->widget);
	
	child->reattach = FALSE;	
	
}

void position_grid_attach (PositionGrid *position_grid, GtkWidget *widget, guint position)
{
	PositionGridChild * position_grid_child;
	GtkTable *table;
	guint column_number, row_number;
	
	position_grid_child = g_new (PositionGridChild, 1);
	
	position_grid_child->widget = widget;
	
	position_grid_child->position = position;
	
	position_grid_child->reattach = FALSE;
	
	
	table = GTK_TABLE (position_grid);
	
	row_number = ceil ((double)position/(double)table->ncols);
	
	column_number = position - ((row_number -1) * table->ncols);
	
	
	gtk_table_attach_defaults (GTK_TABLE (position_grid), widget, column_number -1,
		column_number, row_number - 1, row_number);
	
	g_signal_connect (GTK_OBJECT (widget), "destroy", G_CALLBACK (position_grid_remove), position_grid); 
	
	position_grid->children = g_list_prepend (position_grid->children, position_grid_child);
	
	
}
	


	
