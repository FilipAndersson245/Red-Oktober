#include "node.h"
Node::Node(QPoint aLocation)
{
    _maxNoOfConnectors = 1 + returnRandom(5);
    _locationOfNode = aLocation;
}


// to be implemented //
void Node::paintMember(QPainter &painter)
{

}
int Node::returnRandom(int limit)
{
    return rand() % limit;

    std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());     // provide seed

    std::uniform_int_distribution<int> uid{ 1,limit };   // help dre to generate nos from 0 to lim (lim included);
    return uid(dre);    // pass dre as an argument to uid to generate the random no

}
