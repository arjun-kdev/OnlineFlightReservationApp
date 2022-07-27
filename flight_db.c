//#pragma once
#include "header.h"
#include "flight_db.h"

void flight_bdb_insert(flight *ft)
{
    char fileName[] = "Flights.dat";
    FILE *out = fopen(fileName, "ab");
    if (out == NULL)
    {
        printf("FILE ERROR.\n");
        return;
    }
    fwrite(ft, 1, sizeof(flight), out);
    fclose(out);
}

void flight_bdb_read_count(int *countAddr)
{
    int I = 0;
    flight FT;

    char fileName[] = "Flights.dat";
    FILE *in = fopen(fileName, "rb");
    if (in == NULL)
    {
        printf("FILE ERROR.\n");
        return;
    }
    while (fread(&FT, 1, sizeof(flight), in))
    {
        I++;
    }
    fclose(in);
    (*countAddr) = I;
}
void flight_bdb_read_count_seat(int *countAddr, int *countSeat)
{
    int I = 0;
    flight FT;
    char fileName[] = "Flights.dat";
    FILE *in = fopen(fileName, "rb");
    if (in == NULL)
    {
        printf("FILE ERROR.\n");
        return;
    }
    while (fread(&FT, 1, sizeof(flight), in))
    {
        (*countSeat) = (*countSeat) + FT.seats_available;
        I++;
    }
    fclose(in);
    (*countAddr) = I;
}

void flight_bdb_readAll(flight *ft)
{
    int I = 0;
    flight FT;

    char fileName[] = "Flights.dat";
    FILE *in = fopen(fileName, "rb");
    if (in == NULL)
    {
        printf("FILE ERROR.\n");
        return;
    }
    while (fread(&FT, 1, sizeof(flight), in))
    {
        ft[I] = FT;
        I++;
    }
    fclose(in);
}

void flight_bdb_readByServiceId(flight *ft, char *sNumber, char *doj, int *count)
{
    int I = 0;
    flight FT;

    char fileName[] = "Flights.dat";
    FILE *in = fopen(fileName, "rb");
    if (in == NULL)
    {
        printf("FILE ERROR.\n");
        return;
    }
    while (fread(&FT, 1, sizeof(flight), in))
    {
        if (!strcmp(FT.serviceNumber, sNumber))
        {
            if (!strcmp(FT.doj, doj))
            {
                (*ft) = FT;
                (*count)++;
                break;
            }
        }
        I++;
    }
    fclose(in);
}

void flight_bdb_update_time_status(flight ft)
{
    int I = 0;
    flight FT;

    char fileName[] = "Flights.dat";
    FILE *in = fopen(fileName, "rb+");
    if (in == NULL)
    {
        printf("FILE ERROR.\n");
        return;
    }
    while (fread(&FT, 1, sizeof(flight), in))
    {
        I++;
        if (!(strcmp(FT.serviceNumber, ft.serviceNumber)))
        {
            break;
        }
    }
    if (I > 0)
    {
        fseek(in, (I - 1) * sizeof(flight), SEEK_SET);
        fwrite(&ft, 1, sizeof(flight), in);
    }
    fclose(in);
}

void flight_bdb_delete(char *sNumber)
{
    int I = 0;
    flight FT;

    char fileName[] = "Flights.dat";
    char tempFileName[] = "Flightstemp.dat";
    FILE *in = fopen(fileName, "r");
    FILE *out = fopen(tempFileName, "w");
    if (in == NULL)
    {
        printf("(in)FILE ERROR.\n");
        return;
    }
    if (out == NULL)
    {
        printf("(out)FILE ERROR.\n");
        return;
    }
    while (fread(&FT, 1, sizeof(flight), in))
    {
        I++;
        if (strcmp(FT.serviceNumber, sNumber))
        {
            fwrite(&FT, 1, sizeof(flight), out);
        }
    }
    fclose(out);
    fclose(in);
    remove(fileName);
    rename(tempFileName, fileName);
}

void flight_bdb_readBy_src_dest_date_count(int *count, char *src, char *dest, char *doj)
{
    int I = 0;
    flight FT;

    char fileName[] = "Flights.dat";
    FILE *in = fopen(fileName, "rb");
    if (in == NULL)
    {
        printf("FILE ERROR.\n");
        return;
    }
    while (fread(&FT, 1, sizeof(flight), in))
    {
        printf("\nprint1\n");
        printf("%s %s %s\n", FT.source, FT.destination, FT.doj);
        printf("%s %s %s\n", src, dest, doj);
        if ((!strcmp(FT.source, src)) && (!strcmp(FT.destination, dest)) && (!strcmp(FT.doj, doj)))
        {
            printf("\n print2\n");
            (*count)++;
        }
        I++;
    }
    fclose(in);
}

void flight_bdb_readBy_src_dest_date(flight *ft, char *src, char *dest, char *doj)
{
    int I = 0;
    flight FT;

    char fileName[] = "Flights.dat";
    FILE *in = fopen(fileName, "rb");
    if (in == NULL)
    {
        printf("FILE ERROR.\n");
        return;
    }
    while (fread(&FT, 1, sizeof(flight), in))
    {
        if (!strcmp(FT.source, src) && !strcmp(FT.destination, dest) && !strcmp(FT.doj, doj))
        {
            ft[I] = FT;
            I++;
        }
    }
    fclose(in);
}

void flight_bdb_readByServiceId_date(flight *ft, char *sNumber, char *doj, int *count)
{
    int I = 0;
    flight FT;

    char fileName[] = "Flights.dat";
    FILE *in = fopen(fileName, "rb");
    if (in == NULL)
    {
        printf("FILE ERROR.\n");
        return;
    }
    while (fread(&FT, 1, sizeof(flight), in))
    {
        if (!strcmp(FT.serviceNumber, sNumber) && !strcmp(FT.doj, doj))
        {
            (*ft) = FT;
            (*count)++;
            break;
        }
        I++;
    }
    fclose(in);
}