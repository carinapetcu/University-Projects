from Exceptions.Exceptions import ValidationError


class ValidateInput:
    def __init__(self):
        pass

    def validate_entry(self, acres_to_buy_sell, food, acres_to_plant, total_acres, grain_stocks, land_price):
        if acres_to_buy_sell + total_acres < 0:
            raise ValidationError("There are not enough acres to sell!")
        if acres_to_buy_sell > grain_stocks // land_price:
            raise ValidationError("There are not enogh units to buy the land!")
        if grain_stocks - acres_to_buy_sell * land_price < food:
            raise ValidationError("There are not enough units to buy the food!")
        if acres_to_buy_sell + total_acres < acres_to_plant:
            raise ValidationError("There are not enough acres to plant!")
