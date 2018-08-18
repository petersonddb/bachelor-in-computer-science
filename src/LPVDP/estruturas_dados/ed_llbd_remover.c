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
 * Remove um nó em uma lista linear
 * bidirecional, cujo os dados no
 * endereço de memória [carga+desl, carga+desl_inicial+bytes]
 * seja igual aos dados informados em padrão
 * @param ptr_llbd um ponteiro para uma lista llbd
 * @param ptr_padrao um ponteiro para o padrão
 * @param desl o deslocamento inicial a partir da carga
 * @param bytes o número de bytes a comparar a partir de carga+desl
 * @return o código de resultado
 */
ed_llbd_resultado ed_llbd_remover(ed_llbd *ptr_llbd, 
                                  void *ptr_padrao, 
                                  ed_llbd_desl desl, 
                                  ed_llbd_desl bytes) {
    
    ed_llbd_resultado resultado;
    ed_llbd_no *no_remover;
    
    if(ptr_llbd == NULL)
        return ED_LLBD_NULA;
    
    no_remover = NULL;
    if((resultado = ed_llbd_buscar_por_carga(*ptr_llbd, &no_remover, ptr_padrao, desl, bytes)) != ED_LLBD_NO_ENCONTRADO)
        return resultado;
    
    if(no_remover == ed_llbd_obter_primeiro(*ptr_llbd) && no_remover == ed_llbd_obter_ultimo(*ptr_llbd)) {
        ed_llbd_conf_primeiro(ptr_llbd, NULL);
        ed_llbd_conf_ultimo(ptr_llbd, NULL);
    } else if(no_remover == ed_llbd_obter_primeiro(*ptr_llbd)) {
        ed_llbd_no_conf_anterior(ed_llbd_no_obter_proximo(*no_remover), NULL);
        ed_llbd_conf_primeiro(ptr_llbd, ed_llbd_no_obter_proximo(*no_remover));
    } else if(no_remover == ed_llbd_obter_ultimo(*ptr_llbd)) {
        ed_llbd_no_conf_proximo(ed_llbd_no_obter_anterior(*no_remover), NULL);
        ed_llbd_conf_ultimo(ptr_llbd, ed_llbd_no_obter_anterior(*no_remover));
    } else {
        ed_llbd_no_conf_anterior(ed_llbd_no_obter_proximo(*no_remover), ed_llbd_no_obter_anterior(*no_remover));
        ed_llbd_no_conf_proximo(ed_llbd_no_obter_anterior(*no_remover), ed_llbd_no_obter_proximo(*no_remover));
    }
    free(no_remover);
    
    return ED_LLBD_NO_REMOVIDO;
    
}
