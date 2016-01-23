
#include <Audio.h>
#include <Wire.h>
#include <SerialFlash.h>
#include <IntervalTimer.h>

#include "reSID.h"
#include "pp_hammer.h"

IntervalTimer myTimer;

AudioPlaySID             playSID;  //xy=189,110
AudioAnalyzeRMS          rms1;           //xy=265,187
AudioOutputI2S           i2s1;           //xy=366,111
AudioConnection          patchCord1(playSID, 0, i2s1, 0);
AudioConnection          patchCord2(playSID, 0, i2s1, 1);
AudioConnection          patchCord3(playSID, rms1);
AudioControlSGTL5000     sgtl5000_1;     //xy=354,176

void sound(void);

void soundInit(void) {
   AudioMemory(4);
   sgtl5000_1.enable();
   sgtl5000_1.volume(0.6);  
   myTimer.begin(sound, 20*1000);  
}

void sound(void) {
  static unsigned int snd_pos = 0;
  static char oldbuffer[26] = {0};  

  for(int i=0;i<25;i++) {
      if(snd_data[snd_pos+i] != oldbuffer[i]) {       
        playSID.setreg(i, snd_data[snd_pos+i]);
        oldbuffer[i] = snd_data[snd_pos+i];                  
      } 
  }
  snd_pos +=25;
  if (snd_pos > sizeof(snd_data)) snd_pos = 0;
}


