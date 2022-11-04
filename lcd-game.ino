#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//12 - dioda
//11 - przycisk

//znak ludzika
byte customChar[8] = {
	0b00000,
	0b01110,
	0b01110,
	0b01110,
	0b00100,
	0b00110,
	0b00100,
	0b01010
};

void setup() {
  Serial.begin(9600);

  pinMode(12, OUTPUT);
  pinMode(11, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcd.begin(16,2);
  lcd.createChar(0, customChar);
  lcd.setCursor(1,0);
  lcd.write((byte)0);

}

void drawRect() {
  while(true) {
    lcd.setCursor(1,0);
    lcd.print("Hello world");
  }
}

bool playerUp = true;

void movePlayer() {
  if(playerUp) {
    lcd.setCursor(1,0);
    lcd.print(" ");

    lcd.setCursor(1,1);
    lcd.write((byte)0);
  } else {
    lcd.setCursor(1,1);
    lcd.print(" ");

    lcd.setCursor(1,0);
    lcd.write((byte)0);
  }
    playerUp = !playerUp;
}

char text[] = "Hello!";
unsigned long delayTime = 500;
unsigned long currentTime = 0;
unsigned long lastTime = 0;

int i = 0; //text's index
String text2 = "";
int x = 15; //position to print

void loop() {
  currentTime = millis();

  if(digitalRead(11) == LOW) {
    digitalWrite(12, HIGH);
    movePlayer();
    delay(500);  
  } else {
    digitalWrite(12, LOW); 
  }

 
  if(currentTime - lastTime >= delayTime) {
    lastTime = currentTime;
    x -= 1;
    lcd.setCursor(x,1);
    if(i < strlen(text)) {
      text2+=text[i];
      lcd.print(text2);  // Print a message to the LCD.
    } else {
      lcd.print(text2 + " ");
    }
    
    
    i+=1;
  }
}
