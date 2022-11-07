# DjiMotorSocketCanDriver

A simple c++ driver for Dji M3508 and M2006.

## Platform
Linux

## Requirements
- CMake
- a USB2Can board that supports socketCan

## Usage

#### Initialization

0. Plug in your socketCan board and use `ip link show` to check its portname. Normally, it should be "can0". 

1. Specify portname and initialize `CanManager`.

```c++
CanManager::Instance()->SetPortName("can0");
CanManager::Instance()->Init();
```

2. Construct Motor object and set CanID.

```c++
M3508 testMotor; //Construct object
testMotor.Registration(0x201);  //specify Can ID
```

3. Configure Control Mode.

Here we provided 3 control modes: `SPD_MODE`, `POS_MODE` and `RELAX_MODE`. When in `RELAX_MODE` the motor will have no output torque.

Example: to use speed control mode:

```C++
testMotor.controlMode = Motor::SPD_MODE;
```

4. Configure PID Parameter.

In the motor class we provide a nested PID controller for position and speed control. (Check `M3508::Update()`). 

Configuring `pidPosition` is not required when using `SPD_MODE`, but we strongly recommand you to do so. 

```C++
//Position Control
testMotor.pidPosition.kp = ...;
testMotor.pidPosition.ki = ...;
testMotor.pidPosition.kd = ...;
testMotor.pidPosition.maxOut = ...;
testMotor.pidPosition.maxIOut = ...;

//Speed Control
testMotor.pidSpeed.kp = ...;
testMotor.pidSpeed.ki = ...;
testMotor.pidSpeed.kd = ...;
testMotor.pidSpeed.maxOut = ...;
testMotor.pidSpeed.maxIOut = ...;
```

#### Control loop

0. The control loop should be ran at about 1000 Hz.

1. To control the motor, simply set `speedSet` or `positionSet`.

```c++
testMotor.speedSet = velDesired;
```

or

```c++
testMotor.positionSet = posDesired;
```

2. Then, call `update()`.

```c++
testMotor.update();
```

See `Motor.hpp` for details.

3. Send Command

```C++
DjiMotorManager::Instance()->Update();
```


## Brief example
```c++
int main()
{
    
    CanManager::Instance()->SetPortName("can0");
    CanManager::Instance()->Init();
    
    M3508 testMotor; 
    testMotor.Registration(0x207); //set ID

    testMotor.pidSpeed.kp = 3;
    testMotor.pidSpeed.ki = 0.2;
    testMotor.pidSpeed.kd = 0.05;
    testMotor.pidSpeed.maxOut = 10;
    testMotor.pidSpeed.maxIOut = 10;
    testMotor.controlMode = Motor::SPD_MODE; //set control mode

    while(true)
    {
        testMotor.speedSet = 2.0f;
        testMotor.Update();
        DjiMotorManager::Instance()->Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}



```
