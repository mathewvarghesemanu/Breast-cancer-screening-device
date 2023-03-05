
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

//Setup
// Use dedicated hardware SPI pins
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// constants
#define buttonpin 0
#define x_increment 32
#define y_increment 34
#define x1 150
#define x2 x1+x_increment
#define x3 x2+x_increment
#define y1 25
#define y2 y1+y_increment
#define y3 y2+y_increment
#define CIRCLE_RADIUS 15
#define RECTANGLE_SIDES 25


// variables
float p = 3.1415926;
int acolor=100;
int resistance_high = 8191;
int resistance_window = 8191;
int resistance_low = resistance_high-resistance_window;
int text_start=20;
int analog_pin_array[3][3] = {
  {A0, A1, A2},
  {A3, A4, A5},
  {A0, A1, A3}
  };
int analog_value_array[3][3]={
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
  };
int analog_scaled_value_array[3][3]={
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
  };
char analog_scaled_char_array[3][3];
int analog_value_array_adjustment[3][3]={
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
  };;

void tft_setup();
void rectangle(int x, int y, int color);
int findLargest(int arr[][3]);
void testdrawtext(int x, int y, char *text, uint16_t color);

void setup(void) {
  Serial.begin(9600);           //Starting the serial communication
  tft_setup();                  //Starting the TFT screen
  tare();                        //Resetting the base value of sensor array
  delay(200);

  pinMode(buttonpin, INPUT_PULLUP);
  Serial.print(digitalRead(buttonpin));
  for (int i = 0; i < 3; i++) {
      pinMode(analog_pin_array[0][i], INPUT_PULLUP);
      pinMode(analog_pin_array[1][i], OUTPUT);
    }
    tft.fillScreen(0x0000);

}

void loop() {
 
    Serial.print(digitalRead(buttonpin));
    // tft.fillScreen(acolor);
    // acolor +=100;
    

    read_analog();
    // Serial.print(analog_value_array[0][0]);
    // Serial.print("--");
    // Serial.print(analog_value_array[0][1]);
    // Serial.print("--");
    // Serial.print(analog_value_array[0][2]);
    // Serial.print("--");
    // Serial.print(analog_value_array[1][1]);
    // Serial.print("--");
    // Serial.print(analog_value_array[1][2]);
    // Serial.print("--");
    // Serial.print(analog_value_array[1][3]);
    // Serial.print("--");
    // Serial.print(analog_value_array[2][1]);
    // Serial.print("--");
    // Serial.print(analog_value_array[2][2]);
    // Serial.print("--");
    // Serial.print(analog_value_array[2][3]);
    // Serial.println("--");
    delay(100);
  
    char sendchararr[4];
    // String stri;
    // int a = 128;

    // stri = String(a);
    // stri.toCharArray(sendchararr, 3);
    // Serial.println(sendchararr);


    

      //rectangle1
    rectangle(x1-RECTANGLE_SIDES/2,y1-RECTANGLE_SIDES/2,pressure_color(analog_scaled_value_array[0][0]));
    itoa(100-analog_scaled_value_array[0][0], sendchararr, 10);
    testdrawtext(x1-RECTANGLE_SIDES/2+2, y1-5,sendchararr, 0x0000);

    rectangle(x1-RECTANGLE_SIDES/2,y2-RECTANGLE_SIDES/2,pressure_color(analog_scaled_value_array[0][1]));
    itoa(100-analog_scaled_value_array[0][1], sendchararr, 10);
    testdrawtext(x1-RECTANGLE_SIDES/2+2, y2-5,sendchararr, 0x0000);

    rectangle(x1-RECTANGLE_SIDES/2,y3-RECTANGLE_SIDES/2,pressure_color(analog_scaled_value_array[0][2]));
    itoa(100-analog_scaled_value_array[0][2], sendchararr, 10);
    testdrawtext(x1-RECTANGLE_SIDES/2+2, y3-5, sendchararr, 0x0000);


    // //rectangle2
    rectangle(x2-RECTANGLE_SIDES/2,y1-RECTANGLE_SIDES/2,pressure_color(analog_scaled_value_array[1][0]));
    itoa(100-analog_scaled_value_array[1][0], sendchararr, 10);
    testdrawtext(x2-RECTANGLE_SIDES/2+2, y1-5, sendchararr, 0x0000);

    rectangle(x2-RECTANGLE_SIDES/2,y2-RECTANGLE_SIDES/2,pressure_color(analog_scaled_value_array[1][1]));
    itoa(100-analog_scaled_value_array[1][1], sendchararr, 10);
    testdrawtext(x2-RECTANGLE_SIDES/2+2, y2-5, sendchararr, 0x0000);

    rectangle(x2-RECTANGLE_SIDES/2,y3-RECTANGLE_SIDES/2,pressure_color(analog_scaled_value_array[1][2]));
    itoa(100-analog_scaled_value_array[1][2], sendchararr, 10);
    testdrawtext(x2-RECTANGLE_SIDES/2+2, y3-5, sendchararr, 0x0000);


    // //rectangle3
    rectangle(x3-RECTANGLE_SIDES/2,y1-RECTANGLE_SIDES/2,pressure_color(analog_scaled_value_array[2][0]));
    itoa(100-analog_scaled_value_array[2][0], sendchararr, 10);
    testdrawtext(x3-RECTANGLE_SIDES/2+2, y1-5, sendchararr, 0x0000);

    rectangle(x3-RECTANGLE_SIDES/2,y2-RECTANGLE_SIDES/2,pressure_color(analog_scaled_value_array[2][1]));
    itoa(100-analog_scaled_value_array[2][1], sendchararr, 10);
    testdrawtext(x3-RECTANGLE_SIDES/2+2, y2-5, sendchararr, 0x0000);

    rectangle(x3-RECTANGLE_SIDES/2,y3-RECTANGLE_SIDES/2,pressure_color(analog_scaled_value_array[2][2]));
    itoa(100-analog_scaled_value_array[2][2], sendchararr, 10);
    testdrawtext(x3-RECTANGLE_SIDES/2+2, y3-5, sendchararr, 0x0000);

    

  if (digitalRead(buttonpin)==0){
    calibrate();
    Serial.print("resistance_high :");
    Serial.println(resistance_high);
    Serial.print("resistance_low");
    Serial.print(resistance_low);
    Serial.print("resistance_window");
    Serial.print(resistance_window);

  }
}

void rectangle(int x, int y, int color=0xF800){
  // Function to draw a rectangle 
 tft.drawRect(x, y, RECTANGLE_SIDES, RECTANGLE_SIDES, color);
 tft.fillRect(x, y, RECTANGLE_SIDES, RECTANGLE_SIDES, color);
}

void circle(int x, int y, int color=0xF800){
  // Function to draw circle 
  tft.drawCircle(x, y, CIRCLE_RADIUS,  color);
  tft.fillCircle(x, y, CIRCLE_RADIUS,  color);
}

void testdrawtext(int x, int y, char *text, uint16_t color=0xFFFF) {
  // Function to draw text In TFT
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void read_analog(){
  char analog_char_array[4];
  // Function to Read the analog value of the sensor array
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++){
      //make jth pin in 2nd row high
      digitalWrite(analog_pin_array[1][j], HIGH);
      delay(50);
      analog_value_array[i][j] = analogRead(analog_pin_array[0][j]);
      analog_scaled_value_array[i][j]=map(analog_value_array[i][j], resistance_low, resistance_high, 0, 100);
      Serial.println(analog_value_array[i][j]);
      // analog_scaled_value_array[i][j]==100-analog_scaled_value_array[i][j];
      // Serial.println(analog_scaled_value_array[i][j]);
      // analog_scaled_char_array[i][j]= itoa(analog_value_array[i][j], analog_char_array, 10);
      
      delay(50);
      digitalWrite(analog_pin_array[1][j], LOW);
    }}}

void tare(){
  // Function to reset the base value of the sensors
  read_analog();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++){
      analog_value_array_adjustment[i][j]=analog_value_array[i][j];
  }}
  // resistance_high=findLargest(analog_value_array);
  testdrawtext(text_start, text_start, "tare executed", 0xFFFF);
  delay(1000);
  }

int findSmallest(int arr[][3]) {
  int smallest = arr[0][0];  // initialize the smallest value to the first element of the array

  for (int i = 0; i < 3; i++) {  // iterate through each row
    for (int j = 0; j < 3; j++) {  // iterate through each column
      if (arr[i][j] < smallest) {  // check if the current element is smaller than the current smallest value
        smallest = arr[i][j];  // update the smallest value if necessary
}}}
  return smallest;  // return the smallest value found
}

int findLargest(int arr[][3]) {
  int largest = arr[0][0];  // initialize the smallest value to the first element of the array

  for (int i = 0; i < 3; i++) {  // iterate through each row
    for (int j = 0; j < 3; j++) {  // iterate through each column
      if (arr[i][j] > largest) {  // check if the current element is smaller than the current smallest value
        largest = arr[i][j];  // update the smallest value if necessary
}}}

  return largest;  // return the smallest value found
}

void calibrate(){
  tft.fillScreen(ST77XX_BLACK);
  testdrawtext(text_start, text_start, "Calibration started", 0xFFFF);
  delay(2000);
  tft.fillScreen(ST77XX_BLACK);

  tare();
  testdrawtext(text_start, text_start, "tare executed", 0xFFFF);
  delay(1000);
  tft.fillScreen(ST77XX_BLACK);

  testdrawtext(text_start, text_start, "Please press sensor firmly", 0xFFFF);
  testdrawtext(40, 20, "5", 0xFFFF);
  delay(1000);
  testdrawtext(40, 20, "4", 0xFFFF);
  delay(1000);
  testdrawtext(40, 20, "3", 0xFFFF);
  delay(1000);
  testdrawtext(40, 20, "2", 0xFFFF);
  delay(1000);
  testdrawtext(40, 20, "1", 0xFFFF);
  delay(1000);
  tft.fillScreen(ST77XX_BLACK);
  read_analog();
  resistance_low=findSmallest(analog_value_array);
  resistance_window = resistance_high-resistance_low;
  testdrawtext(text_start, text_start, "Upper limit set", 0xFFFF);

  delay(1000);
  testdrawtext(text_start, text_start, "Calibration complete", 0xFFFF);
}

uint16_t pressure_color(int analog_resistance){
  uint16_t colors=0xF800;
  if (analog_resistance<20)
    colors=0xF800;
  else if (analog_resistance<40)
    colors=0xe590;
  else if (analog_resistance<60)
    colors=0xFFE0;
  else if (analog_resistance<150)
    colors=0x07E0;
  else 
  colors=0xF800;
  // colors = map(analog_resistance, -5, 110, 0, 65535);
  // colors=65535-colors;
  return colors;
}

void tft_setup(){
   //Function to set up TFT display
  // turn on backlite
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  // turn on the TFT / I2C power supply
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);

  // initialize TFT
  tft.init(135, 240); // Init ST7789 240x135
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);

  Serial.println(F("Initialized"));
}
