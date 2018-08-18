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

#ifndef GERENCIADOR_TERMINAIS_H
#define GERENCIADOR_TERMINAIS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <fcntl.h>
#include <stdio.h>
#include <estruturas_dados/ed_lista_linear_bidirecional.h>
    
    /* constantes */
#define GT_TERMINAL_NOME_TAMANHO 20
#define GT_TERMINAL_IP4_ENDERECO_TAMANHO 20
#define GT_TERMINAL_IP6_ENDERECO_TAMANHO 20
#define GT_TERMINAL_ENDERECO_TAMANHO GT_TERMINAL_IP6_ENDERECO_TAMANHO + sizeof(unsigned int)
    
    typedef enum gt_bd_abertura_modo {
        GT_BD_ABERTURA_MODO_L = O_RDONLY,
        GT_BD_ABERTURA_MODO_E = O_WRONLY,
        GT_BD_ABERTURA_MODO_LE = O_RDWR,
    } gt_bd_abertura_modo;
    
    typedef enum gt_resultado {
        GT_INCLUIDO = 0x1,
        GT_REMOVIDO = 0x2,
        GT_ATUALIZADO = 0x3,
        GT_ENCONTRADO = 0x4,
        GT_NAO_ENCONTRADO = 0x5,
        GT_CRIADO = 0x6,
        GT_CARREGADOS = 0x7,
        GT_TESTES_CONCLUIDO = 0x8,
        GT_IMPRESSOS = 0x9,
        GT_FALHA_BD_SEEK = 0xFFFFFFFF,
        GT_FALHA_BD_ESCRITA = 0xFFFFFFFE,
        GT_FALHA_BD_LEITURA = 0xFFFFFFFD,
        GT_LLBD_FALHA_NULA = 0xFFFFFFFC,
        GT_FALHA_NULO = 0xFFFFFFFB,
        GT_LLBD_FALHA_PADRAO_NULO = 0xFFFFFFFA,
        GT_LLBD_FALHA_TERMINAL_NAO_ENCONTRADO = 0xFFFFFFF9,
        GT_TESTES_FALHA = 0xFFFFFFF8,
        GT_FALHA_DESCONHECIDO = 0x80000000
    } gt_resultado;
    
    /* tipos */
    typedef char gt_nome_t[GT_TERMINAL_NOME_TAMANHO],
            gt_ip4_t[GT_TERMINAL_IP4_ENDERECO_TAMANHO],
            gt_ip6_t[GT_TERMINAL_IP6_ENDERECO_TAMANHO],
            gt_endereco_t[GT_TERMINAL_ENDERECO_TAMANHO];
    
    typedef unsigned int gt_porta_t;
    
    /* estruturas */
    typedef struct gt_terminal {
        gt_nome_t nome;
        gt_endereco_t endereco;
    } gt_terminal;
    
    typedef struct gt_ip4_endereco {
        gt_ip4_t ip_endereco;
        gt_porta_t porta;
    } gt_ip4_endereco;
    
    typedef struct gt_ip6_endereco {
        gt_ip6_t ip_endereco;
        gt_porta_t porta;
    } gt_ip6_endereco;
       
    /* interface */
    int gt_bd_abrir(gt_bd_abertura_modo);
    int gt_bd_fechar(int);
    
    gt_resultado gt_bd_incluir(gt_terminal, int);
    gt_resultado gt_bd_remover_por_nome(gt_nome_t, int);
    gt_resultado gt_bd_atualizar(gt_terminal, int);
    gt_resultado gt_bd_buscar_por_nome(gt_nome_t, gt_terminal *, int);
    gt_resultado gt_bd_buscar(ed_llbd *, int);
    gt_resultado gt_bd_imprimir_ipv4(FILE *, int);
    
    gt_resultado gt_criar(gt_terminal **);
    
    void gt_obter_endereco_de_ip4(gt_endereco_t, gt_ip4_endereco);
    void gt_obter_endereco_de_ip6(gt_endereco_t, gt_ip6_endereco);
    
    gt_ip4_endereco gt_obter_ip4_de_endereco(gt_endereco_t);
    gt_ip6_endereco gt_obter_ip6_de_endereco(gt_endereco_t);

    gt_terminal gt_obter_terminal_ip4(gt_nome_t, gt_ip4_t, gt_porta_t);
    gt_terminal gt_obter_terminal_ip6(gt_nome_t, gt_ip6_t, gt_porta_t);
    
    gt_resultado gt_ed_llbd_adicionar(ed_llbd *, gt_terminal *);
    gt_resultado gt_ed_llbd_remover_por_nome(ed_llbd *, gt_nome_t);
    gt_resultado gt_ed_llbd_buscar_por_nome(ed_llbd, gt_nome_t, gt_terminal **);
    gt_resultado gt_ed_llbd_imprimir_ipv4(ed_llbd, FILE *);
    
    gt_resultado gt_ed_llbd_mapear_resultado(ed_llbd_resultado);
    char *gt_str_resultado(gt_resultado);
    
    gt_resultado gt_testar(FILE *);
    
#ifdef __cplusplus
}
#endif

#endif /* GERENCIADOR_TERMINAIS_H */
