#define RUN 1
#define WALK 0
#define END -1

long times[2][128] = {{
    0, WALK, 300, 
    RUN, 60, WALK, 90, 
    RUN, 60, WALK, 90,
    RUN, 60, WALK, 90, 
    RUN, 60, WALK, 90,
    RUN, 60, WALK, 90, 
    RUN, 60, WALK, 90,
    RUN, 60, WALK, 90, 
    RUN, 60, WALK, 90,
    END, END
},{
    0, WALK, 20, 
    RUN, 60, WALK, 90, 
    RUN, 60, WALK, 90,
    RUN, 60, WALK, 90, 
    RUN, 60, WALK, 90,
    RUN, 60, WALK, 90, 
    RUN, 60, WALK, 90,
    RUN, 60, WALK, 90, 
    RUN, 60, WALK, 90,
    END, END
}};

int sound[] = {131, 440};

void beep(int iSpeed) {
  int iBeepTime;
  Serial.println(millis());
  Serial.println("Beeping...");
  for (iBeepTime = 0 ; iBeepTime < 10; iBeepTime++) {
    tone(8, sound[iSpeed]);
    delay(500);
    noTone(8);
    delay(500);
  }
}

void setup(void) {
  int i = 0;
  int bDone = 0;
  Serial.begin(9600);
  Serial.println("");
  while (!bDone) {
    if (times[0][i] == END) {
         Serial.println(millis());
         Serial.println("Sing a little song - we're done...");
         bDone = 1;
         i+=2;
    } else {
      if (times[0][i] == 0) {
         Serial.println(millis());
         Serial.println("First Walk");
         beep(WALK);
      } else {
          Serial.println(millis());
          Serial.println("Transition ");
          Serial.print(times[0][i-1]);
          Serial.print(" ");
          Serial.print(i);
          Serial.println("");
          beep(times[0][i-1]);
      }
    Serial.println(millis());
    Serial.println("Delaying ");
    Serial.print(times[0][i] * 1000);
    Serial.println("");
    delay(times[0][i] * 1000);
    Serial.println(millis());
    Serial.println("Done delay");
    i+=2;
    }
  }
}
  

void loop(void) {
  
}
