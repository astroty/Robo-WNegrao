#define saida3 3//saida para o primeiro sensor de linha(Dianteiro) LED
#define saida4 4 //saida para o segundo sensor de linha (Traseiro) LED
#define sensorFrente 5 //pino para receber o sinal do fototransistor de frente  
#define sensorTras 6 //pino para receber o sinal do fototransistor de 
int estado1, estado2;     //variável utilizada armazenar o estado do sensor de linha
 
 
#define trigPin 13 //Pino do trigger (Obs: Não trocar)
#define echoPin 12 //Pino do Echo (Obs: Não trocar)
#define saida2 11 //Pino definido para escrita caso o sensor encontre algo LED
long duration, distance;
    
    
void setup(){
  Serial.begin(9600);
 pinMode(sensorFrente,INPUT); //definindo o pino do sensor como entrada
  pinMode(sensorTras, INPUT);
  pinMode(saida3, OUTPUT); //pino para a escrita caso o sensor indentifique a linha branca
  pinMode(saida4, OUTPUT);
  
  pinMode(trigPin, OUTPUT); // declarar pino de saída da onda
  pinMode(echoPin, INPUT); // declara pino da leitura da onda
  pinMode(saida2, OUTPUT); // declara pino de escrita caso seja encont LED
}

void loop(){
  digitalWrite(saida3, sensordelinhaFrente());
  digitalWrite(saida4, sensordelinhaTras());
    
    
  if(encontrarObstaculo()){
    digitalWrite(saida2, HIGH);//Caso retorne true escreve 5v no pino de saida
    Serial.println("ok");
  }
 else{
  Serial.println("nada"); //caso retorne false deixa o sinal em LOW no pino de saida
  digitalWrite(saida2, LOW);
 }
 delay(100);
delay(100);
 }
  
  
int sensordelinhaFrente(){
  estado1 = digitalRead(sensorFrente); //lê o estado do sensor (alto = inativo, baixo = ativo) //lê o estado do sensor de linha
  if (estado1 == HIGH) { 
    Serial.println("preto 1");
  } 
  else { 
    Serial.println("branco 1");
  }
 return !estado1; //retorna o inverso, logo se encontrar lihnha branca retornará true, se tiver em preto, false.
}


int sensordelinhaTras(){
  estado2 = digitalRead(sensorTras); //lê o estado do sensor (alto = inativo, baixo = ativo) //lê o estado do sensor de linha
  if (estado2 == HIGH) { 
    Serial.println("preto 2");
  } else { 
    Serial.println("branco 2");
  }
 return !estado2; //retorna o inverso, logo se encontrar lihnha branca retornará true, se tiver em preto, false.
}


 boolean encontrarObstaculo(){
    //Começo do código padrão para uso do ultrassom (creio que não preciso explicar isso)
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = ((duration)/29.1)/2;
    //Fim do código padrão
    if (distance >= 130 || distance <= 0){ //Caso a distancia seja maior que 130(nosso robô tem 20cm e a arena 150cm, logo 130cm é o suficient para atravessa-la) ou menor/igual a 0 (nada encontrado) retorna FALSO
      return false;
    }
    else {
      return true; //caso a confdição anterior não seja satisfeita, retornará true
    }
}
