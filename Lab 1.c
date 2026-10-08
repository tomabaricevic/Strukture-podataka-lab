#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define LEN 50
#define FNO -1
#define max_br_bodova 100

typedef struct _Student{
    char name[LEN];
    char Lname[50];
    int bodovi;
}stud;
int main(){
    char buffer[LEN] = {0};           //inicijalizacija niza charova u u koji spremamo podatke te postavljanje svih clanova na 0
    int brojac = 0;
    FILE *fp = fopen("popis.txt", "r");
    if(fp == NULL){
        printf("Nemoguće otvoriti datoteku!");
        return FNO;
    }
    while(!feof(fp)){              //petlja se ponavlja dok program ne učita kraj datoteke
        fgets(buffer,LEN,fp);      //podatci o studentu spremaju se u buffer 
        brojac++;
    }
    rewind(fp);                    //vracamo pokazivac na pocetak
    stud* studenti = NULL;         //pokazivač na strukturu postavljamo na NULL
    studenti=(stud*)malloc(brojac*sizeof(stud));         //alokacija memorije za potreban broj studenata
    if(studenti == NULL){
        printf("Neuspješna alokacija memorije!");
        free(studenti);
        fclose(fp);
        return FNO;
    }
    for(int i=0;i<brojac;i++){
        fscanf(fp, "%s %s %d", studenti[i].name, studenti[i].Lname, &studenti[i].bodovi);      //upisivanje podataka iz datoteke u strukturu
    }
    float relativan_br_bodova;
    printf("IME           PREZIME         APSOLUTNI BROJ BODOVA        RELATIVAN BROJ BODOVA");
    for(int i=0;i<brojac;i++){
        relativan_br_bodova= ((float)studenti[i].bodovi/max_br_bodova)*100;       //bodove stavljamo kao float da nam rezultat ne bi vratio 0
        printf("%s %12s %24d %36f \n", studenti[i].name, studenti[i].Lname, studenti[i].bodovi, relativan_br_bodova);
    }

    fclose(fp);
    free(studenti);
    return 0;
}