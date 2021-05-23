#include <stdio.h>
#include <stdlib.h>

//Função random
int random_number (int max){
    int result;
    result = rand() % max;
    return result;
}

void main(){
    int n, result_random = 0;
    printf("Entre com o número de processos\n");
    scanf("%d", &n);
    result_random =  random_number(n);
    printf("O processo escolhido é: %d\n", result_random);
    
}