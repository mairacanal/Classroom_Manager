/* ---------------------------------------------------------------------------------------
CLASSROOM MANAGER
Developed by Maíra Canal and Caroline Grupe

GitHub: @mairacanal and @Carolgrupe

Goal: Develop a system to manager a classroom, generating statistics of all classrooms.

USP - ICC1 - 2020
------------------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLUNAS 5

// STRUCT

typedef struct {
    char nome[16];
    char sobrenome[16];
    int nusp;
    float p1, p2, trabalho, media;
} aluno;

// END STRUCT


// PROTOTYPES

void read_student (aluno *student, int number_of_students);
void print_student (aluno *student, int pos);
aluno* allocate_StudentArray (int number_of_students);
float** allocate_statistics (int c);
void realloc_statistics (int c, float** statistics);
int search_StudentByName (aluno* turma, int pos, int num, char* name, char* sobrenome);
void generate_statistics (int c, aluno* turma, int number_of_students, float** statistics);
void print_statistics (float** statistics);
void save_statistics (float** statistics, int c);
void free_statistics (float** statistics, int c);
aluno* create_class (int c, float** statistics, int number_of_students);
void save_class (float** statistics, int c);

// END PROTOTYPES


// MAIN FUNCTION

int main(){
    int opcao;
    int c = 1;
    int number_of_students;
    float** statistics = NULL;
    aluno* turma;

    while (1){
        printf("----------------- GERENCIADOR DE NOTAS -------------------\n");
        printf("                      -- MENU --                          \n");
        printf(" 1 - Criar uma turma                                      \n");
        printf(" 2 - Procurar um aluno                                    \n");
        printf(" 3 - Gerar estatisticas das turmas                        \n");
        printf(" 4 - Gravar informacoes de uma turma                      \n");
        printf(" 5 - Encerrar o sistema                                   \n");
        printf("                 -- Digite sua opcao --                   \n");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                printf("----------------------- TURMA %d -------------------------\n", c);
                printf("Numero de alunos da turma: ");
                scanf("%d", &number_of_students);
                printf("----------------------------------------------------------\n");

                if (c == 1){
                    statistics = allocate_statistics(c);
                }
                else{
                    free(turma);
                    realloc_statistics(c, statistics);
                }

                turma = create_class(c, statistics, number_of_students);
                c++;

                break;
            case 2: ;
                char nome[16];
                char sobrenome[16];
                int pos;

                printf("----------------------------------------------------------\n");
                printf("Digite o nome completo do aluno que procura: ");
                scanf("%s %s", nome, sobrenome);
                pos = search_StudentByName(turma, 0, (number_of_students - 1), nome, sobrenome);
                if (pos == -1){
                    printf("Aluno nao encontrado.\n");
                }
                else{
                    print_student(turma, pos);
                }

                break;
            case 3:
                save_statistics (statistics, c);
                break;
            case 4:
                save_class (statistics, c);
                break;
            case 5:
                free_statistics (statistics, c);
                printf("-------------------------- FIM ---------------------------\n");
                return 0;
            default:
                printf("Opcao invalida. Tente novamente.");
                break;
        }
    }   
}

// END MAIN


// AUX FUNCTIONS

void read_student (aluno *student, int number_of_students){
    for(int i = 0; i < number_of_students; i++){
        printf("\n------------------------ ALUNO %d -------------------------\n", i+1);
        printf("Nome do aluno: ");
        scanf("%s", student[i].nome);
        printf("Sobrenome do aluno: ");
        scanf("%s", student[i].sobrenome);
        printf("Numero USP: ");
        scanf("%d", &student[i].nusp);
        printf("Nota da primeira prova: ");
        scanf("%f", &student[i].p1);
        printf("Nota da segunda prova: ");
        scanf("%f", &student[i].p2);
        printf("Nota do trabalho: ");
        scanf("%f", &student[i].trabalho);

        student[i].media = (float) (student[i].p1 + student[i].p2 + student[i].trabalho)/3;
    }
}

void print_student (aluno *student, int pos){
    printf("----------------------------------------------------------\n");
    printf("Nome completo do aluno: %s %s", student[pos].nome, student[pos].sobrenome);
    printf("Numero USP: %d", student[pos].nusp);
    printf("Nota da primeira prova: %.2f", student[pos].p1);
    printf("Nota da segunda prova: %.2f", student[pos].p2);
    printf("Nota do trabalho: %.2f", student[pos].trabalho);
    printf("Media: %.2f", student[pos].media);
    printf("----------------------------------------------------------\n");
}

aluno* allocate_StudentArray (int number_of_students){
    aluno* turma = (aluno*) malloc (number_of_students * sizeof(aluno));
    return turma;
}

float** allocate_statistics (int c){
    float** statistics = (float**) malloc(c * sizeof(float*));
    for(int i = 0; i < c; i++){
        statistics [i] = (float*) malloc(COLUNAS * sizeof(float));
    }
    return statistics;
}

void realloc_statistics (int c, float** statistics){
    statistics = (float **) realloc (statistics, c * sizeof(float *));
    statistics[c - 1] = (float*) malloc(COLUNAS * sizeof(float));
}

int search_StudentByName (aluno* turma, int pos, int num, char* name, char* sobrenome){

    if (num == pos){
        return -1;
    }
    else if (strncmp(name, turma[pos].nome, strlen(turma[pos].nome)) == 0 && strncmp(sobrenome, turma[pos].sobrenome, strlen(turma[pos].sobrenome)) == 0){
        return (pos);
    }
    else {
        pos++;
        search_StudentByName(turma, pos, num, name, sobrenome);
    }
}

void generate_statistics (int c, aluno* turma, int number_of_students, float** statistics){
    float soma_p1 = 0;
    float soma_p2 = 0;
    float soma_trab = 0;
    float soma_med = 0;
    float soma_aprovados = 0;

    for (int i = 0; i < number_of_students; i++){
        soma_p1 = soma_p1 + turma[i].p1;
        soma_p2 = soma_p2 + turma[i].p2;
        soma_trab = soma_trab + turma[i].trabalho;
        soma_med = soma_med + turma[i].media;
        if (turma[i].media >= 5) soma_aprovados++;
    }

    statistics[c - 1][0] = (float) soma_p1/number_of_students; 
    statistics[c - 1][1] = (float) soma_p2/number_of_students;
    statistics[c - 1][2] = (float) soma_trab/number_of_students;
    statistics[c - 1][3] = (float) soma_med/number_of_students;
    statistics[c - 1][4] = (float) soma_aprovados/number_of_students;
}

void print_statistics (float** statistics){
    int c;

    printf("Digite o numero da turma que deseja consultar: ");
    scanf("%d", &c);

    printf("\n------------------------ TURMA %d -------------------------\n", c);
    printf("Media P1: %.2f\n", statistics[c - 1][0]);
    printf("Media P2: %.2f\n", statistics[c - 1][1]);
    printf("Media Trabalho: %.2f\n", statistics[c - 1][2]);
    printf("Media final: %.2f\n", statistics[c - 1][3]);
    printf("Porcentagem de aprovados: %.2f\n", (statistics[c - 1][4])*100);
    printf("-------------------------------------------------------------\n");
}

void save_statistics (float** statistics, int c){
    FILE* fp = fopen("estat.bin", "wb");

    if (fp == NULL){
        printf("Erro na criacao do arquivo.\n");
    }
    else{
        for (int i = 0; i < c; i++){
            fwrite(statistics[i], sizeof(float), COLUNAS, fp);
        }
    }
    fclose(fp);
}

void free_statistics (float** statistics, int c){
    for (int i = 0; i < c; i++){
        free (statistics[i]);
    }
    free (statistics);
}

aluno* create_class (int c, float** statistics, int number_of_students){
    aluno* turma = allocate_StudentArray(number_of_students);
    
    printf("           -- Entre com os dados dos alunos --            \n");
    read_student(turma, number_of_students);

    generate_statistics (c, turma, number_of_students, statistics);

    return turma;
}

void save_class (float** statistics, int c){
    char name_file[30];

    for (int i = 0; i < (c - 1); i++){
        printf("Nome do arquivo da turma %d: ", i+1);
        scanf("%s", name_file);

        FILE* arquivo = fopen(name_file, "w");

        fprintf(arquivo, "Turma %d\n", i + 1);
        fprintf(arquivo, "Media P1: %.2f\n", statistics[i][0]);
        fprintf(arquivo, "Media P2: %.2f\n", statistics[i][1]);
        fprintf(arquivo, "Media Trabalho: %.2f\n", statistics[i][2]);
        fprintf(arquivo, "Media final: %.2f\n", statistics[i][3]);
        fprintf(arquivo, "Porcentagem de aprovados: %.2f\n", (statistics[i][4])*100);

        fclose(arquivo);
    }
}

// END AUX FUNCTION