#include "turnouts.h"

Turnouts::Turnouts(int id, DccClientNetwork *net, QObject *parent) : QObject(parent),  m_id(id),  m_network(net)
{
}
