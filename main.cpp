#include "CanManager.hpp"
#include "DM4310.hpp"

int main()
{

    CanManager::Instance()->SetPortName("can0");
    CanManager::Instance()->Init();

    DM4310 testMotor;
    testMotor.Registration(518,519);

    while(true)
    {
        testMotor.positionSet = 0.0;
        std::cout << "Position: " << testMotor.positionFdb << "Vel:" << testMotor.speedFdb << std::endl;
        
        testMotor.Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

}
