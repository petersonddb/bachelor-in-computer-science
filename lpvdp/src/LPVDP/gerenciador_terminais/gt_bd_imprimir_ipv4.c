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
 * Imprime todos os terminais de
 * um BD na saída informada
 * @param saida a saída para imprimir os terminais
 * @param bd o banco de dados com terminais
 * @return o código de resultado
 */
gt_resultado gt_bd_imprimir_ipv4(FILE *saida, int bd) {
    
    gt_terminal terminal;
    gt_ip4_endereco ip4;
    gt_resultado resultado;
    int bytes;
    
    if(lseek(bd, 0, SEEK_SET) < 0)
        return GT_FALHA_BD_SEEK;
       
    while((bytes = read(bd, &terminal, sizeof(gt_terminal))) > 0) {
        if(strcmp(terminal.nome, "")) { /* Possuem nome em branco os excluidos */
            ip4 = gt_obter_ip4_de_endereco(terminal.endereco);
            fprintf(
                saida, 
                "Name: %s Type: IP Version: 4 Address: %s Port: %d\n",
                terminal.nome,
                ip4.ip_endereco,
                ip4.porta
            );
        }
    }
    
    if(bytes < 0)
        resultado = GT_FALHA_BD_LEITURA; /* erro */
    else
        resultado = GT_IMPRESSOS;
    
    return resultado;
    
}
