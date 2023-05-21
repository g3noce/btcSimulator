#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

//[RAPPEL DE COMPILATION](pour Mingw en C) : gcc .\tradingBot.c -o .\tradingBot.exe

void tSma(float *ptrArrNumbers, float *ptrArrNumbers2, int length);

int crossover(float *ptrArrNumbers1, float *ptrArrNumbers2, int length1, int length2);
int crossunder(float *ptrArrNumbers1, float *ptrArrNumbers2, int length1, int length2);

void getFilePrice(float *ptrArrNumbers, int length);


//maths functions
void tSma(float *ptrArrNumbers, float *ptrArrNumbers2, int length){
    float sum = 0.0;
    int i = 1;
    for (i = 1; i <= length; ++i)
        sum += ptrArrNumbers[length-i];

    i = 0;
    for (i = 0; i < length; ++i)
        ptrArrNumbers2[i] = ptrArrNumbers2[i+1];
    ptrArrNumbers2[length-1] = sum / length;

	return;
    }


//choose functions
int crossover(float *ptrArrNumbers1, float *ptrArrNumbers2, int length1, int length2){
    float newClose1 = ptrArrNumbers1[length1-1];
    float ndClose1 = ptrArrNumbers1[length1-2];
    float newClose2 = ptrArrNumbers2[length2-1];
    if(ndClose1 <= newClose2 && newClose1 >= newClose2)
        return 1;
    else
        return 0;
    }
int crossunder(float *ptrArrNumbers1, float *ptrArrNumbers2, int length1, int length2){
    float newClose1 = ptrArrNumbers1[length1-1];
    float ndClose1 = ptrArrNumbers1[length1-2];
    float newClose2 = ptrArrNumbers2[length2-1];
    if(newClose1 <= newClose2 && ndClose1 >= newClose2)
        return 1;
    else
        return 0;
    }


//file function
void getFilePrice(float *ptrArrNumbers, int length){
    int i = 0;
    float btcPrice = {0.0};

    FILE* BTCUSD = fopen("BTC-USD.json", "r");

    for (int i = 0; i < length; ++i){
        ptrArrNumbers[i] = ptrArrNumbers[i+1];
        }
    if(BTCUSD != NULL){
        fscanf(BTCUSD,"%f", &btcPrice);
        ptrArrNumbers[length-1] = btcPrice;
    }
    else
        printf("Canno't access BTC-USD.json\n");
    fclose(BTCUSD);
    return;
    }


int main(int argc, char const *argv[]){
    system("wt powershell \"python.exe .\\downloadBtcData.py\"");
    float arrBTCPrice[74] = { 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 
        0.00, 0.00 }; // initialisat with BTC-USD.json file !!
    int countarrBTCPrice = sizeof(arrBTCPrice) / sizeof(float);
    if(countarrBTCPrice != 74){
        printf("Error : arrBTCPrice no total\n");
        return 0;
    }

        float arrSma5[5] = {0.00, 0.00, 0.00, 0.00, 0.00}; // initialisat with BTC-USD.json file !!
    int countarrSma5 = sizeof(arrSma5) / sizeof(float);
    if(countarrSma5 != 5){
        printf("Error : arrSma5 no total\n");
        return 0;
    }
        float arrSma74[74] = { 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 
        0.00, 0.00 }; // initialisat with BTC-USD.json file !!
    int countarrSma74 = sizeof(arrSma74) / sizeof(float);
    if(countarrSma74 != 74){
        printf("Error : arrSma74 no total\n");
        return 0;
    }

    getFilePrice(arrBTCPrice, countarrBTCPrice);
    float close = arrBTCPrice[countarrBTCPrice-1];
    tSma(arrBTCPrice, arrSma5, 5);
    tSma(arrBTCPrice, arrSma74, 74);

    int buyEntry = crossover(arrSma5,arrSma74,countarrSma5,countarrSma74);
    int sellEntry = crossunder(arrSma5,arrSma74,countarrSma5,countarrSma74);

    while(1){
        Sleep(1000);

        float btcPrice = {0.0};

        FILE* BTCUSD = fopen("BTC-USD.json", "r");

        fscanf(BTCUSD,"%f", &btcPrice);
        if (arrBTCPrice[countarrBTCPrice-1] != btcPrice){

            system("cls");
            countarrBTCPrice = sizeof(arrBTCPrice) / sizeof(float);
            if(countarrBTCPrice != 74){
                printf("Error : arrBTCPrice no total\n");
                return 0;
            }
            countarrSma5 = sizeof(arrSma5) / sizeof(float);
            if(countarrSma5 != 5){
                printf("Error : arrSma5 no total\n");
                return 0;
            }
            countarrSma74 = sizeof(arrSma74) / sizeof(float);
            if(countarrSma74 != 74){
                printf("Error : arrSma74 no total\n");
                return 0;
            }

            getFilePrice(arrBTCPrice, countarrBTCPrice);
            tSma(arrBTCPrice, arrSma5, 5);
            tSma(arrBTCPrice, arrSma74, 74);
            close = arrBTCPrice[countarrBTCPrice-1];

            buyEntry = crossover(arrSma5,arrSma74,countarrSma5,countarrSma74);
            sellEntry = crossunder(arrSma5,arrSma74,countarrSma5,countarrSma74);

            if(buyEntry == 1){
                system("wt powershell \"python.exe .\\buy.py\"");
            }
            if(sellEntry == 1){
                system("wt powershell \"python.exe .\\sell.py\"");
            }
            printf("current price : %.2f\n",close);
        }
        fclose(BTCUSD);
    }
	return 0;
}