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
#include <math.h>
#include <unistd.h>

#include <lpvdp.h>

#define ARQ_PRIMOS "primos.txt"

/* prototipos */
lpvdp_argumentos gerar_primos(lpvdp_argumentos);

void init_lpvdp() {
    lpvdp_argumentos args;
    lpvdp_resultado lpvdp_r;
    
    printf("Hello from inside plugin cinco!\n");
    
    args.bytes = sizeof(int);
    args.dados = (void *) malloc(sizeof(int));
    *(int *) args.dados = (int) 0;
    
    /* Chamada a API da plataforma para paralelizar uma funcao */
    lpvdp_r = lpvdp_paralelizar("libsample_plugin_cinco.so", "gerar_primos", args, NULL, NULL);
    
    if(lpvdp_r != LPVDP_PARALELIZADO)
        printf("Failed to parallelize a procedure of plugin cinco: %s\n", lpvdp_str_resultado(lpvdp_r));
    
    printf("Bye from inside plugin cinco (the primes generation is going on...)\n");
}

/**
 * gera o maximo de numeros primos possiveis
 * e coloca-os em um arquivo de texto
 * @param args nada
 * @return nada
 */
lpvdp_argumentos gerar_primos(lpvdp_argumentos args) {
    lpvdp_argumentos ret;
    
    FILE *arq;
    
    printf("Hello from inside the gerar_primos procedure, which generates primes, of plugin cinco!\n");
    
    if((arq = fopen(ARQ_PRIMOS, "w+")) >= 0) {
        unsigned long primo;
        unsigned long temp;
        short eh_primo;
        
        primo = 0;
        
        do {
            ++primo;
            temp = primo - 1;
            eh_primo = 1;
            while(temp > 1 && eh_primo) {
                eh_primo = (primo % temp == 0);
                --temp;
            }
            if(eh_primo)
                fscanf(arq, "%d\n", primo);
        } while(primo < (int) pow(2, sizeof(unsigned long))); /* infinito */
        
        fclose(arq);
    }
    
    ret = args;
    return ret;
}
