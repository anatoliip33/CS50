<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select class="form-control" name="symbol">
                <option disabled="" selected="" value="">Symbol</option>
                <?php foreach ($shares as $share): ?>
                    <option value="<?= $share["symbol"] ?>">
                        <?= $share["symbol"] ?>
                    </option>
                <?php endforeach ?>
            </select>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">Sell</button>
        </div>
    </fieldset>
</form>