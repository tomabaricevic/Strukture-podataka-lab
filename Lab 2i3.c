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


int insertBegin(char* ime, char* prezime, int godina, position head){
    position newPerson = NULL; //novi pokazivač tipa position
    newPerson = (position)malloc(sizeof(Person));
    if(newPerson == NULL){
        printf("Greška prilikom alokacije memorije!");
        free(newPerson);
        return -1;
    }
    strcpy(newPerson->ime, ime); //kopiranje
    strcpy(newPerson->prezime, prezime);
    newPerson->godina=godina;
    newPerson->next=NULL;
    insertAfter(newPerson, head);   // spajanje novog cvora u listu pomocu insertAfter
    return 0;
}

int insertEnd(position newPerson, position p){
    while(p->next!=NULL){
        p=p->next;
    }
    insertAfter(newPerson,p);
    return 0;
}

position findLname(position p, char *prezime){
    for(p=p->next;p!=NULL;p=p->next){
        if(strcmp(p->prezime, prezime)==0){
            return p;
        }
    }
    return NULL;
}

int deletePerson(position head, char *prezime){
    position prev = head;
    position curr = head->next;
    curr = findLname(prev, prezime);
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
int insertKraj(char* trazenoPrezime, char* ime, char* prezime, int godina, position p) {
   
    position target = findLname(p,trazenoPrezime);

    if (target == NULL) {
        printf("Osoba s prezimenom %s nije pronađena\n", trazenoPrezime);
        return -1;
    }

    position newPerson = (position)malloc(sizeof(Person));
    if (newPerson == NULL) {
        return -1;
    }
    strcpy(newPerson->ime, ime);
    strcpy(newPerson->prezime, prezime);
    newPerson->godina = godina;

    newPerson->next = target->next;
    target->next = newPerson;

    return 0;
}
int insertPrije(char* trazenoPrezime, char* ime, char* prezime, int godina, position p) {
    position prev = p;
    position curr = p->next;
    while (curr != NULL && strcmp(curr->prezime, trazenoPrezime) != 0) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        return -1;
    }
    position newPerson = (position)malloc(sizeof(Person));
    if (newPerson == NULL) {
        printf("Greška prilikom alokacije memorije!\n");
        return -1;
    }
    strcpy(newPerson->ime, ime);
    strcpy(newPerson->prezime, prezime);
    newPerson->godina = godina;
    newPerson->next = curr;
    prev->next = newPerson;

    return 0;
}
int sortList(position head) {
	if (!head->next) {
		printf("Lista je prazna");
		return -1;
	}

	int n = 0;
	Person* prev = head;

	while (prev->next) {
		n++;
		prev = prev->next;
	}

	for (int i=0;i <n-1;i++) {
		prev = head;
		Person* curr = head->next;
		for (int j=0;j<n-1-i;j++) {
			int resultLastName = strcmp(curr->prezime, curr->next->prezime);
			int resultName = strcmp(curr->ime, curr->next->ime);
			if ((resultLastName > 0) ||
				(resultLastName == 0 && resultName > 0)) {
				Person* temp = curr->next; // 1. Spremimo sljedeci cvor u privremenu varijablu
                prev->next = temp;         // 2. Prethodni cvor sada pokazuje na temp umjesto na curr
                curr->next = temp->next;   // 3. Curr sada preskace temp i pokazuje na ono sto je bilo iza tempa
                temp->next = curr;         // 4. Temp sada pokazuje na curr (cvorovi su zamijenili mjesta)
                prev = temp;               // 5. Azuriramo prev da ostane ispred curr-a za sljedeci korak
			}
			else {
				prev = curr;
				curr = curr->next;
			}
		}
	}

	return 0;
}
int citajDat(char *imeDat, position head){
    	FILE* fp = fopen(imeDat, "r");
	if (!fp) {
		return -1;
	}
    Person temp;
    int brojac;
    	while (fscanf(fp, "%s %s %d", temp.ime, temp.prezime, &temp.godina) == 3) {
		insertEnd(temp.ime, temp.prezime, temp.godina, head);
		brojac++;
	}
    if(brojac == 0){
        fclose(fp);
        return -1;
    }
    fclose(fp);

}
int pisiDat(char *imeDat, position head){
    FILE *fp;
    fp= fopen(imeDat, "w");
    if(!fp){
        return -1;
    }
    Person* curr = head->next;
    while (curr) {
		if (fprintf(fp, "%s %s %d\n", curr->ime, curr->prezime, curr->godina) <= 0) {
			fclose(fp);
			return -1;
		}
		curr = curr->next;
	}

	fclose(fp);

	return 0;
}
int main(){
    Person Head = {.ime={0},.prezime={0}, .godina={0}, .next=NULL}; //inicijaliziranje heada na nulu
    
    position p = &Head;
    return 0;
}