#include <ChainableLED.h>
#include <Wire.h>
#include <ADXL345.h>
#define NUM_LEDS  6
ADXL345 adxl; //variable adxl is an instance of the ADXL345 library
const int buzzerPin =  4;      // the number of the buzzer pin
ChainableLED leds(7, 8, NUM_LEDS);
int anArray[] = {0,1,2,3,4,5};
int elements = sizeof(anArray) / sizeof(int);
int accelerometer0[] = {0,0,235};
int accelerometer1[] = {0,-245,0};
int accelerometer2[] = {0,255,0};
int accelerometer3[] = {255,0,0};
int accelerometer4[] = {-255,0,0};
int accelerometer5[] = {0,0,-255};
int tolerantzia = 20;
int rand_range(int n)
{
    int r, ul;
    ul = RAND_MAX - RAND_MAX % n;
    while ((r = random(RAND_MAX+1)) >= ul);
    //r = random(ul);
    return r % n;
}


void shuffle_swap(int index_a, int index_b, int *array, int size)
{
    char *x, *y, tmp[size];

    if (index_a == index_b) return;

    x = (char*)array + index_a * size;
    y = (char*)array + index_b * size;

    memcpy(tmp, x, size);
    memcpy(x, y, size);
    memcpy(y, tmp, size);
}


// shuffle an array using fisher-yates method, O(n)
void shuffle(int *array, int nmemb, int size)
{
    int r;
    
    while (nmemb > 1) {                                                                      
        r = rand_range(nmemb--);                                                              
        shuffle_swap(nmemb, r, array, size);
    }
}


void setup()
{
  Serial.begin(9600); //Accelerometer
  adxl.powerOn();

  //set activity/ inactivity thresholds (0-255)
  adxl.setActivityThreshold(75); //62.5mg per increment
  adxl.setInactivityThreshold(75); //62.5mg per increment
  adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?
 
  //look of activity movement on this axes - 1 == on; 0 == off 
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);
 
  //look of inactivity movement on this axes - 1 == on; 0 == off
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);
 
  //look of tap movement on this axes - 1 == on; 0 == off
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(1);
 
  //set values for what is a tap, and what is a double tap (0-255)
  adxl.setTapThreshold(50); //62.5mg per increment
  adxl.setTapDuration(15); //625us per increment
  adxl.setDoubleTapLatency(80); //1.25ms per increment
  adxl.setDoubleTapWindow(200); //1.25ms per increment
 
  //set values for what is considered freefall (0-255)
  adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment
 
  //setting all interrupts to take place on int pin 1
  //I had issues with int pin 2, was unable to reset it
  adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN );
 
  //register interrupt actions - 1 == on; 0 == off  
  adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT,  1);
  adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,   1);
  adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1);
  // 
//  Serial.begin (9600); //bariableak ikusi
  pinMode(buzzerPin, OUTPUT); 
  for (int i=0; i <= 10; i++){
  delay(10);
  int noise = analogRead(2);
  randomSeed(noise);
  // Fisher-yates
  shuffle(anArray, elements, sizeof(int));
    
  leds.setColorRGB(anArray[0],0,0,255);
  leds.setColorRGB(anArray[1],0,255,0);
  leds.setColorRGB(anArray[2],255,0,0);//gorria
  leds.setColorRGB(anArray[3],255,255,0);
  leds.setColorRGB(anArray[4],255,13,134);
  leds.setColorRGB(anArray[5],255,255,255);

   } 
   
    digitalWrite(buzzerPin, HIGH);  
    delay(1000);
    digitalWrite(buzzerPin, LOW); 
    delay(3000);
}

void loop()
{
	int x,y,z,xgorri,ygorri,zgorri;  
	adxl.readXYZ(&x, &y, &z); //read the accelerometer values and store them in variables  x,y,z
        Serial.print(anArray[0]);
        Serial.print(anArray[1]);
        Serial.print(anArray[2]);
        Serial.print(anArray[3]);
        Serial.print(anArray[4]);
        Serial.println(anArray[5]);
        
switch (anArray[2]) {
  case 3:
      xgorri = 0;
      ygorri = 0;
      zgorri = 235;
      break;
    case 2:
      xgorri = 0;
      ygorri = -245;
      zgorri = 0;
      break;
    case 1:
      xgorri = 0;
      ygorri = 255;
      zgorri = 0;
      break;
    case 4:
      xgorri = 255;
      ygorri = 0;
      zgorri = 0;
      break;
    case 5:
      xgorri = -255;
      ygorri = 0;
      zgorri = 0;
      break;    
    case 0:
      xgorri = 0;
      ygorri = 0;   
      zgorri = -255;
      break;
  }
if ( x > (xgorri-tolerantzia) && x < (xgorri+tolerantzia) && y > (ygorri-tolerantzia) && y < (ygorri+tolerantzia) && z > (zgorri-tolerantzia) && z < (zgorri+tolerantzia)){
      digitalWrite(buzzerPin, HIGH);  
      delay(1000);
      digitalWrite(buzzerPin, LOW); 
  for (int i=0; i <= 10; i++){
  delay(10);
  int noise = analogRead(2);
  randomSeed(noise);
  // Fisher-yates
  shuffle(anArray, elements, sizeof(int)); 
  leds.setColorRGB(anArray[0],0,0,255);
  leds.setColorRGB(anArray[1],0,255,0);
  leds.setColorRGB(anArray[2],255,0,0);//gorria
  leds.setColorRGB(anArray[3],255,255,0);
  leds.setColorRGB(anArray[4],255,13,134);
  leds.setColorRGB(anArray[5],255,255,255);
}
}
}

