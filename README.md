# 🗺️ Route-Planner

**Route-Planner** is a Qt-based application that visualizes a map of western France and allows users to:

- Compute the **shortest path** between two cities using data stored in a MySQL database.
- Access **Wikipedia information** about any city.
- Interact with a dynamic and user-friendly **graphical interface**.

---

## 👥 Authors

- `Boris GANGUE`
- `Gaspard VIEUJEAN`

---

## ⚙️ Installation & Usage

### 1. Connect to MySQL  
Ensure you have a MySQL server running with the appropriate database loaded.  
The application connects using `libmysqlcppconn`.

### 2. Compile the Application  
Navigate to the `src` directory and run:

```bash
make
```

### 3. Run the Application  
From the same directory, execute:

```bash
./routePlanner
```

---

> ⚠️ **Important**  
Before launching the application, make sure:
- The MySQL database is correctly loaded on your Linux machine.
- You have the **host name**, **database name**, **user name**, and **password** ready for authentication.

---

## ✨ Features

- 🔍 **Shortest path computation** between two cities.
- 🌐 **Wikipedia integration**: fetch and display city-related content.
- 🗺️ **Interactive map** with route drawing.
- 🧭 **Mini-map** with zoom/pan support, North arrow, and scale display.
- 📌 **Cursor coordinate display** for better map interaction.
- 🧪 **Input validation** for city names.
- 🔒 **Login system** for connecting to the database.

---

## 🧠 Application Structure

### A. 📦 Database (MySQL)

#### **Schema Overview**

```sql
+-------------+
|   CONTOUR   |
+-------------+
| num_pt (PK) |
| lat         |
| lon         |
+-------------+

+-----------+                 +----------------+
| WAYPOINT  |                 |      ROUTE     |
+-----------+                 +----------------+
| nom (PK)  | ◄────────────►  | nom_debut (FK) |
| lat       | ◄────────────►  | nom_fin (FK)   |
| lon       |                 | distance       |
+-----------+                 +----------------+
    ▲                
    │               
    │               
+--------------+           
|    VILLE     |           
+--------------+         
| nom (PK, FK) |
| code_postal  |
| nb_habitants |
| site         |
+--------------+
```

### B. 📊 Graph Structure

![Graph](<ressource/images/graph_correct.png>)

The graph is built from the ROUTE and WAYPOINTS tables, using waypoints as vertices and routes as weighted edges.  
A shortest-path algorithm (Dijkstra) is used to find the optimal path.

### C. 🎨 Graphical Interface (Qt)

#### **Main Functionalities**
- Input fields for **departure** and **arrival** cities.
- Visualization of the **computed shortest path** on the map.
- Access to **city metadata** and **Wikipedia** page.
- Responsive UI with mouse interactions and map navigation.

![UI](<ressource/images/route-planner.png>)

---

## 🗂️ Project Structure

```
Route-Planner/
├── ressource/
│   ├── documents/
│   │   ├── MiniProjet2024-2025.pdf
│   │   ├── Presentation-RoutePlanner.pdf
│   │   ├── Processus_implementation_graph_algorithm.pdf
│   │   ├── RoadMap-RoutePlanner.pdf
│   │   ├── edgeList.txt
│   │   └── RoutePlanner-archive.zip
│   ├── images/
│   │   ├── north.png
│   │   ├── graph_correct.png
│   │   └── route-planner.png
├── sql/
│   └── map.sql
├── src/
│   ├── model/
│   │   ├── BDD.hpp/.cpp
│   │   ├── Graph.hpp/.cpp
│   │   ├── SceneCarte.hpp/.cpp
│   │   ├── Carte.hpp
│   │   ├── Contour.hpp
│   │   ├── Waypoint.hpp
│   │   ├── Route.hpp
│   │   ├── Ville.hpp
│   │   ├── Point.hpp
│   │   └── libBDD.a
│   ├── view/
│   │   ├── MainWindow.hpp/.cpp
│   │   ├── LoginDialog.hpp/.cpp
│   │   ├── MainView.hpp
│   │   └── MiniView.hpp
│   ├── main.cpp
│   ├── makefile
│   ├── .qmake.stask
│   ├── src.pro
│   └── routePlanner
├── README.md
```