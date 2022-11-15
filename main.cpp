#include "CanManager.hpp"
#include "DjiMotorManager.hpp"
#include "M2006.hpp"
#include "M3508.hpp"
#include "M6020.hpp"

int main()
{
    M6020 testMotor;
    testMotor.Registration(0x208);
	
	testMotor.pidSpeed.kp = 3;
	testMotor.pidSpeed.ki = 0.2;
	testMotor.pidSpeed.kd = 0.05;
	testMotor.pidSpeed.maxOut = 10;
	testMotor.pidSpeed.maxIOut = 10;
    testMotor.controlMode = Motor::RELAX_MODE;

    CanManager::Instance()->SetPortName("can0");
    CanManager::Instance()->Init();

    while(true)
    {
        testMotor.speedSet = 2.0f;
        testMotor.Update();
        DjiMotorManager::Instance()->Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

}
