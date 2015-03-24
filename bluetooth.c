/* Uses the wonderful SoftwareSerial library to allow a cheap
	 bluetooth device's settings to be edited through AT commands.
	 
	 In an effort to get Tom Igoe's/Mikal Hart's ftdi substitute (?)
	 working for my bluetooth device I found that adding a delay(10)
	 while reading each character from the serial input allowed the
	 longer commands such as AT-VERSION to function correctly. Whereas
	 before only AT worked and resulted on a simple OK.
	 
	 This sketch was used to program my JY-MCU v1.03 Firmware Version
	 Linvor 1.5. Not sure how it will work on other devices/firmwares.
	 I used the Arduino 1.01 serial monitor to send commands.
	 
	 
	 Commands that worked for me:
	 AT
	 AT+VERSION
	 AT+BAUDx      where 'x' is 1 or 2 or 3 or ...
	 AT+NAME...    where '...' is a 20 char or less name.
	 AT+PINxxxx    where 'xxxx' is four numbers. Example 1234.
	 
	 Receives from the hardware serial, sends to software serial.
	 Receives from software serial, sends to hardware serial.
	 
	 The circuit: 
	 * RX is digital pin 10 (connect to TX of other device)
	 * TX is digital pin 11 (connect to RX of other device)
	 
	*********************************************************
	*********************************************************
	 Created back in the mists of time
	 Modified 25 May 2012
	 by Tom Igoe
	 based on Mikal Hart's example.
	 
	 Modified 10 July 2012
	 by Peter Timinski
	 based on Tom Igoe's changes to Mikal Hart's example.
	 
	 This example code is in the public domain.
	 Nothing is guaranteed to work so PROCEDE at your OWN RISK!
	 Forum: http://arduino.cc/forum/index.php?topic=101452.0
	 *********************************************************
	 *********************************************************
	 */

	#include <SoftwareSerial.h>

	SoftwareSerial mySerial(10, 11); // RX, TX
	String command = ""; // Stores response of bluetooth device
	                     // which simply allows \n between each
	                     // response.
	void setup()  
	{
	  // Open serial communications and wait for port to open:
	  Serial.begin(115200);
	  Serial.println("Type AT commands!");
	  // SoftwareSerial "com port" data rate. JY-MCU v1.03 defaults to 9600.
	  mySerial.begin(9600);
	}

	void loop()
	{
	  // Read device output if available.
	  if (mySerial.available()) {
	    while(mySerial.available()) { // While there is more to be read, keep reading.
	      command += (char)mySerial.read();
	    }
	    Serial.println(command);
	    command = ""; // No repeats
	  }
	  
	  // Read user input if available.
	  if (Serial.available()){
	      delay(10); // The DELAY!
	      mySerial.write(Serial.read());
	  }
	}// END loop()