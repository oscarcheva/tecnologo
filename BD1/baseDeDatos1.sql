USE OscarTest;

CREATE TABLE
    EMPLOYEE (
        id int AUTO_INCREMENT PRIMARY KEY,
        name varchar(50),
        last_name varchar(50),
        department varchar(50)
    );

CREATE TABLE
    DEPARTMENT (
        id int AUTO_INCREMENT PRIMARY KEY,
        name varchar(50),
        address varchar(50)
    );

INSERT INTO
    EMPLOYEE (name, last_name, department)
VALUES
    ("Oscar", "Echeverria", "IT"),
    ("Lusnery", "Bello", "HR"),
    ("Enrique", "Ache", "HR"),
    ("Victoria", "Ortega", "Accounting"),
    ("Victorio", "Ortego", "Operations");

INSERT INTO
    DEPARTMENT (name, address)
VALUES
    ("IT", "2nd Floor"),
    ("HR", "3rd Floor"),
    ("Accounting", "4th Floor");

#1
SELECT
    *
FROM
    EMPLOYEE
WHERE
    DEPARTMENT = 'HR';

#2
SELECT
    name,
    last_name
FROM
    EMPLOYEE
WHERE
    DEPARTMENT = 'HR';

#3 Combine two queries into one result set
SELECT
    name
FROM
    EMPLOYEE e
UNION
SELECT
    name
FROM
    DEPARTMENT d;

#4 Select the difference between two tables
SELECT
    department
FROM
    EMPLOYEE
WHERE
    department NOT IN(
        SELECT
            name
        FROM
            DEPARTMENT
    );

#5 Select the intersection between two tables and displays all rows
SELECT
    E.*
FROM
    EMPLOYEE E
    INNER JOIN DEPARTMENT D ON E.department = D.name;

#6 Cartesian product, all ordered pairs
Select
    *
FROM
    EMPLOYEE,
    DEPARTMENT;

#7 Renaming
SELECT
    name as nombre,
    last_name as apellido
FROM
    EMPLOYEE;