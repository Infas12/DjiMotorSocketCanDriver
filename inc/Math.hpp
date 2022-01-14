#ifndef MATH_HPP
#define MATH_HPP

#include <stdint.h>

class Math
{
public:
    static const float Pi;
    static const float PiX2;

    static float LoopFloatConstrain(float input, float minValue, float maxValue)
    {
        if (maxValue < minValue)
        {
            return input;
        }

        if (input > maxValue)
        {
            float len = maxValue - minValue;
            while (input > maxValue)
            {
                input -= len;
            }
        }
        else if (input < minValue)
        {
            float len = maxValue - minValue;
            while (input < minValue)
            {
                input += len;
            }
        }
        return input;
    }

    static float LimitMax(float _input, float _max)
    {
        if(_input > _max)
        {
            return _max;
        }
        else if(_input < -_max)
        {
            return -_max;
        }
        return _input;
    }

    static float FloatConstrain(float Input, float minValue, float maxValue)
    {
        if (maxValue < minValue)
        {
            return Input;
        }

        if (Input > maxValue)
        {
            Input = maxValue;
        }
        else if (Input < minValue)
        {
            Input = minValue;
        }
        return Input;
    }

    static uint32_t ConvertToFixed(float _inNum, float _inMin, float _inPrecision)
    {
        return (uint32_t)((_inNum - _inMin) / _inPrecision);
    }

    static float ConvertFromFixed(uint32_t _inNum, float _inMin, float _inPrecision)
    {
        return (float)(_inNum) * _inPrecision + _inMin;
    }
};

#endif
