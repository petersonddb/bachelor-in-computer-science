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

#include <lpvdp_iu.h>

/**
 * interface principal com o
 * usuário
 */
void lpvdp_iu_principal() {
    int op;
    
    capacidade_t capacidade_maxima;
    
    lpvdp_resultado lpvdp_r;
    
    gt_porta_t porta_entrada;
    
    printf(
        "===== LPVDP - Init =====\n\n"
	"Max workload of this instance: "
    );
    scanf("%d", &capacidade_maxima);
    printf("Network port for incoming remote requests: ");
    scanf("%d", &porta_entrada);
    
    if((lpvdp_r = lpvdp_init(capacidade_maxima, porta_entrada)) != LPVDP_INICIADO)
        lpvdp_str_resultado(lpvdp_r);
    else
        do {
            printf(
                "===== LPVDP - Menu =====\n\n"
                "\t[1] Terminals\n"
                "\t[2] Plugins\n"
                "\t[3] Exit\n\n"
                ">"
            );
            scanf("%d", &op);
            switch(op) {
                case 1:
                    lpvdp_iu_terminais();
                    break;
                case 2:
                    lpvdp_iu_plugins();
                    break;
                case 3:
                    printf("Bye!\n");
                    break;
                default:
                    printf("Invalid option!\n");
            }
        } while(op != 3);
}
