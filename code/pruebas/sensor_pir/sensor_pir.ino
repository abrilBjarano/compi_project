int pir = 2;
int led = 3;
int buz = 4;
int mov; // variable que cuenta las veces que el pir detectó al gato jugando

void setup() {

  pinMode(pir, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buz, OUTPUT);
  Serial.begin(9600);

}

void loop() {

  if(digitalRead(pir) == HIGH){
    digitalWrite(led, HIGH);
    digitalWrite(buz, HIGH); 
    mov = mov + 1; // cada vez que detecte movimiento, se suma uno a la variable mov
  } 
  else {
    digitalWrite(led, LOW);
    digitalWrite(buz, LOW);
    mov = mov + 0; // si no, no se suma nada
  }

  Serial.println(mov); // para verificar por el serial monitor si funcionaba
  delay(2000);

} 
