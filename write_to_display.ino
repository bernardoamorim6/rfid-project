//Incluimos a livraria LiquidCrystal
#include <LiquidCrystal.h>

//Definimos os pinos que vamos a usar
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
lcd.begin(16, 2); //Inicializamos o ecrã
lcd.setCursor(0, 0); //Situamos o cursor

}

void loop()
{
lcd.print("bbb");
delay(3000);

lcd.setCursor(2,1);

lcd.print("");

lcd.setCursor(16,2);

}
