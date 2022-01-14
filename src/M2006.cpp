#include "M2006.hpp"
#include "Math.hpp"
#include "DjiMotorManager.hpp"


const float M2006::RawPos2Rad =  0.0000212970875893596f;  /* 2Pi / 8191 / 36 */
const float M2006::RawRpm2Rps =  0.002908882037037037f;    /* 2Pi / 60 / 36 */
const float M2006::PiDiv36    =  0.0872664826f;      /* PI / 36 */


void M2006::HandleNewMsg(can_frame msg)
{
    ecd = (uint16_t)(msg.data[0] << 8 | msg.data[1]);           
    speed_rpm = (uint16_t)(msg.data[2] << 8 | msg.data[3]);     
    given_current = (uint16_t)(msg.data[4] << 8 | msg.data[5]); 
    temperate = msg.data[6];  

    rotorLastPosition = rotorPosition;
    rotorPosition = ecd * RawPos2Rad - PiDiv36;

    positionFdb += Math::LoopFloatConstrain((rotorPosition - rotorLastPosition), - PiDiv36, PiDiv36);
    speedFdb = speed_rpm * RawRpm2Rps;

    //std::cout << (int)msg.can_dlc << std::endl;
    //std::cout << "ID:" << canId << " pos:" << positionFdb << std::endl;
}

void M2006::Update()
{
    if (controlMode == POS_MODE)
    {
        pidPosition.ref = positionSet;
        pidPosition.fdb = positionFdb;

        pidPosition.UpdateResult();

        speedSet = pidPosition.result;
    }

    pidSpeed.ref = speedSet;
    pidSpeed.fdb = speedFdb;

    pidSpeed.UpdateResult();

    currentSet = pidSpeed.result;
    currentSet = Math::FloatConstrain(currentSet,-10.0,10.0);
    
    uint16_t currentSend = currentSet * 1000;
    if(controlMode == RELAX_MODE)
    {
        currentSet = 0.0f;
    }

    DjiMotorManager::Instance() -> Add2Buffer(canId,currentSend);

}
