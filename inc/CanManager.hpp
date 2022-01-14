#ifndef CAN_MANAGER_HPP
#define CAN_MANAGER_HPP

#include <net/if.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <iostream>
#include <signal.h>
#include <cstring>
#include <string>
#include <chrono>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <pthread.h>
#include <map>


class CanMsgHandler
{
    private:
        int m_id;
    public:
        CanMsgHandler(){};
        void Registration(int id); 
        virtual void HandleNewMsg(can_frame msg) = 0 ;
};

class CanManager
{
private:

    CanManager(){};
    ~CanManager(){};
    std::string m_PortName;
    bool m_IsRunning;

public:
    
    int SocketFD;
    std::mutex SocketMtx;
    bool TxRequestFlag;
    pthread_t RxThreadID{};
    std::map<int,CanMsgHandler*> HandlerMap;

    static CanManager* Instance()
    {
        static CanManager instance;
        return &instance;
    };
    
    void SetPortName(const std::string PortName){m_PortName = PortName;};
    void Init();
    bool IsRunning(){return m_IsRunning;}
    
    //Transmit
    void SendMsg(can_frame msg);

    //Receive, with a single thread.
    void StartRxThread();
    void EndRxThread();
    static void* RxThread(void *arg);

};
//written like sh*t





#endif