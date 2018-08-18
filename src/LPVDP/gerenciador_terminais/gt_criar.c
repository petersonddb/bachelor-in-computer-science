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

#include <stdlib.h>

/**
 * Cria um novo terminal
 * @param ptr_t um ponteiro para o ponteiro que receberá o terminal
 * @return o código de resultado
 */
gt_resultado gt_criar(gt_terminal **ptr_t) {
    
    if(ptr_t == NULL)
        return GT_FALHA_NULO;
    
    *ptr_t = (gt_terminal *) malloc(sizeof(gt_terminal));
    
    return GT_CRIADO;
    
}
