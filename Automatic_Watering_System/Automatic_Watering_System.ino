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

    /* Touchscreen Debugging Code
    Serial.print("x=");
    Serial.print(p.x);
    Serial.print("       y=");
    Serial.println(p.y);
    */
    
  }
}

  


//-------------------------------------------------------------------------------//
//Beginning Editable Code

//Pinouts
  const int sensorPowerOne = 7;
  const int sensorPowerTwo = 8;
  const int sensorPowerThree = 9;
  const int sensorPowerFour = 10;
  const int sensorPowerFive = 11;

  const int sensorPinOne = A6;
  const int sensorPinTwo = A7;
  const int sensorPinThree = A8;
  const int sensorPinFour = A9;
  const int sensorPinFive = A10;

  const int valvePinOne = 2;
  const int valvePinTwo = 3;
  const int valvePinThree = 4;
  const int valvePinFour = 5;
  const int valvePinFive = 6;

//---Initialize Variables---//
//Timing Loops
unsigned long prevTenthSecondMillis = 0;
unsigned long prevSecondMillis = 0;
unsigned long prevFiveSecondMillis = 0;
unsigned long prevTenSecondMillis = 0;
unsigned long prevMinuteMillis = 0;
unsigned long prevTenMinuteMillis = 0;

//Moisture State Machine
int moistureState = 0;

//Setup function
void setup(void) {
  nonEditableSetup();
  //editableSetup();  
  testPage();
}

//Begin looping of the program
void loop() {
  touchscreenLoop();

  //Scheduling Loops
  unsigned long M = millis();

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
  //Ten Minute Loop
  if (M - prevTenMinuteMillis >= 600000) {

    prevTenMinuteMillis = M;
  }
  
}

/*
void editableSetup() {
  //Initialize Sensors
  

  pinMode(sensorPinOne, INPUT);
  pinMode(sensorPinTwo, INPUT);
  pinMode(sensorPinThree, INPUT);
  pinMode(sensorPinFour, INPUT);
  pinMode(sensorPinFive, INPUT);



  pinMode(sensorPowerOne, OUTPUT);
  pinMode(sensorPowerTwo, OUTPUT);
  pinMode(sensorPowerThree, OUTPUT);
  pinMode(sensorPowerFour, OUTPUT);
  pinMode(sensorPowerFive, OUTPUT);

  //Initialize Valves
  

  pinMode(valvePinOne, OUTPUT);
  pinMode(valvePinTwo, OUTPUT);
  pinMode(valvePinThree, OUTPUT);
  pinMode(valvePinFour, OUTPUT);
  pinMode(valvePinFive, OUTPUT);
}
*/

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
  coordinates();
  
}

void checkMoisture() {
  moistureState = 1;
}

void moistureStateMachine() {
  switch (moistureState) {
    case 0:
      //Wait to start the machine
      break;
    case 1:
      //Power on the sensors
      moistureState++;
      break;
    case 2:
      //Read the moisture
      moistureState++;
      break;
    case 3:
      //Turn off the Sensors
      moistureState++;
      break;
    default:
      moistureState = 0;
      break;
  }
    
  
}


