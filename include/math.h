typedef struct
{
    float x;
    float y;
    float z;
} VERTEX;

#define PI 3.14159265358979
#define RANDMAX 32767
#define SUMLIMIT 50

#define abs(a) (((a) > 0) ? a : -(a))

int rand();
int sign(int x);
int floor(double x);

double sin(double x);
double cos(double x);
double tan(double x);

double sqrt(double x);
double exp2(double x);
double atan(double x);
double atan2(double x, double y);
double fabs(double x);
float pow(double base, int exp);

int ABS(int x);