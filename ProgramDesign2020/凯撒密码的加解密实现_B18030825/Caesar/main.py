import logging
import json

import PySimpleGUI as sg

import Caesar



# ------ Logger Setup ------ #
logging.basicConfig(format='%(asctime)s %(message)s')
logger = logging.getLogger('simple_example')
logger.setLevel(logging.DEBUG)

# ------ Menu Definition ------ #
menu_def = [['&File', ['&Open', '&Save', 'E&xit']],
            ['&Cipher', ['Caesar', 'CaesarPlus']],
            ['&Help', '&About'], ]

# ------ Layout Definition ------ #
layout = [
    [sg.Menu(menu_def, tearoff=True)],
    [sg.Text("Plaintext: ", size=(8, 1)), sg.Multiline("Please input your plaintext here!", key="-PLAINTEXT-")],
    [sg.Text("Key: ", size=(8, 1)),
     sg.Slider(range=(0, 25), size=(32, 15), orientation='h', default_value=3, key="-KEY-", enable_events=True,)],
    [sg.Text("", size=(8, 1)), sg.Button("encrypt", size=(10, 1), border_width=2, pad=(15,15)), sg.Button("decrypt", size=(10, 1), border_width=2, pad=(15,15)), sg.Button("attack", size=(10, 1), border_width=2, pad=(15,15))],
    [sg.Text("Ciphertext: ", size=(8, 1)), sg.Multiline(key="-CIPHERTEXT-")]
]


window = sg.Window(title="Caesar Cipher Tool", layout=layout, margins=(30, 50))
crypto = Caesar.Caesar()


while True:
    event, values = window.read()

    if event == None or event == 'Exit':
        logger.warning("EXIT...")
        break

    elif event == "encrypt":
        plain = values["-PLAINTEXT-"]
        cipher = crypto.encrypt(plain)
        window["-CIPHERTEXT-"].update(cipher)
        logger.info(f"ENCRYPT: {plain.strip()} -> {cipher.strip()}")

    elif event == "decrypt":
        cipher = values["-CIPHERTEXT-"]
        plain = crypto.decrypt(cipher)
        window["-PLAINTEXT-"].update(plain)
        logger.info(f"DECRYPT: {cipher.strip()} -> {plain.strip()}")

    elif event == "attack":
        cipher = values["-CIPHERTEXT-"]
        guesses = crypto.attack(cipher)
        plains = "\n".join(str(k) + " " + guess.strip() for k, guess in guesses)
        window["-PLAINTEXT-"].update(plains)
        logger.info(f"ATTACK: {cipher.strip()} -> {plains}")

    elif event == "-KEY-":
        crypto.key = int(values["-KEY-"])
        logger.info(f"Key has been set as {crypto.key}")

    elif event == "Open":
        filename = sg.popup_get_file('Please enter a file name to open')
        with open(filename, "r") as f:
            data = json.loads(f.read())
        window["-PLAINTEXT-"].update(data["Plaintext"])
        window["-CIPHERTEXT-"].update(data["Ciphertext"])
        window["-KEY-"].update(data["Key"])
        if data["Crypto"] == "Caesar":
            crypto = Caesar.Caesar(data["Key"])
        elif data["Crypto"] == "CaesarPlus":
            crypto = Caesar.CaesarPlus(data["Key"])
        logger.info(f"OPEN: File {filename} has been loaded, with data={data}")

    elif event == "Save":
        data = dict()
        data["Plaintext"] = values["-PLAINTEXT-"].strip()
        data["Ciphertext"] = values["-CIPHERTEXT-"].strip()
        data["Key"] = int(values["-KEY-"])
        data["Crypto"] = str(crypto)
        data = json.dumps(data)
        filename = sg.popup_get_file('Please enter a file name to save')
        with open(filename, "w") as f:
            f.write(data)
        logger.info(f"SAVE: File has been saved to {filename} with data={data}")

    elif event == "Caesar":
        key = int(values["-KEY-"])
        crypto = Caesar.Caesar(key)
        logger.warning(f"CRYPTO: Crypto has been switched to Caesar with key={key}")

    elif event == "CaesarPlus":
        key = int(values["-KEY-"])
        crypto = Caesar.CaesarPlus(key)
        logger.warning(f"CRYPTO: Crypto has been switched to CaesarPlus with key={key}")

    elif event == "About":
        sg.Popup("Written by Soreat_u")

    else:
        logger.error(f"Unhandled event: {event}")


window.close()