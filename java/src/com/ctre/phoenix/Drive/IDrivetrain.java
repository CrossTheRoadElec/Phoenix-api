package com.ctre.phoenix.Drive;

public interface IDrivetrain
{
	void set(Styles.Basic mode, double forward, double turn);
	void setVoltageRampRate(double rampRate);
	void setVoltageCompensationRampRate(double rampRate);
    void configPeakPercentOutputVoltage(double forwardPercentOutput, double reversePercentOutput);
    void configNominalPercentOutputVoltage(double forwardPercentOutput, double reversePercentOutput);
}