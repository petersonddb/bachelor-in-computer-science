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

#include <stdio.h>
#include <string.h>

#include <lpvdp.h>

/* propriedades */
int estado;

/* prototipos */
lpvdp_argumentos sucesso(lpvdp_argumentos);
void falha(lpvdp_resultado);

void init_lpvdp() {
    lpvdp_argumentos args;
    lpvdp_resultado lpvdp_r;
    
    estado = 1;
    
    printf("Hello from inside plugin tres!\n");
    
    args.bytes = sizeof(int);
    args.dados = (void *) malloc(sizeof(int));
    *(int *) args.dados = (int) 100;
    
    /* Chamada a API da plataforma para paralelizar uma funcao */
    lpvdp_r = lpvdp_paralelizar("libsample_plugin_um.so", "func_nao_existe", args, sucesso, falha);
    
    if(lpvdp_r != LPVDP_PARALELIZADO)
        printf("Failed to parallelize a procedure of plugin tres: %s\n", lpvdp_str_resultado(lpvdp_r));
    else 
        while(estado);
    
    printf("Bye from inside plugin tres\n");
    
}

lpvdp_argumentos sucesso(lpvdp_argumentos args) {
    lpvdp_argumentos ret;
    
    memset(&ret, 0, sizeof(lpvdp_argumentos));
    printf("Hello from inside the success procedure of plugin tres, I received: %d!\n", *(int*)args.dados);
    --estado;
    
    return ret;
}

void falha(lpvdp_resultado resultado) {
    printf("Hello from inside the fail procedure of plugin tres with result: %s\n", lpvdp_str_resultado(resultado));
    --estado;
}
