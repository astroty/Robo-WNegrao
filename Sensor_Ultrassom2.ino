#define trigPin 13
#define echoPin 12
#define saida2 11
    long duration, distance;
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT); // declarar pino de saída
  pinMode(echoPin, INPUT);
  pinMode(saida2, OUTPUT);
}

void loop() {
 if(encontrarObstaculo()){
    digitalWrite(saida2, HIGH);
  }
 else{
  Serial.println("nada");
  digitalWrite(saida2, LOW);
 }
 delay(100);
}
  boolean encontrarObstaculo(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = ((duration)/29.1)/2;
    if (distance >= 130 || distance <= 0){
      return false;
    }
    else {
      return true;
    }
}
