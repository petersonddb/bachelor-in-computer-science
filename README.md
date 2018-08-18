# LPVDP - Layered Parallel Virtual Distributed Platform

Academic parallel distributed computing virtual platform to automatic directing of individual parallelizable operations from plugin based client softwares to different (conventional) processing machines (nodes) in platform's execution instance known network, trying to improve the usage of computational power from a **"non-special"** computers set.

## Features

* Provides node choosing's transparency to the client software;
* Provides load balancing;
* Thin granularity, i.e. parallelizes individual operations instead of whole softwares;
* Client softwares can execute each other operations;
* Runs only on user-space mode;
* Doesn't need non-conventional hardware neither non-conventional software;
* Currently, runs only on Unix based operating systems (tested only on Linux).

## Client softwares

Client softwares must be **shared libraries**, i.e. plugins to the platform to load them, and they must include **lpvdp.h** header to access the platform's functionalities. They must **explicitly** specify which operations they want to be parallelized using the platform's API. Currently, the client software must be manually locally installed in each node. The installation path must be **~/lpvdp_plugins**, the platform will search there for the plugins (*.so).

## How to compile and install

From the project root folder, create the Makefile running:

`./configure`

Or:

`./configure --prefix=<installation_folder>`

**prefix** defaults to **/usr/local**.

Then, build and install it running:

`make install`

Or:

`make` then `make install`

To compile the sample plugins, from each sample plugin folder, create it's Makefile running:

`./configure`

Or:

`./configure --includes=<path_to_lpvdp_include_files_folder>`

Then, build and install it running:

`make install`

Or:

`make` then `make install`

They will be installed inside **~/lpvdp_plugins**.

## Author

LPVDP was originally created by Peterson Daronch de Bem (Petch) in 2018.

petersondaronch@gmail.com
