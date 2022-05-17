int laser = 10;
int bt = 9;
int st; // aquí se almacena el valor del botón

void setup(){
  pinMode(laser, OUTPUT);
  pinMode(bt, OUTPUT);
  digitalWrite(bt, HIGH); // así se pone para que funcione el botón

  Serial.begin(9600);
}

void loop(){

  st = digitalRead(bt); // aquí se lee el estado y se almacena en la variable

  if(st == LOW){
    digitalWrite(laser, HIGH);
  } else if (st == HIGH){
    digitalWrite(laser, LOW);
  }

  Serial.println(st);
}
