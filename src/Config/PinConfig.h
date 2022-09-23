#ifndef PINCONFIG_H
#define PINCONFIG_H
#define PIN_TROTTLE_SENSOR  17 // ehem 27; //D9,A9 //Poti für Geschwindigkeit // TODO prüfen ob im M4 noch unterstütz an dieser Stelle -> wire manually

#define PIN_ODRV_SERIAL_RX 0 // -> wired manually

#define PIN_ODRV_SERIAL_TX 1 // -> wired manually
#define PIN_LED 13 // -> wired manually
#define PIN_BUTTON_UP 19 // ehem 23 -> wired manually
#define PIN_BUTTON_DOWN 23 // ehem 14 -> wired manually
#define PIN_BUTTON_RIGHT 24 //ehem 15 -> wired manually
#define PIN_BUTTON_LEFT 25 //ehem 16 -> wired manually
#define PIN_BUTTON_MID 18 //ehem 22 -> wired manually
#define PIN_BUTTON_ON_OFF 11 // -> wired manually
#define PIN_HOLD_PWR 10 // -> wired manually
#define PIN_I2C_TCK = 22 //ehem 3 -> wired manually
#define PIN_I2C_SDA = 21 // ehem 21 -> wired manually

#endif //PINCONFIG_H