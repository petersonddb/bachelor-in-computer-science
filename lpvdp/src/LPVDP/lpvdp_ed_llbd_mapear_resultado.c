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
 * operação em uma lista llbd para o
 * código de resultado correspondente de
 * uma operação da plataforma
 * @param ed_llbd_r o código de resultado da operação em lista llbd
 * @return o código de resultado de operação da plataforma
 */
lpvdp_resultado lpvdp_ed_llbd_mapear_resultado(ed_llbd_resultado ed_llbd_r) {
    switch(ed_llbd_r) {
        case ED_LLBD_NULA: return LPVDP_LLBD_FALHA_NULA;
        default: return LPVDP_DESCONHECIDO;
    }
}
