# ESL_Final

## Introduction
This project contains a Divide and Conquer algorithm for Matrix multiplication built on riscv-vp. <br>

## Build and run on riscv-vp

1. Download the updated software source code to your working directory $EE6470. <br>

    <br>

        $ cd $EE6470 
    <br>

        $ git clone https://github.com/MingShiuanSung/ESL_Final.git
    <br>

        $ cp -r ESL_Final/riscv-vp/vp/src/platform/* $EE6470/riscv-vp/vp/src/platform
    <br>

        $ cp -r ESL_Final/riscv-vp/sw/* $EE6470/riscv-vp/sw
    <br>

2. Build the Matrix Multiplication platform of riscv-vp:

    <br>

        $ cd $EE6470
    <br>

        $ cd riscv-vp/vp/build
    <br>

        $ cmake ..
    <br>

        $ make install
    <br>

## Build Matrix Multiplication software

1. For example if we want to build "dac-one-core". <br>

<br>

    $ cd $EE6470
<br>

    $ cd riscv-vp/sw
<br>

    $ cd dac-one-core
<br>

    $ make
<br>

    $ make sim
<br>

2. If we want to build "dac-two-core". <br>

<br>

    $ cd dac-two-core
<br>

    $ make
<br>

    $ make sim
<br>

3. If we want to build "dac-four-core". <br>

<br>

    $ cd dac-four-core
<br>

    $ make
<br>

    $ make sim
<br>