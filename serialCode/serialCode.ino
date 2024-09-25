#define a11 2
#define a12 3

#define a21 4
#define a22 5

#define a31 6
#define a32 7

void reset() {
  digitalWrite(a11, 1);
  digitalWrite(a12, 1);
  digitalWrite(a21, 1);
  digitalWrite(a22, 1);
  digitalWrite(a31, 1);
  digitalWrite(a32, 1);
}

void setup() {
  pinMode(a11, OUTPUT);
  pinMode(a12, OUTPUT);
  pinMode(a21, OUTPUT);
  pinMode(a22, OUTPUT);
  pinMode(a31, OUTPUT);
  pinMode(a32, OUTPUT);

  reset();

  pinMode(13, OUTPUT);
  digitalWrite(13, 0);

  Serial.begin(115200);
  Serial.setTimeout(50);
}

unsigned long t = 0;

void loop() {
  String buff = "";

  // while (Serial.available() > 0) {
  //   char ch = Serial.read();
  //   buff += ch;
  // }
  if (Serial.available() > 0) {
    buff = Serial.readString();

    if (buff.length()==3) {
      if (buff[0] == 'f') {
        digitalWrite(a11, 1);
        digitalWrite(a12, 0);
      } else if (buff[0] == 'r') {
        digitalWrite(a11, 0);
        digitalWrite(a12, 1);
      } else {
        digitalWrite(a11, 1);
        digitalWrite(a12, 1);
      }

      if (buff[1] == 'f') {
        digitalWrite(a21, 1);
        digitalWrite(a22, 0);
      } else if (buff[1] == 'r') {
        digitalWrite(a21, 0);
        digitalWrite(a22, 1);
      } else {
        digitalWrite(a21, 1);
        digitalWrite(a22, 1);
      }

      if (buff[2] == 'f') {
        digitalWrite(a31, 1);
        digitalWrite(a32, 0);
      } else if (buff[2] == 'r') {
        digitalWrite(a31, 0);
        digitalWrite(a32, 1);
      } else {
        digitalWrite(a31, 1);
        digitalWrite(a32, 1);
      }

      digitalWrite(13, 1);
      //delay(10);

    } else {
      digitalWrite(13, 0);
      //reset();
    }

    t = millis();
  }

  // if 500ms has passed from last input then reset
  if ((millis() - t) > 500) {
    reset();
    t = millis();
    digitalWrite(13, 0);
  }
}
