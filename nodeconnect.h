#pragma once

class Node;

class NodeConnect
{
public:

    NodeConnect();

    void connect(Node* target);

    bool addBridge();

    bool removeBridge();

    int getAmountOfConnects();

    Node *getTarget();

    void setAmountOfConnects(int amount);

    void setTarget(Node* target);

private:

    int _connections = 0;

    Node* _target = nullptr;

};
