#ifndef SERVICESTATE_H
#define SERVICESTATE_H

enum class ServiceState {
    Init,
    AwaitingClient,
    ConnectedInit,
    ConnectedIdle,
    ConnectedMoving
};

#endif // SERVICESTATE_H
