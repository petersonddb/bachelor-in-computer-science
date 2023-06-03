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
 * Libera (limpa e desinicializa) uma lista llbd
 * @param ptr_llbd um ponteiro para lista a liberar
 * @return o código do resultado
 */
ed_llbd_resultado ed_llbd_liberar(ed_llbd *ptr_llbd) {
    ed_llbd_no *no, *tmp;    
    ed_llbd_resultado resultado;
    
    if(ptr_llbd == NULL)
        return ED_LLBD_NULA;
    
    no = ed_llbd_obter_primeiro(*ptr_llbd);
    while(no != NULL) {
        tmp = no->proximo;
        free(no);
        no = tmp;
    }    
    free(ptr_llbd);

    return ED_LLBD_ATUALIZADA;
}
