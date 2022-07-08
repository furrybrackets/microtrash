# microtrash
A minimal utility for managing your trash.

## Info
`microtrash` runs through the `trash` command. It will trash your files in the `~/.trash` directory, and you can write a `.trash.toml` file in your home directory as well. This can be used to minimally configure `microtrash` on launch.
It is not Freedesktop Standard compliant. It is small and minimal, designed purely for quick deletion and recovery.

## Commands

```
trash <FILE...>
```
Trashes a file and throws it into the trash-folder.

```
trash list
```
Lists all files and directories in the root of the trash folder.

```
trash show <FILE | DIRECTORY>
```
`cat` command but for files & directories in the trash. File-path should be relative to the trash directory.

```
trash get <FILE | DIRECTORY> <OUTPUT PATH>
```
Returns the file from your trash to the `OUTPUT PATH`.

```
trash compress -t | --type=<TYPE> -j<CORES>
```
Compresses your trash directory. `-t` options are:
* `zip`
* `tar`
* `rzip`
* `gzip`

You can run trash on multiple cores for the following compression options:
* `gzip`

Specify the number of cores using the `-j` flag:
*Example*
```
trash compress -t gzip -j8
```
