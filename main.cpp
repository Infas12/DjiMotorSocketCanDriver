#include "CanManager.hpp"
#include "DjiMotorManager.hpp"
#include "M2006.hpp"
#include "M3508.hpp"
#include "joystick.hh"

M3508 ChassisMotor[4];
float Vy = 1.0;
float Vw = 0.0;
Joystick joystick("/dev/input/js0");

int main()
{

    for(int i = 0; i < 4; i++)
    {
        ChassisMotor[i].Registration(0x201+i);
        ChassisMotor[i].pidSpeed.kp = 3;
	    ChassisMotor[i].pidSpeed.ki = 0.2;
	    ChassisMotor[i].pidSpeed.kd = 0.05;
	    ChassisMotor[i].pidSpeed.maxOut = 10;
	    ChassisMotor[i].pidSpeed.maxIOut = 10;
        ChassisMotor[i].controlMode = Motor::SPD_MODE;
    }

    CanManager::Instance()->SetPortName("can0");
    CanManager::Instance()->Init();

    while(true)
    {

        JoystickEvent event;
        if (joystick.sample(&event))
        {
            if (!event.isAxis()) continue;

            if(event.number == 1)
            {
                Vy = 5.0 * -static_cast<double>(event.value)/32767.0;
                std::cout << Vy << std::endl;
            }

            if(event.number == 3)
            {
                Vw = 5.0 * static_cast<double>(event.value)/32767.0;
            }      
        }
        
        ChassisMotor[0].speedSet = Vy - Vw; //RightFront
        ChassisMotor[1].speedSet = Vy + Vw; //LeftFront
        ChassisMotor[2].speedSet = Vy + Vw; //LeftRear
        ChassisMotor[3].speedSet = Vy - Vw; //RightRear        

        for(int i = 0; i < 4; i++)
        {
            ChassisMotor[i].Update();
        }

        DjiMotorManager::Instance()->Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

}