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

#include <unistd.h>

/**
 * Inclui um novo terminal no
 * registro de terminais
 * @param t o novo terminal
 * @param bd o descritor de arquivo do bd
 * @return o código de resultado
 */
gt_resultado gt_bd_incluir(gt_terminal t, int bd) {
    gt_resultado resultado;
    gt_terminal terminal;
    
    if((resultado = gt_bd_buscar_por_nome(t.nome, &terminal, bd)) == GT_NAO_ENCONTRADO) {
        if(lseek(bd, 0, SEEK_END) < 0)
            resultado = GT_FALHA_BD_SEEK;
        else if(write(bd, &t, sizeof(gt_terminal)) < 0)
            resultado = GT_FALHA_BD_ESCRITA;
        else
            resultado = GT_INCLUIDO;
    }
    
    return resultado;
}
