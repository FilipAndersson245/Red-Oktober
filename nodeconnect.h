#ifndef NODECONNECT_H
#define NODECONNECT_H
#include "node.h"

class NodeConnect
{
public:
    NodeConnect();

    bool connect(Node* target);
    bool disconnect();
    int getAmountOfConnects();
    Node *getTarget();

private:
    int _connections = 0;
    Node* _target = nullptr;

};

#endif // NODECONNECT_H
