#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);
int b1Input = 8; // Waveform Switching Button
int b2Input = 11; // Frequency Scale Switching Button
int freqState = 1; // Variable to Check State of the Scale
int tbj1Output = 9; // Output Signal to Activate TBJ1
int tbj2Output = 10; // Output Signal to Activate TBJ2
int waveState = 1; // Variable to Check state of the Wave
int prevWaveState = 1; // Variable used to change LCD screen
int tbj3Output = 12; // Output Signal to Activate TBJ3
int tbj4Output = 13; // Output Signal to Activate TBJ4
int tbj5Output = 0; // Output Signal to Activate TBJ5
int tbj6Output = 1; // Output Signal to Activate TBJ6

void setup() {
  pinMode(b1Input, INPUT);
  pinMode(tbj1Output, OUTPUT);
  pinMode(tbj2Output, OUTPUT);
  pinMode(b2Input, INPUT);
  pinMode(tbj3Output, OUTPUT);
  pinMode(tbj4Output, OUTPUT);
  pinMode(tbj5Output, OUTPUT);
  pinMode(tbj6Output, OUTPUT);
  lcd.begin(16,2);
  lcd.print("Waveform: Sine"); // The first Waveform is always a Sine
}

void loop() {
  digitalRead(b1Input);
  digitalRead(b2Input);
  
  if (digitalRead(b1Input) == 1){
    waveState++;
    delay(300);
    if (waveState > 3) waveState = 1;
  }
  
  if (digitalRead(b2Input) == 1){
    freqState++;
    delay(300);
    if (freqState > 4) freqState = 1;
  }

//Switch to Change the Frequency Scale

  switch (freqState){
    //(10-100R) Scale
    case 1:
      digitalWrite(tbj3Output, LOW);
      digitalWrite(tbj4Output, LOW);
      digitalWrite(tbj5Output, LOW);
      digitalWrite(tbj6Output, LOW);
      break;
    // (100R-1k) Scale 
    case 2:
      digitalWrite(tbj3Output, LOW);
      digitalWrite(tbj4Output, LOW);
      digitalWrite(tbj5Output, LOW);
      digitalWrite(tbj6Output, HIGH);
      break;
    // (1k - 10k) Scale  
    case 3:
      digitalWrite(tbj3Output, LOW);
      digitalWrite(tbj4Output, LOW);
      digitalWrite(tbj5Output, HIGH);
      digitalWrite(tbj6Output, HIGH);
      break;
    // (10k-100k) Scale 
    case 4:
      digitalWrite(tbj3Output, LOW);
      digitalWrite(tbj4Output, HIGH);
      digitalWrite(tbj5Output, HIGH);
      digitalWrite(tbj6Output, HIGH);
      break;
      
  }

//Switch to Change the WaveForm
  switch (waveState){
    case 1:
      digitalWrite(tbj1Output, LOW);
      digitalWrite(tbj2Output, LOW);
      break;
    case 2:
      digitalWrite(tbj1Output, LOW);
      digitalWrite(tbj2Output, HIGH);
      break;
    case 3:
      digitalWrite(tbj1Output, HIGH);
      digitalWrite(tbj2Output, HIGH);
      break;
    }

//Check if is necessary to change the Display Message
   if (prevWaveState != waveState){
    switch (waveState){
    case 1:
      lcd.clear();
      lcd.print("Waveform: Sine");
      break;
    case 2:
      lcd.clear();
      lcd.print("Waveform: Square");
      break;
    case 3:
      lcd.clear();
      lcd.print("Waveform: Trian");
      break;
    }   
   }

   prevWaveState = waveState; // Store the Previous State of the Waveform to change LCD
}
