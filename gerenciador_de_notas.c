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
    int class;
    char nome[16];
    char sobrenome[16];
    int nusp;
    float p1, p2, trabalho, media;
} aluno;

// END STRUCT


// PROTOTYPES

void read_student (aluno *student, int number_of_students, int total_students, int c);
void print_student (aluno *student, int pos);

aluno* allocate_StudentArray (int number_of_students);
void realloc_StudentArray (aluno* turma, int total_students, int number_of_students);

void search_StudentByName (aluno* turma, int pos, int num, char name[16], char last_name[16]);

float** allocate_statistics (int c);
void realloc_statistics (int c, float** statistics);
void generate_statistics (int c, aluno* turma, int total_students, int number_of_students, float** statistics);
void free_statistics (float** statistics, int c);
void print_statistics (float** statistics);

aluno* create_class (int c, float** statistics, int number_of_students, int total_students);
void realloc_class (aluno* turma, int c, float** statistics, int number_of_students, int total_students);
void save_data (float** statistics, int c);

// END PROTOTYPES


// MAIN FUNCTION

int main(){

    int c = 1;
    int total_students = 0;

    int opcao;
    int number_of_students;
    float** statistics = NULL;
    aluno* turma;
    char name[16];
    char last_name[16];


    while (1){
        printf("----------------- GERENCIADOR DE NOTAS -------------------\n");
        printf("                      -- MENU --                          \n");
        printf(" 1 - Criar uma turma                                      \n");
        printf(" 2 - Procurar um aluno                                    \n");
        printf(" 3 - Gerar estatisticas das turmas                        \n");
        printf(" 4 - Gravar informacoes de uma turma                      \n");
        printf(" 5 - Encerrar o sistema                                   \n");
        printf("                 -- Digite sua opcao --                   \n");
        scanf ("                            %d", &opcao);

        switch (opcao){
            case 1:
                printf("----------------------- TURMA %d -------------------------\n", c);
                printf("Numero de alunos da turma: ");
                scanf("%d", &number_of_students);
                printf("----------------------------------------------------------\n");

                if (c == 1){
                    statistics = allocate_statistics(c);
                    turma = create_class(c, statistics, number_of_students, total_students);
                }
                else{
                    realloc_statistics(c, statistics);
                    realloc_class(turma, c, statistics, number_of_students, total_students);
                }

                c++;
                total_students = total_students + number_of_students;

                break;
            case 2: 
                printf("----------------------------------------------------------\n");
                printf("Digite o nome completo do aluno que procura: ");
                scanf("%s %s", name, last_name);

                search_StudentByName(turma, (total_students - 1), (total_students - 1), name, last_name);
                break;
            case 3:
                print_statistics (statistics);
                break;
            case 4:
                save_data (statistics, c);                
                break;
            case 5:
                free_statistics (statistics, c);
                free(turma);
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

void read_student (aluno *student, int number_of_students, int total_students, int c){
    int count = 1;

    for(int i = total_students; i < (number_of_students + total_students); i++){
        printf("\n------------------------ ALUNO %d -------------------------\n", count);
        student[i].class = c;
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

        count++;
    }
}

void print_student (aluno *student, int pos){
    printf("----------------------------------------------------------\n");
    printf("Turma: %d\n", student[pos].class);
    printf("Nome completo do aluno: %s %s\n", student[pos].nome, student[pos].sobrenome);
    printf("Numero USP: %d\n", student[pos].nusp);
    printf("Nota da primeira prova: %.1f\n", student[pos].p1);
    printf("Nota da segunda prova: %.1f\n", student[pos].p2);
    printf("Nota do trabalho: %.1f\n", student[pos].trabalho);
    printf("Media: %.2f\n", student[pos].media);
    printf("----------------------------------------------------------\n");
}

aluno* allocate_StudentArray (int number_of_students){
    aluno* turma = (aluno*) malloc (number_of_students * sizeof(aluno));
    return turma;
}

void realloc_StudentArray (aluno* turma, int total_students, int number_of_students){
    turma = (aluno*) realloc (turma, (total_students + number_of_students) * sizeof(aluno));
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

void search_StudentByName (aluno* turma, int pos, int num, char name[16], char last_name[16]){

    if (pos == -1){
        printf("Aluno nao encontrado.\n");
    }
    else if (strncmp(name, turma[pos].nome, strlen(turma[pos].nome)) == 0 && strncmp(last_name, turma[pos].sobrenome, strlen(turma[pos].sobrenome)) == 0){
        print_student(turma, pos);
    }
    else {
        pos--;
        search_StudentByName(turma, pos, num, name, last_name);
    }
}

void generate_statistics (int c, aluno* turma, int total_students, int number_of_students, float** statistics){
    float soma_p1 = 0;
    float soma_p2 = 0;
    float soma_trab = 0;
    float soma_med = 0;
    float soma_aprovados = 0;

    for (int i = total_students; i < (number_of_students + total_students); i++){
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

void free_statistics (float** statistics, int c){
    for (int i = 0; i < c; i++){
        free (statistics[i]);
    }
    free (statistics);
}

void print_statistics (float** statistics){
    int number_of_class;

    printf("----------------------------------------------------------\n");
    printf("Digite o numero da turma que deseja consultar: ");
    scanf("%d", &number_of_class);

    printf("----------------------- TURMA %d -------------------------\n", number_of_class);
    printf("Media P1: %.1f\n", statistics[number_of_class - 1][0]);
    printf("Media P2: %.1f\n", statistics[number_of_class - 1][1]);
    printf("Media Trabalho: %.1f\n", statistics[number_of_class - 1][2]);
    printf("Media Final: %.2f\n", statistics[number_of_class - 1][3]);
    printf("Aprovacao: %.1f\n", (statistics[number_of_class - 1][4])*100);
    printf("----------------------------------------------------------\n");
}

aluno* create_class (int c, float** statistics, int number_of_students, int total_students){
    aluno* turma = allocate_StudentArray(number_of_students);
    
    printf("           -- Entre com os dados dos alunos --            \n");
    read_student(turma, number_of_students, total_students, c);

    generate_statistics (c, turma, total_students, number_of_students, statistics);

    return turma;
}

void realloc_class (aluno* turma, int c, float** statistics, int number_of_students, int total_students){
    realloc_StudentArray (turma, total_students, number_of_students);

    printf("           -- Entre com os dados dos alunos --            \n");
    read_student(turma, number_of_students, total_students, c);

    generate_statistics (c, turma, total_students, number_of_students, statistics);
}

void save_data (float** statistics, int c){
    char name_file[30];

    for (int i = 0; i < (c - 1); i++){
        printf("Nome do arquivo da turma %d: ", i+1);
        scanf("%s", name_file);

        FILE* arquivo = fopen(name_file, "w");

        if (arquivo == NULL) printf("Erro na criacao do arquivo.\n");

        else {
            fprintf(arquivo, "Turma %d\n", i + 1);
            fprintf(arquivo, "Media P1: %.2f\n", statistics[i][0]);
            fprintf(arquivo, "Media P2: %.2f\n", statistics[i][1]);
            fprintf(arquivo, "Media Trabalho: %.2f\n", statistics[i][2]);
            fprintf(arquivo, "Media final: %.2f\n", statistics[i][3]);
            fprintf(arquivo, "Porcentagem de aprovados: %.2f\n", (statistics[i][4])*100);
        }

        fclose(arquivo);
    }

    FILE* file = fopen("estat.bin", "wb");
    for (int i = 0; i < (c - 1); i++){
        fwrite(statistics[i], sizeof(float), COLUNAS, file);
    }
    fclose(file);
}

// END AUX FUNCTION