#ifndef ciz_information_H
#define ciz_information_H
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
class ciz_information
{
private:
    std::string ciz_name;
    unsigned int data;

public:
    std::string &Getciz_name()
    {
        return ciz_name;
    }
    unsigned int Getciz_data()
    {
        return data;
    }
    void setciz_data(unsigned int tmp_data)
    {
        data = tmp_data;
    }
    ciz_information(std::string ciz_name_1, unsigned int data_1);
    ciz_information();
    friend std::ostream &operator<<(std::ostream &out, const ciz_information &obj);
    friend std::istream &operator>>(std::istream &in, ciz_information &obj);
};
std::ostream &operator<<(std::ostream &out, const ciz_information &obj);
std::istream &operator>>(std::istream &in, ciz_information &obj);
#endif
