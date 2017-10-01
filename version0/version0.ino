#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
void rainbowCycleNew(uint8_t wait, uint8_t loc);
int checkRange (int dir, uint16_t loc, int but);
int winner(int pts1, int pts2);
#define TRUE 1
#define FALSE 0

#define PIN 6
//#define PIN 2
//#define PIN 3
const int buttonPin1 = 2;     	// the number of the pushbutton1 pin
const int buttonPin2 = 9; 		// the number of the pushbutton2 pin
const int ledPin =  6;      	// the number of the LED pin

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton1 status
int buttonState2 = 0;         // variable for reading the pushbutton2 status
int swap;						// variable for adjusting the direction of lights loop
int button1Loc=7;
int button2Loc=52;
int direct=1;
float faster=100;
int lightRangeForward=0;
int lightRangeBack=0;
uint16_t lightLocation=0;
int score1=0;
int score2=0;
int finalScore=0;
int level=2;
int score1sum= 0;
int score2sum= 0; 
int pixelCount = 59;
				 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(75, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

Serial.begin(9600);
//Serial.println("SMACKDOWN CHALLENGE");
//Serial.println("Level 1: First player to 5 points WINS!"); 
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  Serial.println(String(score1)+ " " + String(score2) + " " + String(level)); 
 } 
  void loop() 
	{

	  while(lightLocation <= pixelCount && lightLocation >= 0)
          {
                //lightLocation=55;               
                rainbowCycleNew(faster, lightLocation);
                buttonState1 = digitalRead(buttonPin1);
                buttonState2 = digitalRead(buttonPin2);
                
	      if (buttonState1 == LOW && checkRange(direct, lightLocation, button1Loc)== TRUE) 
		{
                   delay(1000);
  		   direct = direct*-1;
                   faster = faster*.95;
                   //Serial.println(faster);
                   if(button1Loc == lightLocation)
                    {
                       score1 = score1 +1;
                      //Serial.print("Hulk Hogan score = ");
                      Serial.println(String(score1)+ " " + String(score2) + " " + String(level)); 
                    }
                    else
                    {
                      score1 = score1 -1;
                      if (score1 < 0)
                       {score1 = 0;}
                      //Serial.print("Hulk Hogan score = ");
                      Serial.println(String(score1)+ " " + String(score2) + " " + String(level)); 
                    }  
                 }
                            
	      if (buttonState2 == LOW && checkRange(direct, lightLocation, button2Loc)==TRUE)
                {
                  delay(1000);
                  direct = direct*-1;
                  faster = faster*.95;
                  //Serial.println(faster);
                  if (button2Loc == lightLocation)
                  {
                    
                    score2 = score2 +1;
                   //Serial.print("The Rock score = ");
                      Serial.println(String(score1)+ " " + String(score2) + " " + String(level)); 
                  }
                  else
                  {
                    score2 = score2 -1;
                    if (score2 < 0)
                     {score2 = 0;}
                      Serial.println(String(score1)+ " " + String(score2) + " " + String(level)); 
                     
                  } 
                }
                if (finalScore= winner(score1, score2, level) > 0)
                {
                  
                  //Serial.println("We have a WINNER!"); 
                  if (score1> score2)
                  {
                    //Serial.println("HULK HOGAN WINS THIS ROUND!");
                    colorWipe(strip.Color(  0,   0, 255), 30); // Blue
                    score1sum = score1sum + 1; 
                  }
                   if (score2> score1)
                  {
                    //Serial.println("THE ROCK WINS THIS ROUND!");
                     colorWipe(strip.Color( 0, 255, 0), 30); // Green
                    score2sum = score2sum + 1;
                  }
                  theaterChase(strip.Color(127, 127, 127), 10); // White
                  rainbowCycle(.05);
                  theaterChaseRainbow(1); 
                  score1=0; 
                  score2=0;
                  level = level - 1; 
                  if (level==3)
                  {
                    //Serial.println("ENTERING LEVEL 2: First Player to 4 WINS!");
                  }
                   if (level==2)
                  {
                    //Serial.println("ENTERING LEVEL 3: First Player to 3 WINS!");
                  }
                   if (level==1)
                  {
                    //Serial.println("ENTERING LEVEL 3: First Player to 2 WINS!");
                  }
                   if (level < 0) 
                  {
                    level = 0;
                  }
                  if (level==0)
                  {
                    //Serial.println("ENTERING THE ULTIMATE CHAMPIONSHIP!!: First Player to 1 WINS!");
                      if (score1> score2 && score1sum > score2sum)
                      {
                        //Serial.println("We have a CHAMPION!");
                        //Serial.println("HULK HOGAN WINS THE GAME!");
                        //Serial.println("Open new Serial Monitor to start a NEW GAME");
                      }
                       if (score2> score1 && score2sum > score1sum)
                      {
                        //Serial.println("We have a CHAMPION!");
                        //Serial.println("THE ROCK WINS THE GAME!");
                        //Serial.println("Open new Serial Monitor to start a NEW GAME");
                        
                      }
                  }
                  
                }
		
             lightLocation = lightLocation + (1*direct);
              if (faster < 5)
              { 
                //Serial.println("TIME IS UP. GAME OVER!!");
                //Serial.println("Open new Serial Monitor to start over");
                colorWipe(strip.Color(255, 0, 0), 50); // Red
                break; 
              }
                
    	    
           }
           if (direct==-1)
           {
           lightLocation = pixelCount;
           lightRangeBack = 0;
           }
           else
           {
            lightLocation = 0;
            lightRangeBack = 0; 
           }
           
}
	
//FUNCTIONS

int checkRange (int dir, uint16_t loc, int but)
{ int condition;
  if (dir ==1)
  {
     if (but >= loc-2 && but <= loc+2)
     {
       condition = TRUE;
     }
     else
     {
       condition = FALSE; 
     }
  }
  if (dir ==-1)
  {
    if (but <= loc+2 && but >= loc-2)
    {
      condition = TRUE;
    }
    else
    {
      condition = FALSE;
    }
  }
return condition; 
}

void rainbowCycleNew(uint8_t wait, uint16_t loc) {
  uint16_t i, j;

  //for(j=0; j<76; j++) { // 5 cycles of all colors on wheel
    
    for(i=0; i< 75; i++) {
     strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
   }
    strip.setPixelColor(loc % strip.numPixels() , strip.Color(255 , 255, 255));
    strip.show();
    delay(wait);  
    
  //}
 // strip.setPixelColor(loc, strip.Color(127, 127, 127));
 }


 
 uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
} 
	
int winner(int pts1, int pts2, int lvl)
{
  if (pts1> lvl)
  {
  return pts1;
  }
  if (pts2> lvl)
  {
  return pts2;
  }
  else
  {
  return 0;
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
