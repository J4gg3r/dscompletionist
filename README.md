# DS Completionist

A D3D hook for Dark Souls: Prepare to Die Edition that draws 3D boxes over pick ups, closed chests and unlit bonfires so you
can visit them all!

## Images

![1](images/1.jpg?raw=true "Boxes from far away visible through walls")
![2](images/2.jpg?raw=true "Unlit bonfire with a orange box drawn over it")
![3](images/3.jpg?raw=true "Pick up object on the way out from Undead Asylum")
![4](images/4.jpg?raw=true "Pick up object up close")
![5](images/5.jpg?raw=true "Closed chests shown as green boxes")

## Compilation requirements

* DirectX SDK with D3D9 headers and libs. I'm using Microsoft DirectX SDK (June 2010).
* MS C++ compiler
* Compile to 32bit DLL

## Installation

Rename compiled DLL to d3d9.dll and put in the game's DATA directory where game executable is located.

## Uninstallation

Remove the d3d9.dll from game's DATA directory.

## When in-game

If properly installed, main menu screen should show "Dark Souls Completionist" label in the right bottom corner.  
Press Numpad0 while in game to show/hide the boxes.

## Known bugs

* Boxes are drawn two times when game is run in windowed mode. It looks like the game is drawing the same scene two times:
first time on the game's window and the second on a viewport that is a bit smaller than the game's window. Couldn't figure a way
to fix this. Playing in fullscreen mode is strongly recommended.
* Some stuff that is not a closed chest may have a green box drawn over it. Couldn't find a way to filter them properly
from all the other objects that can be interacted with so some false positives may happen.

## Summary

This project is the result of some honest debugging and reverse engineering work. There is no SDK for this game so all
the names, especially in `game.h`, are made up by me and not the game developers.
