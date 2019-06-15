#include <Servo.h> 
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#include <cactus_io_AM2302.h>

#define AM2302_PIN 13 

Servo servo;

AM2302 dht(AM2302_PIN);
#define BTN_UP   1
#define BTN_DOWN 2
#define BTN_LEFT 3
#define BTN_RIGHT 4
#define BTN_SELECT 5
#define BTN_NONE 10

int detectButton() {
  int keyAnalog =  analogRead(A0);
  if (keyAnalog < 100) {
    // Значение меньше 100 – нажата кнопка right
    return BTN_RIGHT;
  } else if (keyAnalog < 200) {
    // Значение больше 100 (иначе мы бы вошли в предыдущий блок результата сравнения, но меньше 200 – нажата кнопка UP
    return BTN_UP;
  } else if (keyAnalog < 400) {
    // Значение больше 200, но меньше 400 – нажата кнопка DOWN
    return BTN_DOWN;
  } else if (keyAnalog < 600) {
    // Значение больше 400, но меньше 600 – нажата кнопка LEFT
    return BTN_LEFT;
  } else if (keyAnalog < 800) {
    // Значение больше 600, но меньше 800 – нажата кнопка SELECT
    return BTN_SELECT;
  } else {
    // Все остальные значения (до 1023) будут означать, что нажатий не было
    return BTN_NONE;
  }
}
void clearLine(int line){
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void printDisplay(String message, int row){
  Serial.println(message);
  lcd.setCursor(0, row);
  lcd.print(message);
  delay(1000);
  
}

int relay1=3;
int relay2=11;


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Team 28");
  delay(3000);
  lcd.setCursor(0, 0);
  lcd.print("Team 28");
  dht.begin();
  servo.attach(12);
  servo.write(45);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
}

void buttons(){
int button = detectButton();

  switch (button) {
    case BTN_UP:
      printDisplay("UP",1);
      break;
    case BTN_DOWN:
      printDisplay("DOWN",1);
      break;
    case BTN_LEFT:
      printDisplay("LEFT",1);
      break;
    case BTN_RIGHT:
      printDisplay("RIGHT",1);
      break;
    case BTN_SELECT:
      printDisplay("SELECT",1);
      break;
    default:
      //printDisplay("Press any key");
      break;
  }
  
}


void serv(){
  for(int i=45;i>=0;i--){
  servo.write(i); 
  delay(10);
  }

  delay(200); //ждем 2 секунды

   for(int i=0;i<=90;i++){
  servo.write(i); 
  delay(10);
  }

  delay(200); //ждем 2 секунды

   for(int i=90;i>=45;i--){
  servo.write(i); 
  delay(10);
  }
  
}

float n_temp=27;
int n=0;
void loop() {
  buttons();
  dht.readHumidity();
  dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(dht.humidity) || isnan(dht.temperature_C)) {
    printDisplay("DHT sensor read failure!", 0);
    
    return;
  }

  float temp=dht.temperature_C;
  if(temp < n_temp){

    digitalWrite(relay1, HIGH);    
  }
  else{
    digitalWrite(relay1, LOW); 
  }
  printDisplay("T:"+String(temp)+" C", 0);
  printDisplay("H:"+String(dht.humidity)+"%", 1);
  if(n==10){
    serv();
    n=0;
  }
  
  delay(300);
  n++;
}
