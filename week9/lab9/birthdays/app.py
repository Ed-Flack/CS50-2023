import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST", "PUT", "DELETE"])
def index():
    if request.method == "POST":
        # TODO: Add the user's entry into the database
        print("test")
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        db.execute(
            "INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)",
            name,
            month,
            day,
        )
        return redirect("/")

    elif request.method == "PUT":
        id = request.form.get("id")
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        db.execute(
            "UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id=?",
            name,
            month,
            day,
            id,
        )
        return "saved"

    elif request.method == "DELETE":
        id = request.form.get("id")
        db.execute("DELETE FROM birthdays WHERE id=?", id)
        birthdays = db.execute("SELECT * FROM birthdays")
        return "deleted"

    else:
        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)
