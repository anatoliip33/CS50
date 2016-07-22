<?php

    // configuration
    require("../includes/config.php"); 
    
    // select user shares and symbol row
    $rows = CS50::query("SELECT symbol, shares FROM portfolios 
                WHERE user_id = ?", $_SESSION["id"]);
    
    // select user row
    $user_rows = CS50::query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
    
    // user cash
    $cash = $user_rows[0]["cash"];
    
    // new array for stock name, price,
    // ammount of shares, stock symbol, and total price of shares
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"],
                "shares_cash" => $row["shares"]*$stock["price"]
            ];
        }
    }
    
    // render portfolio, new array, and user cash
    render("portfolio.php", ["positions" => $positions, 
            "cash" => $cash, "title" => "Portfolio"]);
?>
