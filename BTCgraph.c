#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>

#include <windows.h>
#include <urlmon.h>

//[RAPPEL DE COMPILATION](pour Mingw en C) : gcc BTCgraph.c -o BTCgraph.exe -lurlmon -lwininet

void getBTCInfos();
void tNow();
void downloadBtcPrice();
void getFilePrice();
void printBoard();
void printPrice();

/*void printBoard(){

	FILE* BTCUSD = NULL;

	float btcPrice = 0;
	
	BTCUSD =  fopen("response.json","r");
	if(BTCUSD !=NULL){
		fscanf(BTCUSD,"%*[^:]:%*[^:]:%*[^:]:%*[^:]:\"%f", &btcPrice);
	}
	else{
		printf("Canno't access BTC-USD.json\n");
	}

	printf("BTC PRICE IN USD : %.2f\n\n    ----##--##-----\n    ############---\n    --###########--\n    --###-----####-\n    --###------###-\n    --###-----###--\n    --#########----\n    --############-\n    --###------####\n    --###------####\n    --############-\n    ############---\n    ----##--##-----\n", btcPrice);
	

	fclose(BTCUSD);
	return;
	}*/

void tNow(){

	time_t now = time(NULL);
	struct tm *timeInfos = localtime(&now);

	printf("The time is : %02d:%02d:%02d\n\n"
		, timeInfos->tm_hour, timeInfos->tm_min, timeInfos->tm_sec);

	return;
	}
void getBTCInfos(){

	time_t now = time(NULL);
	struct tm *timeInfos = localtime(&now);

	float btcPrice = {1.0};

	FILE* response = NULL;
	FILE* BTCUSD = NULL;

	downloadBtcPrice();
	response = fopen("response.json", "r");
	BTCUSD = fopen("BTC-USD.json", "a");
	if(response != NULL){
		fscanf(response,"%*[^:]:%*[^:]:%*[^:]:%*[^:]:\"%f", &btcPrice);
        printf("%f\n",btcPrice );
		if (BTCUSD != NULL){
			fprintf(BTCUSD, "USD:%.2f\n",btcPrice);
		}
		else{
			printf("Canno't access BTC-USD.json\n");
		}
	}
	else{
		printf("Canno't access response.json\n");
	}
	fclose(response);
	fclose(BTCUSD);
	return;
	}
void downloadBtcPrice(){
	int btcPrice = 100000;

	TCHAR url[] = TEXT("https://api.coinbase.com/v2/prices/spot?currency=USD");
	TCHAR loc[] = TEXT("D:\\Data\\prog\\C\\btcSimulator\\response.json");
	
    if(URLDownloadToFile(0, url, loc, 0, 0))
    {
        printf("\nEchec URLDownloadToFile() !\n");
        return;
    }

	return;
	}

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

void printMap(char *matrice, const int ml, const int mc){
	int x=0,y=0;
	for(x=0;x<ml;++x){
		for(y=0;y<mc;++y){
			if(*(matrice+x*mc+y)==1)
				printf("\033[32;105m  \033[0;0m",x,y);
			else
				printf("\033[0m  \033[0m",x,y);
		}
		printf("\n");
	}
}
void printPrice(float *pntArrBTCPrice,const int length){
	for (int i = 0; i < length; ++i){
		if (&pntArrBTCPrice[i]!=NULL){
			printf("%.2f\n",pntArrBTCPrice[i]);
		}
	}
}


int main(int argc, char const *argv[]){
//printBoard();
const int nbL = 10, nbC = 30;
char map[10][30]={{1}};
float arrBTCPrice[10] = {1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 0.00};
       
int count = sizeof(arrBTCPrice) / sizeof(float);
if(count!=10){
    printf("Error : arrBTCPrice no total\n");
    return 0;
}


//getFilePrice(arrBTCPrice, nbL);
printPrice(arrBTCPrice,nbL);

//printMap(&map[0][0],nbL,nbC);


	/*
int balance = 1000; // fictif money for simulate buy or sell

	time_t now = time(NULL);
	struct tm *timeInfos = localtime(&now);

	do{
		if(timeInfos->tm_min == 0){
			getBTCInfos();
		}

		tNow();

		Sleep(1000);

		system("cls");

	}while(1);/*
*/
	
	return 0;
}

