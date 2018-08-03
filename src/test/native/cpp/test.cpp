#include <gtest/gtest.h>
#include "ctre/Phoenix.h"
#include <iostream>


TEST(TalonID, CheckIDSet) {
    for(int i = 0; i < 63; i++) {
        ctre::phoenix::motorcontrol::can::TalonSRX testTalon(i);

        int id = testTalon.GetDeviceID();

        ASSERT_EQ(id, i);
    }
    
    for(int i = 63; i < 140; i++) {
        ctre::phoenix::motorcontrol::can::TalonSRX testTalon(i);

        int id = testTalon.GetDeviceID();

        ASSERT_EQ(id, i & 0x3F);
    }
}
TEST(TalonError, CheckTimeoutError) {
   
    ctre::phoenix::motorcontrol::can::TalonSRX testTalon(0);
    ctre::phoenix::ErrorCode err =  testTalon.ConfigVelocityMeasurementWindow(16, 10);
    
    ASSERT_EQ(-200, (int) err);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
