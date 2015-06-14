#define trigPin 13 //Pino do trigger (Obs: Não trocar)
#define echoPin 12 //Pino do Echo (Obs: Não trocar)
#define saida2 11 //Pino definido para escrita caso o sensor encontre algo
    long duration, distance;
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT); // declarar pino de saída da onda
  pinMode(echoPin, INPUT); // declara pino da leitura da onda
  pinMode(saida2, OUTPUT); // declara pino de escrita caso seja encontrado algo
}

void loop() {
 if(encontrarObstaculo()){
    digitalWrite(saida2, HIGH);//Caso retorne true escreve 5v no pino de saida
  }
 else{
  //Serial.println("nada"); //caso retorne false deixa o sinal em LOW no pino de saida
  digitalWrite(saida2, LOW);
 }
 delay(100);
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
