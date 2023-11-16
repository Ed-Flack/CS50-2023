# SQL Commands
## Creating the stocks table
```
CREATE TABLE stocks
(user_id NOT NULL, symbol TEXT NOT NULL, shares NUMERIC NOT NULL CHECK (shares > 0),
FOREIGN KEY(user_id) REFERENCES users(id), PRIMARY KEY(user_id, symbol));
```
## Creating the transactions table
```
CREATE TABLE transactions
(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, user_id NOT NULL, symbol TEXT NOT NULL,
action symbol TEXT NOT NULL, price NUMERIC NOT NULL, shares NUMERIC NOT NULL CHECK (shares > 0),
date_time TEXT NOT NULL, FOREIGN KEY(user_id) REFERENCES users(id));
```
