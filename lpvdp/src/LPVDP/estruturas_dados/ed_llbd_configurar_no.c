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

#include "ed_lista_linear_bidirecional.h"

/**
 * Configura um nó de uma lista
 * linear bidirecional
 * @param ptr_no um ponteiro para o nó a configurar
 * @param carga a carga
 * @param ptr_proximo um ponteiro para o próximo nó
 * @param ptr_anterior um ponteiro para o nó anterior
 * @return o código do resultado
 */
ed_llbd_resultado ed_llbd_configurar_no(ed_llbd_no *ptr_no, 
                                        ed_llbd_carga carga, 
                                        ed_llbd_no *ptr_proximo, 
                                        ed_llbd_no *ptr_anterior) {
    
    if(ptr_no == NULL)
        ED_LLBD_NO_NULO;

    ptr_no->carga = carga;
    ptr_no->proximo = ptr_proximo;
    ptr_no->anterior = ptr_anterior;
    
    return ED_LLBD_NO_ATUALIZADO;
    
}
