#ifndef M6020_HPP
#define M6020_HPP

#include "CanManager.hpp"
#include "Pid.hpp"
#include "Motor.hpp"

class M6020 : public CanMsgHandler, public Motor
{
private:
    
    //attribute
    uint32_t canId;

    //Raw feedback
    uint16_t ecd  = 0;
    uint16_t offset = 0;
    int16_t speed_rpm = 0;
    int16_t given_current  = 0;
    uint8_t temperate = 0;
    
    //updated
    const static float RawPos2Rad;  /* 2Pi / 8191 */
    const static float RawRpm2Rps;  /* 2Pi / 60 */


public:

    MotorControlModeType controlMode = Motor::RELAX_MODE;
    Pid pidSpeed;
    Pid pidPosition;

    float currentSet = 0.0;
    

public:

    M6020() : CanMsgHandler() , Motor()
    {};

    void Registration(int id){
        this->CanMsgHandler::Registration(id);
        canId = id;
    };

    virtual void HandleNewMsg(can_frame msg);

    void Update();

};



#endif