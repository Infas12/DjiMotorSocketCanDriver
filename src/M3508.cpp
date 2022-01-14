#include "M3508.hpp"
#include "Math.hpp"
#include "DjiMotorManager.hpp"


const float M3508::RawPos2Rad = 0.00003994561794f;  /* 2Pi / 8191 / 3591 X 187*/
const float M3508::RawRpm2Rps = 0.005453242609f;    /* 2Pi / 60 X 187 / 3591 */
const float M3508::PiDiv19 = 0.1635972783f;      /* PI / 3591 X 187 */


void M3508::HandleNewMsg(can_frame msg)
{
    ecd = (uint16_t)(msg.data[0] << 8 | msg.data[1]);           
    speed_rpm = (uint16_t)(msg.data[2] << 8 | msg.data[3]);     
    given_current = (uint16_t)(msg.data[4] << 8 | msg.data[5]); 
    temperate = msg.data[6];  

    rotorLastPosition = rotorPosition;
    rotorPosition = ecd * RawPos2Rad - PiDiv19;

    positionFdb += Math::LoopFloatConstrain((rotorPosition - rotorLastPosition), - PiDiv19, PiDiv19);
    speedFdb = speed_rpm * RawRpm2Rps;

    //std::cout << speedFdb << std::endl;

}

void M3508::Update()
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

    //calculate current
    currentSet = pidSpeed.result;
    currentSet = Math::FloatConstrain(currentSet,-10.0,10.0);
    if(controlMode == RELAX_MODE)
    {
        currentSet = 0.0f;
    }

    //mapping current back to -1000 to 1000
    int16_t currentSend = currentSet * 1000;
    DjiMotorManager::Instance() -> Add2Buffer(canId,currentSend);
}

