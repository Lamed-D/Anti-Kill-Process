#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

int main()
{

    FILE* fp = NULL;
    int size = 0;
    char* read_buf = NULL;
    char* write_buf = NULL;

    fp = fopen("Anti-Kill-Process.sys", "rb");
    if (fp == NULL)
    {
        printf("Error Open1\n");
        system("pause");
    }

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    read_buf = (char*)malloc(size + 1, sizeof(char));
    //write_buf = (char*)malloc(size + 1, sizeof(char));
    fread(read_buf, sizeof(char), size, fp);

    int ProcessID;

    char ProcessID_char[4];
    char ProcessID_String[10];
    printf("ProcessID : ");
    scanf("%d", &ProcessID);
    sprintf(ProcessID_String, "%d", ProcessID);

    int* address = &read_buf[0x415];
    *address = ProcessID;
    //memcpy((read_buf+0x415), ProcessID, 4);
    //read_buf[0x415] = ProcessID; ORI
    //read_buf[0x415] = ProcessID[0];
    //read_buf[0x416] = ProcessID[1];
    //read_buf[0x417] = ProcessID[2];
    //read_buf[0x418] = ProcessID[3];

    fclose(fp);

    char SYSFileName_String[30];
    sprintf(SYSFileName_String, "%s%s%s", "Anti-Kill-Process_", ProcessID_String, ".sys");
    fp = fopen(SYSFileName_String, "wb");
    if (fp == NULL)
    {
        printf("Error Open2\n");
        system("pause");
    }
    fwrite(read_buf, sizeof(char), size, fp);
    fclose(fp);

    char CurrentDirectory[255];
    GetCurrentDirectoryA(255, CurrentDirectory);
    char BATFileName_String[30];
    sprintf(BATFileName_String, "%s%s%s", "Anti-Kill-Process_", ProcessID_String, ".bat");
    char BATFileName_BUF[800];
    sprintf(BATFileName_BUF, "@echo off\n%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\npause",
        "sc create ",
        "Anti-Kill-Process_",
        ProcessID_String,
        " binpath= \"",
        CurrentDirectory,
        "\\Anti-Kill-Process_",
        ProcessID_String,
        ".sys\"",
        " displayname= \"Anti-Kill-Process_",
        ProcessID_String,
        "\"",
        " start= demand type= kernel\n",
        "sc start ",
        "Anti-Kill-Process_",
        ProcessID_String);

    fp = fopen(BATFileName_String, "w+");
    if (fp == NULL)
    {
        printf("Error Open3\n");
        system("pause");
    }
    fputs(BATFileName_BUF, fp);

    char BATFileName2_String[100];
    char BATFileName2_BUF[100];
    sprintf(BATFileName2_String, "%s%s.bat", "Kill Anti-Kill-Process_", ProcessID_String);
    fp = fopen(BATFileName2_String, "w+");
    if (fp == NULL)
    {
        printf("Error Open4\n");
        system("pause");
    }
    sprintf(BATFileName2_BUF, "@echo off\nsc stop %s%s\npause", "Anti-Kill-Process_", ProcessID_String);
    fputs(BATFileName2_BUF, fp);
    fclose(fp);
    free(read_buf);

    return 0;
}