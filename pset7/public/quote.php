<?php
    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Get Quote"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate for correct entry quote form
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a symbol.");
        }
        else if(lookup($_POST["symbol"]) === false)
        {
            apologize("Symbol not found");
        }
        else
        {
            // find stock symbol from quote form on yahoo site 
            $stock = lookup($_POST["symbol"]);
            // stock name, price and symbol
            $name = $stock["name"];
            $symbol = $stock["symbol"];
            $price = $stock["price"];
            
            // render quote template with stock values
            render("quote.php", ["name" => $name, 
                                "symbol" => $symbol, "price" => $price]);
        }
    }
?>