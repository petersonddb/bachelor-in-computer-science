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
    "incluido com sucesso"
#define GT_RESULTADO_MSG_REMOVIDO \
    "removido com sucesso"
#define GT_RESULTADO_MSG_ATUALIZADO \
    "atualizado com sucesso"
#define GT_RESULTADO_MSG_ENCONTRADO \
    "encontrado"
#define GT_RESULTADO_MSG_CRIADO \
    "criado"
#define GT_RESULTADO_MSG_CARREGADOS \
    "terminais carregados"
#define GT_RESULTADO_MSG_TESTES_CONCLUIDO \
    "testes concluídos com sucesso"
#define GT_RESULTADO_MSG_NAO_ENCONTRADO \
    "nao encontrado"
#define GT_RESULTADO_MSG_FALHA_BD_SEEK \
    "falha na operacao seek no BD"
#define GT_RESULTADO_MSG_FALHA_BD_ESCRITA \
    "falha na operacao de escrita no BD"
#define GT_RESULTADO_MSG_FALHA_BD_LEITURA \
    "falha na operacao de leitura no BD"
#define GT_RESULTADO_MSG_LLBD_FALHA_NULA \
    "lista llbd nula"
#define GT_RESULTADO_MSG_FALHA_NULO \
    "terminal nulo"
#define GT_RESULTADO_MSG_LLBD_FALHA_PADRAO_NULO \
    "padrão para busca está vazio/nulo"
#define GT_RESULTADO_MSG_LLBD_FALHA_TERMINAL_NAO_ENCONTRADO \
    "terminal não encontrado na lista"
#define GT_RESULTADO_MSG_TESTES_FALHA \
    "os testes falharam"
#define GT_RESULTADO_MSG_DESCONHECIDO \
    "desconhecido"


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
