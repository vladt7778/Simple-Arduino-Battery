#pragma once
#include "Arduino.h"

class Battery
{
    constexpr static ulong MAX_BATTERY_CHECK = 500;
    constexpr static uint8_t MIN_VOLTAGE_PERCENTAGE = 75;

    const uint8_t MAX_VOLTAGE;
    const uint8_t BATTERY_PIN;

    ulong m_LastUpdated = 0;

    uint8_t m_MinimumVoltage;
    uint8_t m_MinimumVoltagePercentage;
    uint8_t m_CurrentVoltage;
    uint8_t m_CurrentVoltagePercentage;

    bool m_BatteryLow = false;

    void (*m_LowBatteryHandler)();
    void (*m_NormalBatteryHandler)();

    uint8_t GetVoltageFromPercentage() const;
    uint8_t GetVoltagePercentageFromThreshold() const;

public:
    Battery(uint8_t maxVoltage, uint8_t batteryPin);

    bool Low() const;

    uint8_t GetCurrentVoltage() const;
    uint8_t GetCurrentVoltagePercentage() const;
    uint8_t GetMaxVoltage() const;
    uint8_t GetMinimumVoltage() const;
    uint8_t GetMinimumVoltagePercentage() const;

    void onLowBattery();
    void onNormalBattery();
    void SetMinimumVoltagePercentage(uint8_t thresholdPercentage);
    void SetMinimumVoltageThreshold(uint8_t thresholdVoltage);
    void SetLowBatteryHandler(void (*handler)());
    void SetNormalBatteryHandler(void (*handler)());
    void Update();
};