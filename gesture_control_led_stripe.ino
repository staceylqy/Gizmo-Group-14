//Libraries needed for Sketch
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

//Define the led stript
#define LED_PIN     6
#define NUM_LEDS    29
#define BRIGHTNESS  80
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
int led=0;

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

//BNO055 Sensor
// Set the delay between fresh samples
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055();

//Initialize the value of the word
int a=1;//First occassion
int b=2;//Second occassion
int c=3;//Third occassion
int d=0;//The changed value 
int e=1;//First occassion
int f=2;//Second occassion
int g=3;//Third occassion
int h=0;//The changed value 

//Define the buttons
/*int Button1Value=0; 
int Button2Value=0; 
int Button3Value=0; 
int Button1=4;
int Button2=3;
int Button3=2;*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Define the output pins of buttons
//  pinMode(Button1,INPUT);
//  pinMode(Button2,INPUT);
//  pinMode(Button3,INPUT);
 
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1); 
  }
  delay(1000);
  bno.setExtCrystalUse(true);
}

void loop(void) {
  // put your main code here, to run repeatedly:
  //Get Acceleration vector data from the Sensor
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  /* Display the floating point data */
//  Serial.print("X: ");
//  Serial.print(euler.x());
//  Serial.print(" Y: ");
//  Serial.print(euler.y());
//  Serial.print(" Z: ");
//  Serial.print(euler.z());
//  Serial.print("\n");
  //Conditional statements to check with sensor is falling or rising
  //faster than set points (gravity is 9.8ms^2)
  if (euler.y() > 3 )
  {
    /*
    SetupBlackAndWhiteStripedPalette();    
      //currentPalette = myRedWhiteBluePalette_p; 
    currentBlending = NOBLEND;
      
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */    
    //FillLEDsFromPaletteColors( startIndex);
    for(led=0;led<NUM_LEDS;led++){
      leds[led] = CRGB(237, 49, 98);
    }
    led=0;
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    //To show the word
    if(d!=a){
      Serial.print("A:Hi!");
      Serial.print("\n");
      delay(2000);
      Serial.print("\t\t\tB:Hello!");
      Serial.print("\n");
      d=a;
    }
  }else if(euler.y()<=3 && euler.y()>=-3){
    /*currentPalette = RainbowStripeColors_p;  
    currentBlending = NOBLEND;

    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
  
    //FillLEDsFromPaletteColors( startIndex);
     for(led=0;led<NUM_LEDS;led++){
      leds[led] = CRGB(236, 214, 28);
    }
    led=0;
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    //To show the word
    if(d!=b){
      Serial.print("A:How's it going?");
      Serial.print("\n");
      delay(2000);
      Serial.print("\t\t\tB:Not bad.");
      Serial.print("\n");
      d=b;
    }
  }else if(euler.y()<-3){
    /*currentPalette = CloudColors_p;       
    //SetupTotallyRandomPalette();                
    currentBlending = NOBLEND;
    //Serial.println("Button3 is HIGH");
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
  
    //FillLEDsFromPaletteColors( startIndex);
     for(led=0;led<NUM_LEDS;led++){
      leds[led] = CRGB(24, 83, 192);
    }
    led=0;
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    //To show the word
    if(d!=c){
      Serial.print("A:Thanks for visiting me!");
      Serial.print("\n");
      delay(2000);
       Serial.print("\t\t\tB:Take care, my friend!");
      Serial.print("\n");
      d=c;
    }
  }
  //Give response controlled by buttons
  /* Button1Value=digitalRead(Button1);
   if(Button1Value==HIGH){
      if(h!=e){
       Serial.print("\t\t\tB:Hey!");
       Serial.print("\n");
       h=e;
      }
      Button1Value=0;
   }
   Button2Value=digitalRead(Button2);
   if(Button2Value==HIGH){
    if(h!=f){
       Serial.print("\t\t\tB:I feel excited!");
       Serial.print("\n");
       h=f;
     }
     Button2Value=0;
   }
   Button3Value=digitalRead(Button3);
   if(Button3Value==HIGH){
    if(h!=g){
       Serial.print("\t\t\tB:You are welcome!");
       Serial.print("\n");
       h=g;
    }
    Button3Value=0;
   }*/
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = 255;
    
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};

  

