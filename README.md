# PSP Game

An experimental PSP game project with no specific goal for now. The main objective is to explore the limits of procedural generation on such a constrained system.
![screenshot](https://raw.github.com/Catwallon/psp-game/master/screenshots/1.png)

## Roadmap

- Implement a hash table to cache simplex height values for better performance
- Use cached height values to smooth chunk borders by averaging edge heights
- Fix chunk display issues during reloading
- Add mipmapped textures for improved performance
- Implement procedural placement of 3D models
- Use 2D sprites for distant 3D models to optimize rendering
- Add collision detection

## Dependencies

### Build Requirements:

- `make`
- `psp-toolchain`
- `psp-sdk`

### Runtime Requirements:

- `PPSSPP`

## Compilation

Run the following command to compile the project:

```sh
make
```

## Execution

To run the project, use:

```sh
make run
```
