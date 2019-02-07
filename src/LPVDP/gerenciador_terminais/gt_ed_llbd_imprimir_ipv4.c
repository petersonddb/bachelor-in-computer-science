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
#include <gerenciador_terminais.h>

#include <stdio.h>
#include <string.h>

/**
 * Imprimir terminais IPv4 de uma
 * lista em uma saída
 * @param llbd a lista com os terminais a serem impressos
 * @return o código do resultado
 */
gt_resultado gt_ed_llbd_imprimir_ipv4(ed_llbd llbd, FILE *saida) {
    ed_llbd_no *no;
    gt_terminal t;
    gt_ip4_endereco ip4;
    
    no = ed_llbd_obter_primeiro(llbd);
    while(no != NULL) {
        t = *(gt_terminal *) ed_llbd_no_obter_carga(*no);
        ip4 = gt_obter_ip4_de_endereco(t.endereco);
        fprintf(
            saida, 
            "Name: %s Type: IP Version: 4 Address: %s Port: %d\n",
            t.nome,
            ip4.ip_endereco,
            ip4.porta
        );
        no = ed_llbd_no_obter_proximo(*no);
    }
    
    return GT_IMPRESSOS;
    
}
