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

#include <ed_lista_linear_bidirecional.h>

/**
 * Adiciona um novo nó na lista
 * linear bidirecional
 * @param ptr_llbd um ponteiro para uma lista llbd
 * @param ptr_no um ponteiro para um nó llbd
 * @return o código de resultado
 */
ed_llbd_resultado ed_llbd_adicionar(ed_llbd *ptr_llbd, ed_llbd_no *ptr_no) {
    
    ed_llbd_resultado resultado;
    
    if(ptr_llbd == NULL)
        return ED_LLBD_NULA;
    if(ptr_no == NULL)
        return ED_LLBD_NO_NULO;
    
    if((resultado = ed_llbd_no_conf_proximo(ptr_no, NULL)) != ED_LLBD_NO_ATUALIZADO)
        return resultado;
    if(ed_llbd_vazia(*ptr_llbd) == ED_LLBD_VAZIA) {
        if((resultado = ed_llbd_conf_primeiro(ptr_llbd, ptr_no)) != ED_LLBD_ATUALIZADA || 
           (resultado = ed_llbd_conf_ultimo(ptr_llbd, ptr_no)) != ED_LLBD_ATUALIZADA ||
           (resultado = ed_llbd_no_conf_anterior(ptr_no, NULL)) != ED_LLBD_NO_ATUALIZADO)
            return resultado;
    } else {
        if((resultado = ed_llbd_no_conf_anterior(ptr_no, ed_llbd_obter_ultimo(*ptr_llbd))) != ED_LLBD_NO_ATUALIZADO ||
           (resultado = ed_llbd_no_conf_proximo(ed_llbd_obter_ultimo(*ptr_llbd), ptr_no)) != ED_LLBD_NO_ATUALIZADO ||
           (resultado = ed_llbd_conf_ultimo(ptr_llbd, ptr_no)) != ED_LLBD_ATUALIZADA)
            return resultado;
    }
    
    return ED_LLBD_ATUALIZADA;
    
}
