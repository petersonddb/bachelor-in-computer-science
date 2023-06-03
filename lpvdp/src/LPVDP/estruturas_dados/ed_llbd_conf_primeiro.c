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
 * Configrua o primeiro nó de
 * uma lista linear bidirecional
 * @param ptr_llbd um ponteiro para uma lista lbd
 * @param ptr_no um ponteiro para um nó de uma lista lbd
 * @return o código do resultado
 */
ed_llbd_resultado ed_llbd_conf_primeiro(ed_llbd *ptr_llbd, ed_llbd_no *ptr_no) {
    
    if(ptr_llbd == NULL)
        return ED_LLBD_NULA;
    
    ptr_llbd->primeiro = ptr_no;
    
    return ED_LLBD_ATUALIZADA;
    
}
