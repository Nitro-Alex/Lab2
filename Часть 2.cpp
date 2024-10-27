#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <memory>

using namespace std;

char rusmas[256];
char* rus(const char* text)
{
    CharToOemA(text, rusmas);
    return rusmas;
}

class service //тарифы
{
public:
    service(string fname = "Новый тариф", double fcost = 0) //конструктор
    {
        name = fname;
        cost = fcost;
    }
    ~service() //деструктор
    {
        //cout << rus("Тариф удалён") << endl;
    }
    void set_name(string new_name)
    {
        name = new_name;
    }
    string get_name()
    {
        return name;
    }
    void set_cost(double new_cost)
    {
        cost = new_cost;
    }
    double get_cost()
    {
        return cost;
    }
private:
    string name;
    double cost;
};

class resident
{
public:
    resident(string fsurname = "-", string fname = "-") //конструктор
    {
        name = fname;
        surname = fsurname;
    }
    ~resident() //деструктор
    {
        //cout << rus("Жилец удалён") << endl;
    }
    void set_name(string new_name, string new_surname)
    {
        name = new_name;
        surname = new_surname;
    }
    string get_surname()
    {
        return surname;
    }
    void use_service(service cur_service)
    {
        consumption.push_back(cur_service);
        //cout << consumption[0].get_cost() << endl; //ОТЛАДКА
    }
    double summ_service()
    {
        double res_cost = 0;
        cout << consumption.size() << endl;
        for (unsigned int i = 0; i < consumption.size(); i++)
        {
            cout << consumption[i].get_cost() << endl;
            res_cost += consumption[i].get_cost();
        }
        return res_cost;
    }
private:
    string name;
    string surname;
    vector <service> consumption;
};

class ges
{
private:
    string district = "-";
    int number = 0;
    vector <resident> residents; //ДОБАВЛЯТЬ В ВЕКТОРЫ УКАЗАТЕЛИ И РАБОТАТЬ С НИМИ, ПЕРЕДЕЛАТЬ ПРОГРАММУ
    vector <service> services;
public:
    ges(string nd = "-", int nn = 0) //конструктор
    {
        district = nd;
        number = nn;
    }
    ~ges() //деструктор
    {
        cout << rus("ЖЭС удалена") << endl;
    }
    void set_district(string newd)
    {
        district = newd;
    }
    void set_number(int newn)
    {
        number = newn;
    }
    void add_service(service new_service)
    {
        services.push_back(new_service);
    }
    void add_resident(resident new_resident)
    {
        residents.push_back(new_resident);
    }
    resident find_res(string f_surname)
    {
        resident res_to_find;
        for (int i = 0; i < residents.size(); i++)
        {
            if (f_surname == residents[i].get_surname())
            {
                res_to_find = residents[i];
                cout << "+" << endl; //ОТЛАДКА
            }
        }
        return res_to_find;
    }
    service find_service(string f_service)
    {
        service service_to_find;
        for (int j = 0; j < services.size(); j++)
        {
            if (f_service == services[j].get_name())
            {
                service_to_find = services[j];
                cout << "*" << endl; //ОТЛАДКА
            }
        }
        return service_to_find;
    }
    void clean_services()
    {
        vector<service>* ser_addr = &services;
        delete ser_addr;
    }
    void clean_residents()
    {
        vector<resident>* res_addr = &residents;
        delete res_addr;
    }
    double total_cost()
    {
        double total = 0;
        for (unsigned int i = 0; i < residents.size(); i++)
        {
            total += residents[i].summ_service();
        }
        return total;
    }
    void print_info()
    {
        cout << endl << rus("Номер района: ") << district << endl;
        cout << rus("Номер ЖЭС: ") << number << endl;
    }
};

service* create_service(string name, double price) //выделение нового тарифа
{
    return new service(name, price);
}

resident* create_resident(string surname, string name) //выделение нового жильца
{
    return new resident(surname, name);
}

enum menu
{
    input_service_info = 1,
    input_res_info,
    output_res_cost,
    output_total_cost,
    consume_a_service,
    end = 0
};

int main()
{
    ges ges1;
    //меню
    int menu_flag = 1;
    while (1 == 1)
    {
        cout << rus("Введите") << endl;
        cout << rus("1 для ввода информации о тарифе") << endl;
        cout << rus("2 для ввода информации о жильце") << endl;
        cout << rus("3 для вывода стоимости оказанных жильцу услуг") << endl;
        cout << rus("4 для вывода стоимости всех оказанных услуг") << endl;
        cout << rus("5 для записи информации о потреблении жильцом услуги") << endl;
        cout << rus("0 для завершения работы программы") << endl;
        int action;
        cin >> action;
        cout << endl;
        switch (action)
        {
        case menu::input_service_info: //ввод информации о тарифе
        {
            cout << rus("Введите название тарифа") << endl;
            string service_name;
            cin >> service_name;
            cin.get();
            string sprice;
            int flag1;
            do {
                flag1 = 1;
                cout << rus("Введите цену") << endl;
                getline(cin, sprice);
                for (int i = 0; i < sprice.size(); i++)
                {
                    if ((isdigit(sprice[i]) == 0) && (sprice[i] != '.'))
                    {
                        flag1 = 0;
                        break;
                    }
                }
            } while (flag1 == 0);
            double price = stoi(sprice);
            ges1.add_service(*create_service(service_name, price));
        }
        break;
        case menu::input_res_info: //ввод информации о жильце
        {
            cout << rus("Введите фамилию нового жильца") << endl;
            string res_surname;
            cin >> res_surname;
            cin.get();
            cout << rus("Введите имя нового жильца") << endl;
            string res_name;
            cin >> res_name;
            cin.get();
            ges1.add_resident(*create_resident(res_surname, res_name));
        }
        break;
        case menu::output_res_cost: //вывод стоимости оказанных жильцу услуг
        {
            cout << rus("Введите фамилию жильца, информацию о потреблённых услугах которого вы хотите получить") << endl;
            string res_sur;
            cin >> res_sur;
            cin.get();
            resident cur_res = ges1.find_res(res_sur);
            cout << rus("Стоимость услуг, потреблённых жильцом: ") << cur_res.summ_service();
            cout << rus(" рублей") << endl;
        }
        break;
        case menu::output_total_cost: //вывод стоимости всех оказанных услуг
        {
            cout << rus("Общая стоимость всех оказанных жильцам услуг: ") << ges1.total_cost();
            cout << rus(" рублей") << endl;
        }
        break;
        case menu::consume_a_service://запись информации об оказании жильцу услуги
        {
            cout << rus("Введите фамилию жильца, потребившего услугу") << endl;
            string res_sur, service_to_reg;
            cin >> res_sur;
            cout << rus("Введите название потреблённой услуги") << endl;
            cin >> service_to_reg;
            resident cur_res = ges1.find_res(res_sur);
            service cur_ser = ges1.find_service(service_to_reg);
            cur_res.use_service(cur_ser);
        }
        break;
        case menu::end: //завершение работы
        {
            menu_flag = 0;
        }
        break;
        }
        
        if (menu_flag == 0)
        {
            ges1.clean_services();
            cout << rus("Тарифы удалены") << endl;
            ges1.clean_residents();
            cout << rus("Жильцы удалены") << endl;
            break;
        }
    }
    return 0;
}
