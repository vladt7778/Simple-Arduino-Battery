//#define DBG_MODE

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

	batteryPack.SetLowBatteryHandler(onLowBattery);
	batteryPack.SetNormalBatteryHandler(onNormalBattery);
}

void loop()
{
	batteryPack.Update();
}