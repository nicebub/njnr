# njnr
A Compiler for a new Programming Language **njnr** that will compile down to **c**

![Discord](https://img.shields.io/discord/1262591855824998440)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/nicebub/njnr/c-cpp.yml)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/nicebub/njnr/c-cpp_win.yml)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/nicebub/njnr/github-code-scanning%2Fcodeql)
![GitHub branch check runs](https://img.shields.io/github/check-runs/nicebub/njnr/main)
![GitHub tag status](https://img.shields.io/github/checks-status/nicebub/njnr/0.0.1btm)
![GitHub tag check runs](https://img.shields.io/github/check-runs/nicebub/njnr/0.0.1btm)






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
