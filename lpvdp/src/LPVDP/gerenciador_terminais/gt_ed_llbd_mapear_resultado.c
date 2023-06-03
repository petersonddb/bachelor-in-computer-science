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

/**
 * Mapeia um código de resultado de uma
 * operação em lista llbd para o
 * código de resultado correspondente de
 * uma operação de gerenciamento de 
 * terminais
 * @param ed_llbd_resultado  o código de resultado da operação em lista llbd
 * @return o código de resultado de operação de gerenciamento de terminais
 */
gt_resultado gt_ed_llbd_mapear_resultado(ed_llbd_resultado ed_llbd_resultado) {
    switch(ed_llbd_resultado) {
        case ED_LLBD_NULA: return GT_LLBD_FALHA_NULA;
        case ED_LLBD_NO_NULO: return GT_FALHA_NULO;
        case ED_LLBD_PADRAO_NULO: return GT_LLBD_FALHA_PADRAO_NULO;
        case ED_LLBD_NO_NAO_ENCONTRADO: return GT_LLBD_FALHA_TERMINAL_NAO_ENCONTRADO;
        default: return GT_FALHA_DESCONHECIDO;
    }
}
