#include <stdio.h>
#include <stdint.h>
#include <float.h>  //FLT_EPSILON

int main() {
    // int a;
    // a = UINT_MAX;
    // a = CHAR_BIT;
    // a++;
    printf("%d\n", sizeof(int));                        //4
    printf("%d\n", sizeof(float));                      //4
    printf("%d\n", sizeof(double));                     //8
    printf("%d\n", sizeof(int32_t));                    //4
    printf("%d\n", sizeof(int_fast8_t));                //1             można dać %lu zamiast %d żeby nie mieć uwagi o konwersji
    printf("%e %1.10f \n", FLT_EPSILON, FLT_EPSILON);   //1.192093e-07 0.0000001192
}