

#include <NewPing.h>

#define TRIGGER_PIN  46  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     48  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

int led1 = 8;
int led2 = 9;
int led3 = 10;
int led4 = 11;
int led5 = 12;
int count = 0;


int lastping = 0;

int p[1][5] = {led1, led2,led3, led4 ,led5}; 

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


int distance = 100;

void sinLoop()
{
  double pi=3.14159;
for (double i = 0; i-4*pi/15 <= pi; i += pi/30)
{


    analogWrite(8,  sin(i) > 0 ?   255*(sin(i))*(sin(i)) : 0);
  analogWrite(9,  sin(i-pi/15)> 0 ?  255*(sin(i-pi/15))*(sin(i-pi/15)) : 0);
  analogWrite(10, sin(i-2*pi/15)> 0 ?  255*(sin(i-2*pi/15))*(sin(i-2*pi/15)): 0);
  analogWrite(11, sin(i-3*pi/15)> 0 ?  255*(sin(i-3*pi/15))*(sin(i-3*pi/15)): 0);
  analogWrite(12, sin(i-4*pi/15)> 0 ?  255*(sin(i-4*pi/15))*(sin(i-4*pi/15)): 0);
  
  Serial.print(i);Serial.print("\t");
  Serial.println(255*sin(i-4*pi/15));
  delay(100);
}
  analogWrite(8,0);
  analogWrite(9,0);
  analogWrite(10,0);
  analogWrite(11,0);
  analogWrite(12,0);
  count = 0;
}

double last = 140;

void sinLoopWithBreak()
{
  int x = sonar.ping_cm();
  Serial.println("In Sine Loop");
  delay(100);
  double pi=3.14159;
  while(true){
for (double i = 0; i-4*pi/15 <= pi; i += pi/30)
{
  double d = sonar.ping_cm();
Serial.println(d);
  analogWrite(8,  sin(i) > 0 ?   255*(sin(i))*(sin(i)) : 0);
  analogWrite(9,  sin(i-pi/15)> 0 ?  255*(sin(i-pi/15))*(sin(i-pi/15)) : 0);
  analogWrite(10, sin(i-2*pi/15)> 0 ?  255*(sin(i-2*pi/15))*(sin(i-2*pi/15)): 0);
  analogWrite(11, sin(i-3*pi/15)> 0 ?  255*(sin(i-3*pi/15))*(sin(i-3*pi/15)): 0);
  analogWrite(12, sin(i-4*pi/15)> 0 ?  255*(sin(i-4*pi/15))*(sin(i-4*pi/15)): 0);
  

  
  if (d != x & d < 104 & d != 0){
    Serial.println("");Serial.println(d);

    return;
    }
    if (d != 0)
     x = d;
  delay(100);
}
  analogWrite(8,0);
  analogWrite(9,0);
  analogWrite(10,0);
  analogWrite(11,0);
  analogWrite(12,0);
  count = 0;
  }
}


void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.

sinLoop();
delay(100);
sinLoop();


}

void loop() {
  
  int ping1 = sonar.ping_cm();
if (ping1 == 0 )ping1 = 104;
distance = ping1;

if (distance > 104)distance = 104;
  
  {
    float point = 7.8 + ((float)distance)/20;
    double lower = fmod(point,1);


      for (int integer : p[0])
        {    
      if (integer == floor(point))
      {
      analogWrite(integer,255*(1-lower));
      }
      else if (integer == floor(point) +1)
      {
      analogWrite(integer,255*(lower));
      }
      else
        {
          analogWrite(integer,0);
        }
      }
    }
    
    if (lastping == ping1 | (lastping > 103 & ping1 > 103))count = count + 1;
    else count = 0;
    Serial.print(count);Serial.print("\t");Serial.println(ping1);
    if (count > 50)
    {
      sinLoopWithBreak();
      count = 0;
    }
    lastping = ping1;
    delay(100);
}

void loop1() {
  delay(100); 
  int ping1 = sonar.ping();
if (ping1 == 0 )ping1 = 104*50;
distance = ping1;
 Serial.print(ping1);Serial.print("\t");
if (distance > 104*50)distance = 104*50;
  
  {
    
    float point = 7.8 + ((float)distance)/20;
    double lower = fmod(point,1);
    Serial.print(floor(point));Serial.print("\t");
    Serial.print(lower);
    Serial.println("");

      for (int integer : p[0])
        {    
      if (integer == floor(point))
      {
      analogWrite(integer,255*(1-lower));
  //   Serial.print(integer);Serial.print("\t");Serial.print(255*(1-lower));Serial.println("");
      }
      else if (integer == floor(point) +1)
      {
      analogWrite(integer,255*(lower));
  //    Serial.print(integer);Serial.print("\t");Serial.print(255*(lower));Serial.println("");
      }
      else
        {
          analogWrite(integer,0);
 //     Serial.print(integer);Serial.print("\t");Serial.print(0);Serial.println("");
        }
      }
    }
}

