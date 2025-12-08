# tinyCardputer

![TinyCardputer Splash](https://raw.githubusercontent.com/soykhaler/tinyCardputer/refs/heads/main/splash.jpg)

A retro-style, ASCII micro–operating environment for the **M5Stack Cardputer**, inspired by early home computers such as the ZX Spectrum, Commodore 64 and Amstrad CPC — and based conceptually on the original **tinyComputer** project (written in Godot).

tinyCardputer brings the spirit of 80s programming to a real handheld device, allowing you to write programs, run commands, and interact with a tiny scripting language **directly on the Cardputer itself**.
No PC required — the Cardputer *becomes* the computer.

---

## What is tinyCardputer?

tinyCardputer is a minimalistic retro environment that includes:

- A **green ASCII terminal** with simulated vintage style.
- A built-in **tiny scripting language**, inspired by tinyComputer's MiniCoder.
- On-device programming through the **miniCoder editor**, with line numbers and live execution.
- System commands such as:
  - `echo` — print text
  - `beep` — beeper sound with variable pitch
  - `window` — ASCII message windows
  - `wait` — timed delays
  - `boot` — boot sequence sound
  - `error` — error tone
  - `clear`, `help`, `exit`
- A **splash screen embedded in ROM**.
- Sequential script execution with delays (like coroutines).
- A working beeper engine.
- 100% offline, self-contained retro micro-OS feel.

The goal is to recreate the experience of learning to code as in the old days:
typing simple commands, experimenting, and seeing immediate results —
**just like programming a ZX Spectrum or Commodore 64**, but on a modern Cardputer.

---

## 🌱 Origin of the Project
![TinyCardputer Banner](https://raw.githubusercontent.com/soykhaler/tinyComputer/refs/heads/main/itch_resources%20/banner%20315x250.png)


tinyCardputer is a **derivative project** of **tinyComputer**, originally developed in Godot 3.5 as a virtual retro computer intended for beginners and experimentation.

Original tinyComputer project:
https://github.com/soykhaler/tinyComputer

tinyCardputer takes that conceptual foundation and ports it to an actual hardware device — the **M5Stack Cardputer**.

Where tinyComputer was virtual, tinyCardputer is **real**.

