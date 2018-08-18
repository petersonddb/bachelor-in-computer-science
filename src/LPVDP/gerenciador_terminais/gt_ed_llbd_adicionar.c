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
 * Adiciona um terminal em
 * uma lista llbd
 * @param ptr_llbd o ponteiro para a lista llbd
 * @param ptr_t o ponteiro para o terminal a adicionar
 * @return o código do resultado
 */
gt_resultado gt_ed_llbd_adicionar(ed_llbd *ptr_llbd, gt_terminal *ptr_t) {
    ed_llbd_no *ptr_llbd_no;    
    ed_llbd_resultado llbd_resultado;
        
    if(ptr_t == NULL)
        return GT_FALHA_NULO;
    
    if((llbd_resultado = ed_llbd_no_criar(&ptr_llbd_no)) != ED_LLBD_NO_CRIADO)
        return gt_ed_llbd_mapear_resultado(llbd_resultado);
    
    if((llbd_resultado = ed_llbd_no_conf_carga(ptr_llbd_no, (ed_llbd_carga) ptr_t)) != ED_LLBD_NO_ATUALIZADO)
        return gt_ed_llbd_mapear_resultado(llbd_resultado);
    
    if((llbd_resultado = ed_llbd_adicionar(ptr_llbd, ptr_llbd_no)) != ED_LLBD_ATUALIZADA)
        return gt_ed_llbd_mapear_resultado(llbd_resultado);
    
    return GT_INCLUIDO;
    
}
