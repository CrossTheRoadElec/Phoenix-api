package com.ctre.phoenix.Drive;

public interface ISmartDrivetrain extends IDrivetrain
{
	void set(Styles.Smart mode, float forward, float turn);

    void SetCurrentLimit(int currentLimitAmps, int timeoutMs);
    float GetDistance();
    float GetVelocity();

    float GetEncoderHeading();
    void SetPosition(float position);
}