#include <iostream>
#include "GLBall.hpp"
#include "NBodyScene.hpp"
#include <math.h>
#include <vector>

using namespace std;

// Ваш класс для описания тела.
// Унаследован от GLBall, реализует его интерфейс с методами getX / getY / getR.
// (Для точечных тел внутри getR можете сделать возврат константы.)
class SampleBall : public GLBall {
protected:
    int n;
    double *radius = NULL;
    double *massa = NULL;
    double *x = NULL;
    double *y = NULL;
    double *v_x = NULL;
    double *v_y = NULL;
    double *new_x = NULL;
    double *new_y = NULL;

public:
    SampleBall(int n)
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
    ~SampleBall()
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
    void move(double dt) {
        for (int i = 0; i < n; i++)
        {
            x[i] += v_x[i] * dt;
            y[i] += v_y[i] * dt;

        }
    }

    // Реализация методов интерфейса на базе *ваших* переменных.
    // Переписывать всю свою реализацию под эти имена *не* надо.
    double getX(int i) const {
        return x[i];
    }
    double getY(int i) const {
        return y[i];
    }
    double getR(int i) const {
        return radius[i];
    }
};

// Ваш класс сцены. В него де-факто превратится текущий main или его аналог.
// Унаследован от NBodyScene, реализует интерфейс с методами getNumberOfBodies / getBody / doTimeStep.
class SampleScene : public NBodyScene {
protected:
    int n;
    double time;
    double g_const = (6.67 / 100000000000);
    double s_x, s_y, f_x, f_y;
    std::vector<SampleBall> bodies;
    double *radius = NULL;
    double *massa = NULL;
    double *x = NULL;
    double *y = NULL;
    double *v_x = NULL;
    double *v_y = NULL;
    double *new_x = NULL;
    double *new_y = NULL;

public:
    SampleScene(int n)
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
    ~SampleScene()
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
    }    // Реализация методов интерфейса на базе *ваших* переменных

    unsigned int getNumberOfBodies() const override {
        return bodies.size();
    }

    const GLBall& getBody(unsigned int number) const override {
        return bodies.at(number);
    }

    void doTimeStep() override {
        for(SampleBall& b : bodies)
            b.move(0.1);
    }

    // Далее ещё куча ваших методов, никак не связанных с NBodyScene

    void initScene() {
        bodies.push_back(SampleBall(0, 0, 10, 1, 0));
        bodies.push_back(SampleBall(15, 15, 1, 0, 1));
    }
};

// Функция, которая готовит всю сцену и возвращает готовый объект.
// Если нужно читать из файла и консоли, вызывать кучу методов - это здесь.
NBodyScene* getScene()
{
    SampleScene* s = new SampleScene();
    s->initScene();
    return s;
}


// Ваш отладочный main
int main()
{
    // Создаём сцену
    SampleScene* scene = (SampleScene*)getScene();
    double M, R, X, Y, VX, VY;
    SampleBall a(5);
    for(int i = 0; i < 5; ++i)
    {
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
    }
    delete scene;
    return 0;
}

