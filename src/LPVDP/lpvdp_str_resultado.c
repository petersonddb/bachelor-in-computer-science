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

#include <lpvdp.h>

#include <stdlib.h>
#include <string.h>

/* constantes */
#define LPVDP_INICIADO_MSG \
    "started"
#define LPVDP_IMPRESSOS_MSG \
    "printed"
#define LPVDP_TESTES_CONCLUIDO_MSG \
    "tests passed"
#define LPVDP_GT_INCLUIDO_MSG \
    "terminal included"
#define LPVDP_GP_EXECUTADO_MSG \
    "plugin executed"
#define LPVDP_PARALELIZADO_MSG \
    "task parallelized"
#define LPVDP_CONEXAO_REDE_ABERTA_MSG \
    "connected"
#define LPVDP_GT_FALHA_ACESSO_BD_MSG \
    "failed to connect to the terminals database"
#define LPVDP_GT_NAO_ENCONTRADO_MSG \
    "terminal not found"
#define LPVDP_GT_FALHA_BD_SEEK_MSG \
    "failed to seek the terminals database"
#define LPVDP_GT_FALHA_BD_ESCRITA_MSG \
    "failed to write onto the terminals database"
#define LPVDP_GT_FALHA_BD_LEITURA_MSG \
    "failed to read from the terminals database"
#define LPVDP_LLBD_FALHA_NULA_MSG \
    "null list llbd"
#define LPVDP_GT_FALHA_NULO_MSG \
    "null terminal"
#define LPVDP_LLBD_FALHA_PADRAO_NULO_MSG \
    "null search pattern"
#define LPVDP_LLBD_FALHA_TERMINAL_NAO_ENCONTRADO_MSG \
    "terminal not found in the list"
#define LPVDP_GT_TESTES_FALHA_MSG \
    "tests of terminals management failed"
#define LPVDP_GP_FALHA_REPOSITORIO_NULO_MSG \
    "null plugins repository"
#define LPVDP_GP_FALHA_CARREGAMENTO_MSG \
    "failed to load the plugin"
#define LPVDP_GP_FALHA_NOME_NULO_MSG \
    "null plugin name"
#define LPVDP_FALHA_PARALELIZACAO_MSG \
    "task could not be parallelized"
#define LPVDP_FALHA_TENTRADA_MSG \
    "failed to load the incoming thread"
#define LPVDP_FALHA_ABRIR_CONEXAO_REDE_MSG \
    "failed to connect"
#define LPVDP_FALHA_GT_INDISPONIVEL_MSG \
    "no terminals available"
#define LPVDP_FALHA_TRAVA_ESTADO_MSG \
    "the state lock failed"
#define LPVDP_FALHA_FALTA_MEMORIA_MSG \
    "no enough memory"
#define LPVDP_DESCONHECIDO_MSG \
    "unknown"


/**
 * retorna um texto explicando
 * um resultado
 * @param codigo o código do resultado
 * @return uma string explicando o resultado de código codigo
 */
char *lpvdp_str_resultado(lpvdp_resultado resultado) {
    char *msg;
    switch(resultado) {
        case LPVDP_INICIADO:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_INICIADO_MSG) + sizeof(char));
            strcpy(msg, LPVDP_INICIADO_MSG);
            break;
        case LPVDP_IMPRESSOS:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_IMPRESSOS_MSG) + sizeof(char));
            strcpy(msg, LPVDP_IMPRESSOS_MSG);
            break;
        case LPVDP_TESTES_CONCLUIDO:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_TESTES_CONCLUIDO_MSG) + sizeof(char));
            strcpy(msg, LPVDP_TESTES_CONCLUIDO_MSG);
            break;
        case LPVDP_GT_INCLUIDO:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_GT_INCLUIDO_MSG) + sizeof(char));
            strcpy(msg, LPVDP_GT_INCLUIDO_MSG);
            break;
        case LPVDP_GP_EXECUTADO:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_GP_EXECUTADO_MSG) + sizeof(char));
            strcpy(msg, LPVDP_GP_EXECUTADO_MSG);
            break;
        case LPVDP_PARALELIZADO:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_PARALELIZADO_MSG) + sizeof(char));
            strcpy(msg, LPVDP_PARALELIZADO_MSG);
            break;
        case LPVDP_CONEXAO_REDE_ABERTA:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_CONEXAO_REDE_ABERTA_MSG) + sizeof(char));
            strcpy(msg, LPVDP_CONEXAO_REDE_ABERTA_MSG);
            break;
        case LPVDP_GT_FALHA_ACESSO_BD:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_GT_FALHA_ACESSO_BD_MSG) + sizeof(char));
            strcpy(msg, LPVDP_GT_FALHA_ACESSO_BD_MSG);
            break;
        case LPVDP_GT_NAO_ENCONTRADO:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_GT_NAO_ENCONTRADO_MSG) + sizeof(char));
            strcpy(msg, LPVDP_GT_NAO_ENCONTRADO_MSG);
            break;
        case LPVDP_GT_FALHA_BD_SEEK:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_GT_FALHA_BD_SEEK_MSG) + sizeof(char));
            strcpy(msg, LPVDP_GT_FALHA_BD_SEEK_MSG);
            break;
        case LPVDP_GT_FALHA_BD_ESCRITA:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_GT_FALHA_BD_ESCRITA_MSG) + sizeof(char));
            strcpy(msg, LPVDP_GT_FALHA_BD_ESCRITA_MSG);
            break;
        case LPVDP_GT_FALHA_BD_LEITURA:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_GT_FALHA_BD_LEITURA_MSG) + sizeof(char));
            strcpy(msg, LPVDP_GT_FALHA_BD_LEITURA_MSG);
            break;
        case LPVDP_LLBD_FALHA_NULA:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_LLBD_FALHA_NULA_MSG) + sizeof(char));
            strcpy(msg, LPVDP_LLBD_FALHA_NULA_MSG);
            break;
        case LPVDP_GT_FALHA_NULO:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_GT_FALHA_NULO_MSG) + sizeof(char));
            strcpy(msg, LPVDP_GT_FALHA_NULO_MSG);
            break;
        case LPVDP_LLBD_FALHA_PADRAO_NULO:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_LLBD_FALHA_PADRAO_NULO_MSG) + sizeof(char));
            strcpy(msg, LPVDP_LLBD_FALHA_PADRAO_NULO_MSG);
            break;
        case LPVDP_LLBD_FALHA_TERMINAL_NAO_ENCONTRADO:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_LLBD_FALHA_TERMINAL_NAO_ENCONTRADO_MSG) + sizeof(char));
            strcpy(msg, LPVDP_LLBD_FALHA_TERMINAL_NAO_ENCONTRADO_MSG);
            break;
        case LPVDP_GT_TESTES_FALHA:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_GT_TESTES_FALHA_MSG) + sizeof(char));
            strcpy(msg, LPVDP_GT_TESTES_FALHA_MSG);
            break;
        case LPVDP_GP_FALHA_REPOSITORIO_NULO:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_GP_FALHA_REPOSITORIO_NULO_MSG) + sizeof(char));
            strcpy(msg, LPVDP_GP_FALHA_REPOSITORIO_NULO_MSG);
            break;
        case LPVDP_GP_FALHA_CARREGAMENTO:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_GP_FALHA_CARREGAMENTO_MSG) + sizeof(char));
            strcpy(msg, LPVDP_GP_FALHA_CARREGAMENTO_MSG);
            break;
        case LPVDP_GP_FALHA_NOME_NULO:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_GP_FALHA_NOME_NULO_MSG) + sizeof(char));
            strcpy(msg, LPVDP_GP_FALHA_NOME_NULO_MSG);
            break;
        case LPVDP_FALHA_PARALELIZACAO:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_FALHA_PARALELIZACAO_MSG) + sizeof(char));
            strcpy(msg, LPVDP_FALHA_PARALELIZACAO_MSG);
            break;
        case LPVDP_FALHA_TENTRADA:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_FALHA_TENTRADA_MSG) + sizeof(char));
            strcpy(msg, LPVDP_FALHA_TENTRADA_MSG);
            break;
        case LPVDP_FALHA_ABRIR_CONEXAO_REDE:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_FALHA_ABRIR_CONEXAO_REDE_MSG) + sizeof(char));
            strcpy(msg, LPVDP_FALHA_ABRIR_CONEXAO_REDE_MSG);
            break;
        case LPVDP_FALHA_GT_INDISPONIVEL:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_FALHA_GT_INDISPONIVEL_MSG) + sizeof(char));
            strcpy(msg, LPVDP_FALHA_GT_INDISPONIVEL_MSG);
            break;
        case LPVDP_FALHA_TRAVA_ESTADO:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_FALHA_TRAVA_ESTADO_MSG) + sizeof(char));
            strcpy(msg, LPVDP_FALHA_TRAVA_ESTADO_MSG);
            break;
        case LPVDP_FALHA_FALTA_MEMORIA:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_FALHA_FALTA_MEMORIA_MSG) + sizeof(char));
            strcpy(msg, LPVDP_FALHA_FALTA_MEMORIA_MSG);
            break;
        default:
            msg = (char *) malloc(sizeof(char) * strlen(LPVDP_DESCONHECIDO_MSG) + sizeof(char));
            strcpy(msg, LPVDP_DESCONHECIDO_MSG);
    }
    return msg;
}
