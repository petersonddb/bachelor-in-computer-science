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
 * Verifica se uma lista linear 
 * bidirecional está vazia
 * @param llbd uma lista llbd
 * @return o código do resultado
 */
ed_llbd_resultado ed_llbd_vazia(ed_llbd llbd) {
    
    if(ed_llbd_obter_primeiro(llbd) == NULL && ed_llbd_obter_ultimo(llbd) == NULL)
        return ED_LLBD_VAZIA;
    
    return ED_LLBD_NAO_VAZIA;
    
}
