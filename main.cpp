#include <iostream>
#include <cmath>
#include <cstring>
#include <windows.h>
#include <chrono>
using namespace std;

//CONSTANTS
const int   SEQUENCES_QUANTITY = 6,
            ORDERED = 3,
            PART_ORDERED = 3,
            MIN_INT = -1000,
            MAX_INT = 1000,
            LENGTH = 3500000,
            INTERVAL_LENGTH = 5000;
const double    MIN_DOUBLE = -1000,
                MAX_DOUBLE = 1000;

//VARIABLES
int ArrayInt[LENGTH];
double ArrayDouble[LENGTH];

//GENERATING INTEGER SEQUENCES
void AscendingSequenceInt(int[], int);
void DescendingSequenceInt(int[], int);
void RandomSequenceInt(int[], int);
void SawSequenceInt(int[], int, int, int, int);
void SinSequenceInt(int[], int, int, int, int);
void StepSequenceInt(int[], int, int, int, int);

//GENERATING DOUBLE SEQUENCES
void AscendingSequenceDouble(double[], int);
void DescendingSequenceDouble(double[], int);
void RandomSequenceDouble(double[], int);
void SawSequenceDouble(double[], int, int, double, double);
void SinSequenceDouble(double[], int, int, double, double);
void StepSequenceDouble(double[], int, int, double, double);

//PRINTING SEQUENCES
void PrintArrConsoleInt(int[], int); 
void PrintArrFileInt(int[], int, FILE*, int64_t);
void PrintArrConsoleDouble(double[], int);
void PrintArrFileDouble(double[], int, FILE*, int64_t);

//POINTERS INTEGER FUNCTIONS
void (*funcInt1)(int[], int) = AscendingSequenceInt;
void (*funcInt2)(int[], int) = DescendingSequenceInt;
void (*funcInt3)(int[], int) = RandomSequenceInt;
void (*funcInt4)(int[], int, int, int, int) = SawSequenceInt;
void (*funcInt5)(int[], int, int, int, int) = SinSequenceInt;
void (*funcInt6)(int[], int, int, int, int) = StepSequenceInt;
void(*IntOrdered[ORDERED])(int[], int) ={funcInt1, funcInt2, funcInt3};
void(*IntPartOrdered[PART_ORDERED])(int[], int, int, int, int) ={funcInt4, funcInt5, funcInt6};

//POINTERS DOUBLE FUNCTIONS
void (*funcDouble1)(double[], int) = AscendingSequenceDouble;
void (*funcDouble2)(double[], int) = DescendingSequenceDouble;
void (*funcDouble3)(double[], int) = RandomSequenceDouble;
void (*funcDouble4)(double[], int, int, double, double) = SawSequenceDouble;
void (*funcDouble5)(double[], int, int, double, double) = SinSequenceDouble;
void (*funcDouble6)(double[], int, int, double, double) = StepSequenceDouble;
void(*DoubleOrdered[ORDERED])(double[], int) ={funcDouble1, funcDouble2, funcDouble3};
void(*DoublePartOrdered[PART_ORDERED])(double[], int, int, double, double) ={funcDouble4, funcDouble5, funcDouble6};

//ERROR HANDLERS
int ErrorHandler(int, int, double, double, int, int);
void PrintError(int);

//FILES
//INT
const char AscendingInt[] = "output/AscendingInt.txt";
const char DescendingInt[] = "output/DescendingInt.txt";
const char RandomInt[] = "output/RandomInt.txt";
const char SawInt[] = "output/SawInt.txt";
const char SinInt[] = "output/SinInt.txt";
const char StepInt[] = "output/StepInt.txt";
//DOUBLE
const char AscendingDouble[] = "output/AscendingDouble.txt";
const char DescendingDouble[] = "output/DescendingDouble.txt";
const char RandomDouble[] = "output/RandomDouble.txt";
const char SawDouble[] = "output/SawDouble.txt";
const char SinDouble[] = "output/SinDouble.txt";
const char StepDouble[] = "output/StepDouble.txt";
const char* FilesInt[6] = {AscendingInt, DescendingInt, RandomInt, SawInt, SinInt, StepInt};
const char* FilesDouble[6] = {AscendingDouble, DescendingDouble, RandomDouble, SawDouble, SinDouble, StepDouble};


int main(){
    setlocale(LC_ALL, "ru");
    int error = ErrorHandler(MIN_INT, MAX_INT, MIN_DOUBLE, MAX_DOUBLE, LENGTH, INTERVAL_LENGTH);
    if (error != 0){
        PrintError(error);
        return error;
    }

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < ORDERED; j++){
            if (i == 0){
                FILE *file = fopen(FilesInt[j], "w");

                auto begin = chrono::steady_clock::now(); 
                IntOrdered[j](ArrayInt, LENGTH);
                auto end = chrono::steady_clock::now();
                auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin);

                PrintArrFileInt(ArrayInt, LENGTH, file, elapsed_ms.count());
                fclose(file);
            } else{
                FILE *file = fopen(FilesDouble[j], "w");

                auto begin = chrono::steady_clock::now(); 
                DoubleOrdered[j](ArrayDouble, LENGTH);
                auto end = chrono::steady_clock::now();
                auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin);

                PrintArrFileDouble(ArrayDouble, LENGTH, file, elapsed_ms.count());
                fclose(file);
            }
        }
    }
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < PART_ORDERED; j++){
            if (i == 0){
                FILE *file = fopen(FilesInt[j + PART_ORDERED], "w");

                auto begin = chrono::steady_clock::now(); 
                IntPartOrdered[j](ArrayInt, LENGTH, INTERVAL_LENGTH, MIN_INT, MAX_INT);
                auto end = chrono::steady_clock::now();
                auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin);
                
                PrintArrFileInt(ArrayInt, LENGTH, file, elapsed_ms.count());
                fclose(file);
            } else{
                FILE *file = fopen(FilesDouble[j + PART_ORDERED], "w");

                auto begin = chrono::steady_clock::now(); 
                DoublePartOrdered[j](ArrayDouble, LENGTH, INTERVAL_LENGTH, MIN_DOUBLE, MAX_DOUBLE);
                auto end = chrono::steady_clock::now();
                auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin);

                PrintArrFileDouble(ArrayDouble, LENGTH, file, elapsed_ms.count());
                fclose(file);
            }
        }
    }
    
} 

//error handler
int ErrorHandler(int minInt, int maxInt, double minDouble, double maxDouble, int length, int intervalLength){
    if (maxInt < minInt) return 1;
    if (maxDouble < minDouble) return 2;
    if (length < 1) return 3;
    if (length < intervalLength) return 4;
    if (intervalLength < 1) return 5;
    return 0;
}

//print an error
void PrintError(int error){
    printf("ERROR: ");
    switch (error){
        case 1:
            printf("MIN_INT must be less then MAX_INT. error code: %d\n", error);
            break;
        case 2:
            printf("MIN_DOUBLE must be less then MAX_DOUBLE. error code: %d\n", error);
            break;
        case 3:
            printf("LENGTH must be greater then 0. error code: %d\n", error);
            break;
        case 4:
            printf("INTERVAL_LENGTH must be less then LENGTH. error code: %d\n", error);
            break;
        case 5:
            printf("INTERVAL_LENGTH must be greater then 0. error code: %d\n", error);
            break;
    }
}


//print int array to console
void PrintArrConsoleInt(int Array[], int len){
    if (len >= 100000){
        return;
    }
    for (int i = 0; i < len; i++){
        char end[3];
        if (i != len - 1){
            strcpy(end, ", ");
        } else{
            strcpy(end, "]\n");
        }
        printf("%d%s", Array[i], end);
    }
}

//print int array to file
void PrintArrFileInt(int Array[], int len, FILE *file, int64_t time){
    // fprintf(file, "Время работы алгоритма по формированию последовательности: %d(мкС)\n", time);
    fprintf(file, "%d(мкС)\n", time);
    if (len >= 100000){
        return;
    }
    for (int i = 0; i < len; i++){
        fprintf(file, "%d\n", Array[i]);
    }
    fprintf(file, "\n");
}

//generates an ascending integer sequence
void AscendingSequenceInt(int Array[], int len){
    double k = ((MAX_INT - MIN_INT) * 1.0) / (len * 1.0), b = MIN_INT;
    for (int i = 0; i < len; i++){
        Array[i] = k * i + b;
    }
}

//generates a descending integer sequence
void DescendingSequenceInt(int Array[], int len){
    double k = ((MAX_INT - MIN_INT) * -1.0) / (len * 1.0), b = MAX_INT;
    for (int i = 0; i < len; i++){
        Array[i] = k * i + b;
    }
}

//generates a random integer sequence
void RandomSequenceInt(int Array[], int len){
    srand(time(NULL));
    for (int i = 0; i < len; i++){
        Array[i] = MIN_INT + rand() % (MAX_INT - MIN_INT + 1);
    }
}

//generates a saw integer sequence
void SawSequenceInt(int Array[], int len, int intervalLen, int min, int max){
    double k = ((max - min) * 1.0) / (intervalLen * 1.0);
    for (int i = 0; i < len; i++){
        Array[i] = (int)(k * (i % intervalLen)) + min;
    }
}

//generates a sinusoidal integer sequence
void SinSequenceInt(int Array[], int len, int intervalLen, int min, int max){
    double x = 2 * M_PI / (intervalLen * 1.0);
    int k = (max - min) / 2;
    for (int i = 0; i < len; i++){
        Array[i] = k * sin(i * x) + min + k;
    }
}


//generates a step integer sequence
void StepSequenceInt(int Array[], int len, int intervalLen, int min, int max){
    int intMin, intMax, intCount, stepHigh;
    if (len % intervalLen == 0){
        intCount = len / intervalLen;
    } else{
        intCount = len / intervalLen + 1;
    }
    
    stepHigh = (max - min) / intCount;
    intMin = min;
    intMax = min + stepHigh;

    srand(time(NULL));
    for (int i = 0; i < len; i++){
        if (i > 0 && i < len - 1 && i % intervalLen == 0 &&  (i + 1) / intervalLen > 0){
            intMin = intMax;
            intMax += stepHigh;
        }
        Array[i] = rand() % (intMax - intMin + 1) + intMin;
    }
}


//print double array to console
void PrintArrConsoleDouble(double Array[], int len){
    if (len >= 100000){
        return;
    }
    for (int i = 0; i < len; i++){
        char end[3];
        if (i != len - 1){
            // end = ", ";
            strcpy(end, ", ");
        } else{
            strcpy(end, "]\n");
        }
        printf("%.3f%s", Array[i], end);
    }
}

//print double array to file
void PrintArrFileDouble(double Array[], int len, FILE *file, int64_t time){
    // fprintf(file, "Время работы алгоритма по формированию последовательности: %d(мкС)\n", time);
    fprintf(file, "%d(мкС)\n", time);
    if (len >= 100000){
        return;
    }
    for (int i = 0; i < len; i++){
        fprintf(file, "%.3f\n", Array[i]);
    }
    fprintf(file, "\n");
}


//generates an ascending double sequence
void AscendingSequenceDouble(double Array[], int len){
    double k = ((double)(MAX_DOUBLE - MIN_DOUBLE) - 0.125) / (double)(len), b = MIN_DOUBLE + 0.875;
    for (int i = 0; i < len; i++){
        Array[i] = k * i + b;
    }
}

//generates a descending double sequence
void DescendingSequenceDouble(double Array[], int len){
    double k = ((MAX_DOUBLE - MIN_DOUBLE - 0.125) * -1.0) / (len * 1.0), b = MAX_DOUBLE - 0.125;
    for (int i = 0; i < len; i++){
        Array[i] = k * i + b;
    }
}

//generates a random double sequence
void RandomSequenceDouble(double Array[], int len){
    srand(time(NULL));
    for (int i = 0; i < len; i++){
        Array[i] =  (double)(rand())/RAND_MAX * (MAX_DOUBLE - MIN_DOUBLE) + MIN_DOUBLE;
    }
}

//generates a saw double sequence
void SawSequenceDouble(double Array[], int len, int intervalLen, double min, double max){
    double k = (max - min) / (double)(intervalLen);
    for (int i = 0; i < len; i++){
        Array[i] = (double)(k * (i % intervalLen)) + min;
    }
}

//generates a sinusoidal double sequence
void SinSequenceDouble(double Array[], int len, int intervalLen, double min, double max){
    double x = 2 * M_PI / (intervalLen * 1.0);
    double k = (max - min) / (double)(2);
    for (int i = 0; i < len; i++){
        Array[i] = k * sin(i * x) + min + k;
    }
}


//generates a step double sequence
void StepSequenceDouble(double Array[], int len, int intervalLen, double min, double max){
    int intMin, intMax, intCount; 
    double stepHigh;
    if (len % intervalLen == 0){
        intCount = len / intervalLen;
    } else{
        intCount = len / intervalLen + 1;
    }
    
    stepHigh = (max - min) / (double)(intCount);
    intMin = min;
    intMax = min + stepHigh;

    srand(time(NULL));
    for (int i = 0; i < len; i++){
        if (i > 0 && i < len - 1 && i % intervalLen == 0 && (i + 1) / intervalLen > 0){
            intMin = intMax;
            intMax += stepHigh;
        }
        Array[i] =  (double)(rand())/RAND_MAX * (intMax - intMin) + intMin;
    }
}