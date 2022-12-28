# pe_unmapper

[![Build status](https://ci.appveyor.com/api/projects/status/mr5g6h6ld8tc6c5q?svg=true)](https://ci.appveyor.com/project/hasherezade/pe-unmapper)
[![GitHub release](https://img.shields.io/github/release/hasherezade/pe_unmapper.svg)](https://github.com/hasherezade/pe_unmapper/releases)
[![Github All Releases](https://img.shields.io/github/downloads/hasherezade/pe_unmapper/total.svg)](https://github.com/hasherezade/pe_unmapper/releases) 

Small tool to convert beteween the PE alignments (raw and virtual).

Allows for easy PE unmapping: useful in recovering executables dumped from the memory.

Usage:

```
Args:

Required: 
/in	: Input file name

Optional: 
/base	: Base address where the image was loaded: in hex
/out	: Output file name
/mode	: Choose the conversion mode:
	 U: UNMAP (Virtual to Raw) [DEFAULT]
	 M: MAP (Raw to Virtual)
	 R: REALIGN (Virtual to Raw, where: Raw == Virtual)
```
Example:

```
pe_unmapper.exe /in _02660000.mem /base 02660000 /out payload.dll
```
