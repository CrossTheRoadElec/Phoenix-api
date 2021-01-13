# This Repo is No Longer Being Updated
This repo is no longer actively updated.
Source code is circa 2019.

## Phoenix-api
CTRE Phoenix Application-Level Library for Java and C++

Relevant Source Files are located in the following locations:

C++: src/main/native
Java: src/main/java


## Dependencies
FRC C++ Toolchain

Java Development Kit 8u77 (Any other version risks gradle incompatibility)

Phoenix libraries are pulled down as a maven dependency for all builds.
You will need either an internet connection OR to have installed Phoenix locally to satisfy these dependencies.

FRC NetComm library is pulled down as a dependency for athena (roboRIO) builds.  This requires an internet connection or a local copy of the corresponding WPI maven artifact.

## Building
To build, run `./gradlew build`.
This will build binaries but will not place them into a maven-style artifact.  Binaries can be found in the build/libs folder.

To publish to a maven-style repository, use `./gradlew publish`.
By default this will publish maven artifacts to {Userhome}/releases/maven/development.
Where the version of Phoenix is typically Maj.Min.Build-[classifier], these artifacts will be versioned as Maj.424242.Min.Build-[suffix]-[classifier].

## Using these artifacts in your FRC project
This repository also contains a 'Phoenix-dev.json' file that will reference locally published artifacts.
To use this file:
- Modify 'Phoenix-dev.json' to replace 'C:/Users/[Username]' with your UserHome folder.  For Windows users, you will likely only need to replace your Username in the path.
- Copy 'Phoenix-dev.json' into your project's 'vendordeps' folder.  Be sure to remove any existing Phoenix.json file from the vendordeps directory to avoid dependency conflicts.
