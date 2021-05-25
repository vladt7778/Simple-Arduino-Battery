#include "Battery.h"

uint8_t Battery::GetVoltageFromPercentage() const
{
    return MAX_VOLTAGE * m_CurrentVoltagePercentage / 100;
}

uint8_t Battery::GetVoltagePercentageFromThreshold() const
{
    return m_CurrentVoltage * 100 / MAX_VOLTAGE;
}

Battery::Battery(uint8_t maxVoltage, uint8_t batteryPin) : MAX_VOLTAGE(maxVoltage), BATTERY_PIN(batteryPin)
{
    SetMinimumVoltagePercentage(MIN_VOLTAGE_PERCENTAGE);
}

bool Battery::Low() const
{
    return m_BatteryLow;
}

uint8_t Battery::GetCurrentVoltage() const
{
    return m_CurrentVoltage;
}

uint8_t Battery::GetCurrentVoltagePercentage() const
{
    return m_CurrentVoltagePercentage;
}

uint8_t Battery::GetMaxVoltage() const
{
    return MAX_VOLTAGE;
}

uint8_t Battery::GetMinimumVoltage() const
{
    return m_MinimumVoltage;
}

uint8_t Battery::GetMinimumVoltagePercentage() const
{
    return m_MinimumVoltagePercentage;
}

void Battery::onLowBattery()
{
    if (*m_LowBatteryHandler)
    {
        m_LowBatteryHandler();
    }
}

void Battery::onNormalBattery()
{
    if (*m_NormalBatteryHandler)
    {
        m_NormalBatteryHandler();
    }
}

void Battery::SetMinimumVoltagePercentage(uint8_t thresholdPercentage)
{
    m_MinimumVoltagePercentage = thresholdPercentage;
    m_MinimumVoltage = GetVoltageFromPercentage();
}

void Battery::SetMinimumVoltageThreshold(uint8_t thresholdVoltage)
{
    m_MinimumVoltage = thresholdVoltage;
    m_MinimumVoltagePercentage = GetVoltagePercentageFromThreshold();
}

void Battery::SetLowBatteryHandler(void (*handler)())
{
    m_LowBatteryHandler = handler;
}

void Battery::SetNormalBatteryHandler(void (*handler)())
{
    m_NormalBatteryHandler = handler;
}

void Battery::Update()
{
    if (millis() - m_LastUpdated > MAX_BATTERY_CHECK)
    {
        m_CurrentVoltagePercentage = (uint8_t)map(analogRead(BATTERY_PIN), 0, 1023, 0, 100);
        m_CurrentVoltage = GetVoltageFromPercentage();

        if (m_CurrentVoltagePercentage < m_MinimumVoltagePercentage)
        {
            if (!m_BatteryLow)
            {
                m_BatteryLow = true;
                onLowBattery();
            }
        }
        else
        {
            if (m_BatteryLow)
            {
                m_BatteryLow = false;
                onNormalBattery();
            }
        }
        m_LastUpdated = millis();
    }
}