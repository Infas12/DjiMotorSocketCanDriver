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

    static float dm_uint_to_float(uint16_t x_int, float x_min, float x_max, uint16_t bits){
        /// converts unsigned int to float, given range and number of bits ///
        /// for DM series motors ///
        float span = x_max - x_min;
        float offset = x_min;
        return ((float)x_int)*span/((float)((1<<bits)-1)) + offset;
    }

    static int dm_float_to_uint(float x, float x_min, float x_max, uint16_t bits){
        /// Converts a float to an unsigned int, given range and number of bits
        float span = x_max - x_min;
        float offset = x_min;
        return (int) ((x-offset)*((float)((1<<bits)-1))/span);
    }





};

#endif
