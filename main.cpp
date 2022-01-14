#include "CanManager.hpp"
#include "DjiMotorManager.hpp"
#include "M2006.hpp"


int main()
{
    M2006 testMotor;
    M2006 testMotor2;

    testMotor.Registration(0x203);
    testMotor2.Registration(0x202);

    testMotor.pidSpeed.kp = 3;
	testMotor.pidSpeed.ki = 0.2;
	testMotor.pidSpeed.kd = 0.05;
	testMotor.pidSpeed.maxOut = 10;
	testMotor.pidSpeed.maxIOut = 10;
    testMotor.controlMode = M2006::SPD_MODE;

    testMotor2.pidSpeed.kp = 3;
	testMotor2.pidSpeed.ki = 0.2;
	testMotor2.pidSpeed.kd = 0.05;
	testMotor2.pidSpeed.maxOut = 10;
	testMotor2.pidSpeed.maxIOut = 10;
    testMotor2.controlMode = M2006::SPD_MODE;    

    CanManager::Instance()->SetPortName("can0");
    CanManager::Instance()->Init();

    while(true)
    {
        testMotor.speedSet = 1.0f;
        testMotor2.speedSet = 2.0f;
        testMotor.Update();
        testMotor2.Update();
        DjiMotorManager::Instance()->Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

}