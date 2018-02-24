#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>

typedef struct{ //OUQUEI
    char *digit;
    int size;
    char sign;
}number;

int Bigger(number num1, number num2){   //OUQUEI

    int i,j=0,k=0;

    if(num1.size == num2.size){
        for(i=0;i<num1.size;i++){
            if(num1.digit[i] > num2.digit[i])
                return -1;
            else if(num1.digit[i] < num2.digit[i])
                return 1;           //NUERO EH MAIOR,
        }                       //-1, SE num1 > num2
    }                           //0, SE num1 = num2
    else{                       //1, SE num1 < num2
        if(num1.size-j > num2.size-k)
            return -1;
        else
            return 1;
    }

    return 0;
}
int Max(int n, int m){  //OUQUEI
    if(n >= m)
        return n;
    else
        return m;
}
int BiggerThan0(number num){

    int i,cont = 0;

    for(i=0;i<num.size;i++){
        if(num.digit[i] == 0)
            cont++;
        if(num.digit < 0)
            return 0;
    }
    if(cont == num.size)
        return 0;

    return 1;

}

number ReadNumber(FILE *arq){   //OUQUEI

    int i=0,cont=0;

    number numero;
    numero.digit = malloc(sizeof(short int));

    if(fgetc(arq) == '-')
        numero.sign = '-';
    else{
        numero.sign = '+';
        rewind(arq);
    }

    while(!feof(arq)){
        fscanf(arq,"%1d",&numero.digit[i++]);
        numero.digit = realloc(numero.digit,(++cont)*sizeof(short int));
    }
    numero.digit = realloc(numero.digit,(--cont)*sizeof(short int));
    numero.size = cont;

    return numero;
}
void PrintNumber(number num){   //OUQUEI

    int i=0;

    while(num.digit[i] == 0)
        i++; // PROCURA O INICIO DO NUMERO

    printf("\n");
    if(num.sign == '-')
        printf("-");

    for(i;i<num.size;i++)
        printf("%d",num.digit[i]);
    printf("\n\n");
}
void PrintNumberFile(number num){

    FILE *arq;
    int i=0;
    char dir[100];
    char act[255] = "notepad ";
    GetCurrentDirectoryA(255,dir);
    arq = fopen("result.txt","w+");

    while(num.digit[i] == 0)
        i++; // PROCURA O INICIO DO NUMERO

    printf("\n");
    if(num.sign == '-')
        fprintf(arq,"-");

    for(i;i<num.size;i++)
        fprintf(arq,"%d",num.digit[i]);

    fclose(arq);

    system(strcat(act,strcat(dir,"\\result.txt")));
}
number Sum(number num1, number num2){   // OUQUEI

    int i,j,max,min;
    number min_num,max_num,result;

    max=Max(num1.size,num2.size);
    result.digit = calloc(max+1,sizeof(short int));
    result.size=max+1;

    if(num1.size == num2.size){
        for(i=max;i>0;i--){
            if((result.digit[i] + num1.digit[i-1] + num2.digit[i-1])>9){
                result.digit[i] += (num1.digit[i-1] + num2.digit[i-1]);
                result.digit[i] %= 10;
                result.digit[i-1]++;
            }
            else{
                result.digit[i] += num1.digit[i-1] + num2.digit[i-1];
            }
        }
    }
    else{
        if(num1.size > num2.size){
            max_num = num1;
            min_num = num2;
        }
        else{
            max_num = num2;
            min_num = num1;
        }
        j=max_num.size;
        min=min_num.size-1;

        for(i=1;i<max+1;i++)
            result.digit[i] = max_num.digit[i-1];

        for(i=min;i>=0;i--){
            if((result.digit[j] + min_num.digit[i])>9){
                result.digit[j] += min_num.digit[i];
                result.digit[j] %= 10;
                result.digit[j-1]++;
            }
            else
                result.digit[j] += min_num.digit[i];
            j--;
        }
    }

    for(i=max;i>0;i--){
        if(result.digit[i] > 9){
            result.digit[i] %= 10;
            result.digit[i-1]++;
        }
    }

    return result;
}
number Sub(number num1, number num2){   //OUQUEI

    int i,j,max;
    number min_num,max_num,result;

    max=Max(num1.size,num2.size);
    result.digit=calloc(max,sizeof(short int));
    result.size=max;

    for(i=0;i<num1.size;i++)
        result.digit[i] = 9-num1.digit[i];

    result = Sum(result, num2);
    i=0;
    while(result.digit[i] == 0) i++; //PROCURAR INICIO DO NUMERO

    for(i;i<result.size;i++)
        result.digit[i] = 9-result.digit[i];

    return result;
}
number MultiBy10(number num){           //OUQUEI

    num.digit = realloc(num.digit,(num.size+1)*sizeof(short int));
    num.digit[num.size++] = 0;

    return num;
}
number MultParcial(number num1, int num){   //OUQUEI

    int i;
    number parcial, result;
    parcial = num1;

    if(num == 1)
        return parcial;
    else
        for(i=0;i<num-1;i++)
            parcial = Sum(parcial, num1);

    return parcial;
}
number Multi(number num1, number num2){ //OUQUEI

    int i,j=1;
    number parcial,result;

    result = num1;
    result = Sub(result, num1);

    for(i=0;i<num2.size;i++){
        if(num2.digit[i] != 0){
            parcial = MultParcial(num1, num2.digit[i]);
            result = Sum(result, parcial);
        }
        if(i < num2.size-1)
            result = MultiBy10(result);
    }

    return result;
}
//number Div(number num1, number num2){
//
//    int cont = 0;
//    number div = num1;
//
//    while(BiggerThan0(div) == 1){
//        PrintNumber(div);
//        printf("\n Big = %d\n",BiggerThan0(div));
//        printf("div.size = %d\n", div.size);
//        printf("num2.size = %d\n",num2.size);
//        div = Sub(div, num2);
//        cont++;
//    }
//
//    printf("\ncont = %d\n",cont);
//
//    return div;
//}
void SignGame(char op, number num1, number num2){   //OUQUEI

    int B;
    number result;
    B = Bigger(num1, num2);

    if(op == '+'){                                      // ++++++++++++++++++
        if(num1.sign == '+' && num2.sign == '+')        // (+)+(+) = +
            result = Sum(num1, num2);
        else if(num1.sign == '+' && num2.sign == '-'){  // (+)+(-) =
            if(B == -1)                                 // + SE NUM1 > NUM2
                result = Sub(num1, num2);
            else if(B == 1){                            // - SE NUM2 > NUM1
                result = Sub(num2, num1);
                result.sign = '-';
            }
        }
        else if(num1.sign == '-' && num2.sign == '+'){  //(-)+(+) =
            if(B == -1){                                // - SE NUM1 > NUM2
                result = Sub(num1, num2);
                result.sign = '-';
            }
            else if(B == 1)                             // + SE NUM2 > NUM1
                result = Sub(num2, num1);
        }
        else if(num1.sign == '-' && num2.sign == '-'){   // (-)+(-) = -
            result = Sum(num1, num2);
            result.sign = '-';
        }
    }
    else if(op == '-'){                                 // ------------------
        if(num1.sign == '+' && num2.sign == '+'){  // (+)-(+) =
            if(B == -1)                                 // + SE NUM1 > NUM2
                result = Sub(num1, num2);
            else if(B == 1){                            // - SE NUM2 > NUM1
                result = Sub(num2, num1);
                result.sign = '-';
            }
        }
        else if(num1.sign == '+' && num2.sign == '-')   // (+)-(-) = +
            result = Sum(num1, num2);
        else if(num1.sign == '-' && num2.sign == '+'){   // (-)-(+) = -
            result = Sum(num1, num2);
            result.sign = '-';
        }
        else if(num1.sign == '-' && num2.sign == '-'){   // (-)-(-) =
            if(B == -1){                                // - SE NUM1 > NUM2
                result = Sub(num1, num2);
                result.sign = '-';
            }
            else if(B == 1){                            // + SE NUM2 > NUM1
                result = Sub(num2, num1);
            }
        }
    }
    else if(op == 'x' || op == '/'){                    // */*/*/*/*/*/*/*/*/
        if(op == 'x')
            result = Multi(num1, num2);
        //else
        //    result = Div(num1, num2);
        if(num1.sign == num2.sign)
            result.sign = '+';
        else
            result.sign = '-';
    }

    PrintNumberFile(result);
}

int main(void){

    system("color 0a");
    FILE *num1, *num2;
    number numero1, numero2, result;
    int i;
    char c;
    numero1.digit = NULL;
    numero2.digit = NULL;
    num1 = fopen("num1.txt","r");
    num2 = fopen("num2.txt","r");
    numero1 = ReadNumber(num1);
    numero2 = ReadNumber(num2);

    printf("%%%%%%%%%%%%%%%%%%%%\tQUASE CALCULADORA QUASE INFINITA\t%%%%%%%%%%%%%%%%%%%%\n\n");

    printf("Numero 1: ");
    PrintNumber(numero1);
    printf("Numero 2: ");
    PrintNumber(numero2);
    printf("Digite:\n");
    printf(" (+) Soma\n (-) Subtracao\n (x) Multiplicacao\n (/) Divisao(indisponivel na funcao de avaliacao)\n\n");
    printf("Obs.: O resultado sera impresso em um novo arquivo chamado result.txt\n\n");
    c = getc(stdin);
    printf("\n\nCalculando");

    for(i=1;i<=3;i++){
        system("TIMEOUT /T 1 > null /NOBREAK");
        printf(".");
    }
    printf("\n\n");

    SignGame(c,numero1, numero2);

    printf("\n");

    return 0;
}
