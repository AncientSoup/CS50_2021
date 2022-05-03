import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


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

# Added an "add cash" function.
@app.route("/add-cash", methods=["GET","POST"])
@login_required
def add_cash():
    if request.method == "POST":
        cash = db.execute("UPDATE users SET cash = cash + :amount WHERE id = :user_id", amount=request.form.get("cash"), user_id=session["user_id"])
        flash("Cash successfully added.")
        return redirect("/")
    else:
        return render_template("add-cash.html")
    
    
@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user = session["user_id"]
    # learned group function through https://www.w3schools.com/sql/sql_groupby.asp
    stock = db.execute("SELECT symbol, name, price, SUM(shares) as finals FROM transactions WHERE user_id = ? GROUP BY symbol", user)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user)[0]["cash"]
    final = cash
    
    for i in stock:
        final += i["price"] * i["finals"]
        
    return render_template("index.html", stock=stock, cash=cash, usd=usd, final=final)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        #.upper is used to prevent the need of uppercasing the symbols later on.
        symbol = request.form.get("symbol").upper()
        shares = int(request.form.get("shares"))
        stock = lookup(symbol)
        if not symbol:
            return apology("Symbol missing.")
        if not stock:
            return apology("Symbol typed is invalid.")
        elif shares <= 0:
            return apology("Shares should be greater than 0.")
        # To make sure the shares don't have any decimal points or invalid characters.
        elif not request.form.get("shares").isdigit():
            return apology("Number of shares is invalid.")
            
        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        
        stock_price = stock["price"]
        stock_name = stock["name"]
        total = stock_price * shares
        
        if cash < total:
            return apology("Not enough money.")
        elif cash == 0:
            return apology("Bruh you're broke.")
        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total, user_id)
            db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)", user_id, stock_name, shares, stock_price, "buy", symbol)
        
        return redirect("/")
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transaction = db.execute("SELECT symbol, price, shares, time FROM transactions WHERE user_id=:user_id", user_id=session["user_id"])
    for i in range(len(transaction)):
        transaction[i]["price"] = usd(transaction[i]["price"])
    return render_template("history.html", transaction=transaction)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Type in a stock symbol.")
            
        stock = lookup(symbol)
        # elif doesn't work here and crashes the entire website for some reason. Probably have figured it out by the time this problem set has already been submitted.
        if not stock:
            return apology("Symbol not found.")
        return render_template("success_quote.html", stock = stock)
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        pw = request.form.get("password")
        confirm = request.form.get("confirmation")
        
        if not username:
            return apology("Missing username.")
        elif not pw:
            return apology("Missing password.")
        elif not confirm:
            return apology("Type in the same password.")
        elif pw != confirm:
            return apology("Passwords don't match.")
        hash = generate_password_hash(pw)
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)    
            return redirect("/")
        except:
            return apology("Username already used.")
    else:
        return render_template("reg.html")
        
        
@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        user = session["user_id"]
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        if shares <= 0:
            return apology("Share(s) must be above 0.")
        
        name = lookup(symbol)["name"]
        price = lookup(symbol)["price"]
        owned = db.execute("SELECT SUM(shares) FROM transactions WHERE user_id = ? AND symbol = ?", user, symbol)[0]["SUM(shares)"]
        if owned < shares:
            return apology("Not enough shares.")
        
        final_cash = shares * price
        
        ccash = db.execute("SELECT cash FROM users WHERE id = ?", user)[0]["cash"]
        # To update the user's cash.
        db.execute("UPDATE users SET cash = ? WHERE id = ? ", ccash+final_cash, user)
        db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)", user, name, -shares, price, "sell", symbol)
        
        return redirect("/")
    else:
        user = session["user_id"]
        symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", user)
        return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
