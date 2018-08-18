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
 * Atualiza um nó em uma lista linear
 * bidirecional, cujo os dados no
 * endereço de memória [carga+desl, carga+desl_inicial+bytes]
 * seja igual aos dados informados em padrão
 * @param llbd uma lista llbd
 * @param carga a nova carga para o nó
 * @param ptr_padrao um ponteiro para o padrão
 * @param desl o deslocamento inicial a partir da carga
 * @param bytes o número de bytes a comparar a partir de carga+desl
 * @return o código de resultado
 */
ed_llbd_resultado ed_llbd_atualizar(ed_llbd llbd, 
                                    ed_llbd_carga carga, 
                                    void *ptr_padrao, 
                                    ed_llbd_desl desl, 
                                    ed_llbd_desl bytes) {
    
    ed_llbd_resultado resultado;
    ed_llbd_no *no_atualizar;
    
    no_atualizar = NULL;
    if((resultado = ed_llbd_buscar_por_carga(llbd, &no_atualizar, ptr_padrao, desl, bytes)) != ED_LLBD_NO_ENCONTRADO)
        return resultado;
    
    ed_llbd_no_conf_carga(no_atualizar, carga);
    
    return ED_LLBD_NO_ATUALIZADO;
    
}
