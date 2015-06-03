int sensorPin = 6;  //pino para receber o sinal do fototransistor
int estado;         //variável utilizada armazenar o estado do sensor de linha
 
void setup(){
  Serial.begin(9600);
  pinMode(sensorPin,INPUT); //definindo o pino do sensor como entrada
}

void loop(){
  sensordelinha();
  Serial.println(estado);
  delay(100);
}
  
  
  int sensordelinha(){
  estado = digitalRead(sensorPin); //lê o estado do sensor (alto = inativo, baixo = ativo) //lê o estado do sensor de linha
  if (estado == HIGH) { 
    Serial.println("preto");
  } else { 
    Serial.println("branco");
  }
 delay(1);
 return estado;
}
