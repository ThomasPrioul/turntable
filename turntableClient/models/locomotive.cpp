#include "locomotive.h"

Locomotive::Locomotive(int id, DccClientNetwork *net, QObject *parent) : QObject(parent), m_direction(false), m_id(id), m_functionValues(), m_network(net), m_speed(0)
{
    for(int i = 0; i < 29; i++)
        m_functionValues.append(new LocomotiveFunction(i, false, this));
}
