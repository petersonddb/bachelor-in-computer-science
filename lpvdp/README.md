# LPVDP - Layered Parallel Virtual Distributed Platform

**Note:** *This is an academic software.*

Virtual platform of distributed parallel computing to automatic distribution of individual parallelizable operations from client software (plugins) into different conventional processing machines (nodes) on the network known by the platform's execution instance, trying to improve the usage of computational power from a **non-special** computer set.

## Features

* Provides node choosing's transparency for the client software;
* Provides load balancing;
* Thin granularity, i.e., parallelizes individual operations instead of the whole software;
* Different client software can execute each other operations;
* Runs only on user-space mode;
* Doesn't need non-conventional hardware neither non-conventional systems;
* Currently, runs only on Unix based operating systems (tested only on Linux).

## Client software

Client software must be **shared libraries**, i.e., plugins to the platform to load them, and they must include **lpvdp.h** header to access the platform features. They must **explicitly** specify which operations they want to be parallelized using the platform API. Currently, the client software must be manually installed on each node. The installation path must be **~/lpvdp_plugins**, the platform will search there for the plugins (*.so).

## How to compile and install

From the project root folder, create a Makefile running:

`./configure`

or:

`./configure --prefix=<installation_folder>`

**prefix** defaults to **/usr/local**.

Then, build and install the software running:

`make install`

or:

`make` then `make install`

To compile a sample plugin, from its folder, create a Makefile running:

`./configure`

or:

`./configure --includes=<path_to_lpvdp_include_files_folder>`

Then, build and install the plugin running:

`make install`

or:

`make` then `make install`

It will be installed into **~/lpvdp_plugins**.

## Author

LPVDP was originally created by Peterson Daronch de Bem (Petch) in 2018.

petersondaronch@gmail.com
