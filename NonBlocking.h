#pragma once

#include "Arduino.h"

template <class ObjectType>
void NonBlockRun(void (ObjectType::*RunPtr)(), void (ObjectType::*CompletePtr)(), ObjectType *ObjPtr, bool &run, unsigned long &_LastTime, uint8_t period, int iterationLimit, int &iterationParam)
{
    if (!run)
        return;

    if (millis() - _LastTime >= period && iterationParam < iterationLimit)
    {

        (ObjPtr->*RunPtr)();
        iterationParam++;
        _LastTime = millis();
    }

    if (iterationParam == iterationLimit)
    {
        run = false;
        iterationParam = 0;
        _LastTime = 0;
        (ObjPtr->*CompletePtr)();
    }
}

template <class ObjectType>
void Once(void (ObjectType::*OncePtr)(), bool &once, ObjectType *ObjPtr)
{
    if (once)
    {
        (ObjPtr->*OncePtr)();
        once = false;
    }
}

template <class ObjectType>
void Once(void (ObjectType::*OncePtr)(bool), bool param1, bool &once, ObjectType *ObjPtr)
{
    if (once)
    {
        (ObjPtr->*OncePtr)(param1);
        once = false;
    }
}
template <class ObjectType>
void Once(void (ObjectType::*OncePtr)(bool, bool), bool param1, bool param2, bool &once, ObjectType *ObjPtr)
{
    if (once)
    {
        (ObjPtr->*OncePtr)(param1, param2);
        once = false;
    }
}

template <class ObjectType>
void Observe(void (ObjectType::*actionFunc)(), ObjectType *ObjPtr, bool &observing)
{
    if (!observing)
        return;

    (ObjPtr->*actionFunc)();
}
template <class ObjectType>
void Observe(void (ObjectType::*actionFunc)(), ObjectType *ObjPtr, bool &observing, bool &observe)
{
    // Serial.println(observe);
    if (!observe)
        return;    

    if (!observing)
        return;
    Serial.println("action func works");
    (ObjPtr->*actionFunc)();

    observe = false;
}
template <class ObjectType>
void Observe(void (ObjectType::*actionFunc)(int), int param, ObjectType *ObjPtr, bool &observing)
{
    if (!observing)
        return;

    (ObjPtr->*actionFunc)(param);
    observing = false;
}
template <class ObjectType>
void Observe(void (ObjectType::*actionFunc)(bool), bool param, ObjectType *ObjPtr, bool &observing)
{
    if (!observing)
        return;

    (ObjPtr->*actionFunc)(param);
    observing = false;
}
