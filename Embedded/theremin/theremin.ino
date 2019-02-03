#define potPin A0
#define buttonPin 11
#define ledPin 8
#define spkrPin 3

#define MAX_FREQ 3150
#define MIN_FREQ 260

int freq = 0;
int potValue = 0;

int low_notes[] = {261,277,293,311,329,349,369,392,415,440,466,493,523};
int med_notes[] = {783,830,880,932,987,1046,1108,1174,1244,1318};
int hi_notes[] = {1396,1479,1567,1661,1760,1864,1975,2093,2217,2349,2489,2637,2793,2959,2135};      

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(spkrPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

int findNote(int freq)
{
  if(freq < 780){
    Serial.println("me");
    for (int i = 0; i < 13-1; i++)
      {
        if (low_notes[i] - freq < 0)
          continue;
        else
        {
          int dist1 = freq - low_notes[i-1];
          int dist2 = low_notes[i] - freq;
          Serial.println("you");
          if (dist1 > dist2)
            return low_notes[i];
          else
            return low_notes[i-1];
         }
      }
  }

  else if(freq > 780 && freq < 1350)
  {
     for (int i = 0; i < 10-1; i++)
      {
        if (med_notes[i] - freq < 0)
        continue;
        else
        {
          int dist1 = freq - med_notes[i-1];
          int dist2 = med_notes[i] - freq;
          if (dist1 > dist2)
            return med_notes[i];
          else
            return med_notes[i-1];
         }
      }
  }
  //mid notes

  else if(freq > 1350)
  {
      for (int i = 0; i < 15-1; i++)
      {
        if (hi_notes[i] - freq < 0)
        continue;
        else
        {
          int dist1 = freq - hi_notes[i-1];
          int dist2 = hi_notes[i] - freq;
          if (dist1 > dist2)
            return hi_notes[i];
          else
            return hi_notes[i-1];
         }
      }
  }
}
void loop() {
  potValue = analogRead(potPin);
  float potFrac = potValue/1024.0;
  freq = (int)(potFrac*(MAX_FREQ-MIN_FREQ));
  freq += MIN_FREQ;
  //Serial.println(freq);
  
  if(!digitalRead(buttonPin)){ 
    int playTone = findNote(freq); 
    Serial.println(playTone);  
    tone(spkrPin, playTone);
    digitalWrite(ledPin, HIGH);
    delay(10);
  }
  else{
    noTone(spkrPin);    
    digitalWrite(ledPin, LOW);
  }
}
