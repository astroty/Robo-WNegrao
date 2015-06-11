#define saida3 3
#define saida4 4
#define sensorFrente 5 //pino para receber o sinal do fototransistor
#define sensorTras 6
int estado;     //variável utilizada armazenar o estado do sensor de linha
 
void setup(){
  Serial.begin(9600);
  pinMode(sensorFrente,INPUT); //definindo o pino do sensor como entrada
  pinMode(sensorTras, INPUT);
  pinMode(saida3, OUTPUT);
}

void loop(){
  digitalWrite(saida3, sensordelinhaFrente());
  digitalWrite(saida4, sensordelinhaTras());
  delay(100);
}
  
  
int sensordelinhaFrente(){
  estado = digitalRead(sensorFrente); //lê o estado do sensor (alto = inativo, baixo = ativo) //lê o estado do sensor de linha
  if (estado == HIGH) { 
    Serial.println("preto");
  } else { 
    Serial.println("branco");
  }
 return !estado;
}
int sensordelinhaTras(){
  estado = digitalRead(sensorTras); //lê o estado do sensor (alto = inativo, baixo = ativo) //lê o estado do sensor de linha
  if (estado == HIGH) { 
    Serial.println("preto");
  } else { 
    Serial.println("branco");
  }
 return !estado;
}
