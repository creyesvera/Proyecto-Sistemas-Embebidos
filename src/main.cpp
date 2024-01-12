#include <Arduino.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2

const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };


void writeDisclaimer(void){
  display.setTextSize(1); //Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20,0);
  display.println("-Disclaimer-");

  display.setCursor(0,8);
  display.println("Este producto fue ");
  display.setCursor(0, 16);
  display.println("creado con fines edo-");
  display.setCursor(0, 24); 
  display.println("ativos.No nos");
  display.setCursor(0, 32);
  display.println("hacemos responsables");
  display.setCursor(0, 40);
  display.println("del mal uso que se le");
  display.setCursor(0, 48);
  display.println("pueda dar a cualquier");
  display.setCursor(0, 50);
  display.println("parte del desarrollo XD");

  display.display(); 
  delay (4000);

  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor (SSD1306_WHITE);

  display.setCursor(0, 8);
  display.println("Cualquier parecido");
  display.setCursor (0, 16);
  display.println("con algun personaje");
  display.setCursor(0, 24);
  display.println("ficticio es mera");
  display.setCursor (0, 32);
  display.println("coincidencia. =)");
  display.setCursor(0, 48);
  display.println("att: XD");

  display.display(); 
  delay (2000);
}

const unsigned char puercoin [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xff, 0xf0, 0x00, 0x00, 0x01, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xff, 0xf0, 0x00, 0x00, 0x01, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x78, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x78, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x78, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x78, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x78, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x78, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xff, 0xfc, 0x00, 0x00, 0x07, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xff, 0xfc, 0x00, 0x00, 0x07, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xff, 0xfc, 0x00, 0x00, 0x07, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xff, 0xfc, 0x00, 0x00, 0x07, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x7f, 0xff, 0xe0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x7f, 0xff, 0xe0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x7f, 0xff, 0xe0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x7f, 0xff, 0xc0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x1f, 0xff, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x1f, 0xff, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x1f, 0xff, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x1f, 0xff, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x7f, 0xff, 0xc0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x7f, 0xff, 0xc0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x7f, 0xff, 0xc0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x7f, 0xff, 0xe0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x7f, 0xff, 0xe0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 400)


// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 400)
const int epd_bitmap_allArray_LEN = 2;
const unsigned char* epd_bitmap_allArray[2] = {
	puercoin
};


void drawbitmapUMG (void) { //testdrawbitmap
display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
}

void drawLogoPuercoin(void) {
display.clearDisplay();
display.drawBitmap (0,0, puercoin, 128, 64, 1);
display.display();
delay(2000);
}

void drawintro(void){
display.clearDisplay();
display.setTextSize(1); // Draw 2X-scale text 
display.setTextColor (SSD1306_WHITE); 
display.setCursor (30, 0);
display.println("-Bienvenido-");

display.setTextSize(1); 
display.setCursor (28, 8); 
display.println("Nivel 1: $2");

display.setTextSize(1); 
display.setCursor (28, 16); 
display.println("Nivel 2: $5");

display.setTextSize(1); 
display.setCursor (28, 24); 
display.println("Nivel 3: $10");

display.setTextSize(1);
display.setCursor (28, 32); 
display.println("Nivel 4: $20");

display.setTextSize(1); 
display.setCursor(28, 40); 
display.println("Nivel 5: $50");

display.setTextSize(1); // Draw 2X-scale text 
display.setTextColor (SSD1306_WHITE);
display.setCursor(4, 48);
display.println("Inserta una moneda");

display.setTextSize(1);
display.setCursor(2, 56);
display.println(" para continuar...");

display.display(); 
//delay(1000);
}

void animacionFinal (const uint8_t *bitmap, uint8_t w, uint8_t h) { //testanimate
  int8_t f, icons[NUMFLAKES][3];

  // Initialize 'snowflake' positions
  for(f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(1, 6);
    Serial.print(F("x: "));
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(F(" y: "));
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(F(" dy: "));
    Serial.println(icons[f][DELTAY], DEC);
  }

  for(;;) { // Loop forever...
    display.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for(f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
    }

    display.display(); // Show the display buffer on the screen
    delay(200);        // Pause for 1/10 second

    // Then update coordinates of each flake...
    for(f=0; f< NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= display.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
}



//Puerto para boton de RESET
const int btnReset = 32;

const int btnBocina=18;

//Puertos de entrada y salida del sensor
const int sensorEntrada = 13;
const int sensorSalida = 14;

//Puertos para diferenciar el tamaño de las monedas
const int sMoneda1 = 27; //Detecta moneda $1
const int sMoneda2 = 26; //Detecta moneda $2
const int sMoneda3 = 25; //Detecta moneda $5
const int sMoneda4 = 33; //Detecta moneda $10

//Variables para la cantidad de monedas por separado
int monCincuenta = 0;
int monUno = 0;
int monDos = 0;
int monCinco = 0;
int monDiez = 0;

int valorProgresBar =0;
int numeroNivel =1;
int metaNivel_actual =20;
int metaNivel_prev =0; //valor dinero

//Variable para la suma total de monedas
float dineroTotal = 0;
int monedasTotales = 0;

//Variables que se utilizan dentro de la interrupcion
bool senEntrada = LOW;
bool senSalida = HIGH;
volatile boolean monedaNueva = LOW;

//Guarda la leectura de los tamaños de monedas
boolean boolMoneda1 = LOW;
boolean boolMoneda2 = LOW;
boolean boolMoneda3 = LOW;
boolean boolMoneda4 = LOW;

//Funcion que se ejecuta cuando se inserta una moneda en el sensor
void Ext_INT_sensorEntrada(){  
  senEntrada = HIGH;
  senSalida = LOW;
}

void Ext_INT_sMoneda1(){  
  boolMoneda1 = HIGH;
}

void Ext_INT_sMoneda2(){  
  boolMoneda2 = HIGH;
}

void Ext_INT_sMoneda3(){  
  boolMoneda3 = HIGH;
}

void Ext_INT_sMoneda4(){  
  boolMoneda4 = HIGH;
}

//Funcion que se ejecuta cuando sale la moneda del sensor
void Ext_INT_sensorSalida(){
  senEntrada = LOW;
  senSalida = HIGH;

}

void Ext_INT_reset(){
    monCincuenta = 0;
    monUno = 0;
    monDos = 0;
    monCinco = 0;
    monDiez = 0;

    
    //EEPROM.write(4, 0);
    //EEPROM.write(3, 0);
    //EEPROM.write(2, 0);
    //EEPROM.write(1, 0);
    //EEPROM.write(0, 0);
    //EEPROM.commit();
    
    //Cálculo de total de monedas y dinero
      monedasTotales = 0;
      dineroTotal = 0;
    
      Serial.print("$0.10:");
      Serial.print(monCincuenta);
      Serial.print("$0.05:");
      Serial.print(monUno);
      Serial.print("$0.25:");
      Serial.print(monDos);
      Serial.print(" $1:");
      Serial.print(monCinco);
      Serial.print("$0.50:");
      Serial.print(monDiez);
      Serial.print(" Total: $");
      Serial.print(dineroTotal);
      Serial.print(" Monedas:");
      Serial.print(monedasTotales);
      Serial.println();    
  	  drawintro();
}

//Funcion para llenar Progress bar
void drawProgress(void){
  display.clearDisplay();
  display.drawRect (0, 0, 128, 46, SSD1306_WHITE);
  display.drawRect(0, 47, 128, 17, SSD1306_WHITE);
  display.drawLine (35, 0, 35, 44, SSD1306_WHITE);
  display.fillRect(2, 50, valorProgresBar, 11, WHITE);

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor (SSD1306_WHITE);
  display.setCursor(53, 15);
  display.println(dineroTotal);
  display.setCursor(40, 15);
  display.println("$");
  display.setCursor (14, 18);
  display.println(numeroNivel);

  display.setTextSize(1);
  display.setCursor(4, 4);
  display.println("Nivel");
  display.setCursor (65, 4);
  display.println("Ahorro");
  display.setCursor (37, 34);
  display.println("PUERCOIN");

  display.display(); //Para que salga la imagen en el diplay
  delay(1);
}


//Asigna el valor de la moneda y lo almacena
void asignarValorMoneda(){
  if(boolMoneda1==HIGH){
    if(boolMoneda2==HIGH){
      if(boolMoneda3==HIGH){
        if(boolMoneda4==HIGH){
          monDiez = monDiez + 1;
        }else{
          monCinco = monCinco + 1;
        }
      }else{
        monDos = monDos + 1;
      }
    }else{
      monUno = monUno + 1;
    }
  }else{
    monCincuenta = monCincuenta + 1;
  }
  //Resetea los valores de los sensores para leer otra moneda
  boolMoneda1 = LOW;
  boolMoneda2 = LOW;
  boolMoneda3 = LOW;
  boolMoneda4 = LOW;
}


//Configuracion inicial
void setup() {
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  display.clearDisplay();

  writeDisclaimer();
  drawLogoPuercoin();
  drawintro();
     
  pinMode(sensorEntrada,INPUT_PULLUP);
  pinMode(sensorSalida,INPUT_PULLUP);
  pinMode(sMoneda1,INPUT_PULLUP);
  pinMode(sMoneda2,INPUT_PULLUP);
  pinMode(sMoneda3,INPUT_PULLUP);
  pinMode(sMoneda4,INPUT_PULLUP);
  pinMode(btnReset,INPUT_PULLDOWN); 
  pinMode(btnBocina,OUTPUT); 

  attachInterrupt(sensorEntrada, Ext_INT_sensorEntrada, FALLING);
  attachInterrupt(sensorSalida, Ext_INT_sensorSalida, FALLING);
  attachInterrupt(sMoneda1, Ext_INT_sMoneda1, FALLING);  
  attachInterrupt(sMoneda2, Ext_INT_sMoneda2, FALLING);
  attachInterrupt(sMoneda3, Ext_INT_sMoneda3, FALLING);
  attachInterrupt(sMoneda4, Ext_INT_sMoneda4, FALLING);  
  attachInterrupt(btnReset, Ext_INT_reset, RISING);  

}

//Bucle repetitivo
void loop() {
 /*
     Serial.print("Sensor entrada... \t");
     Serial.print(String(senEntrada));   
     Serial.print(" \t Sensor salida... \t");
     Serial.println(String(senSalida));
     Serial.print(" \t Moneda1 \t");
     Serial.println(String(boolMoneda1));
     Serial.print(" \t Moneda2 \t");
     Serial.println(String(boolMoneda2));
     Serial.print(" \t Moneda3 \t");
     Serial.println(String(boolMoneda3));
     Serial.print(" \t Moneda4 \t");
     Serial.println(String(boolMoneda4));
     Serial.print(" \t boton \t");
     if(btnReset == HIGH)
      Serial.println(String(1));
     else
      Serial.println(String(0));
    
  delay(1000);
   */
  //Verifica la entrada de una moneda
  if (senEntrada == HIGH && senSalida == LOW){
    monedaNueva = HIGH;
    //digitalWrite(btnBocina,LOW);
    Serial.println("Sensando Moneda...");    
    //leerValorMonedas();
  }

  //Verifica que haya salido la moneda
  if (senEntrada == LOW && senSalida == HIGH){

    //Pregunta si tenemos una moneda nueva y determina su valor
    if (monedaNueva == HIGH){
      asignarValorMoneda();
      digitalWrite(btnBocina, LOW);
      delay (5);
      digitalWrite(btnBocina, HIGH);
      monedaNueva = LOW;

      //Cálculo de total de monedas y dinero
      monedasTotales = monCincuenta + monUno + monDos + monCinco + monDiez;
      dineroTotal = (monCincuenta*0.10)+(monUno*0.05)+(monDos*0.25)+(monCinco*1)+(monDiez*0.50);
    
      Serial.print("$0.10:");
      Serial.print(monCincuenta);
      Serial.print("$0.05:");
      Serial.print(monUno);
      Serial.print("$0.25:");
      Serial.print(monDos);
      Serial.print(" $1:");
      Serial.print(monCinco);
      Serial.print("$0.50:");
      Serial.print(monDiez);
      Serial.print("  Total: $");
      Serial.print(dineroTotal);
      Serial.print(" Monedas:");
      Serial.print(monedasTotales);
      Serial.println();        

    //Guardar en numeroNivel y valorProgresBar

    }
  }
 /*
  if(digitalRead(btnReset) == HIGH){
    
    monCincuenta = 0;
    monUno = 0;
    monDos = 0;
    monCinco = 0;
    monDiez = 0;

    
    //EEPROM.write(4, 0);
    //EEPROM.write(3, 0);
    //EEPROM.write(2, 0);
    //EEPROM.write(1, 0);
    //EEPROM.write(0, 0);
    //EEPROM.commit();
    
    //Cálculo de total de monedas y dinero
      monedasTotales = 0;
      dineroTotal = 0;
    
      Serial.print("$0.5:");
      Serial.print(monCincuenta);
      Serial.print(" $1:");
      Serial.print(monUno);
      Serial.print(" $2:");
      Serial.print(monDos);
      Serial.print(" $5:");
      Serial.print(monCinco);
      Serial.print(" $10:");
      Serial.print(monDiez);
      Serial.print(" Total: $");
      Serial.print(dineroTotal);
      Serial.print(" Monedas:");
      Serial.print(monedasTotales);
      Serial.println();    
  	  drawintro();
}
*/ //Esto esta en Ext_INT_reset

  //Revisa que no se haya presionado el boton de RESET
  //"Nivel 1: $2"
  //"Nivel 2: $5" 
  //"Nivel 3: $10"
  //"Nivel 4: $20"
  //"Nivel 5: $50"

  valorProgresBar =128 * (dineroTotal-metaNivel_prev)/(metaNivel_actual-metaNivel_prev);

  if (dineroTotal>=50){
    numeroNivel=6;
    animacionFinal(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT);
  }else if (dineroTotal>=20){
    numeroNivel=5;
    metaNivel_prev=20;
    metaNivel_actual=50;
    drawProgress(); 
  }else if (dineroTotal>=10){
    numeroNivel=4;
    metaNivel_prev=10;
    metaNivel_actual=20;
    drawProgress();
  }else if (dineroTotal>=5){
    numeroNivel=3;
    metaNivel_prev=5;
    metaNivel_actual=10;
    drawProgress();     
  }else if (dineroTotal>=2){
    numeroNivel=2;
    metaNivel_prev=2;
    metaNivel_actual=5;
    drawProgress();
  }else{
    numeroNivel=1;
    metaNivel_prev=0;
    metaNivel_actual=2;
    drawProgress();
  }
  
}

