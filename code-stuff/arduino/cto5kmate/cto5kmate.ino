// stuff
const int weekPin = 5;
const int programPin = 6;
const int runPin = 7;
const int audioOutPin = 8;
int weekMode = 0;
int progMode = 0;

#define WEEKMAX 9
#define PROGMAX 3

int runPinState = 0;
int weekPinState = 0;
int programPinState = 0;
int runState = 0;
int i = 0;

#define RUN 1
#define WALK 0
#define END -1

long times[3][128] = {{
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
// B A G A B B B A A A B D D
int littlesong[] = {247, 220, 196, 220, 247, 247, 247, 220, 220, 220, 247, 294, 294, 294};

void playlittlesong(void) {
    int count = 0;
    for (count = 0; count < 15; count++) {
      tone(audioOutPin, littlesong[count]);
      delay(250);
      noTone(audioOutPin);
      delay(250);
  }
}

void beep(int iSpeed) {
  int iBeepTime;
  //Serial.println(millis());
  //Serial.println("Beeping...");
  for (iBeepTime = 0 ; iBeepTime < 10; iBeepTime++) {
    tone(audioOutPin, sound[iSpeed]);
    delay(500);
    noTone(audioOutPin);
    delay(500);
  }
}

void setup() {
  // Serial configuration used for debugging in the serial consol monitor
  Serial.begin(9600);
  delay(1000);
  Serial.println("Startup");
  
  // INPUT 
  pinMode(runPin,INPUT);
  pinMode(weekPin, INPUT);
  pinMode(programPin, INPUT);
  pinMode(audioOutPin, OUTPUT);

  return;
}

void loop() {
  runPinState = digitalRead(runPin);
  weekPinState = digitalRead(weekPin);
  programPinState = digitalRead(programPin);
  //Serial.println("");
  //Serial.print(runPinState);
  //Serial.print(" ");
  //Serial.print(programPinState);
  //Serial.print(" ");
  //Serial.print(weekPinState);

  if (!(runState)) {
    if (runPinState == HIGH) {
      runState = 1;
      i = 0;
      Serial.println("HIGH");
      Serial.println("RUN!!!!");
    } else {
      // Serial.println("LOW");
    }
    if (weekPinState == HIGH) {  
      Serial.println("Week mode incrementing");
      weekMode ++;
      weekMode = weekMode % WEEKMAX;
      Serial.println("\tWeekmode beep: ");
      Serial.print(weekMode);
      Serial.println("");
      delay(200);
    }
    if (programPinState == HIGH) {
      Serial.println("Program mode incrementing");
      progMode ++;
      progMode = progMode % PROGMAX;
      Serial.println("\tProgmode beep: ");
      Serial.print(progMode);
      Serial.println("");
      delay(200);
    }
  } else {
    int j = 0;
    int bDone = 0;

    while (!bDone) {
      if (times[0][j] == END) {
	Serial.println("Sing a little song - we're done...");
        playlittlesong();
	bDone = 1;
	j+=2;
      } else {
	if (times[0][j] == 0) {
	  beep(WALK);
	} else {
          beep(times[0][j-1]);
	}
	delay(times[0][j] * 1000);
	j+=2;
      }
    }
    runState = 0;
    weekMode = 0;
    progMode = 0;
  }
}
