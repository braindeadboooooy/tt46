#ifndef sotrudnik_information_H
#define sotrudnik_information_H
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
class sotrudnik_information
{
private:
    std::string name;
    std::string surname;
    std::string middle_name;

public:
    std::string &Getsotrudnik_name()
    {
        return name;
    }
    std::string &Getsotrudnik_surname()
    {
        return surname;
    }
    std::string &Getsotrudnik_middlename()
    {
        return middle_name;
    }
    sotrudnik_information();
    sotrudnik_information(std::string name_1, std::string surname_1, std::string middlename_1);
    friend std::ostream &operator<<(std::ostream &out, const sotrudnik_information &obj);
    friend std::istream &operator>>(std::istream &in, sotrudnik_information &obj);
};
std::ostream &operator<<(std::ostream &out, const sotrudnik_information &obj);
std::istream &operator>>(std::istream &in, sotrudnik_information &obj);
#endif
