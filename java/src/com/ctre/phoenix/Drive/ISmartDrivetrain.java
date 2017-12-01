package com.ctre.phoenix.Drive;

public interface ISmartDrivetrain extends IDrivetrain
{
	void set(Styles.Smart mode, double forward, double turn);

    void setCurrentLimit(int currentLimitAmps, int timeoutMs);
    double getDistance();
    double getVelocity();

    double getEncoderHeading();
    void setPosition(double position);
}