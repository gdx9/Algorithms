import string

class CaesarCipher:
    def __init__(self):
        letters = [l for l in string.ascii_lowercase + " "]
        self.num_letters = len(letters)
        positions = [n for n in range(self.num_letters)]

        self.letter_positions = dict(zip(letters, positions))
        self.position_letters = dict(zip(positions, letters))

    def encrypt_message(self, message, shift=3):
        message = message.lower()

        encrypted = ""
        for letter in message:
            pos = self.letter_positions[letter] if(letter in self.letter_positions) else self.num_letters-1# position of ' ' for unknown symbols

            pos = (pos + shift) % self.num_letters# same as if(pos > max_pos-1): pos -= max_pos-1
            encrypted += self.position_letters[pos]

        return encrypted

    def decrypt_message(self, message, original_shift):
        return self.encrypt_message(message, -original_shift)

if __name__ == "__main__":
    original_message = "i love Okinawa, Kyiv and Osaka"
    shift = 8

    caesar = CaesarCipher()
    encrypted = caesar.encrypt_message(original_message, shift)
    decrypted = caesar.decrypt_message(encrypted, shift)
    print("original:  {}\nencrypted: {}\ndecrypted: {}".format(
        original_message, encrypted, decrypted))
