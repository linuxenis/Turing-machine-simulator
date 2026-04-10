#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <locale>
#include <cmath>
#include <vector>
#include <map>
#include <windows.h>
#include <conio.h>

using namespace std;

struct bus
{
    vector<char> esamas1, esamas2, naujas1, naujas2;
    vector<int> judejimas1, judejimas2;
    vector<string> naujabusena;
};



int main()
{
    cout<<"Iveskit ivesties failo pilna pavadinima: ";
    string failas;
    cin>>failas;
    
    ifstream fin(failas);

    ///////////////////////////////////////////////juostos

    int kiekjuostu;
    fin >> kiekjuostu;

    string temp;
    fin >> temp; //jeigu juostoje yra tarpai, tai neveiks, bet tiesiog speju kad nera

    vector<char> juosta1, juosta2;

    for (int i = 0; i < temp.size(); i++)
    {
        juosta1.push_back(temp[i]);
    }

    int pos1, pos2;

    if (kiekjuostu == 2) //jeigu yra antra juosta, tai ivedu
    {
        fin >> temp;

        for (int i = 0; i < temp.size(); i++)
        {
            juosta2.push_back(temp[i]);
        }


        fin >> pos1 >> pos2;
        pos1--;
        pos2--;
    }
    else
    {
        fin >> pos1;
        pos1--;
    }
    ///////////////////////////////////////////////busenu ivedimas
    map<string, bus> busena;
    while (fin.good()) // !eof() kazkodel neveikia
    {

        string a;
        fin >> a;

        char b;

        fin >> b;
        busena[a].esamas1.push_back(b);

        if (kiekjuostu == 2)
        {
            fin >> b;
            busena[a].esamas2.push_back(b);
        }

        fin >> b;
        busena[a].naujas1.push_back(b);

        if (kiekjuostu == 2)
        {
            fin >> b;
            busena[a].naujas2.push_back(b);
        }

        fin >> b;
        int c;
        if (b == 'L')
        {
            c = -1;
        }
        else if (b == 'R')
        {
            c = 1;
        }
        else
        {
            c = 0;
        }
        busena[a].judejimas1.push_back(c);

        if (kiekjuostu == 2)
        {
            fin >> b;
            if (b == 'L')
            {
                c = -1;
            }
            else if (b == 'R')
            {
                c = 1;
            }
            else
            {
                c = 0;
            }
            busena[a].judejimas2.push_back(c);
        }

        char tarpas;
        fin.get(tarpas);//praleidziu tarpa kad netikrintu jo

        string d;
        fin >> d;
        busena[a].naujabusena.push_back(d);


    }
    ///////////////////////////////////////////////rodykliu sukurimas
    vector<char> rodykle1, rodykle2;
    for (int i = 0; i < juosta1.size(); i++)
    {
        rodykle1.push_back(' ');
    }
    rodykle1[pos1] = '^';

    if (kiekjuostu == 2)//antros juostos rodykle
    {
        for (int i = 0; i < juosta2.size(); i++)
        {
            rodykle2.push_back(' ');
        }
        rodykle2[pos2] = '^';
    }
    ///////////////////////////////////////////////veikimas
    string esamabusena = "0";

    bool arrado = false;

    while (!_kbhit()) // <conio.h> biblioteka, jeigu kazkas ant klaviaturos paspausta, tai ciklas baigiasi
    {

        system("cls"); //istrina konsole

        for (int i = 0; i < juosta1.size(); i++)//isvedu juosta
        {
            cout << juosta1[i];

        }
        cout << endl;

        for (int i = 0; i < rodykle1.size(); i++)//isvedu rodykle
        {
            cout << rodykle1[i];
        }
        cout << endl;
        rodykle1[pos1] = ' '; //istrinu rodykle, veliau vel idedu nauja

        if (kiekjuostu == 2) //antros juostos isvedimas
        {
            for (int i = 0; i < juosta2.size(); i++)//isvedu juosta
            {
                cout << juosta2[i];

            }
            cout << endl;

            for (int i = 0; i < rodykle2.size(); i++)//isvedu rodykle
            {
                cout << rodykle2[i];
            }
            cout << endl;
            rodykle2[pos2] = ' '; //istrinu rodykle, veliau vel idedu nauja
        }

        cout << "esama busena: " << esamabusena << endl;


        arrado = false;
        if (kiekjuostu == 1)
        {
            for (int i = 0; i < busena[esamabusena].esamas1.size(); i++)//veikimas, jeigu tik viena juosta
            {

                if (juosta1[pos1] == busena[esamabusena].esamas1[i])
                {

                    juosta1[pos1] = busena[esamabusena].naujas1[i];

                    pos1 = pos1 + busena[esamabusena].judejimas1[i];

                    if (pos1 == -1) //juostos begalinis pletimas i kaire ir desine
                    {
                        juosta1.insert(juosta1.begin(), '*');  //pratesiu juosta zvaigzdutemis
                    }
                    else if (pos1 == juosta1.size())
                    {
                        juosta1.push_back('*');
                    }

                    string tempbusena = esamabusena;
                    esamabusena = busena[tempbusena].naujabusena[i];
                    arrado = true;
                    break;
                }
            }
        }
        else
        {
            for (int i = 0; i < busena[esamabusena].esamas1.size(); i++)//veikimas, jeigu dvi juostos
            {

                if (juosta1[pos1] == busena[esamabusena].esamas1[i] && juosta2[pos2] == busena[esamabusena].esamas2[i])
                {

                    juosta1[pos1] = busena[esamabusena].naujas1[i];

                    pos1 = pos1 + busena[esamabusena].judejimas1[i];

                    juosta2[pos2] = busena[esamabusena].naujas2[i];

                    pos2 = pos2 + busena[esamabusena].judejimas2[i];

                    if (pos1 == -1) //juostos begalinis pletimas i kaire ir desine
                    {
                        juosta1.insert(juosta1.begin(), '*');  //nezinau kaip pratest juosta, tai tiesiog zvaigzdutes dedu
                    }
                    else if (pos1 == juosta1.size())
                    {
                        juosta1.push_back('*');
                    }

                    if (pos2 == -1) //juostos begalinis pletimas i kaire ir desine
                    {
                        juosta2.insert(juosta2.begin(), '*');  //nezinau kaip pratest juosta, tai tiesiog zvaigzdutes dedu
                    }
                    else if (pos2 == juosta2.size())
                    {
                        juosta2.push_back('*');
                    }
                    string tempbusena = esamabusena;
                    esamabusena = busena[tempbusena].naujabusena[i];
                    arrado = true;
                    break;
                }
            }
        }

        rodykle1[pos1] = '^';

        if (kiekjuostu == 2)
        {
            rodykle2[pos2] = '^';
        }

        if (arrado == false)//jeigu nezinoma ka daryt su tokiu simboliu dabartineje busenoje, darbas nutraukiamas
        {
            cout << "esama busena nezino ka daryti su tokiu simboliu." << endl;
            return 0;
        }
        else if (busena[esamabusena].esamas1.size() == 0) //jeigu tuscia busena, tai tiesiog baigta
        {
            cout << "baigta, galutine  busena: " << esamabusena << endl;
            return 0;
        }

        cout << endl << "paspauskite bet koki klaviaturos mygtuka kad baigtumet darba" << endl;

        Sleep(50); //windows.h biblioteka, padaro delay. kuo mazesnis delay, tuo prastesnis juostos matomumas
    }
    return 0;
}
