<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $rows = CS50::query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        $user_name = $rows[0]["username"];
        
        // else render form
        render("account_form.php", ["title" => "Account", "username" => $user_name]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate for correct entry account form
        if (empty($_POST["username"]))
        {
            apologize("You must provide your new username.");
        }
        elseif (empty($_POST["new_password"]))
        {
            apologize("You must provide your new password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must confirm your new password.");
        }
        else if ($_POST["new_password"] !== $_POST["confirmation"])
        {
            apologize("Passwords do not match.");
        }
        
        // validate uniqueness of update username in account and update password 
        $result = CS50::query("UPDATE IGNORE users SET username = ?, hash = ? WHERE id = ?", 
            $_POST["username"], password_hash($_POST["new_password"], PASSWORD_DEFAULT), 
            $_SESSION["id"]);
        
        if ($result === 0)
        {
            apologize("This username is in use, try another");
        }
        
        else
        {
            logout();
            redirect("/");
        }
    }
        
?>