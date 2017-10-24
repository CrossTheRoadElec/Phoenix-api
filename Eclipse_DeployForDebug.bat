:: move the headers into the WPILIB folder for FRC applications
xcopy /Y /E ..\..\Phoenix-frc-lib\cpp\include\ctre %HOMEPATH%\wpilib\user\cpp\include\ctre

:: move the low level static lib so Robot apps use it
xcopy /Y /E .\libCTRE_Phoenix.a %HOMEPATH%\wpilib\user\cpp\lib\libCTRE_Phoenix.a