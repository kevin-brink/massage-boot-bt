#define bt_rx 0     //Receive from BT     (Shouldn't actually need
#define bt_tx 1     //Transmit to BT       to use these two directly)
const int NUM = 8;
const int FIRST = 6;
int valve[NUM];

void setup() {      // put your setup code here, to run once:
  setup_bluetooth();
  for (int i = 0; i < NUM; ++i)
    valve[i] = FIRST + i;
  for(int i = 0; i < NUM; ++i) {    //Start with all valves 'false'
    pinMode(valve[i], OUTPUT);
    digitalWrite(valve[i], LOW);
  }
  pinMode(4, OUTPUT);
  
}

char seqx = 0;

void loop() {       // put your main code here, to run repeatedly
  seqx = check_bluetooth(seqx);
  seqxuence();
}

void seqxuence() {    //These sequences are just my test sequences. Not expected to actually stick around..
  int timer;
  switch (seqx) {
    case '1': {
      timer = 250;
      for (int i = 0; i < NUM; ++i) {
        seqx = check_bluetooth(seqx);
        delay(timer);
        digitalWrite(valve[i], HIGH);
      }
      digitalWrite(4, HIGH);
    
      for (int i = 0; i< NUM; ++i) {
        seqx = check_bluetooth(seqx);
        delay(timer);
        digitalWrite(valve[i], LOW);
      }
      digitalWrite(4, LOW);
    } 
      Serial.write("Finished 1\n");break;
    
    case '2': {
      timer = 100;
      for (int i = 0; i < NUM; ++i) {
        seqx = check_bluetooth(seqx);
        delay(timer);
        digitalWrite(valve[i], HIGH);
        for (int j = i + 1; j < NUM; ++j) {
          seqx = check_bluetooth(seqx);
          delay(timer);
          digitalWrite(valve[j], HIGH);
        }
        for (int j = NUM - 1; j > i; --j) {
          seqx = check_bluetooth(seqx);
          delay(timer);
          digitalWrite(valve[j], LOW);
        }
      }
      delay(timer * 5);
      for (int i = 0; i < NUM; ++i)
        digitalWrite(valve[i], LOW);
    }
      Serial.write("Finished 2\n"); break;
    
    case '3': {
      timer = 1000;
      for (int i = 0; i < NUM; ++i) {
        seqx = check_bluetooth(seqx);
        digitalWrite(valve[i], HIGH);
        delay(timer);
        digitalWrite(valve[i], LOW);
      }
    }
      Serial.write("Finished 3\n"); break;
    
    default: {
      timer = 500;
      for (int i = 0; i < NUM; ++i) 
        digitalWrite(valve[i], HIGH);
      seqx = check_bluetooth(seqx);
      delay(timer);
      for (int i = 0; i < NUM; ++i)
        digitalWrite(valve[i], LOW);
      seqx = check_bluetooth(seqx);
      delay(timer);
    }
      Serial.write("Finished Def\n");
  }
}
