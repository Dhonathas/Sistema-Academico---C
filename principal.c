#include <stdio.h>
#include <stdlib.h>
#include "sistema_academico.h"

int main(void) {
    t_curso curso;
    curso.quantidade_turmas = 0;
    curso.turmas = NULL;

    while (1) {
        exibir_menu();
        int opcao = obter_opcao_menu();
        processar_opcao_menu(opcao, &curso);
    }

    return 0;
}