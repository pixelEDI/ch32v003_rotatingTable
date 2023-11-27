/*
        _          _ ______ _____ _____ 
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |  
 | '_ \| \ \/ / _ \ |  __| | |  | || |  
 | |_) | |>  <  __/ | |____| |__| || |_ 
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |                                    
 |_|                                    
                             
www.pixeledi.eu | https://linktr.ee/pixeledi
Rotating Table | V1.0 | 11.2023

  Idea and Code by Maker 101: 
  https://www.hackster.io/mertarduino/3d-printed-arduino-rotating-table-with-28byj-48-stepper-0a5cfe

*/

const int btn = D6;
// Define the pins for ULN2003AN
const int in1 = C1;
const int in2 = C2;
const int in3 = C4;
const int in4 = A2;

// Any other Arduino
// const int in1 = 2;
// const int in2 = 3;
// const int in3 = 4;
// const int in4 = 5;

int delayTime = 10;
int cnt = 0;

//max torque
int steps[4][4] = {
  { 1, 1, 0, 0 },
  { 0, 1, 1, 0 },
  { 0, 0, 1, 1 },
  { 1, 0, 0, 1 }
};

void checkReset() {
  //if max val is recognized (x times) -> startvalue is reassigend
  if (cnt == 5) {
    cnt = 0;
    delayTime = 10;
  }
}

void checkBtn() {
  if (digitalRead(btn) == HIGH) {
    delayTime++;

    if (delayTime >= 30) {
      delayTime = 30;
      cnt++;

      checkReset();
    }
    //oldschool debounce
    delay(100);
  }
}

void setup() {
  pinMode(btn, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
}
void loop() {

  checkBtn();

  for (int i = 0; i < 4; i++) {

    //ch32v003 doenst like variables in digitalWrite?!
    digitalWrite(in1, (steps[i][0] == HIGH) ? HIGH : LOW);
    digitalWrite(in2, (steps[i][1] == HIGH) ? HIGH : LOW);
    digitalWrite(in3, (steps[i][2] == HIGH) ? HIGH : LOW);
    digitalWrite(in4, (steps[i][3] == HIGH) ? HIGH : LOW);

    // you can use this for Arduinos
    // digitalWrite(in1, steps[i][0]);
    // digitalWrite(in2, steps[i][1]);
    // digitalWrite(in3, steps[i][2]);
    // digitalWrite(in4, steps[i][3]);

    delay(delayTime);

    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}
