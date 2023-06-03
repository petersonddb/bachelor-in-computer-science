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

#ifndef GERENCIADOR_PLUGINS_H
#define GERENCIADOR_PLUGINS_H

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GP_REPOSITORIO "lpvdp_plugins"

    /* constantes */
#define GP_NOME_TAMANHO 256 /* Vindo de struct dirent, nao ha uma constante existente la */
#define GP_FUNC_NOME_TAMANHO 256
    
    typedef enum gp_resultado {
        GP_IMPRESSOS = 0x0,
        GP_TESTES_CONCLUIDO = 0x1,
        GP_EXECUTADO = 0x2,
        GP_COPIADO = 0x3, 
        GP_FALHA_REPOSITORIO_NULO = 0xFFFFFFFF,
        GP_FALHA_CARREGAMENTO = 0xFFFFFFFE,
        GP_FALHA_TESTES = 0xFFFFFFFD,
        GP_FALHA_NOME_NULO = 0xFFFFFFFC,
        GP_DESCONHECIDO = 0x80000000
    } gp_resultado;
    
    /* tipos */
    typedef char gp_nome_t[GP_NOME_TAMANHO];
    typedef char* gp_caminho_t;
    typedef char gp_func_nome_t[GP_FUNC_NOME_TAMANHO];
    
    /* interface */
    DIR *gp_abrir();
    gp_resultado gp_fechar(DIR *);
    gp_resultado gp_imprimir(FILE *, DIR *);
    gp_resultado gp_exec(gp_caminho_t);

    gp_resultado gp_obter_nome(char *, gp_nome_t);
    gp_caminho_t gp_obter_caminho(gp_nome_t);
    gp_resultado gp_func_obter_nome(char *, gp_func_nome_t);
    
    gp_resultado gp_testar(FILE *);
    
    char *gp_str_resultado(gp_resultado);

    char *gp_get_from_homed(char *);
    
#ifdef __cplusplus
}
#endif

#endif /* GERENCIADOR_PLUGINS_H */

