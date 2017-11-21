package com.ctre.phoenix.Drive;

public interface ISmartDrivetrain extends IDrivetrain
{
	void set(Styles.Smart mode, double forward, double turn);

    void SetCurrentLimit(int currentLimitAmps, int timeoutMs);
    double GetDistance();
    double GetVelocity();

    double GetEncoderHeading();
    void SetPosition(double position);
}