// These are the library import code to import libraries

#include <Wire.h>
#include <SdFat.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ImageReader.h>
#include <Adafruit_NeoPixel.h>

#define IMG_BUTTON_PIN 14 // defines that the image button's pin's at GPIO 14 (beside the image display)
#define TXT_BUTTON_PIN 15 // defines that the text button's pin is at GPIO 15 (beside the text display)
#define LED_BUTTON_PIN 16 // for third button beside the LED lightstrip
#define LED_PIN 17         // for pin connected to the LED data IN

// These parts set up the OLED screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 // So this means that the OLED doesn't have a reset pin which is apparently common for SSD1306

// These parts are still setting up the OLED, but the first line creates a custom Twowire object for my display because its I^2C (because otherwise the code would assume default pins only)
TwoWire customWire(i2c0);
// Creates an instance of an OLED display and specifies stats of the display as stats
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &customWire, OLED_RESET);

// Sets up the SD card reader
#define SD_CS      6     // defines pin# for the CS pin of the SD card reader
SdFat sd; // Creates an instance of the SDFat library because we need it for us to work with the SD card. Its called "sd" so we can just refer likek sd.open() n stuff like that
SPIClass customSPI(spi0); // SD card on SPI0

// Define image file tracking stuff
#define MAX_IMAGES 20 // Defines how many BMP image files are stored before the array stops
String imageFiles[MAX_IMAGES];  // Store up to 20 image filenames, as mentioned in the previous line
int imageCount = 0;     // Initialise total number of valid image files
int currentIndex = 0;   // Initialise which image filename we're currently showing

// Define text file tracking stuff
#define MAX_TEXTS 20 // Defines how many text files to store
String textFiles[MAX_TEXTS]; // Store up to 20 text filenames
int textCount = 0;     // Number of .txt files found
int currentTextIndex = 0; // Tracks which text file is currently shown

// Set up the image screen (ST7735), same process as before, just pointing out which pins go where on the Pico's GPIOs
#define TFT_CS   17
#define TFT_DC   18
#define TFT_RST  19
SPIClass tftSPI(spi1);  // Create separate SPI bus for display as the SD card already uses spi0
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);  // Initialises the screen using the pins defined above
Adafruit_ImageReader reader(sd);  // Links the ImageReader preset to the SD so that it can read stuff

Adafruit_NeoPixel strip(8, LED_PIN, NEO_GRB + NEO_KHZ800); //WS2812B strip with 8 LEDs

bool ledOn = false; //initialise current LED strip state
bool wasLedPressed = false;  // making sure that only one signal is sent in the button

void setup() {
  //Initialises USB communication for debugging ("Serial.println(...)")
  Serial.begin(115200);

  pinMode(IMG_BUTTON_PIN, INPUT_PULLUP);  // Add internal pull-up resistor for image button
  pinMode(TXT_BUTTON_PIN, INPUT_PULLUP);  // Add internal pull-up resistor for text button
  pinMode(LED_BUTTON_PIN, INPUT_PULLUP);  // LED button setup

  strip.begin();          // initialize LED strip
  strip.show();           // clear all pixels initially
  strip.setBrightness(50); // optional brightness limit is set here

  // Initialise OLED pins by telling where they are on the pico board
  customWire.setSDA(4);
  customWire.setSCL(5);
  customWire.begin(); // Starts I2C bus

  // Starts SSD1306 OLED and checks if it's working
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 init failed")); // There's an error, program halts
    while (1);
  }

  // If OLED is fine, print confirmation to it
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("OLED OK");
  display.display();

  // SD card SPI setup
  customSPI.setSCK(10); // Clock
  customSPI.setTX(11);  // MOSI
  customSPI.setRX(12);  // MISO
  customSPI.begin();    // Starts SPI bus

  // Begin to initialise the SD card reader
  if (!sd.begin(SD_CS, customSPI)) {
    display.println("SD Fail");
    display.display();
    Serial.println("SD initialization failed!");
    return;
  }

  display.println("SD OK!");
  display.display();
  delay(1000);

  // Set up the ST7735 screen (uses separate SPI1)
  tftSPI.setSCK(14);
  tftSPI.setTX(15);
  tftSPI.begin();
  tft.initR(INITR_BLACKTAB); // Common config for ST7735
  tft.setRotation(1);        // Landscape mode
  tft.fillScreen(ST77XX_BLACK); // Clear screen

  // Open image folder and show first image
  File root = sd.open("/images");
  listImageFiles(root);
  showImageName();

  // Open text folder and show first text file
  File textRoot = sd.open("/texts");
  listTextFiles(textRoot);
  showTextFile();
}

// Function to show BMP image on the ST7735 screen, similar process to displaying the text (function seen below the definition of this function)
void showImageName() {
  tft.fillScreen(ST77XX_BLACK);


  if (imageCount == 0) {
    tft.setCursor(10, 30);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(1);
    tft.println("No BMPs in /images");
    return;
  }


  String path = "/images/" + imageFiles[currentIndex];
  Serial.println("Showing: " + path);


  ImageReturnCode stat = reader.drawBMP(path.c_str(), tft, 0, 0);
  if (stat != IMAGE_SUCCESS) {
    tft.setCursor(0, 0);
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(1);
    tft.println("Load error");
    tft.println(stat);
  }
}


// Function to load the current text file and displays it on the SSD1306 (text display)
void showTextFile() {
  display.clearDisplay(); //Clears up the display
  display.setCursor(0, 0);  //Sets the cursor at the top left corner (where things will start to get drawn)
  display.setTextSize(1); //Sets text size to a present of 1, apparently 6x8 pixels per character)
  display.setTextColor(SSD1306_WHITE); // Sets text colour to a preset of white


  //Error message if there's no text files
  if (textCount == 0) {
    display.println("No .txt files");
    display.display();
    return;
  }


  //Generates the full file path to the text files
  String path = "/texts/" + textFiles[currentTextIndex];
  Serial.println("Loading: " + path); //Debug message printing


  File file = sd.open(path.c_str());  //Opens file from SD card


  //If file cannot be opened, show an error message
  if (!file) {
    display.println("Read error");
    display.display();
    return;
  }


  //Start reading the file one character at a time, by knowing if there's still characters left and if the Y would go beyond the screen
  while (file.available() && display.getCursorY() < SCREEN_HEIGHT) {
    char c = file.read(); //Read next character
    display.write(c); // Write the loaded character to screen buffer
  }


  file.close(); //Close the file
  display.display(); // Actually push buffer to screen and loads text
}


// Scans the "/images" folder and stores all .bmp file names
void listImageFiles(File dir) {
  imageCount = 0; //Resets the image counter to 0 before scanning for how many images there are
  //Infinite loop to keep checking the directory
  while (true) {
    File entry = dir.openNextFile();  //openNextFile is a function that will always check the next file. As long as there's a next file, there'd always be an entry
    if (!entry) break;  //However, if there's no entry, the loop will stop because that means there's no files left to read.


    String filename = entry.name(); //Converts filename from a char to a String type of object because apparently its easier to work with.


    //Filters files only if they have endings w/ .bmp or .BMP so that it only accepts compatiable formats.
    if (filename.endsWith(".bmp") || filename.endsWith(".BMP")) {
      if (imageCount < MAX_IMAGES) {
        imageFiles[imageCount++] = filename;
        Serial.println("Found: " + filename);
      }
    }


    entry.close();  //Close current file and move onto the next
  }
}


// Scans the /texts folder and stores all the .txt file names, similar process to w/ the images folder
void listTextFiles(File dir) {
  textCount = 0;


  while (true) {
    File entry = dir.openNextFile();
    if (!entry) break;


    String filename = entry.name();
    if (filename.endsWith(".txt") || filename.endsWith(".TXT")) {
      if (textCount < MAX_TEXTS) {
        textFiles[textCount++] = filename;
        Serial.println("Text found: " + filename);
      }
    }


    entry.close();
  }
}


void loop() {
  static bool wasImgPressed = false;
  static bool wasTxtPressed = false;

  bool imgPressed = digitalRead(IMG_BUTTON_PIN) == LOW;
  bool txtPressed = digitalRead(TXT_BUTTON_PIN) == LOW;
  bool ledPressed = digitalRead(LED_BUTTON_PIN) == LOW; 

  // If the image button is pressed...  Call the show images function and switch images based on the new index
  if (imgPressed && !wasImgPressed) {
    if (imageCount > 0) {
      currentIndex++;
      if (currentIndex >= imageCount) currentIndex = 0;
      showImageName();
      delay(200);
    }
  }

  // If the text button is pressed... Call the show texts function and switch text based on the new index
  if (txtPressed && !wasTxtPressed) {
    if (textCount > 0) {
      currentTextIndex++;
      if (currentTextIndex >= textCount) currentTextIndex = 0;
      showTextFile();
      delay(200);
    }
  }

  // Toggle LED strip on button press
  if (ledPressed && !wasLedPressed) {      // If there's a press (not a hold)...
    ledOn = !ledOn;                        // toggle the state of the LEDOn
    // Adjusts the LED either to full white or none according to the LEDOn status
    for (int i = 0; i < strip.numPixels(); i++) {  
      strip.setPixelColor(i, ledOn ? strip.Color(255, 255, 255) : 0);  
    strip.show();                           
    delay(200);                             
  }                                         

  //Stores button states for use in next loop to prevent repeated (holding) triggers.

  wasImgPressed = imgPressed;
  wasTxtPressed = txtPressed;
  wasLedPressed = ledPressed;
}
