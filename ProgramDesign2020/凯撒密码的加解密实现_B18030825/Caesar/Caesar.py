from string import ascii_uppercase as _alphabet


__all__ = ['Caesar', 'CaesarPlus']


_ctoi = lambda c: _alphabet.index(c)
_itoc = lambda i: _alphabet[i]


class Caesar:
    def __init__(self, key=3):
        self._key = key

    @property
    def key(self):
        return self._key

    @key.setter
    def key(self, new_key):
        self._key = new_key


    def encrypt(self, msg):
        cipher = ""
        for m in msg.upper():
            if m in _alphabet:
                cipher += _itoc((_ctoi(m) + self._key) % 26)
            else:
                cipher += m
        return cipher

    def decrypt(self, cipher):
        msg = ""
        for c in cipher.upper():
            if c in _alphabet:
                msg += _itoc((_ctoi(c) - self._key) % 26)
            else:
                msg += c
        return msg

    def attack(self, cipher):
        res = []
        inital_key = self.key
        for k in range(26):
            self.key = k
            res.append((k, self.decrypt(cipher)))
        self.key = inital_key
        return res

    def __repr__(self):
        return "Caesar"



class CaesarPlus:
    def __init__(self, key=3):
        self._key = key

    @property
    def key(self):
        return self._key

    @key.setter
    def key(self, new_key):
        self._key = new_key


    def encrypt(self, msg):
        cipher = ""
        i = self._key
        for m in msg.upper():
            if m in _alphabet:
                cipher += _itoc((_ctoi(m) + i) % 26)
                i += 1
            else:
                cipher += m
        return cipher

    def decrypt(self, cipher):
        msg = ""
        i = self._key
        for c in cipher.upper():
            if c in _alphabet:
                msg += _itoc((_ctoi(c) - i) % 26)
                i += 1
            else:
                msg += c
        return msg

    def attack(self, cipher):
        res = []
        inital_key = self.key
        for k in range(26):
            self.key = k
            res.append((k, self.decrypt(cipher)))
        self.key = inital_key
        return res

    def __repr__(self):
        return "CaesarPlus"


# -------------------------------------------------
def test1():
    crypto = Caesar(13)

    msg = "the fox jumps over the lazy dog".upper()
    cipher = crypto.encrypt(msg)
    decrypted = crypto.decrypt(cipher)


    print(f"msg: {msg}")
    print(f"cipher: {cipher}")
    print(f"decrypted: {decrypted}")


def test2():
    crypto = CaesarPlus(13)

    msg = "the fox jumps over the lazy dog".upper()
    cipher = crypto.encrypt(msg)
    decrypted = crypto.decrypt(cipher)


    print(f"msg: {msg}")
    print(f"cipher: {cipher}")
    print(f"decrypted: {decrypted}")


if __name__ == "__main__":
    test1()
    test2()
