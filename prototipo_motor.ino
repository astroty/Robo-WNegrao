#define esquerdo 5 //Pino 5 ativa o motor esquerdo para frente
#define direito 6 //Pino 6 ativa o motor direito para frente
int bitultimo=0; //define qual foi a ultima aço feita pelo motor (se ele ativou esquerdo, direito, ou outro)
int t; //Tempo dos estados do motor
int x; //contador
int sensor; //Variavel determinando se o robo adversario saiu do sensor direito ou do sensor esquerdo
void setup()  
{  
   Serial.begin(9600); //inicia a porta serial  
   pinMode(esquerdo, OUTPUT);
   pinMode(direito, OUTPUT);
}  
  
void loop()  
{  
bitultimo = ativarmotor();
x=0;

}  

int ativarmotor()
{
switch(bitultimo){
    case 0: //estado inicial, onde ele virará meio tempo para a esquerda
      delay(5);
      digitalWrite(esquerdo, HIGH);
      while(x<(t/2)){
        //******parte de leitura dos sensores***** Vai consistir de uma leitura e um IF que resultará em um return+break caso necessário
        x++;
      }
      return 1;
      break;
      
    case 1: //Motor est virado para a direita, hora de virar para a esquerda
      digitalWrite(esquerdo, LOW);
      digitalWrite(direito, HIGH);
      while(x<t){
        //******parte de leitura dos sensores***** Vai consistir de uma leitura e um IF que resultará em um return+break caso necessário
        x++;
      }
      return 2;
      break;
      
    case 2: //Motor est virado para a esquerda, hora de virar para a direita
      digitalWrite(esquerdo, HIGH);
      digitalWrite(direito, LOW);
      while(x<t){
        //******parte de leitura dos sensores***** Vai consistir de uma leitura e um IF que resultará em um return+break caso necessário
        x++;
      }
      return 1;
      break;
      
    case 3: //Detectou um robo na frente
      digitalWrite(esquerdo, HIGH);
      digitalWrite(direito, HIGH);
      while(x=0){
        //******parte de leitura dos sensores***** Vai consistir de uma leitura e um IF que resultará em um return+break caso necessário
        // Setar no if para duas situaçes, caso o sensor de linha seja encontrado retornar o valor 4, caso o rob suma da frente, retornar valor 5
        x++; //caso o robo saia da frente dos sensores ou caso seja encontrada uma linha
        //Nao esquecer do return aqui dentro
      }
      break;
      
    case 4://caso onde ele detectou uma linha no sensor frontal
      digitalWrite(esquerdo, HIGH);
      digitalWrite(direito, LOW);
      while(x<2*t){
        //******parte de leitura dos sensores***** Vai consistir de uma leitura e um IF que resultará em um return+break caso necessário
        // Setar no if para duas situaçes, caso o sensor de linha seja encontrado retornar o valor 4, caso o rob suma da frente, retornar valor 5
        x++; 
      }
      return 1
      break;
      
    case 5: //O rob sumiu de um dos sensores do robo (direito ou esquerdo), ele tentara fazer o tracking
      switch(sensor){
      case 0: //robo esquivou para a esquerda do robo
        //While(ativar a roda direita em velocidade maxima e a esquerda em meia velocidade. Da break quando os dois sensores sao detectados, voltando para o ataque.
        break;
      case 1:
        //While(ativar a roda esquerda em velocidade maxima e a direita em meia velocidade. Da break quando os dois sensores sao detectados, voltando para o ataque.
        break;
      }
      return 3;
  }   break;
}
