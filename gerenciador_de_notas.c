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

void read_student (aluno* student, int number_of_students, int total_students, int c);
/*
Protótipo: void read_student (aluno* , int, int, int);

Parâmetros: (aluno* ) array struct aluno, (int) número de alunos da turma que está sendo cadastrada, (int) número 
total de alunos (todas as turmas) e (int) número de turmas (classes).

Objetivos: ler as informações do aluno que está sendo registrado e armazená-las no array struct aluno, sendo que a
posição do aluno no array é definida pela ordem de cadastro no sistema.
*/

void print_student (aluno* student, int pos);
/*
Protótipo: void print_student (aluno* , int );

Parâmetros: (aluno*) array struct aluno e (int) posição do aluno no array.

Objetivos: imprime as informações do aluno que está na posição "pos" do array.
*/

aluno* allocate_StudentArray (int number_of_students);
/*
Protótipo: aluno* allocate_StudentArray (int );

Parâmetros: (int) número de alunos da primeira turma cadastrada.

Objetivos: aloca dinamicamente o array de structs aluno.

Retorno: array de structs aluno.
*/

void realloc_StudentArray (aluno* student, int total_students, int number_of_students);
/*
Protótipo: void realloc_StudentArray (aluno* , int, int);

Parâmetros: (aluno*) array struct aluno, (int) número total de alunos (todas as turmas) e (int) número de alunos 
da turma que está sendo cadastrada.

Objetivos: realoca dinamicamente o array de structs aluno a cada turma registrada, visando acomodar todos os
alunos cadastrados.
*/

void search_StudentByName (aluno* student, int pos, int num, char name[16], char last_name[16]);
/*
Protótipo: void search_StudentByName (aluno* , int, int, char*, char*);

Parâmetros: (aluno*) array struct aluno, (int) posição inicial de busca no array, (int) número de posições no array,
(char*) nome do aluno buscado e (char*) sobrenome do aluno buscado.

Objetivos: buscar, de forma recursiva, a posição do aluno que o usúario digitou o nome completo. Tal função imprime
"Aluno não encontrado", caso o aluno não tenha sido cadastrado, ou imprime os dados do aluno buscado, por meio da função 
print_student().
*/

float** allocate_statistics (int c);
/*
Protótipo: float** allocate_statistics (int );

Parâmetros: (int) número de turmas cadastradas.

Objetivos: aloca dinamicamente um matriz com "c" linhas, isto é, uma linha para cada turma, e 5 colunas, sendo que a primeira 
contem a média da turma na primeira avaliação; a segunda, na segunda avaliação; a terceira, no trabalho; a quarta, a média da 
nota final da turma; e a última a porcentagem de alunos aprovados, sendo que um aluno é aprovado se sua média final é igual ou 
maior do que 5.

Retorno: matriz de elementos float.
*/

void realloc_statistics (int c, float** statistics);
/*
Protótipo: void realloc_statistics (int , float** );

Parâmetros: (int) número de turmas cadastradas e (float**) matriz de elementos float com as estatísticas das turmas.

Objetivos: realoca dinamicamente a matriz "statistics" a cada nova turma cadastrada, visando aumentar o seu número de linhas,
de forma a comportar uma nova turma.
*/

void generate_statistics (int c, aluno* student, int total_students, int number_of_students, float** statistics);
/*
Protótipo: void generate_statistics (int , aluno* , int , int , float** );

Parâmetros: (int) número de turmas cadastradas, (aluno*) array de structs aluno, (int) número total de alunos (todas as turmas),
(int) número de estudantes da turma que está sendo cadastrada e (float**) matriz de elementos float com as estatísticas das turmas.

Objetivos: gera todas as estatísticas da turma que está sendo cadastrada (média na primeira avaliação, média na segunda avaliação, 
média no trabalho, média final e porcentagem de aprovados) e guarda esses dados na matriz "statistics".
*/

void free_statistics (float** statistics, int c);
/*
Protótipo: void free_statistics (float** , int );

Parâmetros: (float**) matriz de elementos float com as estatísticas das turmas e (int) número de turmas cadastradas (e, por consequência,
o número de linhas da matriz de elementos float).

Objetivos: desaloca dinamicamente a matriz "statistics", liberando o espaço de memória.
*/

void print_statistics (float** statistics);
/*
Protótipo: void print_statistics (float** );

Parâmetros: (float**) matriz de elementos float com as estatísticas das turmas.

Objetivos: recebe, como input, o número da turma para a qual o usuário deseja receber informações e imprime no terminal as estatíticas
dessa turma.
*/

aluno* create_class (int c, float** statistics, int number_of_students, int total_students);
/*
Protótipo: aluno* create_class (int , float** , int , int );

Parâmetros: (int) número de turmas cadastradas, (float**) matriz de elementos float com as estatísticas das turmas, (int) número de 
estudantes da turma que está sendo cadastrada e (int) número total de alunos (todas as turmas).

Objetivos: função que aglutina as funções allocate_StudentArray(), read_student() e generate_statistics(), visando formar um bloco de 
cadastro de uma turma. Essa função cria a primeira turma e as demais turmas são criadas pela função realloc_class().

Retorno: array de structs aluno.
*/

void realloc_class (aluno* student, int c, float** statistics, int number_of_students, int total_students);
/*
Protótipo: aluno* realloc_class (aluno* , int , float** , int , int );

Parâmetros: (aluno*) array de struct aluno, (int) número de turmas cadastradas, (float**) matriz de elementos float com as estatísticas 
das turmas, (int) número de estudantes da turma que está sendo cadastrada e (int) número total de alunos (todas as turmas).

Objetivos: função que aglutina as funções realloc_StudentArray(), read_student() e generate_statistics(), visando formar um bloco de 
cadastro de uma turma.
*/

void save_data (float** statistics, int c);
/*
Protótipo: void save_data (float** , int );

Parâmetros: (float**) matriz de elementos float com as estatísticas das turmas e (int) número de turmas cadastradas (e, por consequência,
o número de linhas da matriz de elementos float).

Objetivos: gera arquivos textos para cada uma das turmas, contendo as estatísticas de cada uma delas, sendo o nome do arquivo é inserido pelo
usuário. Além disso, também gera um arquivo binário contendo as estatísticas de todas as turmas, sendo que esse arquivo tem o nome "estat.bin".
*/

// END PROTOTYPES


// MAIN FUNCTION

int main(){

    int c = 1;
    int total_students = 0;
    int opcao;
    int number_of_students;

    float** statistics = NULL;
    aluno* student;

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
                
                // Cadastro da primeira turma
                if (c == 1){                                                            
                    statistics = allocate_statistics(c);
                    student = create_class(c, statistics, number_of_students, total_students);
                }

                else{
                    realloc_statistics(c, statistics);
                    realloc_class(student, c, statistics, number_of_students, total_students);
                }

                c++;
                total_students = total_students + number_of_students;

                break;
            case 2: 
                printf("----------------------------------------------------------\n");
                printf("Digite o nome completo do aluno que procura: ");
                scanf("%s %s", name, last_name);

                search_StudentByName(student, (total_students - 1), (total_students - 1), name, last_name);
                break;
            case 3:
                print_statistics (statistics);
                break;
            case 4:
                save_data (statistics, c);                
                break;
            case 5:
                free_statistics (statistics, c);
                free(student);
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
    aluno* student = (aluno*) malloc (number_of_students * sizeof(aluno));
    return student;
}

void realloc_StudentArray (aluno* student, int total_students, int number_of_students){
    student = (aluno*) realloc (student, (total_students + number_of_students) * sizeof(aluno));
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

void search_StudentByName (aluno* student, int pos, int num, char name[16], char last_name[16]){

    if (pos == -1){
        printf("Aluno nao encontrado.\n");
    }
    else if (strncmp(name, student[pos].nome, strlen(student[pos].nome)) == 0 && strncmp(last_name, student[pos].sobrenome, strlen(student[pos].sobrenome)) == 0){
        print_student(student, pos);
    }
    else {
        pos--;
        search_StudentByName(student, pos, num, name, last_name);
    }
}

void generate_statistics (int c, aluno* student, int total_students, int number_of_students, float** statistics){
    float soma_p1 = 0;
    float soma_p2 = 0;
    float soma_trab = 0;
    float soma_med = 0;
    float soma_aprovados = 0;

    for (int i = total_students; i < (number_of_students + total_students); i++){
        soma_p1 = soma_p1 + student[i].p1;
        soma_p2 = soma_p2 + student[i].p2;
        soma_trab = soma_trab + student[i].trabalho;
        soma_med = soma_med + student[i].media;
        if (student[i].media >= 5) soma_aprovados++;
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
    aluno* student = allocate_StudentArray(number_of_students);
    
    printf("           -- Entre com os dados dos alunos --            \n");
    read_student(student, number_of_students, total_students, c);

    generate_statistics (c, student, total_students, number_of_students, statistics);

    return student;
}

void realloc_class (aluno* student, int c, float** statistics, int number_of_students, int total_students){
    realloc_StudentArray (student, total_students, number_of_students);

    printf("           -- Entre com os dados dos alunos --            \n");
    read_student(student, number_of_students, total_students, c);

    generate_statistics (c, student, total_students, number_of_students, statistics);
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