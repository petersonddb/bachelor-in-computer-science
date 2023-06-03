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

#include <gerenciador_plugins.h>

#include <string.h>

/**
 * copia uma string para uma
 * variavel do tipo nome de funcao de plugin
 * @param func_nome a string
 * @param func a variavel destino de nome de funcao de plugin
 * @return o codigo de resultado
 */
gp_resultado gp_func_obter_nome(char *func_nome, gp_func_nome_t func) {
    
    if(func_nome == NULL || func == NULL)
        return GP_FALHA_NOME_NULO;
    
    memcpy(func, func_nome, GP_NOME_TAMANHO);
    func[GP_FUNC_NOME_TAMANHO - 1] = 0; /* para garantir, caso nome_plugin seja maior que nome! */
    
    return GP_COPIADO;
    
}
