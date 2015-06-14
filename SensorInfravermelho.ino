#define sensorIR 0    //Declaração do Pino analógico em que será feita a leitura do sensor
#define saida 10       //Pino onde será escrito o booleano (Se há, ou não, um objeto ou adversário na frente do robô)
float sensorValue, cm;    //Must be of type float for pow()

void setup() {
  Serial.begin(9600);
  pinMode(saida, OUTPUT); //Definindo o pino para escrita
}

void loop() {
  if(encontrarObstaculoIR()){ //executa função principal que retorna boleano
    digitalWrite(saida, HIGH); //caso o boleano retorne true, será feita uma escrita na porta
  }
  else{
    //Serial.println("nada");
    digitalWrite(saida, LOW); //caso contrario a porta estará sem sinal (LOW)
  }
  delay(100);
}

boolean encontrarObstaculoIR(){
  sensorValue = analogRead(sensorIR);
  //inches = 4192.936 * pow(sensorValue,-0.935) - 3.937;
  cm = 10650.08 * pow(sensorValue,-0.935) - 7; //Função definida por http://arduinomega.blogspot.com.br/2011/05/infrared-long-range-sensor-gift-of.html e adaptada para nosso caso
  if(cm>=20.0 && cm<=150.0){ // Caso o retorno em cm seja entre 20m e 150cm então é retornado um booleano true
  //Serial.print("cm: ");
  //Serial.println(cm);
  return true;
  }
  //Serial.println("nada");
  return false; //caso não tenha retorno o if anterior, então retorna um false
}
