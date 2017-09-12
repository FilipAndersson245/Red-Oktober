#ifndef NODECONNECT_H
#define NODECONNECT_H

class Node;

class NodeConnect
{
public:
    NodeConnect();

    bool connect(Node* target);
    bool disconnect();
    int getAmountOfConnects();
    Node *getTarget();

    bool setAmountOfConnects(int amount);
    bool setTarget(Node* target);

private:
    int _connections = 0;
    Node* _target = nullptr;

};

#endif // NODECONNECT_H
