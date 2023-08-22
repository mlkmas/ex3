#include "HealthPoints.h"

HealthPoints::HealthPoints(int maxHP)
{
    if(maxHP>0)
    {
        this->m_maxHP=maxHP;
        this->m_currentHP=maxHP;
    }
    else
    {
        throw HealthPoints::InvalidArgument();
    }
}

HealthPoints& HealthPoints::operator+=(const int value)
{
    if((value+this->m_currentHP)>this->m_maxHP )
    {
        this->m_currentHP = this->m_maxHP;
        return (*this);
    }
    if(this->m_currentHP+value<0)
    {
        this->m_currentHP=0;
        return *this;
    }
    this->m_currentHP+=value;
    return (*this);
}
HealthPoints& HealthPoints::operator+=(const HealthPoints& Hp)
{
    *this+= Hp.m_currentHP;
    return (*this);
}

HealthPoints  operator+( const int value , HealthPoints& Hp)
{
    HealthPoints result (Hp);
    result+=value;
    return result;
}

HealthPoints  operator-(const int value, HealthPoints Hp)
{
    int num=value;
    num*=-1;
     num+Hp;
    return Hp;

}

HealthPoints HealthPoints:: operator+(const int value)
{
    return value+*this;
}
HealthPoints HealthPoints:: operator-(const int value)
{
  return (-value)+*this;
}

HealthPoints& HealthPoints::operator-=(const int value)
{
    int num=value;
    num*=-1;
    *this+=num;
    return *this;

}

HealthPoints& HealthPoints::operator-=(const HealthPoints &Hp )
{
   *this-=Hp.m_currentHP;
    return *this;
}

bool operator==(const HealthPoints Hp1, const HealthPoints& Hp2)
{
   if(Hp1.m_currentHP==Hp2.m_currentHP)
       return true;
    return false;
}

bool operator==(const HealthPoints& Hp, const int value)
{
    if(Hp.m_currentHP== value)
        return true;
    return false;
}

bool operator==(const int value ,const HealthPoints& Hp)
{
    return Hp==value;
}

bool operator!=(const int value ,const HealthPoints Hp1)
{
    return !(Hp1==value);
}
bool operator!=(const HealthPoints Hp1, const int value)
{
    return value!=Hp1.m_currentHP;
}
bool operator!=(const HealthPoints Hp1, const HealthPoints& Hp2)
{
    return !(Hp1==Hp2);
}
bool operator>(const HealthPoints Hp1, const HealthPoints& Hp2)
{
    return (Hp1.m_currentHP>Hp2.m_currentHP);
}
bool operator>(const HealthPoints Hp1, const int value)
{
    return (Hp1.m_currentHP>value);
}
bool operator>( const int value, const HealthPoints& Hp2)
{
    return value>Hp2.m_currentHP;
}

bool operator<(const HealthPoints Hp1, const HealthPoints& Hp2)
{
    return (Hp1.m_currentHP<Hp2.m_currentHP);
}

bool operator<(const HealthPoints Hp1, const int value)
{
    return Hp1.m_currentHP<value;
}
bool operator<( const int value, const HealthPoints& Hp2)
{
    return value<Hp2.m_currentHP;
}

bool operator<=(const HealthPoints Hp1, const HealthPoints& Hp2)
{
    return !(Hp1>Hp2);
}
bool operator<=(const int value, const HealthPoints& Hp2)
{
    return value+Hp2.m_currentHP;
}
bool operator<=(const HealthPoints Hp1, const int value)
{
    return (value>Hp1);
}
bool operator>=(const HealthPoints Hp1, const HealthPoints& Hp2)
{
    return !(Hp1<Hp2);
}
bool operator>=(const int value, const HealthPoints& Hp2)
{
    return value>=Hp2.m_currentHP;
}
bool operator>=(const HealthPoints Hp1, const int value)
{
    return Hp1.m_currentHP>=value;
}

 std::ostream& operator<<(std::ostream& os, const HealthPoints& Hp)
{
 os <<Hp.m_currentHP;
 os << "(" << Hp.m_maxHP << ")" ;
    return os;
}
