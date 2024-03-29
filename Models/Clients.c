/**
 * @file Clients.c
 * @author Francisco Arantes (a23504@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Header_Files/client.h"

/**
 * @brief Verify is the client exist in the linked list
 * 
 * @param begin 
 * @param ccode 
 * @return int 
 */
int existClient(Client* begin, int ccode)
{
    while (begin != NULL)
    {
        if (begin->cCode == ccode)
        {
            return 1;
        }
        begin = begin->nextc;
    }
    return 0;
}

/**
 * @brief Saves the current data of the linked list into the clientes.txt file
 * 
 * @param begin 
 * @return int 
 */
int saveClient(Client* begin)
{
    FILE* fp;
    fp = fopen("Text_Files/clients.txt", "w");
    if (fp != NULL)
    {
        Client* aux = begin;
        while (aux != NULL)
        {
            fprintf(fp, "%d;%d;%s;%f;%s;%s;\n",aux->cCode, aux->nif, aux->name, aux->balance, aux->address, aux->geocode);
            aux = aux->nextc;
        }
        fclose(fp);
        return(1);
    }
    else return(0);
}

/**
 * @brief Reads all the data from the clients.txt file to the linked list
 * 
 * @return Client* 
 */
Client* readClients()
{
    FILE* fp;
    int nif, ccode;
    float bal;
    char name[100], addr[100], geocode[100];

    Client* aux = NULL;
    fp = fopen("Text_Files/clients.txt", "r");
    if (fp != NULL)
    {
        while(!feof(fp))
        {fscanf(fp, "%d;%d;%[^;];%f;%[^;];%[^;];\n", &ccode, &nif, name, &bal, addr, geocode);
        aux = insertClient(aux, ccode, nif, name, bal, addr, geocode);
        }
        fclose(fp);
    }
    return(aux);
}

/**
 * @brief Insert a new client on the linked list
 * 
 * @param begin 
 * @param ccode 
 * @param nif 
 * @param name 
 * @param bal 
 * @param addr 
 * @param geocode 
 * @return Client* 
 */
Client* insertClient(Client* begin, int ccode, int nif, char name[], float bal, char addr[], char geocode[])
{
    if (!existClient(begin, ccode))
    {
        Client* newClient = malloc(sizeof(struct client));  // Allocate memory for new node;
        if (newClient != NULL)
        {
            newClient->cCode = ccode;
            newClient->nif = nif;
            strcpy(newClient->name, name);
            newClient->balance = bal;
            strcpy(newClient->address, addr);
            strcpy(newClient->geocode, geocode);
            newClient->nextc = begin;
            begin = newClient;
        }
    }
    return(begin);
}

/**
 * @brief Removes a client from the linked list
 * 
 * @param begin 
 * @param ccode 
 * @return Client* 
 */
Client* removeClient(Client* begin, int ccode)
{
    Client *previous = begin, *actual = begin, *aux;
    if (actual == NULL) return(NULL);
    else if (actual->cCode == ccode)
    {
        aux = actual->nextc;
        free(actual);
        return(aux);
    }
    else
    {
        while((actual != NULL)&&(actual->cCode != ccode))
        {
            previous = actual;
            actual = actual->nextc;
        }
        if (actual == NULL) return(begin);
        else
        {
            previous->nextc = actual->nextc;
            free(actual);
            return(begin);
        }
    }  
}

/**
 * @brief list all the clients of the linked list
 * 
 * @param begin 
 */
void listClients(Client* begin)
{
    while (begin != NULL) 
    {
        printf("%d -> %d -> %s -> %.2f -> %s -> %s\n", begin->cCode, begin->nif, begin->name, begin->balance, begin->address, begin->geocode);
        begin = begin->nextc;
    }
}

/**
 * @brief Updates a certain client of the linked list 
 * 
 * @param begin 
 * @param ccode 
 * @param nif 
 * @param newaddress 
 * @return int 
 */
int UpdateClients(Client* begin, int ccode, int nif, char newaddress[]) 
{
    Client *actual = begin;
    while(actual != NULL)
    {
        if(actual->cCode == ccode && actual->nif == nif)
        {
            strcpy(actual->address, newaddress);
            printf("Client updated sucessfully!\n");
            return 1;
            
        }
        actual= actual->nextc;
    }
    return 0;
}

/**
 * @brief Increses the funds of a certain client
 * 
 * @param begin 
 * @param ccod 
 * @param value 
 * @return Client* 
 */
Client* chargeBalance(Client *begin, int ccod, float value) 
{
    Client *client = begin;
    while (client != NULL) 
    {
        if (client->cCode == ccod ) 
        {
            client->balance += value;
            printf("Balance updated!!\n New Balance: %.2f\n", client->balance);
            return client;
        }
        client = client->nextc;
    }
    return NULL;
    printf("Client not found.\n");
}

