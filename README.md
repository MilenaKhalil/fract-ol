
# fract-ol
Colorful representation of the Mandelbroot, Julia and Lyapunov fractals. Using MLX library and C.

## Description

Here are the features of the program and the instractions you can give to it:

* Spesify the fractal you want by the first capital letter (M, J or L).

* Pass no parametrs to the Mandelbroot, two numbers from -2 to 2 for different Julia sets and finally a string of capital "A"s and "B"s for the Lyapunov fractal.

* Scroll with your mouse or treckpad for zooming in and out. It will zoom to the current mouse position.

* Resize the image if needed.

* Use the arrow keys for moving the fractal image up & down or left & right.

* Use the keys "R", "G", "B" for the dynamic colorshifts.

* Read more about this fractals. The math behind it is very interesting!

## Building the project

First download the repo and enter it:

```console
git clone https://github.com/MilenaKhalil/fract-ol fract-ol
cd fract-ol
```

Make the project:

```console
make
```

> NOTE! If you have this issue with compiling: "library not found for -lglfw3", first make sure that the library glfw is installed on your PC, run:

```console
brew install glfw
```

If you don't have brew first install it, it's an extremely usefull tool. Install brew [here](https://docs.brew.sh/Installation). And run the line above again.

If it still doesn't work after the installation (or if it was already installed) excess the Makefile (through vim, nvim, vscode or something else what you prefer):

```console
nvim Makefile
```
Go to the line №42:

```makefile
$(CC) $(CFLAGS) $^ -o $@ -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
```

And then remove _3_ in the end of the flag _-lglfw3_. It should look like this _-lglfw_. And the line itself should be:

```makefile
$(CC) $(CFLAGS) $^ -o $@ -lglfw -framework Cocoa -framework OpenGL -framework IOKit
```

Run `make` again.

The executable "fractol" should apear. Run it with one of 3 letters (depending on the fractal you want)

```console
./fractol J -0.79 0.15
```

> NOTE! The program will work faster for the smaller window. Also, the deepness for the fractals is limited due to the presition of doubles. Also the > deeper slides requir more computation and processing. Lyaponov fractal needs much more computation.


This will create the folowing fractal:

https://github.com/MilenaKhalil/fract-ol/assets/105588814/0bee3fac-1c31-4451-bc97-6bc8c31a75b9

Use the letters "r", "g" and "b" for dinamic color shifts!
