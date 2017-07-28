#ifndef LIST_H
#define LIST_H

/*!
 * \struct listNode
 * \brief Typ bazowy listy dwukierunkowej
 *
 * Wykorzystywana jako bufer do zapisu kodów przy przechodzeniu przez drzewo.
 */

struct listNode {
  char code; /**< Pole zawierające kod '0' bądz '1' zależności od kierunku
                  przechodzenia przez drzewo */
  struct listNode *prev; /**< Adres poprzedniego elementu listy */
  struct listNode *next; /**< Adres następnego elementu listy */
};

/*!
 * \struct list_pointers
 * \brief Struktura wskaźników do listy
 *
 * Tworzymy listę dwustronną, aby ułatwić odczyt kodów.
 */

struct listPointers {
  struct listNode *head; /**< Adres czoła listy */
  struct listNode *tail; /**< Adres ogona listy */
};

/*!
 * \fn void createList(struct list_pointers *list)
 * \brief Funkcja tworząca listę
 *
 * \param struct list_pointers *list - wskaźnik do struktury wskaźników na listę
 *
 * Funkcja tworzy pierwszy element listy i ustawia wskaźniki head i tail na nowo powstały element, oraz
 * wskaźniki next i prev na NULL.
 */

void createList(struct listPointers *list);

/*!
 * \fn insertListNode(struct list_pointers *list)
 * \brief Dodanie elementu do listy
 *
 * \param struct list_pointers *list - wskaźnik do struktury wskaźników na listę
 *
 * Jeśli lista nie jest pusta, funkcja dodaje nowy element listy do jej czoła.
 */

void insertListNode(struct listPointers *list);

/*!
 * \fn void deleteListNode(struct list_pointers **list)
 * \brief Funkcja usuwająca element listy
 *
 * \param struct list_pointers **list - podwójny wskaźnik do struktury wskaźników
 * na listę
 *
 * Funckja usuwa ostatnio dodany do listy element pod warunkiem, że lista nie jest
 * pusta.
 */

void deleteListNode(struct listPointers **list);

#endif