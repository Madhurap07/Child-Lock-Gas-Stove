#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int relayPin = 10;
String password = "1234";
String input = "";

bool gasState = false;

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Child Lock Gas");
  lcd.setCursor(0,1);
  lcd.print("Enter Password");
}

void loop() {

  char key = keypad.getKey();

  if (key) {

    if (key >= '0' && key <= '9') {
      input += key;
      lcd.setCursor(input.length()-1,1);
      lcd.print("*");
    }

    if (input.length() == 4) {

      lcd.clear();

      if (input == password) {

        gasState = !gasState;

        if (gasState) {
          digitalWrite(relayPin, HIGH);
          lcd.print("Gas ON");
        }
        else {
          digitalWrite(relayPin, LOW);
          lcd.print("Gas OFF");
        }
      }
      else {
        lcd.print("Incorrect");
        lcd.setCursor(0,1);
        lcd.print("Password");
      }

      delay(2000);

      lcd.clear();
      lcd.print("Enter Password");
      input = "";
    }
  }
}