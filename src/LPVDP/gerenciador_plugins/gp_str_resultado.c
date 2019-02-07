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

#include <gerenciador_plugins.h>

#include <stdlib.h>
#include <string.h>

/* constantes */
#define GP_IMPRESSOS_MSG \
    "plugins printed"
#define GP_TESTES_CONCLUIDO_MSG \
    "tests passed"
#define GP_EXECUTADO_MSG \
    "plugin executed"
#define GP_COPIADO_MSG \
    "plugin data copied"
#define GP_FALHA_REPOSITORIO_NULO_MSG \
    "null repository"
#define GP_FALHA_CARREGAMENTO_MSG \
    "failed to load the plugin"
#define GP_FALHA_TESTES_MSG \
    "tests failed"
#define GP_FALHA_NOME_NULO_MSG \
    "null name"
#define GP_DESCONHECIDO_MSG \
    "unknown"

/**
 * retorna um texto explicando
 * um resultado
 * @param codigo o código do resultado
 * @return uma string explicando o resultado de código codigo
 */
char *gp_str_resultado(gp_resultado resultado) {
    char *msg;
    switch(resultado) {
        case GP_IMPRESSOS:
            msg = (char *) malloc(sizeof(char) * strlen(GP_IMPRESSOS_MSG) + sizeof(char));
            strcpy(msg, GP_IMPRESSOS_MSG);
            break;
        case GP_TESTES_CONCLUIDO:
            msg = (char *) malloc(sizeof(char) * strlen(GP_TESTES_CONCLUIDO_MSG) + sizeof(char));
            strcpy(msg, GP_TESTES_CONCLUIDO_MSG);
            break;
        case GP_EXECUTADO:
            msg = (char *) malloc(sizeof(char) * strlen(GP_EXECUTADO_MSG) + sizeof(char));
            strcpy(msg, GP_EXECUTADO_MSG);
            break;
        case GP_COPIADO:
            msg = (char *) malloc(sizeof(char) * strlen(GP_COPIADO_MSG) + sizeof(char));
            strcpy(msg, GP_COPIADO_MSG);
            break;
        case GP_FALHA_REPOSITORIO_NULO:
            msg = (char *) malloc(sizeof(char) * strlen(GP_FALHA_REPOSITORIO_NULO_MSG) + sizeof(char));
            strcpy(msg, GP_FALHA_REPOSITORIO_NULO_MSG);
            break;
        case GP_FALHA_CARREGAMENTO:
            msg = (char *) malloc(sizeof(char) * strlen(GP_FALHA_CARREGAMENTO_MSG) + sizeof(char));
            strcpy(msg, GP_FALHA_CARREGAMENTO_MSG);
            break;
        case GP_FALHA_TESTES:
            msg = (char *) malloc(sizeof(char) * strlen(GP_FALHA_TESTES_MSG) + sizeof(char));
            strcpy(msg, GP_FALHA_TESTES_MSG);
            break;
        case GP_FALHA_NOME_NULO:
            msg = (char *) malloc(sizeof(char) * strlen(GP_FALHA_NOME_NULO_MSG) + sizeof(char));
            strcpy(msg, GP_FALHA_NOME_NULO_MSG);
            break;
        default:
            msg = (char *) malloc(sizeof(char) * strlen(GP_DESCONHECIDO_MSG) + sizeof(char));
            strcpy(msg, GP_DESCONHECIDO_MSG);
    }
    return msg;
}
