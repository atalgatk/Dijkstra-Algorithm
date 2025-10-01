
#include "BetterPriorityQueue.h"

using namespace std;

//checks if the queue contains the given DNode
bool BetterPriorityQueue::Contains(DNode dn)
{
    if (dn.node == nullptr)
    {
        return false;
    }

    for (DNode d : c)
    {
        if (d == dn)
        {
            return true;
        }
    }
    return false;
}

//updates the queue with the given dn
bool BetterPriorityQueue::Update(DNode dn)
{
    GraphNode gn1;
    GraphNode gn2;
    vector<DNode> vec;
    size_t vecSize = c.size();
    bool isChanged = false;

    if (Contains(dn))
    {
        gn1 = *dn.node;
        for (size_t i = 0; i < vecSize; i++)
        {
            vec.push_back(this->top());
            this->pop();
        }

        for (size_t i = 0; i < vec.size(); i++)
        {
            gn2 = *vec.at(i).node;

            if ((gn2.key == gn1.key) && (vec.at(i).pri > dn.pri))
            {
                vec.at(i).pri = dn.pri;

                isChanged = true;
            }

            this->push(vec.at(i));
        }
    }
    return isChanged;
}


string BetterPriorityQueue::ToString()
{
    DNode gn;
    string st = "[";
    for (size_t i = 0; i < c.size(); i++)
    {
        gn = c.at(i);
        if (i == c.size() - 1)
        {
            st += DnodeToString(gn) + "]";
        }
        else
        {
            st += DnodeToString(gn) + ", ";
        }
    }
    return st;
}

string BetterPriorityQueue::DnodeToString(DNode dn)
{
    GraphNode gn = *dn.node;
    string st = "(" + to_string(gn.key) + ", pri: " + to_string(dn.pri) + ")";
    return st;
}