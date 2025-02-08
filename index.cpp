#include <iostream>
#include <vector>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#define RUNS 2000000

const int NUM_THREADS = 20; // Adjust this based on the number of available cores
const int ITERATIONS = RUNS / NUM_THREADS;

double cc[] = {-1.8451, -1.5302, -1.3858, -1.2070, -1.1761, -0.9541, -0.9132, -0.7032, -0.6853, -0.6752,
                  -0.6727, -0.6502, -0.6065, -0.5795, -0.5308, -0.5056, -0.5005, -0.3485, -0.3431, -0.2602,
                  -0.2531, -0.1939, -0.1515, -0.1035, -0.0503, -0.0466, -0.0356, 0.0566, 0.0813, 0.1036,
                  0.1049, 0.2083, 0.2139, 0.3572, 0.3666, 0.3767, 0.3931, 0.3975, 0.4095, 0.4269,
                  0.4775, 0.5146, 0.5156, 0.5200, 0.5359, 0.5456, 0.6184, 0.6657, 0.6806, 0.7429,
                  0.7839, 0.7986, 0.8635, 0.9006, 0.9203, 1.0378, 1.0765, 1.0917, 1.1790, 1.2641,
                  1.2906, 1.7520, 1.8093};

double calculate(double a, double b, double c, double d, double e, double f)
{
    return cc[62] * a + cc[0] * b + cc[1] * a * b + cc[2] * c + cc[3] * a * c + cc[4] * b * c + cc[5] * a * b * c + cc[6] * d + cc[7] * a * d + cc[8] * b * d + cc[9] * a * b * d + cc[10] * c * d + cc[11] * a * c * d + cc[12] * b * c * d + cc[13] * a * b * c * d + cc[14] * e + cc[15] * a * e + cc[16] * b * e + cc[17] * a * b * e + cc[18] * c * e + cc[19] * a * c * e + cc[20] * b * c * e + cc[21] * a * b * c * e + cc[22] * d * e + cc[23] * a * d * e + cc[24] * b * d * e + cc[25] * a * b * d * e + cc[26] * c * d * e + cc[27] * a * c * d * e + cc[28] * b * c * d * e + cc[29] * a * b * c * d * e + cc[30] * f + cc[31] * a * f + cc[32] * b * f + cc[33] * a * b * f + cc[34] * c * f + cc[35] * a * c * f + cc[36] * b * c * f + cc[37] * a * b * c * f + cc[38] * d * f + cc[39] * a * d * f + cc[40] * b * d * f + cc[41] * a * b * d * f + cc[42] * c * d * f + cc[43] * a * c * d * f + cc[44] * b * c * d * f + cc[45] * a * b * c * d * f + cc[46] * e * f + cc[47] * a * e * f + cc[48] * b * e * f + cc[49] * a * b * e * f + cc[50] * c * e * f + cc[51] * a * c * e * f + cc[52] * b * c * e * f + cc[53] * a * b * c * e * f + cc[54] * d * e * f + cc[55] * a * d * e * f + cc[56] * b * d * e * f + cc[57] * a * b * d * e * f + cc[58] * c * d * e * f + cc[59] * a * c * d * e * f + cc[60] * b * c * d * e * f + cc[61] * a * b * c * d * e * f;
}

struct ThreadData {
    double* a_his;
    double* b_his;
    double* c_his;
    double* d_his;
    double* e_his;
    double* f_his;
    double* ans_his;
    int start_index;
};

void* threadFunction(void* arg)
{
    ThreadData* data = static_cast<ThreadData*>(arg);
    for (int i = 0; i < ITERATIONS; ++i)
    {
        int index = data->start_index + i;
        double a = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        double b = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        double c = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        double d = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        double e = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        double f = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        data->a_his[index] = a;
        data->b_his[index] = b;
        data->c_his[index] = c;
        data->d_his[index] = d;
        data->e_his[index] = e;
        data->f_his[index] = f;
        data->ans_his[index] = calculate(a, b, c, d, e, f);
    }
    return nullptr;
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    double* a_his = new double[RUNS];
    double* b_his = new double[RUNS];
    double* c_his = new double[RUNS];
    double* d_his = new double[RUNS];
    double* e_his = new double[RUNS];
    double* f_his = new double[RUNS];
    double* ans_his = new double[RUNS];

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        thread_data[i] = {a_his, b_his, c_his, d_his, e_his, f_his, ans_his, i * ITERATIONS};
        pthread_create(&threads[i], nullptr, threadFunction, &thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(threads[i], nullptr);
    }

    std::ofstream outFile("output.txt");
    if (outFile.is_open())
    {
        for (int i = 0; i < RUNS; ++i)
        {
            outFile << a_his[i] << ", " << b_his[i] << ", " << c_his[i] << ", "
                    << d_his[i] << ", " << e_his[i] << ", " << f_his[i] << ", "
                    << ans_his[i] << "\n";
        }
        outFile.close();
    }
    else
    {
        std::cerr << "Unable to open file";
    }

    delete[] a_his;
    delete[] b_his;
    delete[] c_his;
    delete[] d_his;
    delete[] e_his;
    delete[] f_his;
    delete[] ans_his;

    return 0;
}