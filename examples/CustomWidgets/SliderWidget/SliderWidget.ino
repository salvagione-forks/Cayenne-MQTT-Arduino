/*
Cayenne Slider Widget Example

This sketch shows how to set up a Slider Widget with Cayenne.

The CayenneMQTT Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. In the Cayenne Dashboard add a new Slider Custom Widget.
2. Select a virtual channel number.
3. Set the slider widget min value to 0 and max value to 255.
4. Set the VIRTUAL_CHANNEL value below to the virtual channel number you selected.
5. Attach an output device to a digital PWM pin (3, 5, 6, 9, 10, and 11 on most Arduino boards).
6. Set the ACTUATOR_PIN value below to the digital PWM pin number you selected.
7. Set the Cayenne authentication info to match the authentication info from the Dashboard.
8. Compile and upload this sketch.
9. Once the Arduino connects to the Dashboard you can use the slider to change PWM values.
*/

#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#include <CayenneMQTTEthernet.h>

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "MQTT_USERNAME";
char password[] = "MQTT_PASSWORD";
char clientID[] = "CLIENT_ID";

#define VIRTUAL_CHANNEL 1
#define ACTUATOR_PIN 3

void setup()
{
	Serial.begin(9600);
	Cayenne.begin(username, password, clientID);
}

void loop()
{
	Cayenne.loop();
}

// This function is called when data is sent from Cayenne.
CAYENNE_IN(VIRTUAL_CHANNEL)
{
	int value = getValue.asInt(); // 0 to 255
	CAYENNE_LOG("Channel %d, pin %d, value %d", VIRTUAL_CHANNEL, ACTUATOR_PIN, value);
	// Write the value received to the PWM pin. analogWrite accepts a value from 0 to 255.
	analogWrite(ACTUATOR_PIN, value);
}

// This function is called at intervals to send data to Cayenne and keep the device online.
// Will create a temporary green widget on Channel 0, make it permanent by clicking on '+'. 
CAYENNE_OUT(0)
{
	CAYENNE_LOG("Send data for Virtual Channel 0");
	// This command writes the device's uptime in seconds to the Virtual Channel. 
	Cayenne.virtualWrite(0, millis() / 1000);
}
