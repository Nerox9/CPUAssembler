#include <stdio.h>
#include <stdlib.h>

void findHex(char mnemonic[],char operand1[],char operand2[], FILE *ptrOFile);

int main()
{

    char ch,content[10000],fileaddress[25]; // ch is char buffer, content array is ascii buffer, fileaddress array is address of asm file
    char mnem[10],op1[10],op2[10];
    int i = 0, counter =0, opcntr = 0, state = 0; //i is char counter, bin array is binary buffer
loop:
    printf("Enter the path of assembly file:\n");
    scanf("%s",fileaddress);
    printf("\n");

    if( strcmp(fileaddress,"EXIT") == 0 || strcmp(fileaddress,"exit") == 0 )
        return 0;

    FILE *ptrFile; //input asm file
    FILE *ptrOFile;//output bin file

    ptrFile = fopen(fileaddress,"r");
    ptrOFile = fopen("output","w");

    if(ptrFile==NULL)
    {
        perror("Error while opening the assembly file.\n");
        exit(EXIT_FAILURE);
    }

    if(ptrOFile==NULL)
    {
        perror("Error while creating the binary file.\n");
        exit(EXIT_FAILURE);
    }


    while( ( ch = fgetc (ptrFile) ) != EOF )
     {
         content[i]=ch; //each char to array char buffer
         i++;
     }

    printf("%s\n",content);
    fprintf(ptrOFile,"v2.0 raw\n");

    while( i >= counter )
    {
        if ( counter == i )
        {
            findHex(mnem,op1,op2,ptrOFile);
            printf("%s %s %s\n",mnem,op1,op2);
        }

        if( content[counter] == '\t' || content[counter] == ' ' || content[counter] == ',' || content[counter] == '\n' )
         {

             state++;

             if( content[counter] == '\n' )
                {
                    findHex(mnem,op1,op2,ptrOFile);
                    printf("%s %s %s\n",mnem,op1,op2);

                    mnem[0] = '\0';
                    op1[0] = '\0';
                    op2[0] = '\0';
                    state = 0;
                }

             opcntr=0;
             counter++;

             if( state > 2 )
                state = 0;

         }
         switch (state)
         {
         case 0 :
            mnem[opcntr] = content[counter];
            break;
         case 1 :
            op1[opcntr] = content[counter];
            break;
         case 2 :
            op2[opcntr] = content[counter];
            break;
         default :
            break;
         }

         opcntr++;
         counter++;
    }


    fclose(ptrOFile);



    fclose(ptrFile);

    printf("Compile is SUCCESSFUL!\n");
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Output file: %s\\output\n\n",cwd);
    goto loop;
}

void findHex(char mnemonic[],char operand1[],char operand2[], FILE *ptrOFile)
{
    if( strcmp(mnemonic,"ADD") == 0 ) //OK
    {

        if( operand1[0] == 'A' )
        {
            if( operand2[0] == 'B' )
                fprintf(ptrOFile,"01 ");
            else if( operand2[0] == 'C' )
                fprintf(ptrOFile,"03 ");
            else
                fprintf(ptrOFile,"15 %s 01 ",operand2);
        }

        if( operand1[0] == 'B' )
        {
            if( operand2[0] == 'A' )
                fprintf(ptrOFile,"02 ");
            else if( operand2[0] == 'C' )
                fprintf(ptrOFile,"05 ");
            else
                fprintf(ptrOFile,"14 %s 02 ",operand2);
        }

        if( operand1[0] == 'C' )
        {
            if( operand2[0] == 'A' )
                fprintf(ptrOFile,"04 ");
            else if( operand2[0] == 'B' )
                fprintf(ptrOFile,"06 ");
            else
                fprintf(ptrOFile,"14 %s 04 ",operand2);
        }

    }

    if( strcmp(mnemonic,"AND") == 0 ) //OK
    {
        if( operand1[0] == 'A' )
        {
            if( operand2[0] == 'B' )
                fprintf(ptrOFile,"07 ");
            else if( operand2[0] == 'C' )
                fprintf(ptrOFile,"09 ");
            else
                fprintf(ptrOFile,"0d %s ",operand2);
        }

        if( operand1[0] == 'B' )
        {
            if( operand2[0] == 'A' )
                fprintf(ptrOFile,"08 ");
            else if( operand2[0] == 'C' )
                fprintf(ptrOFile,"0b ");
        }

        if( operand1[0] == 'C' )
        {
            if( operand2[0] == 'A' )
                fprintf(ptrOFile,"0a ");
            else if( operand2[0] == 'B' )
                fprintf(ptrOFile,"0c ");
        }

    }

    if( strcmp(mnemonic,"MOV") == 0 ) //OK
    {
        if( operand1[0] == 'A' )
        {
            if( operand2[0] == 'B' )
                fprintf(ptrOFile,"0e ");
            else if( operand2[0] == 'C' )
                fprintf(ptrOFile,"10 ");
            else
                fprintf(ptrOFile,"14 %s ",operand2);
        }

        if( operand1[0] == 'B' )
        {
            if( operand2[0] == 'A' )
                fprintf(ptrOFile,"0f ");
            else if( operand2[0] == 'C' )
                fprintf(ptrOFile,"12 ");
            else
                fprintf(ptrOFile,"15 %s ",operand2);
        }

        if( operand1[0] == 'C' )
        {
            if( operand2[0] == 'A' )
                fprintf(ptrOFile,"11 ");
            else if( operand2[0] == 'B' )
                fprintf(ptrOFile,"13 ");
            else
                fprintf(ptrOFile,"16 %s ",operand2);
        }

    }

    if( strcmp(mnemonic,"OUT") == 0 ) //OK
    {
        if( operand1[0] == '3' )
            fprintf(ptrOFile,"17 ");

        if( operand1[0] == '4' )
            fprintf(ptrOFile,"18 ");


    }

if( strcmp(mnemonic,"JMP") == 0 ) //OK
    {
        fprintf(ptrOFile,"19 %s ",operand1);
    }

if( strcmp(mnemonic,"LDA") == 0 )
    {

    }

    if( strcmp(mnemonic,"CALL") == 0 )
    {

    }

    if( strcmp(mnemonic,"CMP") == 0 )
    {

    }

    if( strcmp(mnemonic,"DEC") == 0 )
    {

    }

    if( strcmp(mnemonic,"HLT") == 0 )
    {

    }

    if( strcmp(mnemonic,"IN") == 0 )
    {

    }

    if( strcmp(mnemonic,"INC") == 0 )
    {

    }

    if( strcmp(mnemonic,"JNZ") == 0 )
    {

    }

    if( strcmp(mnemonic,"JZ") == 0 )
    {

    }

    if( strcmp(mnemonic,"NOP") == 0 )
    {

    }

    if( strcmp(mnemonic,"OR") == 0 )
    {

    }

    if( strcmp(mnemonic,"RAL") == 0 )
    {

    }

    if( strcmp(mnemonic,"RAR") == 0 )
    {

    }

    if( strcmp(mnemonic,"RET") == 0 )
    {

    }

    if( strcmp(mnemonic,"STA") == 0 )
    {

    }

    if( strcmp(mnemonic,"SUB") == 0 )
    {

    }

    if( strcmp(mnemonic,"XOR") == 0 )
    {

    }

    if( strcmp(mnemonic,"CML") == 0 )
    {

    }
    return 0;
}
