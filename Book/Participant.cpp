#include "Participant.h"

Participant::Participant():
    _id(0),
    _status(Participant::Status::INVALID)
{
}

Participant::Participant(const UniqueID& id):
    _id(id)
{
}

Participant::~Participant()
{
}

Participant::Participant(const Participant& rhs)
{
    _id      = rhs._id;
    _status  = rhs._status;
    _balance = rhs._balance;
    _buyEscrow  = rhs._buyEscrow;
    _sellEscrow  = rhs._sellEscrow;
    _name    = rhs._name;    
}

Participant& Participant::operator=(const Participant& rhs)
{
    _id      = rhs._id;
    _status  = rhs._status;
    _balance = rhs._balance;
    _buyEscrow  = rhs._buyEscrow;
    _sellEscrow  = rhs._sellEscrow;
    _name    = rhs._name;
    
    return *this;
}


const UniqueID& Participant::GetID() const
{
    return _id;
}

const Participant::Status& Participant::GetStatus() const
{
    return _status;
}

const unsigned int& Participant::GetBalance() const
{
    return _balance;
}


const std::string& Participant::GetName() const
{
    return _name;
}

Participant& Participant::SetStatus(const Status& status)
{
    _status = status;
    return *this;
}

Participant& Participant::SetBalance(const unsigned int& balance)
{
    _balance = balance;
    return *this;
}

Participant& Participant::SetName(const std::string& name)
{
    _name = name;
    return *this;
}
