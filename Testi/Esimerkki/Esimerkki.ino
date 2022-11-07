void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(sum(1,3));
Serial.println(multiply(2,5));
delay(1000);
Serial.println("hei");
}