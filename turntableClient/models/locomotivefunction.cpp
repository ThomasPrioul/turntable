#include "locomotivefunction.h"
#include "locomotive.h"

LocomotiveFunction::LocomotiveFunction(int id, bool funcVal, Locomotive* loco, QObject* parent)
        : QObject(parent)
        , m_id(id)
        , m_loco(loco)
        , m_functionValue(funcVal)
{}

void LocomotiveFunction::setFunctionValue(bool value)
{
    if (value == m_functionValue) return;
    m_functionValue = value;
    emit functionValueChanged();

    std::ostringstream output;
    output << "LF " << m_loco->id() << " " << m_id << " " << value << '\n';
    m_loco->network()->sendMessage(output.str());
}
