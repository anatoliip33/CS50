<?php

    // configuration
    require("../includes/config.php");
    
    $histories = CS50::query("SELECT * FROM history WHERE user_id = ?", $_SESSION["id"]);
    
    // render portfolio, new array, and user cash
    render("history.php", ["title" => "History", "histories" => $histories]);
?>