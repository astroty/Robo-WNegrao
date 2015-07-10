#include <Servo.h>
#include <Button.h>

#define esquerdo1   5    //Pino 5 ativa o motor esquerdo para frente
#define direito1    7    //Pino 6 ativa o motor direito para frente
#define direito2    6    //Pino 6 ativa o motor direito para frente
#define linha2      8    //sensor de linha
#define linha       9    //sensor de linha
#define echoPin     12   //Pino do Echo (Obs: Não trocar)
#define trigPin     13   //Pino do trigger (Obs: Não trocar)
int bitultimo=0;         //define qual ser a proxima açao do motor
int bitinicio;           //define a ultima açao do motor
int t=800;                 //Tempo dos estados do motor
int sensor;              //variavel que sera usada para o return na funçao ativarmotor(). Ele sera atribuido o valor da leitura e sera uma das condiçoes de saida precoce do while, sendo retornado como resultado da funçao int
//LINHA
int estado1, estado2;     //variável utilizada armazenar o estado do sensor de linha
//ULTRASSOM
long duration, distance;
volatile unsigned long LastPulseTime;
static unsigned long startTime;
Button button1 = Button(2,PULLUP);
Button button2 = Button(3,PULLUP);
    




//leitura
int l,l2,u;
int i;

void setup()  
{  
   Serial.begin(9600); //inicia a porta serial  
   //Motores
   digitalWrite(esquerdo1, HIGH);
   digitalWrite(direito1, LOW);
   digitalWrite(direito2, LOW);
   pinMode(esquerdo1, OUTPUT);
   pinMode(direito1, OUTPUT);
   pinMode(direito2, OUTPUT);
   //Sensores
   pinMode(linha, INPUT);
   pinMode(linha2, INPUT);   
   pinMode(trigPin, OUTPUT); // declarar pino de saída da onda
   pinMode(echoPin, INPUT); // declara pino da leitura da onda

}

void loop()  
{
Serial.println("");     
Serial.print("bitultimo:");     
Serial.print(bitultimo);   
bitultimo = ativarmotor();
LastPulseTime=0;
startTime=0;
}  





// MOTORES



//Rele esquerda
void esquerdofrente(){
     digitalWrite(esquerdo1, LOW);
   
}

void esquerdopara(){
   digitalWrite(esquerdo1, HIGH);
}

//Ponte H direita

void direitofrente(){
     digitalWrite(direito2, LOW);
     digitalWrite(direito1, HIGH);
   
}

void direitotraz(){
   digitalWrite(direito1, LOW);
   digitalWrite(direito2, HIGH);
}


void direitopara(){
   digitalWrite(direito1, LOW);  
   digitalWrite(direito2, LOW);
}



//SENSORES

void sensordelinhaFrente(){
  estado1 = digitalRead(linha); //lê o estado do sensor (alto = inativo, baixo = ativo) //lê o estado do sensor de linha
  if(estado1==0){
    bitultimo=4;
    ativarmotor();
    } 
  estado2 = digitalRead(linha2); //lê o estado do sensor (alto = inativo, baixo = ativo) //lê o estado do sensor de linha
  if(estado2==0){
    bitultimo=4;
    ativarmotor();
  } 
}



void buttom(){
        if(button1.isPressed()){
                  bitultimo=6;
                  sensor=0;
                  ativarmotor();
        }
        if(button2.isPressed()){
                  bitultimo=7;
                  sensor=0;
                  ativarmotor();
        }
}

void encontrarObstaculoUS(){
 //ComeÃ§o do cÃ³digo padrÃ£o para uso do ultrassom (creio que nÃ£o preciso explicar isso)

  digitalWrite(trigPin, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
 /* Serial.println("");  
  Serial.print("Duraçao:");
  Serial.println(duration);
*/
  distance = ((duration)/29.1)/2;

  Serial.println("");  
  Serial.print("Distancia:");
  Serial.println(distance);
  if (distance >= 100 || distance <= 0){} //Caso a distancia seja maior que 130(nosso robÃ´ tem 20cm e a arena 150cm, logo 130cm Ã© o suficient para atravessa-la) ou menor/igual a 0 (nada encontrado) retorna FALSO
  
  else {  
    bitultimo=3;
    sensor=3;
    ativarmotor();
  }
}




int leitura(){
   //linhafrente
//   l=sensordelinhaFrente();  
sensordelinhaFrente();  
//buttom();
   //linhatras
//   l2=sensordelinhaTras();
//sensordelinhaTras();
   //US
   //u=encontrarObstaculoUS();
encontrarObstaculoUS();   
      return 0;
}



int ativarmotor(){
switch(bitultimo){
    case 0: //estado inicial, onde ele virará meio tempo para a esquerda
      delay(3500);
      direitopara();
      esquerdofrente();
      startTime=millis();      
      while(LastPulseTime<=(t/2) && sensor==0){
        sensor=leitura();
        LastPulseTime=(millis()-startTime);
              Serial.println("");
              Serial.print("LastPulseTime0:");
              Serial.print(LastPulseTime); 
      }
      Serial.println("");
      Serial.print("sensor");
      Serial.print(sensor);      
      bitinicio=2;
      if(sensor==0) return 1;
      else return sensor;
      break;
      
      
    case 1: //Motor est virado para a direita, hora de virar para a esquerda
      esquerdopara();
      direitofrente();
      startTime=millis();      
      while(LastPulseTime<=t && sensor==0){
        sensor=leitura();
        LastPulseTime=(millis()-startTime);
      }
      Serial.println("");
      Serial.print("LastPulseTime1:");
      Serial.print(LastPulseTime);            
      bitinicio=1;
      if(sensor==0) return 2;
      else return sensor;
      break;
      
      
    case 2: //Motor est virado para a esquerda, hora de virar para a direita
      direitopara();
      esquerdofrente();
      startTime=millis();      
      while(LastPulseTime<=t  && sensor==0){
        sensor=leitura();
        LastPulseTime=(millis()-startTime);
      }
      Serial.println("");
      Serial.print("LastPulseTime2:");
      Serial.print(LastPulseTime);            
      bitinicio=2;
      if(sensor==0) return 1;
      else return sensor;
      break;
      
      
    case 3: //Detectou um robo na frente
      delay(200);
      Serial.println("");     
      Serial.print("bitultimo:");     
      Serial.print(bitultimo);       
      esquerdofrente();
      direitofrente();
      while(sensor==3){
       sensor=leitura();
      };
      if(sensor==0 && bitinicio==2) return 1;
      if(sensor==0 && bitinicio==1) return 2;
      else return sensor;
      break;
      
    case 4://caso onde ele detectou uma linha no sensor frontal
      Serial.println("");     
      Serial.print("bitultimo:");     
      Serial.print(bitultimo);     
      direitotraz();      
      esquerdofrente();
      delay(560);   
      esquerdofrente();
      direitofrente();
      delay(500);
      sensor=leitura();
      if(sensor==0 && bitinicio==2) return 1;
      if(sensor==0 && bitinicio==1) return 2;
      else return sensor;
      break; 
      
    case 5: //caso ele tenha detectado uma linha na traseira dele. O que será impossível sem a ação do outro robô, pois ele não dá ré por conta própria
      Serial.println("");     
      Serial.print("bitultimo:");     
      Serial.print(bitultimo); 
      esquerdofrente();      
      direitotraz();
      delay(560);
      direitofrente();
      LastPulseTime=0;
      sensor=leitura(); //reseta a variavel sensor      
      startTime=millis();      
      while(LastPulseTime<=t  && sensor==3){
        sensor=leitura();
        LastPulseTime=(millis()-startTime);
      }
      return sensor; //ao final da revoluçao, empurra normalmente
      break; 
      
    case 6:  //botão esquerdo
      Serial.println("");     
      Serial.print("bitultimo:");     
      Serial.print(bitultimo);     
      esquerdopara();
      direitofrente();
      startTime=millis();      
      while(LastPulseTime<=500  && sensor==0){
        sensor=leitura();
        LastPulseTime=(millis()-startTime);
      }
      Serial.println("");
      Serial.print("LastPulseTime6:");
      Serial.print(LastPulseTime);            
      if(sensor==0 && bitinicio==2) return 1;
      if(sensor==0 && bitinicio==1) return 2;
      else return sensor;
      break;
      
    case 7:  //botão esquerdo
      Serial.println("");     
      Serial.print("bitultimo:");     
      Serial.print(bitultimo);       
      direitopara();
      esquerdofrente();
      startTime=millis();  
 
      while(LastPulseTime<=500  && sensor==0){                                
        sensor=leitura();
        LastPulseTime=(millis()-startTime);   
      }
      Serial.println("");
      Serial.print("LastPulseTime7:");
      Serial.print(LastPulseTime);            
      if(sensor==0 && bitinicio==2) return 1;
      if(sensor==0 && bitinicio==1) return 2;
      else return sensor;
      break;      
   }
}
