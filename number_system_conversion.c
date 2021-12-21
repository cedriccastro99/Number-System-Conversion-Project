#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct input{

    char number[100];
    char current_base[100];
    char desired_base[100];

    struct input* next;

}in;

typedef struct output{

    char converted[100];

    struct output* next;

}out;

    in *head_input = NULL,*current;
    out *head_output = NULL,*current_out;

//convert hexaDecimalLetters to numbers
char *hexLetterConvert(char hexLetter[100]){

    static char hex[100];
    strcpy(hex,hexLetter);

    if(strcmp(hex,"A") == 0 || strcmp(hex,"a") == 0){
        strcpy(hex,"10");
    }else if(strcmp(hex,"B") == 0 || strcmp(hex,"b") == 0){
        strcpy(hex,"11");
    }else if(strcmp(hex,"C") == 0 || strcmp(hex,"c") == 0){
        strcpy(hex,"12");
    }else if(strcmp(hex,"D") == 0 || strcmp(hex,"d") == 0){
        strcpy(hex,"13");
    }else if(strcmp(hex,"E") == 0 || strcmp(hex,"e") == 0){
        strcpy(hex,"14");
    }else if(strcmp(hex,"F") == 0 || strcmp(hex,"f") == 0){
        strcpy(hex,"15");
    }
    
    return hex;

}

//convert hexaDecimalNubmer to Letters (10,11,12,13,14,15)
char *hexNumbertoLetter(int number){
    static char convert[2];

    if(number == 10){
        strcpy(convert,"A");
    }else if(number == 11){
        strcpy(convert,"B");
    }else if(number == 12){
        strcpy(convert,"C");
    }else if(number == 13){
        strcpy(convert,"D");
    }else if(number == 14){
        strcpy(convert,"E");
    }else if(number == 15){
        strcpy(convert,"F");
    }else{
        sprintf(convert,"%d",number);
    }
    return convert;
}

//get data from "input.txt"
void collectData()
{
    FILE *input;
    in *newNode;
    int count=0;

    newNode = (in*)malloc(sizeof(in));
    input = fopen("input.txt","r");

    char temp_Number,temp_currentBase,temp_desiredbase,temp[100];
    while(fscanf(input,"%s",&temp)!=EOF){
        if(count == 0){
            strcpy(newNode->number,temp);
        }else if(count == 1){
            strcpy(newNode->current_base,temp);
        }else if(count == 2){
            strcpy(newNode->desired_base,temp);
        }
        count++;
        if(count < 3){
            if(head_input == NULL){
                head_input = newNode;
                current = head_input;
                current->next = NULL;
            }else{
                current->next = newNode;
                current = current->next;
                current->next = NULL;
            }
        }else{
            newNode = (in*)malloc(sizeof(in));
            count = 0;
        }
    }

    fclose(input);
}

//save converted number to "output.txt"
void saveOutput(){
    
    FILE *output;

    output = fopen("output.txt","w");
    current_out = head_output;
    while(current_out != NULL){
        fprintf(output,"%s\n",current_out->converted);
        current_out = current_out->next;
    }

    fclose(output);
    
}

//convert any number with any base to binary(base 2)
void toBinary(char *number,char *currentBase){
    
    int i,j,k,num,len,baseInt;
    char currentNumber[100],Base[100],converted[100],exact[100];

    strcpy(currentNumber,number);
    strcpy(Base,currentBase);

    
    memset(exact, 0, sizeof exact); //clear the array first

    out *newNode;
    newNode = (out*)malloc(sizeof(out)); //allocate new memory to output

    if(strcmp(Base,"10") == 0){ //Decimal to Binary

        i = 0;
        num = atoi(number);
        while(num!=0){
            
            if( (num%2) == 0){
                converted[i] = '0';
            }else{
                converted[i] = '1';
            }
            num = num / 2;
            i++;
        }
        k = 0;
        for(j = i-1 ; j  >= 0 ; j--){
            exact[k] = converted[j];
            k++;
        }

        strcpy(newNode->converted,exact);
        
    }else if(strcmp(Base,"8") == 0){ //Octal to Binary

        len = strlen(currentNumber);
        baseInt = atoi(Base);

        //convert to octal to decimal first
        char temp[100];
        int temp_num;
        k = 0;
        num = 0 ;
        for(i = len-1; i >= 0 ; i--){
            temp[0] = currentNumber[i];
            temp_num = atoi(temp);
            num = num + (temp_num * pow(baseInt,k));
            k++;
        }

        i=0;

        while(num!=0){
            
            if( (num%2) == 0){
                converted[i] = '0';
            }else{
                converted[i] = '1';
            }
            num = num / 2;
            i++;
        }

        k = 0;
        for(j = i-1 ; j >= 0 ; j--){
            
            exact[k] = converted[j];
            k++;
        }

        strcpy(newNode->converted,exact);

    }else if(strcmp(Base,"16") == 0){ //HexaDecimal to Binary
        len = strlen(currentNumber);
        baseInt = atoi(Base);

        //convert to hexadecimal to decimal first
        char temp[100];
        int temp_num;
        k = 0;
        num = 0 ;
        for(i = len-1; i >= 0 ; i--){
            temp[0] = currentNumber[i];
            temp_num = atoi(hexLetterConvert(temp));
            num = num + (temp_num * pow(baseInt,k));
            k++;
        }

        i=0;

        while(num!=0){
            
            if( (num%2) == 0){
                converted[i] = '0';
            }else{
                converted[i] = '1';
            }
            num = num / 2;
            i++;
        }

        k = 0;
        for(j = i-1 ; j >= 0 ; j--){
            
            exact[k] = converted[j];
            k++;
        }

        strcpy(newNode->converted,exact);
    }
    
    if(head_output == NULL){
        head_output = newNode;
        current_out = head_output;
        current_out->next = NULL;
    }else{
        current_out->next = newNode;
        current_out = current_out->next;
        current_out->next = NULL;
    }
}

//convert any number with any base to decimal(base 10)
void toDecimal(char *number,char *currentBase){

    int i,j,k,num,len,baseInt;
    char currentNumber[100],Base[100],converted[100],exact[100];

    strcpy(currentNumber,number);
    strcpy(Base,currentBase);

    len = strlen(currentNumber);
    baseInt = atoi(Base);
    
    memset(exact, 0, sizeof exact); //clear the array first

    out *newNode;
    newNode = (out*)malloc(sizeof(out)); //allocate new memory to output

    if(strcmp(Base,"16") == 0){

        char temp[100];
        int temp_num;

        k = 0;
        num = 0 ;

        for(i = len-1; i >= 0 ; i--){
            temp[0] = currentNumber[i];
            temp_num = atoi(hexLetterConvert(temp));
            num = num + (temp_num * pow(baseInt,k));
            k++;
        }
        //convert integer to string
        sprintf(exact,"%d",num);

        strcpy(newNode->converted,exact);

    }else{

        char temp[100];
        int temp_num;

        k = 0;
        num = 0 ;

        for(i = len-1; i >= 0 ; i--){
            temp[0] = currentNumber[i];
            temp_num = atoi(temp);
            num = num + (temp_num * pow(baseInt,k));
            k++;
        }
        //convert integer to string
        sprintf(exact,"%d",num);

        strcpy(newNode->converted,exact);
    }

    if(head_output == NULL){
        head_output = newNode;
        current_out = head_output;
        current_out->next = NULL;
    }else{
        current_out->next = newNode;
        current_out = current_out->next;
        current_out->next = NULL;
    }

}

//convert any number with any base to octal(base 8)
void toOctal(char *number,char *currentBase){
    int i,j,k,num,len,baseInt;
    char currentNumber[100],Base[100],converted[100],exact[100];

    strcpy(currentNumber,number);
    strcpy(Base,currentBase);

    len = strlen(currentNumber);
    baseInt = atoi(Base);

    memset(exact, 0, sizeof exact);

    out *newNode;
    newNode = (out*)malloc(sizeof(out)); //allocate new memory to output

    if(strcmp(Base,"2") == 0){
        char temp[100],singleChar[1];
        int temp_num,limit,count;
        float cutNum;
        int remainder;

        /*
        -check if the binary length is okay to divide into 3
        
        -if not then add another '0' at the beginning of the binary
        to not cause an error :>
        */
        if((len%3) == 1){
            memset(temp, 0, sizeof temp);
            temp[0] = '0';
            k=0;
            for(i=1;i<len+1;i++ && k++){
                temp[i] = currentNumber[k];
            }
            memset(currentNumber, 0, sizeof currentNumber);
            strcpy(currentNumber,temp);
            len = strlen(currentNumber);
            memset(temp, 0, sizeof temp);
        }

        cutNum = len/3.00;


        k = 0;
        num = 0 ;

        limit = round(cutNum);   

        count = 0 ;
        

        if(limit > 2 || len <= 3){  //to prevent negative
            limit = limit-1;    
        }

        //reverse the binary
        for(i = len-1; i >= 0 ; i--){
            temp[count] = currentNumber[i];
            count++;
            if(count == 3 || i == 0){
                num = 0;
                k = 1;
                for(j = 0; j < count ;j++){
                    singleChar[0] = temp[j];
                    temp_num = atoi(singleChar);
                    if(temp_num == 1){
                        num = num+k;
                    }
                    k = k+k;
                }
                

                memset(singleChar, 0, sizeof singleChar);

                sprintf(singleChar,"%d",num);

                exact[limit] = singleChar[0];
                
                limit--;
                count = 0;
                memset(temp, 0, sizeof temp);

            }
        }

        strcpy(newNode->converted,exact);

    }else if(strcmp(Base,"10") == 0){
        i = 0;
        num = atoi(number);
        while(num!=0){
            
            char remainder[1];
            int remainderInt;

            memset(remainder, 0, sizeof remainder);

            remainderInt = (num%8);

            sprintf(remainder,"%d",remainderInt);

            converted[i] = remainder[0];

            num = num / 8;
            i++;

        }

        k = 0;
        for(j = i-1 ; j  >= 0 ; j--){
            exact[k] = converted[j];
            k++;
        }

        strcpy(newNode->converted,exact);

    }else if(strcmp(Base,"16") == 0){

        int temp_num;
        char temp[100];

        len = strlen(currentNumber);
        baseInt = atoi(Base);

        //convert to hexadecimal to decimal first

        k = 0;
        num = 0 ;
        for(i = len-1; i >= 0 ; i--){
            memset(temp, 0, sizeof temp);//clear temp array
            temp[0] = currentNumber[i];
            temp_num = atoi(hexLetterConvert(temp));
            num = num + (temp_num * pow(baseInt,k));
            k++;
        }

        i=0;

        while(num!=0){
            
            if( (num%2) == 0){
                converted[i] = '0';
            }else{
                converted[i] = '1';
            }
            num = num / 2;
            i++;
        }

        k = 0;
        for(j = i-1 ; j >= 0 ; j--){
            
            exact[k] = converted[j];
            k++;
        }

        //==========done converting hexa to binary==========

        memset(currentNumber, 0, sizeof currentNumber);

        strcpy(currentNumber,exact);

        memset(exact, 0, sizeof exact);

        len = 0;

        len = strlen(currentNumber);

        //==========done converting hexa to binary==========

        char singleChar[100];
        int limit,count;
        float cutNum;
        
         /*
        -check if the binary length is okay to divide into 3
        
        -if not then add another '0' at the beginning of the binary
        to not cause an error :>
        */
        if((len%3) == 1){
            memset(temp, 0, sizeof temp);
            temp[0] = '0';
            k=0;
            for(i=1;i<len+1;i++ && k++){
                temp[i] = currentNumber[k];
            }
            memset(currentNumber, 0, sizeof currentNumber);
            strcpy(currentNumber,temp);
            len = strlen(currentNumber);
            memset(temp, 0, sizeof temp);
        }

        cutNum = len/3.00;

        k = 0;

        limit = round(cutNum);   
        
        count = 0 ;
        

        if(limit > 2 || len <= 3){  //to prevent negative
            limit = limit-1;    
        }

        // reverse the binary

        for(i = len-1; i >= 0 ; i--){
            temp[count] = currentNumber[i];
            count++;
            if(count == 3 || i == 0){
                num = 0;
                k = 1;
                memset(singleChar, 0, sizeof singleChar);
                for(j = 0; j < count ;j++){
                    singleChar[0] = temp[j];
                    temp_num = atoi(singleChar);
                    if(temp_num == 1){
                        num = num+k;
                    }
                    k = k+k;
                }
                
                memset(singleChar, 0, sizeof singleChar);

                sprintf(singleChar,"%d",num);

                exact[limit] = singleChar[0];
                
                limit--;
                count = 0;
                memset(temp, 0, sizeof temp);

            }
        }

        strcpy(newNode->converted,exact);
        
    }

    if(head_output == NULL){
        head_output = newNode;
        current_out = head_output;
        current_out->next = NULL;
    }else{
        current_out->next = newNode;
        current_out = current_out->next;
        current_out->next = NULL;
    }

}

//convert any number with any base to hexadecimal(base 16)
void toHexadecimal(char *number,char *currentBase)
{
    int i,j,k,num,len,baseInt;
    char currentNumber[100],Base[100],converted[100],exact[100];

    strcpy(currentNumber,number);
    strcpy(Base,currentBase);

    
    memset(exact, 0, sizeof exact); //clear the array first

    out *newNode;
    newNode = (out*)malloc(sizeof(out)); //allocate new memory to output

    if(strcmp(Base,"2") == 0){

        char singleChar[100];
        int limit,count;
        float cutNum;
        int temp_num;
        char temp[100];

        len = strlen(currentNumber);

        /*
        -check if the binary length is okay to divide into 4
        
        -if not then add another '0' at the beginning of the binary
        to not cause an error :>
        */
        if((len%4) == 1){
            memset(temp, 0, sizeof temp);
            temp[0] = '0';
            k=0;
            for(i=1;i<len+1;i++ && k++){
                temp[i] = currentNumber[k];
            }
            memset(currentNumber, 0, sizeof currentNumber);
            strcpy(currentNumber,temp);
            len = strlen(currentNumber);
            memset(temp, 0, sizeof temp);
        }

        cutNum = (len/4.00);

        k = 0;

        limit = round(cutNum);   
        
        count = 0 ;
        

        if(limit >= 2 || len <= 4){  //to prevent negative
            limit = limit-1;    
        }

        // reverse the binary

        for(i = len-1; i >= 0 ; i--){
            temp[count] = currentNumber[i];
            count++;
            if(count == 4 || i == 0){
                num = 0;
                k = 1;
                memset(singleChar, 0, sizeof singleChar);
                for(j = 0; j < count ;j++){
                    singleChar[0] = temp[j];
                    temp_num = atoi(singleChar);
                    if(temp_num == 1){
                        num = num+k;
                        
                    }
                    k = k+k;
                }
                
                memset(singleChar, 0, sizeof singleChar);

                strcpy(singleChar,hexNumbertoLetter(num));

                exact[limit] = singleChar[0];
                
                limit--;
                count = 0;
                memset(temp, 0, sizeof temp);
            }
        }

        strcpy(newNode->converted,exact);

    }else if(strcmp(Base,"10") == 0){

        i = 0;
        num = atoi(number);
        while(num!=0){
            
            if( (num%2) == 0){
                converted[i] = '0';
            }else{
                converted[i] = '1';
            }
            num = num / 2;
            i++;
        }
        k = 0;
        for(j = i-1 ; j  >= 0 ; j--){
            exact[k] = converted[j];
            k++;
        }
        
        //====================done convert to binary==========================

        memset(currentNumber, 0, sizeof currentNumber);
        strcpy(currentNumber,exact);
        memset(exact, 0, sizeof exact);

        //====================done convert to binary==========================

        char singleChar[100];
        int limit,count;
        float cutNum;
        int temp_num;
        char temp[100];

        len = strlen(currentNumber);

        /*
        -check if the binary length is okay to divide into 4
        
        -if not then add another '0' at the beginning of the binary
        to not cause an error :>
        */
        if((len%4) == 1){
            memset(temp, 0, sizeof temp);
            temp[0] = '0';
            k=0;
            for(i=1;i<len+1;i++ && k++){
                temp[i] = currentNumber[k];
            }
            memset(currentNumber, 0, sizeof currentNumber);
            strcpy(currentNumber,temp);
            len = strlen(currentNumber);
            memset(temp, 0, sizeof temp);
        }

        cutNum = (len/4.00);

        k = 0;

        limit = round(cutNum);   
        
        count = 0 ;
        

        if(limit >= 2 || len <= 4){  //to prevent negative
            limit = limit-1;    
        }

        // reverse the binary


        for(i = len-1; i >= 0 ; i--){
            temp[count] = currentNumber[i];
            count++;
            if(count == 4 || i == 0){
                num = 0;
                k = 1;
                memset(singleChar, 0, sizeof singleChar);
                for(j = 0; j < count ;j++){
                    singleChar[0] = temp[j];
                    temp_num = atoi(singleChar);
                    if(temp_num == 1){
                        num = num+k;
                        
                    }
                    k = k+k;
                }
                
                memset(singleChar, 0, sizeof singleChar);

                strcpy(singleChar,hexNumbertoLetter(num));

                exact[limit] = singleChar[0];
                
                limit--;
                count = 0;
                memset(temp, 0, sizeof temp);
            }
        }

        strcpy(newNode->converted,exact);

    }else if(strcmp(Base,"8") == 0){
        len = strlen(currentNumber);
        baseInt = atoi(Base);

        //convert to octal to decimal first
        char temp[100];
        int temp_num;
        k = 0;
        num = 0 ;
        for(i = len-1; i >= 0 ; i--){
            temp[0] = currentNumber[i];
            temp_num = atoi(temp);
            num = num + (temp_num * pow(baseInt,k));
            k++;
        }

        i=0;

        while(num!=0){
            
            if( (num%2) == 0){
                converted[i] = '0';
            }else{
                converted[i] = '1';
            }
            num = num / 2;
            i++;
        }

        k = 0;
        for(j = i-1 ; j >= 0 ; j--){
            
            exact[k] = converted[j];
            k++;
        }

        //====================done convert to binary==========================

        memset(currentNumber, 0, sizeof currentNumber);
        strcpy(currentNumber,exact);
        memset(exact, 0, sizeof exact);

        //====================done convert to binary==========================

        char singleChar[100];
        int limit,count;
        float cutNum;

        len = strlen(currentNumber);

        /*
        -check if the binary length is okay to divide into 4
        
        -if not then add another '0' at the beginning of the binary
        to not cause an error :>
        */
        if((len%4) == 1){
            memset(temp, 0, sizeof temp);
            temp[0] = '0';
            k=0;
            for(i=1;i<len+1;i++ && k++){
                temp[i] = currentNumber[k];
            }
            memset(currentNumber, 0, sizeof currentNumber);
            strcpy(currentNumber,temp);
            len = strlen(currentNumber);
            memset(temp, 0, sizeof temp);
        }

        cutNum = (len/4.00);

        k = 0;

        limit = round(cutNum);   
        
        count = 0 ;
        

        if(limit >= 2 || len <= 4){  //to prevent negative
            limit = limit-1;    
        }

        // reverse the binary


        for(i = len-1; i >= 0 ; i--){
            temp[count] = currentNumber[i];
            count++;
            if(count == 4 || i == 0){
                num = 0;
                k = 1;
                memset(singleChar, 0, sizeof singleChar);
                for(j = 0; j < count ;j++){
                    singleChar[0] = temp[j];
                    temp_num = atoi(singleChar);
                    if(temp_num == 1){
                        num = num+k;
                        
                    }
                    k = k+k;
                }
                
                memset(singleChar, 0, sizeof singleChar);

                strcpy(singleChar,hexNumbertoLetter(num));

                exact[limit] = singleChar[0];
                
                limit--;
                count = 0;
                memset(temp, 0, sizeof temp);
            }
        }

        strcpy(newNode->converted,exact);

    }

    if(head_output == NULL){
        head_output = newNode;
        current_out = head_output;
        current_out->next = NULL;
    }else{
        current_out->next = newNode;
        current_out = current_out->next;
        current_out->next = NULL;
    }


}

int main(){

    collectData();
    current = head_input;
    char currentNumber[100],currentBase[100],desiredBase[100];
    while(current!=NULL){
        strcpy(currentNumber,current->number);
        strcpy(currentBase,current->current_base);
        strcpy(desiredBase,current->desired_base);
            if(strcmp(desiredBase,"2") == 0){
                toBinary(currentNumber,currentBase);
            }else if(strcmp(desiredBase,"10") == 0){
                toDecimal(currentNumber,currentBase);
            }else if(strcmp(desiredBase,"8") == 0){
                toOctal(currentNumber,currentBase);
            }else if(strcmp(desiredBase,"16") == 0){
                toHexadecimal(currentNumber,currentBase);
            }
        current = current->next;
    }

    current = head_input;
    current_out = head_output;
    
    while(current_out != NULL && current != NULL){
        printf("Number : %s\n"
                "Current Base: %s\n"
                "Desired Base: %s\n",
                current->number,current->current_base,current->desired_base);
        printf("Number : %s(%s)\n\n",current_out->converted,current->desired_base);
        current = current->next;
        current_out = current_out->next;
    }
    
    saveOutput();
    return 0;
}

