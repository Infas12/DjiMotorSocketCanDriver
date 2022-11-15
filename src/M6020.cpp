#include "M6020.hpp"
#include "Math.hpp"
#include "DjiMotorManager.hpp"

const float M6020::RawPos2Rad = 0.0007670840321f;
const float M6020::RawRpm2Rps = 0.1047197551f;


void M6020::HandleNewMsg(can_frame msg)
{
    ecd = (uint16_t)(msg.data[0] << 8 | msg.data[1]);           
    speed_rpm = (uint16_t)(msg.data[2] << 8 | msg.data[3]);     
    given_current = (uint16_t)(msg.data[4] << 8 | msg.data[5]); 
    temperate = msg.data[6];  

    positionFdb = Math::LoopFloatConstrain((float)(ecd - offset) * RawPos2Rad,- Math::Pi, Math::Pi);

    speedFdb = speed_rpm * RawRpm2Rps;

}

void M6020::Update()
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
    uint16_t currentSend = currentSet * 1000;
    DjiMotorManager::Instance() -> Add2Buffer(canId,currentSend);
}

