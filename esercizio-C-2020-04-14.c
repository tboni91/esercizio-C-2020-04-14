#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
è dato il tipo dati contact_type, dovrebbe servire ad implementare una rubrica telefonica molto semplice: 

#define NAME_LEN 64
#define PHONE_LEN 20

typedef struct {
   int id; // id numerico del contatto (valore univoco)
   char name[NAME_LEN + 1]; // nome della persona
   char phone[PHONE_LEN + 1]; // numero di telefono
} contact_type;

sono già date le seguenti funzioni (riutilizzare quelle già sviluppate):

// crea un oggetto di tipo contact_type e lo inizializza con name e phone
contact_type * create_contact(char * name, char * phone);

// scrive su stdout i contenuti dell'oggetto
void print_contact(contact_type * person);

******

scrivere le seguenti nuove funzioni e variabili:

#define ADDRESS_BOOK_SIZE 256

// la rubrica telefonica contiene al massimo 256 nominativi
contact_type * address_book[ADDRESS_BOOK_SIZE]; // global variable
// è un array di puntatori a contact_type
// se address_book[i] == NULL, vuole dire che la cella è utilizzabile per conservare l'indirizzo di un contatto


// confronta due contatti:
// due contatti sono uguali se e solo se c1->name è uguale a c2->name e c1->phone è uguale a c2->phone
// return value:
// 0: contatti uguali
// < 0: se *c1 è ordinato prima di *c2
// > 0: se *c1 è ordinato dopo di *c2
// ovvero FATE COME FA STRCMP (vedete man strcmp)
// NOTA BENE: se c1 == NULL or c2 == NULL, restituisce -1
int compare_contacts(contact_type * c1, contact_type * c2);


// aggiunge il contatto c all'array address_book array 
// la funzione NON controlla se il contatto è già presente; ma cerca la prima cella libero nell'array
// return value:
// >=0: posizione nell'array address_book dove è stato inserito c
// -1: errore (i.e. non c'è più spazio in address_book o c == NULL)
int add_to_address_book(contact_type * c);

// rimuovi il contatto c da address_book (setta a NULL la posizione dove si trova c)
// return value:
// >= 0: posizione dove si trovava c
// -1: non ho trovato c, quindi non ho cancellato nessun contatto
int remove_from_address_book(contact_type * c);


// cerca il contatto c nell'array address_book
// cercare un contatto: confronta c con ogni contatto memorizzato in address_book
// DOVETE USARE compare_contacts()
// return value:
// >= 0: posizione dove si trova il primo contatto uguale a c
// -1: contatto c non trovato
int search_in_address_book(contact_type * c);


// funzione che fa il sort dei contatti in address_book, utilizzando compare_contacts()
void sort_by_name();


scrivete un main() faccia le cose seguenti:

1 - creare gli oggetti di tipo contact_type a partire dai seguenti nominativi e numeri di telefono
ed inserirli in address_book utilizzando la funzione add_to_address_book

creare ed inserire in rubrica i contatti in questo ordine:

"dino","+391237"
"filippo", "+391239"
"barbara","+391235"
"antonio","+391234"
"enrico","+391238"
"chiara","+391236"

2 - cercare il contatto "antonio","+391234"
e se trovato, rimuoverlo

3 - creare ed aggiungere il contatto "pino","+399999"
e scrivere a video tutta la rubrica telefonica (non le celle vuote)

4 - aggiungere di nuovo dil contatto "antonio","+391234"

5 - fare il sort di tutta la rubrica

6 - scrivere a video tutta la rubrica telefonica (non le celle vuote)
il risultato deve essere ordinato 

FINE

*/

#define NAME_LEN 64
#define PHONE_LEN 20
#define ADDRESS_BOOK_SIZE 256

typedef
struct {
  int id; 						        // id numerico del contatto (valore univoco)
  char name[NAME_LEN + 1]; 		// nome della persona
  char phone[PHONE_LEN + 1]; 	// numero di telefono
} contact_type;

// GLOBAL VARIABLES

contact_type * address_book[ADDRESS_BOOK_SIZE];
int id_counter = 1;

// FUNCTIONS DECLARATION

contact_type * create_contact(char * name, char * phone);
void print_contact(contact_type * person);
int add_to_address_book(contact_type * c);
int compare_contacts(contact_type * c1, contact_type * c2);
int remove_from_address_book(contact_type * c);
int search_in_address_book(contact_type * c);
void sort_by_name();
void swap_contacts(int i, int j);

// MAIN

int main(int argc, char *argv[]) {
  int address_index = 0;

  contact_type * dino = create_contact("dino","+391237");
  contact_type * barbara = create_contact("barbara","+391235");
  contact_type * antonio = create_contact("antonio","+391234");
  contact_type * enrico = create_contact("enrico","+391238");
  contact_type * chiara = create_contact("chiara","+391236");

	if (dino == NULL || barbara == NULL || antonio == NULL || enrico == NULL || chiara == NULL) {
    printf("errore in create_contact!\n");
    exit(EXIT_FAILURE);
	}

  if ((address_index = add_to_address_book(dino)) == -1) {
    printf("rubrica piena, o contatto inesistente!\n");
    return EXIT_FAILURE;
  } else {
    printf("nuovo contatto inserito in posizione %d", address_index+1);
    print_contact(address_book[address_index]);
  }

  if ((address_index = add_to_address_book(barbara)) == -1) {
    printf("rubrica piena, o contatto inesistente!\n");
    return EXIT_FAILURE;
  } else {
    printf("nuovo contatto inserito in posizione %d", address_index+1);
    print_contact(address_book[address_index]);
  }

  if ((address_index = add_to_address_book(antonio)) == -1) {
    printf("rubrica piena, o contatto inesistente!\n");
    return EXIT_FAILURE;
  } else {
    printf("nuovo contatto inserito in posizione %d", address_index+1);
    print_contact(address_book[address_index]);
  }

  if ((address_index = add_to_address_book(enrico)) == -1) {
    printf("rubrica piena, o contatto inesistente!\n");
    return EXIT_FAILURE;
  } else {
    printf("nuovo contatto inserito in posizione %d", address_index+1);
    print_contact(address_book[address_index]);
  }

  if ((address_index = add_to_address_book(chiara)) == -1) {
    printf("rubrica piena, o contatto inesistente!\n");
    return EXIT_FAILURE;
  } else {
    printf("nuovo contatto inserito in posizione %d", address_index+1);
    print_contact(address_book[address_index]);
  }

  if (search_in_address_book(antonio) != -1) {
    if (remove_from_address_book(antonio) != -1)
      printf("contatto rimosso con successo!\n");
    else
      printf("contatto non trovato!\n");
  } else
    printf("contatto non trovato!\n");

  contact_type * pino = create_contact("pino","+399999");

  if ((address_index = add_to_address_book(pino)) == -1) {
    printf("rubrica piena, o contatto inesistente!\n");
    return EXIT_FAILURE;
  } else {
    printf("nuovo contatto inserito in posizione %d", address_index+1);
    print_contact(address_book[address_index]);
  }

  for (int i = 0; i < ADDRESS_BOOK_SIZE; i++) {
    if (address_book[i] != NULL)
      print_contact(address_book[i]);
  }

  if ((address_index = add_to_address_book(antonio)) == -1) {
    printf("rubrica piena, o contatto inesistente!\n");
    return EXIT_FAILURE;
  } else {
    printf("nuovo contatto inserito in posizione %d", address_index+1);
    print_contact(address_book[address_index]);
  }

  sort_by_name();

  for (int i = 0; i < ADDRESS_BOOK_SIZE; i++) {
    if (address_book[i] != NULL)
      print_contact(address_book[i]);
  }
  
	return 0;
}

// FUNCTIONS

/* crea un oggetto di tipo contact_type e lo inizializza con name e phone */
contact_type * create_contact(char * name, char * phone) {
	contact_type * new_contact = calloc(sizeof(contact_type), sizeof(char));

  if (new_contact == NULL) {
    return NULL;
  }

	unsigned int dim_name = strlen(name);
	unsigned int dim_phone = strlen(phone);

	if (dim_name > NAME_LEN) {
		return NULL;
	} else {
		strncpy(new_contact->name, name, dim_name);
	}

	if (dim_phone > PHONE_LEN) {
		return NULL;
	} else {
		strncpy(new_contact->phone, phone, dim_phone);
	}

	new_contact->id = id_counter++;

	return new_contact;
}

/* scrive su stdout i contenuti dell'oggetto */
void print_contact(contact_type * person) {
	printf("\t person: id = %d, name = '%s', phone = '%s'\n", person->id, person->name, person->phone);
}

/* aggiunge il contatto c all'array address_book array, la funzione NON controlla se il contatto è già presente, ma cerca la prima cella libero nell'array
return value:
- >=0: posizione nell'array address_book dove è stato inserito c
- -1: errore (i.e. non c'è più spazio in address_book o c == NULL) */
int add_to_address_book(contact_type * c) {
  if (c == NULL)
    return -1;
  
  for (int i = 0; i < ADDRESS_BOOK_SIZE; i++) {
    if (address_book[i] == NULL) {
      // collego l'id alla posizione in rubrica
      c->id = i+1;
      address_book[i] = c;
      return i;
    }
  }

  return -1;
}

/* confronta due contatti: due contatti sono uguali se e solo se 
c1->name è uguale a c2->name e c1->phone è uguale a c2->phone
return value:
- 0: contatti uguali
- < 0: se *c1 è ordinato prima di *c2
- > 0: se *c1 è ordinato dopo di *c2
 NOTA BENE: se c1 == NULL or c2 == NULL, restituisce -1 */
int compare_contacts(contact_type * c1, contact_type * c2) {
  if (c1 == NULL || c2 == NULL)
    return -1;

  
  switch (strcmp(c1->name, c2->name)) {
    case 0:
      switch (strcmp(c1->phone, c2->phone)) {
        case 0:
          return 0;
        default:
          if (c1->id > c2->id)
            return 2;
          else
            return -2;
      }
      break;
    default:
      if (c1->id > c2->id)
        return 2;
      else
        return -2;
  }
}

/* rimuovi il contatto c da address_book (setta a NULL la posizione dove si trova c)
return value:
- >= 0: posizione dove si trovava c
- -1: non ho trovato c, quindi non ho cancellato nessun contatto */
int remove_from_address_book(contact_type * c) {
  int position = search_in_address_book(c);

  if (position != -1) {
    address_book[position] = NULL;
  }

  return position;
}

/* cerca il contatto c nell'array address_book, per cercare un contatto: confronta c con ogni contatto memorizzato in address_book
return value:
- >= 0: posizione dove si trova il primo contatto uguale a c
- -1: contatto c non trovato */
int search_in_address_book(contact_type * c) {
  for (int i = 0; i < ADDRESS_BOOK_SIZE; i++) {
    if (compare_contacts(c, address_book[i]) == 0)
      return i;
  }
  
  return -1;
}

/* funzione che fa il sort dei contatti in address_book, utilizzando compare_contacts() */
void sort_by_name() {
  for (int i = 0; i < ADDRESS_BOOK_SIZE-1; i++) {
    for (int j = 0; j < ADDRESS_BOOK_SIZE-i-1; j++) {
      if (address_book[j] == NULL && address_book[j+1] != NULL)
        swap_contacts(j, j+1);
      else if (address_book[j] != NULL && address_book[j+1] != NULL)
        if (strcmp(address_book[j]->name, address_book[j+1]->name) > 0)
          swap_contacts(j, j+1);
    }
  }
}

void swap_contacts(int i, int j) {
  contact_type *t = address_book[i];
	address_book[i] = address_book[j];
	address_book[j] = t;

}
