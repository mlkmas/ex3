#ifndef UNTITLED23_HEALTHPOINTS_H
#define UNTITLED23_HEALTHPOINTS_H
#include <ostream>

static const int Default_MaxHP = 100;
using namespace std;


class HealthPoints {
private:
    int m_currentHP; //the current hp value
    int m_maxHP;// the max hp value


public:

    HealthPoints(int maxHP = Default_MaxHP);
    HealthPoints(const HealthPoints&)=default;
    HealthPoints& operator=(const HealthPoints& Hp) =default;

    ~HealthPoints() = default;
    HealthPoints &operator+=(const HealthPoints &Hp);
    HealthPoints& operator+=(const int value);
    HealthPoints operator+(const int value);
    HealthPoints operator-(const int value) ;
    HealthPoints &operator-=(const HealthPoints &Hp1);
    HealthPoints &operator-=(const int value);

    friend HealthPoints operator+( const int value, HealthPoints& Hp);
    friend HealthPoints operator-( const int value , HealthPoints& Hp);

    friend bool operator==(const HealthPoints Hp1, const HealthPoints &Hp2);
    friend bool operator==(const HealthPoints& Hp, const int value);
    friend bool operator==(const int value , const HealthPoints& Hp);
    friend bool operator!=(const HealthPoints Hp1, const HealthPoints &Hp2);
    friend bool operator!=(const HealthPoints Hp1, const int value);
    friend bool operator!=(const int value, const HealthPoints &Hp2);
    friend bool operator<(const HealthPoints Hp1, const HealthPoints &Hp2);
    friend bool operator<(const HealthPoints Hp1, const int value);
    friend bool operator<( const int value, const HealthPoints& Hp2);
    friend bool operator>(const HealthPoints Hp1, const int value);
    friend bool operator>( const int value, const HealthPoints& Hp2);
    friend bool operator>(const HealthPoints Hp1, const HealthPoints &Hp2);

    friend bool operator<=(const HealthPoints Hp1, const HealthPoints &Hp2);
    friend bool operator<=(const HealthPoints Hp1, const int value);
    friend bool operator<=(const int value, const HealthPoints &Hp2);
    friend bool operator>=(const HealthPoints Hp1, const HealthPoints &Hp2);
    friend bool operator>=(const HealthPoints Hp1, const int value);
    friend bool operator>=(const int value, const HealthPoints &Hp2);

    friend std::ostream &operator<<(std::ostream &os, const HealthPoints &Hp);

    class InvalidArgument {};

};



#endif //UNTITLED23_HEALTHPOINTS_H
