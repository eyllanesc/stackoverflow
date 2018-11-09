double data = 0.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  data += 0.1;
  Serial.println(data);
  delay(1000);

}
