/**
 * objectivo: realizar programa que sume ingresos de venta, montos, saque estadisticas
 *
 * *estadisticas:  montoActualLogrado, montoTotalFinal,cantidad de ingresos
 *
 * datos de entrada: string nombre de venta, double monto_Deventa
 * datos salida: double montoTotalFinal, int cantidadVentas,
 *
 * constantes: el monto no debe ser <= 0 y el nombre de venta debe ser != " "
 *
 * deberia usar vector para agregar<string nombre, double amount> asi luego iterar la lista de ingresos y mostrarla
 * ademas de sumar sus gastos
 *
 */
#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <limits>
#include <sstream>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

double sum_actual_amounts(double amount, double actual_amount, string name);
double calculate_statistics(map<string, double> map_sells, int sell_quantity);
double calculate_objective(double final_amount, double objective_amnt);
void write_logfile(string log_text);

int main()
{
    double amount;
    double actual_amount;
    double final_amount;
    double objective_amount;
    double rest_objective_amount;
    int sell_quantity;
    string sell_name;
    string next_sell;
    bool finish = false;
    bool is_correct = false;
    map<string, double> map_sells;

    cout << "*** Programa para calcular ingresos iniciado"
         << "\n";
    cout << "*** Podra ingresar sus ventas en siguiente orden"
         << "\n";
    cout << "*** Nombre de la venta"
         << "\n";
    cout << "*** Precio de la venta"
         << "\n";
    cout << "*** Para cerrar el dia, en lugar de ingresar otro nombre de venta,ingrese 'salir' y enter"
         << "\n";

    while (!finish)
    {
        cout << "\n";
        cout << "Ingrese el nombre de la venta" << endl;
        getline(cin, sell_name);
        if (sell_name == "salir" || sell_name == "Salir")
        {
            finish = true;
            continue;
        }
        else if (sell_name == "" || sell_name == " ")
        {
            cout << "Ingrese un nombre valido, campo vacio no permitido." << endl;
            continue;
        }
        cout << "\n";
        cout << "Nombre de la venta: " << sell_name << endl;
        cout << "\n";

        while (!is_correct)
        {
            cout << "Ingrese el monto de la venta: ";
            string input;
            getline(cin, input);

            char *end;
            double temp = strtod(input.c_str(), &end); // conversion of string input to double, and asigns the end string to the end pointer

            if (end == input.c_str() + input.size())
            {
                amount = temp;
                cout << "\n";
                cout << "Monto de " << sell_name << ": $" << amount << endl;
                cout << "\n";
                is_correct = true;
            }
            else
            {
                cout << "Error. Ingrese un valor numerico." << endl;
                is_correct = false;
            }
        }

        // getline(cin, next_sell); // consume the new line character after the number input

        if (amount <= 0)
        {
            cout << "Error El dato de ingreso es 0" << endl;
            continue;
        }
        // actual_amount = sum_amounts(amount, sell_name);
        sell_quantity++;
        map_sells.insert(make_pair(sell_name, amount));
        actual_amount = sum_actual_amounts(amount, actual_amount, sell_name);
        is_correct = false;
    }
    final_amount = calculate_statistics(map_sells, sell_quantity);
    rest_objective_amount = calculate_objective(final_amount, objective_amount);

    auto today_date = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(today_date);
    cout << "*** Cierre del dia : " << ctime(&now_c)
         << "\n";
    cout << "*** Cantidad de ventas : " << sell_quantity
         << "\n";

    cout << "*** Monto total del dia : $" << final_amount
         << "\n";
    // write_logfile();
    return 0;
}

double sum_actual_amounts(double amount, double actual_amount, string name)
{
    actual_amount += amount;
    cout << "Monto actual : $" << actual_amount << endl;
    return actual_amount;
}

double calculate_statistics(map<string, double> map_amounts, int sell_quantity)
{
    double final_amount = 0.0;
    auto today_date = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(today_date);
    std::tm local_time = *std::localtime(&now_c);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%H-%M-%S");
    std::string log_name = "ticket_ingresos_" + ss.str() + ".txt";

    // Open the log file in append mode
    std::ofstream logfile(log_name, std::ios_base::app);

    if (sell_quantity > 0 || map_amounts.size() != 0)
    {
        logfile << "*** Ingresos del hoy: "
                << "\n";
        for (auto itr = map_amounts.begin(); itr != map_amounts.end(); itr++)
        {
            cout << "*Nombre de venta: " + itr->first << " Monto : $" << itr->second << endl;
            logfile << "*Nombre de venta: " + itr->first << " Monto : $" << itr->second << endl;
            final_amount += itr->second;
        }
        logfile << "*** Cierre del dia : " << ctime(&now_c) << "\n";
        logfile << "*** Cantidad de ventas : " << sell_quantity << "\n";
        logfile << "*** Monto total del dia : $" << final_amount << "\n";
        logfile.close();
    }
    return final_amount;
}

double calculate_objective(double final_amount, double objective_amount)
{
    return final_amount - objective_amount;
}

void write_logfile(string element_value) // sin implementar hasta que lo piense bien
{
    auto today_date = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(today_date);
    ofstream logfile;
    logfile.open("ticket ingresos.txt");
    logfile << element_value;
    logfile.close();
}