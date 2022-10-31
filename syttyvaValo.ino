int lastState = 0;
int maara = 0;
String teksti = "";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(8, OUTPUT);


}
    // joka toisella painalluksella toinen ledi syttyy
    // laske samalla toisen ledin syttymisen määrä

  //todo, tee valoista vilkkuvat - vilkkumisen nopeutta säätele potentiometrillä
  // kytke se vielä toiseen valoon, jonka kirkkaus kertoo vilkkumisen nopeudesta

void loop() {
  // put your main code here, to run repeatedly:
  int state = digitalRead(2);
  if (state != lastState) {
    if (state == HIGH) {
      maara += 1;
    }
  }
  delay(50);
  lastState = state;

  if (maara % 2 == 0) {
    if (teksti != "Päällä") {
      teksti = "Päällä";
      Serial.println(teksti);
    }
    digitalWrite(8, HIGH);
  } else {
    if (teksti != "Pois päältä") {
      teksti = "Pois päältä";
      Serial.println(teksti);
    }
    digitalWrite(8, LOW);
  }
}
