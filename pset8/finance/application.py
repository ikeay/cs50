import os
import re
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd


# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


class ValidationError(Exception):
    def __init__(self, message=None, code=None):
        super(ValidationError, self).__init__()
        if message is not None:
            self.message = message
        self.code = code


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    try:
        owned_shares = db.execute("SELECT symbol, name, shares FROM owned_shares WHERE user_id = :user_id", user_id=session["user_id"])
        users_row = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])

        _cash = float(users_row[0]["cash"])

        _total = _cash
        for i, item in enumerate(owned_shares):
            info = lookup(item["symbol"])
            owned_shares[i]["price"] = usd(float(info["price"]))
            owned_shares[i]["total"] = usd(float(info["price"]) * int(item["shares"]))
            _total += float(info["price"]) * int(item["shares"])

        total = usd(_total)
        cash = usd(_cash)

    except Exception as e:
        return apology(e, 400)

    return render_template("index.html", owned_shares=owned_shares, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        try:
            symbol, shares = buy_validation(request.form.get("symbol"), request.form.get("shares"))

            info = lookup(symbol)

            if not info:
                raise Exception("must provide valid sympol", 400)

            num = int(shares)

            cash_row = db.execute("SELECT users.cash FROM users WHERE users.id = :id", id=session["user_id"])

            if len(cash_row) != 1:
                raise Exception("your cash record is not found", 404)

            cash = float(cash_row[0]["cash"])

            sum = float(info["price"]) * num

            if sum > cash:
                raise Exception("cannot afford the number of shares", 400)

            # TODO: Should be rollback if failed
            db.execute("INSERT INTO histories(user_id, symbol, name, shares, price) VALUES (:user_id, :symbol, :name, :shares, :price)",
                       user_id=session["user_id"], symbol=info["symbol"], name=info["name"], shares=num, price=info["price"])

            owned_shares = db.execute("SELECT * FROM owned_shares WHERE symbol = :symbol AND user_id = :user_id",
                                      symbol=info["symbol"], user_id=session["user_id"])
            if len(owned_shares) == 0:
                db.execute("INSERT INTO owned_shares(user_id, symbol, name, shares) VALUES (:user_id, :symbol, :name, :shares)",
                            user_id=session["user_id"], symbol=info["symbol"], name=info["name"], shares=num)
            else:
                shares = int(owned_shares[0]["shares"]) + num
                db.execute("UPDATE owned_shares SET shares = :shares WHERE symbol = :symbol AND user_id = :user_id",
                           shares=shares, symbol=info["symbol"], user_id=session["user_id"])

            change = cash - sum
            db.execute("UPDATE users SET cash = :cash WHERE id = :user_id", cash=change, user_id=session["user_id"])

            return redirect("/")
        except ValidationError as e:
            return apology(e.message, e.code)
        except Exception as e:
            return apology(e, 400)

    else:
        return render_template("buy.html")


def buy_validation(symbol, shares):
    if not symbol:
        raise ValidationError("must provide symbol", 400)

    elif not shares:
        raise ValidationError("must provide shares", 400)

    elif not shares.isdecimal():
        if shares[0] == "-":
            raise ValidationError("must provide shares as positive number", 400)
        else:
            raise ValidationError("must provide shares as number", 400)

    return symbol, int(shares)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    histories = db.execute("SELECT symbol, shares, price, created_at FROM histories WHERE user_id = :user_id ORDER BY created_at DESC",
                           user_id=session["user_id"])

    for i, _ in enumerate(histories):
        histories[i]["price"] = usd(float(histories[i]["price"]))
    return render_template("history.html", histories=histories)


@app.route("/login", methods=["GET", "POST"])
def login():
    session.clear()

    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)
        info = lookup(symbol)
        if not info:
            return apology("invalid symbol", 400)
        return render_template("quoted.html", info=info)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username", 403)

        elif not password:
            return apology("must provide password", 403)

        elif password != confirmation:
            return apology("must provide same password and confirmation", 403)

        elif not allow_password_rule(password):
            return apology("require the number of password length is 8-100 and to include some number of letters, numbers and symbols", 403)

        user = db.execute("SELECT * FROM users WHERE username = :username", username=username)

        if len(user) > 0:
            return apology("do not use duplicate username", 403)

        # Query database for registration
        hash = generate_password_hash(password)
        db.execute("INSERT INTO users(username, hash) VALUES (:username, :hash)", username=username, hash=hash)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


def allow_password_rule(password):
    result = re.match('\A(?=.*?[a-z])(?=.*?\d)(?=.*?[!-/:-@[-`{-~])[!-~]{8,100}\Z(?i)', password)
    if result is None:
        return False
    return True


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        try:
            symbol, shares = sell_validation(request.form.get("symbol"), request.form.get("shares"))

            info = lookup(symbol)

            if not info:
                raise Exception("must provide valid symbol", 400)

            owned_shares_row = db.execute("SELECT * FROM owned_shares WHERE user_id = :user_id AND symbol = :symbol",
                                      user_id=session["user_id"], symbol=symbol)

            if len(owned_shares_row) < 1:
                raise Exception("you do not have such stocks", 400)

            owned_shares = int(owned_shares_row[0]["shares"])
            if owned_shares < shares:
                raise Exception("you do not have enough stocks", 400)

            cash_row = db.execute("SELECT users.cash FROM users WHERE users.id = :id", id=session["user_id"])

            if len(cash_row) != 1:
                raise Exception("your cash record is not found", 404)

            cash = float(cash_row[0]["cash"])

            # a stock’s current price
            sum = float(info["price"]) * shares

            # TODO: Should be rollback if failed
            db.execute("INSERT INTO histories(user_id, symbol, name, shares, price) VALUES (:user_id, :symbol, :name, :shares, :price)",
                       user_id=session["user_id"], symbol=info["symbol"], name=info["name"], shares=shares * -1, price=info["price"])

            if owned_shares - shares == 0:
                db.execute("DELETE FROM owned_shares WHERE user_id = :user_id AND symbol = :symbol", user_id=session["user_id"], symbol=symbol)
            else:
                db.execute("UPDATE owned_shares SET shares = :shares WHERE user_id = :user_id AND symbol = :symbol",
                           shares=owned_shares - shares, user_id=session["user_id"], symbol=symbol)

            db.execute("UPDATE users SET cash = :cash WHERE id = :user_id", cash=cash + sum, user_id=session["user_id"])

            return redirect("/")
        except ValidationError as e:
            return apology(e.message, e.code)
        except Exception as e:
            return apology(e, 400)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        try:
            symbols = db.execute("SELECT symbol FROM owned_shares WHERE user_id = :user_id", user_id=session["user_id"])
            return render_template("sell.html", symbols=symbols)
        except Exception as e:
            return apology(e, 400)


def sell_validation(symbol, shares):
    return buy_validation(symbol, shares)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

