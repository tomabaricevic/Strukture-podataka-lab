#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Polinom{
    int koef;
    int exp;
    struct Polinom *next;
} Polinom;

Polinom *dodPolinom(Polinom *head, int koef, int exp){
    if (koef == 0)                     //ako nema polinoma
        return head;
    Polinom *temp = head;
    Polinom *prev = NULL;
    while (temp != NULL && temp->exp > exp) {         //dodavanje polinoma 
        prev = temp;                                  //prebacivanje pokazivaca
        temp = temp->next;
    }
    if (temp != NULL && temp->exp == exp) {         //zbrajamo koeficijente sa istim exp
        temp->koef += koef;
        if (temp->koef == 0) {
            if (prev == NULL)
                head = temp->next; 
            else
                prev->next = temp->next;
            free(temp);
        }
        return head;
    }
    Polinom *newElem = (Polinom *)malloc(sizeof(Polinom));        //alociranje memorije za novi polinom
    if (newElem == NULL) {
        return head;
    }
    newElem->koef = koef;
    newElem->exp = exp; 
    newElem->next = temp;
    
    if (prev == NULL) {
        head = newElem;
    } else {
        prev->next = newElem;
    }

    return head;
}

int ispPolinom(Polinom *head){
    if(head == NULL){
        printf("0\n");
        return 0;
    }
    Polinom *temp = head;
    int prvi = 1;
    while(temp != NULL){
        if (temp->koef > 0 && !prvi) {               //ispisivanje polinoma
            printf(" + ");
        } else if (temp->koef < 0) {
            printf(" - ");
        }
        int absKoef = (temp->koef < 0) ? -temp->koef : temp->koef;
        if (temp->exp == 0) {
            printf("%d", absKoef);
        } else if (temp->exp == 1) {
            if (absKoef != 1) printf("%d", absKoef);
            printf("x");
        } else {
            if (absKoef != 1) printf("%d", absKoef);
            printf("x^%d", temp->exp);
        }
        prvi = 0;
        temp = temp->next;
    }
    printf("\n");
    return 0;
}

Polinom *freeD(Polinom *head){
    Polinom *temp;
    while (head != NULL)          //oslobadanje memorije
    {
        temp = head;
        head = head->next;
        free(temp);
    }
    return NULL;
}

Polinom *lcitajRed(FILE *file){
    Polinom *head = NULL;
    char redak[100];
    if (fgets(redak, sizeof(redak), file) == NULL)
        return NULL;
    char *p = redak;
    int koef, expVal, procitano; 
    while (sscanf(p, "%d %d%n", &koef, &expVal, &procitano) == 2){
        head = dodPolinom(head, koef, expVal);
        p += procitano;
    }
    return head;
}

int citajDoc(char *filename, Polinom **p1, Polinom **p2)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Greska: Nije moguce otvoriti datoteku %s\n", filename);
        return -1;
    }

    *p1 = lcitajRed(fp);
    *p2 = lcitajRed(fp);

    fclose(fp);
    return 0;
}

Polinom *zbroji(Polinom *a, Polinom *b){
    Polinom *rezultat = NULL;
    Polinom *temp = a;
    while (temp != NULL) {
        rezultat = dodPolinom(rezultat, temp->koef, temp->exp);
        temp = temp->next;
    }
    temp = b;
    while (temp != NULL){
        rezultat = dodPolinom(rezultat, temp->koef, temp->exp);
        temp = temp->next;
    }
    
    return rezultat;
}

Polinom *pomnozi(Polinom *a, Polinom *b){
    Polinom *rezultat = NULL;
    Polinom *tempA = a;
    while (tempA != NULL)
    {
        Polinom *tempB = b;
        while (tempB != NULL){
            rezultat = dodPolinom(rezultat, tempA->koef * tempB->koef, tempA->exp + tempB->exp);
            tempB = tempB->next;
        }
        tempA = tempA->next;
    }
    
    return rezultat;
}

int main(){
    Polinom *p1 = NULL, *p2 = NULL;

    if (citajDoc("polinom.txt", &p1, &p2) != 0)
    {
        return 1;
    }

    printf("P1 = ");
    ispPolinom(p1);
    printf("P2 = ");
    ispPolinom(p2);

    Polinom *zbroj = zbroji(p1, p2);
    Polinom *umnozak = pomnozi(p1, p2);

    printf("P1 + P2 = ");
    ispPolinom(zbroj);
    printf("P1 * P2 = ");
    ispPolinom(umnozak);

    freeD(p1);
    freeD(p2);
    freeD(zbroj);
    freeD(umnozak);

    return 0;
}