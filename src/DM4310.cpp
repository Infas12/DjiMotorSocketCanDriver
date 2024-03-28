#include "DM4310.hpp"
#include "Math.hpp"


const float DM4310::P_MIN = -12.5f;
const float DM4310::P_MAX = 12.5f;
const float DM4310::V_MIN = -45.0f;
const float DM4310::V_MAX = 45.0f;
const float DM4310::T_MIN = -18.0f;
const float DM4310::T_MAX = 18.0f;

const float DM4310::KP_MIN = 0.0f;
const float DM4310::KP_MAX = 500.0f;
const float DM4310::KD_MIN = 0.0f;
const float DM4310::KD_MAX = 5.0f;



void DM4310::HandleNewMsg(can_frame msg)
{
    uint16_t p_int = (uint16_t)(msg.data[1] << 8 | msg.data[2]);
    uint16_t v_int = (uint16_t)(msg.data[3] << 4 | msg.data[4] >> 4);
    uint16_t tau_int = (uint16_t)((msg.data[4] & 0xF) << 8 | msg.data[5]);
    positionFdb = Math::dm_float_to_uint(p_int,P_MIN,P_MAX,16);
    speedFdb = Math::dm_float_to_uint(v_int,V_MIN,V_MAX,12);
    torqueFdb = Math::dm_float_to_uint(tau_int,T_MIN,T_MAX,12);
}

void DM4310::Update()
{
    // apply constraints
    positionSet = Math::FloatConstrain(positionSet,P_MIN,P_MAX);
    speedSet = Math::FloatConstrain(speedSet,V_MIN,V_MAX); 
    tauff = Math::FloatConstrain(tauff,T_MIN,T_MAX);
    kp = Math::FloatConstrain(kp,KP_MIN,KP_MAX);
    kd = Math::FloatConstrain(kd,KD_MIN,KD_MAX);

    if(controlMode!=Motor::POS_MODE){ //using POS_MODE as MIT mode, if not in POS_MODE then do nothing.
        tauff = 0.0;
        kp = 0.0;
        kd = 0.0;
    }

    uint16_t p_int = Math::dm_float_to_uint(positionSet,P_MIN,P_MAX,16);
    uint16_t v_int = Math::dm_float_to_uint(speedSet,V_MIN,V_MAX,12);
    uint16_t tau_int = Math::dm_float_to_uint(tauff,T_MIN,T_MAX,12);
    uint16_t kp_int = Math::dm_float_to_uint(kp,KP_MIN,KP_MAX,12);
    uint16_t kd_int = Math::dm_float_to_uint(kd,KD_MIN,KD_MAX,12);

    can_frame frame;
    frame.can_id = cmdId;
    frame.can_dlc = 8;
    frame.data[0] = (uint8_t)(p_int >> 8);
    frame.data[1] = (uint8_t)(p_int);
    frame.data[2] = (uint8_t)(v_int >> 4);
    frame.data[3] = (uint8_t)((v_int & 0xF) << 4 | (kp_int >> 8));
    frame.data[4] = (uint8_t)(kp_int);
    frame.data[5] = (uint8_t)(kd_int >> 4);
    frame.data[6] = (uint8_t)((kd_int & 0xF) << 4 | (tau_int >> 8));
    frame.data[7] = (uint8_t)(tau_int);


    // CanManager::Instance()->SendMsg(frame);

}


