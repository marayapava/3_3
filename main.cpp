#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class body
{
protected:
    int n;
    double time;
    double g_const = (6.67 / 100000000000);
    double s_x, s_y, f_x, f_y;
    double *radius = NULL;
    double *massa = NULL;
    double *x = NULL;
    double *y = NULL;
    double *v_x = NULL;
    double *v_y = NULL;
    double *new_x = NULL;
    double *new_y = NULL;
public:
    body(int n)
    {
        radius = new double[n];
        massa = new double[n];
        x = new double[n];
        y = new double[n];
        v_x = new double[n];
        v_y = new double[n];
        new_x = new double[n];
        new_y = new double[n];
    }
    ~body()
    {
        delete[]radius;
        delete[]massa;
        delete[]x;
        delete[]y;
        delete[]v_x;
        delete[]v_y;
        delete[]new_x;
        delete[]new_y;
    }
    void set_time(double value)
    {
        time = value;
    }
    void set_radius(int i,double value)
    {
        radius[i] = value;
    }
    void set_massa(int i,double value)
    {
        massa[i] = value;
    }
    void set_x(int i,double value)
    {
        x[i] = value;
    }
    void set_y(int i,double value)
    {
        y[i] = value;
    }
    void set_v_x(int i,double value)
    {
        v_x[i] = value;
    }
    void set_v_y(int i,double value)
    {
        v_y[i] = value;
    }

    void new_location (int k)
    {

        for (int i = 0; i < n; i++)
        {
            new_x[k] = x[k];
            new_y[k] = y[k];
            if (i != k)
            {
                double s = sqrt((x[k] - x[i]) * (x[k] - x[i]) + (y[k] - y[i]) * (y[k] * y[i]));
                double f = (g_const * massa[k] * massa[i]) / (s * s);
                double s_x = abs(x[k] - x[i]);
                double s_y = abs(y[k] - y[i]);
                double f_x = (f * s_x) / s;
                double f_y = (f * s_y) / s;
                new_x[k] = new_x[k] + v_x[k] * time + f_x * time * time / 2 * massa[k];
                new_y[k] = new_y[k] + v_y[k] * time + f_y * time * time / 2 * massa[k];
                v_x[k] = v_x[k] + f_x * time / massa[k];
                v_y[k] = v_y[k] + f_y * time / massa[k];
            }
        }
        for (int i = 0; i < n; i++)
        {
            x[i] = new_x[i];
            y[i] = new_y[i];
        }
    }
};
int main()
{
    double T, M, R, X, Y, VX, VY;
    body a(3);
    for(int i = 0; i < 3; ++i)
    {
        cin>>T;
        a.set_time(T);
        cin>>M;
        a.set_massa(i, M);
        cin>>R;
        a.set_radius(i, R);
        cin>>X;
        a.set_x(i, X);
        cin>>Y;
        a.set_y(i, Y);
        cin>>VX;
        a.set_v_x(i, VX);
        cin>>VY;
        a.set_v_y(i, VY);
        for(int i = 0; i < 3; i++)
            a.new_location(i);
    }
    return 0;
}
