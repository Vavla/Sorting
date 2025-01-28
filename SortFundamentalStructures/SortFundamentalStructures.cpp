// SortFundamentalStructures.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include<array>
#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;
std::regex re3("(0[1-9]|[1|2][0-9]|3[0|1])\.(0[1-9]|1[0-2])\.(1[0-9][0-9][0-9]|2[0][0-2][0-9])");
std::regex re2("([А-Я][а-я]*\ [А-Я][а-я]*\ [А-Я][а-я]*)");

typedef struct Date {
    int day;
    int mouth;
    int year;
}Date;
typedef struct FIO {
    string name;
    string surname;
    string patronymic;
}FIO;
typedef struct Data {
    Date date;
    FIO fio;
    int number;
}Data;
int cmpDateBefore(Date date1,Date date2) {
    
        if (date1.year > date2.year) return 1;
        else if (date1.year < date2.year) return 0;
        else if (date1.year == date2.year) {
            if (date1.mouth > date2.mouth) return 1;
            else if (date1.mouth < date2.mouth) return 0;
            else if (date1.mouth == date2.mouth){
                if (date1.day > date2.day) return 1;
                else if (date1.day < date2.day) return 0;
                else return 2;
            }
        }
    }
int cmpFIOBefore(FIO f1,FIO f2) {
    string s1 = f1.name + " " + f1.surname + " " + f1.patronymic;
    string s2 = f2.name + " " + f2.surname + " " + f2.patronymic;
    return s1.compare(s2);
}


void insertion(Data mass[],int n) {
	int len = n;
	for (int i = 0; i < len; i++) {
		int j = i - 1;
		Data key = mass[i];
		while (cmpDateBefore(key.date,mass[j].date) == 0  && j >= 0) {
            if (cmpDateBefore(key.date, mass[j].date) == 0) {
                mass[j + 1] = mass[j];
                j -= 1;

            }
            else break;
            
		}
        while (cmpDateBefore(key.date, mass[j].date) == 2 && j >= 0 ) {
            
                if (cmpFIOBefore(key.fio, mass[j].fio) == 1) {
                    mass[j + 1] = mass[j];
                    
                   // std::cout << "change " << mass[j].date.day << mass[j].date.mouth << mass[j].date.year << mass[j].fio.surname << endl ;
                    j -= 1;
                }
                else {// std::cout << " not change " << mass[j].date.day << mass[j].date.mouth << mass[j].date.year << mass[j].fio.surname << endl; 
                    break; }
        }
        mass[j + 1] = key;
        /*for (int i = 0; i < 5; i++) {
            std::cout << "Mass " << mass[i].date.day << mass[i].date.mouth << mass[i].date.year << mass[i].fio.surname << " " ;
        }*/
        //cout << endl;
	}
	
}
bool validalDate(std::string s) {
    if (regex_match(s.begin(), s.end(), re3)) return 1;
    else return 0;

}
bool validalFIO(std::string s) {
    if (regex_match(s.begin(), s.end(), re2)) return 1;
    else return 0;

}
// Реализация пирамидальной сортировки на C++

//// Процедура для преобразования в двоичную кучу поддерева с корневым узлом i, что является
//// индексом в arr[]. n - размер кучи
//
void heapify(Data arr[], int n, int i)
{
    int largest = i;
    // Инициализируем наибольший элемент как корень
    int l = 2 * i + 1; // левый = 2*i + 1
    int r = 2 * i + 2; // правый = 2*i + 2

    // Если левый дочерний элемент больше корня
    if (l < n && cmpDateBefore(arr[largest].date,arr[l].date) == 1)
        largest = l;
    else  if (l < n && cmpDateBefore(arr[largest].date, arr[l].date) == 2)
    {
        if(cmpFIOBefore(arr[largest].fio, arr[l].fio))
           largest = l;
    }
        
    // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (r < n && cmpDateBefore(arr[largest].date, arr[r].date))
        largest = r;
    else  if (r < n && cmpDateBefore(arr[largest].date, arr[r].date) == 2)
    {
        if (cmpFIOBefore(arr[largest].fio, arr[r].fio))
            largest = r;
    }

    // Если самый большой элемент не корень
    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);

        // Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        heapify(arr, n, largest);
    }
}

// Основная функция, выполняющая пирамидальную сортировку
void heapSort(Data arr[], int n)
{
    // Построение кучи (перегруппируем массив)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i >= 0; i--)
    {
        // Перемещаем текущий корень в конец
        std::swap(arr[0], arr[i]);

        // вызываем процедуру heapify на уменьшенной куче
        heapify(arr, i, 0);
    }
}
 Data mass[1000000]{};
 Data mass2[1000000]{0};
 int main()
 {   
     int n;
     string s;
     ifstream file;
     file.open("dateFIO.txt", std::ios::in);
     file >> n;
     cout << n << endl;
     for (int i = 0; i <= n+1; i++) { // пока не достигнут конец файла класть очередную строку в переменную (s)
         getline(file, s);
         if (i != 0) {
             Data data;
             data.number = i+2;
             data.date.day = (s[0] - '0')*10 + (s[1] - '0');
             data.date.mouth = (s[3]-'0')*10 + (s[4] - '0');
             data.date.year = (s[6] - '0')*1000 + (s[7] - '0')*100 + (s[8] - '0') * 10 + (s[9] - '0');
             int k = 11;
             while (s[k] != ' ') {
                 data.fio.name += s[k];
                 k++;
             }
             k++;
             while (s[k] != ' ') {
                 data.fio.surname += s[k];
                 k++;
             }
             k++;
             while (k <= s.size()) {
                 data.fio.patronymic += s[k];
                 k++;
             }
             mass[i-1] = data;
             mass2[i-1] = data;
             //std::cout << mass[i].date.day << "." << mass[i].date.mouth << "." << mass[i].date.year << " " << data.fio.name << " " << data.fio.surname << " " << data.fio.patronymic << endl;
                 
             
         }

     }
    
    file.close();
    double start = clock();
	insertion(mass,n);
    double end = clock();
    double time = (end - start)/ CLOCKS_PER_SEC;

    for (int i = 0; i <= n; i++) {
        if (mass[i].date.day < 10) std::cout << "0";
        std::cout << mass[i].date.day << ".";
        if (mass[i].date.mouth < 10) std::cout << "0";
        std::cout << mass[i].date.mouth << "." << mass[i].date.year << " " << mass[i].fio.name << " " << mass[i].fio.surname << " " << mass[i].fio.patronymic << " " << mass[i].number << endl;
    }
    cout << "Time" << time << endl;
   
    cout << "==================================" << endl;
    cout << "==================================" << endl;
    double start2 = clock();
    heapSort(mass2, n);
    double end2 = clock();
    double time2 = (end2 - start2)/ CLOCKS_PER_SEC;

    for (int i = 0; i <= n; i++) {
        if (mass[i].date.day < 10) std::cout << "0";
        std::cout << mass[i].date.day << ".";
        if (mass[i].date.mouth < 10) std::cout << "0";
        std::cout << mass[i].date.mouth << "." << mass[i].date.year << " " << mass[i].fio.name << " " << mass[i].fio.surname << " " << mass[i].fio.patronymic << " " << mass[i].number << endl;
    }
    cout << time2 << endl;
   ///сделать в выходной файл вывод, сделать +2 файла (упорядоченные данные, упорядоченные в обратном порядке) и проверить время работы на них.
}


