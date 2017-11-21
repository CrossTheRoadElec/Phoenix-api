package com.ctre.phoenix.Drive;

public interface IDrivetrain
{
	void set(Styles.Basic mode, double forward, double turn);
	void SetVoltageRampRate(double rampRate);
	void SetVoltageCompensationRampRate(double rampRate);
    void ConfigPeakPercentOutputVoltage(double forwardVoltage, double reverseVoltage); // TODO: rename to PercentOutput
    void ConfigNominalPercentOutputVoltage(double forwardVoltage, double reverseVoltage); // TODO: rename to PercentOutput
}