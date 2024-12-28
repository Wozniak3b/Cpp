# Debt Management System

This is a simple C++ application for managing user debts. The application allows users to register, log in, add debts, and display their debts.

## Features

- User registration
- User login
- Add debts to users
- Display user debts
- Save and load user data from files

## File Structure

- `main.cpp`: The main entry point of the application.
- `Database.hpp`: Contains the `Database` class for managing users and debts.
- `Users.hpp` and `Debts.hpp`: Contains the `User` and `Debts` class representing a user and debt.
- `users.txt`: File to store user data.
- `debts.txt`: File to store debt data.

## Example

```sh

1. Login
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
3. Logout

Choose an option: 1
---------------------
Here are all the users:
ID: 1, Username: Jakub
---------------------

Which user ID: 1
Description: Loan from friend
Amount: 100.50
```
