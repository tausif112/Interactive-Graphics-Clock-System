# 🕒 Interactive Graphics Clock System

<div align="center">

![OpenGL](https://img.shields.io/badge/OpenGL-Graphics-blue)
![Language](https://img.shields.io/badge/Language-C++-orange)
![GLUT](https://img.shields.io/badge/Library-GLUT-green)
![Status](https://img.shields.io/badge/Project-Completed-success)

A real-time analog clock simulation developed using OpenGL and GLUT, demonstrating classic Computer Graphics algorithms and interactive graphical rendering techniques.

</div>

---

# 📌 Project Overview

The **Interactive Graphics Clock System** is a Computer Graphics project developed using **C++**, **OpenGL**, and **GLUT**.

This application simulates a fully functional analog clock that synchronizes with the system time and updates in real time. The project focuses on implementing fundamental Computer Graphics algorithms, including line drawing and circle drawing techniques, rather than relying solely on built-in graphics primitives.

The clock supports multiple visual themes and provides an interactive user experience through keyboard controls.

---

# 🎥 Demo

![Clock Demo](images/clock_demo.gif)

---

# ✨ Features

✅ Real-time analog clock synchronization  
✅ Multiple visual themes  
✅ Interactive keyboard controls  
✅ Dynamic hour, minute, and second hands  
✅ Concentric clock face design  
✅ Algorithm-based graphics rendering  
✅ Lightweight and efficient implementation  

---

# 🛠️ Technologies Used

| Technology | Purpose |
|------------|---------|
| C++ | Programming Language |
| OpenGL | Graphics Rendering |
| GLUT / FreeGLUT | Window Management & Event Handling |
| Code::Blocks | Development Environment |

---

# 📂 Project Structure

```bash
Interactive-Graphics-Clock-System/
│
├── main.cpp
├── Interactive Graphics Clock System.cbp
├── LICENSE
├── README.md
│
└── images/
    ├── Screenshot_1.png
    └── Screenshot_3.png
```

---

# ⚙️ How the Program Works

The application retrieves the current system time and dynamically updates the positions of the clock hands.

The project utilizes:

- Bresenham Line Drawing Algorithm
- Midpoint Circle Algorithm
- Scan Conversion Circle Filling
- Trigonometric calculations for hand positioning
- GLUT Timer Functions for real-time updates

The positions of the clock hands are calculated using trigonometric functions:

```cpp
x = centerX + radius * cos(angle);
y = centerY + radius * sin(angle);
```

The display refreshes every second to ensure accurate synchronization with system time.

---

# 🧠 Core Graphics Algorithms

## 🔹 Bresenham Line Drawing Algorithm

Used for:

- Hour hand rendering
- Minute hand rendering
- Second hand rendering
- Hour markings
- Minute markings

---

## 🔹 Midpoint Circle Algorithm

Used for:

- Clock boundary creation
- Decorative concentric circles

---

## 🔹 Scan Conversion Circle Filling

Used for:

- Multi-layer clock face rendering
- Center pivot rendering

---

# 🎮 User Controls

| Key | Action |
|------|---------|
| `1` | Activate Theme 1 |
| `2` | Activate Theme 2 |
| `ESC` | Exit Application |

---

# 📸 Output Screenshots

## 🔹 Theme 1

![Theme 1](images/Screenshot_1.png)

---

## 🔹 Theme 2

![Theme 2](images/Screenshot_3.png)

---

# 🚀 Compilation & Execution

## Compile

```bash
g++ main.cpp -o clock -lglut -lGLU -lGL
```

## Run

```bash
./clock
```

---

# 📖 Learning Outcomes

Through this project, the following concepts were practiced:

- Computer Graphics Fundamentals
- Raster Graphics Algorithms
- OpenGL Graphics Programming
- Real-Time Rendering
- Event-Driven Programming
- Interactive User Interface Design
- Mathematical Visualization Techniques

---

# 👨‍💻 Author

### Md. Tausif Uddin

Bachelor of Science in Computer Science & Engineering (CSE)  
University of Asia Pacific (UAP)

GitHub: https://github.com/tausif112

---

# 📜 License

This project is licensed under the MIT License.

---

# ⭐ Acknowledgement

This project was developed as part of the Computer Graphics Laboratory coursework and demonstrates the practical implementation of classical graphics algorithms using OpenGL and GLUT.
