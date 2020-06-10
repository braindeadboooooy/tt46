#include "shop_information.h"
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
shop_information::shop_information()
{
    sotrudnik_count = 0;
    ciz_count = 0;
    mas_size_sotrudnik = 0;
    ciz_size = 0;
    sotrudnik_size = 0;
    mas_sotrudnik = NULL;
    mas_ciz = NULL;
    shop_name = "";
}
shop_information::shop_information(string shopname_1)
{
    sotrudnik_count = 0;
    ciz_count = 0;
    mas_size_sotrudnik = 0;
    ciz_size = 0;
    sotrudnik_size = 0;
    mas_sotrudnik = NULL;
    mas_ciz = NULL;
    shop_name = shopname_1;
}
ostream &operator<<(ostream &out, const shop_information &obj)
{

    out << "shop name: " << obj.shop_name << endl;
    out << "____________________________________________________________" << endl;
    return out;
}
istream &operator>>(istream &in, shop_information &obj)
{
    in >> obj.shop_name;
    return in;
}