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
 * Busca um terminal em uma lista de terminais
 * @param llbd uma lista llbd
 * @param nome o nome do terminal a buscar
 * @param o ponteiro para um ponteiro para colocar o terminal encontrado
 * @return o código de resultado
 */
gt_resultado gt_ed_llbd_buscar_por_nome(ed_llbd llbd, gt_nome_t nome, gt_terminal **ptr_t) {
    ed_llbd_no *no;
    ed_llbd_resultado llbd_resultado;
    
    if((llbd_resultado = ed_llbd_buscar_por_carga(llbd, &no, (void *) nome, 0, GT_TERMINAL_NOME_TAMANHO)) != ED_LLBD_NO_ENCONTRADO)
        return gt_ed_llbd_mapear_resultado(llbd_resultado);
    
    *ptr_t = (gt_terminal *) ed_llbd_no_obter_carga(*no);
    
    return GT_ENCONTRADO;
}
