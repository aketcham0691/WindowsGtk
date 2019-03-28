#include <gtk/gtk.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(int argc, char *argv[])
{
    char path[PATH_MAX] = {0};
    char resource_path[PATH_MAX] = {0};

    printf("%s\n", getcwd(NULL, PATH_MAX));
    strcat(path, g_get_user_config_dir ());

    strcat(path, "/Cybersolver/test.cfg");
    printf("%s\n", path);
    GKeyFile* keyfile = g_key_file_new();
    g_key_file_load_from_file(keyfile, path, G_KEY_FILE_NONE, NULL );

    printf("%s\n", g_key_file_get_string(keyfile, "testgroup", "testkey", NULL));
    printf("here\n");
    GError* err = NULL;
    // g_resource_load ("gtktest.resource", &err);

    // if (err) {
    //     fprintf(stderr, "%s\n", err->message);
    // }
    

    GBytes* bytes = g_resources_lookup_data  ("/org/cytocybernetics/gtktest/hello.py", G_RESOURCE_LOOKUP_FLAGS_NONE, &err);
    if (err) {
        fprintf(stderr, "here: %s\n", err->message);
    }
    gsize size = 0;
    const char* program = g_bytes_get_data(bytes, &size);
    printf("program:\n%s\n", program);


    GtkBuilder      *builder; 
    GtkWidget       *window;
    GtkWidget *layout;
    GtkWidget *button;
    
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER (window), layout);
    gtk_widget_show(layout);

    err = NULL;
    GdkPixbuf* test_buff = gdk_pixbuf_new_from_file ("download.jpg", &err);
    GtkWidget* test_image = gtk_image_new_from_pixbuf(test_buff);
    
    if (err != NULL) {
        fprintf(stderr, "error: %s\n", err->message);
    }

    gtk_layout_put(GTK_LAYOUT(layout), test_image, 0, 0);

    button = gtk_button_new_with_label("Button");
    gtk_layout_put(GTK_LAYOUT(layout), button, 150, 50);
    gtk_widget_set_size_request(button, 80, 35);
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
 
    gtk_widget_show_all(window);                
    gtk_main();
 
    return 0;
}
 
// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}