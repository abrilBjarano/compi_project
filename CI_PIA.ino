
#include <SPI.h>              // incuimos las librerias para leer por spi
#include <Wire.h>             //instalamos las librerias para conectar por I2C el dusplay
#include <Time.h>             // importamos las librerias para el tiempo
#include <TimeAlarms.h>       // importamos las librerias para usar las alarmas
#include <Adafruit_GFX.h>     // importamos las librerias para utilizar la pantalla
#include <Adafruit_SSD1306.h> // importamos las librerias para inicializar la pantalla
#include "RTClib.h"           // importamos las librerias para utilizar el reloj
RTC_DS1307 rtc;               // guardamos todos los metodos e la variable rtc
#include <Servo.h>            // incluimos las librerias para utilizar los servos
#include "BluetoothSerial.h"  // incluimos las librerias para utilizar el modulo bluetooth
#include "HX711.h"
HX711 loadcell;

const int LOADCELL_DOUT_PIN = 18;
const int LOADCELL_SCK_PIN = 19;
const long LOADCELL_OFFSET = 50682624;
const long LOADCELL_DIVIDER = 5895655;
float calibration_factor = 48100; // this calibration factor is adjusted according to my load cell
float units;
float ounces;

char buf1[10];     // creamos una variable para almacenar informacion
DateTime ahora;    // almacenamos los metodos de Datetime en la variable
Servo servoMotor;  // iniciamos el servo 1
Servo servoMotor1; // iniciamos el servo 2
Servo servoMotor2; // iniciamos el servo 3
char diasDeLaSemana[7][12] = {"Dom", "Lun", "Mar", "Mier", "Jue", "Vier", "Sab"};

const int led = 26;         // definimos el pin a donde conectaremos el led
const int led1 = 27;        // definimos el pin a donde conectaremos el led 2
const int pir = 15;         // definimos el pin donde conectaremos el sensor de movimiento
int estadoPir = 0;          // creamos una variable de tipo integer para iniciar el 0 el estado del pir
int estadoPir_anterior = 0; // creamos una variable de tipo entero para iniciar el 0 el estado anterior del sensor de movimiento
int contadorPresencia = 0;  // creamos una variable de tipo entero para iniciar l contador de presencia en 0
int ciclosComida = 0;
int Comida = 3;
bool juegos = false;
const int laser = 4;
BluetoothSerial BT;                                                       // almacenamos los metodos en la bariable BT
#define DEBUG 1                                                           // definimos el modo debug en encendido
#define secondsDelay 50000                                                // DEFINE el tiempo de retardo entre cada ciclo de movimientos
#define movimientos 3                                                     // DEFINE la cantidad de movimientos para ejecutar
#define SCREEN_WIDTH 128                                                  // definimos el ancho de nuestro display
#define SCREEN_HEIGHT 32                                                  // definimos el alto de nuestro display
#define OLED_RESET 4                                                      // definimos el pin virtual para resetear el display
#define SCREEN_ADDRESS 0x3C                                               // definimos la direccion del display, en este caso como es un ESP32 usamos el 0x3c, en cualquier otra tarjeta usamos 0x3D
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // mandamos la informacion de nuestra pantalla a la funcion

void Arranque()
{ // definimos la funcion que iniciara la alarma
}

void Apagado()
{                                               // funcion que se ejecutara cuando la alarma termine
  Serial.println("Alarma: - apagado 13:02:00"); // escribimos en el puerto serial que la alarma se apago
  digitalWrite(led1, LOW);                      // apagamos el led numero 1
  display.clearDisplay();                       //  limpiamos el display
  display.display();                            // ponemos disponible el display
}
void servosJuegos()
{

  servoMotor1.write(60);

  digitalWrite(laser, HIGH);
  delay(1500);

  servoMotor2.write(30);
  delay(1000);
  digitalWrite(laser, HIGH);
  servoMotor2.write(60);
  delay(1000);
  servoMotor1.write(70);
  digitalWrite(laser, HIGH);
  delay(1500);
  servoMotor1.write(10);
  delay(1000);
  servoMotor2.write(60);
  delay(1000);
  digitalWrite(laser, HIGH);
  delay(1200);
  servoMotor1.write(90);
  delay(1000);
  servoMotor2.write(30);
  delay(1000);
  digitalWrite(laser, HIGH);
  delay(1600);
  servoMotor1.write(10);
  delay(1000);
  servoMotor2.write(60);
  delay(1000);
  digitalWrite(laser, HIGH);
  delay(1700);
  servoMotor1.write(70);
  delay(1000);
  servoMotor2.write(50);
  digitalWrite(laser, HIGH);
  delay(1100);
  servoMotor1.write(10);
  delay(1000);
  servoMotor2.write(10);
  delay(1000);
  digitalWrite(laser, HIGH);
  delay(1500);
  servoMotor1.write(0);
  delay(1000);
  servoMotor2.write(0);
  delay(1500);
  alimentarMascota();
}

void juegosMascota()
{
  estadoPir = LOW;
  display.clearDisplay(); // limpiamos el display
  display.setTextSize(2);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(1, 10);
  display.print("JUGAMOS");
  display.display();
  servosJuegos();
}

void alimentarMascota()
{
  ciclosComida++;         // si la cantidad de movimientos antes ajustada es igual al contador
  display.clearDisplay(); // limpiamos el display
  display.setTextSize(2);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(1, 10);
  display.print("COMEMOS");
  display.display();
  digitalWrite(laser, LOW);
  delay(1500);
  servoMotor.write(220);
  delay(1500);
  juegos = true;
  servoMotor.write(120);
  delay(1500);
  juegos = true;

  contadorPresencia = 0;
  estadoPir = LOW;
  delay(10000);
  // estadoPir = HIGH;
}

void setup()
{
  Wire.begin();
  Serial.begin(115200);                                                   // inicializamos el puerto serial a 115200 baudios
  BT.begin("BT_Equipo_5");                                                // Nombre de su dispositivo Bluetooth y en modo esclavo
  Serial.println("El dispositivo Bluetooth está listo para emparejarse"); // imprimimos en el puerto serial un mensaje para indicar que esta listo el BT
  pinMode(pir, INPUT_PULLUP);                                             // declaramos el tipo de pin que utilizara el sensor de movimiento
  pinMode(led, OUTPUT);                                                   // declaramos el tipo de pin que utilizara el led
  digitalWrite(led, LOW);                                                 // iniciamos el led apagado
  pinMode(led1, OUTPUT);                                                  // declaramos el tipo de pin que utilizara el led 1
  digitalWrite(led1, LOW);                                                // iniciamos el led 1 apagado
  pinMode(laser, OUTPUT);                                                 // declaramos el tipo de pin que utilizara el led 1
  digitalWrite(laser, LOW);                                               // iniciamos el led 1 apagado
  servoMotor.attach(12);                                                  // indicamos el pin donde conectaremos el servo 1
  servoMotor.write(120);                                                  // lo iniciamos el la posicion de 0 grados
  servoMotor1.attach(13);                                                 // indicamos el pin donde conectaremos el servo 2
  servoMotor1.write(0);                                                   // lo iniciamos el la posicion de 0 grados
  servoMotor2.attach(14);                                                 // indicamos el pin donde conectaremos el servo 3
  servoMotor2.write(0);                                                   // lo iniciamos el la posicion de 0 grados
  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  // loadcell.set_scale(LOADCELL_DIVIDER);
  // loadcell.set_offset(LOADCELL_OFFSET);
  loadcell.set_scale();
  loadcell.tare();                            // Reset the scale to 0
  long zero_factor = loadcell.read_average(); // Get a baseline reading
  if (!rtc.begin())
  {
    Serial.println("No hay un módulo RTC");
    while (1)
      ;
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // rtc.adjust(DateTime(2022, 05, 24, 13, 23, 00));
  ahora = rtc.now();

  setTime(ahora.hour(), ahora.minute(), ahora.second(), ahora.month(), ahora.day(), ahora.year());
  // setTime(0,37,00,13, 5,22); // ajustar el tiempo a 0:37:00 13/05/2022
  // creamos las Alarmas
  Alarm.alarmRepeat(20, 26, 00, juegosMascota); // 00:37:10 todos los dias
  Alarm.alarmRepeat(20, 27, 00, Apagado);       // 00:37:20 todos los dias

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {                                                       // nos aseguramos de que el display funciona correctamente
    Serial.println(F("SSD1306 ubicacion no encontrada")); // si no esta funcionando escribimos que el display no fue encontrado
    for (;;)
      ; // creamos un ciclo infinito
  }

  display.clearDisplay();             // limpiamos el display
  display.setTextSize(0);             // ajustamos el tamaño del texto
  display.setTextColor(WHITE, BLACK); // definimos los colores de nuestro fondo y texto
  display.setCursor(0, 5);            // definimos la posicion del cursor del display
  display.print("PROYECTO PIA");      // mostramos en el display
  display.setCursor(80, 5);           // definimos la posicion del cursor del display
  display.print("EQUIPO 5");          // mostramos en el display
  display.display();                  // ponemos disponible el display
}

void loop()
{

  loadcell.set_scale(calibration_factor); // Adjust to this calibration factor

  // Serial.print("Reading: ");
  units = loadcell.get_units(10), 2;
  if (units < 0)
  {
    units = 0.00;
  }
  ounces = units * 0.035274;
  // Serial.print(units);
  // Serial.print(" kg");
  // Serial.print(" calibration_factor: ");
  // Serial.print(calibration_factor);
  Serial.println();
  delay(100);

  if (Serial.available())
  {
    char temp = Serial.read();
    if (temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if (temp == '-' || temp == 'z')
      calibration_factor -= 1;
  }
  loadcell.set_scale(calibration_factor); // Adjust to this calibration factor

  // Serial.print("Reading: ");
  units = loadcell.get_units(10), 2;
  if (units < 0)
  {
    units = 0.00;
  }
  ounces = units * 0.035274;
  Serial.print(units);
  Serial.print(" kg");
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  delay(100);

  if (Serial.available())
  {
    char temp = Serial.read();
    if (temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if (temp == '-' || temp == 'z')
      calibration_factor -= 1;
  }

  ahora = rtc.now();
  Serial.println(ahora.year());
  setTime(ahora.hour(), ahora.minute(), ahora.second(), ahora.month(), ahora.day(), ahora.year());
  sprintf(buf1, "%02d:%02d:%02d", ahora.hour(), ahora.minute(), ahora.second());
  // sprintf(buf1, "Hora %02d:%02d:%02d", hour(), minute(), second()); // guardamos los datos de hora dentro de la variable
  // Serial.println(buf1); // mostramos en el puerto serial el valor de la variable
  display.setTextSize(0);             // ajustamos el tamaño del texto del display
  display.setTextColor(WHITE, BLACK); // definimos los colores del texto
  display.setCursor(0, 22);
  display.print("Equipo-5");
  display.setCursor(80, 22); // definimos la posicion del cursor en la pantalla
  display.print(buf1);       // mostramos el valor de la variable, nos mostrara la hora, minutos y segundos
  display.setTextSize(0);
  display.setCursor(58, 22);
  display.print(diasDeLaSemana[ahora.dayOfTheWeek()]);
  display.display();            // ponemos disponible el dispaly
                                // ponemos un retardo el la alarma de 1 segundo
  estadoPir = digitalRead(pir); // obtenemos el estado del sensor de movimiento

  if (BT.available()) // si el Bluetooth esta disponible
  {
    int incoming = BT.read();   // guardamos la lectura del bluetooth en la variable incoming
    Serial.print("Recibido: "); // mostramos lo recibido en el puerto serial
    Serial.println(incoming);   // mostramos los datos recibidos en el puerto serial
    if (incoming == 48)
    {                           // si el valor es 1, en codigo ASCII
      digitalWrite(led1, HIGH); // encendemos el led 1
      alimentarMascota();
      BT.println("LED encendido"); // mandamos la informacion de que fue encendido a la aplicacion
    }
    if (incoming == 49)
    { // si el valor recibido es 0 en codigo ASCII
      juegosMascota();
      digitalWrite(led1, LOW);   // apagamos el led 1
      BT.println("LED apagado"); // mandamos la informacion a la app
    }
    if (incoming == 50)
    {                          // si el valor es 2, en codigo ASCII
      digitalWrite(led, HIGH); // encendemos el led 1

      BT.println("LED encendido"); // mandamos por el bluetooth la respuesta a la app
    }
    if (incoming == 51)
    {                            // si el valor es 3, en codigo ASCII
      digitalWrite(led, LOW);    // apagamos el led 1
      BT.println("LED apagado"); // mandamos la informacion a la app por medio del Bluetooth
    }
  }
  if (estadoPir == HIGH) // si el estado del sensor de movimiento es encendido
  {
    digitalWrite(led, HIGH); // encendemos el led 1
    if (led == LOW)          // si previamente estaba apagado
    {

      digitalWrite(led, HIGH);
    }
  }
  else
  {
    digitalWrite(led, LOW); // si no es encendido el sensor de movimiento apagamos el led 1
    if (led == HIGH)        // si previamente estaba encendido
    {

      digitalWrite(led, LOW);
    }
  }
  if (estadoPir == LOW && estadoPir_anterior == HIGH) // si el estado del sensor de movimiento es apagado y su estado anterior es encendido
  {
    contadorPresencia++;                // incrementamos la variable
    display.clearDisplay();             // limpiamos el display
    display.setTextSize(0);             // ajustamos el tamaño del texto
    display.setTextColor(WHITE, BLACK); // ajustamos los colores del texto
    display.setCursor(0, 5);            // definimos la posicion del cursor
    display.print("MOVIMIENTOS ");      // escribimos la palabra en el display
    display.setCursor(110, 5);          // definimos la posicion del cursor
    display.print(contadorPresencia);   // mostramos en el display el valor del contador de movimientos
    display.setCursor(90, 5);           // definimos la posicion del cursor
    display.print(ciclosComida);
    display.display(); // ponemos disponible el displayc
                       // Serial.println(contadorPresencia); // mostramos en el purto serial el valor del contador
  }

  estadoPir_anterior = estadoPir; // guardamos el valor del pir en la variable anterior
  if (ciclosComida <= Comida)
  {
    if (contadorPresencia == movimientos)
    {
      juegosMascota();
      // alimentarMascota();

      // display.clearDisplay();
      //   display.display();
    }
    if (ciclosComida == Comida)
    {
      ciclosComida = 0;
    }
  }

  Alarm.delay(1000);
}
