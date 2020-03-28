# s_fractal_cpp: C++ Mandelbrot and Julia Fractals Generator

![License](https://img.shields.io/github/license/Ludorg/s_fractal_cpp)
![Twitter Follow](https://img.shields.io/twitter/follow/Ludorg1?style=social)

s_fractal_cpp is a Mandelbrot and Julia fractals generator written in C++.

The generation parameters are specified in an XML file. The generated images are in [TGA](http://ludorg.net/amnesia/TGA_File_Format_Spec.html) format.

## Prerequisites

In 2004, s_fractal_cpp was originally compiled on Windows XP with Visual Studio 2003, but it was portable C++.
It now just requires a WSL (Windows Subsystem for Linux) or a Linux shell with CMake and libxml2 installed.

To install WSL on Windows 10, read the [Installation Guide](https://docs.microsoft.com/en-us/windows/wsl/install-win10).

For a quick use of a Linux shell, [Visual Studio Online](https://visualstudio.microsoft.com/services/visual-studio-online/) is a good solution. It was used to test compilation of s_fractal_cpp.

### LibXML2 install

```bash
sudo apt-get install libxml2
```

### CMake install

```bash
sudo apt-get install cmake
```

## Compilation

After cloning this repo, compilation is made with cmake and make

```bash
cmake -Bbuild -H.
cd build
make
```



## Mandelbrot algorithm

### Mandelbrot algorithm in LaTeX/Markdown format

Let $C$ a complex number.
$C$ depends on the coordinates of the pixel.

Let $Z_n$ a complex number. $Z_{n+1} = Z_n * Z_n + C$

if $\|Z_n\|$ > 2 then the color of $C$ is $f(n)$

### Mandelbrot algorithm in Github format (no inline LaTeX in Markdown)

Let ![C](https://latex.codecogs.com/svg.latex?C) a complex number.
![C](https://latex.codecogs.com/svg.latex?C) depends on the coordinates of the pixel.

Let ![Z(n)](https://latex.codecogs.com/svg.latex?Z(n)) a complex number. <img src="https://latex.codecogs.com/svg.latex?Z(n+1)=Z(n)*Z(n)+C"/>

if <img src="https://latex.codecogs.com/svg.latex?\|Z(n)\|"/> > 2 then the color of <img src="https://latex.codecogs.com/svg.latex?C"/> is <img src="https://latex.codecogs.com/svg.latex?f(n)"/>

## Julia algorithm

### Julia algorithm in LaTeX/Markdown format

Let $C$ and $Z$ complex numbers.
$Z$ depends on the coordinates of the pixel.
$C$ is a constant.

if $\|Z_n\|$ > 2 then the color of $Z$ is $f(n)$

### Julia algorithm in Github format (no inline LaTeX in Markdown)

Let ![C](https://latex.codecogs.com/svg.latex?C) and ![Z](https://latex.codecogs.com/svg.latex?Z) complex numbers.
![Z](https://latex.codecogs.com/svg.latex?Z) depends on the coordinates of the pixel.
![C](https://latex.codecogs.com/svg.latex?C) is a constant.

if <img src="https://latex.codecogs.com/svg.latex?\|Z(n)\|"/> > 2 then the color of ![Z](https://latex.codecogs.com/svg.latex?Z) is ![f(n)](https://latex.codecogs.com/svg.latex?f(n))

## Some history on this old code

This code was developed in 2004 and was part of an ambitious (and immodest) side project named __Sofia__. It intended to be a way for developing knowledge.

Its immodest introduction motto was (in french):

_Dans la seconde moitié du Ve siècle avant JC, les sophistes firent profession d'enseigner la sofia, c'est à dire tout ce qui rend l'homme plus habile, plus savant, plus vertueux. Philosophes, ils étudiaient la logique, les phénomènes célestes, remettant en question les idées reçues, éveillant les intelligences._

Which is translated in:

_In the second half of the 5th century BC, sophists made a profession of teaching sofia, that is, all that  makes man more skilful, more learned, more virtuous. Philosophers, they studied logic, celestial phenomena, questioning conventional wisdom, awakening intelligences._

Unconsciously and unrelatedly, Sofia is also the name of my beloved daughter, born in 2015.

## Contact

If you want to contact me you can reach me at <ludorg@ludorg.net>.

## License

This project uses the following license: [MIT](https://github.com/Ludorg/s_automata_cpp/blob/master/LICENSE).
