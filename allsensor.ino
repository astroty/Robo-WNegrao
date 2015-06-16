//Sensores de linha
#define saidasensorlinhafrente 3//saida para o primeiro sensor de linha(Dianteiro) LED
#define saidasensorlinhatras 4 //saida para o segundo sensor de linha (Traseiro) LED
#define sensorFrente 6 //pino para receber o sinal do fototransistor de frente  
#define sensorTras 5 //pino para receber o sinal do fototransistor de 
int estado1, estado2;     //variável utilizada armazenar o estado do sensor de linha

//Sensor ultrassom 
 
#define trigPin 13 //Pino do trigger (Obs: Não trocar)
#define echoPin 12 //Pino do Echo (Obs: Não trocar)
#define saidaultrassom 11 //Pino definido para escrita caso o sensor encontre algo LED
long duration, distance;
int x;

//Sensor IR
    
#define sensorIR 0    //Declaração do Pino analógico em que será feita a leitura do sensor
#define saidaIR 10       //Pino onde será escrito o booleano (Se há, ou não, um objeto ou adversário na frente do robô)
float sensorValue, cm;    //Must be of type float for pow()
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup(){
  Serial.begin(9600);
  //Linha
  pinMode(sensorFrente,INPUT); //definindo o pino do sensor como entrada
  pinMode(sensorTras, INPUT);
  pinMode(saidasensorlinhafrente, OUTPUT); //pino para a escrita caso o sensor indentifique a linha branca
  pinMode(saidasensorlinhatras, OUTPUT);
  
  //Ultrassom
  pinMode(trigPin, OUTPUT); // declarar pino de saída da onda
  pinMode(echoPin, INPUT); // declara pino da leitura da onda
  pinMode(saidaultrassom, OUTPUT); // declara pino de escrita caso seja encont LED
  
  //IR
  pinMode(saidaIR, OUTPUT); //Definindo o pino para escrita do IR
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop(){
  Serial.println("");
  //Linha
  digitalWrite(saidasensorlinhafrente, sensordelinhaFrente());
  digitalWrite(saidasensorlinhatras, sensordelinhaTras());
  
  //IR
  if(encontrarObstaculoIR()){ //executa função principal que retorna boleano
   digitalWrite(saidaIR, HIGH); //caso o boleano retorne true, será feita uma escrita na porta
  }
  else{
   digitalWrite(saidaIR, LOW); //caso contrario a porta estará sem sinal (LOW)
  }
  
  //Ultrassom
  x=6;
  if(x>=6){
   if(encontrarObstaculoUS()){
     Serial.print("||US:");
     Serial.print(distance);
     digitalWrite(saidaultrassom, HIGH);//Caso retorne true escreve 5v no pino de saida
   }
   else{
     digitalWrite(saidaultrassom, LOW);
   }
   x=0;
  }
  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
int sensordelinhaFrente(){
  estado1 = digitalRead(sensorFrente); //lê o estado do sensor (alto = inativo, baixo = ativo) //lê o estado do sensor de linha
  if (estado1 == HIGH) { 
    Serial.print("||preto 1");
  } 
  else { 
    Serial.print("||branco 1");
  }
 return !estado1; //retorna o inverso, logo se encontrar lihnha branca retornará true, se tiver em preto, false.
}


int sensordelinhaTras(){
  estado2 = digitalRead(sensorTras); //lê o estado do sensor (alto = inativo, baixo = ativo) //lê o estado do sensor de linha
  if (estado2 == HIGH) { 
    Serial.print("||preto 2");
  } else { 
    Serial.print("||branco 2");
  }
 return !estado2; //retorna o inverso, logo se encontrar lihnha branca retornará true, se tiver em preto, false.
}


 boolean encontrarObstaculoUS(){
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

boolean encontrarObstaculoIR(){
  sensorValue = analogRead(sensorIR);
  //inches = 4192.936 * pow(sensorValue,-0.935) - 3.937;
  cm = 10650.08 * pow(sensorValue,-0.935) - 7; //Função definida por http://arduinomega.blogspot.com.br/2011/05/infrared-long-range-sensor-gift-of.html e adaptada para nosso caso
  if(cm>=20.0 && cm<=150.0){ // Caso o retorno em cm seja entre 20m e 150cm então é retornado um booleano true
  Serial.print("||cm: ");
  Serial.print(cm);
  return true;
  }
  Serial.print("||cm: ");
  Serial.print("nada");
  return false; //caso não tenha retorno o if anterior, então retorna um false
}
