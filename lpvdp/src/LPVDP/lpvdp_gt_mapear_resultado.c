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

/**
 * Mapeia um código de resultado de uma
 * operação em gerenciamento de terminal para o
 * código de resultado correspondente de
 * uma operação da plataforma
 * @param gt_r o código de resultado da operação em gerenciamento de terminais
 * @return o código de resultado de operação da plataforma
 */
lpvdp_resultado lpvdp_gt_mapear_resultado(gt_resultado gt_r) {
    switch(gt_r) {
        case GT_INCLUIDO: return LPVDP_DESCONHECIDO;
        case GT_REMOVIDO: return LPVDP_DESCONHECIDO;
        case GT_ATUALIZADO: return LPVDP_DESCONHECIDO;
        case GT_ENCONTRADO: return LPVDP_DESCONHECIDO;
        case GT_NAO_ENCONTRADO: return LPVDP_GT_NAO_ENCONTRADO;
        case GT_CRIADO: return LPVDP_DESCONHECIDO;
        case GT_CARREGADOS: return LPVDP_DESCONHECIDO;
        case GT_TESTES_CONCLUIDO: return LPVDP_DESCONHECIDO;
        case GT_IMPRESSOS: return LPVDP_DESCONHECIDO;
        case GT_FALHA_BD_SEEK: return LPVDP_GT_FALHA_BD_SEEK;
        case GT_FALHA_BD_ESCRITA: return LPVDP_GT_FALHA_BD_ESCRITA;
        case GT_FALHA_BD_LEITURA: return LPVDP_GT_FALHA_BD_LEITURA;
        case GT_LLBD_FALHA_NULA: return LPVDP_LLBD_FALHA_NULA;
        case GT_FALHA_NULO: return LPVDP_GT_FALHA_NULO;
        case GT_LLBD_FALHA_PADRAO_NULO: return LPVDP_LLBD_FALHA_PADRAO_NULO;
        case GT_LLBD_FALHA_TERMINAL_NAO_ENCONTRADO: return LPVDP_LLBD_FALHA_TERMINAL_NAO_ENCONTRADO;
        case GT_TESTES_FALHA: return LPVDP_GT_TESTES_FALHA;
        default: return LPVDP_DESCONHECIDO;
    }
}
