#ifndef DJIMOTORMANAGER
#define DJIMOTORMANAGER

#include "CanManager.hpp"

class DjiMotorManager
{

private:
    DjiMotorManager(){}
    uint16_t BufferGroup[2][4] = {0}; //ID range from 201 to 204
    bool NewMsgRequired[2];

public:
    static DjiMotorManager* Instance()
    {
        static DjiMotorManager instance;
        return &instance;
    };

    void Add2Buffer(int ID, uint16_t CurrentSet)
    {
        if(ID<0x205&&ID>0x200){
            BufferGroup[0][ID-0x201] = CurrentSet;
            NewMsgRequired[0] = true;
        }else if(ID<0x209&&ID>0X204){
            BufferGroup[1][ID-0x205] = CurrentSet;
            NewMsgRequired[1] = true;
        }
    };

    void Update()
    {
        for(int i = 0; i < 2; i++)
        {
            if(NewMsgRequired[i])
            {   
                can_frame frame;

                if(i==0){
                    frame.can_id = 0x200;
                    frame.can_dlc = 8;
                }else{
                    frame.can_id = 0x1FF;
                    frame.can_dlc = 8;                    
                }

                frame.data[0] = BufferGroup[i][0] >> 8;
                frame.data[1] = BufferGroup[i][0];
                frame.data[2] = BufferGroup[i][1] >> 8;
                frame.data[3] = BufferGroup[i][1];
                frame.data[4] = BufferGroup[i][2] >> 8;
                frame.data[5] = BufferGroup[i][2];
                frame.data[6] = BufferGroup[i][3] >> 8;
                frame.data[7] = BufferGroup[i][3];

                CanManager::Instance()->SendMsg(frame);
                NewMsgRequired[i] = false;
            }
        }
    };

};


#endif