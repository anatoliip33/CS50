<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // select user stock symbol 
        $rows = CS50::query("SELECT symbol FROM portfolios 
                        WHERE user_id = ?", $_SESSION["id"]);
        // render form
        render("sell_form.php", ["title" => "Sell", "shares"=> $rows]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must select a stock to sell.");
        }
        else
        {
            // find stock with symbol from sell form on yahoo site
            $stock = lookup($_POST["symbol"]);
            
            // select user stock with symbol from sell form 
            // in portfolios table
            $rows = CS50::query("SELECT * FROM portfolios 
                    WHERE user_id = ? AND symbol = ?", $_SESSION["id"], 
                    $_POST["symbol"]);
            
            // ammount of shares
            $shares = $rows[0]["shares"];
            
            // worth of all shares
            $worth = $stock["price"] * $shares;
            
            // remove shares that where sold from potrfolios table
            $sold = CS50::query("DELETE FROM portfolios WHERE user_id = ?
                    AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
            
            // update the user cash in the users table to the value of shares sold
            $update_cash = CS50::query("UPDATE users SET cash = cash + $worth
                    WHERE id = ?", $_SESSION["id"]);
            
            // insert bought shares into portfolios table
            CS50::query("INSERT INTO history (user_id, symbol, shares, price, 
                transaction) VALUES(?, ?, ?, ?, 'SELL')", $_SESSION["id"], 
                $_POST["symbol"], $shares, $stock["price"]);
            
            redirect("/"); 
        }
    }
?>