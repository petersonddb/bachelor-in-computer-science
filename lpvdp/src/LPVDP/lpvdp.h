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

#ifndef LPVDP_H
#define LPVDP_H

#include <gerenciador_terminais/gerenciador_terminais.h>
#include <estruturas_dados/ed_lista_linear_bidirecional.h>
#include <gerenciador_plugins/gerenciador_plugins.h>

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
    
    /* constantes */
#define LPVDP_GT_TERMINAL_NOME_TAMANHO GT_TERMINAL_NOME_TAMANHO
#define LPVDP_GT_TERMINAL_IP4_ENDERECO_TAMANHO GT_TERMINAL_IP4_ENDERECO_TAMANHO    
    
    typedef enum {
        LPVDP_INICIADO = 0x0,
        LPVDP_IMPRESSOS = 0x1,
        LPVDP_TESTES_CONCLUIDO = 0x2,
        LPVDP_GT_INCLUIDO = 0x3,
        LPVDP_GP_EXECUTADO = 0x4,
        LPVDP_PARALELIZADO = 0x5,
        LPVDP_CONEXAO_REDE_ABERTA = 0x6,
        LPVDP_GT_FALHA_ACESSO_BD = 0xFFFFFFFF,
        LPVDP_GT_NAO_ENCONTRADO = 0xFFFFFFFE,
        LPVDP_GT_FALHA_BD_SEEK = 0xFFFFFFFD,
        LPVDP_GT_FALHA_BD_ESCRITA = 0xFFFFFFFC,
        LPVDP_GT_FALHA_BD_LEITURA = 0xFFFFFFFB,
        LPVDP_LLBD_FALHA_NULA = 0xFFFFFFFA,
        LPVDP_GT_FALHA_NULO = 0xFFFFFFF9,
        LPVDP_LLBD_FALHA_PADRAO_NULO = 0xFFFFFFF8,
        LPVDP_LLBD_FALHA_TERMINAL_NAO_ENCONTRADO = 0xFFFFFFF7,
        LPVDP_GT_TESTES_FALHA = 0xFFFFFFF6,
        LPVDP_GP_FALHA_REPOSITORIO_NULO = 0xFFFFFFF5,
        LPVDP_GP_FALHA_CARREGAMENTO = 0xFFFFFFF4,
        LPVDP_FALHA_CB_SUCESSO_NULO = 0xFFFFFFF3,
        LPVDP_FALHA_CB_FRACASSO_NULO = 0xFFFFFFF2,
        LPVDP_GP_FALHA_NOME_NULO = 0xFFFFFFF1,
        LPVDP_FALHA_PARALELIZACAO = 0xFFFFFFF0,
        LPVDP_FALHA_TENTRADA = 0xFFFFFFEF,
        LPVDP_FALHA_ABRIR_CONEXAO_REDE = 0xFFFFFFEE,
        LPVDP_FALHA_GT_INDISPONIVEL = 0xFFFFFFED,
        LPVDP_FALHA_TRAVA_ESTADO = 0xFFFFFFEC,
        LPVDP_FALHA_FALTA_MEMORIA = 0xFFFFFFEB,
        LPVDP_DESCONHECIDO = 0x80000000
    } lpvdp_resultado;

    /* tipos */
    typedef int capacidade_t;
    typedef unsigned int tamanho_t;
    
    typedef struct {
        tamanho_t bytes;
        void *dados;
    } lpvdp_argumentos;
    
    typedef lpvdp_argumentos (*cb_sucesso) (lpvdp_argumentos);
    typedef void (*cb_fracasso) (lpvdp_resultado);
    
    typedef cb_sucesso gp_func;
    
    typedef void (*cb_msg) (lpvdp_resultado);
    
    /* interface */
    lpvdp_resultado lpvdp_init(capacidade_t, gt_porta_t);
    lpvdp_resultado lpvdp_testar(FILE *);
    lpvdp_resultado lpvdp_paralelizar(char *, char *, lpvdp_argumentos, cb_sucesso, cb_fracasso);
    
    lpvdp_resultado lpvdp_gt_incluir(gt_terminal);
    lpvdp_resultado lpvdp_gt_listar(FILE *);
    
    lpvdp_resultado lpvdp_gp_listar(FILE *);
    lpvdp_resultado lpvdp_gp_exec(gp_nome_t, cb_msg);

    char* lpvdp_str_resultado(lpvdp_resultado);
    lpvdp_resultado lpvdp_ed_llbd_mapear_resultado(ed_llbd_resultado);
    lpvdp_resultado lpvdp_gt_mapear_resultado(gt_resultado);
    lpvdp_resultado lpvdp_gp_mapear_resultado(gp_resultado);
    
#ifdef __cplusplus
}
#endif

#endif /* LPVDP_H */

