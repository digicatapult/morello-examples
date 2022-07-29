# morello-examples

This repository contains several code examples illustrating how certain common software defects can be protected against by running on a [Cheri](https://www.cl.cam.ac.uk/research/security/ctsrd/cheri/) enabled platform, notably the [ARM Morello evaluation board](https://www.arm.com/architecture/cpu/morello).

This repository is an element of a demonstrator created as part of the UK government’s Industrial Strategy Challenge Fund (ISCF) [Digital Security by Design (DSbD)](https://www.dsbd.tech/) program.

## Compiling the examples

In order to compile the examples you will need to have a working cross compilation toolchain for the morello platform utilising pure capability mode. This is most easily attained by using [cheribuild](https://github.com/CTSRD-CHERI/cheribuild) and building the `all-morello-purecap` target. Then the examples can be built with `make`:

```sh
# or make all
make
```

a specific example can be build using for example

```sh
make out-of-bounds-read-cheri
```

where the targets are named like `{EXAMPLE_NAME}-cheri` or `{EXAMPLE_NAME}-aarch64` depending on whether you want to build the cheri enabled version or the baseline arm64 version.

### Configuring the morello-sdk install location

By default the `make` build process will assume that the `morello-sdk` is located at the default `cheribuild` location of `~/cheri/output/morello-sdk`. This can however be configured with the `MORELLO_SDK` variable:

```
MORELLO_SDK=/path/to/morello/sdk make
```

## Running the examples

The examples when built will be output to the `./build` directory. When copied to a `morello` compatible machine (either the physical hardware or a qemu virtualised version) they can simply be executed without arguments.
