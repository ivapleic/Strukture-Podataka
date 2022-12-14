#define _CRT_SECURE_NO_WARNINGS
#include "bill.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_LINE (1024)

int InitializeBill(BillP bill) {
    bill->date = NULL;
    bill->next = NULL;
    bill->total = 0.0f;
    memset(bill->name, 0, MAX_BILL_NAME);
    InitializeArticle(&bill->articleHead);

    return EXIT_SUCCESS;
}

BillP CreateBillFromFile(char* billFileName) {
    FILE* fp = NULL;
    BillP bill = NULL;
    int status = EXIT_SUCCESS;
    char fileLine[MAX_LINE] = { 0 };

    fp = fopen(billFileName, "r");
    if (!fp) {
        perror("\tBill not opened!\n");
        return NULL;
    }

    bill = (BillP)malloc(sizeof(Bill));
    if (!bill) {
        perror("Bill not allocated!\n");
        fclose(fp);
        return NULL;
    }

    InitializeBill(bill);

    strcpy(bill->name, billFileName);

    fgets(fileLine, MAX_LINE, fp);
    bill->date = CreateDateFromString(fileLine);
    if (!bill->date) {
        fclose(fp);
        DeleteBill(bill);
        return NULL;
    }

    while (!feof(fp)) {
        ArticleP article = NULL;
        fgets(fileLine, MAX_LINE, fp);

        if (strlen(fileLine) == 0)
            continue;

        article = CreateArticleFromString(fileLine);
        if (!article) {
            fclose(fp);
            DeleteBill(bill);

            return NULL;
        }
        InsertArticleSorted(&bill->articleHead, article);
    }
    fclose(fp);

    return bill;
}

int InsertBillAfter(BillP position, BillP bill) {
    bill->next = position->next;
    position->next = bill;

    return EXIT_SUCCESS;
}

int InsertBillSorted(BillP head, BillP bill) {
    BillP position = head;
    while (position->next != NULL && Datecmp(position->next->date, bill->date) < 0)
        position = position->next;

    InsertBillAfter(position, bill);

    return EXIT_SUCCESS;
}

int ReadBillsFromFile(BillP head, char* fileName) {
    FILE* fp = NULL;
    char fileLine[MAX_LINE] = { 0 };

    fp = fopen(fileName, "r");
    if (!fp) {
        perror("File with bills not opened!\n");
        return FILE_WITH_BILLS_NOT_OPENED;
    }

    while (!feof(fp)) {
        BillP bill = NULL;
        fscanf(fp, "%s", fileLine);

        if (strlen(fileLine) == 0)
            continue;

        bill = CreateBillFromFile(fileLine);
        if (!bill) {
            fclose(fp);
            DeleteAllBills(head);
            return CREATE_BILL_FAILED;
        }
        InsertBillSorted(head, bill);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

int PrintBill(BillP bill) {
    ArticleP article = NULL;

    printf("\t============================\r\n");
    printf("\t\t** Date => ");
    PrintDate(bill->date);
    printf("\r\n");
    printf("\t\t** Articles (name, count, price) \r\n");

    for (article = bill->articleHead.next; article != NULL; article = article->next) {
        printf("\t\t\t * ");
        PrintArticle(article);
        printf("\r\n");
    }

    return EXIT_SUCCESS;
}

int PrintAllBills(BillP head) {
    BillP bill = NULL;
    for (bill = head->next; bill != NULL; bill = bill->next)
        PrintBill(bill);

    return EXIT_SUCCESS;
}

int DeleteBill(BillP bill) {
    if (!bill)
        return EXIT_SUCCESS;

    if (bill->date)
        free(bill->date);

    DeleteAllArticles(&bill->articleHead);
    free(bill);
}

int DeleteBillAfter(BillP position) {
    BillP toDelete = position->next;
    if (!toDelete)
        return EXIT_SUCCESS;

    position->next = toDelete->next;
    DeleteBill(toDelete);

    return EXIT_SUCCESS;
}

int DeleteAllBills(BillP head) {
    while (head->next)
        DeleteBillAfter(head);

    return EXIT_SUCCESS;
}

float CalculateTotalBill(BillP bill)
{
    ArticleP article = NULL;
    bill->total = 0;

        article = &bill->articleHead;
        for (article = article->next; article != NULL; article = article->next)
        {
            bill->total += (float)article->price * article->count;
        }
    return bill->total;
}

BillP FindLowestProfitOfAll(BillP head) {
    
    head = head->next;
    BillP lowest = head;
    float min = FLT_MAX;
    float total = 0.0f;

    for (; head->next != NULL; head = head->next) {
        total=CalculateTotalBill(head);
        if (total < min) {
            min = total;
            lowest = head;
        }
    }
    printf("\nThe lowest profit of all bills is:\t%f\n", lowest->total);

    return lowest;
}

BillP FindHighestProfitOfAll(BillP head) {

    head = head->next;
    BillP highest = NULL;
    float max = FLT_MIN;
    float total = 0;

    for (; head->next != NULL; head = head->next) {
        total = CalculateTotalBill(head);
        if (total > max) {
            max = total;
            highest = head;
        }
    }
    printf("\nThe highest profit of all bills is:\t%f\n", highest->total);

    return highest;
}

int PrintNamesOfAllBills(BillP head) {

    BillP bill = NULL;
    printf("\t-------------------------\n");
    for (bill = head->next; bill != NULL; bill = bill->next)
        printf(
            " \t|\t%s\t|\n"
            "\t-------------------------\n", bill->name);

    return EXIT_SUCCESS;
}

int FindBillsContainingCertainArticle(BillP head, char* articleName) {

    BillP theOne = NULL;
    head = head->next;
    ArticleP article = NULL;

    while (head != NULL) {
        article = &head->articleHead;
        article = article->next;
            for (; article != NULL; article = article->next) {
                if (strcmp(article->name, articleName) == 0) {
                    theOne = head;
                    printf("%s\n", head->name);;
                    //PrintBill(theOne);
                }
            }
            head = head->next;
    }
    if (theOne == NULL) {
        printf("\nThe article you want to find doesn't exists in any of the bills\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

//************************

int CheckIfBillExist(BillP head, char* enterString)
{    
    for (head = head->next; head != NULL; head = head->next)
        if (strcmp(head->name, enterString) == 0)
            return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

BillP CreateBillFromInput(char* billFileName, DateP date) {
    BillP bill = NULL;
    int status = EXIT_SUCCESS;
    char articleName[MAX_LINE] = { 0 };
    int articleAmount = 0 ;
    float articlePrice = 0.0f;
    int choice = -1;

    bill = (BillP)malloc(sizeof(Bill));
    if (!bill) {
        perror("Bill not allocated!\n");
        return NULL;
    }

    InitializeBill(bill);
    strcpy(bill->name, billFileName);
    bill->date = date;
    
    printf(
        "\n===================================================================="
        "\n Add new products to receipt: %s"
        "\n For adding new product enter: 1" 
        "\n For stopping adding new products enter: 0\n"
        "====================================================================\n", billFileName);
    printf("\n Enter your choice: ");
    scanf(" %d", &choice);

    while (choice != 0) {

        printf("\n Enter new article's name: ");
        scanf(" %s", articleName);
        printf(" Enter new article's quantity: ");
        scanf(" %d", &articleAmount);
        printf(" Enter new article's price: ");
        scanf(" %f", &articlePrice);

        ArticleP article = NULL;
        article = CreateArticleFromInput(articleName, articleAmount, articlePrice);
        if (!article) {
            printf("Article not created!\n");
            return NULL;
        }

/*        if (!article) {
            DeleteBill(bill);
            return NULL;
        }
*/      
        InsertArticleSorted(&bill->articleHead, article);
        printf("\n Enter your choice: ");
        scanf(" %d", &choice);
    }

    return bill;
}

int DeleteBillAfter(BillP head, char* billName)
{
    int flag = 0;
    BillP prev = NULL;
    BillP current = NULL;

    for (prev = head; prev->next != NULL; prev = prev->next)
    {
        if (strcmp(prev->next->name, billName) == 0)
        {
            flag++;
            current = prev->next;
            prev->next = prev->next->next;
            free(current);
            break;
        }
    }

    if (flag == 0)
        printf("\nBill with searched name doesn't exist in current bill list!\n");
    else
        printf("\nBill is succesfully deleted from bill list!\n");

    return EXIT_SUCCESS;
}