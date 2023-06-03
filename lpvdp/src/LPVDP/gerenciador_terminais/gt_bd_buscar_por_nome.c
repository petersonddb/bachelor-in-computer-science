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
#include <string.h>

/**
 * busca um terminal no
 * registro de terminais
 * @param nome o nome do terminal
 * @param t o terminal pra guardar o resultado
 * @param bd o descritor de arquivo do bd
 * @return o código de resultado
 */
gt_resultado gt_bd_buscar_por_nome(gt_nome_t nome, gt_terminal *t, int bd) {
    gt_terminal terminal;
    gt_resultado resultado;
    int bytes;
    
    if(lseek(bd, 0, SEEK_SET) < 0)
        return GT_FALHA_BD_SEEK;
    
    resultado = GT_NAO_ENCONTRADO;
    while((bytes = read(bd, &terminal, sizeof(gt_terminal))) > 0)
        if(!strcmp(terminal.nome, nome)) {
            memcpy(t, &terminal, sizeof(gt_terminal));
            resultado = GT_ENCONTRADO;
            break;
        }
    
    if(bytes < 0)
        resultado = GT_FALHA_BD_LEITURA; /* erro */
    
    return resultado;
}
