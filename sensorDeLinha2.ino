#define saida3 3 //saida para o primeiro sensor de linha(Dianteiro)
#define saida4 4 //saida para o segundo sensor de linha (Traseiro)
#define sensorFrente 5 //pino para receber o sinal do fototransistor de frente
#define sensorTras 6 //pino para receber o sinal do fototransistor de tras
int estado;     //variável utilizada armazenar o estado do sensor de linha
 
void setup(){
  Serial.begin(9600);
  pinMode(sensorFrente,INPUT); //definindo o pino do sensor como entrada
  pinMode(sensorTras, INPUT);
  pinMode(saida3, OUTPUT); //pino para a escrita caso o sensor indentifique a linha branca
  pinMode(saida4, OUTPUT);
}

void loop(){
  digitalWrite(saida3, sensordelinhaFrente());
  digitalWrite(saida4, sensordelinhaTras());
  delay(100);
}
  
  
int sensordelinhaFrente(){
  estado = digitalRead(sensorFrente); //lê o estado do sensor (alto = inativo, baixo = ativo) //lê o estado do sensor de linha
  /*if (estado == HIGH) { 
    Serial.println("preto");
  } else { 
    Serial.println("branco");
  }*/
 return !estado; //retorna o inverso, logo se encontrar lihnha branca retornará true, se tiver em preto, false.
}
int sensordelinhaTras(){
  /*estado = digitalRead(sensorTras); //lê o estado do sensor (alto = inativo, baixo = ativo) //lê o estado do sensor de linha
  if (estado == HIGH) { 
    Serial.println("preto");
  } else { 
    Serial.println("branco");
  }*/
 return !estado; //retorna o inverso, logo se encontrar lihnha branca retornará true, se tiver em preto, false.
}
