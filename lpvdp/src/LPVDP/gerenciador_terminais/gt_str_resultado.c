/**
 *   LPVDP - Layered Parallel Virtual Distributed Platform
 *   Copyright (C) 2018 Peterson Daronch de Bem (petersondaronch@gmail.com)
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as published by
 *   the Free Software Foundation, version 3 of the License.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <gerenciador_terminais.h>

#include <stdlib.h>
#include <string.h>

/* constantes */
#define GT_RESULTADO_MSG_INCLUIDO \
    "terminal included"
#define GT_RESULTADO_MSG_REMOVIDO \
    "terminal removed"
#define GT_RESULTADO_MSG_ATUALIZADO \
    "terminal updated"
#define GT_RESULTADO_MSG_ENCONTRADO \
    "terminal found"
#define GT_RESULTADO_MSG_CRIADO \
    "terminal created"
#define GT_RESULTADO_MSG_CARREGADOS \
    "terminals loaded"
#define GT_RESULTADO_MSG_TESTES_CONCLUIDO \
    "tests passed"
#define GT_RESULTADO_MSG_NAO_ENCONTRADO \
    "nothing found"
#define GT_RESULTADO_MSG_FALHA_BD_SEEK \
    "failed to seek the database"
#define GT_RESULTADO_MSG_FALHA_BD_ESCRITA \
    "failed to write on the database"
#define GT_RESULTADO_MSG_FALHA_BD_LEITURA \
    "failed to read from the database"
#define GT_RESULTADO_MSG_LLBD_FALHA_NULA \
    "list llbd are null"
#define GT_RESULTADO_MSG_FALHA_NULO \
    "null terminal"
#define GT_RESULTADO_MSG_LLBD_FALHA_PADRAO_NULO \
    "search pattern are empty/null"
#define GT_RESULTADO_MSG_LLBD_FALHA_TERMINAL_NAO_ENCONTRADO \
    "terminal not found in the list"
#define GT_RESULTADO_MSG_TESTES_FALHA \
    "tests failed"
#define GT_RESULTADO_MSG_DESCONHECIDO \
    "unknown"


/**
 * retorna um texto explicando
 * um resultado
 * @param codigo o código do resultado
 * @return uma string explicando o resultado de código codigo
 */
char *gt_str_resultado(gt_resultado resultado) {
    char *msg;
    switch(resultado) {
        case GT_INCLUIDO:
            msg = (char *) malloc(sizeof(char) * strlen(GT_RESULTADO_MSG_INCLUIDO) + sizeof(char));
            strcpy(msg, GT_RESULTADO_MSG_INCLUIDO);
            break;
        case GT_REMOVIDO:
            msg = (char *) malloc(sizeof(char) * strlen(GT_RESULTADO_MSG_REMOVIDO) + sizeof(char));
            strcpy(msg, GT_RESULTADO_MSG_REMOVIDO);
            break;
        case GT_ATUALIZADO:
            msg = (char *) malloc(sizeof(char) * strlen(GT_RESULTADO_MSG_ATUALIZADO) + sizeof(char));
            strcpy(msg, GT_RESULTADO_MSG_ATUALIZADO);
            break;
        case GT_ENCONTRADO:
            msg = (char *) malloc(sizeof(char) * strlen(GT_RESULTADO_MSG_ENCONTRADO) + sizeof(char));
            strcpy(msg, GT_RESULTADO_MSG_ENCONTRADO);
            break;
        case GT_NAO_ENCONTRADO:
            msg = (char *) malloc(sizeof(char) * strlen(GT_RESULTADO_MSG_NAO_ENCONTRADO) + sizeof(char));
            strcpy(msg, GT_RESULTADO_MSG_NAO_ENCONTRADO);
            break;
        case GT_CRIADO:
            msg = (char *) malloc(sizeof(char) * strlen(GT_RESULTADO_MSG_CRIADO) + sizeof(char));
            strcpy(msg, GT_RESULTADO_MSG_CRIADO);
            break;
        case GT_CARREGADOS:
            msg = (char *) malloc(sizeof(char) * strlen(GT_RESULTADO_MSG_CARREGADOS) + sizeof(char));
            strcpy(msg, GT_RESULTADO_MSG_CARREGADOS);
            break;
        case GT_TESTES_CONCLUIDO:
            msg = (char *) malloc(sizeof(char) * strlen(GT_RESULTADO_MSG_TESTES_CONCLUIDO) + sizeof(char));
            strcpy(msg, GT_RESULTADO_MSG_TESTES_CONCLUIDO);
            break;
        case GT_FALHA_BD_SEEK:
            msg = (char *) malloc(sizeof(char) * strlen(GT_RESULTADO_MSG_FALHA_BD_SEEK) + sizeof(char));
            strcpy(msg, GT_RESULTADO_MSG_FALHA_BD_SEEK);
            break;
        case GT_FALHA_BD_ESCRITA:
            msg = (char *) malloc(sizeof(char) * strlen(GT_RESULTADO_MSG_FALHA_BD_ESCRITA) + sizeof(char));
            strcpy(msg, GT_RESULTADO_MSG_FALHA_BD_ESCRITA);
            break;
        case GT_FALHA_BD_LEITURA:
            msg = (char *) malloc(sizeof(char) * strlen(GT_RESULTADO_MSG_FALHA_BD_LEITURA) + sizeof(char));
            strcpy(msg, GT_RESULTADO_MSG_FALHA_BD_LEITURA);
            break;
        case GT_LLBD_FALHA_NULA:
            msg = (char *) malloc(sizeof(char) * strlen(GT_RESULTADO_MSG_LLBD_FALHA_NULA) + sizeof(char));
            strcpy(msg, GT_RESULTADO_MSG_LLBD_FALHA_NULA);
            break;
        case GT_FALHA_NULO:
            msg = (char *) malloc(sizeof(char) * strlen(GT_RESULTADO_MSG_FALHA_NULO) + sizeof(char));
            strcpy(msg, GT_RESULTADO_MSG_FALHA_NULO);
            break;
        case GT_LLBD_FALHA_PADRAO_NULO:
            msg = (char *) malloc(sizeof(char) * strlen(GT_RESULTADO_MSG_LLBD_FALHA_PADRAO_NULO) + sizeof(char));
            strcpy(msg, GT_RESULTADO_MSG_LLBD_FALHA_PADRAO_NULO);
            break;
        case GT_LLBD_FALHA_TERMINAL_NAO_ENCONTRADO:
            msg = (char *) malloc(sizeof(char) * strlen(GT_RESULTADO_MSG_LLBD_FALHA_TERMINAL_NAO_ENCONTRADO) + sizeof(char));
            strcpy(msg, GT_RESULTADO_MSG_LLBD_FALHA_TERMINAL_NAO_ENCONTRADO);
            break;
        case GT_TESTES_FALHA:
            msg = (char *) malloc(sizeof(char) * strlen(GT_RESULTADO_MSG_TESTES_FALHA) + sizeof(char));
            strcpy(msg, GT_RESULTADO_MSG_TESTES_FALHA);
            break;
        default:
            msg = (char *) malloc(sizeof(char) * strlen(GT_RESULTADO_MSG_DESCONHECIDO) + sizeof(char));
            strcpy(msg, GT_RESULTADO_MSG_DESCONHECIDO);
    }
    return msg;
}
