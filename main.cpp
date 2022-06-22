#include<iostream>
#include<fstream>
#include<nlohmann/json.hpp>

using namespace std;
nlohmann::json json;

struct DATA {
    int month;
    int log;
    string msg;
    string user;
};

#define n 30
#define arq "arquivosJSON/30.json"

int numeroMes(string mes);
void leituraJSON(DATA data[]);
void mostraVetorDATA(DATA data[]);

void ordena(DATA data[]);
void contaLogPorMes(DATA data[], int logPorMes[]);
void countingSortMes(DATA data[], int exp);
void divideLogsPorMes(DATA data[], int ind, int quantLogs);
int valorMaximo(DATA data[]);
void coutingSortLogsPorMes(DATA logsMes[], int exp, int quantLogs);

int main() {
    DATA data[n];
    
    leituraJSON(data);

    cout<< "\nDesordenado: \n";
    mostraVetorDATA(data);
    ordena(data);
    cout<< "\nOrdenado pelos meses e logs: \n";
    mostraVetorDATA(data);

    cout<< "\n\n";
    return 0;
}

int numeroMes(string mes) {
    map<string, int> meses
    {
        { "January", 1 },
        { "February", 2 },
        { "March", 3 },
        { "April", 4 },
        { "May", 5 },
        { "June", 6 },
        { "July", 7 },
        { "August", 8 },
        { "September", 9 },
        { "October", 10 },
        { "November", 11 },
        { "December", 12 }
    };

    return meses[mes];
}

void leituraJSON(DATA data[]) {
    ifstream file(arq);
    file >> json;

    for (int i = 0; i < n; i++) {
        data[i].month = numeroMes(json[i]["month"]);
        data[i].log = json[i]["log"];
        data[i].msg = json[i]["msg"];
        data[i].user = json[i]["user"];
    }

    // cout<< setw(2) << json << "\n";
}

void mostraVetorDATA(DATA data[]) {
    for (int i = 0; i < n; i++) {
        cout << data[i].month << "\t"
             << data[i].log << "\t"
             << data[i].msg << "\t"
             << data[i].user << "\n";
    }
}

void ordena(DATA data[])
{
	int logPorMes[12] = { 0 }, ind = 0;
    DATA *porMes;

    for (int exp = 1; 12 / exp > 0; exp *= 10)
		countingSortMes(data, exp);

    contaLogPorMes(data, logPorMes);

    cout<< "\nOrdenado pelos meses: \n";
    mostraVetorDATA(data);

    for (int i = 0; i < 12; i++) {
        divideLogsPorMes(data, ind, logPorMes[i]);
        ind += logPorMes[i];
    }
}

void contaLogPorMes(DATA data[], int logPorMes[])
{
	for (int i = 0; i < n; i++)
        logPorMes[(data[i].month)-1]++;
}

void countingSortMes(DATA data[], int exp)
{
	DATA saida[n];
	int i, cont[10] = { 0 };

	for (i = 0; i < n; i++)
		cont[(data[i].month / exp) % 10]++;

	for (i = 1; i < 10; i++)
        cont[i] += cont[i - 1];

	for (i = n - 1; i >= 0; i--) {
		saida[cont[(data[i].month / exp) % 10] - 1] = data[i];
		cont[(data[i].month / exp) % 10]--;
	}

	for (i = 0; i < n; i++)
		data[i] = saida[i];
}

void divideLogsPorMes(DATA data[], int ind, int quantLogs) {
    DATA logsMes[quantLogs];
    int max = valorMaximo(data);

    for (int i = 0; i < quantLogs; i++)
        logsMes[i] = data[ind + i];

    for (int exp = 1; max / exp > 0; exp *= 10)
        coutingSortLogsPorMes(logsMes, exp, quantLogs);

    for (int i = 0; i < quantLogs; i++)
        data[ind + i] = logsMes[i];
}

int valorMaximo(DATA data[])
{
	int i, max = data[0].log;

	for (i = 1; i < n; i++) {
		if (data[i].log > max)
			max = data[i].log;
	}

	return max;
}

void coutingSortLogsPorMes(DATA logsMes[], int exp, int quantLogs) {
    DATA saida[quantLogs];
	int i, cont[10] = { 0 };

	for (i = 0; i < quantLogs; i++)
		cont[(logsMes[i].log / exp) % 10]++;

	for (i = 1; i < 10; i++)
        cont[i] += cont[i - 1];

	for (i = quantLogs - 1; i >= 0; i--) {
		saida[cont[(logsMes[i].log / exp) % 10] - 1] = logsMes[i];
		cont[(logsMes[i].log / exp) % 10]--;
	}

	for (i = 0; i < quantLogs; i++)
		logsMes[i] = saida[i];
}
