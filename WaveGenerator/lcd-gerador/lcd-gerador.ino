#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);
int b1Input = 8; // Waveform Switching Button
int b2Input = 11; // Frequency Scale Switching Button
int freqState = 1; // Variable to Check State of the Scale
int prevFreqState = 1; // Variable used to change LCD screen (Frequency Scale) 
int tbj1Output = 9; // Output Signal to Activate TBJ1
int tbj2Output = 10; // Output Signal to Activate TBJ2
int waveState = 1; // Variable to Check state of the Wave
int prevWaveState = 1; // Variable used to change LCD screen (Waveform)
int tbj3Output = 12; // Output Signal to Activate TBJ3
int tbj4Output = 13; // Output Signal to Activate TBJ4
int tbj5Output = 0; // Output Signal to Activate TBJ5
int freqReader = 14; // Frequency Reader (Using A0 as digital)
boolean waveLCD, scaleLCD; // Flags for Writing the LCD

void setup() {
  pinMode(b1Input, INPUT);
  pinMode(tbj1Output, OUTPUT);
  pinMode(tbj2Output, OUTPUT);
  pinMode(b2Input, INPUT);
  pinMode(tbj3Output, OUTPUT);
  pinMode(tbj4Output, OUTPUT);
  pinMode(tbj5Output, OUTPUT);
  pinMode(freqReader, INPUT);
  
  digitalWrite(tbj3Output, HIGH);
  
  lcd.begin(16,2);
  lcd.print("Type: Sine"); // The first Waveform is always a Sine
  lcd.setCursor(0,1);
  lcd.print("R: 10-100Hz"); // The first frequency scale is always 10-100Hz
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
    if (freqState > 3) freqState = 1;
  }

//Switch to Change the Frequency Scale

  switch (freqState){
    //(10-100Hz) Scale
    case 1:
      digitalWrite(tbj3Output, HIGH);
      digitalWrite(tbj4Output, LOW);
      digitalWrite(tbj5Output, LOW);
      break;
    // (100Hz-1k) Scale 
    case 2:
      digitalWrite(tbj3Output, LOW);
      digitalWrite(tbj4Output, HIGH);
      digitalWrite(tbj5Output, LOW);
      break;
    // (1k - 10k) Scale  
    case 3:
      digitalWrite(tbj3Output, LOW);
      digitalWrite(tbj4Output, LOW);
      digitalWrite(tbj5Output, HIGH);
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

//Check if is necessary to change the Display Message (WaveForm)
   if (prevWaveState != waveState){
      waveLCD = true;    
   }

//Check if is necessary to change the Display Message (Frequency Range)
   if (prevFreqState != freqState){
      scaleLCD = true;  
   }

//Write in the LCD

 if((waveLCD) || (scaleLCD)){
     lcd.clear();
     switch (waveState){
      case 1:
        lcd.print("Type: Sine");
        break;
      case 2:
        lcd.print("Type: Square");
        break;
      case 3:
        lcd.print("Type: Trian");
        break;
      }
      switch (freqState){
        case 1:
          lcd.setCursor(0,1);
          lcd.print("R: 10-100Hz");
          break;
          
        case 2:
          lcd.setCursor(0,1);
          lcd.print("R: 100-1kHz");
          break;
        case 3:
          lcd.setCursor(0,1);
          lcd.print("R: 1-10kHz");
          break;
      }
  }

   waveLCD = false;          //
   scaleLCD = false;         //
   prevFreqState = freqState;// Set variables for a new loop cycle
   prevWaveState = waveState;//  
}
