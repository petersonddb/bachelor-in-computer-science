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
lpvdp_argumentos testar_me_2(lpvdp_argumentos);
lpvdp_argumentos sucesso(lpvdp_argumentos);
void falha(lpvdp_resultado);

void init_lpvdp() {
    lpvdp_argumentos args;
    lpvdp_resultado lpvdp_r;
    
    estado = 2;
    
    printf("Hello from inside plugin dois!\n");
    
    args.bytes = sizeof(int);
    args.dados = (void *) malloc(sizeof(int));
    *(int *) args.dados = (int) 55;
    
    /* Chamada a API da plataforma para paralelizar uma funcao */
    lpvdp_r = lpvdp_paralelizar("libsample_plugin_um.so", "testar_me", args, sucesso, falha);
    
    if(lpvdp_r != LPVDP_PARALELIZADO)
        printf("Failed to parallelize a procedure of plugin um for plugin dois: %s\n", lpvdp_str_resultado(lpvdp_r));
    else {
        /* Chamada a API da plataforma para paralelizar uma funcao */
        lpvdp_r = lpvdp_paralelizar("libsample_plugin_dois.so", "testar_me_2", args, sucesso, falha);
        if(lpvdp_r != LPVDP_PARALELIZADO)
            printf("Failed to parallelize a procedure of plugin dois: %s\n", lpvdp_str_resultado(lpvdp_r));
        else
            while(estado);
    }
    
    printf("Bye from inside plugin dois\n");
    
}

lpvdp_argumentos testar_me_2(lpvdp_argumentos args) {
    lpvdp_argumentos ret;
    
    printf("Hello from inside the testar_me_2 procedure of plugin dois, I received: %d!\n", *(int*)args.dados);
    ret = args;
    *(int*)ret.dados = *(int*)ret.dados + 100;
    
    return ret;
}

lpvdp_argumentos sucesso(lpvdp_argumentos args) {
    lpvdp_argumentos ret;
    
    memset(&ret, 0, sizeof(lpvdp_argumentos));
    printf("Hello from inside the success procedure of plugin dois, I received: %d!\n", *(int*)args.dados);
    --estado;
    
    return ret;
}

void falha(lpvdp_resultado resultado) {
    printf("Hello from inside the fail procedure of plugin dois with result: %s\n", lpvdp_str_resultado(resultado));
    --estado;
}
