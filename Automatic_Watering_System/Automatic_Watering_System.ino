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

//Screensaver Timer
unsigned long screenSaverTime = 0;

void touchscreenLoop() {
  //Find the current point where the touchscreen is being touched
  TSPoint p = ts.getPoint();
  
  //Detect if the screen is being touched currently
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    
    // scale from 0->1023 to tft.width
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    /* Touchscreen Debugging Code
    Serial.print("x=");
    Serial.print(p.x);
    Serial.print("       y=");
    Serial.println(p.y);
    */

    //Reset Screensaver Timeout
    screenSaverTime = 0;
  }
}

  


//-------------------------------------------------------------------------------//
//Beginning Editable Code


//---Initialize Variables---//
//Timing Loops
unsigned long prevHundredthSecondMillis = 0;
unsigned long prevTenthSecondMillis = 0;
unsigned long prevSecondMillis = 0;
unsigned long prevFiveSecondMillis = 0;
unsigned long prevTenSecondMillis = 0;
unsigned long prevMinuteMillis = 0;
unsigned long prevTenMinuteMillis = 0;



//---Setup function---//
void setup(void) {
  nonEditableSetup();
  editableSetup();  
  testPage();
}

//---Loop function---//
void loop() {
  

  //Scheduling Loops
  unsigned long M = millis();

  //Hundredth Second Loop (Fastest)
  if (M - prevHundredthSecondMillis >= 10) {
    touchscreenLoop();
    //screenSaver();
    prevHundredthSecondMillis = M;
  }
  //Tenth Second Loop
  if (M - prevTenthSecondMillis >= 100) {

    prevTenthSecondMillis = M;
  }
  //One Second Loop
  if (M - prevSecondMillis >= 1000) {

    prevSecondMillis = M;
  }
  //Five Second Loop
  if (M - prevFiveSecondMillis >= 5000) {

    prevFiveSecondMillis = M;
  }
  //Ten Second Loop
  if (M - prevTenSecondMillis >= 10000) {

    prevTenSecondMillis = M;
  }
  //Minute Loop
  if (M - prevMinuteMillis >= 60000) {

    prevMinuteMillis = M;
  }
  //Ten Minute Loop (Slowest)
  if (M - prevTenMinuteMillis >= 600000) {

    prevTenMinuteMillis = M;
  }
  
}


void editableSetup() {
  tft.setRotation(1);
}


void coordinates() {
  tft.fillScreen(BLACK);
  int tempx = 20;
  int tempy = 20;
  while(tempx <= tft.width()) {
    if(tempx % 100 == 0) {
      tft.drawFastVLine(tempx, 0, 20, GREEN);
    }
    else {
      tft.drawFastVLine(tempx, 0, 10, GREEN);
    }
    tempx += 20; 
  }
  while(tempy <= tft.height()) {
    if(tempy % 100 == 0) {
      tft.drawFastHLine(0, tempy, 20, GREEN);
    }
    else {
      tft.drawFastHLine(0, tempy, 10, GREEN);
    }
    tempy += 20;
  }
  tft.fillRect(tft.width()-10,0,10,10,GREEN);
  tft.fillRect(0, tft.height()-10,10,10,RED);

  
}

void testPage() {
  //coordinates();
  
  changeSensors();
  //tft.drawFastVLine(240,0,tft.height(),GREEN);
  //tft.drawFastHLine(0,160,tft.width(),GREEN);
}

void readFromEEPROM() {
  //Read all values from the machine
}

void screenSaver() {
  if (screenSaverTime > 6000) {
    //Turn Backlight Off 
  }
}

void homePage() {
  tft.fillRect(40,40,400,100,GREEN);
  tft.drawRect(40,40,400,100,WHITE);
  tft.fillRect(40,180,260,100,RED);
  tft.drawRect(40,180,260,100,WHITE);
  tft.fillRect(340,180,100,100,BLUE);
  tft.drawRect(340,180,100,100,WHITE);

  tft.setCursor(52,80);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.print("View Current Readings");

  tft.setCursor(95,220);
  tft.print("Settings");

  tft.drawChar(370,202,'i',BLACK,BLUE,8);
}

void backArrow() {
  tft.fillRect(10,10,40,40,RED);
  tft.fillTriangle(15,30,25,20,25,40,BLACK);
  tft.fillRect(25,25,20,10,BLACK);

  tft.drawRect(10,10,40,40,WHITE);
  tft.drawTriangle(15,30,25,20,25,40,WHITE);
  tft.drawRect(25,25,20,10,WHITE);
  tft.drawFastVLine(25,26,8,BLACK);
}

void currentReadings() {
  backArrow();
  
  tft.fillRect(60,60,360,200,MAGENTA);
  tft.drawRect(60,60,360,200,WHITE);
  tft.drawFastHLine(60,110,360,WHITE);
  tft.drawFastHLine(60,160,360,WHITE);
  tft.drawFastHLine(60,210,360,WHITE);
  tft.drawFastVLine(370,60,200,WHITE);

  tft.fillRect(371,61,48,49,RED);
  tft.fillRect(371,111,48,49,GREEN);
  tft.fillRect(371,161,48,49,BLUE);
  tft.fillRect(371,211,48,48,YELLOW);

  tft.setCursor(310,75);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.print(254);
  tft.setCursor(310,125);
  tft.print(118);
  tft.setCursor(310,175);
  tft.print(148);
  tft.setCursor(310,225);
  tft.print(100);

  for (int i = 0; i < 4; i++) {
  int j = 0;
  j = 50*i+75;
  tft.setCursor(70,j);
  tft.print(1+i);
  tft.setCursor(100,j);
  tft.print("Water Level");
  }
}

void changeSensors() {
  backArrow();

  tft.setCursor(170,10);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Sensor 2");

  tft.fillRect(10,260,50,50,BLUE);
  tft.drawRect(10,260,50,50,WHITE);
  tft.setCursor(27,275);
  tft.print(1);

  tft.fillRect(420,260,50,50,BLUE);
  tft.drawRect(420,260,50,50,WHITE);
  tft.setCursor(437,275);
  tft.print(3);

  tft.fillRect(100,260,280,50,RED);
  tft.drawRect(100,260,280,50,WHITE);
  tft.setCursor(205,275);
  tft.print("Save");

  tft.drawRect(160,135,160,50,WHITE);
  tft.setCursor(215,150);
  tft.print(100);

  tft.fillRect(90,135,50,50,WHITE);
  tft.fillRect(100,159,30,3,BLACK);
  tft.fillRect(340,135,50,50,WHITE);
  tft.fillRect(350,159,30,3,BLACK);
  tft.fillRect(364,145,3,30,BLACK);
}


