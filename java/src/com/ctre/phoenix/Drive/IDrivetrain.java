package com.ctre.phoenix.Drive;

public interface IDrivetrain
{
	void set(Styles.Basic mode, float forward, float turn);
	void SetVoltageRampRate(float rampRate);
	void SetVoltageCompensationRampRate(float rampRate);
    void ConfigPeakPercentOutputVoltage(float forwardVoltage, float reverseVoltage); // TODO: rename to PercentOutput
    void ConfigNominalPercentOutputVoltage(float forwardVoltage, float reverseVoltage); // TODO: rename to PercentOutput
}