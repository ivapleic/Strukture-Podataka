#define _CRT_SECURE_NO_WARNINGS
#include "bill.h"
#include "filter.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_FILE_NAME (1024)
#define MAX_LINE (50)

int UserSearchArticleInRange(BillP head);
int SearchArticleInRange(BillP head, FilterP filter);
int PrintMenu();

int main(int argc, char* argv[]) {
    Bill head;
    char billName[MAX_LINE] = { 0 };
    char fileName[MAX_FILE_NAME] = { 0 };
    char enterString[MAX_LINE] = { 0 };
    char productName[MAX_LINE];
    int year = 0;
    int month = 0;
    int day = 0;
    int status = EXIT_SUCCESS;
    int choice = -1;
    int ch;
    char articleName[MAX_LINE] = { 0 };
    DateP newDate = NULL;

    InitializeBill(&head);

    do {
        system("cls");
        printf(
                "====================================================================\n"
                "\t\tRECEIPT MANAGEMENT SYSTEM\n"
                "====================================================================\n"
                "\n    Please insert FILENAME of the file\n"
                "    that contains name of all existing receipt/s: ");

        scanf(" %s", fileName);
        printf("\n");

        status = ReadBillsFromFile(&head, fileName);
        if (status > EXIT_SUCCESS) {
            printf(
                "\n Press enter to continue app execution.\n\n"
                "====================================================================\n");
            system("pause");
        }
    } while (status > EXIT_SUCCESS);

    if (status != EXIT_SUCCESS) {
        printf("App execution failed!\n");
        return EXIT_FAILURE;
    }

    while (choice != 0) {

        system("cls");
        printf(
            "====================================================================\n"
            "\t\tRECEIPT MANAGEMENT SYSTEM\n"
            "====================================================================\n"
            " File that contains names of all existing receipts: %s\n", fileName);
        PrintMenu();
        printf(" Choose an option from menu: ");
        scanf(" %d", &choice);
        do {
            ch = getchar();
        } while ((ch != EOF) && (ch != '\n'));
        
        switch (choice) {

        case 0:
            system("cls");
            printf(
                "====================================================================\n"
                "\n\t\tYou have exited the application!\t\n\n"
                "====================================================================\n");
            system("pause");
            break;

        case 1:
            // Kike
            status = EXIT_FAILURE;
            printf(
                "====================================================================\n"
                " You chose to add new receipt.\n\n"
                " This is current list of existing receipt/s:\n\n");
            PrintNamesOfAllBills(&head);

            while (status == EXIT_FAILURE) {
                printf("\n Please enter new receipt's name (that doesn't exist already!): ");
                scanf("%s", enterString);
                status = CheckIfBillExist(&head, enterString);
            }
            printf("\n Date: ");
            scanf("%d %d %d", &year, &month, &day);
// date string input needs to be checked with sscanf, 
// and to check existing limits, e.g. month can only be value [1,12], ...
// currently hardcoded lets pretend that input will be valid 
 //attempt of realizing valid date input checker      
/*
            scanf("%d%d%d", &year, &month, &day);
            printf(
                "\n You entered new receipt's name: %s\n\n"
                " Please enter new date"
                "\n in valid format <year>-<month>-<day> "
                "\n  EXAMPLE: 1992-01-03"
                "\n New date: ");
                scanf("%s", enterString);
                status = sscanf(enterString,"%d-%d-%d", &year,&month, &day);
*/
// newDate = CreateDateFromString(enterString);
// input params are different, new func needed
            newDate = CreateDateFromNumbers(year, month, day);
            BillP newBill = NULL;
            newBill = CreateBillFromInput(enterString, newDate);
            InsertBillSorted(&head, newBill);

// to be fixed
//    " Please enter required info for new receipt creation"
//    "\n in valid format: <year>-<month>-<day>: ");
//scanf(" %s", enterString);
//newDate = CreateDateFromString(enterString);
            printf(
                "\n====================================================================\n"
                "\n New receipt is successfully added to the list!"
                "\n Press enter to continue app execution.\n\n"
                "====================================================================\n");
            system("pause");
            break;

        case 2:
            // Kike
            printf(
                "====================================================================\n"
                " You chose to delete certain existing receipt.\n");
// need to do string validation, not to enter an empty string
// ignore for now
            printf("\nEnter name of the bill you want to delete: ");
            status = 0;
            scanf("%s", billName);
            status = CheckIfBillExist(&head, billName);
            DeleteBillAfter(&head, billName);
            printf(
                    "\n Press enter to continue app execution.\n\n\n"
                    "====================================================================\n");
            system("pause");
            break;
// needs to be improved and put inside a loop
// or give an option to user to go bac to main menu 
// and create a new choice
            

        case 3:
            // Kike
            printf(
                "===================================================================="
                " You chose to print all existing receipts info.\n\n");
            PrintAllBills(&head);
            printf(
                "\n\n====================================================================\n"
                "\n All existing receipts info are successfully printed!"
                "\n Press enter to continue app execution.\n\n"
                "====================================================================\n");
            system("pause");
            break;

        case 4:
            // Kike
            printf(
                "===================================================================="
                " You chose to modify data for certain existing receipt.\n\n");

            /*
            *   Conceptually explained:
            *   Data we can change are articles.
            *   currently not that important to ralize date of bill creation
            *   we have to implement logic for
            * 
            *   ADDING new item
            *       a) item doesn't exist, read all data, write new line in file for certain bill
            *       b) item already exist , need only to change it's existing quantity
                       1 only chane one info, not writing a new line in file

                REMOVING existing data
                    a) item doesn't exist, error message to user
                    b) item exist, we can move all existing data for that item, meaning removing
                       certain line in certain bill's file
                    c) we remove less items then they currently exist, meaning only
                       changing info number for quantity, not removing a line for that certain item 
         
            */

            printf("4");
            
            
            printf(
                "\n====================================================================\n"
                "\n All data modifications for certain existing receipt are saved"
                "\n and receipt info is updated!"
                "\n Press enter to continue app execution.\n\n"
                "====================================================================\n");
            system("pause");


        case 5:
            // Iva
            printf(
                "====================================================================\n"
                "\n You chose to print name list of existing receipt/s.\n\n");

            PrintNamesOfAllBills(&head);
            printf(
                "\n====================================================================\n"
                "\n List of existing receipt/s is successfully printed!"
                "\n Press enter to continue app execution.\n\n"
                "====================================================================\n");
            system("pause");
            break;






        case 6:
            // Iva
            printf(
                "====================================================================\n"
                "\n You chose to print all receipts that contain certain product\n\n");

            printf("Please insert the name of the article you want to search in the bills:");
            scanf("%s", articleName);
            FindBillsContainingCertainArticle(&head,articleName);
            printf("====================================");
            system("pause");
            break;





        case 7:
            // Iva
            printf(
                "====================================================================\n"
                "\n You chose to print receipt info with lowest total profit\n\n");
            BillP lowest = NULL;
            lowest=FindLowestProfitOfAll(&head);
            //printf("............%s\n", lowest->name); TESTING
            PrintBill(lowest);
            system("pause");
            break;

        case 8:
            // Iva
            printf(
                "====================================================================\n"
                "\n You chose to print receipt info with highest total profit\n\n");
            BillP highest = NULL;
            highest=FindHighestProfitOfAll(&head);
            //printf("............%s\n", highest->name);    TESTING
            PrintBill(highest);
            system("pause");
            break;

        default:
            printf(
                "====================================================================\n"
                "\n Your choice is invalid.\n"
                " Please enter valid number for certain choice.\n"
                "\n Press enter to continue app execution.\n"
                "====================================================================\n");
            system("pause");
        }
    }
//*********************************************

//    PrintAllBills(&head);
//    UserSearchArticleInRange(&head);
//    DeleteAllBills(&head);

    return EXIT_SUCCESS;
}
//*********************************************

int UserSearchArticleInRange(BillP head) {
    char article[MAX_ARTICLE_NAME] = { 0 };
    char dateFromString[MAX_DATE_AS_STRING] = { 0 };
    char dateToString[MAX_DATE_AS_STRING] = { 0 };
    FilterP filter = NULL;

    printf(
        "\n\n======================== SEARCH ================================\n"
        "\n\t<article> <from date> <to date> (inclusive)\n"
        "\tEXAMPLE: kruh 1992-01-03 1992-02-08\n\n"
        "====================================================================\n\n");

    do {
        printf("\t Your input: ");
        scanf(" %s %s %s", article, dateFromString, dateToString);

        filter = CreateFilter(dateFromString, dateToString, article);
    } while (!filter);

    SearchArticleInRange(head, filter);
    DeleteFilter(filter);

    return EXIT_SUCCESS;
}

int SearchArticleInRange(BillP head, FilterP filter) {
    BillP bill = NULL;
    int totalCount = 0;
    float totalPrice = 0.0f;

    printf("\t     Result:\r\n");

    for (bill = head->next; bill != NULL; bill = bill->next) {
        if (IsDateInsideOfRange(bill->date, filter->from, filter->to)) {
            ArticleP article = FindArticleByName(&bill->articleHead, filter->name);

            if (article) {
                printf("\t\t- ");
                PrintArticle(article);
                printf("\r\n");
                totalCount += article->count;
                totalPrice += article->count * article->price;
            }
        }
    }

    printf(
        "\t\tSearch result for \"%s\"\r\n"
        "\t\t\tCount:\t\t%d\r\n"
        "\t\t\tTotal profit\t%.02f\r\n",
        filter->name,
        totalCount,
        totalPrice
    );
}

int PrintMenu()
{
    printf(
        "====================================================================\n"
        "\t\t\t   MENU\n"
        "====================================================================\n\n"
        "\t1  -  Add new receipt\n"
        "\t2  -  Delete certain existing receipt\n"
        "\t3  -  Print all existing receipts info\n"
        "\t4  -  Modify data for certain existing receipt\n"
        "\t5  -  Print name list of existing receipts\n"
        "\t6  -  Print all receipts that contain certain product\n"
        "\t7  -  Print receipt info with lowest total profit\n"
        "\t8  -  Print receipt info with highest total profit\n"
        "\t0  -  Exit application\n"
        "\n====================================================================\n");

    return EXIT_SUCCESS;
}
/*
    FURTHER IMPROVEMENT:
    _____________________________________________________________________________
    * while scanning choice if input is 'non-number', e.g.: "*"
      we enter an infinte loop -> needs to be resolved!

    -> possible solutions:
       1) https://stackoverflow.com/questions/66723859/why-does-scanf-enter-a-loop-when-i-input-a-character
    _____________________________________________________________________________
    * increase code readability

    -> possible solutions:
       1) divide code inside switch cases (in main.c),
          each case should have it's own function
    _____________________________________________________________________________
    * extending app capabilities 

    -> possible solutions:
       1) realize "login form" and separating different options while login
          a) admin
          b) customer
         
         also separate authorized actions for each case, develop code logic
         new struct needs to be implemented such as:
         
         struct _user;
         typedef struct _user* UserP;
         typedf _user {
            char username[MAX_LINE];
            char password[MAX_LINE];
            int authority;
            BillP billHead;
         }

        for distinguishing authority e.g. : customer -> 1 and admin -> 2 
    _____________________________________________________________________________
    * https://stackoverflow.com/questions/65928723/exception-thrown-read-access-violation-it-was-0xfdfdfdfd
*/
