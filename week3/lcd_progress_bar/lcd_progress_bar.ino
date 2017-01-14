/**
 * The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

// Includes LiquidCrystal library for LCD 
#include  <LiquidCrystal.h>

/**
 * Create lcd object with a pin configuration
 * compatible with shield LCD DFRobots
 */
LiquidCrystal lcd(8 , 9 , 4 , 5 , 6 , 7);


/**
 * Constants for the size of the LCD
 */
const  int LCD_NB_ROWS =  2 ;
const  int LCD_NB_COLUMNS =  16 ;

/* Custom Characters */ 
byte DIV_0_OF_5[8] = {
  B00000, 
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
}; // 0/5

byte DIV_1_OF_5[8] = {
  B10000, 
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000
}; // 1/5

byte DIV_2_OF_5[8] = {
  B11000, 
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000
}; // 2/5

byte DIV_3_OF_5[8] = {
  B11100, 
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100
}; // 3/5

byte DIV_4_OF_5[8] = {
  B11110, 
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110
}; // 4/5

byte DIV_5_OF_5[8] = {
  B11111, 
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
}; // 5/5

/**
 * The LCD configuration function for the progress bar.
 * Uses custom characters from 0 to 5 (6 and 7 remain available).
 */

void setup_progressbar() {
  /**
   * Saves the custom characters in
   * the memory of the LCD
   */
  lcd.createChar ( 0 , DIV_0_OF_5);
  lcd.createChar ( 1 , DIV_1_OF_5);
  lcd.createChar ( 2 , DIV_2_OF_5);
  lcd.createChar ( 3 , DIV_3_OF_5);
  lcd.createChar ( 4 , DIV_4_OF_5);
  lcd.createChar ( 5 , DIV_5_OF_5);
}

void draw_progressbar(byte percent) {
  /* Display the new value in digital form on the first line */ 
  lcd.setCursor (0 , 0);
  lcd.print(percent);
  lcd.print(F("%"));
  // NB The two spaces at end of line can erase digit percentage last
  // when you pass a value to two or three digits to a value two or numbers.

  /* Move the cursor on the second line */ 
  lcd.setCursor(0 , 1);

  /* Map of range (0 ~ 100) to the beach (0 ~ LCD_NB_COLUMNS * 5) */ 
  byte nb_columns = map (percent, 0 , 100 , 0 , LCD_NB_COLUMNS *  5 );

  /* Draw each character in the line */ 
  for (byte i =  0 ; i < LCD_NB_COLUMNS; ++ i) {
    /* Depending on the number of remaining columns to display */ 
    if(nb_columns ==  0) { // empty Case 
      lcd.write((byte) 0);

    } else if (nb_columns >= 5) { // case full 
      lcd.write(5);
      nb_columns -= 5;

    } else { // last non-empty box
      lcd.write (nb_columns);
      nb_columns = 0;
    }
  }
}

void setup() { 
  /* Initializes the LCD screen */
  lcd.begin (LCD_NB_COLUMNS, LCD_NB_ROWS);
  setup_progressbar ();
  lcd.clear ();
}

void loop() {
  /* Value is a percentage of the progress bar */ 
  static byte percent =  0;
 
  /* Displays the value */
  draw_progressbar(percent);

  /* Increases the percentage */ 
  if(++percent >  100) {
    // Returns to zero if the percentage exceeds 100% 
    percent = 0;
    delay(1000);
  }

  /* Wait small time */ 
  delay(100);
}
