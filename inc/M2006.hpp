#ifndef M2006_HPP
#define M2006_HPP

#include "CanManager.hpp"
#include "Pid.hpp"



class M2006 : public CanMsgHandler
{
public:
    enum MotorControlModeType
    {
        RELAX_MODE,
        SPD_MODE,
        POS_MODE,        
    };

private:
    
    //attribute
    uint32_t canId;
    const static float RawPos2Rad;
    const static float RawRpm2Rps;
    const static float PiDiv36;    
    
    //Raw info
    uint16_t ecd  = 0;
    int16_t speed_rpm = 0;
    int16_t given_current  = 0;
    uint8_t temperate = 0;
    
    //updated
    float rotorPosition = 0.0;
    float rotorLastPosition = 0.0;
    
    //rotor info
    float positionFdb = 0.0;
    float speedFdb = 0.0;
    
    //control
    

public:
    MotorControlModeType controlMode = RELAX_MODE;
    Pid pidSpeed;
    Pid pidPosition;
    float speedSet = 0.0;
    float positionSet = 0.0;
    float currentSet = 0.0;
    

public:

    M2006() : CanMsgHandler()
    {};

    void Registration(int id){
        this->CanMsgHandler::Registration(id);
        canId = id;
    };

    virtual void HandleNewMsg(can_frame msg);
    void Update();

};



#endif