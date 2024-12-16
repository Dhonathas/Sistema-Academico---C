#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema_academico.h"

void exibir_menu(void) {
    printf("\n===== Sistema Academico =====\n");
    printf("1. Inserir turma\n");
    printf("2. Inserir disciplina\n");
    printf("3. Inserir aluno\n");
    printf("4. Remover turma\n");
    printf("5. Remover disciplina\n");
    printf("6. Remover aluno\n");
    printf("7. Listar turmas\n");
    printf("8. Listar disciplinas\n");
    printf("9. Listar alunos\n");
    printf("10. Gerenciar arquivos\n");
    printf("11. Sair\n");
}

void exibir_menu_arquivos(void) {
    printf("\n===== Gerenciamento de Arquivos =====\n");
    printf("1. Ler dados\n");
    printf("2. Salvar dados\n");
    printf("3. Voltar\n");
}

int obter_opcao_menu(void) {
    int opcao;
    printf("\nDigite a opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

void processar_opcao_menu(int opcao, t_curso* curso) {
    switch (opcao) {
        case 1: inserir_turma(curso); break;
        case 2: {
            t_turma* turma = obter_turma(curso);
            if (turma) inserir_disciplina(turma);
            break;
        }
        case 3: {
            t_turma* turma = obter_turma(curso);
            if (turma) {
                t_disciplina* disciplina = obter_disciplina(turma);
                if (disciplina) inserir_aluno(disciplina);
            }
            break;
        }
        case 4: {
            int numero_turma;
            printf("Digite o numero da turma para remover: ");
            scanf("%d", &numero_turma);
            remover_turma(curso, numero_turma);
            break;
        }
        case 5: {
            t_turma* turma = obter_turma(curso);
            if (turma) {
                int codigo_disciplina;
                printf("Digite o codigo da disciplina para remover: ");
                scanf("%d", &codigo_disciplina);
                remover_disciplina(turma, codigo_disciplina);
            }
            break;
        }
        case 6: {
            t_turma* turma = obter_turma(curso);
            if (turma) {
                t_disciplina* disciplina = obter_disciplina(turma);
                if (disciplina) {
                    int matricula_aluno;
                    printf("Digite a matricula do aluno para remover: ");
                    scanf("%d", &matricula_aluno);
                    remover_aluno(disciplina, matricula_aluno);
                }
            }
            break;
        }
        case 7: listar_turmas(curso); break;
        case 8: {
            t_turma* turma = obter_turma(curso);
            if (turma) listar_disciplinas(turma);
            break;
        }
        case 9: {
            t_turma* turma = obter_turma(curso);
            if (turma) {
                t_disciplina* disciplina = obter_disciplina(turma);
                if (disciplina) listar_alunos(disciplina);
            }
            break;
        }
        case 10: {
            exibir_menu_arquivos();
            int opcao_arquivos = obter_opcao_menu();
            if (opcao_arquivos == 1) ler_arquivos();
            else if (opcao_arquivos == 2) salvar_dados(curso);
            break;
        }
        case 11: exit(0); break;
        default: printf("Opcao invalida!\n"); break;
    }
}

void inserir_turma(t_curso* curso) {
    t_turma nova_turma;
    printf("Digite o numero da turma: ");
    scanf("%d", &nova_turma.numero);
    nova_turma.nome = (char*)malloc(100 * sizeof(char));
    printf("Digite o nome da turma: ");
    scanf("%s", nova_turma.nome);

    nova_turma.quantidade_disciplinas = 0;
    nova_turma.disciplinas = NULL;

    curso->quantidade_turmas++;
    curso->turmas = (t_turma*)realloc(curso->turmas, curso->quantidade_turmas * sizeof(t_turma));
    curso->turmas[curso->quantidade_turmas - 1] = nova_turma;
}

void inserir_disciplina(t_turma* turma) {
    t_disciplina nova_disciplina;
    printf("Digite o codigo da disciplina: ");
    scanf("%d", &nova_disciplina.codigo);
    nova_disciplina.nome = (char*)malloc(100 * sizeof(char));
    printf("Digite o nome da disciplina: ");
    scanf("%s", nova_disciplina.nome);

    nova_disciplina.quantidade_alunos = 0;
    nova_disciplina.alunos = NULL;

    turma->quantidade_disciplinas++;
    turma->disciplinas = (t_disciplina*)realloc(turma->disciplinas, turma->quantidade_disciplinas * sizeof(t_disciplina));
    turma->disciplinas[turma->quantidade_disciplinas - 1] = nova_disciplina;
}

void inserir_aluno(t_disciplina* disciplina) {
    t_aluno novo_aluno;
    printf("Digite a matricula do aluno: ");
    scanf("%d", &novo_aluno.matricula);
    novo_aluno.nome = (char*)malloc(100 * sizeof(char));
    printf("Digite o nome do aluno: ");
    scanf("%s", novo_aluno.nome);

    disciplina->quantidade_alunos++;
    disciplina->alunos = (t_aluno*)realloc(disciplina->alunos, disciplina->quantidade_alunos * sizeof(t_aluno));
    disciplina->alunos[disciplina->quantidade_alunos - 1] = novo_aluno;
}

void listar_turmas(t_curso* curso) {
    for (int i = 0; i < curso->quantidade_turmas; i++) {
        printf("Turma: %d, Nome: %s\n", curso->turmas[i].numero, curso->turmas[i].nome);
    }
}

void listar_disciplinas(t_turma* turma) {
    for (int i = 0; i < turma->quantidade_disciplinas; i++) {
        printf("Disciplina: %d, Nome: %s\n", turma->disciplinas[i].codigo, turma->disciplinas[i].nome);
    }
}

void listar_alunos(t_disciplina* disciplina) {
    for (int i = 0; i < disciplina->quantidade_alunos; i++) {
        printf("Aluno: %d, Nome: %s\n", disciplina->alunos[i].matricula, disciplina->alunos[i].nome);
    }
}

t_turma* obter_turma(t_curso* curso) {
    int numero_turma;
    printf("Digite o numero da turma: ");
    scanf("%d", &numero_turma);

    for (int i = 0; i < curso->quantidade_turmas; i++) {
        if (curso->turmas[i].numero == numero_turma) {
            return &curso->turmas[i];
        }
    }
    return NULL;
}

t_disciplina* obter_disciplina(t_turma* turma) {
    int codigo_disciplina;
    printf("Digite o codigo da disciplina: ");
    scanf("%d", &codigo_disciplina);

    for (int i = 0; i < turma->quantidade_disciplinas; i++) {
        if (turma->disciplinas[i].codigo == codigo_disciplina) {
            return &turma->disciplinas[i];
        }
    }
    return NULL;
}

void remover_turma(t_curso* curso, int numero_turma) {
    for (int i = 0; i < curso->quantidade_turmas; i++) {
        if (curso->turmas[i].numero == numero_turma) {
            free(curso->turmas[i].nome);
            for (int j = 0; j < curso->turmas[i].quantidade_disciplinas; j++) {
                free(curso->turmas[i].disciplinas[j].nome);
                for (int k = 0; k < curso->turmas[i].disciplinas[j].quantidade_alunos; k++) {
                    free(curso->turmas[i].disciplinas[j].alunos[k].nome);
                }
                free(curso->turmas[i].disciplinas[j].alunos);
                free(curso->turmas[i].disciplinas[j].nome);
            }
            free(curso->turmas[i].disciplinas);
            for (int j = i; j < curso->quantidade_turmas - 1; j++) {
                curso->turmas[j] = curso->turmas[j + 1];
            }
            curso->quantidade_turmas--;
            curso->turmas = (t_turma*)realloc(curso->turmas, curso->quantidade_turmas * sizeof(t_turma));
            break;
        }
    }
}

void remover_disciplina(t_turma* turma, int codigo_disciplina) {
    for (int i = 0; i < turma->quantidade_disciplinas; i++) {
        if (turma->disciplinas[i].codigo == codigo_disciplina) {
            free(turma->disciplinas[i].nome);
            for (int j = 0; j < turma->disciplinas[i].quantidade_alunos; j++) {
                free(turma->disciplinas[i].alunos[j].nome);
            }
            free(turma->disciplinas[i].alunos);
            for (int j = i; j < turma->quantidade_disciplinas - 1; j++) {
                turma->disciplinas[j] = turma->disciplinas[j + 1];
            }
            turma->quantidade_disciplinas--;
            turma->disciplinas = (t_disciplina*)realloc(turma->disciplinas, turma->quantidade_disciplinas * sizeof(t_disciplina));
            break;
        }
    }
}

void remover_aluno(t_disciplina* disciplina, int matricula_aluno) {
    for (int i = 0; i < disciplina->quantidade_alunos; i++) {
        if (disciplina->alunos[i].matricula == matricula_aluno) {
            free(disciplina->alunos[i].nome);
            for (int j = i; j < disciplina->quantidade_alunos - 1; j++) {
                disciplina->alunos[j] = disciplina->alunos[j + 1];
            }
            disciplina->quantidade_alunos--;
            disciplina->alunos = (t_aluno*)realloc(disciplina->alunos, disciplina->quantidade_alunos * sizeof(t_aluno));
            break;
        }
    }
}

void salvar_dados(t_curso* curso) {
    FILE *arquivo_turmas = fopen("turmas.txt", "w");
    FILE *arquivo_disciplinas = fopen("disciplinas.txt", "w");
    FILE *arquivo_alunos = fopen("alunos.txt", "w");

    if (!arquivo_turmas || !arquivo_disciplinas || !arquivo_alunos) {
        printf("Erro ao abrir os arquivos para salvar dados.\n");
        return;
    }

    for (int i = 0; i < curso->quantidade_turmas; i++) {
        fprintf(arquivo_turmas, "%d %s\n", curso->turmas[i].numero, curso->turmas[i].nome);
        for (int j = 0; j < curso->turmas[i].quantidade_disciplinas; j++) {
            fprintf(arquivo_disciplinas, "%d %s %d\n", curso->turmas[i].disciplinas[j].codigo, curso->turmas[i].disciplinas[j].nome, curso->turmas[i].disciplinas[j].quantidade_alunos);
            for (int k = 0; k < curso->turmas[i].disciplinas[j].quantidade_alunos; k++) {
                fprintf(arquivo_alunos, "%d %s %d\n", curso->turmas[i].disciplinas[j].alunos[k].matricula, curso->turmas[i].disciplinas[j].alunos[k].nome, curso->turmas[i].numero);
            }
        }
    }

    fclose(arquivo_turmas);
    fclose(arquivo_disciplinas);
    fclose(arquivo_alunos);

    printf("Dados salvos com sucesso.\n");
}

void ler_arquivos(void) {
    FILE *arquivo_turmas = fopen("turmas.txt", "r");
    FILE *arquivo_disciplinas = fopen("disciplinas.txt", "r");
    FILE *arquivo_alunos = fopen("alunos.txt", "r");

    if (!arquivo_turmas || !arquivo_disciplinas || !arquivo_alunos) {
        printf("Erro ao abrir os arquivos para ler dados.\n");
        return;
    }

   
    printf("\n===== Turmas =====\n");
    while (!feof(arquivo_turmas)) {
        int numero_turma;
        char nome_turma[100];
        if (fscanf(arquivo_turmas, "%d %s", &numero_turma, nome_turma) == 2) {
            printf("Turma: %d, Nome: %s\n", numero_turma, nome_turma);
        }
    }

 
    printf("\n===== Disciplinas =====\n");
    while (!feof(arquivo_disciplinas)) {
        int codigo_disciplina, quantidade_alunos;
        char nome_disciplina[100];
        if (fscanf(arquivo_disciplinas, "%d %s %d", &codigo_disciplina, nome_disciplina, &quantidade_alunos) == 3) {
            printf("Disciplina: %d, Nome: %s, Quantidade de Alunos: %d\n", codigo_disciplina, nome_disciplina, quantidade_alunos);
        }
    }

    
    printf("\n===== Alunos =====\n");
    while (!feof(arquivo_alunos)) {
        int matricula_aluno, numero_turma;
        char nome_aluno[100];
        if (fscanf(arquivo_alunos, "%d %s %d", &matricula_aluno, nome_aluno, &numero_turma) == 3) {
            printf("Aluno: %d, Nome: %s, Matricula: %d, Turma: %d\n", matricula_aluno, nome_aluno, matricula_aluno, numero_turma);
        }
    }

    fclose(arquivo_turmas);
    fclose(arquivo_disciplinas);
    fclose(arquivo_alunos);

    printf("Dados lidos com sucesso.\n");
}

void liberar_memoria_curso(t_curso* curso) {
    for (int i = 0; i < curso->quantidade_turmas; i++) {
        liberar_memoria_turma(&curso->turmas[i]);
    }
    free(curso->turmas);
}

void liberar_memoria_turma(t_turma* turma) {
    free(turma->nome);
    for (int i = 0; i < turma->quantidade_disciplinas; i++) {
        liberar_memoria_disciplina(&turma->disciplinas[i]);
    }
    free(turma->disciplinas);
}

void liberar_memoria_disciplina(t_disciplina* disciplina) {
    free(disciplina->nome);
    for (int i = 0; i < disciplina->quantidade_alunos; i++) {
        liberar_memoria_aluno(&disciplina->alunos[i]);
    }
    free(disciplina->alunos);
}

void liberar_memoria_aluno(t_aluno* aluno) {
    free(aluno->nome);
}