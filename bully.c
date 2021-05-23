#include <stdio.h>
#include <stdlib.h>

//Função random
int random_number (int max){
    int result;
    result = rand() % max;
    return result;
}

void main(){
    int n, result_random = 0, *vector_process, i, j;
    printf("Entre com o número de processos\n");
    scanf("%d", &n);

    vector_process = malloc(n * sizeof(int));

    //Define se o processo está ativo(1) ou dormindo (0)  
    for (i = 0; i < n; i++){
        vector_process[i] = random_number(2);
        printf("%d\n", vector_process[i]);
    }

    //Determina em que processo a eleição começa.
    result_random =  random_number(n);
    printf("O processo escolhido para começar é: %d\n", result_random);

}