#ifndef M2006_HPP
#define M2006_HPP

#include "CanManager.hpp"
#include "Pid.hpp"
#include "Motor.hpp"


class M2006 : public CanMsgHandler, public Motor
{
private:
    
    //attribute
    uint32_t canId;
    const static float RawPos2Rad;
    const static float RawRpm2Rps;
    const static float PiDiv36;    
    
    //Raw feedback
    uint16_t ecd  = 0;
    int16_t speed_rpm = 0;
    int16_t given_current  = 0;
    uint8_t temperate = 0;
    
    //updated
    float rotorPosition = 0.0;
    float rotorLastPosition = 0.0;
    

public:

    MotorControlModeType controlMode = Motor::RELAX_MODE;
    Pid pidSpeed;
    Pid pidPosition;

    float currentSet = 0.0;
    

    M2006() : CanMsgHandler() , Motor()
    {};

    void Registration(int id){
        this->CanMsgHandler::Registration(id);
        canId = id;
    };

    virtual void HandleNewMsg(can_frame msg);
    void Update();

};



#endif