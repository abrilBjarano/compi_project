int buzz = 8; // el pin del buzzer

int Do = 261;
int Re = 293;
int Mi = 329;
int Fa = 349;
int Sol = 392;
int La = 440;
int Si = 493;

int negra = 150; // la duración de la nota
int blanca = 500;
int retardo = 3000; 

void setup(){
}

void loop(){

  hora_comida();
  delay(2000);
  hora_ejercicio();
  delay(2000);
}

void hora_comida(){
  
  tone(buzz, Do, negra);
  delay(negra);
  noTone(buzz);
  delay(negra);
  tone(buzz, Sol, negra);
  delay(negra);
  noTone(buzz);
  delay(negra);
  tone(buzz, La, negra);
  delay(negra);
  noTone(buzz);
  delay(negra);
  tone(buzz, Sol, blanca);
  delay(negra);
  noTone(buzz);
  delay(negra);
}

void hora_ejercicio(){
  
  tone(buzz, Sol, blanca);
  delay(negra);
  noTone(buzz);
  delay(negra);
  tone(buzz, La, negra);
  delay(negra);
  noTone(buzz);
  delay(negra);
  tone(buzz, Sol, negra);
  delay(negra);
  noTone(buzz);
  delay(negra);
  tone(buzz, Do, negra);
  delay(negra);
  noTone(buzz);
  delay(negra);
   
}
