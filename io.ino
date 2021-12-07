////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                        //
//                                               INITIALIZATION                                           //                                                                        
//                                                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Button States
#define BUTTON_PRESSED 0
#define BUTTON_NOT_PRESSED 1

// MIDI Message Status Bytes
#define NOTE_OFF 128
#define NOTE_ON 144
#define PROGRAM_CHANGE 192

// Note Velocities (loudness)
#define MAX_LOUDNESS 127
#define MUTE 0

// Octave Offset Mappings
#define OCTAVE_1 -36
#define OCTAVE_2 -24
#define OCTAVE_3 -12
#define OCTAVE_4 0
#define OCTAVE_5 12
#define OCTAVE_6 24
#define OCTAVE_7 36

// Note MIDI Mappings
int c4 = 60;
int db4 = 61;
int d4 = 62;
int eb4 = 63;
int e4 = 64;
int f4 = 65;
int gb4 = 66;
int g4 = 67;
int ab4 = 68;
int a4 = 69;
int bb4 = 70;
int b4 = 71;
int c5 = 72;

// Miscellaneous Parameters
int delayBetweenNotes = 300;
int octaveOffsetValue = 0;

// Default Button State Off
int C4_buttonDefaultState = BUTTON_NOT_PRESSED;
int Db4_buttonDefaultState = BUTTON_NOT_PRESSED;
int D4_buttonDefaultState = BUTTON_NOT_PRESSED;
int Eb4_buttonDefaultState = BUTTON_NOT_PRESSED;
int E4_buttonDefaultState = BUTTON_NOT_PRESSED;
int F4_buttonDefaultState = BUTTON_NOT_PRESSED;
int Gb4_buttonDefaultState = BUTTON_NOT_PRESSED;
int G4_buttonDefaultState = BUTTON_NOT_PRESSED;
int Ab4_buttonDefaultState = BUTTON_NOT_PRESSED;
int A4_buttonDefaultState = BUTTON_NOT_PRESSED;
int Bb4_buttonDefaultState = BUTTON_NOT_PRESSED;
int B4_buttonDefaultState = BUTTON_NOT_PRESSED;
int C5_buttonDefaultState = BUTTON_NOT_PRESSED;

// Note Button Pins
int C4_button_pin = 22;
int Db4_button_pin = 24;
int D4_button_pin = 26;
int Eb4_button_pin = 28;
int E4_button_pin = 30;
int F4_button_pin = 32;
int Gb4_button_pin = 34;
int G4_button_pin = 36;
int Ab4_button_pin = 38;
int A4_button_pin = 40;
int Bb4_button_pin = 42;
int B4_button_pin = 44;
int C5_button_pin = 46;

// Octave Change Button Pins
int octave_1_pin = 47;
int octave_2_pin = 53;
int octave_3_pin = 51;
int octave_4_pin = 49;
int octave_5_pin = 45;
int octave_6_pin = 50;
int octave_7_pin = 48;

// Photoresistor Pin
int velocity_pin = A0;

// Potentiometer Pin
int program_change_pin = A1;

// Photoresistor Parameters
int readVelocity; // variable that collects velocity/volume information
int photoresistorMinimumVoltage = 0;
int photoresistorMaximumVoltage = 1023; // 2^10 - 1
int midiVelocityMinimum = 35;
int midiVelocityMaximum = 127; // b/c only 7 bits to represent velocity value in note on/off messages

// Potentiometer Parameters
float readProgramChange; // variable that collects program change information
int potentiometerMinimumVoltage = 0;
int potentiometerMaximumVoltage = 1023; // 2^10 - 1
int midiProgramChangeMinimum = 0;
int midiProgramChangeMaximum = 127; // b/c only 7 bits to represent velocity value in note on/off messages


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                        //
//                                              PROGRAM SETUP                                             //                                                                        
//                                                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  pinMode(C4_button_pin, INPUT_PULLUP);
  pinMode(Db4_button_pin, INPUT_PULLUP);
  pinMode(D4_button_pin, INPUT_PULLUP);
  pinMode(Eb4_button_pin, INPUT_PULLUP);
  pinMode(E4_button_pin, INPUT_PULLUP);
  pinMode(F4_button_pin, INPUT_PULLUP);  
  pinMode(Gb4_button_pin, INPUT_PULLUP);  
  pinMode(G4_button_pin, INPUT_PULLUP);  
  pinMode(Ab4_button_pin, INPUT_PULLUP); 
  pinMode(A4_button_pin, INPUT_PULLUP); 
  pinMode(Bb4_button_pin, INPUT_PULLUP); 
  pinMode(B4_button_pin, INPUT_PULLUP);     
  pinMode(C5_button_pin, INPUT_PULLUP);   

  pinMode(octave_1_pin, INPUT_PULLUP);  
  pinMode(octave_2_pin, INPUT_PULLUP); 
  pinMode(octave_3_pin, INPUT_PULLUP); 
  pinMode(octave_4_pin, INPUT_PULLUP); 
  pinMode(octave_5_pin , INPUT_PULLUP);     
  pinMode(octave_6_pin, INPUT_PULLUP); 
  pinMode(octave_7_pin, INPUT_PULLUP);  

  pinMode(velocity_pin, INPUT);

  Serial.begin(115200); // set baud rate
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                        //
//                                               MAIN PROGRAM                                             //                                                                        
//                                                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {  
  resetNotes();
  readVelocity = photoresistorVoltageConverter(analogRead(velocity_pin));
  readProgramChange = potentiometerVoltageConverter(analogRead(program_change_pin));
  midi2MaxPC(PROGRAM_CHANGE, readProgramChange);
 
  int C4_buttonState = digitalRead(C4_button_pin);
  int Db4_buttonState = digitalRead(Db4_button_pin);
  int D4_buttonState = digitalRead(D4_button_pin);
  int Eb4_buttonState = digitalRead(Eb4_button_pin);
  int E4_buttonState = digitalRead(E4_button_pin);
  int F4_buttonState = digitalRead(F4_button_pin);
  int Gb4_buttonState = digitalRead(Gb4_button_pin);
  int G4_buttonState = digitalRead(G4_button_pin);
  int Ab4_buttonState = digitalRead(Ab4_button_pin);
  int A4_buttonState = digitalRead(A4_button_pin);
  int Bb4_buttonState = digitalRead(Bb4_button_pin);
  int B4_buttonState = digitalRead(B4_button_pin);
  int C5_buttonState = digitalRead(C5_button_pin);     

  playNote(C4_buttonState, c4 + getOctave(), readVelocity, delayBetweenNotes); 
  playNote(Db4_buttonState, db4 + getOctave(), readVelocity, delayBetweenNotes); 
  playNote(D4_buttonState, d4 + getOctave(), readVelocity, delayBetweenNotes); 
  playNote(Eb4_buttonState, eb4 + getOctave(), readVelocity, delayBetweenNotes); 
  playNote(E4_buttonState, e4 + getOctave(), readVelocity, delayBetweenNotes); 
  playNote(F4_buttonState, f4 + getOctave(), readVelocity, delayBetweenNotes); 
  playNote(Gb4_buttonState, gb4 + getOctave(), readVelocity, delayBetweenNotes); 
  playNote(G4_buttonState, g4 + getOctave(), readVelocity, delayBetweenNotes); 
  playNote(Ab4_buttonState, ab4 + getOctave(), readVelocity, delayBetweenNotes); 
  playNote(A4_buttonState, a4 + getOctave(), readVelocity, delayBetweenNotes); 
  playNote(Bb4_buttonState, bb4 + getOctave(), readVelocity, delayBetweenNotes); 
  playNote(B4_buttonState, b4 + getOctave(), readVelocity, delayBetweenNotes); 
  playNote(C5_buttonState, c5 + getOctave(), readVelocity, delayBetweenNotes);

  delay(delayBetweenNotes); 

  playNote(C4_buttonState, c4 + getOctave(), MUTE, delayBetweenNotes); 
  playNote(Db4_buttonState, db4 + getOctave(), MUTE, delayBetweenNotes); 
  playNote(D4_buttonState, d4 + getOctave(), MUTE, delayBetweenNotes); 
  playNote(Eb4_buttonState, eb4 + getOctave(), MUTE, delayBetweenNotes); 
  playNote(E4_buttonState, e4 + getOctave(), MUTE, delayBetweenNotes); 
  playNote(F4_buttonState, f4 + getOctave(), MUTE, delayBetweenNotes); 
  playNote(Gb4_buttonState, gb4 + getOctave(), MUTE, delayBetweenNotes); 
  playNote(G4_buttonState, g4 + getOctave(), MUTE, delayBetweenNotes); 
  playNote(Ab4_buttonState, ab4 + getOctave(), MUTE, delayBetweenNotes); 
  playNote(A4_buttonState, a4 + getOctave(), MUTE, delayBetweenNotes); 
  playNote(Bb4_buttonState, bb4 + getOctave(), MUTE, delayBetweenNotes); 
  playNote(B4_buttonState, b4 + getOctave(), MUTE, delayBetweenNotes); 
  playNote(C5_buttonState, c5 + getOctave(), MUTE, delayBetweenNotes);

  
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                        //
//                                               FUNCTIONS                                                //                                                                        
//                                                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Play designated note when button is pressed. 
 */
void playNote(int buttonState, int note, int velocity, int delayTime) {
  if (buttonState == BUTTON_PRESSED) {
    midi2MaxNoteOn_Off(NOTE_ON, note, velocity);
//    delay(delayTime);

//  } else {
//    midi2MaxNoteOn_Off(NOTE_OFF, note, MUTE);
  }
}

/*  
 * Send a 3-byte NoteOn/NoteOff message. Information about which key is pressed
 * at what velocity, and on what channel.
 * Note on: 1001nnnn, 0kkkkkkk, 0vvvvvvv (status byte + channel, data byte for key pressed, data byte for velocity).
 * Note off: 1000nnnn, 0kkkkkkk, 0vvvvvvv (status byte + channel, data byte for key pressed, data byte for velocity).
 */
void midi2MaxNoteOn_Off(int cmd, int data1, int data2)
{
  Serial.print(cmd); // 1001nnnn
  Serial.print(' ');
  Serial.print(data1); // 0kkkkkkk
  Serial.print(' ');
  Serial.print(data2); // 0vvvvvvv
  Serial.println();
}

/* 
 * Send a 2-byte MIDI program change message (without checking values). 
 * PC: 1011nnnn, 0ppppppp (status byte + channel, data byte for timbre change-new instrument).
 */
void midi2MaxPC(int cmd, int data1)
{
  Serial.print(cmd); // 1011nnnn
  Serial.print(' ');
  Serial.print(data1); // 0ppppppp
  Serial.println();
}

/*  
 * Verify which octave was selected from the pushbuttons and set the appropriate
 * note values. 
 */
int getOctave()
{
    int octave_1_buttonState = digitalRead(octave_1_pin);
    int octave_2_buttonState = digitalRead(octave_2_pin);
    int octave_3_buttonState = digitalRead(octave_3_pin);
    int octave_4_buttonState = digitalRead(octave_4_pin);
    int octave_5_buttonState = digitalRead(octave_5_pin);
    int octave_6_buttonState = digitalRead(octave_6_pin);
    int octave_7_buttonState = digitalRead(octave_7_pin);

    if (octave_1_buttonState == BUTTON_PRESSED) {     
      return OCTAVE_1;
    }
    else if (octave_2_buttonState == BUTTON_PRESSED) {   
      return OCTAVE_2;   
    }
    else if (octave_3_buttonState == BUTTON_PRESSED) {
     return OCTAVE_3;
    }
    else if (octave_4_buttonState == BUTTON_PRESSED) {
      return OCTAVE_4;
    }
    else if (octave_5_buttonState == BUTTON_PRESSED) {
      return OCTAVE_5;
    }
    else if (octave_6_buttonState == BUTTON_PRESSED) {
      return OCTAVE_6;
    }
    else if (octave_7_buttonState == BUTTON_PRESSED) {
      return OCTAVE_7;
    }
    else {
      return 0;
    }
}

/*  
 * Reset the note values to those of octave 4. 
 */
int resetNotes()
{
  c4 = 60;
  db4 = 61;
  d4 = 62;
  eb4 = 63;
  e4 = 64;
  f4 = 65;
  gb4 = 66;
  g4 = 67;
  ab4 = 68;
  a4 = 69;
  bb4 = 70;
  b4 = 71;
  c5 = 72;
}

/*  
 * Convert the analog input photoresistor values to the permissible 
 * midi message range for velocity bits. 
 */
int photoresistorVoltageConverter(int photoresistorVoltage)
{
  float decimalConvertion = ((photoresistorVoltage-photoresistorMinimumVoltage) / float((photoresistorMaximumVoltage-photoresistorMinimumVoltage)));
  int newMidiValue = (decimalConvertion *(midiVelocityMaximum-midiVelocityMinimum)) + midiVelocityMinimum;
  return newMidiValue;
}

/*  
 * Convert the analog input potentiometer values to the permissible 
 * midi message range for velocity bits. 
 */
int potentiometerVoltageConverter(int potentiometerVoltage)
{
  float decimalConvertion = ((potentiometerVoltage-potentiometerMinimumVoltage) / float(potentiometerMaximumVoltage-potentiometerMinimumVoltage));
  int newMidiValue = (decimalConvertion *(midiProgramChangeMaximum-midiProgramChangeMinimum)) + midiProgramChangeMinimum;
  return newMidiValue;
}
