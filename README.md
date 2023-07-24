# fract-ol
Representation of the Mandelbroot, Julia and Lyapunov fractals. Using MLX library and C.

# What the programm can do?

Spesify the fractal you want by the first capital letter (M, J or L).

Pass no parametrs to the Mandelbroot, two numbers from -2 to 2 for different Julia sets and finally a string of capital "A"s and "B"s for the Lyapunov fractal.

Scroll with your mouse or treckpad for zooming in and out. It will zoom to the current mouse position.

You can also resize the image.

Use the arrow keys for moving the fractal image up & down or left & right.

Use the keys "R", "G", "B" for the dynamic colorshifts.

Red more about this fractals. The math behind it is very interesting!

NOTE! The program will work faster for the smaller window. Also, the deepness for the fractals is limited due to the presition of doubles. Also the deeper slides requir more computation and processing. Lyaponov fractal needs much more computation.

# Building the project

First download the repo and enter it:

```console
git clone https://github.com/MilenaKhalil/fract-ol fract-ol
cd fract-ol
```

Make the project:

```console
make
```

NOTE! If you have this issue with compiling: "library not found for -lglfw3", first make sure that this library is installed on your PC, run:

If it still doesn't work after installation (or if it was already installed) excess the Makefile (through vim, nvim, vscode or something else what you prefer):

```console
nvim Makefile
```
Go to the line №42:

```makefile
$(CC) $(CFLAGS) $^ -o $@ -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
```
And then remove '3' from the library name "-lglfw3", should be "-lglfw":

```makefile
$(CC) $(CFLAGS) $^ -o $@ -lglfw -framework Cocoa -framework OpenGL -framework IOKit
```

Go to the line

The executable "fractol" should apear. Run it with one of 3 letters (depending on the fractal you want)

```console
./fractol J -0.79 0.15
```

This will create the folowing fractal:

https://github.com/MilenaKhalil/fract-ol/assets/105588814/0bee3fac-1c31-4451-bc97-6bc8c31a75b9

Use the letters "r", "g" and "b" for dinamic color shifts!
