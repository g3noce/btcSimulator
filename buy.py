import bybit
import math
from pybit import usdt_perpetual

session_auth = usdt_perpetual.HTTP(
    endpoint="https://api.bybit.com/",
    api_key="5FLdbvQqybLAKtOi6o",
    api_secret="tsV6i846D8i9RxwS8wNpVZlV0LO1TXnMcgl7"
)

def truncate(number, digits) -> float:
    stepper = 10.0 ** digits
    return math.trunc(number * stepper) / stepper

client = bybit.bybit(test = False, api_key='5FLdbvQqybLAKtOi6o', api_secret='tsV6i846D8i9RxwS8wNpVZlV0LO1TXnMcgl7')
print('login to\n', client)

info = client.Market.Market_symbolInfo(symbol="BTCUSDT").result()
pos = client.LinearPositions.LinearPositions_myPosition(symbol="BTCUSDT").result()
get_wallet = client.Wallet.Wallet_getBalance(coin="USDT").result()

keys = pos[0]['result']
leverage = keys[0]['leverage']

keys = info[0]['result']
ask_price = keys[0]['ask_price']

balance = get_wallet[0]['result']['USDT']['available_balance']
qty = truncate(float(balance*leverage)/float(ask_price), 3)

keys = pos[0]['result']
position_value = keys[1]['position_value']
position_side = keys[1]['side']

if position_side == "Sell" and position_value != 0:
    cancel_all_order = session_auth.close_position(symbol="BTCUSDT")
    set_leverage = client.LinearPositions.LinearPositions_saveLeverage(symbol="BTCUSDT", buy_leverage=2, sell_leverage=2).result()
    set_buy_postion = client.LinearOrder.LinearOrder_new(side="Buy",symbol="BTCUSDT",order_type="Limit",qty=qty,price=ask_price,time_in_force="GoodTillCancel",reduce_only=False, close_on_trigger=False).result()
keys = pos[0]['result']
position_value = keys[0]['position_value']
position_side = keys[0]['side']

if position_side == "Buy" and position_value != 0:
    print("")
else:
    set_leverage = client.LinearPositions.LinearPositions_saveLeverage(symbol="BTCUSDT", buy_leverage=2, sell_leverage=2).result()
    set_buy_postion = client.LinearOrder.LinearOrder_new(side="Buy",symbol="BTCUSDT",order_type="Limit",qty=qty,price=ask_price,time_in_force="GoodTillCancel",reduce_only=False, close_on_trigger=False).result()
