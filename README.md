SSFT: Script/Source File Templates
==================================

A collection of (?:script|source) file templates with helper tools.

License
-------

| File                              | License           |
|-----------------------------------|-------------------|
| Files in [./bin](./bin) directory | zlib License      |
| Files in other directory          | CC0 1.0 Universal |

Target environments
-------------------

| File type      | Target environments           |
|----------------|-------------------------------|
| Template files | Cygwin, Linux, macOS, Windows |
| Helper tools   | Cygwin, Linux, macOS          |

If you want to use helper tools
-------------------------------

### Set up

1. Put a helper tool `bin/ssft` in a directory registered in `PATH` environment variable.
2. Set your template directory in the `SSFT_TEMPLATE_PATH` environment variable.
    * If you cloned the ssft repository in `$HOME/git`,
      probably your template directory is `$HOME/git/ssft/template`,
      and *you don't have to set `SSFT_TEMPLATE_PATH`*.
    * If you cloned the ssft repository in your home directory,
      probably your template directory is `$HOME/ssft/template`,
      and you must set `$HOME/ssft/template` in the `SSFT_TEMPLATE_PATH`.

### Usage

Please check help message `ssft -h`

### Example

```sh
# Show a template list.
ssft -l

# Copy one or more template files in the current directory.
ssft shell-script/basic.sh
ssft gmake-bin/linux/Makefile gmake-bin/unix-common/common.mk
```
