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

#ifndef LPVDP_IU_H
#define LPVDP_IU_H

#include <lpvdp.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

    /* interface */
    void lpvdp_iu_principal();
    void lpvdp_iu_terminais();
    void lpvdp_iu_plugins();

#ifdef __cplusplus
}
#endif

#endif /* LPVDP_IU_H */

