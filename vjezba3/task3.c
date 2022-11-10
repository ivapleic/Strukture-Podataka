/*
2. Definirati strukturu osoba(ime, prezime, godina rodenja) i napisati program koji :
    A.  dinamicki dodaje novi element na pocetak liste,
    B.  ispisuje listu,
    C.  dinamicki dodaje novi element na kraj liste,
    D.  pronalazi element u listi(po prezimenu),
    E.  brise odredeni element iz liste,
   U zadatku se ne smiju koristiti globalne varijable.
3. Prethodnom zadatku dodati funkcije:
    F. dinamicki dodaje novi element iza odredenog elementa,
    G. dinamicki dodaje novi element ispred odredenog elementa,
    H. sortira listu po prezimenima osoba,
    I. upisuje listu u datoteku,
    J. cita listu iz datoteke.
*/

#define CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
//#include <unistd.h>
#define MAX_SIZE (50)

struct _person;
typedef struct _person* PersonP;
typedef struct _person
{
    char firstName[MAX_SIZE];
    char lastName[MAX_SIZE];
    int birthYear;
    PersonP next;
} Person;

// 2nd Task
int PrintMenu();
int EnterValidString(char* string, char* variableName);
int AddFirst(PersonP head, char* firstName, char* lastName, int birthYear);
PersonP CreatePerson(char* firstName, char* lastName, int birthYear);
int InsertAfter(PersonP position, PersonP newPerson);
int AddLast(PersonP head, char* firstName, char* lastName, int birthYear);
PersonP FindLast(PersonP head);
int FindByLastName(PersonP first, char* lastName);
int DeleteAfter(PersonP head, char* lastName);
int PrintList(PersonP head);
int DeleteList(PersonP head);
// 3rd Task
int InsertAfterCertainEl(PersonP head, PersonP newPerson, char* findLastName);
int InsertBeforeCertainEl(PersonP head, PersonP newPerson, char* findLastName);
int SortList(PersonP head);
int WriteInFile(PersonP head, char* fileName);
int ReadListFromFile(PersonP head, char* fileName);
char* EnterFileName();

int main()
{
    Person head = { .firstName = {0}, .lastName = {0}, .birthYear = 0, .next = NULL };
    PersonP p = &head;
    char firstName[MAX_SIZE] = { 0 };
    char lastName[MAX_SIZE] = { 0 };
    char searchLastName[MAX_SIZE] = { 0 };
    int birthYear = 0;
    int choice = -1;
    int flag;
    PersonP newPerson = NULL;
    char* fileName = NULL;

    while (choice != 0)
    {
        system("cls");
        PrintMenu();
        printf("Choose an option from menu: ");
        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            printf(
                "=================================================================\n"
                "You chose to add new person to the beginning of list.\n\n"
                "Please enter person's first name: ");
            scanf(" %s", firstName);
            EnterValidString(firstName, "first name");
            printf("Please enter person's last name: ");
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            printf("Please enter person's birth year: ");
            scanf(" %d", &birthYear);
            AddFirst(p, firstName, lastName, birthYear);
            printf(
                "\nNew person is successfully added to the beginning of list!\n\n"
                "Press enter to continue app execution.\n"
                "=================================================================\n");
            system("pause");
            break;

        case 2:
            printf(
                "=================================================================\n"
                "You chose to add new person to the end of list.\n\n"
                "Please enter person's first name: ");
            scanf(" %s", firstName);
            EnterValidString(firstName, "first name");
            printf("Please enter person's last name: ");
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            printf("Please enter person's birth year: ");
            scanf(" %d", &birthYear);
            AddLast(p, firstName, lastName, birthYear);
            printf(
                "\nPerson is successfully added to the end of list!\n\n"
                "Press enter to continue app execution.\n"
                "=================================================================\n");
            system("pause");
            break;

        case 3:
            printf(
                "=================================================================\n"
                "You chose to search for a person by their last name.\n\n"
                "Please enter person's last name: ");
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            FindByLastName(p, lastName);
            printf(
                "\nPress enter to continue app execution.\n"
                "=================================================================\n");
            system("pause");
            break;

        case 4:
            printf(
                "=================================================================\n"
                "You chose to delete existing person.\n\n"
                "Please enter person's last name: ");
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            DeleteAfter(p, lastName);
            printf(
                "\nPress enter to continue app execution.\n"
                "=================================================================\n");
            system("pause");
            break;

        case 5:
            printf(
                "=================================================================\n"
                "You chose to print current person list:\n\n");
            PrintList(p);
            printf(
                "\n\nPress enter to continue app execution.\n"
                "=================================================================\n");
            system("pause");
            break;

        case 6:
            printf(
                "=================================================================\n"
                "You chose to insert new person after certain person (by surname).\n\n"
                "Enter last name of person in the list, after who you want to add new person: ");
            scanf(" %s", searchLastName);
            EnterValidString(searchLastName, "searched last name");

            printf("Please enter new person's first name: ");
            scanf(" %s", firstName);
            EnterValidString(firstName, "first name");
            printf("Please enter new person's last name: ");
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            printf("Please enter new person's birth year: ");
            scanf(" %d", &birthYear);
            newPerson = CreatePerson(firstName, lastName, birthYear);
            flag = InsertAfterCertainEl(p, newPerson, searchLastName);
            if (flag == EXIT_SUCCESS)
                printf(
                    "\nPerson is succesfully added after certain person in the list!\n\n"
                    "\nPress enter to continue app execution.\n"
                    "=================================================================\n");
            else
                printf(
                    "\nPerson with searched last name doesn't exist in the list!\n"
                    "Please choose another option.\n\n"
                    "Press enter to continue app execution.\n"
                    "=================================================================\n");
            system("pause");
            break;

        case 7:
            printf(
                "=================================================================\n"
                "You chose to insert new person before certain person (by surname).\n\n"
                "Enter last name of person in the list, before who you want to add new person: ");
            scanf(" %s", searchLastName);
            EnterValidString(searchLastName, "searched last name");

            printf("Please enter new person's first name: ");
            scanf(" %s", firstName);
            EnterValidString(firstName, "first name");
            printf("Please enter new person's last name: ");
            scanf(" %s", lastName);
            EnterValidString(lastName, "last name");
            printf("Please enter new person's birth year: ");
            scanf(" %d", &birthYear);
            newPerson = CreatePerson(firstName, lastName, birthYear);
            flag = InsertBeforeCertainEl(p, newPerson, searchLastName);
            if (flag == EXIT_SUCCESS)
                printf(
                    "\nPerson is succesfully added after certain person in the list!\n\n"
                    "\nPress enter to continue app execution.\n"
                    "=================================================================\n");
            else
                printf(
                    "\nPerson with searched last name doesn't exist in the list!\n"
                    "Please choose another option.\n\n"
                    "Press enter to continue app execution.\n"
                    "=================================================================\n");
            system("pause");
            break;

        case 8:
            printf(
                "=================================================================\n"
                "You chose to sort the list of people(by surname):\n\n");
            SortList(p);
            printf(
                "\nList has been successfully sorted!\n\n"
                "\nPress enter to continue app execution.\n"
                "=================================================================\n");
            system("pause");
            break;

        case 9:
            printf(
                "=================================================================\n"
                "You chose to insert the list of people in the file:\n\n");
            fileName = EnterFileName();
            flag = WriteInFile(p, fileName);
            if (flag == EXIT_SUCCESS)
                printf("\nList has been successfully added to the file : %s\n\n", fileName);
            printf("\nPress enter to continue app execution.\n"
                   "=================================================================\n");
            system("pause");
            break;

        case 10:
            printf(
                "=================================================================\n"
                "You chose to read the list of people from the file:\n\n");
            fileName = EnterFileName();
            flag = ReadListFromFile(p, fileName);
            if (flag == EXIT_SUCCESS)
                printf("\nList has been sucesfully read from the file : %s\n\n", fileName);
            printf("\nPress enter to continue app execution.\n"
                   "=================================================================\n");
            system("pause");
            break;

            system("cls");
            printf(
                "=================================================================\n"
                "\nYou have exited the application!\n\n"
                "=================================================================\n");
            DeleteList(p);
            if (p->next == NULL)
                printf("\nList is successfully deleted!\n\n");
            system("pause");

            return EXIT_SUCCESS;
        }
    }
}

int PrintMenu()
{
    printf(
        "=================================================================\n"
        "\t\t\tMENU\n"
        "=================================================================\n"
        "    1  -  Add new person to the beginning of list\n"
        "    2  -  Add new person to the end of list\n"
        "    3  -  Find person (search by last name)\n"
        "    4  -  Delete certain person\n"
        "    5  -  Print current person list\n"
        "    6  -  Insert new person after certain person (by surname)\n"
        "    7  -  Insert new person before certain person (by surname)\n"
        "    8  -  Sort the list of people (by surname)\n"
        "    9  -  Insert the list in the file\n"
        "    10 -  Read the list from the file\n "
        "   0  -  Exit application\n"
        "=================================================================\n");

    return EXIT_SUCCESS;
}

int EnterValidString(char* string, char* variableName)
{
    if (strcmp(string, "") != 0)
        return EXIT_SUCCESS;
    else
    {
        scanf(" %s", string);
        while (strcmp(string, "") == 0)
        {
            printf(
                "You entered an empty string!\n"
                "Please enter new %s: ",
                variableName);
            scanf(" %s", string);
        }

        return EXIT_SUCCESS;
    }
}

int AddFirst(PersonP head, char* firstName, char* lastName, int birthYear)
{
    PersonP newPerson = NULL;
    newPerson = CreatePerson(firstName, lastName, birthYear);
    if (!newPerson)
    {
        printf("Memory not allocated!\n");
        return EXIT_FAILURE;
    }
    InsertAfter(head, newPerson);

    return EXIT_SUCCESS;
}

PersonP CreatePerson(char* firstName, char* lastName, int birthYear)
{
    PersonP newPerson = NULL;
    newPerson = (PersonP)malloc(sizeof(Person));

    if (!newPerson)
    {
        printf("Memory not allocated!\n");
        return NULL;
    }
    strcpy(newPerson->firstName, firstName);
    strcpy(newPerson->lastName, lastName);
    newPerson->birthYear = birthYear;
    newPerson->next = NULL;

    return newPerson;
}

int InsertAfter(PersonP position, PersonP newPerson)
{
    newPerson->next = position->next;
    position->next = newPerson;

    return EXIT_SUCCESS;
}

int AddLast(PersonP head, char* firstName, char* lastName, int birthYear)
{
    PersonP newPerson = NULL;
    PersonP lastPerson = NULL;
    newPerson = CreatePerson(firstName, lastName, birthYear);
    if (!newPerson)
    {
        printf("Memory not allocated!\n");
        return EXIT_FAILURE;
    }
    lastPerson = FindLast(head);
    InsertAfter(lastPerson, newPerson);

    return EXIT_SUCCESS;
}

PersonP FindLast(PersonP head)
{
    PersonP temp = head;
    while (temp->next)
    {
        temp = temp->next;
    }
    return temp;
}

int FindByLastName(PersonP first, char* lastName)
{
    int flag = 0;
    PersonP temp = NULL;
    for (temp = first->next; temp != NULL; temp = temp->next)
    {
        if (strcmp(temp->lastName, lastName) == 0)
        {
            flag++;
            if (flag == 1)
                printf("\nPerson/s with searched last name is/are:\n");

            printf("FIRST NAME: %s, LAST NAME: %s, BIRTH YEAR: %d\n", temp->firstName, temp->lastName, temp->birthYear);
        }
    }
    if (flag == 0)
        printf("\nPerson with searched last name currently doesn't exist in the list!\n");

    return EXIT_SUCCESS;
}

int DeleteAfter(PersonP head, char* lastName)
{
    int flag = 0;
    PersonP prev = NULL;
    PersonP current = NULL;

    for (prev = head; prev->next != NULL; prev = prev->next)
    {
        if (strcmp(prev->next->lastName, lastName) == 0)
        {
            flag++;
            current = prev->next;
            prev->next = prev->next->next;
            free(current);
            break;
        }
    }
    if (flag == 0)
        printf("\nPerson with searched last name doesn't exist in current person list!\n");
    else
        printf("\nPerson is succesfully deleted from person list!\n");

    return EXIT_SUCCESS;
}

int PrintList(PersonP head)
{
    PersonP q = head->next;
    printf("| First name          || Last name          || Birth year \n");
    printf("-----------------------------------------------------------\n");
    for (q = head->next; q != NULL; q = q->next)
        printf("| %-20s || %-20s || %d\n", q->firstName, q->lastName, q->birthYear);

    return EXIT_SUCCESS;
}

int DeleteList(PersonP head)
{
    PersonP temp = NULL;
    while (head->next != NULL)
    {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    return EXIT_SUCCESS;
}

int InsertAfterCertainEl(PersonP head, PersonP newPerson, char* findLastName)
{
    int flag = 0;
    PersonP temp = NULL;
    temp = head;
    while (temp->next != NULL)
    {
        if (strcmp(temp->lastName, findLastName) == 0)
        {
            flag++;
            InsertAfter(temp, newPerson);
        }
        temp = temp->next;
    }
    if (flag == 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int InsertBeforeCertainEl(PersonP head, PersonP newPerson, char* findLastName)
{
    int flag = 0;
    PersonP temp = NULL;
    temp = head;
    while (temp->next != NULL)
    {
        if (strcmp(temp->next->lastName, findLastName) == 0)
        {
            flag++;
            InsertAfter(temp, newPerson);
            break;
        }
        temp = temp->next;
    }
    if (flag == 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int SortList(PersonP p)
{
    PersonP a = NULL, b = NULL, prev = NULL, end = NULL;
    PersonP temp;
    for (a = p; a->next != end;)
    {
        prev = a;
        for (b = a->next; b->next != end; b = b->next)
        {
            if (strcmp(b->lastName, b->next->lastName) > 0)
            {
                temp = b->next;
                prev->next = temp;
                b->next = temp->next;
                temp->next = b;
                b = temp;
            }
            prev = b;
        }
        end = b;
    }

    return EXIT_SUCCESS;
}

char* EnterFileName()
{
    char* fileName = NULL;
    fileName = malloc(sizeof(char) * 20);
    printf("\nInsert the name of the file: ");
    scanf(" %s", fileName);
    EnterValidString(fileName, "file name");

    return fileName;
}

int WriteInFile(PersonP head, char* fileName)
{

    FILE* fp = NULL;
    fp = fopen(fileName, "w");

    PersonP temp = head->next;
    if (NULL == fp)
    {
        printf("Unable to open file!\n");
        return EXIT_FAILURE;
    }
    while (temp)
    {
        fprintf(fp, "%s %s %d\n", temp->firstName, temp->lastName, temp->birthYear);
        temp = temp->next;
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

int ReadListFromFile(PersonP head, char* fileName)
{
    char firstName[MAX_SIZE] = { 0 };
    char lastName[MAX_SIZE] = { 0 };
    int birthYear = 0;
    int status = 3;
    PersonP p = head;

    FILE* fp = NULL;
    fp = fopen(fileName, "r");
    if (NULL == fp)
    {
        printf("Unable to open file!\n");
        return EXIT_FAILURE;
    }

    //while (fgets(buffer, MAX_LINELENGTH, fp))
    //while (!feof(fp))
    while(status == 3)
    {
        status = fscanf(fp, "%s %s %d", firstName, lastName, &birthYear);
        AddLast(p, firstName, lastName, birthYear);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

/*
    FURTHER IMPROVEMENT:
    * In case when we want to delete certain person (list element),
      it is not precisely defined how to distinguish which element to delete
      if we have people with same first and last name,
      currently it deletes 1st person found with searched last name
   -> possible solutions:
      1) add new int variable 'id' in struct, and search person we want delete
         by it's unique id.
      2) (Probably wasn't intended to work this way)
         To delete all existing people in current list
         with searched last name.

    * using ( from C++ logic ) tolower/toupper functions, while enetering data, 
      to apply no case-sensitive data input
    _____________________________________________________________________________
    * compiler version issue, warnings for not assigning scanf's return value
    -> possible solutions:
       1) define these commands:
            #define _CRT_SECURE_NO_DEPRECATE
            #define _CRT_NONSTDC_NO_DEPRECATE
    _____________________________________________________________________________
    * increasing code readability
    -> possible solutions:
       1) inside switch case, put each case in it's own function code block
    _____________________________________________________________________________
    * logical bug when free-ing allocated memory
      e.g. in function AddFirst after adding new person to list
           program does not work properly if we try to free(newPerson), perché?

    -> possible solution: free is only for things allocated on the heap with malloc.
       If you allocate something on the stack its memory is managed for you.
    _____________________________________________________________________________
    * reading data from .txt file
    
    different compilers read data from .txt file as expected,
    in some cases last existing line is read twice?
    Probably depends if e.g. notepad automatically, while saving .txt file,
    saves 1 extra line, doesn't matter :)

    -> possible solutions:
       1) https://stackoverflow.com/questions/23062471/reading-from-a-text-file-that-shows-the-last-line-details-twice-in-the-output
       2) https://stackoverflow.com/questions/30540804/program-reading-last-line-of-file-twice
       3) https://www.appsloveworld.com/c/100/468/c-fscanf-last-line-is-read-twice
*/
