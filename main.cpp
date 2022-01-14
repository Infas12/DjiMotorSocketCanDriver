#include "CanManager.hpp"
#include "DjiMotorManager.hpp"
#include "M2006.hpp"
#include "M3508.hpp"

int main()
{
    M2006 testMotor;
    M2006 testMotor2;
    M3508 testMotor3;

    testMotor.Registration(0x207);
    testMotor2.Registration(0x202);
    testMotor3.Registration(0x201);

    testMotor.pidSpeed.kp = 3;
	testMotor.pidSpeed.ki = 0.2;
	testMotor.pidSpeed.kd = 0.05;
	testMotor.pidSpeed.maxOut = 10;
	testMotor.pidSpeed.maxIOut = 10;
    testMotor.controlMode = Motor::RELAX_MODE;

    testMotor2.pidSpeed.kp = 3;
	testMotor2.pidSpeed.ki = 0.2;
	testMotor2.pidSpeed.kd = 0.05;
	testMotor2.pidSpeed.maxOut = 10;
	testMotor2.pidSpeed.maxIOut = 10;
    testMotor2.controlMode = Motor::RELAX_MODE;    

    testMotor3.pidSpeed.kp = 3;
	testMotor3.pidSpeed.ki = 0.2;
	testMotor3.pidSpeed.kd = 0.05;
	testMotor3.pidSpeed.maxOut = 10;
	testMotor3.pidSpeed.maxIOut = 10;
    testMotor3.controlMode = Motor::SPD_MODE;

    CanManager::Instance()->SetPortName("can0");
    CanManager::Instance()->Init();

    while(true)
    {
        testMotor3.speedSet = 2.0f;
        testMotor3.Update();
        DjiMotorManager::Instance()->Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

}