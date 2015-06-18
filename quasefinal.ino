#define linha       5    //sensor de linha
#define linha2      6    //sensor de linha
#define esquerdo2   7    //Pino 5 ativa o motor esquerdo para frente
#define direito2    8    //Pino 6 ativa o motor direito para frente
#define esquerdo1   9    //Pino 5 ativa o motor esquerdo para frente
#define direito1    10   //Pino 6 ativa o motor direito para frente
#define echoPin     12   //Pino do Echo (Obs: Não trocar)
#define trigPin     13   //Pino do trigger (Obs: Não trocar)
#define iv          0    //infravermelho ANALOGICO
int bitultimo=0;         //define qual ser a proxima açao do motor
int bitinicio;           //define a ultima açao do motor
int t=5;               //Tempo dos estados do motor
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
    
   pinMode(esquerdo1, OUTPUT);
   //pinMode(esquerdo2, OUTPUT);
   pinMode(direito1, OUTPUT);
   //pinMode(direito2, OUTPUT);
   digitalWrite(esquerdo1, LOW);
   digitalWrite(direito1, LOW);  
   //Sensores
   pinMode(linha, INPUT);
   pinMode(linha2, INPUT);   
   pinMode(iv, INPUT);
   pinMode(trigPin, OUTPUT); // declarar pino de saída da onda
   pinMode(echoPin, INPUT); // declara pino da leitura da onda

}  
  
void loop()  
{  
  digitalWrite(esquerdo1, HIGH);
   digitalWrite(direito1, HIGH);   
Serial.println("bitultimo");
//Serial.println(bitultimo);   
delay(5000);
//bitultimo = ativarmotor();
//x=0;
delay(1000);
}  

//MOVIMENTO

int ativarmotor(){
switch(bitultimo){
    case 0: //estado inicial, onde ele virará meio tempo para a esquerda
      delay(5000);
      esquerdofrente();
      direitopara();
      while(x<(t/2) && sensor==0){
        sensor=leitura();
        x++;
      }
      bitinicio=0;
      if(sensor==0) return 1;
      else return sensor;
      break;
      
    case 1: //Motor est virado para a direita, hora de virar para a esquerda
      esquerdopara();
      direitofrente();
      while(x<t){
        sensor=leitura();
        x++;
      }
      bitinicio=1;
      if(sensor==0) return 2;
      else return sensor;
      break;
      
    case 2: //Motor est virado para a esquerda, hora de virar para a direita
      esquerdofrente();
      direitopara();
      while(x<t){
        sensor=leitura();
        x++;
      }
      bitinicio=2;
      if(sensor==0) return 1;
      else return sensor;
      break;
      
    case 3: //Detectou um robo na frente   
         
      esquerdopara();
      direitopara();
      while(sensor==3){
       Serial.println("estou aqui"); 
       sensor=leitura();
      }
      if(sensor==0 && bitinicio==2) return 1;
      if(sensor==0 && bitinicio==1) return 2;
      else return sensor;
      bitinicio=3;
      
      break;
      
    case 4://caso onde ele detectou uma linha no sensor frontal
      esquerdofrente();
      direitopara();
      while(x<2*t){
        x++; 
      }
      bitinicio=4;
      return 1;
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
      esquerdofrente();
      //direitotraz();
      direitopara();
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
   }
}

// MOTORES

void esquerdofrente(){
   digitalWrite(esquerdo1, HIGH);
//   digitalWrite(esquerdo2, LOW);
   
}


void direitofrente(){
   digitalWrite(direito1, HIGH);
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
   digitalWrite(direito1, LOW);
//   digitalWrite(direito2, LOW);
}

void esquerdopara(){
   digitalWrite(esquerdo1, LOW);
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
  if(cm>=20.0 && cm<=100.0){ // Caso o retorno em cm seja entre 20m e 150cm então é retornado um booleano true
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
   Serial.println(l); 
   l2=sensordelinhaTras();
   Serial.println(l2); 
   //i=encontrarObstaculoIR();
   i=0;  //provisorio para infravermelho nao funcional
   u=encontrarObstaculoUS();
   Serial.println(u);
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
