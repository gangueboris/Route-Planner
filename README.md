### **Route-Planner**  

The project involves developing a graphical application in C++ to calculate and display the shortest path between two cities using Qt and a MySQL database. 

## *Authors*
- `Boris GANGUE`
- `Gaspard VIEUJEAN`
- `Ahmed YAHA`

---

## **1. Description of different parts of Route-Planner**  

### **A. Database (MySQL)**  
- **Tables:**  
```shell
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

- `Contour`: Stores geographical contour points.  
- `Waypoint`: Represents nodes in the road network (intermediate points and cities).  
- `Route`: Defines routes between waypoints (graph representation with distances).  
- `Ville`: A subset of waypoints representing cities.  


- **Connecting to MySQL:** Use `libmysqlcppconn` to fetch data.  

### **B. Model (MVC - "Model" Part)**  
- **Main Classes:**  
  - `Carte`: Manages data and relationships between waypoints and routes.  
  - `Waypoint`: Represents a network point (base class).  
  - `Ville`: Inherits from `Waypoint` (includes postal code, population, and website).  
  - `Route`: Links two waypoints with an associated distance.  
  - `Graphe`: Stores the network structure and implements the shortest path algorithm.  

![class-MVC](<ressource/images/class-mvc.png>)

- **Important Methods:**  
  - `neighbours(int index) → vector<int>`: Returns neighboring waypoints.  
  - `distance(int i1, int i2) → float`: Returns the distance between two waypoints.  
  - `getShortestPath(int start, int end) → vector<Route>`: Implements Dijkstra or A*.  

### **C. Graphical Interface (Qt)**  
- **UI Elements:**  
  - Input fields for departure and arrival cities.  
  - Interactive map displaying the shortest route.  
  - Mini-map with an overview view.  
  - Optional features: cursor coordinates, scale, North arrow.  

- **Graphical Display:**  
  - Loading and displaying map data.  
  - Dynamically displaying the computed route.  

![alt text](<ressource/images/route-planner.png>)

---

## **PROJECT STRUCTURE**

```
|── ressource/
│   ├── documents/
│   ├── images/
│   ├── north.png
│── sql/
│   ├── plans.sql
│── src/
│   ├── model/
│   │   ├── .hpp
│   │   ├── .cpp
│   │   ├── .hpp
│   │   ├── .cpp
│   ├── view/
│   │   ├── MainWindow.hpp
│   │   ├── MainWindow.cpp
│   │   ├── LoginDialog.hpp
│   │   ├── LoginDialog.cpp
│   ├── main.cpp
│── README.md
```

## **Project guidelines** 
- Respect file destination (put each file in their corresponding folder).
- Respest Class name `CamelCase` (eg. MainWindow.hpp) logic.
- Respect the comment adding:
eg.
**For a class**
```cpp
/**
 * @class ContactManager
 * @brief Manages a collection of contacts.
 *
 * This class allows adding, removing, and searching for contacts.
 * It provides efficient operations and supports saving/loading from a file.
 *
 * @author Boris Gangue
 * @date March 21, 2025
 */
class ContactManager {
public:
    // Constructor and Destructor
    ContactManager();
    ~ContactManager();

    // Member Functions
    void addContact(const std::string& name, const std::string& phone);
    bool removeContact(const std::string& name);
    std::string searchContact(const std::string& name) const;

private:
    std::map<std::string, std::string> contacts; ///< Stores contacts in a name-phone mapping.
};
```

**For a method**
```cpp
/**
 * @brief Adds a new contact to the contact list.
 * 
 * @param name The name of the contact.
 * @param phone The phone number of the contact.
 * @return void
 */
void ContactManager::addContact(const std::string& name, const std::string& phone) {
    contacts[name] = phone;
}
```

+-----------+                 +-----------+
| WAYPOINT  |                 | ROUTE     |
+-----------+                 +-----------+
| nom (PK)  | ◄────────────►  | nom_debut (FK) |
| lat       | ◄────────────►  | nom_fin (FK)   |
| lon       |                 | distance       |
+-----------+                 +-----------+
    ▲                
    │               
    │               
+-----------+           
| VILLE     |           
+-----------+         
| nom (PK, FK) |
| code_postal  |
| nb_habitants |
| site         |
+-----------+
```

