:: move the headers into the WPILIB folder for FRC applications
xcopy /Y /E ..\..\CTRLib\cpp\include\ctrlib %HOMEPATH%\wpilib\user\cpp\include\ctrlib

:: move the low level static lib so Robot apps use it
xcopy /Y /E .\libCTRLib.a %HOMEPATH%\wpilib\user\cpp\lib\libCTRLib.a