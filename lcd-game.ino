#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//12 - diode pin
//11 - button pin

//it creates custom character on lcd screen
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

  lcd.begin(16, 2);
  lcd.createChar(0, customChar);
  lcd.setCursor(1, 0);
  lcd.write((byte)0);

}

bool playerUp = 1;

void movePlayer() {
  if (playerUp) {
    lcd.setCursor(1, 0);
    lcd.print(" ");

    lcd.setCursor(1, 1);
    lcd.write((byte)0);
  } else {
    lcd.setCursor(1, 1);
    lcd.print(" ");

    lcd.setCursor(1, 0);
    lcd.write((byte)0);
  }
  playerUp = !playerUp;
}

char text[] = "=====";
unsigned long delayTime = 300;
unsigned long currentTime = 0;
unsigned long lastTime1 = 0;
unsigned long lastTime2 = 0;

int i = 0; //text's index
String text1 = "";
int x = 13; //position to print
int y = 13;
int j = 0;
String text2 = "";
int textLen = strlen(text);
unsigned long firstDelay = 5000;

unsigned long pointDelay = 2000;
unsigned long lastPoint = 0;
int points = 0;

bool checkTouch() {
  if (playerUp && y < 2 && y > -3) {
    return true;
  } else if (!playerUp && x < 2 && x > -3) {
    return true;
  }
  return false;
}
bool touched = false;
void loop() {

  if (checkTouch()) {
    if (touched == false) {
      touched = true;
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
      delay(500);
    }
    lcd.setCursor(2, 0);
    lcd.print("Your score: ");
    lcd.setCursor(7, 1);
    lcd.print(points);
    return;
  }

  lcd.setCursor(14, 0);
  lcd.print(points);

  if (currentTime - lastPoint >= pointDelay) {
    lastPoint = currentTime;
    points++;
  }
  currentTime = millis();

  if (digitalRead(11) == LOW) {
    digitalWrite(12, HIGH);
    movePlayer();
    delay(500);

  } else {
    digitalWrite(12, LOW);
  }
  if (currentTime - lastTime1 >= delayTime) {
    lastTime1 = currentTime;
    x -= 1;
    lcd.setCursor(x, 1);
    if (i < textLen) {
      text1 += text[i];
      lcd.print(text1);
    } else {
      if (x >= 0) {
        lcd.print(text1 + " ");
      } else {
        text1.remove(text1.length() - 1);
        lcd.print(text1 + " ");
      }
    }
    i += 1;
  }
  //it slows down appearance of the first platform
  if (currentTime < firstDelay) {
    return;
  }
  if (currentTime - lastTime2 >= delayTime) {
    lastTime2 = currentTime;
    y -= 1;
    lcd.setCursor(y, 0);
    if (j < textLen) {
      text2 += text[j];
      lcd.print(text2);
    } else {
      if (y >= 0) {
        lcd.print(text2 + " ");
      } else {
        text2.remove(text2.length() - 1);
        lcd.print(text2 + " ");
      }
    }
    j += 1;
  }
  //show another platform
  if (x < textLen - 2 * textLen) {
    x = 13;
    i = 0;
  }
  if (y < textLen - 2 * textLen) {
    y = 13;
    j = 0;
  }
}
