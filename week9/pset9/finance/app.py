import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
import re

from helpers import apology, login_required, lookup, usd, passwordMeetsComplexityRequirements, isfloat

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute(
        "SELECT symbol, shares FROM stocks WHERE user_id = ?", session["user_id"]
    )
    balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0][
        "cash"
    ]
    totalBalance = balance
    stocks = []
    for row in rows:
        stockLookup = lookup(row["symbol"])
        totalBalance += stockLookup["price"]
        stocks.append(
            {
                "symbol": stockLookup["symbol"],
                "price": usd(stockLookup["price"]),
                "shares": row["shares"],
                "totalPrice": usd(stockLookup["price"] * row["shares"]),
            }
        )
    return render_template(
        "index.html",
        balance=usd(balance),
        totalBalance=usd(totalBalance),
        stocks=stocks,
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        stockLookup = lookup(request.form.get("symbol"))
        if stockLookup == None:
            return apology("Stock does not exist")
        if (not request.form.get("shares").isdigit()):
            return apology("Shares must be a positive integer")
        user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]
        shares = int(request.form.get("shares"))
        price = round(stockLookup["price"] * shares, 2)
        if price > user["cash"]:
            return apology("Not enough money in account")
        balance = round(user["cash"] - price, 2)
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", balance, session["user_id"]
        )
        ownedStocks = db.execute(
            "SELECT * FROM stocks WHERE user_id = ? AND symbol = ?",
            session["user_id"],
            stockLookup["symbol"],
        )
        if len(ownedStocks) > 0:
            updatedShares = shares + ownedStocks[0]["shares"]
            print("updated shares: " + str(updatedShares))
            db.execute(
                "UPDATE stocks SET shares = ? WHERE user_id = ? AND symbol = ?",
                updatedShares,
                session["user_id"],
                stockLookup["symbol"],
            )
        else:
            db.execute(
                "INSERT INTO stocks (user_id, symbol, shares) VALUES (?, ?, ?)",
                session["user_id"],
                stockLookup["symbol"],
                shares,
            )
        db.execute(
            "INSERT INTO transactions (user_id, symbol, action, price, shares, date_time) VALUES (?, ?, ?, ?, ?, ?);",
            session["user_id"],
            stockLookup["symbol"],
            "BUY",
            stockLookup["price"],
            shares,
            datetime.now(),
        )
        return redirect("/")
    if request.args.get("symbol") != None:
        return render_template("buy.html", symbol=request.args.get("symbol"))
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT * FROM transactions WHERE user_id = ?", session["user_id"]
    )
    for transaction in transactions:
        transaction.update(
            {"total_price": usd(transaction["price"] * transaction["shares"])}
        )
        transaction["price"] = usd(transaction["price"])
    return render_template("history.html", transactions=transactions)


@app.route("/profile")
@login_required
def profile():
    """User profile settings"""
    username = db.execute(
        "SELECT username FROM users WHERE id = ?", session["user_id"]
    )[0]["username"]
    return render_template("profile.html", username=username)


@app.route("/change-password", methods=["GET", "POST"])
@login_required
def changePassword():
    """Change password"""
    if request.method == "POST":
        oldPassword = request.form.get("oldPassword")
        newPassword = request.form.get("newPassword")
        if oldPassword == "" or newPassword == "":
            return apology("Did not enter old and/or new password")
        storedPassword = db.execute(
            "SELECT hash FROM users WHERE id = ?", session["user_id"]
        )[0]["hash"]
        if not check_password_hash(storedPassword, oldPassword):
            return apology("Old password is incorrect")
        if not passwordMeetsComplexityRequirements(request.form.get("newPassword")):
            return apology(
                "Password must be longer than 8 characters and contain upper case, lower case, numbers, and special characters"
            )
        db.execute(
            "UPDATE users SET hash = ? WHERE id = ?",
            generate_password_hash(newPassword),
            session["user_id"],
        )
        flash("Password changed!")
    return render_template("change-password.html")


@app.route("/add-funds", methods=["GET", "POST"])
@login_required
def addFunds():
    """Add funs to account"""
    balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    if request.method == "POST":
        print(request.form.get("funds"))
        print("ed look" + str(isfloat(request.form.get("funds"))))
        if (not isfloat(request.form.get("funds"))):
            return apology("Funds must be more than $1.00")
        balance = round(float(request.form.get("funds")) + balance, 2)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, session["user_id"])
        flash("Funds added!")
    return render_template("add-funds.html", balance=usd(balance))


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))
        if stock == None:
            return apology("Stock does not exist")
        stock["price"] = usd(stock["price"])
        stocks = []
        stocks.append(stock)
        return render_template("quoted.html", stocks=stocks)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if (
            request.form.get("username") == ""
            or request.form.get("password") == ""
            or request.form.get("confirmation") == ""
        ):
            return apology("Did not fill in all required fields")
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )
        if len(rows) != 0:
            return apology("Username already exists")
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match")
        if not passwordMeetsComplexityRequirements(request.form.get("password")):
            return apology(
                "Password must be longer than 8 characters and contain upper case, lower case, numbers, and special characters"
            )
        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            request.form.get("username"),
            generate_password_hash(request.form.get("password")),
        )
        return redirect("/")
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        if request.form.get("symbol") == "":
            return apology("No stock selected")
        stocks = db.execute(
            "SELECT symbol, shares FROM stocks WHERE user_id = ? AND symbol = ?",
            session["user_id"],
            request.form.get("symbol"),
        )
        if len(stocks) == 0 or stocks[0]["symbol"] != request.form.get("symbol"):
            return apology("Stock not owned")

        if (not request.form.get("shares").isdigit()):
            return apology("Shares must be a positive integer")

        if int(request.form.get("shares")) > stocks[0]["shares"]:
            return apology("You do not own that many shares")

        shares = int(request.form.get("shares"))
        updatedShares = stocks[0]["shares"] - shares
        if updatedShares == 0:
            db.execute(
                "DELETE FROM stocks WHERE user_id = ? and symbol = ? ",
                session["user_id"],
                request.form.get("symbol"),
            )
        else:
            db.execute(
                "UPDATE stocks SET shares = ? WHERE user_id = ? and symbol = ? ",
                updatedShares,
                session["user_id"],
                request.form.get("symbol"),
            )
        stockLookup = lookup(request.form.get("symbol"))
        db.execute(
            "INSERT INTO transactions (user_id, symbol, action, price, shares, date_time) VALUES (?, ?, ?, ?, ?, ?);",
            session["user_id"],
            stockLookup["symbol"],
            "SELL",
            stockLookup["price"],
            shares,
            datetime.now(),
        )
        newBalance = (
            db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0][
                "cash"
            ]
            + stockLookup["price"]
        )
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", newBalance, session["user_id"]
        )
        return redirect("/")

    stocks = db.execute(
        "SELECT symbol, shares FROM stocks WHERE user_id = ?", session["user_id"]
    )
    if request.args.get("symbol") != None:
        return render_template(
            "sell.html", stocks=stocks, symbol=request.args.get("symbol")
        )
    return render_template("sell.html", stocks=stocks)
