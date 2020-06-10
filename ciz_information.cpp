#include "ciz_information.h"
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
ciz_information::ciz_information()
{
    ciz_name = "";
    data = 0;
}
ciz_information::ciz_information(string ciz_name_1, unsigned int data_1)
{
    ciz_name = ciz_name_1;
    data = data_1;
}
ostream &operator<<(ostream &out, const ciz_information &obj)
{
    out << "ciz_name: " << obj.ciz_name << endl;
    out << "data: " << obj.data << endl;
    out << "------------------------------------------------------------" << endl;
    return out;
}
istream &operator>>(istream &in, ciz_information &obj)
{
    in >> obj.ciz_name;
    in >> obj.data;
    return in;
}
