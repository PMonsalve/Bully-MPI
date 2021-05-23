#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int state;
    int weight;
}process;



//Função random
int random_number (int max){
    int result;
    result = rand() % max;
    return result;
}

void main(){
    int n, result_random = 0, i, j;
    process *vector_process;
    printf("Entre com o número de processos\n");
    scanf("%d", &n);

    vector_process = malloc(n * sizeof(process));

    //Define se o processo está ativo(1) ou dormindo (0)  
    for (i = 0; i < n; i++){
        vector_process[i].state = random_number(2);
        vector_process[i].weight = random_number(n);
    }

    //Determina em que processo a eleição começa.
    result_random =  random_number(n);
    printf("O processo escolhido para começar é: %d\n", result_random);


}