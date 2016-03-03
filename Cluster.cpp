// Gaurav Bhandari
// Cluster.cpp --- implementation of cluster.h
//

#include <string>
#include <sstream>
#include <algorithm>
#include "Cluster.h"

using namespace Clustering;

namespace Clustering
{

    LNode::LNode(const Point & newPoint, LNodePtr nextPtr):point(newPoint)
    {
        point=newPoint;
        next=nextPtr;
    }

    Clustering::Cluster::Cluster()
    {
        __size = 0;
        __points = nullptr;
    }

    Clustering::Cluster::Cluster(const Cluster & rhs):Cluster()
    {
        for (int i = 0; i < rhs.__size; i++)
            add(rhs[i]);
    }

   Cluster &Clustering::Cluster::operator=(const Cluster &rhs)
    {
        LNodePtr curr;

        if(this==&rhs)
            return *this;
        else
        {
            while (__points != nullptr) {
                curr = __points;
                __points = __points->next;
                delete curr;
                __size--;
            }

            for (int i = 0; i < rhs.__size; i++)
                add(rhs[i]);
        }

        return *this;
    }

    const Point &Cluster::operator[](unsigned int index) const
    {
        LNodePtr cursor=__points;
        for(int i=0;(i<index) && (cursor->next!=nullptr); i++)
            cursor=cursor->next;
        return cursor->point;
    }

    Clustering::Cluster::~Cluster()
    {
        if(__points!=nullptr)
        {
            LNodePtr prev=__points;
            LNodePtr curr=nullptr;
            while (prev!= nullptr)
            {
                curr=prev->next;
                delete prev;
                prev=curr;
            }
        }
    }

    int Clustering::Cluster::getSize() const
    {
        return __size;
    }

    void Clustering::Cluster::add(const Point &p)
    {
        LNodePtr insertPtr=new LNode(p, nullptr);
        LNodePtr curr=__points;
        LNodePtr prev=__points;

        if(__points==nullptr)
        {
            __points = insertPtr;
            __size++;
            return;
        }
        else if(__points->next==nullptr)
        {
            if(p<__points->point)
            {
                __points=insertPtr;
                insertPtr->next=prev;
                __size++;
                return;
            }
            else
            {
                __points->next=insertPtr;
                __size++;
                return;
            }
        }
        else
        {
            curr=curr->next;
            if(p<prev->point)
            {
                __points=insertPtr;
                insertPtr->next=prev;
                __size++;
                return;
            }
            while(curr!=nullptr)
            {
                if(p<curr->point)
                {
                    prev->next=insertPtr;
                    insertPtr->next=curr;
                    __size++;
                    return;
                }
                curr=curr->next;
                prev=prev->next;
            }
            prev->next=insertPtr;
            __size++;

        }
    }

    const Point &Clustering::Cluster::remove(const Point & p)
    {

        LNodePtr current=__points;
        LNodePtr prev=__points;

        if(__points==nullptr)
            return p;
        else if(__points->point==p)
        {
            current=__points;
            __points=__points->next;
            delete current;
            __size--;
        }
        else
        {
            current=current->next;
            while (current!= nullptr)
            {
                if (current->point == p)
                {
                    prev->next=current->next;
                    delete current;
                    __size--;
                    break;
                }
                current = current->next;
                prev = prev->next;
            }
        }
        return p;
    }

    bool Clustering::Cluster::contains(const Point & p)
    {
        for (LNodePtr Cursor = this->__points; Cursor != nullptr; Cursor = Cursor->next)
        {
            if (Cursor->point == p)
                return true;
        }
        return false;
    }

    bool operator==(const Cluster &a, const Cluster &b)
    {
        LNodePtr k1= a.__points;
        LNodePtr k2=b.__points;
        bool equal=true;
        if (a.__size != b.__size)
            equal=false;
        while(k1!=nullptr && k2!=nullptr)
        {
            if(k1->point!=k2->point)
                equal=false;
            k1=k1->next;
            k2=k2->next;
        }
        return equal;
    }

    bool operator!=(const Cluster &a, const Cluster &b)
    {
        return (!(a==b));
    }

    Cluster &Clustering::Cluster::operator+=(const Point &p)
    {
        add(p);
        return *this;
    }

    Cluster &Clustering::Cluster::operator-=(const Point & p)
    {
        remove(p);
        return *this;
    }

    const Cluster operator+(const Cluster & a, const Point & p)
    {
        Cluster b(a);
        b += p;

        return b;
    }

    const Cluster operator-(const Cluster & a, const Point & p)
    {
        Cluster b(a);
        b -= p;
        return b;
    }

    Cluster &Clustering::Cluster::operator+=(const Cluster &a)
    {
        for (int i = 0; i < a.__size; i++)
        {
            if (!contains(a[i]))
                add(a[i]);
        }
        return *this;
    }

    Cluster &Clustering::Cluster::operator-=(const Cluster &a)
    {
        for (int i = 0; i < a.__size; i++)
            if (contains(a[i]))
                remove(a[i]);
        return *this;
    }

    const Cluster operator+(const Cluster &a, const Cluster &b)
    {
        Cluster c(a);
        c += b;
        return c;
    }

    const Cluster operator-(const Cluster &a, const Cluster &b)
    {
        Cluster c(a);
        c -= b;
        return c;
    }

    std::ostream &operator<<(std::ostream &os, const Cluster &a)
    {
        LNodePtr cursor= a.__points;
        int i=0;
        for(; i < a.__size - 1; i++)
        {
            os << cursor->point<<std::endl;
            cursor = cursor->next;
        }
        os<<cursor->point;
        return os;
    }

    std::istream &operator>>(std::istream &input, Cluster &a)
    {
        std::string line, newline;

        while(!input.eof())
        {

            double d = 0.0;
            int i = 0;
            getline(input, line);
            int size = std::count(line.begin(), line.end(), ',') + 1;
            Point p(size);

            std::stringstream sIn(line);
            while (getline(sIn, newline, ','))
            {
                std::stringstream s2(newline);
                s2 >> d;
                p[i] = d;
                i++;
            }
            a.add(p);

        }
        return input;
    }

}