#ifndef SISTEMA_ACADEMICO_H
#define SISTEMA_ACADEMICO_H

typedef struct {
    int matricula;
    char* nome;
} t_aluno;

typedef struct {
    int codigo;
    char* nome;
    t_aluno* alunos;
    int quantidade_alunos;
} t_disciplina;

typedef struct {
    int numero;
    char* nome;
    t_disciplina* disciplinas;
    int quantidade_disciplinas;
} t_turma;

typedef struct {
    t_turma* turmas;
    int quantidade_turmas;
} t_curso;

void exibir_menu(void);
void exibir_menu_arquivos(void);
int obter_opcao_menu(void);
void processar_opcao_menu(int opcao, t_curso* curso);
void inserir_turma(t_curso* curso);
void inserir_disciplina(t_turma* turma);
void inserir_aluno(t_disciplina* disciplina);
void remover_turma(t_curso* curso, int numero_turma);
void remover_disciplina(t_turma* turma, int codigo_disciplina);
void remover_aluno(t_disciplina* disciplina, int matricula_aluno);
void listar_turmas(t_curso* curso);
void listar_disciplinas(t_turma* turma);
void listar_alunos(t_disciplina* disciplina);
t_turma* obter_turma(t_curso* curso);
t_disciplina* obter_disciplina(t_turma* turma);
t_aluno* obter_aluno(t_disciplina* disciplina);
void liberar_memoria_curso(t_curso* curso);
void liberar_memoria_turma(t_turma* turma);
void liberar_memoria_disciplina(t_disciplina* disciplina);
void liberar_memoria_aluno(t_aluno* aluno);

void ler_arquivos(void);
void ler_turmas(void);
void ler_disciplinas(void);
void ler_alunos(void);
void salvar_dados(t_curso* curso);
void salvar_turmas(t_curso* curso);
void salvar_disciplinas(t_curso* curso);
void salvar_alunos(t_curso* curso);

#endif