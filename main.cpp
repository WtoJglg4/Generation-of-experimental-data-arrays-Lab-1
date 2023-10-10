#include <iostream>
#include <cmath>
using namespace std;

const int MIN = 10, MAX = 20, length = 50, intervalLen = 30;

//print array
void PrintArr(int Array[], int len){
    cout << "Array: \n[";
    for (int i = 0; i < len; i++){
        if (i != len - 1){
            cout << Array[i] << ", ";
        } else{
            cout << Array[i] << "]\n";
        }
    }
}

//generates an ascending sequence
void AscendingSequence(int Array[], int len){
    float k = ((MAX - MIN) * 1.0) / (len * 1.0), b = MIN;
    cout << k << endl;
    for (int i = 0; i < len; i++){
        Array[i] = k * i + b;
    }
}

//generates a descending sequence
void DescendingSequence(int Array[], int len){
    float k = ((MAX - MIN) * -1.0) / (len * 1.0), b = MAX;
    for (int i = 0; i < len; i++){
        Array[i] = k * i + b;
    }
}

//generates a descending sequence
void RandomSequence(int Array[], int len){
    srand(time(NULL));
    for (int i = 0; i < len; i++){
        Array[i] = MIN + rand() % (MAX - MIN + 1);
    }
}

//generates a sawtooth sequence
void SawSequence(int Array[], int len, int intervalLen, int min, int max){
    if (intervalLen == 0){
        cout << "ERROR: devision by zero";
        return;
    }
    float k = ((max - min) * 1.0) / (intervalLen * 1.0);
    int b = min;
    for (int i = 0; i < len; i++){
        // Array[i] = (int)(k * i) % b + b;
        Array[i] = ((int)(k * i)) % (max - min) + b;
    }
}

//generates a sinusoidal sequence
void SinSequence(int Array[], int len, int intervalLen, int min, int max){
    float x = 2 * M_2_PI / intervalLen;
    int k = (max - min) / 2;
    for (int i = 0; i < len; i++){
        Array[i] = k * sin(i * x) + min + k;
        //cout << Array[i] << " " << i * x << " " << sin(i * x) <<  endl;
    }
}

//generates a step sequence
void StepSequence(int Array[], int len, int intervalLen, int min, int max){
    int intMin, intMax, intCount, stepHigh;
    if (len % intervalLen == 0){
        intCount = len / intervalLen - 1;
    } else{
        intCount = len / intervalLen + 1;
    }
    stepHigh = (MAX - MIN) / intCount;
    intMin = MIN;
    intMax = MIN + stepHigh;

    srand(time(NULL));
    for (int i = 0; i < len; i++){
        if (i > 0 && i < len - 1 && (i + 1) % intervalLen == 0 ){
            intMin = intMax;
            intMax += stepHigh;
        }
        Array[i] = intMin + rand() % (intMax - intMin + 1);
        //cout << Array[i] << " " << i << " " << intMin << " " << intMax << endl;
    }
}

// const int MIN = 10, MAX = 20, length = 50, intervalLen = 10;

int main(){
    int A[length];
    // AscendingSequence(A, length);
    // PrintArr(A, length); 
    // DescendingSequence(A, length);
    // PrintArr(A, length); 
    // RandomSequence(A, length);
    // PrintArr(A, length); 
    // SawSequence(A, length, intervalLen, MIN, MAX);
    // PrintArr(A, length); 
    // SinSequence(A, length, intervalLen, MIN, MAX);
    // PrintArr(A, length);
    StepSequence(A, length, intervalLen, MIN, MAX);
    PrintArr(A, length);
} 
