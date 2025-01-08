# Debt Management System

This is a simple C++ application for managing user debts. The application allows users to register, log in, add debts, and display their debts.

## Features

- User registration
- User login
- Add debts to users
- Display user debts
- Mark debts as paid
- Save and load user data from files

## File Structure

- `main.cpp`: The main entry point of the application.
- `Database.hpp`: Contains the `Database` class for managing users and debts.
- `Users.hpp`: Contains the `User` class representing a user.
- `Debts.hpp`: Contains the `Debt` class representing a debt.
- `users.txt`: File to store user data.
- `debts.txt`: File to store debt data.

## Example

```sh
Files not found. Starting with empty database

2. Register
3. Exit

Choose an option: 2
---------------------
Username: Jakub
Password: my_secret_key
User registered with ID: 1

1. Login
2. Register
3. Exit

Choose an option: 1
---------------------
Username: Jakub
Secret Key: my_secret_key

1. Add debt
2. Display my debts
3. Mark debt as paid
4. Logout

Choose an option: 1
---------------------
Here are all the users:
ID: 1, Username: Jakub
ID: 2, username: Jakub2
---------------------

Which user ID: 1
Description: Loan from friend
Amount: 100.50
Debt added successfully
```

## How to Run

1. Compile the project using a C++ compiler.
2. Run the executable.

## Authors

- Jakub Wozniak
  Kraków 2025r.
