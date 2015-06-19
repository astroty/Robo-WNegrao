#define linha       5    //sensor de linha
#define linha2      6    //sensor de linha
#define esquerdo1   7    //Pino 5 ativa o motor esquerdo para frente
#define direito1    8   //Pino 6 ativa o motor direito para frente
#define esquerdo2   9    //Pino 5 ativa o motor esquerdo para frente
#define direito2    10    //Pino 6 ativa o motor direito para frente
#define echoPin     12   //Pino do Echo (Obs: Não trocar)
#define trigPin     13   //Pino do trigger (Obs: Não trocar)
#define iv          0    //infravermelho ANALOGICO
int bitultimo=0;         //define qual ser a proxima açao do motor
int bitinicio;           //define a ultima açao do motor
int t=60;               //Tempo dos estados do motor
int x=0;                 //contador
int sensor;              //variavel que sera usada para o return na funçao ativarmotor(). Ele sera atribuido o valor da leitura e sera uma das condiçoes de saida precoce do while, sendo retornado como resultado da funçao int
//LINHA
int estado1, estado2;     //variável utilizada armazenar o estado do sensor de linha
//ULTRASSOM
long duration, distance;
//IR
float sensorValue, cm;    //Must be of type float for pow()


//leitura
int l,l2,u;
int i;

void setup()  
{  
   Serial.begin(9600); //inicia a porta serial  
   //Motores
   digitalWrite(esquerdo1, HIGH);
   digitalWrite(direito1, HIGH);
   pinMode(esquerdo1, OUTPUT);
   pinMode(esquerdo2, OUTPUT);
   pinMode(direito1, OUTPUT);
   pinMode(direito2, OUTPUT);
   //Sensores
   pinMode(linha, INPUT);
   pinMode(linha2, INPUT);   
   pinMode(iv, INPUT);
   pinMode(trigPin, OUTPUT); // declarar pino de saída da onda
   pinMode(echoPin, INPUT); // declara pino da leitura da onda

}  
  
void loop()  
{
Serial.println("bitultimo");     
Serial.println(bitultimo);   
bitultimo = ativarmotor();
x=0;
delay(100);
}  

//MOVIMENTO

int ativarmotor(){
switch(bitultimo){
    case 0: //estado inicial, onde ele virará meio tempo para a esquerda
      delay(5000);
      direitopara();
      esquerdofrente();
      while(x<(t/2) && sensor==0){
        sensor=leitura();
        x++;
      }
      bitinicio=2;
      if(sensor==0) return 1;
      else return sensor;
      break;
      
      
    case 1: //Motor est virado para a direita, hora de virar para a esquerda
      esquerdopara();
      direitofrente();
      while(x<(3*t/4) && sensor==0){
        sensor=leitura();
        x++;
      }
      bitinicio=1;
      if(sensor==0) return 8;
      else return sensor;
      break;
      
      
    case 2: //Motor est virado para a esquerda, hora de virar para a direita
      direitopara();
      esquerdofrente();
      while(x<(3*t/4)  && sensor==0){
        sensor=leitura();
        x++;
      }
      bitinicio=2;
      if(sensor==0) return 8;
      else return sensor;
      break;
      
      
    case 3: //Detectou um robo na frente
      esquerdopara();
      direitopara();
      esquerdofrente();
      direitofrente();
      while(sensor==3){
       sensor=leitura();
      }
      if(sensor==0 && bitinicio==2) return 1;
      if(sensor==0 && bitinicio==1) return 2;
      else return sensor;
      break;
      
      
    case 4://caso onde ele detectou uma linha no sensor frontal
      direitopara();
      esquerdofrente();
      delay(2000);
      sensor=0;
      return 8;
      break;
      
      
    case 5: //tracking esquerdo
      //nao sera incluido enquanto/se nao for instalado o pwm
      bitinicio=5;
      break;
      
      
      
    case 6: //tracking direito
      //nao sera incluido enquanto/se nao for instalado o pwm
      bitinicio=6;
      break;
      
      
      
    case 7: //caso ele tenha detectado uma linha na traseira dele. O que será impossível sem a ação do outro robô, pois ele não dá ré por conta própria
      direitopara();
      esquerdofrente();
      //direitotraz();
      //tenta girar o robô, para o por numa posição desvantajosa
      while(x<t){
        x++; //primeiro dá uma meia revolução, para sair de cima da linha e poder começar a ler normalmente
      }
      x=0; //reseta o contador
      sensor=leitura(); //reseta a variavel sensor
      while(x<t && sensor==3){ //dá o resto da revolução, contanto que o adversário esteja na frente
        sensor=leitura(); 
        x++; 
      }
      bitinicio=6;
      return sensor; //ao final da revoluçao, empurra normalmente
      break;
      
      
      
    case 8:
      esquerdofrente();
      direitofrente();
      while(x<t  &&  sensor==0){
       sensor=leitura();
       x++;
      }
      esquerdopara();
      direitopara();
      if(sensor==0 && bitinicio==2) return 1;
      if(sensor==0 && bitinicio==1) return 2;
      else return sensor;
      break;
      
   }
}

// MOTORES

void esquerdofrente(){
     digitalWrite(esquerdo1, LOW);
     Serial.println("esquerdofrente");   
//   digitalWrite(esquerdo2, LOW);
   
}


void direitofrente(){
     digitalWrite(direito1, LOW);
     Serial.println("direitofrente");   
//   digitalWrite(direito2, LOW);
   
}
/*
void esquerdotraz(){
   digitalWrite(esquerdo1, LOW);
   digitalWrite(esquerdo2, HIGH);
}


void direitotraz(){
   digitalWrite(direito1, LOW);
   digitalWrite(direito2, HIGH);
}
*/

void direitopara(){
   digitalWrite(direito1, HIGH);
     Serial.println("direitopara");   
//   digitalWrite(direito2, LOW);
}

void esquerdopara(){
   digitalWrite(esquerdo1, HIGH);
   Serial.println("esquerdopara");   
//   digitalWrite(esquerdo2, LOW);
}

//SENSORES

int sensordelinhaFrente(){
 estado1 = digitalRead(linha); //lê o estado do sensor (alto = inativo, baixo = ativo) //lê o estado do sensor de linha
 return !estado1; //retorna o inverso, logo se encontrar lihnha branca retornará true, se tiver em preto, false.
}


int sensordelinhaTras(){
 estado2 = digitalRead(linha2); //lê o estado do sensor (alto = inativo, baixo = ativo) //lê o estado do sensor de linha
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
  sensorValue = analogRead(iv);
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


int leitura(){
   Serial.println("vai");
   l=sensordelinhaFrente();  
   Serial.print("||");
   Serial.print(l);
   //l2=sensordelinhaTras();
   l2=0;
   //i=encontrarObstaculoIR();
   i=0;  //provisorio para infravermelho nao funcional
   u=encontrarObstaculoUS();
   Serial.print("||");
   Serial.print(u);
   if(l==1){
      return 4;
   }
   if(l2==1){
      return 7;
   }
   if(i==1 || u==1){
      return 3;
   }
   /*if(i==1 && u==0){
      return 5;
   }
   if(u==1 && i==0){
      return 6;
   }
   */
   else{
      return 0;
   }
}
