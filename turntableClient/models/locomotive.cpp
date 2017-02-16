#include "locomotive.h"

Locomotive::Locomotive(int id, QObject *parent) : QObject(parent), m_id(id), m_functionValues()
{
    for(int i = 0; i < 29; i++)
        m_functionValues.append(new LocomotiveFunction(i));
}
