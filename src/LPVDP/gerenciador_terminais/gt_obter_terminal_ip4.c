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

#include <string.h>

/**
 * Retorna um terminal
 * iniciado com endereço IP v. 4
 */
gt_terminal gt_obter_terminal_ip4(gt_nome_t nome, gt_ip4_t ip4_endereco, gt_porta_t porta) {
    gt_terminal t;
    gt_ip4_endereco ip4;
    
    memset(&t, 0, sizeof(gt_terminal));
    memset(&ip4, 0, sizeof(gt_ip4_endereco));
    
    strcpy(t.nome, nome);
    
    strcpy(ip4.ip_endereco, ip4_endereco);
    ip4.porta = porta;
    
    gt_obter_endereco_de_ip4(t.endereco, ip4);
    
    return t;
}
