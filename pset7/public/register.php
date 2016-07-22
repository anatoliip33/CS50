<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate for correct entry registration form
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        elseif (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must confirm your password.");
        }
        else if ($_POST["password"] !== $_POST["confirmation"])
        {
            apologize("Passwords do not match.");
        }
        
        // validate uniqueness of entry username
        $result = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 5000.0000)", 
            $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
        
        if ($result === 0)
        {
            apologize("This username is in use, try another");
        }
        else
        {
            // id of last registered user 
            $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
            $id = $rows[0]["id"];
            
            // user now logged in by storing user's ID in session
            $_SESSION["id"] = $id;
            
            // redirect to portfolio
            redirect("/");
        }
    }

?>