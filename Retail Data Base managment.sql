-- create database 
create database RETAL_DATA;


-- create customer table

create  table Customer (
  CustomerID int primary key ,
  First_name varchar(20) not null,
  Middle_name varchar(20) not null,
  Last_name varchar(20) not null,
  [Location] varchar(20)); 

-- create customer phone

create table CustomerPhone (
  CustomerID int,
  phone NVARCHAR(15),
  foreign key (CustomerID) REFERENCES Customer (CustomerID));

-- create The store table

create table store (
   storeID int primary key identity(1,1),
  [location] varchar(50) not null);  

-- create The product table

CREATE TABLE Product (
    ProductID INT PRIMARY KEY IDENTITY(1,1),
    Name NVARCHAR(100) NOT NULL,
    Description NVARCHAR(255),
    Category NVARCHAR(100),
    Price DECIMAL(10, 2) NOT NULL,
    Cost DECIMAL(10, 2) NOT NULL,
    QuantityInStock INT NOT NULL,
    StoreID INT,
    FOREIGN KEY (StoreID) REFERENCES Store(StoreID)
);

-- Create the Employee table
CREATE TABLE Employee (
    EmployeeID INT PRIMARY KEY ,
    First_name varchar(20) not null,
  Middle_name varchar(20) not null,
  Last_name varchar(20) not null,
    [Role] VARCHAR(50)
);

-- create the  Employee Phone table
create table EmployeePhone (
  EmployeeID int,
  phone NVARCHAR(15),
  foreign key (EmployeeID) REFERENCES Employee ( EmployeeID));

-- Create the Transaction table
CREATE TABLE [Transaction] (
    TransactionID INT PRIMARY KEY ,
    DateTime DATETIME ,
    CustomerId INT,
    TotalPrice DECIMAL(7, 3) NOT NULL,
    PaymentMethod NVARCHAR(100) NOT NULL,
    FOREIGN KEY (CustomerId) REFERENCES Customer(CustomerID)
);

-- create relation ship table for the employee and the product
create table [Transaction_Product] (
   TransactionID int,
   ProductID int,
   primary key (TransactionID,ProductID),
   foreign key (TransactionID) references [Transaction](TransactionID),
   foreign key (ProductID) references product(ProductID));

-- create relationship table for the Customer and the transaction
create table Transaction_Employee(
  CustomerID int,
  EmployeeID int,
  primary key (CustomerID ,EmployeeID),
  foreign key (CustomerID) REFERENCES Customer (CustomerID),
  foreign key (EmployeeID) REFERENCES Employee ( EmployeeID)
);


-- Insert data into the Customer table
INSERT INTO Customer (CustomerID, First_name, Middle_name, Last_name, [Location])
VALUES 
(1, 'John', 'A.', 'Doe', 'New York'),
(2, 'Jane', 'B.', 'Smith', 'Los Angeles'),
(3, 'Michael', 'C.', 'Johnson', 'Chicago');

-- Insert data into the CustomerPhone table
INSERT INTO CustomerPhone (CustomerID, phone)
VALUES 
(1, '555-1234'),
(2, '555-5678'),
(3, '555-8765');

-- Insert data into the Store table
INSERT INTO Store ([location])
VALUES 
('New York'),
('Los Angeles'),
('Chicago');

-- Insert data into the Product table
INSERT INTO Product (Name, Description, Category, Price, Cost, QuantityInStock, StoreID)
VALUES 
('Laptop', '15 inch laptop', 'Electronics', 1200.00, 800.00, 10, 1),
('Smartphone', 'Latest model smartphone', 'Electronics', 800.00, 500.00, 20, 2),
('Tablet', '10 inch tablet', 'Electronics', 600.00, 400.00, 15, 3);

-- Insert data into the Employee table
INSERT INTO Employee (EmployeeID, First_name, Middle_name, Last_name, [Role])
VALUES 
(1, 'Alice', 'D.', 'Brown', 'Manager'),
(2, 'Bob', 'E.', 'Davis', 'Sales Associate'),
(3, 'Carol', 'F.', 'Garcia', 'Cashier');

-- Insert data into the EmployeePhone table
INSERT INTO EmployeePhone (EmployeeID, phone)
VALUES 
(1, '555-1111'),
(2, '555-2222'),
(3, '555-3333');

-- Insert data into the Transaction table
INSERT INTO [Transaction] (TransactionID, DateTime, CustomerId, TotalPrice, PaymentMethod)
VALUES 
(1, '2023-05-01 10:00:00', 1, 1800.00, 'Credit Card'),
(2, '2023-05-02 11:00:00', 2, 800.00, 'Cash'),
(3, '2023-05-03 12:00:00', 3, 600.00, 'Credit Card');

-- Insert data into the Transaction_Product table
INSERT INTO Transaction_Product (TransactionID, ProductID)
VALUES 
(1, 1),
(1, 2),
(2, 2),
(3, 3);

-- Insert data into the Transaction_Employee table
INSERT INTO Transaction_Employee (CustomerID, EmployeeID)
VALUES 
(1, 1),
(2, 2),
(3, 3);

-- Query to verify data insertion
SELECT * FROM Customer;
SELECT * FROM Employee;
SELECT * FROM [Transaction];
SELECT * FROM Store;
SELECT * FROM Product;
SELECT * FROM Transaction_Product;
SELECT * FROM Transaction_Employee;


select * from Customer;
select * from Employee;
Select * from [Transaction];
select * from store;
select * from product;
select * from [Transaction_Product];
select * from Transaction_Employee;
