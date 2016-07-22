<form action="account.php" method="post">
    <fieldset>
        <div class="form-group">
            <input class="form-control" name="username" value="<?= $username ?>" type="text"/>
        </div>
        <div class="form-group">  
            <input class="form-control" autocomplete="off" name="new_password" placeholder="New password" type="password"/>
        </div>
        <div class="form-group">  
            <input class="form-control" autocomplete="off" name="confirmation" placeholder="Password confirmation" type="password"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">Submit</button>
        </div>
    </fieldset>
</form>
<div>
    or back to <a href="/">portfolio</a>
</div>