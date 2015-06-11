  #define sensorIR 0    //Must be an analog pin
#define saida 7
float sensorValue, cm;    //Must be of type float for pow()

void setup() {
  Serial.begin(9600);
  pinMode(saida, OUTPUT);
}

void loop() {
  if(encontrarObstaculoIR()){
    digitalWrite(saida, HIGH);
  }
  else{
    //Serial.println("nada");
    digitalWrite(saida, LOW);
  }
  delay(100);
}

boolean encontrarObstaculoIR(){
  sensorValue = analogRead(sensorIR);
  //inches = 4192.936 * pow(sensorValue,-0.935) - 3.937;
  cm = 10650.08 * pow(sensorValue,-0.935) - 7;
  if(cm>=20.0 && cm<=150.0){
  //Serial.print("cm: ");
  //Serial.println(cm);
  return true;
  }
  //Serial.println("nada");
  return false;
}
