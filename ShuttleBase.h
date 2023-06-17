#ifndef SHUTTLEBASE_H
#define SHUTTLEBASE_H

class ShuttleBase
{
public:
    virtual void ShuttleClicked() = 0;
    virtual void ShuttleAdd() {};
    virtual void ShuttleReduce() {};
};

#endif // SHUTTLEBASE_H
