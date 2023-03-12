#include <iostream>
#include <fstream>
using namespace std;

void sysout(double **a, double *y, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << "*x" << j + 1;
            if (j < n - 1)
                cout << " + ";
        }
        cout << " = " << y[i] << endl;
    }
    return;
}

double *gauss(double **a, double *y, int n)
{
    double *x, max;
    int k, index;
    const double eps = 0.00001;
    x = new double[n];
    k = 0;
    while (k < n)
    {
        max = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++)
        {
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);
                index = i;
            }
        }
        if (max < eps)
        {
            cout << "the equation has no solution " << endl
                 << "=> x = no solution";
            return 0;
        }
        for (int j = 0; j < n; j++)
        {
            double temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }
        double temp = y[k];
        y[k] = y[index];
        y[index] = temp;
        for (int i = k; i < n; i++)
        {
            double temp = a[i][k];
            if (abs(temp) < eps)
                continue;
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / temp;
            y[i] = y[i] / temp;
            if (i == k)
                continue;
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            y[i] = y[i] - y[k];
        }
        k++;
    }

    for (k = n - 1; k >= 0; k--)
    {
        x[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * x[k];
    }
    return x;
}

int main()
{
    int chosse;
    cout << " Please choose your option: " << endl
         << "1. import data from file" << endl
         << "2. input data from the keyboard" << endl;
    cin >> chosse;
    if (chosse == 1)
    {
        ifstream file;
        file.open("input.txt");
        double **a, *y, *x;
        int n;
        file >> n;
        a = new double *[n];
        y = new double[n];
        for (int i = 0; i < n; i++)
        {
            a[i] = new double[n];
            for (int j = 0; j < n; j++)
            {
                file >> a[i][j];
            }
            file >> y[i];
        }
        sysout(a, y, n);
        cout << "The solution of this equation is: " << endl;
        if (gauss(a, y, n) != 0)
        {
            x = gauss(a, y, n);
            for (int i = 0; i < n; i++)
            {
                if (typeid(x[i]) == typeid(double))
                {
                    cout << "=> "
                         << "x[" << i + 1 << "]=" << x[i] << endl;
                }
            }
        }
        return 0;
        file.close();
        }
    else if (chosse == 2)
    {
        double **a, *y, *x;
        int n;
        system("cls");
        cout << "Enter number of equations: ";
        cin >> n;
        a = new double *[n];
        y = new double[n];
        for (int i = 0; i < n; i++)
        {
            cout << "equation number " << i + 1 << endl;
            a[i] = new double[n];
            for (int j = 0; j < n; j++)
            {
                cout << "x" << j + 1 << " = ";
                cin >> a[i][j];
            }
            cout << "y" << i + 1 << " = ";
            cin >> y[i];
        }
        sysout(a, y, n);
        cout << "The solution of this equation is: " << endl;
        if (gauss(a, y, n) != 0)
        {
            x = gauss(a, y, n);
            for (int i = 0; i < n; i++)
            {
                if (typeid(x[i]) == typeid(double))
                {
                    cout << "=> "
                         << "x[" << i + 1 << "]=" << x[i] << endl;
                }
            }
        }
        cin.get();
        cin.get();
        return 0;
    }
}