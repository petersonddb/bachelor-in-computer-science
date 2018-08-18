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
 * Preenche um endereco de ip4
 * apartir de um endereço de ip
 * @param ender o endereço
 * @return um endereço IP v. 4
 */
gt_ip4_endereco gt_obter_ip4_de_endereco(gt_endereco_t ender) {
    gt_ip4_endereco ip4;
    
    memcpy(&ip4, ender, sizeof(gt_ip4_endereco));
    return ip4;
}
