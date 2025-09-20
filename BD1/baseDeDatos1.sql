USE oscarTest2;


#1
SELECT * FROM EMPLOYEE
WHERE DEPARTMENT = 'HR';

#2
SELECT name, last_name FROM EMPLOYEE
WHERE DEPARTMENT = 'HR';

#3 Combine two queries into one result set
SELECT name FROM EMPLOYEE e 
UNION SELECT name FROM DEPARTMENT d ;

#4 Select the difference between two tables
SELECT department
FROM EMPLOYEE
WHERE department NOT IN (SELECT name FROM DEPARTMENT);

#5 Select the intersection between two tables and displays all rows
SELECT E.*
FROM EMPLOYEE E
INNER JOIN DEPARTMENT D
ON E.department = D.name ;

#6 Cartesian product, all ordered pairs
Select * FROM EMPLOYEE, DEPARTMENT;

#7 Renaming
SELECT 
name as nombre,
last_name as apellido
FROM EMPLOYEE;


