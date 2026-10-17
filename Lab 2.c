#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Person{
    char ime[20];
    char prezime[30];
    int godina;
    struct _Person *next;
}Person;

typedef struct _Person *position; //postavljanje pokazivača na strukturu

int insertAfter(position newPerson, position p){
    newPerson->next=p->next; //bitno!
    p->next=newPerson; //bitno!
    return 0;
}


int insertBegin(char* name, char* Lname, int year, position p){
    position newPerson = NULL; //novi pokazivač tipa position
    newPerson = (position)malloc(sizeof(Person));
    if(newPerson == NULL){
        printf("Greška prilikom alokacije memorije!");
        free(newPerson);
        return -1;
    }
    strcpy(newPerson->ime, name); //kopiranje
    strcpy(newPerson->prezime, Lname);
    newPerson->godina=year;
    newPerson->next=NULL;
    insertAfter(newPerson, p);   // spajanje novog cvora u listu pomocu insertAfter
    return 0;
}

position next;


int insertKraj(position newPerson, position p){
    while(p->next!=NULL){
        p=p->next;
    }
    insertAfter(newPerson,p);
    return 0;
}

position findLname(position p, char *Lastname){
    for(p=p->next;p!=NULL;p=p->next){
        if(strcmp(p->prezime, Lastname)==0){
            return p;
        }
    }
    return NULL;
}

int deletePerson(position head, char *Lastname){
    position prev = head;
    position curr = head->next;
    curr = findLname(prev, Lastname);
    if(curr == NULL){
        return -1; 
    }
    while(prev->next != curr){
        prev = prev->next;
    }
    prev->next=curr->next;
    free(curr);
    return 0;
}

int ispis(position p){
    p = p->next; // preskacemo head 
    if(p == NULL) {
        printf("Lista je prazna.\n");
        return 0;
    }
    while(p != NULL){
        printf("Ime: %s, Prezime: %s, Godina: %d\n", p->ime, p->prezime, p->godina);
        p = p->next;
    }
    return 0;
}
int main(){
    Person Head = {.ime={0},.prezime={0}, .godina={0}, .next=NULL}; //inicijaliziranje heada na nulu
    
    position p = &Head;
    return 0;
}