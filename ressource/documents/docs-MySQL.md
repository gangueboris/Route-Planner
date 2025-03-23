Write here steps that we have to follow to setup the database on our local machine and your todo list in order to track your evolution in the project.

This is a proposal on how it should looks like:


## DATABASE CONNEXION INFORMATIONS
host: localhost
database: routeplanner
username: routePlanner
password: azerty1234

## CREATE DATABASE
``` sql
create database 'databasename';
use 'databasename';
source itineraire.sql;
```

## CREATE A MYSQL USER
``` sql
CREATE USER 'username'@'localhost' IDENTIFIED BY 'password';
GRANT ALL PRIVILEGES ON my_database.* TO 'username'@'localhost';
FLUSH PRIVILEGES;
```

## COMMAND TO CONNECT MYSQL WITH A SPECIFIC USER 
```sh
mysql -u routePlanner -p -h localhost
```

## VERIFY USER PRIVILEGES
``` sql
SHOW GRANTS FOR 'username'@'localhost';
```
```sql
SELECT user, host FROM mysql.user WHERE user = 'routePlanner';
SELECT user, host FROM mysql.user;
```

## TODO
1. Setup the database login
2. Comment my project
3. Add Point on each wall (QGraphicsLineItem)

## Issues
- Can't load data for the database.



