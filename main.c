#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <gtk/gtk.h>
#include <glib/gprintf.h>
#include <libconfig.h> 
//in ubuntu sudo apt-get install libconfig-dev
//in msys2: pacman -S mingw-w64-x86_64-libconfig
//#include <conio.h>

GtkBuilder *builder;
GObject *window;

GObject *entry1;
GObject *label1;
GObject *button_read1;
GObject *button_write1;

GObject *entry2;
GObject *label2;
GObject *button_read2;
GObject *button_write2;

GObject *switch1;
GObject *label3;
GObject *button_read3;

GObject *button_delete_conf;
GObject *button_create_conf;
GObject *button_read_all;
GObject *button_write_all;

GObject *scrolledwindow1;
GObject *treeview1;
GObject *button_clear1;

enum{
    LIST_ITEM=0,
    N_COLUMNS
};
void print_me( const gchar * data){
        GtkListStore *store;
        GtkTreeIter iter;
        store=GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview1)));
        gtk_list_store_append(store,&iter);
        gtk_list_store_set(store,&iter,LIST_ITEM,data,-1);
}
void on_button_read1_clicked(){
    print_me("\nbutton read 1 clicked\n ----------------------------------------------------");
   
    config_t cfg;
    config_init(&cfg);

    if (!config_read_file(&cfg, "config.cfg")) {
        fprintf(stderr, "Error: %s\n", config_error_text(&cfg));
        config_destroy(&cfg);
        return;
    }


    int setting_value;
    if (config_lookup_int(&cfg, "setting1", &setting_value)) {
            gchar mystr[50]="aaaaaaaaaa";
            g_sprintf(mystr, "setting1 = %d\n", setting_value);
            print_me(mystr);
            sprintf(mystr, "%d", setting_value);
            gtk_label_set_text(GTK_LABEL(label1),mystr);
    } else {
        fprintf(stderr, "Error: Failed to read setting\n");
    }
    config_destroy(&cfg);
  
}
void on_button_read2_clicked(GtkWidget *widget,gpointer label)
{
    print_me("\nbutton read 2 clicked\n ----------------------------------------------------");
    config_t cfg;
    config_init(&cfg);

    if (!config_read_file(&cfg, "config.cfg")) {
        fprintf(stderr, "Error: %s\n", config_error_text(&cfg));
        config_destroy(&cfg);
        return;
    }

    const char* setting_value;
    if (config_lookup_string(&cfg, "setting2", &setting_value)) {
        print_me(setting_value);
        gtk_label_set_text(GTK_LABEL(label2),setting_value);
    } else {
        fprintf(stderr, "Error: Failed to read setting2\n");
    }

    config_destroy(&cfg);
}
void on_button_read3_clicked(){
    print_me("\nbutton read 3 clicked\n ----------------------------------------------------");
   
    config_t cfg;
    config_init(&cfg);

    if (!config_read_file(&cfg, "config.cfg")) {
        fprintf(stderr, "Error: %s\n", config_error_text(&cfg));
        config_destroy(&cfg);
        return;
    }

    int setting3_value;

    if (config_lookup_bool(&cfg, "setting3", &setting3_value)) {  
            gchar mystr[50]="aaaaaaaaaa";         
            g_sprintf(mystr, "setting3 = %d", setting3_value);
            print_me(mystr);
            sprintf(mystr, "%d", setting3_value);
            gtk_label_set_text(GTK_LABEL(label3),mystr);
    } else {
        fprintf(stderr, "Error: Failed to read setting3\n");
    }

    config_destroy(&cfg);
}
void on_button_read_all_clicked(GtkWidget *widget,gpointer label)
{
    print_me("\nbutton read all clicked\n ----------------------------------------------------");
    config_t cfg;
    config_init(&cfg);

    if (!config_read_file(&cfg, "config.cfg")) {
        fprintf(stderr, "Error: %s\n", config_error_text(&cfg));
        config_destroy(&cfg);
        return;
    }
    gchar mystr[50]="aaaaaaaaaa";
    int setting1_value;
    if (config_lookup_int(&cfg, "setting1", &setting1_value)) {           
            g_sprintf(mystr, "setting1 = %d", setting1_value);
            print_me(mystr);
            sprintf(mystr, "%d", setting1_value);
            gtk_label_set_text(GTK_LABEL(label1),mystr);
    } else {
        fprintf(stderr, "Error: Failed to read setting\n");
    }

    const char* setting2_value;
    if (config_lookup_string(&cfg, "setting2", &setting2_value)) {
        gtk_label_set_text(GTK_LABEL(label2),setting2_value);
        g_sprintf(mystr, "setting2 = %s", setting2_value);
        print_me(mystr);
    } else {
        fprintf(stderr, "Error: Failed to read setting2\n");
    }

    int setting3_value;
    if (config_lookup_bool(&cfg, "setting3", &setting3_value)) {           
            g_sprintf(mystr, "setting3 = %d", setting3_value);
            print_me(mystr);
            sprintf(mystr, "%d", setting3_value);
            gtk_label_set_text(GTK_LABEL(label3),mystr);
			gtk_switch_set_active(GTK_SWITCH(switch1),!setting3_value) ; 
    } else {
        fprintf(stderr, "Error: Failed to read setting3\n");
    }
    config_destroy(&cfg);
}
//
void on_button_write1_clicked(GtkWidget *widget,gpointer label1)
{
    print_me("\nbutton write 1 clicked\n ----------------------------------------------------");
    print_me("trying write entry1 text to setting1 in config.cfg");
    print_me(gtk_entry_get_text	(GTK_ENTRY(entry1)));

    config_t cfg;
    config_init(&cfg);

    // Load the configuration file
    if (!config_read_file(&cfg, "config.cfg")) {
        char myerrorstr[20]=" ";
        sprintf(myerrorstr, "%s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
        print_me(myerrorstr);
        config_destroy(&cfg);
        return;
    }

    // Update one setting
    config_setting_t *setting1 = config_lookup(&cfg, "setting1");
    if (setting1 != NULL) {
        //int setting_value=atoi(gtk_entry_get_text	(GTK_ENTRY(entry1)));
        config_setting_set_int(setting1, atoi(gtk_entry_get_text	(GTK_ENTRY(entry1))));
    }

    config_write_file(&cfg, "config.cfg");

    config_destroy(&cfg);

}
void on_button_write2_clicked(GtkWidget *widget,gpointer label2){
    print_me("\nbutton write 2 clicked\n ----------------------------------------------------");
    print_me("trying write entry2 text to setting2 in config.cfg");
    print_me(gtk_entry_get_text	(GTK_ENTRY(entry2)));
    config_t cfg;
    config_init(&cfg);
    // Load the configuration file
    if (!config_read_file(&cfg, "config.cfg")) {
        char myerrorstr[20]="test ";
        sprintf(myerrorstr, "%s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
        print_me(myerrorstr);
        config_destroy(&cfg);
        return;
    }

    // Update one setting
    config_setting_t *setting2 = config_lookup(&cfg, "setting2");
    if (setting2 != NULL) {
        config_setting_set_string	(setting2, gtk_entry_get_text (GTK_ENTRY(entry2)));
    }

    config_write_file(&cfg, "config.cfg");

    config_destroy(&cfg);
}
void on_switch1_state_set(GtkWidget *widget,gpointer label1){
    print_me("\nswitch 1 state set()\n ----------------------------------------------------");
   // print_me("trying write entry1 text to setting3 in config.cfg");;

    config_t cfg;
    config_init(&cfg);

    // Load the configuration file
    if (!config_read_file(&cfg, "config.cfg")) {
        char myerrorstr[20]=" ";
        sprintf(myerrorstr, "%s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
        print_me(myerrorstr);
        config_destroy(&cfg);
        return;
    }

    // Update one setting
    config_setting_t *setting3 = config_lookup(&cfg, "setting3");
    if (setting3 != NULL) {
        config_setting_set_bool(setting3,gtk_switch_get_state(GTK_SWITCH(switch1)));
    }

    config_write_file(&cfg, "config.cfg");

    config_destroy(&cfg);

}
//
void on_button_write_all_clicked(GtkWidget *widget,gpointer   user_data){
    print_me("\nbutton write all clicked\n ----------------------------------------------------");
    config_t cfg;
    config_init(&cfg);
    // Load the configuration file
    if (!config_read_file(&cfg, "config.cfg")) {
        char myerrorstr[20]=" ";
        sprintf(myerrorstr, "%s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
        print_me(myerrorstr);
        config_destroy(&cfg);
        return;
    }
    config_setting_t *setting1 = config_lookup(&cfg, "setting1");
    if (setting1 != NULL) {
        config_setting_set_int(setting1, atoi(gtk_entry_get_text	(GTK_ENTRY(entry1))));
    }
    config_setting_t *setting2 = config_lookup(&cfg, "setting2");
    if (setting2 != NULL) {
        config_setting_set_string	(setting2, gtk_entry_get_text (GTK_ENTRY(entry2)));
    }
    config_write_file(&cfg, "config.cfg");
    config_destroy(&cfg);
}
//
void on_button_delete_conf_clicked(){
    if (remove("config.cfg") == 0) {
        print_me("File deleted successfully.\n");
    } else {
        print_me("Unable to delete the file.\n");
    }
}
void on_button_create_conf_clicked(){
    print_me("\nbutton create conf clicked\n ----------------------------------------------------");
    config_t cfg;
    config_init(&cfg);
    // Create two settings
    config_setting_t *setting1 = config_setting_add(config_root_setting(&cfg), "setting1", CONFIG_TYPE_INT		);
    config_setting_t *setting2 = config_setting_add(config_root_setting(&cfg), "setting2", CONFIG_TYPE_STRING	);
    config_setting_t *setting3 = config_setting_add(config_root_setting(&cfg), "setting3", CONFIG_TYPE_BOOL		);
    config_setting_set_int		(setting1, 10			);
    config_setting_set_string	(setting2, "Hello World");
    config_setting_set_bool		(setting3, 0			);
    config_write_file(&cfg, "config.cfg");
    config_destroy(&cfg);
     print_me("config.cfg file created");
}
//
void on_button_clear1_clicked(){
    //Remove All item
    GtkListStore *store;
    GtkTreeModel *model;
    GtkTreeIter iter;
    model=gtk_tree_view_get_model(GTK_TREE_VIEW(treeview1));
    store=GTK_LIST_STORE(model);
    if(gtk_tree_model_get_iter_first(model,&iter)==FALSE)
        return ;
    gtk_list_store_clear(store);
}
void scroll_bottom_gravity (GtkWidget    *scrolled_window,GdkRectangle *allocation,gpointer      user_data){
    GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment (GTK_SCROLLED_WINDOW (scrolled_window));
    double *from_bottom = user_data;
    double upper = gtk_adjustment_get_upper (adjustment);
    double page_size = gtk_adjustment_get_page_size (adjustment);
    gtk_adjustment_set_value (adjustment, upper - page_size - *from_bottom);
}


int main (int   argc,char *argv[]){

	gtk_init (&argc, &argv);
	builder = gtk_builder_new ();
	gtk_builder_add_from_file 		(builder, "ui.glade", NULL);
	window				=gtk_builder_get_object (builder, "window"			    );
    entry1              =gtk_builder_get_object	(builder, "entry1"              );
    entry2              =gtk_builder_get_object	(builder, "entry2"              );

	label1				=gtk_builder_get_object	(builder, "label1"			    );
	label2				=gtk_builder_get_object	(builder, "label2"			    );
	label3				=gtk_builder_get_object	(builder, "label3"			    );

	button_read1		=gtk_builder_get_object (builder, "button_read1"	    );
	button_read2		=gtk_builder_get_object (builder, "button_read2"	    );
	button_read3		=gtk_builder_get_object (builder, "button_read3"	    );

	button_write1		=gtk_builder_get_object (builder, "button_write1"	    );
	button_write2		=gtk_builder_get_object (builder, "button_write2"	    );
    switch1             =gtk_builder_get_object (builder, "switch1"	    );

	button_delete_conf	=gtk_builder_get_object (builder, "button_delete_conf"  );
	button_create_conf	=gtk_builder_get_object (builder, "button_create_conf"  );

	button_read_all		=gtk_builder_get_object (builder, "button_read_all"     );
	button_write_all	=gtk_builder_get_object (builder, "button_write_all"    );
    
    scrolledwindow1	    =gtk_builder_get_object (builder, "scrolledwindow1"     );
    treeview1           =gtk_builder_get_object (builder, "treeview1"           );
    button_clear1       =gtk_builder_get_object (builder, "button_clear1"       );
	gtk_builder_connect_signals(builder, NULL);
	//############################################################################
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1),gtk_tree_view_column_new_with_attributes("List 1",gtk_cell_renderer_text_new(),"text",LIST_ITEM,NULL));
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview1),GTK_TREE_MODEL(GTK_LIST_STORE(gtk_list_store_new(N_COLUMNS,G_TYPE_STRING))));
	double from_bottom = 0.00;
    g_signal_connect (scrolledwindow1, "size-allocate", (GCallback) scroll_bottom_gravity, &from_bottom);
	//############################################################################
    print_me("\nStartup reading all settings... \n ----------------------------------------------------");
    config_t cfg;
    config_init(&cfg);

    if (!config_read_file(&cfg, "config.cfg")) {
        fprintf(stderr, "Error: %s\n", config_error_text(&cfg));
        config_destroy(&cfg);
        return 0;
    }
    gchar mystr[50]="aaaaaaaaa";
    int setting1_value;
    if (config_lookup_int(&cfg, "setting1", &setting1_value)) {           
            g_sprintf(mystr, "setting1 = %d", setting1_value);
            print_me(mystr);
            sprintf(mystr, "%d", setting1_value);
            gtk_label_set_text(GTK_LABEL(label1),mystr);
    } else {
        fprintf(stderr, "Error: Failed to read setting\n");
    }

    const char* setting2_value;
    if (config_lookup_string(&cfg, "setting2", &setting2_value)) {
        gtk_label_set_text(GTK_LABEL(label2),setting2_value);
        g_sprintf(mystr, "setting2 = %s", setting2_value);
        print_me(mystr);
    } else {
        fprintf(stderr, "Error: Failed to read setting2\n");
    }

    int setting3_value=0;
    if (config_lookup_bool(&cfg, "setting3", &setting3_value)) {                       
            g_sprintf(mystr, "setting3 = %d", setting3_value);
            print_me(mystr);
            sprintf(mystr, "%d", setting3_value);
            gtk_label_set_text(GTK_LABEL(label3),mystr);
            gtk_switch_set_active(GTK_SWITCH(switch1),!setting3_value) ; 
    } else {
        fprintf(stderr, "Error: Failed to read setting3\n");
    }
    config_destroy(&cfg);
//############################################################################

	gtk_main ();

	return 0;
}
