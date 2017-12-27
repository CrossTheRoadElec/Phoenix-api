package com.ctre.phoenix.drive;

public interface IDrivetrain
{
	void set(DriveMode mode, double forward, double turn);
	void setVoltageRampRate(double rampRate);
	void setVoltageCompensationRampRate(double rampRate);
    void configPeakPercentOutputVoltage(double forwardPercentOutput, double reversePercentOutput);
    void configNominalPercentOutputVoltage(double forwardPercentOutput, double reversePercentOutput);
}