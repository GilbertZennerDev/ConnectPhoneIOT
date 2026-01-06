# 📱 ConnectPhoneIOT: 3D Smartphone Chain Simulator 🛰️

Welcome to **ConnectPhoneIOT**! This project simulates a dynamic chain of smartphones connecting via Bluetooth-like signals in a **3D environment**. Using a Breadth-First search logic, the simulation determines if a signal can "hop" from a starting device to a target destination through a mesh network of intermediate peers.

---

## 🚀 Features

* **3D Spatial Logic**: Unlike standard 2D simulations, this accounts for height (-axis), making it perfect for simulating multi-story buildings. 🏢
* **Dynamic Scaling**: Configure the number of phones, the "spread" (world size), and the signal range via command-line arguments. 📏
* **Dual Implementation**:
* **C++ Version**: High-performance, memory-managed (42-style), and strictly typed. ⚡
* **Python Version**: Flexible, easy to read, and great for rapid prototyping. 🐍


* **Path Tracking**: Visualizes the "ripple effect" of the signal as it discovers new reachable neighbors. 🌊

---

## 🛠️ How it Works

The algorithm uses the **Euclidean Distance** formula in 3D space to check connectivity:

If the distance  is less than or equal to your `maxDistance`, the signal successfully hops!

---

## 💻 Usage

### 🔵 C++ Version

**Compilation:**

make

**Execution:**

```bash
./IOT [num_phones] [spread] [target_id] [max_distance]

```

*Example:* `./mesh_sim 100 500 42 15`

---

### 🟡 Python Version

**Execution:**

```bash
python3 IOT.py phonescount startid endid distance limx limy

```

---

## 🏗️ Project Structure

* `t_pos`: A custom structure/class holding the  coordinates.
* `Phone Class`: Encapsulates the device ID and its spatial data.
* `trackpath`: The core logic that iterates through the network to find the destination.

---

## 👤 Author

**Gilbert Zenner** (Student at 42)

* *Disciplined code, memory-safe logic, and 3D spatial awareness.*

---

> **Want to see the signal path?**
> Check out the `iteration` logs in the console to see how many new phones were discovered in every "hop" of the mesh! 📈✨

Would you like me to add a **Contribution** section or a **License** file to this README?
