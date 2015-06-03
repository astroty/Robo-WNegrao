#define echoPin 7 //Pino 13 recebe o pulso do echo  
#define trigPin 8 //Pino 12 envia o pulso para gerar o echo  
long distancia, duration; // sao da funçao sensor ultrassom

void setup()  
{  
   Serial.begin(9600); //inicia a porta serial  
   pinMode(echoPin, INPUT); // define o pino 13 como entrada (recebe)  
   pinMode(trigPin, OUTPUT); // define o pino 12 como saida (envia)  
}  
  
void loop()  
{  
  sensorultrassom();
  Serial.print("Distancia em CM: ");
  Serial.print(distancia);
  Serial.println();
  delay(1000);

}  

int sensorultrassom(){ 
    digitalWrite(trigPin, LOW);  
    delayMicroseconds(2);   
    digitalWrite(trigPin, HIGH);  
    delayMicroseconds(10);  
    digitalWrite(trigPin, LOW);  
    duration = pulseIn(echoPin,HIGH);  //pulseInt lê o tempo entre a chamada e o pino entrar em high  
    //Esse calculo é baseado em s = v . t, lembrando que o tempo vem dobrado , porque é o tempo de ida e volta do ultrassom  
     distancia = duration /29/2 ; 
   // A velocidade do som é 340 m/s ou 29 microssegundos por centímetro.
  // A rajada sonora vai e volta, portanto, para achar a distância até o
  // objeto, tomamos metade da distância de viagem.
 
   return distancia;

}
