#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void pass1(char Label[10],char Opcode[10],char Operand[10],char Instrn[10],char Mneumonic[3]);
void main()
{ 
  char Label[10];
  char Opcode[10];
  char Operand[10];
  char Instrn[10];
  char Mneumonic[03];
  pass1(Label,Opcode,Operand,Instrn,Mneumonic);
}
void pass1(char Label[10],char Opcode[10],char Operand[10],char Instrn[10],char Mneumonic[3])
{
  int locctr,start,length,opd;
  FILE *fp1,*fp2,*fp3,*fp4,*fp5;
  fp1=fopen("input.txt","r");
  fp2=fopen("OPTAB.txt","r");
  fp3=fopen("Symtab.txt","w");
  fp4=fopen("Intrmd.txt","w");
  fp5=fopen("Length.txt","w");
  
  fscanf(fp1,"%s\t%s\t%x\t",Label,Opcode,&opd);
  if (strcmp(Opcode,"START")==0)
  {
    start=opd;
    locctr=start;
    fprintf(fp4,"%s\t%s\t%x\t\n",Label,Opcode,opd);
    fscanf(fp1,"%s\t%s\t%s\t",Label,Opcode,Operand);
   }
   else{
     locctr=0;
    }
 while(strcmp(Opcode,"END")!=0)
  {
    fprintf(fp4,"%x\t%s\t%s\t%s\n",locctr,Label,Opcode,Operand);
    if(strcmp(Label,"**")!=0)
    {
      fprintf(fp3,"%s\t%x\n",Label,locctr);
    }
    fscanf(fp2,"%s\t%s",Instrn,Mneumonic);
    
    while(strcmp(Instrn,"END")!=0)
    {
      if(strcmp(Opcode,Instrn)==0)
      {
        locctr+=3;
        break;
      }
      
     fscanf(fp2,"%s\t%s",Instrn,Mneumonic);
    }
     if(strcmp(Opcode,"WORD")==0)
     {
       locctr+=3;
     }
     else if(strcmp(Opcode,"RESW")==0)
     {
       locctr+=(3*(atoi(Operand)));
     }
     else if(strcmp(Opcode,"BYTE")==0)
       {
        int byte=strlen(Operand)-3;
        locctr=locctr+byte;
     }
    else if(strcmp(Opcode,"RESB")==0)
        locctr+=atoi(Operand);

     fscanf(fp1,"%s\t%s\t%s",Label,Opcode,Operand);
  }
     fprintf(fp4,"%x\t%s\t%s\t%s\n",locctr,Label,Opcode,Operand);
     
     fclose(fp1);
     fclose(fp2);
     fclose(fp3);
     fclose(fp4);
     
     char str;
     FILE *fp6,*fp7,*fp8;
     printf("The Contents of input table:\n\n");
     fp6=fopen("input.txt","r");
     str=fgetc(fp6);
     while(str!=EOF)
     {
       printf("%c",str);
       str=fgetc(fp6);
     }
    fclose(fp6);
    
   printf("The contents of Output table:\n\n");
   fp7=fopen("Intrmd.txt","r");
   str=fgetc(fp7);
   while(str!=EOF)
   {
     printf("%c",str);
     str=fgetc(fp7);
   }
   fclose(fp7);
   
   printf("\nThe contents of Symtab:\n\n");
   fp8=fopen("Symtab.txt","r");
   str=fgetc(fp8);
   while(str!=EOF)
   {
     printf("%c",str);
     str=fgetc(fp8);
   }
  fclose(fp8);
  length=locctr-start;
  printf("\nThe length of Instrn: %d",length);
  printf("\nThe value of Locctre: %x\n",locctr);
  
  fprintf(fp5,"The Length of the program : %d\n",length);
 }
