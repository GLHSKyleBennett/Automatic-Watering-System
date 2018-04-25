//----------------------------------------------------------------------------//
//DO NOT EDIT

//Include Libraries
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

//Defining Pins
#define YP A5  // must be an analog pin, use "An" notation!
#define XM A4  // must be an analog pin, use "An" notation!
#define YM 11   // can be a digital pin
#define XP 10   // can be a digital pin

//Defining resistance levels for the touchscreen position
#define TS_MINX 150
#define TS_MINY 80
#define TS_MAXX 900
#define TS_MAXY 900

//Define pressure min and max
#define MINPRESSURE 10
#define MAXPRESSURE 1000

//Initialize touchscreen
TouchScreen ts = TouchScreen(YM, XM, YP, XP, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//Initialize LCD
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, A4);

void nonEditableSetup() {
  //Begin serial communication for debugging
  Serial.begin(9600);

  //Reset and begin communication with the LCD
  tft.reset();
  tft.begin(0x8357);

  //Clears screen
  tft.fillScreen(BLACK);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
}

void touchscreenLoop() {
  //Find the current point where the touchscreen is being touched
  TSPoint p = ts.getPoint();
  
  //Detect if the screen is being touched currently
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    
    // scale from 0->1023 to tft.width
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

  }
}



//-------------------------------------------------------------------------------//
//Beginning Editable Code


//Setup function
void setup(void) {
  nonEditableSetup();  
}

//Begin looping of the program
void loop() {
  touchscreenLoop();
}







