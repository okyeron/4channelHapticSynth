/*
  You must select MIDI or Serial + MIDI from the "Tools > USB Type" menu

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformModulated waveformMod4;   //xy=126,470
AudioSynthWaveformModulated waveformMod3;   //xy=128,411
AudioSynthWaveformModulated waveformMod2;   //xy=131,358
AudioSynthWaveformModulated waveformMod1;   //xy=132,301
AudioAmplifier           amp1;           //xy=301,302
AudioAmplifier           amp2;           //xy=302,358
AudioAmplifier           amp3;           //xy=303,411
AudioAmplifier           amp4;           //xy=305,469
AudioOutputI2SQuad       audioOutput;    //xy=610,390
AudioConnection          patchCord1(waveformMod4, amp4);
AudioConnection          patchCord2(waveformMod3, amp3);
AudioConnection          patchCord3(waveformMod2, amp2);
AudioConnection          patchCord4(waveformMod1, amp1);
AudioConnection          patchCord5(amp1, 0, audioOutput, 0);
AudioConnection          patchCord6(amp2, 0, audioOutput, 1);
AudioConnection          patchCord7(amp3, 0, audioOutput, 2);
AudioConnection          patchCord8(amp4, 0, audioOutput, 3);
AudioControlSGTL5000     sgtl5000_2;     //xy=152,105
AudioControlSGTL5000     sgtl5000_1;     //xy=154,61
// GUItool: end automatically generated code


// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

int current_waveform=0;

// SETUP
void setup() {
	Serial.begin(115200);
	
	usbMIDI.setHandleNoteOn(myNoteOn);
	usbMIDI.setHandleNoteOff(myNoteOff);
	usbMIDI.setHandleAfterTouchPoly(myAfterTouchPoly);
	usbMIDI.setHandleControlChange(myControlChange);
//	usbMIDI.setHandleProgramChange(myProgramChange);
	usbMIDI.setHandleAfterTouchChannel(myAfterTouchChannel);
	usbMIDI.setHandlePitchChange(myPitchChange);
	usbMIDI.setHandleRealTimeSystem(myRealTimeSystem);

	AudioMemory(10);

	sgtl5000_1.setAddress(LOW);
	sgtl5000_1.enable();
	sgtl5000_1.volume(0.5);

	sgtl5000_2.setAddress(HIGH);
	sgtl5000_2.enable();
	sgtl5000_2.volume(0.5);

  amp1.gain(1);
  amp2.gain(1);
  amp3.gain(1);
  amp4.gain(1);

	// Configure for middle C (261.63) note without modulation ?
	float default_freq = 261.63;
  current_waveform = WAVEFORM_TRIANGLE;
  waveformMod1.begin(1.0, default_freq, current_waveform);
	waveformMod2.begin(1.0, default_freq, current_waveform);
	waveformMod3.begin(1.0, default_freq, current_waveform);
	waveformMod4.begin(1.0, default_freq, current_waveform);

  // uncomment to try modulating phase instead of frequency
  //waveformMod1.phaseModulation(720.0);
  
  
//	SPI.setMOSI(SDCARD_MOSI_PIN);
//	SPI.setSCK(SDCARD_SCK_PIN);
//	if (!(SD.begin(SDCARD_CS_PIN))) {
	// stop here, but print a message repetitively
//	while (1) {
//	  Serial.println("Unable to access the SD card");
//	  delay(500);
//	}
//	}
}

// MAIN LOOP
void loop() {
	usbMIDI.read();

}

// FUNCTIONS
void myNoteOn(byte channel, byte note, byte velocity) {
}

void myNoteOff(byte channel, byte note, byte velocity) {
}

void myAfterTouchPoly(byte channel, byte note, byte velocity) {
}

void myControlChange(byte channel, byte control, byte value) {
    switch (control) {
      case 3:
        // change freq 1  
        waveformMod1.frequency(value*2);
        Serial.println("cc1");
        break;
      case 2:
      	// change freq 2	
      	waveformMod2.frequency(value*2);
         Serial.println("cc2");
       break;
      case 1:
        // change freq 3
        waveformMod3.frequency(value*2);
         Serial.println("cc3");
       break;
      case 0:
        // change freq 4
        waveformMod4.frequency(value*2);
         Serial.println("cc4");
       break;
      default:
        break;
    }
}

void myAfterTouchChannel(byte channel, byte pressure) {
}

void myPitchChange(byte channel, int pitch) {
}

void myRealTimeSystem(uint8_t realtimebyte) {
}

void waveChanger(int current_waveform){

 // input changes the waveform type
    switch (current_waveform) {
      case WAVEFORM_SINE:
        current_waveform = WAVEFORM_SAWTOOTH;
        Serial.println("Sawtooth");
        break;
      case WAVEFORM_SAWTOOTH:
        current_waveform = WAVEFORM_SAWTOOTH_REVERSE;
        Serial.println("Reverse Sawtooth");
        break;
      case WAVEFORM_SAWTOOTH_REVERSE:
        current_waveform = WAVEFORM_SQUARE;
        Serial.println("Square");
        break;
      case WAVEFORM_SQUARE:
        current_waveform = WAVEFORM_TRIANGLE;
        Serial.println("Triangle");
        break;
      case WAVEFORM_TRIANGLE:
        current_waveform = WAVEFORM_TRIANGLE_VARIABLE;
        Serial.println("Variable Triangle");
        break;
      case WAVEFORM_TRIANGLE_VARIABLE:
        current_waveform = WAVEFORM_ARBITRARY;
        Serial.println("Arbitary Waveform");
        break;
      case WAVEFORM_ARBITRARY:
        current_waveform = WAVEFORM_PULSE;
        Serial.println("Pulse");
        break;
      case WAVEFORM_PULSE:
        current_waveform = WAVEFORM_SAMPLE_HOLD;
        Serial.println("Sample & Hold");
        break;
      case WAVEFORM_SAMPLE_HOLD:
        current_waveform = WAVEFORM_SINE;
        Serial.println("Sine");
        break;
    }
    waveformMod1.begin(current_waveform);
    waveformMod2.begin(current_waveform);
    waveformMod3.begin(current_waveform);
    waveformMod4.begin(current_waveform);

}
