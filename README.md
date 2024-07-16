# njnr
A Compiler for a new Programming Language **njnr** that will compile down to **c**

![Discord](https://img.shields.io/discord/1262591855824998440)

#### To build:

**Update Automake files**

    ./autogen.sh

**If you don't want to build in the top source directory, do something similar to this**

**Example**: using <top_src_dir>**/build/** as build directory:

    mkdir build
    cd build

To choose a different install directory than the default, add the cmd-line option **--prefix=** to your "configure", otherwise don't add that cmd-line option.

    <top_source_dir>/configure --prefix=<install_dir>

**Example**: using <top_src_dir>**/build/** as build directory:

    ../configure --prefix=/home/myhome/
    make


**Otherwise, if you DO want to build in the top source directory...**
To choose a different install directory than the default, add this to your "./configure", otherwise don't add that option.

    ./configure --prefix=<install_dir>
    make

**Example**: using the default install directory, ie no **--prefix=** cmd-line option

    ./configure
    make

#### To Install:

    make install

# See <a href=Language_Grammar.md>Language_Grammar.md</a>
