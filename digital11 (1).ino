int led_red = 6; // the red LED is connected to Pin 0 of the Arduino
int led_yellow = 7; // the yellow LED is connected to Pin 1 of the Arduino
int led_green = 2; // the green LED is connected to Pin 2 of the Arduino
int led_redp = 3;
int led_greenp = 4;
int puls = 5;
void setup() {
  // set up all the LEDs as OUTPUT
  pinMode(led_red, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_redp, OUTPUT);
  pinMode(led_greenp, OUTPUT);
  pinMode(puls, INPUT);
  Serial.begin(9600);
}

void loop()
{
  blink(); 
}
void blink(void){
 const uint32_t semver = 5500;// This is the first constant time that it waits to start to change the green light
 static uint8_t ESTADO = 0;// This is teh state that is gonna be in
 static uint32_t RELOJ0 = 0; 
 static uint32_t c=0;// This is a logical value to see if it entered turned off the vehicular green led
 static uint32_t k=0;//This is the number of pulses it cpounts
 static uint32_t y=0;//This is a logical value to see if it entered a case
 static uint32_t d=0;//This is a logical value to see if it entered a case
 static uint32_t t=0;
 static uint32_t RELOJ1=0;//This is a logical value to see if it entered a case
 switch(ESTADO)
 {
  case 0:// This is how the conditions of the leds start
   digitalWrite(led_green, HIGH);
   digitalWrite(led_red, LOW);
   digitalWrite(led_yellow, LOW);
   digitalWrite(led_redp, HIGH);
   digitalWrite(led_greenp, LOW);
   RELOJ0 = millis();
   c=0;// these are values that need to reinitiate each loop
   k=0;
   y=0;
   d=0;
   t=0;
   ESTADO = 1;
   
   break;

  case 1:// this is how the green vehicular led changes
    if(((millis() - RELOJ0 >= semver) && (c==0)) || ((residuo(float(millis() - RELOJ0),0.5)==0.0)&&(c>=1)&&(c<11))||(k>=5)){//this are the conditions to end the green automobile light
     digitalWrite(led_green, !digitalRead(led_green));//Semver should be 84.5sec
     c=c+1;
     esperar(500);
     //Serial.println((float(millis() - RELOJ0),0.5));
    }
    if (c>=11){
     ESTADO=2;}
    if(digitalRead(puls)==HIGH){// this reads the pulses that the person presses
     k=k+1;
     esperar(100);}
    break;
  case 2:
   if((millis() - RELOJ0 >= 11000)&&(y==0) || ((c>=11)&&(y==0))){// the constant in here should be 90sec whic is when the yellow lights up
     digitalWrite(led_yellow, !digitalRead(led_yellow));
     //Serial.println(2);
     y=y+1;
     RELOJ1=millis();
     }
   if((millis() - RELOJ0 -RELOJ1>= 1000) && (y==1)){//The constant in here is when the yellow light shuts down which should be 95sec
    digitalWrite(led_yellow, !digitalRead(led_yellow));
     //Serial.println(float(millis()));
    ESTADO=3;
   }
   break;
    case 3:
   if (((millis()-RELOJ0 >= 10500)&& d==0 )||((y==1)&& (d<1))){// this constant is when the red led lights up which should be 95sec
     digitalWrite(led_red, !digitalRead(led_red));
     //Serial.println(d);
     d=d+1;
     ESTADO=4;
   }
   if(((millis()-RELOJ0 >= 16000)&&(d==1))||(t>=10)){// this constant is when the red led shuts down which should be 115sec
     esperar(500);//This is teh time that it has to wait for the vehicular light to go green
     ESTADO=0;// This goes back to the start of the loop
     Serial.println(t);
   }
   break;
   case 4:
   if((millis()-RELOJ0 >= 12000) && (t==0)||((d==1)&&(t==0))){// this is the constant when the person light changes which should be 97sec
     digitalWrite(led_redp, !digitalRead(led_redp));
     digitalWrite(led_greenp, !digitalRead(led_greenp));
     esperar(1000);//This is the time that is comnstant green the persons light
     //Serial.println(t);
     t=t+1;
   }
   if ((t>0)&&(t<=11)){
     digitalWrite(led_greenp, !digitalRead(led_greenp));
     t=t+1; 
     Serial.println(t);
     esperar(500);
   }
   if (t>=10){
    digitalWrite(led_redp, !digitalRead(led_redp));
    digitalWrite(led_greenp, !digitalRead(led_greenp));
     if((digitalRead(led_greenp)==HIGH) && (digitalRead(led_redp)==HIGH)){
       digitalWrite(led_greenp, !digitalRead(led_greenp));}
    Serial.println(t);
    ESTADO=3;//This is when the led has already titilated 5 times
   }
   break;
 }
}
float residuo(float i, float j){
  float residue;
  residue= float(i/j)-float(int(i/j));
  return residue;
}
void esperar(int g){
  unsigned long reloj2 = millis();
  while(millis()-reloj2<g){ 
    if (millis()-reloj2>g){
      break;
    }
}
}