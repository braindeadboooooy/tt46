#include "sotrudnik_information.h"
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
sotrudnik_information::sotrudnik_information()
{
    name = "";
    surname = "";
    middle_name = "";
}
sotrudnik_information::sotrudnik_information(string name_1, string surname_1, string middlename_1)
{
    name = name_1;
    surname = surname_1;
    middle_name = middlename_1;
}
ostream &operator<<(ostream &out, const sotrudnik_information &obj)
{
    out << "name: " << obj.name << endl;
    out << "surname: " << obj.surname << endl;
    out << "middle name: " << obj.middle_name << endl;
    out << "------------------------------------------------------------" << endl;
    return out;
}
istream &operator>>(istream &in, sotrudnik_information &obj)
{
    in >> obj.name;
    in >> obj.surname;
    in >> obj.middle_name;
    return in;
}