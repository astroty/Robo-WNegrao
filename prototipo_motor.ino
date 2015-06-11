#define esquerdo1 5  //Pino 5 ativa o motor esquerdo para frente
#define esquerdo2 6  //Pino 5 ativa o motor esquerdo para frente
#define direito1  7  //Pino 6 ativa o motor direito para frente
#define direito2  8  //Pino 6 ativa o motor direito para frente
#define linha     10 //sensor de linha
#define iv        11 //infravermelho
#define usa       12 //ultrassom
int bitultimo=0;     //define qual foi a ultima aço feita pelo motor (se ele ativou esquerdo, direito, ou outro)
int t;               //Tempo dos estados do motor
int x;               //contador
int sensor;

void setup()  
{  
   Serial.begin(9600); //inicia a porta serial  
   pinMode(esquerdo1, OUTPUT);
   pinMode(esquerdo2, OUTPUT);
   pinMode(direito1, OUTPUT);
   pinMode(direito2, OUTPUT);
   pinMode(linha, INPUT);
   pinMode(iv, INPUT);
   pinMode(usa, INPUT);
}  
  
void loop()  
{  
bitultimo = ativarmotor();
x=0;

}  

int ativarmotor(){
switch(bitultimo){
    case 0: //estado inicial, onde ele virará meio tempo para a esquerda
      delay(5000);
      esquerdofrente();
      while(x<(t/2) && sensor==0){
        sensor=leitura();
        x++;
      }
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
      if(sensor==0) return 1;
      else return sensor;
      break;
      
    case 3: //Detectou um robo na frente
      esquerdofrente();
      direitofrente();
      while(sensor==3){
       sensor=leitura();
      }
      return sensor;
      break;
      
    case 4://caso onde ele detectou uma linha no sensor frontal
      esquerdofrente();
      direitopara();
      while(x<2*t){
        x++; 
      }
      return 1;
      break;
      
    case 5: //tracking esquerdo
      //nao sera incluido enquanto/se nao for instalado o pwm
      break;
    case 6: //tracking direito
      //nao sera incluido enquanto/se nao for instalado o pwm
      break;
   }
}


void esquerdofrente(){
   digitalWrite(esquerdo1, HIGH);
   digitalWrite(esquerdo2, LOW);
   
}


void direitofrente(){
   digitalWrite(direito1, HIGH);
   digitalWrite(direito2, LOW);
   
}

void esquerdotraz(){
   digitalWrite(esquerdo1, LOW);
   digitalWrite(esquerdo2, HIGH);
}


void direitotraz(){
   digitalWrite(direito1, LOW);
   digitalWrite(direito2, HIGH);
}

void direitopara(){
   digitalWrite(direito1, LOW);
   digitalWrite(direito2, LOW);
}

void esquerdopara(){
   digitalWrite(esquerdo1, LOW);
   digitalWrite(esquerdo2, LOW);
}


int leitura(){
   int l=digitalRead(linha) , i=digitalRead(iv) , u=digitalRead(usa);
   if(l==1){
      return 4;
   }
   if(i==1 && u==1){
      return 3;
   }
   if(i==1 && u==0){
      return 5;
   }
   if(u==1 && i==0){
      return 6;
   }
   else{
      return 0;
   }
}
