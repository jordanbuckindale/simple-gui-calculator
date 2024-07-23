/* 
-----------------------------------------------------
Jordan Buckindale
Date: July 18 2024

This program is a simple GUI calculator built in C using the GTK library.
The goal of this project is to practice working with GUI elements and the GTK library, and to implement a GUI in a roulette C program.
-----------------------------------------------------
*/

#include<gtk/gtk.h> // import GTK library

#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
    

// set a definite variable to 
#define SIZE 10

// create a stuct with GTKwidget variables.
// these variables will make the compose the calculator.
typedef struct {
        
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button[17];

}calc;
    
GtkWidget *box;

//bufffer variables
int input_buffer[100] = {};
int output_buffer[100]= {};

// operator variables.
bool add = false;
bool mul = false;
bool divv = false; 
bool sub = false;
bool clear_buffer = false;

float result = 0.0;
static float num[SIZE];
int count = 0;

// Function to connect button to signal and compute the answer of selected user input.
static void calculate(GtkButton *button, gpointer data){

    // create text box to present calculation.
	const gchar* text = gtk_button_get_label(button);

    // select operation based off user interaction
	if( (strcmp("+", text)==0) ||   (strcmp("-", text)==0) ||  (strcmp("/", text)==0) ||  (strcmp("x", text)==0) ||  (strcmp("=", text)==0) ){
		
		num[count] = atof(input_buffer);
		count++;
		clear_buffer = true;

		if(strcmp("+",text)==0){
			add = true;
		}
		if(strcmp("-",text)==0){
			sub = true;
		}
		if(strcmp("/",text)==0){
			divv = true;
		}
		if(strcmp("x",text)==0){
			mul = true;
		}
	}

    // perform selected operation on the respective selected numbers.
	if(strcmp("=",text)==0){
		int x = sizeof(num)/sizeof(num[0]);
		
		if(add){
			for(int i=0; i<x; i++){
				result += num[i];
			}
		}

		if(divv){
			result = num[0]/num[1];
		}

		if(sub){
				if(result == 0.0){
					result = num[0]*2;
				}
			for(int i=0; i<x; i++){
				result -= num[i];
			}
		}
	
		if(mul){
			result = num[0]*num[1];
		}

        // reset the variables.
		add = false;
		mul = false;
		divv = false;
		sub = false;
		
        // reset the output screen then outputs the result of computation.
		gtk_entry_set_text(GTK_ENTRY(box), "");
		sprintf(output_buffer, "%.3f", result);
		gtk_entry_set_text(GTK_ENTRY(box), output_buffer);

        // reset the result variable that stores the result of computation.
		result = 0.0;
	}
    // clears the buffer data, and clears the output screen.
	else{
		if(clear_buffer){
			memset(input_buffer,0,strlen(input_buffer));
			clear_buffer = false;
		}else{
			strncat(input_buffer,text, 1);
		}
		
			strncat(output_buffer,text, 1);
			gtk_entry_set_text(GTK_ENTRY(box), output_buffer);
	}
    // clears the stored data when user selects 'c'.
	if(strcmp("C",text)==0){

        // reset textbox.
		gtk_entry_set_text(GTK_ENTRY(box), "");
		memset(input_buffer,0,strlen(input_buffer));
		memset(output_buffer,0,strlen(output_buffer));

        // reset count.
		count = 0;
		int x = sizeof(num)/sizeof(num[0]);
		
        // reset num array.
		for(int i=0; i<x; i++){
				num[i] = 0;
		}

        // reset variables
		add = false;
		mul = false;
		divv = false;
		sub = false;
	}
}


// Function that is the actiive signal that will be sent when the application is launched with g_application_run().g
// Function will also create the widget application. 
// specifications on size, title, position.
static void activate(GtkApplication *app, gpointer user_data) {

    // create structure to hold all the GUI elements.
    calc widget;

    // create window widget and configure settings.
    widget.window = gtk_application_window_new(app);
    // where on screen the gui will appear.
    gtk_window_set_position(GTK_WINDOW(widget.window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(widget.window), "A Simple Calculator");
    gtk_window_set_default_size(GTK_WINDOW(widget.window), 200, 200);
    gtk_container_set_border_width(GTK_CONTAINER(widget.window), 10);

    
    // create grid layout for widget application.
    widget.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(widget.window),widget.grid);

    // create the display box.
    box = gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(box), FALSE);

    // create calculator buttons. 
    widget.button[0] = gtk_button_new_with_label("0");
	widget.button[1] = gtk_button_new_with_label("1");
	widget.button[2] = gtk_button_new_with_label("2");
	widget.button[3] = gtk_button_new_with_label("3");
	widget.button[4] = gtk_button_new_with_label("4");
	widget.button[5] = gtk_button_new_with_label("5");
	widget.button[6] = gtk_button_new_with_label("6");
	widget.button[7] = gtk_button_new_with_label("7");
	widget.button[8] = gtk_button_new_with_label("8");
	widget.button[9] = gtk_button_new_with_label("9");
	widget.button[10] = gtk_button_new_with_label(".");
	widget.button[11] = gtk_button_new_with_label("+");
	widget.button[12] = gtk_button_new_with_label("-");
	widget.button[13] = gtk_button_new_with_label("x");
	widget.button[14] = gtk_button_new_with_label("/");
	widget.button[15] = gtk_button_new_with_label("C");
	widget.button[16] = gtk_button_new_with_label("=");

    // place the button widgets into specific positions (rows decending from the top)

    // 1st row (top)
    gtk_grid_attach(GTK_GRID(widget.grid),box, 0, 0, 4, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[15], 0, 1, 3, 1);
    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[14],3,1,1,1);

    // 2nd row
    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[7],0,2,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[8],1,2,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[9],2,2,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[13],3,2,1,1);
    
    // 3rd row
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[4],0,3,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[5],1,3,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[6],2,3,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[12],3,3,1,1);

    // 4th row
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[1],0,4,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[2],1,4,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[3],2,4,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[11],3,4,1,1);

    // 5th row (bottom)
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[0],0,5,2,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[10],2,5,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[16],3,5,1,1);

    // connect signals to buttons.
    // this connects the 'clicked' signal of each button to calculate function.
	g_signal_connect(widget.button[0],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[1],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[2],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[3],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[4],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[5],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[6],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[7],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[8],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[9],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[10],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[11],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[12],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[13],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[14],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[15],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[16],"clicked",G_CALLBACK(calculate), NULL);

    // makes all widgets visible.
	gtk_widget_show_all(widget.window);

}


// function to create a GtkApplication object and run it.
int main(int argc, char **argv) {

   // start application 
    GtkApplication *app;

    // initialize GTK library.
    gtk_init(&argc, &argv);

    // set variable to indicate status of application.
    int status;
    // create application object, and setting application identifier to org.gtk.calculator.
    app = gtk_application_new("org.gtk.calculator", G_APPLICATION_FLAGS_NONE);
   

   /*function that connects the callback function to signal. 
     
     parameter variables: 
     instance --> app (object that will emit signal)
     detailed_signal --> 'activate'
     c_hander --> G_CALLBACK() (a pointer to callback function)
     data --> NULL (user data passed to call back)
    */
    g_signal_connect(app, "activate",G_CALLBACK(activate),NULL);
    //initializes the application, runs loop of program, waits for interaction, returns value to consoole when exited.
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);


    return status;
}
