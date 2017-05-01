#include <gtk/gtk.h>
#include <cairo.h>
#include <math.h>
#include <time.h>
#include "Modelo/Calles.h"
#include "Modelo/Vehiculo.h"
#include "Modelo/Iniciador.h"

#define MAX_POS 6
#define CALLES_COUNT 102 

typedef enum { ///colores
	red,
	blue,
	green,
	black,
	white,
	orange,	
	pink,
        sky,
	gray 
}colors;

typedef enum { //tipo de calles admitidas en el sistema
    rotonda,
    puente,
    calleVArr,
    calleVAb,
    calleHDer,
    calleHIz 
} tipo_calles;

struct point {
   int x;
   int y;
};

struct calle_mapper {
	int x; ///pos x
        int y; ///pos y
        int len;//longitud de la calle
        tipo_calles tipo; ///tipo de calle
};

static char buffer[256];

cairo_surface_t *image;

int ambulance_blink = 0;///es una variable para hacer el efecto de la sirena de la ambulancia

static struct calle_mapper map_array[103] = {
				{70,10,80,calleHDer},//0
				{150,10,80,calleHDer},//1
				{230,10,80,calleHDer},//2
				{310,10,80,calleHDer},//3
				{390,10,80,calleHDer},//4
				{470,10,80,calleHDer},//5
				{80,80,80,calleVArr},//6
				{140,20,80,calleVAb},//7
				{160,80,80,calleVArr},//8
				{220,20,80,calleVAb},//9
				{240,80,80,calleVArr},//10
				{300,20,80,calleVAb},//11
				{320,80,80,calleVArr},//12
				{380,20,80,calleVAb},//13
				{400,80,80,calleVArr},//14
				{460,20,80,calleVAb},//15
				{480,80,80,calleVArr},//16
				{540,20,80,calleVAb},//17
				{150,90,80,calleHIz},//18
				{230,90,80,calleHIz},//19
				{310,90,80,calleHIz},//20
				{390,90,80,calleHIz},//21
				{470,90,80,calleHIz},//22
				{550,0,80,calleHIz},//23
				{80,160,80,calleVArr},//24
				{140,100,80,calleVAb},//25
				{160,160,80,calleVArr},//26
				{220,100,80,calleVAb},//27
				{240,160,80,calleVArr},//28
				{300,100,80,calleVAb},//29
				{320,160,80,calleVArr},//30
				{380,100,80,calleVAb},//31
				{400,160,80,calleVArr},//32
				{460,100,80,calleVAb},//33
				{480,100,80,calleVArr},//34
				{540,100,80,calleVAb},//35
				{530,160,80,rotonda},///pendiente 36
				{150,180,80,puente},//37
				{230,180,80,puente},//38
				{310,180,80,puente},//39
				{390,180,80,puente},//40
				{470,180,80,puente},//41
				{80,160,80,rotonda},//pendiente 42
				{80,340,80,calleVArr},//43
				{140,280,80,calleVAb},//44
				{160,340,80,calleVArr},//45
				{220,280,80,calleVAb},//46
				{240,340,80,calleVArr},//47
				{300,280,80,calleVAb},//48
				{320,340,80,calleVArr},//49
				{380,280,80,calleVAb},//50
				{400,340,80,calleVArr},//51
				{460,280,80,calleVAb},//52
				{480,340,80,calleVArr},//53
				{540,280,80,calleVAb},//54
				{70,350,80,calleHDer},//55
				{150,350,80,calleHDer},//56
				{230,350,80,calleHDer},//57
				{310,350,80,calleHDer},//58
				{390,350,80,calleHDer},//59
				{470,350,80,calleHDer},//60
				{150,90,80,calleHIz},//61
				{230,90,80,calleHIz},//62
				{310,90,80,calleHIz},//63
				{390,90,80,calleHIz},//64
				{470,90,80,calleHIz},//65
				{550,0,80,calleHIz},//66
				{80,420,80,calleVArr},//67
				{140,360,80,calleVAb},//68
				{160,420,80,calleVArr},//69
				{220,360,80,calleVAb},//70
				{240,420,80,calleVArr},//71
				{300,360,80,calleVAb},//72
				{320,420,80,calleVArr},//73
				{380,360,80,calleVAb},//74
				{400,420,80,calleVArr},//75
				{460,360,80,calleVAb},//76
				{480,420,80,calleVArr},//77
				{540,360,80,calleVAb},//78
				{150,550,80,calleHIz},//79
				{230,550,80,calleHIz},//80
				{310,550,80,calleHIz},//81
				{390,550,80,calleHIz},//82
				{470,550,80,calleHIz},//83
				{550,550,80,calleHIz},//84
				{0,0,80,calleHIz},//85
				{0,0,80,calleHIz},//86
				{0,0,80,calleHIz},//87
				{0,0,80,calleHIz},//88
				{0,0,80,calleHIz},//89
				{0,0,80,calleHIz},//90
				{0,0,80,calleHDer},//91
				{0,0,80,calleHDer},//92
				{0,0,80,calleHDer},//93
				{0,0,80,calleHDer},//94
				{0,0,80,calleHDer},//95
				{0,0,80,calleHDer},//96
				{0,0,80,calleHIz},//97
				{0,0,80,calleHIz},//98
				{0,0,80,calleHIz},//99
				{0,0,80,calleHIz},//100
				{0,0,80,calleHIz},//102
				{0,0,80,calleHIz}//102
                                };

struct point getPosition(int street_num, int pos) {
     struct calle_mapper map_info = map_array[street_num];///obtener informacion de la calle
     struct point position;
     int pix_x = 0;
     int pix_y = 0;
     switch (map_info.tipo) {
     	case puente:
        position.x = map_info.x;
        position.y = map_info.y - (pos * map_info.len)/MAX_POS; 
	break;
	case rotonda:
        position.x = map_info.x;
        position.y = map_info.y - (pos * map_info.len)/MAX_POS;////para este se debe calcular todo de manera completamente diferente, por ahora lo voy a dejar asi :D
	break;
	case calleVArr:
        position.x = map_info.x;
        position.y = map_info.y - (pos * map_info.len)/MAX_POS; 
	break;
	case calleVAb:
        position.x = map_info.x;
        position.y = map_info.y + (pos * map_info.len)/MAX_POS; 
	break;
	case calleHDer:
	position.x = map_info.x + (pos * map_info.len)/MAX_POS;
        position.y = map_info.y; 
	break;
	case calleHIz:
        position.x = map_info.x - (pos * map_info.len)/MAX_POS;
        position.y = map_info.y;
	break;
	default:
        position.x = map_info.x;
        position.y = map_info.y; 
	break;
     }
    return position; 
}

///genera un vector de tres double para generar un color
double* getRGB(colors color) {
        static double rgb[3];
	switch(color) {
		case red: rgb[0]=1;
			  rgb[1]=0;
			  rgb[2]=0;
			  break;
		case blue: rgb[0]=0;
			  rgb[1]=0;
			  rgb[2]=0.6;
			  break;
		case green: rgb[0]=0;
			  rgb[1]=0.4;
			  rgb[2]=0;
			  break;
		case black: rgb[0]=0;
			  rgb[1]=0;
			  rgb[2]=0;
			  break;
		case white: rgb[0]=1;
			  rgb[1]=1;
			  rgb[2]=1;
			  break;
		case orange: rgb[0]=0.8;
			  rgb[1]=0.4;
			  rgb[2]=0;
			  break;
		case pink: rgb[0]=1;
			  rgb[1]=0.6;
			  rgb[2]=0.6;
			  break;
		case sky: rgb[0]=0.4;
			  rgb[1]=0.7;
			  rgb[2]=1;
			  break;
		case gray: rgb[0]=0.75;
			  rgb[1]=0.75;
			  rgb[2]=0.75;
			  break;
		default: rgb[0]=0;
			  rgb[1]=0;
			  rgb[2]=0;
			  break;		
	}
	return rgb;
}

void hello (void)
{
  g_print ("Hello World\n");
}

void destroy (void)
{
  gtk_main_quit ();
}

///los vehiculos se van a representar con circulos por simplicidad y claridad (no soy muy fan de las imagenes)
///dibuja el bus
void drawBus(int x, int y,colors color_fill, colors color_border, cairo_t *cr) {
        double* rgb_comb = getRGB(color_fill);
        cairo_set_source_rgb(cr, rgb_comb[0], rgb_comb[1], rgb_comb[2]);
        cairo_set_line_width(cr, 5);
        ///dibujo del circulo
        cairo_arc(cr, x, y, 
            8, 0, 2 * M_PI);
        cairo_stroke_preserve(cr);
        /////seteo el color de fondo
        rgb_comb = getRGB(color_border);
        cairo_set_source_rgb(cr, rgb_comb[0], rgb_comb[1], rgb_comb[2]);
        cairo_fill(cr);
	return;
}
///dibuja la ambulancia
void drawAmbulance(int x, int y, int blink, cairo_t *cr) {
        colors color_border = (blink == 0)?white:red;
	double* rgb_comb = getRGB(color_border);
        cairo_set_source_rgb(cr, rgb_comb[0], rgb_comb[1], rgb_comb[2]);
        cairo_set_line_width(cr, 5);
        ///dibujo del circulo
        cairo_arc(cr, x, y, 
            5, 0, 2 * M_PI);
        cairo_stroke_preserve(cr);
        /////seteo el color de fondo
        rgb_comb = getRGB(white);
        cairo_set_source_rgb(cr, rgb_comb[0], rgb_comb[1], rgb_comb[2]);
        cairo_fill(cr);
	return;
}
///dibuja el carro
void drawCar(int x, int y,colors color_fill, colors color_border, cairo_t *cr) {
	double* rgb_comb = getRGB(color_fill);
        cairo_set_source_rgb(cr, rgb_comb[0], rgb_comb[1], rgb_comb[2]);
        cairo_set_line_width(cr, 5);
        ///dibujo del circulo
        cairo_arc(cr, x, y, 
            4, 0, 2 * M_PI);
        cairo_stroke_preserve(cr);
        /////seteo el color de fondo
        rgb_comb = getRGB(color_border);
        cairo_set_source_rgb(cr, rgb_comb[0], rgb_comb[1], rgb_comb[2]);
        cairo_fill(cr);
	return;
}

int xc = 60;
int yc = 60;
int dirx = 2;
int diry = 2;

/* Expose Event
   se dibuja el escenario aqui, la idea es leer la estructura de datos y dibujar */
static gboolean on_expose_event (GtkWidget *widget,
                                 GdkEventExpose *event,
                                 gpointer data)
{
  cairo_t *cr;///contexto de cairo
  int width, height;//altura y anchura
  cr = gdk_cairo_create (widget->window);//crea el conexto
  gtk_window_get_size(GTK_WINDOW(widget), &width, &height);///obtengo el ancho y el alto de la ventana
  
  ///boberias de ejemplo
  if ((xc > width) || (xc < 0)) {
    dirx = dirx * -1;
  }

  if ((yc > height) || (yc < 0)) {
    diry = diry * -1;
  }

  xc = xc + dirx;
  yc = yc + diry;
  ambulance_blink = (ambulance_blink == 0)?1:0;
  cairo_set_source_surface(cr, image, 10, 10);
  cairo_paint(cr);
  drawBus(xc+50,yc,red, green, cr);
  drawCar(yc,xc, blue, red, cr);
  drawBus(xc,yc+50,gray, black, cr);
  drawCar(yc-20,xc, pink, sky, cr);
  drawAmbulance(xc-30, yc-20, ambulance_blink, cr);
  cairo_destroy(cr);

  ///revisar vector de calles y en base a eso dibujar
  for (int i = 0; i<=)
  return FALSE;
}

/* Timer event 
   Forces a window expose event.
   Consider this the main loop (framerate controlled) */
static gboolean time_handler(GtkWidget *widget)
{
  if (widget->window == NULL) 
	return FALSE;
  gtk_widget_queue_draw(widget);
  return TRUE;
}

int main (int argc, char *argv[])
{
  GtkWidget *window;
  image = cairo_image_surface_create_from_png("treadville.png");

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_signal_connect (GTK_OBJECT (window), "destroy",
                      GTK_SIGNAL_FUNC (destroy), NULL);
  gtk_container_border_width (GTK_CONTAINER (window), 10);

  g_signal_connect(G_OBJECT(window), "expose-event",
                   G_CALLBACK(on_expose_event), NULL);
  g_signal_connect(G_OBJECT(window), "destroy",
                   G_CALLBACK(gtk_main_quit), NULL);

  g_timeout_add(33, (GSourceFunc) time_handler, (gpointer) window); 
  gtk_window_set_title(GTK_WINDOW(window), "Threadville");
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 780, 440); 
  gtk_widget_set_app_paintable(window, TRUE);
  gtk_widget_show_all(window);

  time_handler(window);

  gtk_main ();

  return 0;
}
