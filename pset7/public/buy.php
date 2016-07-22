<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("buy_form.php", ["title" => "Buy"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate for correct entry buy form
        if (empty($_POST["symbol"]))
        {
            apologize("You must specify a stock to buy.");
        }
        elseif (empty($_POST["shares"]))
        {
            apologize("You must specify a number of shares.");
        }
        else if(lookup($_POST["symbol"]) === false)
        {
            apologize("Symbol not found");
        }
        elseif(preg_match("/^\d+$/", $_POST["shares"]) == false)
        {
            apologize("Invalid number of shares.");
        }
        
        // find stock by symbol on yahoo site  
        $stock = lookup($_POST["symbol"]);
        
        // ammount of shares to buy
        $buy_shares = $_POST["shares"];
        
        // worth of all bought shares 
        $worth = $stock["price"] * $buy_shares;
        
        // select user cash
        $user_cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $cash = $user_cash[0]["cash"];
        
        // check if user has enough cash to buy shares
        if ($worth > $cash)
        {
            apologize("You can't afford that.");
        }
        else
        {
            // update cash after user bought shares
            CS50::query("UPDATE users SET cash = cash - $worth
                    WHERE id = ?", $_SESSION["id"]);
            
            // insert bought shares into portfolios table
            CS50::query("INSERT INTO portfolios (user_id, symbol, shares) 
                VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + $buy_shares",
                $_SESSION["id"], strtoupper($_POST["symbol"]), $_POST["shares"]);
            
            // insert bought shares into portfolios table
            CS50::query("INSERT INTO history (user_id, symbol, shares, price, 
                transaction) VALUES(?, ?, ?, ?, 'BUY')", $_SESSION["id"], 
                strtoupper($_POST["symbol"]), $buy_shares, $stock["price"]);
            
            // redirect to portfolio
            redirect("/");
        }
    }
?>