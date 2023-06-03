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
 * Remove um terminal da lista
 * @param ptr_llbd o ponteiro para a lista llbd
 * @param nome o nome do terminal
 * @return o código de resultado
 */
gt_resultado gt_ed_llbd_remover_por_nome(ed_llbd *ptr_llbd, gt_nome_t nome) {
    ed_llbd_resultado llbd_resultado;
    
    if((llbd_resultado = ed_llbd_remover(ptr_llbd, (void *) nome, 0, GT_TERMINAL_NOME_TAMANHO)) != ED_LLBD_NO_REMOVIDO)
        return gt_ed_llbd_mapear_resultado(llbd_resultado);
    
    return GT_REMOVIDO;
}
