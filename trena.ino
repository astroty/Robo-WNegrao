#include <LiquidCrystal.h> 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
const int echo = 8 , trigger = 9 , medir = 6 , medidaDinamica = 7 , area = 10;
double tempo;
float distancia_cm , x , y , medirArea;
int botaoMedir , botaoMedidaDinamica , botaoArea ;

void setup() { 
  Serial.begin(9600);
  lcd.begin(16, 2); 
  pinMode(echo, INPUT);
  pinMode(medir, INPUT);
  pinMode(medidaDinamica, INPUT);
  pinMode(area, INPUT);
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW);
  lcd.setCursor(0,0);
  lcd.print("   Escolha a ");
  lcd.setCursor(0,1);
  lcd.print(" funcionalidade");
} 

void loop() {

  lerBotao();
  if (botaoMedir == LOW){
    distancia() ;
  }
  else if (botaoMedidaDinamica == LOW){
    lerBotao();
    distanciaDinamica() ;
  }
  else if (botaoArea == LOW){
    areas() ;
  }
}



int lerBotao () {
  botaoMedir = digitalRead(medir); 
  botaoMedidaDinamica = digitalRead(medidaDinamica); 
  botaoArea = digitalRead(area); 

  return botaoMedir , botaoMedidaDinamica , botaoArea ;
}



void distancia () {
  calculoDistancia();
  limparTela();
  lcd.setCursor(0,0);
  lcd.print(distancia_cm); 
  lcd.setCursor(7,0);
  lcd.print("cm");
}



void distanciaDinamica () {
  do{
    calculoDistancia ();
    limparTela();
    lcd.setCursor(0,0);
    lcd.print(distancia_cm);
    lcd.setCursor(7,0);
    lcd.print("cm");
    lerBotao();
    delay(300);  
  }
  while(botaoMedir == HIGH);

}


void areas () {
  limparTela();
  lcd.setCursor(0,0);
  lcd.print("Pressione");
  lcd.setCursor(0,1);
  lcd.print("Medir Area ");
  delay(200);
  do{
      lerBotao();
      x = calculoDistancia();
      delay(200);
    }
  while(botaoArea == 1);
    
  
      limparTela();
      lcd.setCursor(0,0);
      lcd.print("Pressione-o");
      lcd.setCursor(0,1);
      lcd.print("novamente");
      delay(200);
  do{
	lerBotao();
	y = calculoDistancia();
        delay(200);
	}
   while(botaoArea == 1);
	medirArea = x*y;
        limparTela();
        lcd.setCursor(0,0);
	lcd.print("Area total    2"); 
	lcd.setCursor(0,1);
	lcd.print(medirArea);
        lcd.setCursor(12,1);
	lcd.print("cm");  

} 



int calculoDistancia () {
  digitalWrite(trigger, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  tempo = pulseIn(echo, HIGH);
  distancia_cm = tempo/58 ;
 
  return distancia_cm;
}

void limparTela(){
lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");  
}
