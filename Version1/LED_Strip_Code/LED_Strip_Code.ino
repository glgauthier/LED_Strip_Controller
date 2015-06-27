#define REDPIN 5
#define GREENPIN 3
#define BLUEPIN 6
int b = 0;
int r = 0;
int g = 0;
int FADESPEED = 25;
int STROBESPEED = 50;

int music = 0;
int mode = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~Setup Loop~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(2, INPUT);
  attachInterrupt(0, changemode, CHANGE); //interrupt for mode change on pin 2 (I.0)
  
  analogWrite(REDPIN, 60);
  analogWrite(GREENPIN, 60);
  analogWrite(BLUEPIN, 60);
  delay(333);  
  analogWrite(REDPIN, 150);
  analogWrite(GREENPIN, 150);
  analogWrite(BLUEPIN, 150);
  delay(333); 
  
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~Interrupt Loop~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void changemode(){

 static unsigned long last_interrupt_time = 0; //used to debounce button press
 unsigned long interrupt_time = millis(); //used to debounce button press
 if (interrupt_time - last_interrupt_time > 200){ //if the button has been pressed..
   if (mode < 12) mode++;
   else mode = 0;
 }
 last_interrupt_time = interrupt_time;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Main Loop ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void loop() { //normal loop

//-----------Mode 0 - White Light -------------------------------//  
  while (mode == 0) {
    if (digitalRead(2) == HIGH) break;
    analogWrite(BLUEPIN, 200);
    analogWrite(REDPIN, 200);
    analogWrite(GREENPIN, 200);
  }

//-----------Mode 1 - Music Reactance----------------------------//  
 while (mode == 1){
  if (digitalRead(2) == HIGH) break;
    analogWrite(BLUEPIN, b);
    analogWrite(REDPIN, r);
    analogWrite(GREENPIN, g);
  
    music = analogRead(0);
    
    if (music>50 & music<200) b = (b + 25);
      else b=100; 
  
    if (music>350 ) g = (255);
      else(g= 0) ;
      
    if (music>150){ 
      r=(r+70);
      b=(b+95);
    }
    else { 
      if (r>0 & b>0){ 
        r=(r-10); 
        b=(b-15);
      }
      else {
      r=0; 
      b=0;
      }
    }
  }

//--------------Mode 2- Music (more reactive)------------------------------------//  
 while (mode == 2){
  if (digitalRead(2) == HIGH) break;
    analogWrite(BLUEPIN, b);
    analogWrite(REDPIN, r);
    analogWrite(GREENPIN, g);
  
    music = analogRead(0);
    
    if (music>15 & music<50) b = (b + 50);
      else b=100; 
  
    if (music>150 ) g = (255);
      else(g= 0) ;
      
    if (music>50){ 
      r=(r+100);
      b=(b+120);
    }
    else { 
      if (r>0 & b>0){ 
        r=(r-10); 
        b=(b-25);
      }
      else {
      r=0; 
      b=0;
      }
    }
  }
 
//-------------------Mode 3 - Red-------------------------------//  
 while (mode == 3){
   if (digitalRead(2) == HIGH) break;
    analogWrite(BLUEPIN, 0);
    analogWrite(REDPIN, 255);
    analogWrite(GREENPIN, 0);
  }

//-------------------Mode 4 - Orange----------------------------//  
  while (mode == 4){
    if (digitalRead(2) == HIGH) break;
    analogWrite(BLUEPIN, 0);
    analogWrite(REDPIN, 255);
    analogWrite(GREENPIN, 128);
  }

//-------------------Mode 5- Yellow-----------------------------//  
   while (mode == 5){
    analogWrite(BLUEPIN, 0);
    analogWrite(REDPIN, 255);
    analogWrite(GREENPIN, 255);
  }

//-------------------Mode 6- Green------------------------------//  
   while (mode == 6){
    if (digitalRead(2) == HIGH) break;
    analogWrite(BLUEPIN, 0);
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN, 255);
  }

//--------------------Mode 7- Cyan------------------------------//  
   while (mode == 7){
    if (digitalRead(2) == HIGH) break;
    analogWrite(BLUEPIN, 255);
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN, 255);
  }

//--------------------Mode 8- Blue------------------------------//  
   while (mode == 8){
    if (digitalRead(2) == HIGH) break;
    analogWrite(BLUEPIN, 255);
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN, 0);
  }

//--------------------Mode 9- Purple-----------------------------//  
   while (mode == 9){
    if (digitalRead(2) == HIGH) break;
    analogWrite(BLUEPIN, 255);
    analogWrite(REDPIN, 128);
    analogWrite(GREENPIN, 0);
  }
  
//--------------------Mode 10- Violet-----------------------------//  
   while (mode == 10){
    if (digitalRead(2) == HIGH) break;
    analogWrite(BLUEPIN, 255);
    analogWrite(REDPIN, 255);
    analogWrite(GREENPIN, 0);
  }

//-------------------Mode 11- Fader-----------------------//  
   while (mode == 11){
    if (digitalRead(2) == HIGH) break;
    int r2, g2, b2;
   
   for (r2 = 0; r2 < 255; r2++) { // fade from blue to violet
      if (digitalRead(2) == HIGH) break;
     analogWrite(REDPIN, r2);
     delay(FADESPEED);
   } 
   for (b2 = 255; b2 > 0; b2--) { // fade from violet to red
      if (digitalRead(2) == HIGH) break;
     analogWrite(BLUEPIN, b2);
     delay(FADESPEED);
   } 
   for (g2 = 0; g2 < 255; g2++) { // fade from red to yellow
       if (digitalRead(2) == HIGH) break;
      analogWrite(GREENPIN, g2);
      delay(FADESPEED);
  } 
  for (r2 = 255; r2 > 0; r2--) { // fade from yellow to green
     if (digitalRead(2) == HIGH) break;
    analogWrite(REDPIN, r2);
    delay(FADESPEED);
  } 
  for (b2 = 0; b2 < 255; b2++) { // fade from green to teal
     if (digitalRead(2) == HIGH) break;
    analogWrite(BLUEPIN, b2);
    delay(FADESPEED);
  } 
  for (g2 = 255; g2 > 0; g2--) { // fade from teal to blue
     if (digitalRead(2) == HIGH) break;
    analogWrite(GREENPIN, g2);
    delay(FADESPEED);
  } 
  }
//-------------------Mode 12- Flasher-----------------------//  
  while (mode == 12){
    if (digitalRead(2) == HIGH) break;
    analogWrite(REDPIN, 255);
    analogWrite(GREENPIN, 0);
    analogWrite(BLUEPIN, 0);
    delay(333);  
    analogWrite(REDPIN, 255);
    analogWrite(GREENPIN, 0);
    analogWrite(BLUEPIN, 255);
    if (digitalRead(2) == HIGH) break;
    delay(333);  
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN, 0);
    analogWrite(BLUEPIN, 255);
    if (digitalRead(2) == HIGH) break;
    delay(333);  
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN, 255);
    analogWrite(BLUEPIN, 255);
    if (digitalRead(2) == HIGH) break;
    delay(333);  
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN, 255);
    analogWrite(BLUEPIN, 0);
    if (digitalRead(2) == HIGH) break;
    delay(333);  
    analogWrite(REDPIN, 255);
    analogWrite(GREENPIN, 255);
    analogWrite(BLUEPIN, 0);
    if (digitalRead(2) == HIGH) break;
    delay(333);  
  }
}

