# Route-Planner
*Authors*
`Gaspard VIEUJEAN`
`Boris GANGUE`
`Ahmed YAHA`
---


# PROJECT STRUCTURE
```
|── ressource/
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

# Database

```
+-----------+
| CONTOUR   |
+-----------+
| num_pt (PK) |
| lat         |
| lon         |
+-----------+

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

aaaa
daihdiahdb
ta
t
at
ta