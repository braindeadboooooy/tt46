#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "ciz_information.h"
#include "sotrudnik_information.h"
#include "shop_information.h"
#include "help.h"
using namespace std;
int main(int argc, char *argv[])
{
    string shopname_adding;
    string name_adding;
    string surname_adding;
    string middlename_adding;
    string ciz_name_adding;
    unsigned int ciz_data_adding;

    string surname_search;
    string name_search;
    string middlename_search;
    string shopname_search;

    unsigned int ciz_data;
    unsigned int data_srok;
    int size_ciz;
    int size_sotrudnik;
    int count_sotr;
    int count_ciz;
    shop_information *mas_shop;
    string file_name;
    ifstream rf;
    int choice;
    string poisk_shop_name;
    string answer;
    help hlpob;
    if (argc >= 2)
    {
        file_name = string(argv[1]);
        rf.open(argv[1], ios::binary | ios::in);
    }
    else
    {
        cout << "Введите имя файла\n";
        cin >> file_name;
        rf.open(file_name, ios::binary | ios::in);
    }
    if (!rf)
    {
        cout << "Cannot open file!" << endl;
        return 1;
    }
    int size_shop = 1;
    int count_shop = 0;
    rf.read((char *)&size_shop, sizeof(size_shop));
    rf.read((char *)&count_shop, sizeof(count_shop));
    if (!rf.gcount())
    {
        size_shop = 1;
    }
    mas_shop = new shop_information[size_shop];
    for (int i = 0; i < count_shop; i++)
    {
        size_t size1;
        rf.read((char *)&size1, sizeof(size1));
        mas_shop[i].Getshop_name().resize(size1);
        rf.read((char *)(mas_shop[i].Getshop_name().c_str()), size1);

        sotrudnik_information **mas_sotrudnik = mas_shop[i].Getmas_sotrudnik();
        ciz_information **mas_ciz = mas_shop[i].Getmas_ciz();

        rf.read((char *)&size_sotrudnik, sizeof(size_sotrudnik));
        mas_shop[i].setsotrudnik_size(size_sotrudnik);

        rf.read((char *)&size_ciz, sizeof(size_ciz));
        mas_shop[i].setciz_size(size_ciz);

        rf.read((char *)&count_sotr, sizeof(count_sotr));
        mas_shop[i].setsotrudnik_count(count_sotr);

        rf.read((char *)&count_ciz, sizeof(count_ciz));
        mas_shop[i].setciz_count(count_ciz);

        if (size_sotrudnik != 0)
        {
            *mas_sotrudnik = new sotrudnik_information[size_sotrudnik];
        }
        if (size_ciz != 0)
        {
            *mas_ciz = new ciz_information[size_ciz];
        }
        for (int j = 0; j < count_sotr; j++)
        {
            size_t size2;
            rf.read((char *)&size2, sizeof(size2));
            (*mas_sotrudnik)[j].Getsotrudnik_name().resize(size2);
            rf.read((char *)((*mas_sotrudnik)[j].Getsotrudnik_name().c_str()), size2);
            size_t size3;
            rf.read((char *)&size3, sizeof(size3));
            (*mas_sotrudnik)[j].Getsotrudnik_surname().resize(size3);
            rf.read((char *)((*mas_sotrudnik)[j].Getsotrudnik_surname().c_str()), size3);
            size_t size4;
            rf.read((char *)&size4, sizeof(size4));
            (*mas_sotrudnik)[j].Getsotrudnik_middlename().resize(size4);
            rf.read((char *)((*mas_sotrudnik)[j].Getsotrudnik_middlename().c_str()), size4);
        }
        for (int k = 0; k < count_ciz; k++)
        {
            rf.read((char *)&ciz_data, sizeof(ciz_data));
            (*mas_ciz)[k].setciz_data(ciz_data);
            size_t size5;
            rf.read((char *)&size5, sizeof(size5));
            (*mas_ciz)[k].Getciz_name().resize(size5);
            rf.read((char *)((*mas_ciz)[k].Getciz_name().c_str()), size5);
        }
    }

    rf.close();
    for (;;)
    {
        hlpob.showmenu();
        do
        {
            cin >> choice;
        } while (!hlpob.isvalid(choice));
        if (choice == MAX_MENU_NUMBER)
            break;
        cout << endl;
        switch (choice)
        {
        case 1:
        {
            int flag_name = 0;
            cout << "Введите имя цеха" << endl;
            cin >> poisk_shop_name;
            for (int i = 0; i < count_shop; i++)
            {
                if (poisk_shop_name == mas_shop[i].Getshop_name())
                {
                    cout << "Введите имя сотрудника" << endl;
                    cin >> name_adding;
                    cout << "Введите фамилию сотрудника" << endl;
                    cin >> surname_adding;
                    cout << "Введите отчество сотрудника" << endl;
                    cin >> middlename_adding;
                    sotrudnik_information a(name_adding, surname_adding, middlename_adding);
                    flag_name = 1;
                    sotrudnik_information **mas_sotrudnik = mas_shop[i].Getmas_sotrudnik();
                    if (*mas_sotrudnik == NULL)
                    {
                        *mas_sotrudnik = new sotrudnik_information[5];
                        mas_shop[i].setmas_size_sotrudnik(5);
                        mas_shop[i].setsotrudnik_size(5);
                    }
                    if (mas_shop[i].Getmas_size_sotrudnik() <= mas_shop[i].Getsotrudnik_count())
                    {
                        sotrudnik_information *new_mas_sotrudnik = new sotrudnik_information[2 * size_sotrudnik];
                        copy_n(*mas_sotrudnik, size_sotrudnik, new_mas_sotrudnik);
                        delete[] * mas_sotrudnik;
                        *mas_sotrudnik = new_mas_sotrudnik;
                        size_sotrudnik *= 2;
                    }
                    count_sotr = mas_shop[i].Getsotrudnik_count();
                    (*mas_sotrudnik)[count_sotr++] = a;
                    mas_shop[i].setsotrudnik_count(count_sotr);
                    break;
                }
            }
            if (flag_name == 0)
            {
                cout << "Введенного цеха не существует" << endl;
            }
        }
        break;
        case 2:
        {
            for (int i = 0; i < count_shop; ++i)
            {
                cout << "Shop #" << i + 1 << endl;
                cout << mas_shop[i] << endl;
                sotrudnik_information **mas_sotrudnik = mas_shop[i].Getmas_sotrudnik();
                if (*mas_sotrudnik != NULL)
                {
                    count_sotr = mas_shop[i].Getsotrudnik_count();
                    for (int j = 0; j < count_sotr; j++)
                    {
                        cout << "Sotrudnik: " << j + 1 << endl;
                        cout << (*mas_sotrudnik)[j] << endl;
                    }
                }
            }
        }
        break;
        case 3:
        {
            int flag_name = 0;
            cout << "Введите имя цеха" << endl;
            cin >> poisk_shop_name;
            for (int i = 0; i < count_shop; i++)
            {
                if (poisk_shop_name == mas_shop[i].Getshop_name())
                {
                    cout << "Введите  название СИЗ" << endl;
                    cin >> ciz_name_adding;
                    cout << "Введите  срок ношения" << endl;
                    cin >> ciz_data_adding;
                    ciz_information c(ciz_name_adding, ciz_data_adding);
                    flag_name = 1;
                    ciz_information **mas_ciz = mas_shop[i].Getmas_ciz();
                    if (*mas_ciz == NULL)
                    {
                        *mas_ciz = new ciz_information[5];
                        mas_shop[i].setciz_size(5);
                        mas_shop[i].setmas_size_ciz(5);
                    }
                    if (mas_shop[i].Getmas_size_ciz() <= mas_shop[i].Getciz_count())
                    {
                        ciz_information *new_mas_ciz = new ciz_information[2 * size_ciz];
                        copy_n(*mas_ciz, size_ciz, new_mas_ciz);
                        delete[] * mas_ciz;
                        *mas_ciz = new_mas_ciz;
                        size_ciz *= 2;
                    }
                    count_ciz = mas_shop[i].Getciz_count();
                    (*mas_ciz)[count_ciz++] = c;
                    mas_shop[i].setciz_count(count_ciz);
                }
            }
            if (flag_name == 0)
            {
                cout << "Введенного цеха не существует" << endl;
            }
        }
        break;
        case 4:
        {
            for (int i = 0; i < count_shop; i++)
            {
                cout << "Shop #" << i + 1 << endl;
                cout << mas_shop[i] << endl;
                ciz_information **mas_ciz = mas_shop[i].Getmas_ciz();
                if (*mas_ciz != NULL)
                {
                    count_ciz = mas_shop[i].Getciz_count();
                    for (int k = 0; k < count_ciz; ++k)
                    {
                        cout << "СИЗ:" << k + 1 << endl;
                        cout << (*mas_ciz)[k] << endl;
                    }
                }
            }
        }
        break;
        case 5:
        {
            cout << "Введите название цеха" << endl;
            cin >> shopname_adding;
            shop_information b(shopname_adding);
            if (size_shop <= count_shop)
            {
                shop_information *new_mas_shop = new shop_information[2 * size_shop];
                copy_n(mas_shop, size_shop, new_mas_shop);
                delete[] mas_shop;
                mas_shop = new_mas_shop;
                size_shop *= 2;
            }
            mas_shop[count_shop++] = b;
        }
        break;
        case 6:
        {
            for (int i = 0; i < count_shop; ++i)
            {
                cout << "Shop #" << i + 1 << endl;
                cout << mas_shop[i] << endl;
                ciz_information **mas_ciz = mas_shop[i].Getmas_ciz();
                if (*mas_ciz != NULL)
                {
                    count_ciz = mas_shop[i].Getciz_count();
                    for (int k = 0; k < count_ciz; ++k)
                    {
                        cout << "СИЗ:" << k + 1 << endl;
                        cout << (*mas_ciz)[k] << endl;
                    }
                }
            }
        }
        break;
        case 7:
        {
            cout << "Введите имя цеха: " << endl;
            cin >> shopname_search;
            int check = 0;
            int check2 = 0;
            for (int i = 0; i < count_shop; ++i)
            {
                if (shopname_search == mas_shop[i].Getshop_name())
                {
                    sotrudnik_information **mas_sotrudnik = mas_shop[i].Getmas_sotrudnik();
                    count_sotr = mas_shop[i].Getsotrudnik_count();
                    check2 = 1;
                    if (count_sotr == 0)
                    {
                        cout << "Цех пуст!" << endl;
                        break;
                    }
                    else
                    {
                        cout << "Введите имя сотрудника: " << endl;
                        cin >> name_search;
                        cout << "Введите фамилию сотрудника: " << endl;
                        cin >> surname_search;
                        cout << "Введите отчество сотрудника: " << endl;
                        cin >> middlename_search;
                        for (int j = 0; j < count_sotr; ++j)
                        {
                            if ((surname_search == (*mas_sotrudnik)[j].Getsotrudnik_surname()) && (name_search == (*mas_sotrudnik)[j].Getsotrudnik_name()) && (middlename_search == (*mas_sotrudnik)[j].Getsotrudnik_middlename()))
                            {
                                for (int k = j; k < count_sotr - 1; ++k)
                                {
                                    (*mas_sotrudnik)[k].Getsotrudnik_surname() = (*mas_sotrudnik)[k + 1].Getsotrudnik_surname();
                                    (*mas_sotrudnik)[k].Getsotrudnik_name() = (*mas_sotrudnik)[k + 1].Getsotrudnik_name();
                                    (*mas_sotrudnik)[k].Getsotrudnik_middlename() = (*mas_sotrudnik)[k + 1].Getsotrudnik_middlename();
                                }
                                count_sotr = count_sotr - 1;
                                mas_shop[i].setsotrudnik_count(count_sotr);
                                check = check + 1;
                            }
                        }
                        if (check == 0)
                        {
                            cout << "Сотрудник не найден!" << endl;
                            break;
                        }
                    }
                }
            }
            if (check2 == 0)
            {
                cout << "Цех не найден!" << endl;
            }
            break;
        }
        case 8:
        {
            cout << "Введите для кого рассчитать" << endl;
            cout << "1 - если для цеха, 2- для сотрудника, 3 - для предприятия" << endl;
            cin >> answer;
            if (answer == "1")
            {
                int flag_name_2 = 0;
                cout << "Введите название цеха" << endl;
                cin >> poisk_shop_name;
                cout << "Введите на какой срок рассчитать кол-во СИЗов" << endl;
                cin >> data_srok;
                int count = 0;
                int count_1 = 0;
                int count_12 = 0;
                int count_13 = 0;
                for (int i = 0; i < count_shop; ++i)
                {
                    if (poisk_shop_name == mas_shop[i].Getshop_name())
                    {
                        flag_name_2 = 1;
                        sotrudnik_information **mas_sotrudnik = mas_shop[i].Getmas_sotrudnik();
                        if (*mas_sotrudnik != NULL)
                        {
                            count_sotr = mas_shop[i].Getsotrudnik_count();
                        }
                        else
                        {
                            cout << "В цеху нет сотрудников" << endl;
                        }
                        ciz_information **mas_ciz = mas_shop[i].Getmas_ciz();
                        if (*mas_ciz != NULL)
                        {
                            count_ciz = mas_shop[i].Getciz_count();
                            for (int k = 0; k < count_ciz; ++k)
                            {
                                if (data_srok <= (*mas_ciz)[k].Getciz_data())
                                {
                                }
                                if (data_srok == (*mas_ciz)[k].Getciz_data())
                                {
                                    count_12 = count_12 + 1;
                                }
                            }
                        }
                        else
                        {
                            cout << "В цеху нет сизов" << endl;
                        }
                    }
                }
                if (flag_name_2 == 0)
                {
                    cout << "Введенного цеха не существует" << endl;
                }
                cout << "Количество СИЗов = " << count << endl;
            }
            else
            {
                if (answer == "2")
                {
                    int flag_name_2 = 0;
                    cout << "Введите название цеха" << endl;
                    cin >> poisk_shop_name;
                    cout << "Введите фамилию сотрудника: " << endl;
                    cin >> surname_search;
                    cout << "Введите имя сотрудника: " << endl;
                    cin >> name_search;
                    cout << "Введите отчество сотрудника: " << endl;
                    cin >> middlename_search;
                    cout << "Введите на какой срок рассчитать кол-во СИЗов" << endl;
                    cin >> data_srok;
                    int check = 0;
                    int count = 0;
                    for (int i = 0; i < count_shop; ++i)
                    {
                        if (poisk_shop_name == mas_shop[i].Getshop_name())
                        {
                            flag_name_2 = 1;
                            sotrudnik_information **mas_sotrudnik = mas_shop[i].Getmas_sotrudnik();
                            if (*mas_sotrudnik != NULL)
                            {
                                count_sotr = mas_shop[i].Getsotrudnik_count();
                                for (int j = 0; j < count_sotr; j++)
                                {
                                    if ((surname_search == (*mas_sotrudnik)[i].Getsotrudnik_surname()) && (name_search == (*mas_sotrudnik)[i].Getsotrudnik_name()) && (middlename_search == (*mas_sotrudnik)[i].Getsotrudnik_middlename()))
                                    {
                                        check = 1;
                                    }
                                }
                            }
                            if (check == 1)
                            {
                                ciz_information **mas_ciz = mas_shop[i].Getmas_ciz();
                                if (*mas_ciz != NULL)
                                {
                                    count_ciz = mas_shop[i].Getciz_count();
                                    for (int k = 0; k < count_ciz; ++k)
                                    {
                                        if (data_srok < (*mas_ciz)[k].Getciz_data())
                                        {
                                            count = count_ciz * ((*mas_ciz)[k].Getciz_data() - data_srok);
                                        }
                                        else if (data_srok == (*mas_ciz)[k].Getciz_data())
                                        {
                                            count = count_ciz;
                                        }
                                        else
                                        {
                                            count = count_ciz * data_srok;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (flag_name_2 == 0)
                    {
                        cout << "Введенного цеха не существует" << endl;
                    }
                    if (check == 0)
                    {
                        cout << "Введенного сотрудника не существует" << endl;
                    }
                    cout << count << endl;
                }
                if (answer == "3")
                {
                    cout << "Введите на какой срок рассчитать кол-во СИЗов" << endl;
                    cin >> data_srok;
                    int count = 0;
                    for (int i = 0; i < count_shop; ++i)
                    {
                        sotrudnik_information **mas_sotrudnik = mas_shop[i].Getmas_sotrudnik();
                        if (*mas_sotrudnik != NULL)
                        {
                            count_sotr = mas_shop[i].Getsotrudnik_count();
                        }
                        cout << count_sotr;
                        ciz_information **mas_ciz = mas_shop[i].Getmas_ciz();
                        if (*mas_ciz != NULL)
                        {
                            count_ciz = mas_shop[i].Getciz_count();
                            for (int k = 0; k < count_ciz; ++k)
                            {
                                if (data_srok <= (*mas_ciz)[k].Getciz_data())
                                {
                                    count += count_shop * count_ciz * count_sotr;
                                }
                                else
                                {
                                    count = 1;
                                }
                            }
                            cout << "kolvo" << count << endl;
                        }
                    }
                }
            }
        }
        break;
        }
    }
    ofstream wf;
    wf.open(file_name, ios::binary | ios::out);
    wf.write((char *)&size_shop, sizeof(size_shop));
    wf.write((char *)&count_shop, sizeof(count_shop));
    for (int i = 0; i < count_shop; i++)
    {
        size_t size1 = mas_shop[i].Getshop_name().length();
        wf.write((char *)&size1, sizeof(size1));
        wf.write((char *)(mas_shop[i].Getshop_name().c_str()), size1);

        sotrudnik_information **mas_sotrudnik = mas_shop[i].Getmas_sotrudnik();
        ciz_information **mas_ciz = mas_shop[i].Getmas_ciz();

        size_sotrudnik = mas_shop[i].Getsotrudnik_size();
        wf.write((char *)&size_sotrudnik, sizeof(size_sotrudnik));

        size_ciz = mas_shop[i].Getciz_size();
        wf.write((char *)&size_ciz, sizeof(size_ciz));

        count_sotr = mas_shop[i].Getsotrudnik_count();
        wf.write((char *)&count_sotr, sizeof(count_sotr));

        count_ciz = mas_shop[i].Getciz_count();
        wf.write((char *)&count_ciz, sizeof(count_ciz));
        for (int j = 0; j < count_sotr; j++)
        {
            size_t size2 = (*mas_sotrudnik)[j].Getsotrudnik_name().length();
            wf.write((char *)&size2, sizeof(size2));
            wf.write((char *)((*mas_sotrudnik)[j].Getsotrudnik_name().c_str()), size2);

            size_t size3 = (*mas_sotrudnik)[j].Getsotrudnik_surname().length();
            wf.write((char *)&size3, sizeof(size3));
            wf.write((char *)((*mas_sotrudnik)[j].Getsotrudnik_surname().c_str()), size3);

            size_t size4 = (*mas_sotrudnik)[j].Getsotrudnik_middlename().length();
            wf.write((char *)&size4, sizeof(size4));
            wf.write((char *)((*mas_sotrudnik)[j].Getsotrudnik_middlename().c_str()), size4);
        }
        for (int k = 0; k < count_ciz; k++)
        {
            ciz_data = (*mas_ciz)[k].Getciz_data();
            wf.write((char *)&ciz_data, sizeof(ciz_data));
            size_t size5 = (*mas_ciz)[k].Getciz_name().length();
            wf.write((char *)&size5, sizeof(size5));
            wf.write((char *)((*mas_ciz)[k].Getciz_name().c_str()), size5);
        }
    }
    wf.close();
    delete[] mas_shop;
    return 0;
}
