#include "Battery.h"

Battery battery(9, A0);

void onLowBattery()
{
	Serial.println("The battery is low");
}

void onNormalBattery()
{
	Serial.println("The battery is running normally");
}

void setup()
{
	Serial.begin(9600);
	Serial.setTimeout(250);

	battery.SetLowBatteryHandler(onLowBattery);
	battery.SetNormalBatteryHandler(onNormalBattery);
}

void loop()
{
	battery.Update();
}