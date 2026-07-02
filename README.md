# 2D Particle Physics & Autonomous Vacuum Simulator 🤖✨

[![Language](https://img.shields.io/badge/Language-C++11-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B11)
[![Library](https://img.shields.io/badge/Graphics-Raylib-red.svg)](https://www.raylib.com/)
[![Platform](https://img.shields.io/badge/Platform-Linux-orange.svg)](https://www.linux.org/)

A high-performance, interactive 2D physics simulation environment written in native C++ using **Raylib** for real-time graphical rendering. The project features a custom dynamic particle engine with low-level memory handling, elastic collisions, and an automated "Robot Vacuum" sandbox mode that actively clears kinetic particles from the workspace.

---

## 📺 Project Demo

![Simulator Demo](https://via.placeholder.com/1280x720.png?text=Add+a+cool+simulation+GIF+here!)

---

## 🚀 Key Features

* **Low-Level Memory Management:** Implements an optimized dynamic array container (`ParticleSet`) using raw pointers (`new[]`/`delete[]`), sequential block allocation (`BLOCK_SIZE = 3`), and strict enforcement of the **Rule of Three** (Deep Copying, Destructuring, and Assignment Safety).
* **Kinematic & Physics Engine:** Features a fully-fledged 2D vector mathematics implementation managing displacement, velocity damping, and acceleration vectors.
* **Advanced Boundary Behaviors:** Supports multiple particle environmental boundary physics, including hard specular bouncing (`bounce()`) and continuous toroidal wrapping (`wrap()`).
* **Interactive Sandbox System:** Control a master "Vacuum Robot" particle via keyboard input to clean the screen. Features dynamic textual rendering and automated geometric text-centering using real-time string dimension measurements.

---

## 🛠️ Architecture & Project Structure

The project follows a standard professional C++ directory layout separating interfaces, implementations, objects, and compiled binaries:

```text
.
├── Makefile                # Automated multi-target build configuration
├── bin/                    # Compiled production-ready executables
│   └── particle_sim
├── include/                # Header files (.hpp)
│   ├── Particle.hpp
│   ├── ParticleSet.hpp
│   ├── Vector2D.hpp
│   ├── params.hpp          # Global physics and window constants
│   └── useful.hpp
├── obj/                    # Intermediate architecture object files (.o)
└── src/                    # Source code implementations (.cpp)
    ├── Particle.cpp
    ├── ParticleSet.cpp
    ├── Vector2D.cpp
    ├── main_raylib.cpp     # Graphics loop & window initialization
    └── useful.cpp

```

---

## ⚙️ Compilation & Getting Started

### Prerequisites

Ensure you have a C++ compiler supporting `C++11` standards and the `raylib` development library installed on your Linux system.

On Ubuntu/Kubuntu/Kali, install dependencies via:
```bash
sudo apt wget libraylib-dev
```

### Building the Project

The workspace includes a robust, production-grade `Makefile` using pattern rules and automatic variables for optimized build times.

```bash
# Clean previous object builds
make clean

# Compile the optimized production binary
make
```

### Running the Simulator

Execute the binary from the root directory passing the **vacuum radius** and the **initial particle count** as arguments:

```bash
./bin/particle_sim <robot_radius> <particle_count>
```

*Example:*
```bash
./bin/particle_sim 25 60
```

---

## 🎮 Interactive Controls

Once the window initializes, you can actively interact with the physics sandbox:

* `[Arrow Keys]`: Manually override and adjust the directional velocity vectors of the Vacuum Robot.
* `[ENTER]`: Dynamically instantiate and inject a new batch of random kinetic particles into the active frame.
* `[ESC / Close Button]`: Gracefully free all heap allocations, terminate the OpenGL context, and exit.

---

## 📊 Technical Highlights

### Explicit Deep Copying & Assignment Safety
To prevent pointer aliasing and segmentation faults during particle clustering, the assignment operator executes safe resource releasing and deep data duplication:
```cpp
ParticleSet& ParticleSet::operator=(const ParticleSet &c){
    if(this != &c){ // Self-assignment guard
        freeMemory();
        reserve(c.size());
        setSize(c.size());
        copy(c);
    }
    return *this;
}
```

### Mathematical Text Centering
To maintain perfect geometric symmetry under standard $1280 \times 720$ HD configurations, mid-screen text strings are calculated dynamically relative to the runtime font allocation dimensions:

$$\text{Position X} = \frac{\text{Screen Width}}{2} - \frac{\text{Text Width}}{2}$$

```cpp
int textWidth = MeasureText("CLEAN ROOM", fontSize);
int posX = (GetScreenWidth() - textWidth) / 2;
```
