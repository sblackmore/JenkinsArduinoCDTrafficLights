int serialData;
int yellowLight = 10;
int greenLight = 9;
int redLight = 11;
int incomingByte = 0;
int lastTx = 0;

int speakerPin = 3;
int length = 15;
char notes[] = "ccggaagffeeddc ";
int beats[] = {1,1,1,1,1,1,2,1,1,1,1,1,1,2,4};
int tempo = 300;

void playTone(int tone, int duration){
  for(long i = 0; i < duration*1000L; i+= tone*2) {
   digitalWrite(speakerPin, HIGH);
   delayMicroseconds(tone);
   digitalWrite(speakerPin, LOW);
   delayMicroseconds(tone);
  } 
}

void playNote(char note, int duration) {
   char names[] = {'c','d','e','f','g','a','b','c'};
   int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
   
   for(int i = 0; i <8; i++){
     if(names[i] == note)
       playTone(tones[i], duration);
   }
}


void setup() {
  Serial.begin(9600);
  Serial.println("Hello");
  pinMode(yellowLight,OUTPUT);
  pinMode(greenLight, OUTPUT);
  pinMode(redLight, OUTPUT);
  
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  Serial.println(incomingByte, DEC);
  if(Serial.available() > 0) {
    incomingByte = Serial.read();
    
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
    
    switch(incomingByte) {
     case 48: 
       digitalWrite(yellowLight,HIGH);
       break;
     case 49:
       digitalWrite(greenLight,HIGH);
       break;
     case 50:
       digitalWrite(redLight,HIGH);
        for(int i = 0; i < length; i++) {
          if(notes[i] == ' '){
            delay(beats[i] * tempo);
          } 
          else
          {
           playNote(notes[i],beats[i]*tempo); 
          }
          delay(tempo/2);
       }
       break;
    }
  }    
}
