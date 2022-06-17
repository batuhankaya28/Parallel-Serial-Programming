#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <omp.h>
#include <random>

using namespace std;

#define Thread_sayaci 4

double** M1, ** M2, ** MUX;// double matris icin tanimladigim pointer dizisi
double say_baslat, say_durdur; // süre icin tanimladigim degiskenler
float** FM1, ** FM2, ** FMUX; // float matris icin tanimladigim pointer dizisi
int alan; // matris boyutlarini tuttugum degisken


/*=========================================================================================================================================================
=====================================FLOAT MATRIS ISLEMLERININ YAPILDIGI KISIM=============================================================================
=========================================================================================================================================================*/


void float_Matris_Ata()
{
    FM1 = new float* [alan]; //Float 1.Matris
    FM2 = new float* [alan];//Float 2.Matris
    FMUX = new float* [alan];//Float Carpým Matrýsý

    for (int i = 0; i < alan; i++)
    {
        FM1[i] = new float[alan];
    } //1.Matrýsýn olusturuldugu kýsým

    for (int i = 0; i < alan; i++)
    {
        FM2[i] = new float[alan];
    } // 2.Matrýsýn olusturuldugu kýsým

    for (int i = 0; i < alan; i++)
    {
        FMUX[i] = new float[alan];
    } // Carpým matrýsýnýn olusturuldugu kýsým

    for (int i = 0; i < alan; i++)
    {
        for (int j = 0; j < alan; j++)
        {
            FM1[i][j] = 1; //1.Matrýs degerlerýnýn 1'e setlendýgý kýsým
        }
    }

    for (int i = 0; i < alan; i++)
    {
        for (int j = 0; j < alan; j++)
        {
            FM2[i][j] = 1; //2.Matrýs degerlerýnýn 1'e setlendýgý kýsým

        }
    }
    cout << alan << "x" << alan << " boyutlu Float Matris Olusturuldu" << endl;
}

void float_ParallelCarp()
{
    int i, j, k;
    say_baslat = omp_get_wtime(); // saniyeler içinde geçen duvar saati zamanýna eþit çift duyarlýklý kayan nokta deðerine döndürüldüðü kýsým

    omp_set_num_threads(Thread_sayaci);
#pragma omp parallel for private(i,j,k) schedule(dynamic) // bu fonksiyonun pararel carpým yapmasýný saglayan pararele donusturucu kod kýsmý
    for (i = 0; i < alan; i++)
    {
        for (j = 0; j < alan; j++)
        {

            for (k = 0; k < alan; k++)
            {
                FMUX[i][j] += FM1[i][k] * FM2[k][j]; //Matrýs carpýmýnýn yapýldýgý kýsým
            }
        }
    }

    say_durdur = omp_get_wtime() - say_baslat; // gecen surenýn hesaplandýgý kýsým
    cout << "Paralel Carpma Sonucu gecen sure ==>  " << say_durdur << " saniye \n" << endl;
}

void float_SeriCarp()
{
    say_baslat = omp_get_wtime();
    for (int i = 0; i < alan; i++)
    {
        for (int j = 0; j < alan; j++)
        {
            double temp = 0;
            for (int k = 0; k < alan; k++)
            {
                temp += FM1[i][k] * FM2[k][j]; // Matrýs carpýmýnýn yapýldýgý kýsým
            }
        }
    }
    say_durdur = omp_get_wtime() - say_baslat;
    cout << "\nSeri Carpim Sonucu gecen sure ==> " << say_durdur << " saniye\n" << endl;
}

void float_Matrisi_Temizle()
{
    for (int i = 0; i < alan; i++)
    {
        delete[] FM1[i];
    }
    for (int i = 0; i < alan; i++)
    {
        delete[] FM2[i];
    }
    for (int i = 0; i < alan; i++)
    {
        delete[] FMUX[i];
    }

    delete[] FM1;
    delete[] FM2;
    delete[] FMUX;

    cout << "Float Matris Bilgileri silindi .\n" << endl;

}

/*=========================================================================================================================================================
====================================================DOUBLE MATRIS ISLEMLERININ YAPILDIGI KISIM=============================================================
==========================================================================================================================================================*/


void double_Matris_Ata()
{
    M1 = new double* [alan]; //1.Matris
    M2 = new double* [alan];//2.Matris
    MUX = new double* [alan];//Carpým Matrýsý

    for (int i = 0; i < alan; i++)
    {
        M1[i] = new double[alan];
    }

    for (int i = 0; i < alan; i++)
    {
        M2[i] = new double[alan];
    }

    for (int i = 0; i < alan; i++)
    {
        MUX[i] = new double[alan];
    }

    for (int i = 0; i < alan; i++)
    {
        for (int j = 0; j < alan; j++)
        {
            M1[i][j] = 1;
        }
    }

    for (int i = 0; i < alan; i++)
    {
        for (int j = 0; j < alan; j++)
        {
            M2[i][j] = 1;

        }
    }
    cout << alan << "x" << alan << " boyutlu Double Matris Olusturuldu" << endl;
}



void double_ParallelCarp()
{
    int i, j, k;
    say_baslat = omp_get_wtime();

    omp_set_num_threads(Thread_sayaci);
#pragma omp parallel for private(i,j,k) schedule(dynamic)
    for (i = 0; i < alan; i++)
    {
        for (j = 0; j < alan; j++)
        {

            for (k = 0; k < alan; k++)
            {
                MUX[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }

    say_durdur = omp_get_wtime() - say_baslat;
    cout << "\nParalel Carpma Sonucu gecen sure ==>  " << say_durdur << " saniye \n" << endl;
}




void double_SeriCarp()
{
    say_baslat = omp_get_wtime();
    for (int i = 0; i < alan; i++)
    {
        for (int j = 0; j < alan; j++)
        {
            double temp = 0;
            for (int k = 0; k < alan; k++)
            {
                temp += M1[i][k] * M2[k][j];
            }
        }
    }
    say_durdur = omp_get_wtime() - say_baslat;
    cout << "\nSeri Carpim Sonucu gecen sure ==> " << say_durdur << " saniye" << endl;
}


void double_Matrisi_Temizle()
{
    for (int i = 0; i < alan; i++) { delete[] M1[i]; }
    for (int i = 0; i < alan; i++) { delete[] M2[i]; }
    for (int i = 0; i < alan; i++) { delete[] MUX[i]; }

    delete[] M1;
    delete[] M2;
    delete[] MUX;

    cout << "Double Matris Bilgileri silindi ." << endl;

}



int main()
{

    cout << "Olusturulacak Matris boyutunu giriniz ==> ";
    cin >> alan;
    cout << "Girmis oldugunuz boyutta kare matris olusturuldu... \n" << endl;
    double_Matris_Ata();
    double_SeriCarp();
    double_ParallelCarp();
    double_Matrisi_Temizle();
    cout << "\n=======================================================================================" << endl;
    cout << "========================================================================================\n" << endl;
    float_Matris_Ata();
    float_SeriCarp();
    float_ParallelCarp();
    float_Matrisi_Temizle();
    system("pause");
    return 0;

}
