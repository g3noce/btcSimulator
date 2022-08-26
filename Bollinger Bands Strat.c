#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

//[RAPPEL DE COMPILATION](pour Mingw en C) : gcc .\tradingBot.c -o .\tradingBot.exe

float tSma(float *ptrArrNumbers, int length);
float stdev(float *ptrArrNumbers, int lengthStdev, int length);

int crossover(float *ptrArrNumbers, float upper, int count);
int crossunder(float *ptrArrNumbers, float lower, int count);
int cross(float *ptrArrNumbers,  float sma, int count);

void getFilePrice(float *ptrArrNumbers, int length);
//maths function

float tSma(float *ptrArrNumbers, int length){
    float sum = 0.0, sma;
    int i = 1;
    for (int i = 1; i <= length; ++i)
        sum += ptrArrNumbers[length-i];
    sma = sum / length;

	return sma;
    }
float stdev(float *ptrArrNumbers, int lengthStdev, int length){
    float sum = 0.0, sma, SD = 0.0;
    int i = 1;
    for(i = 1; i <= lengthStdev; ++i)
        sum += ptrArrNumbers[length-i];
    sma = sum / lengthStdev;

    for (i = 1; i <= lengthStdev; ++i)
        SD += pow(ptrArrNumbers[length-i] - sma, 2);
    SD = sqrt(SD / lengthStdev);
    return SD;
    }

int crossover(float *ptrArrNumbers, float upper, int length){
    float newClose = ptrArrNumbers[length-1];
    float ndClose = ptrArrNumbers[length-2];
    if(upper < ndClose && upper >= newClose)
        return 1;
    else
        return 0;
    }
int crossunder(float *ptrArrNumbers, float lower, int length){
    float newClose = ptrArrNumbers[length-1];
    float ndClose = ptrArrNumbers[length-2];
    if(lower > ndClose && lower <= newClose)
        return 1;
    else
        return 0;
    }
int cross(float *ptrArrNumbers, float sma, int length){
    float newClose = ptrArrNumbers[length-1];
    float ndClose = ptrArrNumbers[length-2];
    if(sma < newClose && sma >= ndClose)
        return 1;
    else if(sma > newClose && sma <= ndClose)
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
    int length = 27;
    int lengthStdev = 24;
    float arrBTCPrice[27] = { 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00 };
        
    int count = sizeof(arrBTCPrice) / sizeof(float);
    if(count!=27){
        printf("Error : arrBTCPrice no total\n");
        return 0;
    }
    
    getFilePrice(arrBTCPrice, length);

	float sma = tSma(arrBTCPrice, length);
	float dev = stdev(arrBTCPrice, lengthStdev, length);
	float upper = sma + dev;
	float lower = sma - dev;
    float close = arrBTCPrice[length-1];

    int buyEntry = crossover(arrBTCPrice, upper, length);
    int sellEntry = crossunder(arrBTCPrice, lower, length);

    while(1){
        Sleep(1000);

        float btcPrice = {0.0};

        FILE* BTCUSD = fopen("BTC-USD.json", "r");

        fscanf(BTCUSD,"%f", &btcPrice);
        if (arrBTCPrice[length-1] != btcPrice){
            system("cls");
            count = sizeof(arrBTCPrice) / sizeof(float);
            if(count!=27){
                printf("Error : arrBTCPrice no total\n");
                return 0;
            }
            getFilePrice(arrBTCPrice, length);
            sma = tSma(arrBTCPrice, length);
            dev = 1.5 * stdev(arrBTCPrice, lengthStdev, length);
            upper = sma + dev;
            lower = sma - dev;
            close = arrBTCPrice[length-1];

            buyEntry = crossunder(arrBTCPrice, lower, length);
            sellEntry = crossover(arrBTCPrice, upper, length);

            if(buyEntry == 1){
                system("wt powershell buy");
                system("wt powershell \"python.exe .\\buy.py\"");
            }
            if(sellEntry == 1){
                system("wt powershell sell");
                system("wt powershell \"python.exe .\\sell.py\"");
            }

            printf("sma : %f\ndev : %f\nupper : %.2f\nlower : %.2f\ncurrent price : %.2f\n", sma, dev, upper, lower, close);
        }
        fclose(BTCUSD);
    }
	return 0;
}
